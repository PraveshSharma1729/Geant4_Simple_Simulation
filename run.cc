#include "run.hh"
#include <sstream>

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();

man->OpenFile("0.5mm.root");

man->CreateNtuple("E_Dep","E_Dep");
man->CreateNtupleDColumn("Enegy_511keV_Photon_0.5mm_Pb");
man->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();

man->Write();

man->CloseFile();

}

