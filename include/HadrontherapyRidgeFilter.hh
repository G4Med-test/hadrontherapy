//
//  HadrontherapyRidgeFilter.hpp
//  hadrontherapy
//
//  Created by Giada Petringa on 17/07/18.
//

#ifndef HadrontherapyRidgeFilter_hpp
#define HadrontherapyRidgeFilter_hpp

#include <stdio.h>
#include "globals.hh"
#include <fstream>
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"


class G4LogicalVolume;
class G4VPhysicalVolume;

class HadrontherapyRidgeFilter
{
public:

    
    void BuildRidgeFilter(G4LogicalVolume*,G4double);
private:
    
    
};

#endif /* HadrontherapyRidgeFilter_hpp */
