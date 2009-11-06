#include "../interface/LeptonAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

LeptonAnalyzer::LeptonAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity),initOK_(false),dummyVertex_(false),trackBuilder_(),primaryVertex_(0),vertexPoint_(0)
{
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
   dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
   doPrimaryVertex_ = myConfig.getUntrackedParameter<bool>("doPrimaryVertex");
   doBeamSpot_ = myConfig.getUntrackedParameter<bool>("doBeamSpot");
   vertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
}


LeptonAnalyzer::~LeptonAnalyzer()
{
   if (dummyVertex_) delete primaryVertex_;
   if (vertexPoint_ != 0) delete vertexPoint_;
}


void LeptonAnalyzer::initIPCalculator(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent, TRootBeamSpot* rootBeamSpot)
{
   
   // Get the track builder
   try
   {
      iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder_);
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  LeptonAnalyzer::initIPCalculator => Track builder is missing in EventSetup #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No Track builder, skip IP3D calculation" << endl;
      initOK_ = false;
   }
   
   // Get primary vertex collection
   unsigned int nVertices = 0;
   edm::Handle< reco::VertexCollection > recoVertices;
   try
   {
      iEvent.getByLabel(vertexProducer_, recoVertices);
      nVertices = recoVertices->size();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  LeptonAnalyzer::initIPCalculator => Vertex collection is missing #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No Vertex collection, skip IP3D calculation" << endl;
      initOK_ = false;
   }
   
   
   if ( nVertices==0 )
   {
      // FIXME - Take beamspot instead ?
      cout << "***** ERROR in LeptonAnalyzer::initIPCalculator() - No reco::Vertex for this event - Will use dummy vertex *****" << endl;
      reco::Vertex::Point point(0,0,0);
      reco::Vertex::Error error;
      error(0,0) = 0.0015*0.0015;
      error(1,1) = 0.0015*0.0015;
      error(2,2) = 15.*15.;
      primaryVertex_ = new reco::Vertex(point,error,1,1,1);
      dummyVertex_ = true;
   }
   else if ( rootEvent->primaryVertexIndex()>=int(recoVertices->size()) )
   {
      cout << "***** ERROR in LeptonAnalyzer::initIPCalculator() - Selected primary vertex not found in reco::Vertex collection - Will use first reco::Vertex *****" << endl;
      primaryVertex_ = & ((*recoVertices)[0]);
   }
   else if ( rootEvent->primaryVertexIndex()<0 )
   {
      cout << "***** ERROR in LeptonAnalyzer::initIPCalculator() - No Primary vertex was selected in reco::Vertex collection - Will use first reco::Vertex *****" << endl;
      primaryVertex_ = & ((*recoVertices)[0]);
   }
   else
   {
      primaryVertex_ = & ((*recoVertices)[rootEvent->primaryVertexIndex()]);
   }
   
   vertexPoint_ = new GlobalPoint(primaryVertex_->position().x(),primaryVertex_->position().y(),primaryVertex_->position().z());
   
   initOK_ = true;
}


float LeptonAnalyzer::ip3DSignificance(const reco::TransientTrack& track)
{
   float significance = -9999.;
   if ( initOK_ )
   {
      const TrajectoryStateOnSurface tsos = track.stateOnSurface(*vertexPoint_);
      if (!tsos.isValid())
      {
         significance = -8888.;
      }
      else
      {
         std::pair<bool,Measurement1D> muIPpair;
         muIPpair = IPTools::signedImpactParameter3D(tsos, tsos.globalDirection(), *primaryVertex_);
         
         if (muIPpair.first)
         {
            significance = muIPpair.second.significance();
         }
         else
         {
            significance = -7777.;
         }
      }
   }
   return significance;
}
