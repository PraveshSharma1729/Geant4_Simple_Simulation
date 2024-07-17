#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
G4NistManager *nist = G4NistManager::Instance();


G4Material *Silicon= nist->FindOrBuildMaterial("G4_Si");

G4Material *worldMat =nist->FindOrBuildMaterial("G4_Galactic");

G4Material *Tungsten= nist->FindOrBuildMaterial("G4_W");

G4Box *solidWorld = new G4Box("solidWorld",20.0*m,20.0*m,20.0*m);

G4LogicalVolume *logicWorld = new G4LogicalVolume( solidWorld, worldMat, "logicWorld");

G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

	
	
	
// Defining Logic Volume for Absorber
    G4double zPlaneAbs[] = { 0*um, 0.5*mm }; // Z planes
    G4double rInnerAbs[] = { 0*cm, 0*cm };  // Inner radius
    G4double rOuterAbs[] = { 101.6*mm, 101.6*mm };  // Outer radius
 
    G4Polyhedra* Abs = new G4Polyhedra("Abs", 0.*deg, 360.*deg, 6, 2, zPlaneAbs, rInnerAbs, rOuterAbs);

    G4LogicalVolume *logicAbs = new G4LogicalVolume(Abs, Tungsten, "logicAbs");


	// Create and configure visualization attributes
	G4VisAttributes* absVisAttr = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Redcolor
	absVisAttr->SetVisibility(true); // Ensure the volume is visible
	absVisAttr->SetForceSolid(true); // Render the volume as a solid object

	// Assign the visualization attributes to the logical volume
	logicAbs->SetVisAttributes(absVisAttr);



 // Defining Logic volume for Silicon sensors
 
    G4double zPlane[] = { 0*um, 300*um }; // Z planes
    G4double rInner[] = { 0*cm, 0*cm };  // Inner radius
    G4double rOuter[] = { 10.0*cm, 10.0*cm };  // Outer radius
 
    G4Polyhedra* solidDetector = new G4Polyhedra("solidDetector", 0.*deg, 360.*deg, 6, 2, zPlane, rInner, rOuter);
    G4RotationMatrix* rotation = new G4RotationMatrix();
    rotation->rotateZ(30.0 * CLHEP::degree);

    logicDetector = new G4LogicalVolume(solidDetector, Silicon, "logicDetector");
    fScoringVolume = logicDetector;

    
	
    G4VPhysicalVolume *physDetector = new G4PVPlacement(rotation,G4ThreeVector(0.,0.,5*cm),logicDetector,"physDetector",logicWorld,false,1,true);
		
    G4VPhysicalVolume *physAbs = new G4PVPlacement(rotation, G4ThreeVector(0.0,0.0,5*cm-0.5*mm),logicAbs,"physAbs",logicWorld,false,2,true);
		




return physWorld;
}





void MyDetectorConstruction :: ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	
	logicDetector->SetSensitiveDetector(sensDet);


}
