//
//  HadrontherapyRidgeFilter.cpp
//  hadrontherapy
//
//  Created by Giada Petringa on 17/07/18.
//

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Transform3D.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include <iostream>
#include "HadrontherapyRidgeFilter.hh"
#include "G4PVPlacement.hh"



void HadrontherapyRidgeFilter::BuildRidgeFilter(G4LogicalVolume* motherVolume,G4double pos)
{
    G4ThreeVector untitled_v0 = G4ThreeVector(-0.06*mm,0.05999994*mm,3.361754*mm);
    G4ThreeVector untitled_v1 = G4ThreeVector(0.0*mm,0.0*mm,3.361754*mm);
    G4ThreeVector untitled_v2 = G4ThreeVector(0.05999994*mm,0.05999994*mm,3.361754*mm);
    G4ThreeVector untitled_v3 = G4ThreeVector(-0.08999997*mm,0.09000003*mm,3.249966*mm);
    G4ThreeVector untitled_v4 = G4ThreeVector(0.09000003*mm,0.09000003*mm,3.249966*mm);
    G4ThreeVector untitled_v5 = G4ThreeVector(-0.12*mm,0.12*mm,3.181302*mm);
    G4ThreeVector untitled_v6 = G4ThreeVector(0.12*mm,0.12*mm,3.181302*mm);
    G4ThreeVector untitled_v7 = G4ThreeVector(-0.15*mm,0.15*mm,3.094842*mm);
    G4ThreeVector untitled_v8 = G4ThreeVector(0.15*mm,0.15*mm,3.094842*mm);
    G4ThreeVector untitled_v9 = G4ThreeVector(-0.19*mm,0.1900001*mm,2.952935*mm);
    G4ThreeVector untitled_v10 = G4ThreeVector(0.1900001*mm,0.1900001*mm,2.952935*mm);
    G4ThreeVector untitled_v11 = G4ThreeVector(-0.23*mm,0.23*mm,2.782771*mm);
    G4ThreeVector untitled_v12 = G4ThreeVector(0.23*mm,0.23*mm,2.782771*mm);
    G4ThreeVector untitled_v13 = G4ThreeVector(-0.28*mm,0.28*mm,2.533467*mm);
    G4ThreeVector untitled_v14 = G4ThreeVector(0.28*mm,0.28*mm,2.533467*mm);
    G4ThreeVector untitled_v15 = G4ThreeVector(-0.33*mm,0.33*mm,2.246969*mm);
    G4ThreeVector untitled_v16 = G4ThreeVector(0.33*mm,0.33*mm,2.246969*mm);
    G4ThreeVector untitled_v17 = G4ThreeVector(-0.39*mm,0.39*mm,1.860138*mm);
    G4ThreeVector untitled_v18 = G4ThreeVector(0.39*mm,0.39*mm,1.860138*mm);
    G4ThreeVector untitled_v19 = G4ThreeVector(-0.47*mm,0.47*mm,1.288696*mm);
    G4ThreeVector untitled_v20 = G4ThreeVector(0.47*mm,0.47*mm,1.288696*mm);
    G4ThreeVector untitled_v21 = G4ThreeVector(-0.63*mm,0.63*mm,0.09175515*mm);
    G4ThreeVector untitled_v22 = G4ThreeVector(0.63*mm,0.63*mm,0.09175515*mm);
    G4ThreeVector untitled_v23 = G4ThreeVector(-0.7*mm,0.7*mm,-0.3928729*mm);
    G4ThreeVector untitled_v24 = G4ThreeVector(0.7*mm,0.7*mm,-0.3928729*mm);
    G4ThreeVector untitled_v25 = G4ThreeVector(-0.75*mm,0.75*mm,-0.7059278*mm);
    G4ThreeVector untitled_v26 = G4ThreeVector(0.75*mm,0.75*mm,-0.7059278*mm);
    G4ThreeVector untitled_v27 = G4ThreeVector(-0.79*mm,0.79*mm,-0.9272109*mm);
    G4ThreeVector untitled_v28 = G4ThreeVector(0.79*mm,0.79*mm,-0.9272109*mm);
    G4ThreeVector untitled_v29 = G4ThreeVector(-0.82*mm,0.8200001*mm,-1.068232*mm);
    G4ThreeVector untitled_v30 = G4ThreeVector(0.8200001*mm,0.8200001*mm,-1.068232*mm);
    G4ThreeVector untitled_v31 = G4ThreeVector(-0.84*mm,0.84*mm,-1.143632*mm);
    G4ThreeVector untitled_v32 = G4ThreeVector(0.84*mm,0.84*mm,-1.143632*mm);
    G4ThreeVector untitled_v33 = G4ThreeVector(-0.85*mm,0.85*mm,-1.36*mm);
    G4ThreeVector untitled_v34 = G4ThreeVector(0.85*mm,0.85*mm,-1.36*mm);
    G4ThreeVector untitled_v35 = G4ThreeVector(-1.0*mm,1.0*mm,-1.36*mm);
    G4ThreeVector untitled_v36 = G4ThreeVector(1.0*mm,1.0*mm,-1.36*mm);
    G4ThreeVector untitled_v37 = G4ThreeVector(-1.0*mm,1.0*mm,-2.36*mm);
    G4ThreeVector untitled_v38 = G4ThreeVector(1.0*mm,1.0*mm,-2.36*mm);
    G4ThreeVector untitled_v39 = G4ThreeVector(-0.06*mm,-0.06*mm,3.361754*mm);
    G4ThreeVector untitled_v40 = G4ThreeVector(0.05999994*mm,-0.06*mm,3.361754*mm);
    G4ThreeVector untitled_v41 = G4ThreeVector(-0.08999997*mm,-0.08999997*mm,3.249966*mm);
    G4ThreeVector untitled_v42 = G4ThreeVector(0.09000003*mm,-0.08999997*mm,3.249966*mm);
    G4ThreeVector untitled_v43 = G4ThreeVector(-0.12*mm,-0.12*mm,3.181302*mm);
    G4ThreeVector untitled_v44 = G4ThreeVector(0.12*mm,-0.12*mm,3.181302*mm);
    G4ThreeVector untitled_v45 = G4ThreeVector(-0.15*mm,-0.15*mm,3.094842*mm);
    G4ThreeVector untitled_v46 = G4ThreeVector(0.15*mm,-0.15*mm,3.094842*mm);
    G4ThreeVector untitled_v47 = G4ThreeVector(-0.19*mm,-0.19*mm,2.952935*mm);
    G4ThreeVector untitled_v48 = G4ThreeVector(0.1900001*mm,-0.19*mm,2.952935*mm);
    G4ThreeVector untitled_v49 = G4ThreeVector(-0.23*mm,-0.23*mm,2.782771*mm);
    G4ThreeVector untitled_v50 = G4ThreeVector(0.23*mm,-0.23*mm,2.782771*mm);
    G4ThreeVector untitled_v51 = G4ThreeVector(-0.28*mm,-0.28*mm,2.533467*mm);
    G4ThreeVector untitled_v52 = G4ThreeVector(0.28*mm,-0.28*mm,2.533467*mm);
    G4ThreeVector untitled_v53 = G4ThreeVector(-0.33*mm,-0.33*mm,2.246969*mm);
    G4ThreeVector untitled_v54 = G4ThreeVector(0.33*mm,-0.33*mm,2.246969*mm);
    G4ThreeVector untitled_v55 = G4ThreeVector(-0.39*mm,-0.39*mm,1.860138*mm);
    G4ThreeVector untitled_v56 = G4ThreeVector(0.39*mm,-0.39*mm,1.860138*mm);
    G4ThreeVector untitled_v57 = G4ThreeVector(-0.47*mm,-0.47*mm,1.288696*mm);
    G4ThreeVector untitled_v58 = G4ThreeVector(0.47*mm,-0.47*mm,1.288696*mm);
    G4ThreeVector untitled_v59 = G4ThreeVector(-0.63*mm,-0.63*mm,0.09175515*mm);
    G4ThreeVector untitled_v60 = G4ThreeVector(0.63*mm,-0.63*mm,0.09175515*mm);
    G4ThreeVector untitled_v61 = G4ThreeVector(-0.7*mm,-0.7*mm,-0.3928729*mm);
    G4ThreeVector untitled_v62 = G4ThreeVector(0.7*mm,-0.7*mm,-0.3928729*mm);
    G4ThreeVector untitled_v63 = G4ThreeVector(-0.75*mm,-0.75*mm,-0.7059278*mm);
    G4ThreeVector untitled_v64 = G4ThreeVector(0.75*mm,-0.75*mm,-0.7059278*mm);
    G4ThreeVector untitled_v65 = G4ThreeVector(-0.79*mm,-0.79*mm,-0.9272109*mm);
    G4ThreeVector untitled_v66 = G4ThreeVector(0.79*mm,-0.79*mm,-0.9272109*mm);
    G4ThreeVector untitled_v67 = G4ThreeVector(-0.82*mm,-0.82*mm,-1.068232*mm);
    G4ThreeVector untitled_v68 = G4ThreeVector(0.8200001*mm,-0.82*mm,-1.068232*mm);
    G4ThreeVector untitled_v69 = G4ThreeVector(-0.84*mm,-0.84*mm,-1.143632*mm);
    G4ThreeVector untitled_v70 = G4ThreeVector(0.84*mm,-0.84*mm,-1.143632*mm);
    G4ThreeVector untitled_v71 = G4ThreeVector(-0.85*mm,-0.85*mm,-1.36*mm);
    G4ThreeVector untitled_v72 = G4ThreeVector(0.85*mm,-0.85*mm,-1.36*mm);
    G4ThreeVector untitled_v73 = G4ThreeVector(-1.0*mm,-1.0*mm,-1.36*mm);
    G4ThreeVector untitled_v74 = G4ThreeVector(1.0*mm,-1.0*mm,-1.36*mm);
    G4ThreeVector untitled_v75 = G4ThreeVector(-1.0*mm,-1.0*mm,-2.36*mm);
    G4ThreeVector untitled_v76 = G4ThreeVector(1.0*mm,-1.0*mm,-2.36*mm);
    
    G4VSolid* solid;    G4TessellatedSolid& untitled = *new G4TessellatedSolid("untitled-SOL");
    G4VFacet *facet0 = new G4TriangularFacet(untitled_v0,untitled_v1,untitled_v2,ABSOLUTE);
    G4VFacet *facet1 = new G4TriangularFacet(untitled_v3,untitled_v0,untitled_v4,ABSOLUTE);
    G4VFacet *facet2 = new G4TriangularFacet(untitled_v2,untitled_v4,untitled_v0,ABSOLUTE);
    G4VFacet *facet3 = new G4TriangularFacet(untitled_v5,untitled_v3,untitled_v6,ABSOLUTE);
    G4VFacet *facet4 = new G4TriangularFacet(untitled_v4,untitled_v6,untitled_v3,ABSOLUTE);
    G4VFacet *facet5 = new G4TriangularFacet(untitled_v7,untitled_v5,untitled_v8,ABSOLUTE);
    G4VFacet *facet6 = new G4TriangularFacet(untitled_v6,untitled_v8,untitled_v5,ABSOLUTE);
    G4VFacet *facet7 = new G4TriangularFacet(untitled_v9,untitled_v7,untitled_v10,ABSOLUTE);
    G4VFacet *facet8 = new G4TriangularFacet(untitled_v8,untitled_v10,untitled_v7,ABSOLUTE);
    G4VFacet *facet9 = new G4TriangularFacet(untitled_v11,untitled_v9,untitled_v12,ABSOLUTE);
    G4VFacet *facet10 = new G4TriangularFacet(untitled_v10,untitled_v12,untitled_v9,ABSOLUTE);
    G4VFacet *facet11 = new G4TriangularFacet(untitled_v13,untitled_v11,untitled_v14,ABSOLUTE);
    G4VFacet *facet12 = new G4TriangularFacet(untitled_v12,untitled_v14,untitled_v11,ABSOLUTE);
    G4VFacet *facet13 = new G4TriangularFacet(untitled_v15,untitled_v13,untitled_v16,ABSOLUTE);
    G4VFacet *facet14 = new G4TriangularFacet(untitled_v14,untitled_v16,untitled_v13,ABSOLUTE);
    G4VFacet *facet15 = new G4TriangularFacet(untitled_v17,untitled_v15,untitled_v18,ABSOLUTE);
    G4VFacet *facet16 = new G4TriangularFacet(untitled_v16,untitled_v18,untitled_v15,ABSOLUTE);
    G4VFacet *facet17 = new G4TriangularFacet(untitled_v19,untitled_v17,untitled_v20,ABSOLUTE);
    G4VFacet *facet18 = new G4TriangularFacet(untitled_v18,untitled_v20,untitled_v17,ABSOLUTE);
    G4VFacet *facet19 = new G4TriangularFacet(untitled_v21,untitled_v19,untitled_v22,ABSOLUTE);
    G4VFacet *facet20 = new G4TriangularFacet(untitled_v20,untitled_v22,untitled_v19,ABSOLUTE);
    G4VFacet *facet21 = new G4TriangularFacet(untitled_v23,untitled_v21,untitled_v24,ABSOLUTE);
    G4VFacet *facet22 = new G4TriangularFacet(untitled_v22,untitled_v24,untitled_v21,ABSOLUTE);
    G4VFacet *facet23 = new G4TriangularFacet(untitled_v25,untitled_v23,untitled_v26,ABSOLUTE);
    G4VFacet *facet24 = new G4TriangularFacet(untitled_v24,untitled_v26,untitled_v23,ABSOLUTE);
    G4VFacet *facet25 = new G4TriangularFacet(untitled_v27,untitled_v25,untitled_v28,ABSOLUTE);
    G4VFacet *facet26 = new G4TriangularFacet(untitled_v26,untitled_v28,untitled_v25,ABSOLUTE);
    G4VFacet *facet27 = new G4TriangularFacet(untitled_v29,untitled_v27,untitled_v30,ABSOLUTE);
    G4VFacet *facet28 = new G4TriangularFacet(untitled_v28,untitled_v30,untitled_v27,ABSOLUTE);
    G4VFacet *facet29 = new G4TriangularFacet(untitled_v31,untitled_v29,untitled_v32,ABSOLUTE);
    G4VFacet *facet30 = new G4TriangularFacet(untitled_v30,untitled_v32,untitled_v29,ABSOLUTE);
    G4VFacet *facet31 = new G4TriangularFacet(untitled_v33,untitled_v31,untitled_v34,ABSOLUTE);
    G4VFacet *facet32 = new G4TriangularFacet(untitled_v32,untitled_v34,untitled_v31,ABSOLUTE);
    G4VFacet *facet33 = new G4TriangularFacet(untitled_v35,untitled_v33,untitled_v36,ABSOLUTE);
    G4VFacet *facet34 = new G4TriangularFacet(untitled_v34,untitled_v36,untitled_v33,ABSOLUTE);
    G4VFacet *facet35 = new G4TriangularFacet(untitled_v35,untitled_v36,untitled_v37,ABSOLUTE);
    G4VFacet *facet36 = new G4TriangularFacet(untitled_v38,untitled_v37,untitled_v36,ABSOLUTE);
    G4VFacet *facet37 = new G4TriangularFacet(untitled_v39,untitled_v40,untitled_v1,ABSOLUTE);
    G4VFacet *facet38 = new G4TriangularFacet(untitled_v41,untitled_v42,untitled_v39,ABSOLUTE);
    G4VFacet *facet39 = new G4TriangularFacet(untitled_v40,untitled_v39,untitled_v42,ABSOLUTE);
    G4VFacet *facet40 = new G4TriangularFacet(untitled_v43,untitled_v44,untitled_v41,ABSOLUTE);
    G4VFacet *facet41 = new G4TriangularFacet(untitled_v42,untitled_v41,untitled_v44,ABSOLUTE);
    G4VFacet *facet42 = new G4TriangularFacet(untitled_v45,untitled_v46,untitled_v43,ABSOLUTE);
    G4VFacet *facet43 = new G4TriangularFacet(untitled_v44,untitled_v43,untitled_v46,ABSOLUTE);
    G4VFacet *facet44 = new G4TriangularFacet(untitled_v47,untitled_v48,untitled_v45,ABSOLUTE);
    G4VFacet *facet45 = new G4TriangularFacet(untitled_v46,untitled_v45,untitled_v48,ABSOLUTE);
    G4VFacet *facet46 = new G4TriangularFacet(untitled_v49,untitled_v50,untitled_v47,ABSOLUTE);
    G4VFacet *facet47 = new G4TriangularFacet(untitled_v48,untitled_v47,untitled_v50,ABSOLUTE);
    G4VFacet *facet48 = new G4TriangularFacet(untitled_v51,untitled_v52,untitled_v49,ABSOLUTE);
    G4VFacet *facet49 = new G4TriangularFacet(untitled_v50,untitled_v49,untitled_v52,ABSOLUTE);
    G4VFacet *facet50 = new G4TriangularFacet(untitled_v53,untitled_v54,untitled_v51,ABSOLUTE);
    G4VFacet *facet51 = new G4TriangularFacet(untitled_v52,untitled_v51,untitled_v54,ABSOLUTE);
    G4VFacet *facet52 = new G4TriangularFacet(untitled_v55,untitled_v56,untitled_v53,ABSOLUTE);
    G4VFacet *facet53 = new G4TriangularFacet(untitled_v54,untitled_v53,untitled_v56,ABSOLUTE);
    G4VFacet *facet54 = new G4TriangularFacet(untitled_v57,untitled_v58,untitled_v55,ABSOLUTE);
    G4VFacet *facet55 = new G4TriangularFacet(untitled_v56,untitled_v55,untitled_v58,ABSOLUTE);
    G4VFacet *facet56 = new G4TriangularFacet(untitled_v59,untitled_v60,untitled_v57,ABSOLUTE);
    G4VFacet *facet57 = new G4TriangularFacet(untitled_v58,untitled_v57,untitled_v60,ABSOLUTE);
    G4VFacet *facet58 = new G4TriangularFacet(untitled_v61,untitled_v62,untitled_v59,ABSOLUTE);
    G4VFacet *facet59 = new G4TriangularFacet(untitled_v60,untitled_v59,untitled_v62,ABSOLUTE);
    G4VFacet *facet60 = new G4TriangularFacet(untitled_v63,untitled_v64,untitled_v61,ABSOLUTE);
    G4VFacet *facet61 = new G4TriangularFacet(untitled_v62,untitled_v61,untitled_v64,ABSOLUTE);
    G4VFacet *facet62 = new G4TriangularFacet(untitled_v65,untitled_v66,untitled_v63,ABSOLUTE);
    G4VFacet *facet63 = new G4TriangularFacet(untitled_v64,untitled_v63,untitled_v66,ABSOLUTE);
    G4VFacet *facet64 = new G4TriangularFacet(untitled_v67,untitled_v68,untitled_v65,ABSOLUTE);
    G4VFacet *facet65 = new G4TriangularFacet(untitled_v66,untitled_v65,untitled_v68,ABSOLUTE);
    G4VFacet *facet66 = new G4TriangularFacet(untitled_v69,untitled_v70,untitled_v67,ABSOLUTE);
    G4VFacet *facet67 = new G4TriangularFacet(untitled_v68,untitled_v67,untitled_v70,ABSOLUTE);
    G4VFacet *facet68 = new G4TriangularFacet(untitled_v71,untitled_v72,untitled_v69,ABSOLUTE);
    G4VFacet *facet69 = new G4TriangularFacet(untitled_v70,untitled_v69,untitled_v72,ABSOLUTE);
    G4VFacet *facet70 = new G4TriangularFacet(untitled_v73,untitled_v74,untitled_v71,ABSOLUTE);
    G4VFacet *facet71 = new G4TriangularFacet(untitled_v72,untitled_v71,untitled_v74,ABSOLUTE);
    G4VFacet *facet72 = new G4TriangularFacet(untitled_v73,untitled_v75,untitled_v74,ABSOLUTE);
    G4VFacet *facet73 = new G4TriangularFacet(untitled_v76,untitled_v74,untitled_v75,ABSOLUTE);
    G4VFacet *facet74 = new G4TriangularFacet(untitled_v40,untitled_v2,untitled_v1,ABSOLUTE);
    G4VFacet *facet75 = new G4TriangularFacet(untitled_v42,untitled_v4,untitled_v40,ABSOLUTE);
    G4VFacet *facet76 = new G4TriangularFacet(untitled_v2,untitled_v40,untitled_v4,ABSOLUTE);
    G4VFacet *facet77 = new G4TriangularFacet(untitled_v44,untitled_v6,untitled_v42,ABSOLUTE);
    G4VFacet *facet78 = new G4TriangularFacet(untitled_v4,untitled_v42,untitled_v6,ABSOLUTE);
    G4VFacet *facet79 = new G4TriangularFacet(untitled_v46,untitled_v8,untitled_v44,ABSOLUTE);
    G4VFacet *facet80 = new G4TriangularFacet(untitled_v6,untitled_v44,untitled_v8,ABSOLUTE);
    G4VFacet *facet81 = new G4TriangularFacet(untitled_v48,untitled_v10,untitled_v46,ABSOLUTE);
    G4VFacet *facet82 = new G4TriangularFacet(untitled_v8,untitled_v46,untitled_v10,ABSOLUTE);
    G4VFacet *facet83 = new G4TriangularFacet(untitled_v50,untitled_v12,untitled_v48,ABSOLUTE);
    G4VFacet *facet84 = new G4TriangularFacet(untitled_v10,untitled_v48,untitled_v12,ABSOLUTE);
    G4VFacet *facet85 = new G4TriangularFacet(untitled_v52,untitled_v14,untitled_v50,ABSOLUTE);
    G4VFacet *facet86 = new G4TriangularFacet(untitled_v12,untitled_v50,untitled_v14,ABSOLUTE);
    G4VFacet *facet87 = new G4TriangularFacet(untitled_v54,untitled_v16,untitled_v52,ABSOLUTE);
    G4VFacet *facet88 = new G4TriangularFacet(untitled_v14,untitled_v52,untitled_v16,ABSOLUTE);
    G4VFacet *facet89 = new G4TriangularFacet(untitled_v56,untitled_v18,untitled_v54,ABSOLUTE);
    G4VFacet *facet90 = new G4TriangularFacet(untitled_v16,untitled_v54,untitled_v18,ABSOLUTE);
    G4VFacet *facet91 = new G4TriangularFacet(untitled_v58,untitled_v20,untitled_v56,ABSOLUTE);
    G4VFacet *facet92 = new G4TriangularFacet(untitled_v18,untitled_v56,untitled_v20,ABSOLUTE);
    G4VFacet *facet93 = new G4TriangularFacet(untitled_v60,untitled_v22,untitled_v58,ABSOLUTE);
    G4VFacet *facet94 = new G4TriangularFacet(untitled_v20,untitled_v58,untitled_v22,ABSOLUTE);
    G4VFacet *facet95 = new G4TriangularFacet(untitled_v62,untitled_v24,untitled_v60,ABSOLUTE);
    G4VFacet *facet96 = new G4TriangularFacet(untitled_v22,untitled_v60,untitled_v24,ABSOLUTE);
    G4VFacet *facet97 = new G4TriangularFacet(untitled_v64,untitled_v26,untitled_v62,ABSOLUTE);
    G4VFacet *facet98 = new G4TriangularFacet(untitled_v24,untitled_v62,untitled_v26,ABSOLUTE);
    G4VFacet *facet99 = new G4TriangularFacet(untitled_v66,untitled_v28,untitled_v64,ABSOLUTE);
    G4VFacet *facet100 = new G4TriangularFacet(untitled_v26,untitled_v64,untitled_v28,ABSOLUTE);
    G4VFacet *facet101 = new G4TriangularFacet(untitled_v68,untitled_v30,untitled_v66,ABSOLUTE);
    G4VFacet *facet102 = new G4TriangularFacet(untitled_v28,untitled_v66,untitled_v30,ABSOLUTE);
    G4VFacet *facet103 = new G4TriangularFacet(untitled_v70,untitled_v32,untitled_v68,ABSOLUTE);
    G4VFacet *facet104 = new G4TriangularFacet(untitled_v30,untitled_v68,untitled_v32,ABSOLUTE);
    G4VFacet *facet105 = new G4TriangularFacet(untitled_v72,untitled_v34,untitled_v70,ABSOLUTE);
    G4VFacet *facet106 = new G4TriangularFacet(untitled_v32,untitled_v70,untitled_v34,ABSOLUTE);
    G4VFacet *facet107 = new G4TriangularFacet(untitled_v74,untitled_v36,untitled_v72,ABSOLUTE);
    G4VFacet *facet108 = new G4TriangularFacet(untitled_v34,untitled_v72,untitled_v36,ABSOLUTE);
    G4VFacet *facet109 = new G4TriangularFacet(untitled_v74,untitled_v76,untitled_v36,ABSOLUTE);
    G4VFacet *facet110 = new G4TriangularFacet(untitled_v38,untitled_v36,untitled_v76,ABSOLUTE);
    G4VFacet *facet111 = new G4TriangularFacet(untitled_v39,untitled_v1,untitled_v0,ABSOLUTE);
    G4VFacet *facet112 = new G4TriangularFacet(untitled_v41,untitled_v39,untitled_v3,ABSOLUTE);
    G4VFacet *facet113 = new G4TriangularFacet(untitled_v0,untitled_v3,untitled_v39,ABSOLUTE);
    G4VFacet *facet114 = new G4TriangularFacet(untitled_v43,untitled_v41,untitled_v5,ABSOLUTE);
    G4VFacet *facet115 = new G4TriangularFacet(untitled_v3,untitled_v5,untitled_v41,ABSOLUTE);
    G4VFacet *facet116 = new G4TriangularFacet(untitled_v45,untitled_v43,untitled_v7,ABSOLUTE);
    G4VFacet *facet117 = new G4TriangularFacet(untitled_v5,untitled_v7,untitled_v43,ABSOLUTE);
    G4VFacet *facet118 = new G4TriangularFacet(untitled_v47,untitled_v45,untitled_v9,ABSOLUTE);
    G4VFacet *facet119 = new G4TriangularFacet(untitled_v7,untitled_v9,untitled_v45,ABSOLUTE);
    G4VFacet *facet120 = new G4TriangularFacet(untitled_v49,untitled_v47,untitled_v11,ABSOLUTE);
    G4VFacet *facet121 = new G4TriangularFacet(untitled_v9,untitled_v11,untitled_v47,ABSOLUTE);
    G4VFacet *facet122 = new G4TriangularFacet(untitled_v51,untitled_v49,untitled_v13,ABSOLUTE);
    G4VFacet *facet123 = new G4TriangularFacet(untitled_v11,untitled_v13,untitled_v49,ABSOLUTE);
    G4VFacet *facet124 = new G4TriangularFacet(untitled_v53,untitled_v51,untitled_v15,ABSOLUTE);
    G4VFacet *facet125 = new G4TriangularFacet(untitled_v13,untitled_v15,untitled_v51,ABSOLUTE);
    G4VFacet *facet126 = new G4TriangularFacet(untitled_v55,untitled_v53,untitled_v17,ABSOLUTE);
    G4VFacet *facet127 = new G4TriangularFacet(untitled_v15,untitled_v17,untitled_v53,ABSOLUTE);
    G4VFacet *facet128 = new G4TriangularFacet(untitled_v57,untitled_v55,untitled_v19,ABSOLUTE);
    G4VFacet *facet129 = new G4TriangularFacet(untitled_v17,untitled_v19,untitled_v55,ABSOLUTE);
    G4VFacet *facet130 = new G4TriangularFacet(untitled_v59,untitled_v57,untitled_v21,ABSOLUTE);
    G4VFacet *facet131 = new G4TriangularFacet(untitled_v19,untitled_v21,untitled_v57,ABSOLUTE);
    G4VFacet *facet132 = new G4TriangularFacet(untitled_v61,untitled_v59,untitled_v23,ABSOLUTE);
    G4VFacet *facet133 = new G4TriangularFacet(untitled_v21,untitled_v23,untitled_v59,ABSOLUTE);
    G4VFacet *facet134 = new G4TriangularFacet(untitled_v63,untitled_v61,untitled_v25,ABSOLUTE);
    G4VFacet *facet135 = new G4TriangularFacet(untitled_v23,untitled_v25,untitled_v61,ABSOLUTE);
    G4VFacet *facet136 = new G4TriangularFacet(untitled_v65,untitled_v63,untitled_v27,ABSOLUTE);
    G4VFacet *facet137 = new G4TriangularFacet(untitled_v25,untitled_v27,untitled_v63,ABSOLUTE);
    G4VFacet *facet138 = new G4TriangularFacet(untitled_v67,untitled_v65,untitled_v29,ABSOLUTE);
    G4VFacet *facet139 = new G4TriangularFacet(untitled_v27,untitled_v29,untitled_v65,ABSOLUTE);
    G4VFacet *facet140 = new G4TriangularFacet(untitled_v69,untitled_v67,untitled_v31,ABSOLUTE);
    G4VFacet *facet141 = new G4TriangularFacet(untitled_v29,untitled_v31,untitled_v67,ABSOLUTE);
    G4VFacet *facet142 = new G4TriangularFacet(untitled_v71,untitled_v69,untitled_v33,ABSOLUTE);
    G4VFacet *facet143 = new G4TriangularFacet(untitled_v31,untitled_v33,untitled_v69,ABSOLUTE);
    G4VFacet *facet144 = new G4TriangularFacet(untitled_v73,untitled_v71,untitled_v35,ABSOLUTE);
    G4VFacet *facet145 = new G4TriangularFacet(untitled_v33,untitled_v35,untitled_v71,ABSOLUTE);
    G4VFacet *facet146 = new G4TriangularFacet(untitled_v73,untitled_v35,untitled_v75,ABSOLUTE);
    G4VFacet *facet147 = new G4TriangularFacet(untitled_v37,untitled_v75,untitled_v35,ABSOLUTE);
    G4VFacet *facet148 = new G4TriangularFacet(untitled_v75,untitled_v38,untitled_v76,ABSOLUTE);
    G4VFacet *facet149 = new G4TriangularFacet(untitled_v75,untitled_v37,untitled_v38,ABSOLUTE);
    
    untitled.AddFacet(facet0);
    untitled.AddFacet(facet1);
    untitled.AddFacet(facet2);
    untitled.AddFacet(facet3);
    untitled.AddFacet(facet4);
    untitled.AddFacet(facet5);
    untitled.AddFacet(facet6);
    untitled.AddFacet(facet7);
    untitled.AddFacet(facet8);
    untitled.AddFacet(facet9);
    untitled.AddFacet(facet10);
    untitled.AddFacet(facet11);
    untitled.AddFacet(facet12);
    untitled.AddFacet(facet13);
    untitled.AddFacet(facet14);
    untitled.AddFacet(facet15);
    untitled.AddFacet(facet16);
    untitled.AddFacet(facet17);
    untitled.AddFacet(facet18);
    untitled.AddFacet(facet19);
    untitled.AddFacet(facet20);
    untitled.AddFacet(facet21);
    untitled.AddFacet(facet22);
    untitled.AddFacet(facet23);
    untitled.AddFacet(facet24);
    untitled.AddFacet(facet25);
    untitled.AddFacet(facet26);
    untitled.AddFacet(facet27);
    untitled.AddFacet(facet28);
    untitled.AddFacet(facet29);
    untitled.AddFacet(facet30);
    untitled.AddFacet(facet31);
    untitled.AddFacet(facet32);
    untitled.AddFacet(facet33);
    untitled.AddFacet(facet34);
    untitled.AddFacet(facet35);
    untitled.AddFacet(facet36);
    untitled.AddFacet(facet37);
    untitled.AddFacet(facet38);
    untitled.AddFacet(facet39);
    untitled.AddFacet(facet40);
    untitled.AddFacet(facet41);
    untitled.AddFacet(facet42);
    untitled.AddFacet(facet43);
    untitled.AddFacet(facet44);
    untitled.AddFacet(facet45);
    untitled.AddFacet(facet46);
    untitled.AddFacet(facet47);
    untitled.AddFacet(facet48);
    untitled.AddFacet(facet49);
    untitled.AddFacet(facet50);
    untitled.AddFacet(facet51);
    untitled.AddFacet(facet52);
    untitled.AddFacet(facet53);
    untitled.AddFacet(facet54);
    untitled.AddFacet(facet55);
    untitled.AddFacet(facet56);
    untitled.AddFacet(facet57);
    untitled.AddFacet(facet58);
    untitled.AddFacet(facet59);
    untitled.AddFacet(facet60);
    untitled.AddFacet(facet61);
    untitled.AddFacet(facet62);
    untitled.AddFacet(facet63);
    untitled.AddFacet(facet64);
    untitled.AddFacet(facet65);
    untitled.AddFacet(facet66);
    untitled.AddFacet(facet67);
    untitled.AddFacet(facet68);
    untitled.AddFacet(facet69);
    untitled.AddFacet(facet70);
    untitled.AddFacet(facet71);
    untitled.AddFacet(facet72);
    untitled.AddFacet(facet73);
    untitled.AddFacet(facet74);
    untitled.AddFacet(facet75);
    untitled.AddFacet(facet76);
    untitled.AddFacet(facet77);
    untitled.AddFacet(facet78);
    untitled.AddFacet(facet79);
    untitled.AddFacet(facet80);
    untitled.AddFacet(facet81);
    untitled.AddFacet(facet82);
    untitled.AddFacet(facet83);
    untitled.AddFacet(facet84);
    untitled.AddFacet(facet85);
    untitled.AddFacet(facet86);
    untitled.AddFacet(facet87);
    untitled.AddFacet(facet88);
    untitled.AddFacet(facet89);
    untitled.AddFacet(facet90);
    untitled.AddFacet(facet91);
    untitled.AddFacet(facet92);
    untitled.AddFacet(facet93);
    untitled.AddFacet(facet94);
    untitled.AddFacet(facet95);
    untitled.AddFacet(facet96);
    untitled.AddFacet(facet97);
    untitled.AddFacet(facet98);
    untitled.AddFacet(facet99);
    untitled.AddFacet(facet100);
    untitled.AddFacet(facet101);
    untitled.AddFacet(facet102);
    untitled.AddFacet(facet103);
    untitled.AddFacet(facet104);
    untitled.AddFacet(facet105);
    untitled.AddFacet(facet106);
    untitled.AddFacet(facet107);
    untitled.AddFacet(facet108);
    untitled.AddFacet(facet109);
    untitled.AddFacet(facet110);
    untitled.AddFacet(facet111);
    untitled.AddFacet(facet112);
    untitled.AddFacet(facet113);
    untitled.AddFacet(facet114);
    untitled.AddFacet(facet115);
    untitled.AddFacet(facet116);
    untitled.AddFacet(facet117);
    untitled.AddFacet(facet118);
    untitled.AddFacet(facet119);
    untitled.AddFacet(facet120);
    untitled.AddFacet(facet121);
    untitled.AddFacet(facet122);
    untitled.AddFacet(facet123);
    untitled.AddFacet(facet124);
    untitled.AddFacet(facet125);
    untitled.AddFacet(facet126);
    untitled.AddFacet(facet127);
    untitled.AddFacet(facet128);
    untitled.AddFacet(facet129);
    untitled.AddFacet(facet130);
    untitled.AddFacet(facet131);
    untitled.AddFacet(facet132);
    untitled.AddFacet(facet133);
    untitled.AddFacet(facet134);
    untitled.AddFacet(facet135);
    untitled.AddFacet(facet136);
    untitled.AddFacet(facet137);
    untitled.AddFacet(facet138);
    untitled.AddFacet(facet139);
    untitled.AddFacet(facet140);
    untitled.AddFacet(facet141);
    untitled.AddFacet(facet142);
    untitled.AddFacet(facet143);
    untitled.AddFacet(facet144);
    untitled.AddFacet(facet145);
    untitled.AddFacet(facet146);
    untitled.AddFacet(facet147);
    untitled.AddFacet(facet148);
    untitled.AddFacet(facet149);
    
    untitled.SetSolidClosed(true);    solid=&untitled;
    
    G4Element* hydrogenNist = G4NistManager::Instance()->FindOrBuildElement("H");
    G4Element* oxygenNist = G4NistManager::Instance()->FindOrBuildElement("O");
    G4Element* carbonNist = G4NistManager::Instance()->FindOrBuildElement("C");
    
    G4Material* plastic = new G4Material("Plastic", 1.40*g/cm3, 3);
    plastic -> AddElement(carbonNist, 21);
    plastic -> AddElement(oxygenNist, 4);
    plastic -> AddElement(hydrogenNist, 24);
    
    G4LogicalVolume* LogicRidgeFilter;
    LogicRidgeFilter= new G4LogicalVolume(solid,plastic,"ridgeFilterVol");
    

    G4int numberOfLayers = 30;
   
    G4double minZ = 29*mm;
    G4double minY = 29*mm;

    
    
    std::vector<G4ThreeVector> singleTrapPositions;
    for (int i = 0; i < numberOfLayers; i++)
    {
        for (int j = 0; j < numberOfLayers; j++)
        {
            singleTrapPositions.push_back({pos-2.36*mm,minY-i*2,minZ- j*2});
            
        }
    }
    G4double phi = -90. *deg;
    G4RotationMatrix rm;
    rm.rotateY(phi);
    
    G4int peaks = numberOfLayers*numberOfLayers;
    for (int i = 0; i < peaks; i++)
    {
        
        std::ostringstream tName;
        tName << "singleTrap" << i;
        new G4PVPlacement(G4Transform3D(rm,singleTrapPositions[i]),LogicRidgeFilter,
                         "tName.str()",
                          motherVolume,
                          0,
                          i);
    }
    


}
