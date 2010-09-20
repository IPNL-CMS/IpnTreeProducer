#ifndef ParticleTreeDrawer_h
#define ParticleTreeDrawer_h
//
// class ParticleTreeDrawer
// Adapted from Luca Lista's plugin
//
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
//#include "DataFormats/HepMCCandidate/interface/GenParticleCandidate.h"

#include <iostream>
#include <algorithm>


class ParticleTreeDrawer
{

   public:
      ParticleTreeDrawer(const edm::ParameterSet & config, const edm::ParameterSet & producersNames);
      bool analyze( const edm::Event &, const edm::EventSetup & );

   private:
      bool allowMissingCollection_;
      edm::InputTag src_;
      edm::ESHandle<ParticleDataTable> pdt_;
      bool printP4_, printPtEtaPhi_, printVertex_, printStatus_, printIndex_;
      typedef std::vector<int> vint;
      vint status_;
      std::vector<const reco::Candidate *> cands_;

      void printDecay( const reco::Candidate &, const std::string & pre ) const;
      //void printP4( const reco::Candidate & ) const;
      void printInfo( const reco::Candidate & ) const;
      bool accept( const reco::Candidate & ) const;
      bool hasValidDaughters( const reco::Candidate & ) const;

};

#endif
