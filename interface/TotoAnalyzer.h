#ifndef TotoAnalyzer_h
#define TotoAnalyzer_h

// system include files
#include <memory>
#include <string>
#include <iostream>
#include <ctime>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Provenance/interface/EventID.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "FWCore/Framework/interface/FileBlock.h"
#include "DataFormats/Common/interface/ConditionsInEdm.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEgamma/EgammaTools/interface/ConversionLikelihoodCalculator.h"

#include "../interface/L1TriggerAnalyzer.h"
#include "../interface/HLTAnalyzer.h"
#include "../interface/MCAnalyzer.h"
#include "../interface/MCAssociator.h"
#include "../interface/VertexAnalyzer.h"
#include "../interface/ZeeVertexAnalyzer.h"
#include "../interface/TrackAnalyzer.h"
#include "../interface/JetAnalyzer.h"
#include "../interface/MuonAnalyzer.h"
#include "../interface/ElectronAnalyzer.h"
#include "../interface/PhotonAnalyzer.h"
#include "../interface/ClusterAnalyzer.h"
#include "../interface/SuperClusterAnalyzer.h"
#include "../interface/EcalRecHitsAnalyzer.h"
#include "../interface/METAnalyzer.h"
#include "../interface/ClusterAssociator.h"
#include "../interface/ElectronAssociator.h"
#include "../interface/PhotonAssociator.h"
#include "../interface/PhotonIsolator.h"
#include "../interface/AmbiguitySolver.h"

#include "../interface/TRootRun.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootSignalEvent.h"
#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootBeamSpot.h"
#include "../interface/TRootVertex.h"
#include "../interface/TRootTrack.h"
#include "../interface/TRootJet.h"
#include "../interface/TRootMuon.h"
#include "../interface/TRootElectron.h"
#include "../interface/TRootPhoton.h"
#include "../interface/TRootCluster.h"
#include "../interface/TRootSuperCluster.h"
#include "../interface/TRootEcalRecHit.h"
#include "../interface/TRootMET.h"
#include "../interface/TRootBardak.h"

#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"


class TotoAnalyzer : public edm::EDAnalyzer
{
   
   public:
      explicit TotoAnalyzer(const edm::ParameterSet&);
      ~TotoAnalyzer();
      
   private:
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void beginJob() ;
      virtual void endJob() ;
      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void respondToOpenInputFile(edm::FileBlock const& fb);
      virtual void respondToCloseInputFile(edm::FileBlock const& fb);
      
      edm::ParameterSet myConfig_;
      edm::ParameterSet producersNames_;
      
      time_t startTime_;
      int verbosity_;
      bool allowMissingCollection_;
      std::string rootFileName_ ;
      TFile* rootFile_ ;
      TTree* eventTree_;
      TTree* runTree_;
      std::string dataType_ ;
      double datasetXsection_;
      std::string datasetDesciption_;
      bool doL1_;
      bool doHLT_;
      bool doMC_;
      bool doJetMC_;
      bool doMETMC_;
      bool doPDFInfo_;
      bool doSignalMuMuGamma_;
      bool doSignalTopTop_;
      bool doPhotonConversionMC_;
      bool drawMCTree_;
      bool doBeamSpot_;
      bool doPrimaryVertex_;
      bool doZeePrimaryVertex_;
      bool doTrack_;
      bool doJet_;
      bool doMuon_;
      bool doElectron_;
      bool doPhoton_;
      bool doCluster_;
      bool keepAllEcalRecHits_;
      bool keepClusterizedEcalRecHits_;
      bool doPhotonConversion_;
      bool doPhotonIsolation_;
      bool doMET_;
      bool doBardak_;
      
      ConversionLikelihoodCalculator* conversionLikelihoodCalculator_;
      
      int nTotEvt_;
      TRootRun* runInfos_;
      TRootEvent* rootEvent_;
      TRootEvent::BeamStatus lhcStatus_;
      L1TriggerAnalyzer* l1TriggerAnalyzer_;
      HLTAnalyzer* hltAnalyzer_;
      TClonesArray* rootMCParticles_;
      TClonesArray* rootGenJets_;
      TClonesArray* rootGenMETs_;
      TRootSignalEvent* rootMuMuGammaEvent_;
      TClonesArray* rootMCTopTop_;
      TClonesArray* rootMCPhotons_;
      TRootBeamSpot* rootBeamSpot_;
      TClonesArray* rootVertices_;
      TClonesArray* rootZeeVertices_;
      TClonesArray* rootTracks_;
      unsigned int nJetsArrays_;
      TClonesArray** rootJetsArrays_;
      TClonesArray* rootMuons_;
      TClonesArray* rootElectrons_;
      TClonesArray* rootPhotons_;
      TClonesArray* rootBasicClusters_;
      TClonesArray* rootSuperClusters_;
      TClonesArray* rootEcalRecHits_;
      TClonesArray* rootConversionTracks_;
      TClonesArray* rootMETs_;
      TRootBardak* rootBardak_;
      
};

#endif
