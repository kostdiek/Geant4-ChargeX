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
/// \file radioactivedecay/rdecay01/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//
// $Id: DetectorConstruction.cc 68030 2013-03-13 13:51:27Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "DetectorConstruction.hh"//

#include "G4Material.hh"//
#include "G4NistManager.hh"//

#include "G4Tubs.hh"
#include "G4Box.hh"//
#include "G4Cons.hh"
#include "G4EllipticalTube.hh"
#include "G4LogicalVolume.hh"//
#include "G4PVPlacement.hh"//

#include "G4AutoDelete.hh"
#include "G4String.hh"
#include "G4RotationMatrix.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4SDManager.hh"//
#include "G4SDNeutralFilter.hh"
#include "G4PSPassageTrackLength.hh"
#include "G4MultiFunctionalDetector.hh"//
#include "G4VPrimitiveScorer.hh"//
#include "G4PSEnergyDeposit.hh"//
#include "G4PSTrackLength.hh"//
#include "G4VSDFilter.hh"
#include "G4VisAttributes.hh"//
#include "G4Colour.hh"//
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4PSPassageCellCurrent.hh"
#include "G4SDParticleFilter.hh"
#include "G4SDKineticEnergyFilter.hh"
#include "G4PSNofStep.hh"//

#include "G4SystemOfUnits.hh"//
#include "G4ios.hh"//



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 :G4VUserDetectorConstruction(),
  fCheckOverlaps(true)
{;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  static const G4double pi = 3.14159265358979323846;
  static const G4double inch = 2.54*cm;
  //
  // define Air and Pyrex
  //   
  G4NistManager* NISTman= G4NistManager::Instance();
  G4Material* fAir   = NISTman->FindOrBuildMaterial("G4_AIR"); 
  G4Material *fLead = NISTman->FindOrBuildMaterial("G4_Pb");
  G4Material* fAluminum = NISTman->FindOrBuildMaterial("G4_Al");
  G4Material* fBeryllium = NISTman->FindOrBuildMaterial("G4_Be");
  G4Material* fPlastic = NISTman->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* fCarbon = NISTman->FindOrBuildMaterial("G4_C");
  

  //----------------------------------------------------------------------
  // World
  //
  //G4double fWorldSize = 9* cm;
  G4Box*  
  worldSolid = new G4Box("World",                          //its name
                   10.*m,10.*m,10.*m);//its size
                   
  G4LogicalVolume*                         
  worldLogical = new G4LogicalVolume(worldSolid,             //its solid
                                   fAir,                    //its material
                                   "World");               //its name
  G4VPhysicalVolume*                                   
  fWorldPhys = new G4PVPlacement(0,                        //no rotation
                                 G4ThreeVector(),          //at (0,0,0)
                                 worldLogical,               //its logical volume
                                 "World",                  //its name
                                 0,                        //its mother  volume
                                 false,                    //no boolean operation
                                 0);                       //copy number
 
  //----------------------------------------------------------------------
  
  
  

 
					     
  //Carbon Strippers
  //Carbon 1
  
  G4Box* carbon1 = new G4Box("Carbon1", 2*cm, 2*cm, 0.01*cm);

  G4LogicalVolume*
    carbon1logical = new G4LogicalVolume(carbon1, fCarbon, "Carbon1");

  new G4PVPlacement(0 ,
		   G4ThreeVector(0, 0, 0),
		   carbon1logical,
		   "Carbon1",
		   worldLogical,
		   false,
		   0);

  //Carbon 2

   G4Box* carbon2 = new G4Box("Carbon2", 2*cm, 2*cm, 0.01*cm);

  G4LogicalVolume*
    carbon2logical = new G4LogicalVolume(carbon2, fCarbon, "Carbon2");

  new G4PVPlacement(0 ,
		   G4ThreeVector(-3.5*m, 0, 0),
		   carbon2logical,
		   "Carbon2",
		   worldLogical,
		   false,
		   0);



  //
  //Visualization attributes (This makes the World Invisible)
  //
  worldLogical->SetVisAttributes (G4VisAttributes::Invisible);	//world is invisible
 
  G4VisAttributes* simpleBoxVisAtt = new G4VisAttributes(G4Colour::Grey());

  simpleBoxVisAtt->SetVisibility(true);	
  			
  
  carbon1logical->SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));
  carbon2logical->SetVisAttributes(new G4VisAttributes(G4Colour::Blue()));

//--------------
  
  //
  //always return the physical World
  //  
 
  return fWorldPhys;
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{;} 
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

