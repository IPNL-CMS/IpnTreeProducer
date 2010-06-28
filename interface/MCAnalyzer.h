#ifndef MCAnalyzer_h
#define MCAnalyzer_h

// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/METReco/interface/GenMET.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruthFinder.h"
#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruth.h"
#include "RecoEgamma/EgammaMCTools/interface/ElectronMCTruth.h"
//#include "DataFormats/EgammaCandidates/interface/ConvertedPhoton.h"

#include "../interface/ParticleTreeDrawer.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootSignalEvent.h"
#include "../interface/TRootTopTop.h"
#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootMCPhoton.h"
#include "../interface/TRootJet.h"

#include "TClonesArray.h"


class MCAnalyzer
{

   public:
      MCAnalyzer(const edm::ParameterSet& config, const edm::ParameterSet& producersNames);
      ~MCAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      void drawMCTree(const edm::Event& iEvent, const edm::EventSetup& iSetup, const edm::ParameterSet& config, const edm::ParameterSet& producersNames);
      bool pdfInfo(const edm::Event& iEvent, TRootEvent* rootEvent);
      bool processMCParticle(const edm::Event& iEvent, TClonesArray* rootMCParticles);
      bool processGenJets(const edm::Event& iEvent, TClonesArray* rootGenJets);
      bool processGenMETs(const edm::Event& iEvent, TClonesArray* rootGenMETs);
      bool processConvertedPhoton(const edm::Event& iEvent, TClonesArray* rootMCPhotons);
      bool processMuMuGammaEvent(const edm::Event& iEvent, TRootSignalEvent* rootSignalEvent);
      bool processTopTopEvent(const edm::Event& iEvent, TClonesArray* rootMCTopTop);

   private:

      int verbosity_;

      bool doPhotonMC_;
      double photonMC_etaMax_;
      double photonMC_ptMin_;
      bool doElectronMC_;
      double electronMC_etaMax_;
      double electronMC_ptMin_;
      bool doMuonMC_;
      double muonMC_etaMax_;
      double muonMC_ptMin_;
      bool doJetMC_;
      double jetMC_etaMax_;
      double jetMC_ptMin_;
      bool doMETMC_;
      bool doUnstablePartsMC_;

      std::string signalGenerator_;
      edm::InputTag genParticlesProducer_;
      edm::InputTag genJetsProducer_;
      edm::InputTag genMETsProducer_;

      bool allowMissingCollection_;

};

#endif
