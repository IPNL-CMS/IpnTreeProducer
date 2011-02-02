#ifndef TauAnalyzer_h
#define TauAnalyzer_h

#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TauReco/interface/PFTauFwd.h"
//#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
//#include "DataFormats/Math/interface/Point3D.h"

#include "../interface/LeptonAnalyzer.h"
#include "../interface/TRootTau.h"

#include "TClonesArray.h"


class TauAnalyzer : public LeptonAnalyzer
{

   public:
      TauAnalyzer(const edm::InputTag& tauProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
      ~TauAnalyzer();
      bool process(const edm::Event& iEvent, TRootBeamSpot* rootBeamSpot, TClonesArray* rootTaus);

   private:
      bool useMC_;
      edm::InputTag tauProducer_;

};

#endif
