//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#include "HadrontherapyRBE.hh"
#include "HadrontherapyMatrix.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <numeric>

#define width 15L

using namespace std;

// TODO: Perhaps we can use the material database???
const std::map<G4String, G4int> elements = {
    {"H", 1},
    {"He", 2},
    {"Li", 3},
    {"Be", 4},
    {"B", 5},
    {"C", 6},
    {"N", 7},
    {"O", 8},
    {"F", 9},
    {"Ne", 10}
};

HadrontherapyRBE* HadrontherapyRBE::instance = nullptr;

HadrontherapyRBE* HadrontherapyRBE::GetInstance()
{
    return instance;
}

HadrontherapyRBE* HadrontherapyRBE::CreateInstance(G4int voxelX, G4int voxelY, G4int voxelZ, G4double massOfVoxel)
{
    if (instance) delete instance;
    instance = new HadrontherapyRBE(voxelX, voxelY, voxelZ, massOfVoxel);
    return instance;
}

HadrontherapyRBE::HadrontherapyRBE(G4int voxelX, G4int voxelY, G4int voxelZ, G4double massOfVoxel)
: fNumberOfVoxelsAlongX(voxelX),
fNumberOfVoxelsAlongY(voxelY),
fNumberOfVoxelsAlongZ(voxelZ),
fNumberOfVoxels(voxelX * voxelY * voxelY),
fMassOfVoxel(massOfVoxel)
{
    CreateMessenger();
    
    // x axis for 1-D plot
    // TODO: Remove
    x = new G4double[fNumberOfVoxelsAlongX];
    
    for (G4int i = 0; i < fNumberOfVoxelsAlongX; i++)
    {
        x[i] = 0;
    }
    
}

HadrontherapyRBE::~HadrontherapyRBE()
{
    delete[] x;
    delete fMessenger;
}

void HadrontherapyRBE::PrintParameters()
{
    G4cout << "RBE Cell line: " << fActiveCellLine << G4endl;
    G4cout << "RBE Dose threshold value: " << fDoseCut / gray << " gray" << G4endl;
    G4cout << "RBE Alpha X value: " << fAlphaX * gray << " 1/gray" << G4endl;
    G4cout << "RBE Beta X value: " << fBetaX * pow(gray, 2) << " 1/gray2" << G4endl;
}

/**
 * @short Split string into parts using a delimiter.
 *
 * @param line a string to be splitted
 * @param delimiter a string to be looked for
 *
 * Usage: Help function for reading CSV
 * Also remove spaces and quotes around.
 * Note: If delimiter is inside a string, the function fails!
 */
vector<G4String> split(const G4String& line, const G4String& delimiter)
{
    vector<G4String> result;
    
    size_t current = 0;
    size_t pos = 0;
    
    while(pos != G4String::npos)
    {
        pos = line.find(delimiter, current);
        G4String token = line.substr(current, pos - current);
        token = token.strip(G4String::both);
        token = token.strip(G4String::both, '\"');
        result.push_back(token);
        current = pos + delimiter.size();
    }
    return result;
}

void HadrontherapyRBE::LoadLEMTable(G4String path)
{
    // TODO: Check for presence? Perhaps we want to be able to load more
    
    ifstream in(path);
    if (!in)
    {
        stringstream ss;
        ss << "Cannot open LEM table input file: " << path;
        G4Exception("HadrontherapyRBE::LoadData", "WrongTable", FatalException, ss.str().c_str());
    }
    
    // Start with the first line
    G4String line;
    if (!getline(in, line))
    {
        stringstream ss;
        ss << "Cannot read header from the LEM table file: " << path;
        G4Exception("HadrontherapyRBE::LoadLEMTable", "CannotReadHeader", FatalException, ss.str().c_str());
    }
    vector<G4String> header = split(line, ",");
    
    // Find the order of columns
    std::vector<G4String> columns = { "alpha_x", "beta_x", "D_t", "specific_energy", "alpha", "beta", "cell", "particle"};
    std::map<G4String, int> columnIndices;
    for (auto columnName : columns)
    {
        auto pos = find(header.begin(), header.end(), columnName);
        if (pos == header.end())
        {
            stringstream ss;
            ss << "Column " << columnName << " not present in the LEM table file.";
            G4Exception("HadrontherapyRBE::LoadLEMTable", "ColumnNotPresent", FatalException, ss.str().c_str());
        }
        else
        {
            columnIndices[columnName] = distance(header.begin(), pos);
        }
    }
    
    // Continue line by line
    while (getline(in, line))
    {
        vector<G4String> lineParts = split(line, ",");
        G4String cellLine = lineParts[columnIndices["cell"]];
        G4int element = elements.at(lineParts[columnIndices["particle"]]);
        
        fTablesEnergy[cellLine][element].push_back(
                                                   stod(lineParts[columnIndices["specific_energy"]]) * MeV
                                                   );
        fTablesAlpha[cellLine][element].push_back(
                                                  stod(lineParts[columnIndices["alpha"]])
                                                  );
        /* fTablesLet[cellLine][element].push_back(
         stod(lineParts[columnIndices["let"]])
         ); */
        fTablesBeta[cellLine][element].push_back(
                                                 stod(lineParts[columnIndices["beta"]])
                                                 );
        
        fTablesAlphaX[cellLine] = stod(lineParts[columnIndices["alpha_x"]]) / gray;
        fTablesBetaX[cellLine] = stod(lineParts[columnIndices["beta_x"]]) / (gray * gray);
        fTablesDoseCut[cellLine] = stod(lineParts[columnIndices["D_t"]]) * gray;
    }
    
    // Sort the tables by energy
    // (https://stackoverflow.com/a/12399290/2692780)
    for (auto aPair : fTablesEnergy)
    {
        for (auto ePair : aPair.second)
        {
            vector<G4double>& tableEnergy = fTablesEnergy[aPair.first][ePair.first];
            vector<G4double>& tableAlpha = fTablesAlpha[aPair.first][ePair.first];
            vector<G4double>& tableBeta = fTablesBeta[aPair.first][ePair.first];
            
            vector<size_t> idx(tableEnergy.size());
            iota(idx.begin(), idx.end(), 0);
            sort(idx.begin(), idx.end(),
                 [&tableEnergy](size_t i1, size_t i2) {return tableEnergy[i1] < tableEnergy[i2];});
            
            vector<vector<G4double>*> tables = {
                &tableEnergy, &tableAlpha, &tableBeta
            };
            for (vector<G4double>* table : tables)
            {
                vector<G4double> copy = *table;
                for (size_t i = 0; i < copy.size(); ++i)
                {
                    (*table)[i] = copy[idx[i]];
                }
                // G4cout << (*table)[0];
                // reorder(*table, idx);
                G4cout << (*table)[0] << G4endl;
            }
        }
    }
    
    if (fVerboseLevel > 0)
    {
        G4cout << "RBE: read LEM data for the following cell lines and elements [number of points]: " << G4endl;
        for (auto aPair : fTablesEnergy)
        {
            G4cout << "- " << aPair.first << ": ";
            for (auto ePair : aPair.second)
            {
                G4cout << ePair.first << "[" << ePair.second.size() << "] ";
            }
            G4cout << G4endl;
        }
    }
}

void HadrontherapyRBE::SetCellLine(G4String name)
{
    if (fTablesEnergy.size() == 0)
    {
        G4Exception("HadrontherapyRBE::SetCellLine", "NoCellLine", FatalException, "Cannot select cell line, probably LEM table not loaded yet?");
    }
    if (fTablesEnergy.find(name) == fTablesEnergy.end())
    {
        stringstream str;
        str << "Cell line " << name << " not found in the LEM table.";
        G4Exception("HadrontherapyRBE::SetCellLine", "", FatalException, str.str().c_str());
    }
    else
    {
        fAlphaX = fTablesAlphaX[name];
        fBetaX = fTablesBetaX[name];
        fDoseCut = fTablesDoseCut[name];
        
        fActiveTableEnergy = &fTablesEnergy[name];
        fActiveTableAlpha = &fTablesAlpha[name];
        fActiveTableBeta = &fTablesBeta[name];
        
        fMinZ = 0;
        fMaxZ = 0;
        fMinEnergies.clear();
        fMaxEnergies.clear();
        
        for (auto energyPair : *fActiveTableEnergy)
        {
            if (!fMinZ || (energyPair.first < fMinZ)) fMinZ = energyPair.first;
            if (energyPair.first > fMaxZ) fMaxZ = energyPair.first;
            
            fMinEnergies[energyPair.first] = energyPair.second[0];
            fMaxEnergies[energyPair.first] = energyPair.second[energyPair.second.size() - 1];
        }
    }
    
    fActiveCellLine = name;
    
    if (fVerboseLevel > 0)
    {
        G4cout << "RBE: cell line " << name << " selected." << G4endl;
    }
}

std::tuple<G4double, G4double> HadrontherapyRBE::GetHitAlphaAndBeta(G4double E, G4int Z)
{
    if (!fActiveTableEnergy)
    {
        G4Exception("HadrontherapyRBE::GetHitAlphaAndBeta", "NoCellLine", FatalException, "No cell line selected. Please, do it using the /rbe/cellLine command.");
    }
    
    // Check we are in the tables
    if ((Z < fMinZ) || (Z > fMaxZ))
    {
        if (fVerboseLevel > 1)
        {
            stringstream str;
            str << "Alpha & beta calculation supported only for ";
            str << fMinZ << " <= Z <= " << fMaxZ << ", but " << Z << " requested.";
            G4Exception("HadrontherapyRBE::GetHitAlphaAndBeta", "", JustWarning, str.str().c_str());
        }
        return make_tuple<G4double, G4double>( 0.0, 0.0 ); //out of table!
    }
    if ((E < fMinEnergies[Z]) || (E >= fMaxEnergies[Z]))
    {
        if (fVerboseLevel > 2)
        {
            G4cout << "RBE hit: Z=" << Z << ", E=" << E << " => out of LEM table";
            if (fVerboseLevel > 3)
            {
                G4cout << " (" << fMinEnergies[Z] << " to " << fMaxEnergies[Z] << " MeV)";
            }
            G4cout << G4endl;
        }
        return make_tuple<G4double, G4double>( 0.0, 0.0 ); //out of table!
    }
    
    std::vector<G4double>& vecEnergy = (*fActiveTableEnergy)[Z];
    std::vector<G4double>& vecAlpha = (*fActiveTableAlpha)[Z];
    std::vector<G4double>& vecBeta = (*fActiveTableBeta)[Z];
    
    // Find the row in energy tables
    const auto eLarger = upper_bound(begin(vecEnergy), end(vecEnergy), E);
    const G4int lower = distance(begin(vecEnergy), eLarger) - 1;
    const G4int upper = lower + 1;
    
    // Interpolation
    const G4double energyLower = vecEnergy[lower];
    const G4double energyUpper = vecEnergy[upper];
    const G4double energyFraction = (E - energyLower) / (energyUpper - energyLower);
    
    //linear interpolation along E
    const G4double alpha = ((1 - energyFraction) * vecAlpha[lower] + energyFraction * vecAlpha[upper]);
    const G4double beta = ((1 - energyFraction) * vecBeta[lower] + energyFraction * vecBeta[upper]);
    if (fVerboseLevel > 2)
    {
        G4cout << "RBE hit: Z=" << Z << ", E=" << E << " => alpha=" << alpha << ", beta=" << beta << G4endl;
    }
    
    return make_tuple(alpha, beta);
}

// Zaider & Rossi alpha & Beta mean
void HadrontherapyRBE::ComputeAlphaAndBeta()
{
    if (fVerboseLevel > 0)
    {
        G4cout << "RBE: Computing alpha and beta..." << G4endl;
    }
    fAlpha = fAlphaNumerator / (fDenominator * gray);
    fBeta = pow(fBetaNumerator / (fDenominator * gray), 2);
}

void HadrontherapyRBE::ComputeRBE()
{
    if (fVerboseLevel > 0)
    {
        G4cout << "RBE: Computing survival and RBE..." << G4endl;
    }
    G4double smax = fAlphaX + 2 * fBetaX * fDoseCut;
    
    // Prepare matrices that were not initialized yet
    fLnS.resize(fNumberOfVoxels);
    fDoseX.resize(fNumberOfVoxels);
    
    for (G4int i = 0; i < fNumberOfVoxels; i++)
    {
        if (std::isnan(fAlpha[i]) || std::isnan(fBeta[i]))
        {
            fLnS[i] = 0.0;
            fDoseX[i] = 0.0;
        }
        else if (fDose[i] <= fDoseCut)
        {
            fLnS[i] = -(fAlpha[i] * fDose[i]) - (fBeta[i] * (pow(fDose[i], 2))) ;
            fDoseX[i] = sqrt((-fLnS[i] / fBetaX) + pow((fAlphaX / (2 * fBetaX)), 2)) - (fAlphaX / (2 * fBetaX));
        }
        else
        {
            G4double ln_Scut = -(fAlpha[i] * fDoseCut) - (fBeta[i] * (pow((fDoseCut), 2)));
            fLnS[i] = ln_Scut - ((fDose[i] - fDoseCut) * smax);
            
            // TODO: CHECK THIS!!!
            fDoseX[i] = ( (-fLnS[i] + ln_Scut) / smax ) + fDoseCut;
        }
    }
    fRBE = fDoseX / fDose;
    fSurvival = exp(fLnS);
}

void HadrontherapyRBE::SetDenominator(const HadrontherapyRBE::array_type denom)
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Setting denominator..."  << G4endl;
    }
    fDenominator = denom;
}

void HadrontherapyRBE::AddDenominator(const HadrontherapyRBE::array_type denom)
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Adding denominator...";
    }
    if (fDenominator.size())
    {
        fDenominator += denom;
    }
    else
    {
        if (fVerboseLevel > 1)
        {
            G4cout << " (created empty array)";
        }
        fDenominator = denom;
    }
    G4cout << G4endl;
}

void HadrontherapyRBE::SetAlphaNumerator(const HadrontherapyRBE::array_type alpha)
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Setting alpha numerator..."  << G4endl;
    }
    fAlphaNumerator = alpha;
}

void HadrontherapyRBE::SetBetaNumerator(const HadrontherapyRBE::array_type beta)
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Setting beta numerator..." << G4endl;
    }
    fBetaNumerator = beta;
}

void HadrontherapyRBE::AddAlphaNumerator(const HadrontherapyRBE::array_type alpha)
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Adding alpha numerator...";
    }
    if (fAlphaNumerator.size())
    {
        fAlphaNumerator += alpha;
    }
    else
    {
        if (fVerboseLevel > 1)
        {
            G4cout << " (created empty array)";
        }
        fAlphaNumerator = alpha;
    }
    G4cout << G4endl;
}

void HadrontherapyRBE::AddBetaNumerator(const HadrontherapyRBE::array_type beta)
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Adding beta...";
    }
    if (fBetaNumerator.size())
    {
        fBetaNumerator += beta;
    }
    else
    {
        if (fVerboseLevel > 1)
        {
            G4cout << " (created empty array)";
        }
        fBetaNumerator = beta;
    }
    G4cout << G4endl;
}

void HadrontherapyRBE::SetEnergyDeposit(const std::valarray<G4double> eDep)
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Setting dose..." << G4endl;
    }
    fDose = eDep * (fDoseScale / fMassOfVoxel);
}

void HadrontherapyRBE::AddEnergyDeposit(const std::valarray<G4double> eDep)
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Adding dose... (" << eDep.size() << " points)" << G4endl;
    }
    if (fDose.size())
    {
        fDose += eDep * (fDoseScale / fMassOfVoxel);
    }
    else
    {
        if (fVerboseLevel > 1)
        {
            G4cout << " (created empty array)";
        }
        fDose = eDep * (fDoseScale / fMassOfVoxel);
    }
}

void HadrontherapyRBE::StoreAlphaAndBeta()
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Writing alpha and beta..." << G4endl;
    }
    ofstream ofs(fAlphaBetaPath);
    
    ComputeAlphaAndBeta();
    
    if (ofs.is_open())
    {
        ofs << "alpha" << std::setw(width) << "beta " << std::setw(width) << "depth(slice)" << G4endl;
        for (G4int i = 0; i < fNumberOfVoxelsAlongX * fNumberOfVoxelsAlongY * fNumberOfVoxelsAlongZ; i++)
            ofs << fAlpha[i]*gray << std::setw(15L) << fBeta[i]*pow(gray, 2) << std::setw(15L) << i << G4endl;
    }
    if (fVerboseLevel > 0)
    {
        G4cout << "RBE: Alpha and beta written to " << fAlphaBetaPath << G4endl;
    }
}

void HadrontherapyRBE::StoreRBE()
{
    ofstream ofs(fRBEPath);
    
    // TODO: only if not yet calculated. Or in RunAction???
    ComputeRBE();
    
    if (ofs.is_open())
    {
        ofs << "Dose(Gy)" << std::setw(width) << "ln(S) " << std::setw(width) << "Survival"  << std::setw(width) << "DoseB(Gy)" << std::setw(width) << "RBE" <<  std::setw(width) << "depth(slice)" << G4endl;
        
        for (G4int i = 0; i < fNumberOfVoxelsAlongX * fNumberOfVoxelsAlongY * fNumberOfVoxelsAlongZ; i++)
            
            ofs << (fDose[i] / gray) << std::setw(width) << fLnS[i] << std::setw(width) << fSurvival[i]
            << std::setw(width) << fDoseX[i] / gray << std::setw(width) << fRBE[i] << std::setw(width)  << i << G4endl;
    }
    if (fVerboseLevel > 0)
    {
        G4cout << "RBE: RBE written to " << fRBEPath << G4endl;
    }
}

void HadrontherapyRBE::Reset()
{
    if (fVerboseLevel > 1)
    {
        G4cout << "RBE: Reset(): ";
    }
    fAlphaNumerator = 0.0;
    fBetaNumerator = 0.0;
    fDenominator = 0.0;
    fDose = 0.0;
    if (fVerboseLevel > 1)
    {
        G4cout << fAlphaNumerator.size() << " points." << G4endl;
    }
}

void HadrontherapyRBE::CreateMessenger()
{
    fMessenger = new G4GenericMessenger(this, "/rbe/");
    fMessenger->SetGuidance("RBE calculation");
    
    fMessenger->DeclareMethod("calculation", &HadrontherapyRBE::SetCalculationEnabled)
    .SetGuidance("Whether to enable RBE calculation")
    .SetStates(G4State_PreInit, G4State_Idle)
    .SetToBeBroadcasted(false);
    
    fMessenger->DeclareMethod("verbose", &HadrontherapyRBE::SetVerboseLevel)
    .SetGuidance("Set verbosity level of RBE")
    .SetGuidance("0 = quiet")
    .SetGuidance("1 = important messages (~10 per run)")
    .SetGuidance("2 = debug")
    .SetToBeBroadcasted(false);
    
    fMessenger->DeclareMethod("loadLemTable", &HadrontherapyRBE::LoadLEMTable)
    .SetGuidance("Load a LEM table used in calculating alpha&beta")
    .SetStates(G4State_PreInit, G4State_Idle)
    .SetToBeBroadcasted(false);
    
    fMessenger->DeclareMethod("cellLine", &HadrontherapyRBE::SetCellLine)
    .SetGuidance("Set the cell line for alpha&beta calculation")
    .SetStates(G4State_PreInit, G4State_Idle)
    .SetToBeBroadcasted(false);
    
    fMessenger->DeclareMethod("doseScale", &HadrontherapyRBE::SetDoseScale)
    .SetGuidance("Set the scaling factor to calculate RBE with the real physical dose")
    .SetGuidance("If you don't set this, the RBE will be incorrect")
    .SetStates(G4State_PreInit, G4State_Idle)
    .SetToBeBroadcasted(false);
    
    fMessenger->DeclareMethod("accumulate", &HadrontherapyRBE::SetAccumulationEnabled)
    .SetGuidance("If false, reset the values at the beginning of each run.")
    .SetGuidance("If true, all runs are summed together")
    .SetStates(G4State_PreInit, G4State_Idle)
    .SetToBeBroadcasted(false);
    
    fMessenger->DeclareMethod("reset", &HadrontherapyRBE::Reset)
    .SetGuidance("Reset accumulated data (relevant only if accumulate mode is on)")
    .SetStates(G4State_PreInit, G4State_Idle)
    .SetToBeBroadcasted(false);
}


void HadrontherapyRBE::SetCalculationEnabled(G4bool enabled)
{
    fCalculationEnabled = enabled;
}

void HadrontherapyRBE::SetAccumulationEnabled(G4bool accumulate)
{
    fAccumulate = accumulate;
    // The accumulation should start now, not taking into account old data
    Reset();
}


void HadrontherapyRBE::SetDoseScale(G4double scale)
{
    fDoseScale = scale;
}




