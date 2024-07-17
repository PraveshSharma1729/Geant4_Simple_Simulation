#include "generator.hh"


MyPrimaryGenerator::MyPrimaryGenerator()
{

	fParticleGun =new G4ParticleGun(1);
	
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	//G4String particleName="mu-";
	G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
	
	G4ThreeVector pos(0.,0.,-5.0*cm);
	G4ThreeVector mom(0.,0.,1.);
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(511*keV);
	fParticleGun->SetParticleDefinition(particle);
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
