#ifndef ElectronAnalyzer_h
#define ElectronAnalyzer_h

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "DataFormats/EgammaReco/interface/ElectronSeed.h"

#include "../interface/LeptonAnalyzer.h"
#include "../interface/TRootElectron.h"

#include "TClonesArray.h"


class ElectronAnalyzer : public LeptonAnalyzer
{

   public:
      ElectronAnalyzer(const edm::InputTag& electronProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
      ~ElectronAnalyzer();
      bool process(const edm::Event& iEvent, TRootBeamSpot* rootBeamSpot, TClonesArray* rootElectrons, EcalClusterLazyTools* lazyTools);

   private:
      bool useMC_;
      edm::InputTag electronProducer_;
      edm::InputTag barrelEcalRecHitCollection_;
};

#endif
