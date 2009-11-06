#ifndef MCAssociator_h
#define MCAssociator_h

#include <memory>
#include <string>
#include <iostream>
#include <map>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootJet.h"

#include "TClonesArray.h"


class MCAssociator
{

   public:
      MCAssociator();
      MCAssociator(const edm::ParameterSet& producersNames, int verbosity);
      ~MCAssociator() {};
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      void init(const edm::Event& iEvent, TClonesArray* mcParticles);
      void matchGenParticlesTo(TClonesArray* recoParticles);
      void printParticleAssociation(TClonesArray* recoParticles);
      void processGenJets(TClonesArray* genJets, TClonesArray* recoJets);
      void printJetAssociation(TClonesArray* recoJets);

   private:
      int verbosity_;
      int nMC_;
      TClonesArray* mcParticles_;
      edm::Handle <reco::GenParticleCollection> genParticles_;
      std::map<int,int> mcParticlesMap_; // map between index in genParticle collection and index in mcParticles TClonesArray
      edm::InputTag genParticlesProducer_;

};

#endif
