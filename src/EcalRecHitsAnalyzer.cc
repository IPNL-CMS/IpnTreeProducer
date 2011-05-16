#include "../interface/EcalRecHitsAnalyzer.h"

using namespace std;
//using namespace reco;
//using namespace edm;

EcalRecHitsAnalyzer::EcalRecHitsAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity),iRecHit_(0)
{
   barrelEcalRecHitCollection_ = producersNames.getParameter<edm::InputTag>("barrelEcalRecHitCollection");
   endcapEcalRecHitCollection_ = producersNames.getParameter<edm::InputTag>("endcapEcalRecHitCollection");
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}


EcalRecHitsAnalyzer::~EcalRecHitsAnalyzer()
{
}


bool EcalRecHitsAnalyzer::process(const edm::Event& iEvent, const edm::EventSetup& iSetup, TClonesArray* rootEcalRecHits)
{
   
   if(verbosity_>1) cout << endl << "Loading egamma LazyTools..." << endl;
   const EcalRecHitCollection *ebRecHits = 0;
   const EcalRecHitCollection *eeRecHits = 0;
   edm::Handle < EcalRecHitCollection > ebRecHitsHandle;
   edm::Handle < EcalRecHitCollection > eeRecHitsHandle;
   try
   {
      iEvent.getByLabel(barrelEcalRecHitCollection_, ebRecHitsHandle );
      ebRecHits = ebRecHitsHandle.product();
      iEvent.getByLabel(endcapEcalRecHitCollection_, eeRecHitsHandle ) ;
      eeRecHits = eeRecHitsHandle.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         if(verbosity_>1) cout << endl << "  ##### ERROR IN  EcalRecHitsAnalyzer::process => EcalRecHitCollections are missing #####" << endl;
         throw exception;
      }
      if(verbosity_>1) cout << endl << "   ===> No EcalRecHitCollections, skip rechits infos" << endl;
      return false;
   }
   
   edm::ESHandle<EcalSeverityLevelAlgo> severityLevelAlgo;
   iSetup.get<EcalSeverityLevelAlgoRcd>().get(severityLevelAlgo);
   
   // get the channel status from the DB
   //edm::ESHandle<EcalChannelStatus> chStatus;
   //iSetup.get<EcalChannelStatusRcd>().get(chStatus);
   //const EcalChannelStatus* channelStatus = 0;
   //if( chStatus.isValid() ) channelStatus = chStatus.product();
   
   if(verbosity_>1) std::cout << "   Number of EB recHits = " << ebRecHits->size() << "   Label: " << barrelEcalRecHitCollection_.label() << "   Instance: " << barrelEcalRecHitCollection_.instance() << std::endl;
   for( EcalRecHitCollection::const_iterator  hit = ebRecHits->begin(); hit != ebRecHits->end(); hit++)
   {
      EBDetId detId = (EBDetId) hit->id();
      
      int iflag;
      for (iflag=EcalRecHit::kUnknown; ; --iflag)
      {
         if ((*hit).checkFlag(iflag)) break;
         if (iflag==0) break;
      }
      
      TRootEcalRecHit localRecHit(
         detId.subdetId()
         ,hit->recoFlag()
         ,hit->energy()
         ,hit->time()
         ,detId.ieta()
         ,detId.iphi()
         ,hit->chi2()
         ,hit->outOfTimeEnergy()
         ,hit->outOfTimeChi2()
         ,severityLevelAlgo->severityLevel(detId, *ebRecHits)
      );
      new( (*rootEcalRecHits)[iRecHit_] ) TRootEcalRecHit(localRecHit);
      //if(verbosity_>4) cout << "   ["<< setw(3) << iRecHit_ << "] " << localRecHit << endl;
      //if(verbosity_>4) cout << "   ["<< iRecHit_ << "] " << localRecHit << endl;
      iRecHit_++;
   }
   
   if(verbosity_>1) std::cout << "   Number of EE recHits = " << eeRecHits->size() << "   Label: " << endcapEcalRecHitCollection_.label() << "   Instance: " << endcapEcalRecHitCollection_.instance() << std::endl;
   for( EcalRecHitCollection::const_iterator  hit = eeRecHits->begin(); hit != eeRecHits->end(); hit++)
   {
      EEDetId detId = (EEDetId) hit->id();
      
      int iflag;
      for (iflag=EcalRecHit::kUnknown; ; --iflag)
      {
         if ((*hit).checkFlag(iflag)) break;
         if (iflag==0) break;
      }
      
      TRootEcalRecHit localRecHit(
         detId.subdetId()
         ,hit->recoFlag()
         ,hit->energy()
         ,hit->time()
         ,detId.ix()
         ,detId.iy()
         ,hit->chi2()
         ,hit->outOfTimeEnergy()
         ,hit->outOfTimeChi2()
         ,severityLevelAlgo->severityLevel(detId, *eeRecHits)
      );
      new( (*rootEcalRecHits)[iRecHit_] ) TRootEcalRecHit(localRecHit);
      //if(verbosity_>4) cout << "   ["<< setw(3) << iRecHit_ << "] " << localRecHit << endl;
      //if(verbosity_>4) cout << "   ["<< iRecHit_ << "] " << localRecHit << endl;
      iRecHit_++;
   }
   
   //Sort rechits by energy using Lambda (BOOST Library)
   
   return true;
}
