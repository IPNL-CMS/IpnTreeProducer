#ifndef MuonAnalyzer_h
#define MuonAnalyzer_h

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/Point3D.h"

#include "../interface/LeptonAnalyzer.h"
#include "../interface/TRootMuon.h"

#include "TClonesArray.h"


class MuonAnalyzer : public LeptonAnalyzer
{

   public:
      MuonAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
      ~MuonAnalyzer();
      bool process(const edm::Event& iEvent, TRootBeamSpot* rootBeamSpot, TClonesArray* rootMuons);

   private:
      bool useMC_;
      edm::InputTag muonProducer_;

};

#endif
