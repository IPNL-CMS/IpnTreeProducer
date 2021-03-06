#ifdef __CINT__
#include "../interface/TRootRun.h"
#include "../interface/TRootBeamStatus.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootHLTObject.h"
#include "../interface/TRootBeamSpot.h"
#include "../interface/TRootVertex.h"
#include "../interface/TRootTrack.h"
#include "../interface/TRootJet.h"
#include "../interface/TRootMuon.h"
#include "../interface/TRootPhoton.h"
#include "../interface/TRootMCPhoton.h"
#include "../interface/TRootMCElectron.h"
#include "../interface/TRootElectron.h"
#include "../interface/TRootTau.h"
#include "../interface/TRootSignalEvent.h"
#include "../interface/TRootCluster.h"
#include "../interface/TRootSuperCluster.h"
#include "../interface/TRootMET.h"
#include "../interface/TRootTopTop.h"
#include "../interface/TRootEcalRecHit.h"
#include "../interface/TRootBardak.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/HybridGBRTree.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/HybridGBRForest.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/RooHybridBDTAutoPdf.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/RooDoubleCBFast.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/RooCBExp.h"
#else
#include "../interface/TRootRun.h"
#include "../interface/TRootBeamStatus.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootMCElectron.h"
#include "../interface/TRootHLTObject.h"
#include "../interface/TRootBeamSpot.h"
#include "../interface/TRootVertex.h"
#include "../interface/TRootTrack.h"
#include "../interface/TRootJet.h"
#include "../interface/TRootMuon.h"
#include "../interface/TRootPhoton.h"
#include "../interface/TRootMCPhoton.h"
#include "../interface/TRootElectron.h"
#include "../interface/TRootTau.h"
#include "../interface/TRootSignalEvent.h"
#include "../interface/TRootCluster.h"
#include "../interface/TRootSuperCluster.h"
#include "../interface/TRootMET.h"
#include "../interface/TRootTopTop.h"
#include "../interface/TRootEcalRecHit.h"
#include "../interface/TRootBardak.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/HybridGBRTree.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/HybridGBRForest.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/RooHybridBDTAutoPdf.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/RooDoubleCBFast.h"
#include "../../../HiggsAnalysis/GBRLikelihood/interface/RooCBExp.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;
#pragma link C++ class TRootRun;
#pragma link C++ class TRootBeamStatus;
#pragma link C++ class TRootEvent;
#pragma link C++ class TRootParticle;
#pragma link C++ class TRootMCParticle;
#pragma link C++ class TRootHLTObject;
#pragma link C++ class TRootBeamSpot;
#pragma link C++ class TRootVertex;
#pragma link C++ class TRootTrack;
#pragma link C++ class TRootJet;
#pragma link C++ class TRootMuon;
#pragma link C++ class TRootPhoton;
#pragma link C++ class TRootMCPhoton;
#pragma link C++ class TRootMCElectron;
#pragma link C++ class TRootElectron;
#pragma link C++ class TRootTau;
#pragma link C++ class TRootSignalEvent;
#pragma link C++ class TRootCluster;
#pragma link C++ class TRootSuperCluster;
#pragma link C++ class TRootMET;
#pragma link C++ class TRootTopTop;
#pragma link C++ class TRootEcalRecHit;
#pragma link C++ class TRootBardak;
#pragma link C++ class HybridGBRForest+;
#pragma link C++ class HybridGBRTree+;
#pragma link C++ class RooGBRFunction+;
#pragma link C++ class RooGBRTarget+;
#pragma link C++ class RooCondAddPdf+;
#pragma link C++ class RooPdfAddReal+;
#pragma link C++ class RooTreeConvert+;
#pragma link C++ class RooRealConstraint+;
#pragma link C++ class RooPowerLaw+;
#pragma link C++ class RooDoubleCBFast+;
#pragma link C++ class RooCBExp+;

#endif
