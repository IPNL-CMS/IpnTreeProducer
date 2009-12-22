#include "../interface/VertexAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

VertexAnalyzer::VertexAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
	beamSpotProducer_ = producersNames.getParameter<edm::InputTag>("beamSpotProducer");
	allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}


VertexAnalyzer::VertexAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
	beamSpotProducer_ = producersNames.getParameter<edm::InputTag>("beamSpotProducer");
	allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}


VertexAnalyzer::~VertexAnalyzer()
{
}


bool VertexAnalyzer::getBeamSpot(const edm::Event& iEvent, TRootBeamSpot* rootBeamSpot)
{
	try
	{
		edm::Handle<reco::BeamSpot> recoBeamSpot;
		iEvent.getByLabel(beamSpotProducer_, recoBeamSpot);
		
		if ( recoBeamSpot.isValid() )
		{
			if(verbosity_>1) std::cout  << "   Beam Spot - Label: " << beamSpotProducer_.label() << "   Instance: " << beamSpotProducer_.instance() << std::endl;
			rootBeamSpot->fill(
			recoBeamSpot->x0()
			,recoBeamSpot->y0()
			,recoBeamSpot->z0()
			,recoBeamSpot->x0Error()
			,recoBeamSpot->y0Error()
			,recoBeamSpot->z0Error()
			,recoBeamSpot->sigmaZ()
			,recoBeamSpot->sigmaZ0Error()
			,recoBeamSpot->BeamWidthX()
			,recoBeamSpot->BeamWidthXError()
			,recoBeamSpot->BeamWidthY()
			,recoBeamSpot->BeamWidthYError()
			);
			if(verbosity_>2) cout << "   "<< *rootBeamSpot << endl << endl;
		}
		else
		{
			if(verbosity_>1) cout << "  ##### ERROR IN  VertexAnalyzer::getBeamSpot => No beam spot available from EventSetup #####"<<endl;
			return false;
		}
	}
	catch (cms::Exception& exception)
	{
		if ( !allowMissingCollection_ )
		{
			cout << "  ##### ERROR IN  VertexAnalyzer::getBeamSpot => No beam spot available from EventSetup #####"<<endl;
			throw exception;
		}
		if(verbosity_>1) cout <<  "   ===> No beam spot available, skip beam spot info" << endl;
		return false;
	}
	
	return true;
}


bool VertexAnalyzer::getVertices(const edm::Event& iEvent, TClonesArray* rootVertices)
{
	
	edm::Handle< reco::VertexCollection > recoVertices;
	try
	{
		iEvent.getByLabel(primaryVertexProducer_, recoVertices);
		int nVertices = recoVertices->size();
		if(verbosity_>1) std::cout  << "   Number of primary vertices = " << nVertices << "   Label: " << primaryVertexProducer_.label() << "   Instance: " << primaryVertexProducer_.instance() << std::endl;
	}
	catch (cms::Exception& exception)
	{
		if ( !allowMissingCollection_ )
		{
			cout << "  ##### ERROR IN  VertexAnalyzer::getVertices => Vertex collection is missing #####"<<endl;
			throw exception;
		}
		if(verbosity_>1) cout <<  "   ===> No primaryVertex collection, skip vertex info" << endl;
		return false;
	}
	
	int iRootVertex = 0;
	for (unsigned int j=0; j<recoVertices->size(); j++)
	{
		const reco::Vertex* vertex = & ((*recoVertices)[j]);
		
		// TODO - Put your vertex selection here....
		//if (! vertex->isValid() ) continue;
		//if ( vertex->isFake() ) continue;
		
		Int_t ntracks = 0;
		Float_t higherPt = 0.;
		Float_t scalarSumPt = 0.;
		Float_t vectorSumPt = 0.;
		math::XYZVector vectorSum(0.,0.,0.);
		
		for( std::vector< reco::TrackBaseRef >::const_iterator it = vertex->tracks_begin(); it != vertex->tracks_end(); it++)
		{
			scalarSumPt += (**it).pt();
			vectorSum += (**it).momentum();
			if( (**it).pt()>higherPt ) higherPt=(**it).pt();
			ntracks++;
		}
		vectorSumPt = sqrt(vectorSum.Perp2());
		
		// No refitted tracks embeded in reco::Vertex....
		//cout  << "vertex->refittedTracks().size()=" << vertex->refittedTracks().size() << endl;
		
		TRootVertex localVertex(
		vertex->x()
		,vertex->y()
		,vertex->z()
		,vertex->xError()
		,vertex->yError()
		,vertex->zError()
		);
		
		localVertex.setAlgoName("RECO");
		localVertex.setIsValid( vertex->isValid() );
		localVertex.setIsFake( vertex->isFake() );
		localVertex.setChi2( vertex->chi2() );
		localVertex.setNdof( vertex->ndof() );
		localVertex.setNtracks( ntracks );
		localVertex.setHigherTrackPt( higherPt );
		localVertex.setScalarSumPt( scalarSumPt );
		localVertex.setVectorSumPt( vectorSumPt );
		
		new( (*rootVertices)[iRootVertex] ) TRootVertex(localVertex);
		if(verbosity_>2) cout << "   ["<< setw(3) << iRootVertex << "] " << localVertex << endl;
		iRootVertex++;
	}
	
	return true;
}


void VertexAnalyzer::selectPrimary(TRootEvent* rootEvent, TClonesArray* rootVertices)
{
	
	int ibestVertex = -1;
	float highestScalarSumPt = -1.;
	TRootVertex* localVertex = 0;
	
	for (int ivtx=0; ivtx<rootVertices->GetEntriesFast(); ivtx++)
	{
		localVertex = (TRootVertex*) rootVertices->At(ivtx);
		// Put you primary vertex selection here...
		if ( localVertex->scalarSumPt()>highestScalarSumPt )
		{
			highestScalarSumPt = localVertex->scalarSumPt();
			ibestVertex = ivtx;
		}
	}
	
	if ( ibestVertex >= 0)
	{
		localVertex = (TRootVertex*) rootVertices->At(ibestVertex);
		rootEvent->setPrimaryVertexIndex( ibestVertex );
		rootEvent->setPrimaryVertex( localVertex );
	}
	
	if(verbosity_>2) std::cout  << "   Selected primary vertex: TRootVertex[" << ibestVertex << "]" << std::endl;
}
