#include "../interface/TrackAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

TrackAnalyzer::TrackAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
   trackProducer_ = producersNames.getParameter<edm::InputTag>("trackProducer");
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}

TrackAnalyzer::~TrackAnalyzer()
{
}

bool TrackAnalyzer::process(const edm::Event& iEvent, TClonesArray* rootTracks)
{

   edm::Handle<reco::TrackCollection> recoTracks;
   try
   {
      iEvent.getByLabel(trackProducer_, recoTracks);
      int nTracks = recoTracks->size();
      if(verbosity_>1) std::cout << "   Number of tracks = " << nTracks << "   Label: " << trackProducer_.label() << "   Instance: " << trackProducer_.instance() << std::endl;
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  TrackAnalyzer::process => Track collection is missing #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No Track collection, skip track info" << endl;
      return false;
   }

   for (unsigned int j=0; j<recoTracks->size(); j++)
   {
      const reco::HitPattern& hit = (*recoTracks)[j].hitPattern();

      TRootTrack localTrack(
      (*recoTracks)[j].px()
      ,(*recoTracks)[j].py()
      ,(*recoTracks)[j].pz()
      ,(*recoTracks)[j].p()
      ,(*recoTracks)[j].vx()
      ,(*recoTracks)[j].vy()
      ,(*recoTracks)[j].vz()
      ,0
      ,(*recoTracks)[j].charge()
      ,hit.pixelLayersWithMeasurement()
      ,hit.stripLayersWithMeasurement()
      ,(*recoTracks)[j].chi2()
      ,(*recoTracks)[j].d0()
      ,(*recoTracks)[j].d0Error()
      ,(*recoTracks)[j].dz()
      ,(*recoTracks)[j].dzError()
      );

      new( (*rootTracks)[j] ) TRootTrack(localTrack);
      if(verbosity_>2) std::cout << "   ["<< setw(3) << j << "] " << localTrack << std::endl;
   }

   return true;
}
