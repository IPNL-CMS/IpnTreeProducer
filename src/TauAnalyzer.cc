#include "../interface/TauAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

TauAnalyzer::TauAnalyzer(const edm::InputTag& tauProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):LeptonAnalyzer(producersNames, myConfig, verbosity)
{
   useMC_ = myConfig.getUntrackedParameter<bool>("doTauMC");
   tauProducer_ = tauProducer;
}

TauAnalyzer::~TauAnalyzer()
{
}

bool TauAnalyzer::process(const edm::Event& iEvent, TRootBeamSpot* rootBeamSpot, TClonesArray* rootTaus)
{
   
  if ( dataType_!="PAT" ) {

    if (verbosity_>1) cout <<  " TauAnalyzer::process() dataType_ != PAT ===> skip tau info" << endl;

    // Do nothing : I just do not know how to handle taus at RECO level.

    return true;
  }

  unsigned int nTaus=0;
  edm::Handle < std::vector <pat::Tau> > patTaus;

  try
    {
      iEvent.getByLabel(tauProducer_, patTaus);
      nTaus = patTaus->size();
    }
  catch (cms::Exception& exception)
    {
      if ( !allowMissingCollection_ )
	{
	  cout << "  ##### ERROR IN  TauAnalyzer::process => pat::Tau collection is missing #####"<<endl;
	  throw exception;
	}
      if(verbosity_>1) cout <<  "   ===> No pat::Tau collection, skip tau info" << endl;
      return false;
    }

  if(verbosity_>1) std::cout << "   Number of taus = " << nTaus << "   Label: " << tauProducer_.label() << "   Instance: " << tauProducer_.instance() << std::endl;

  for (unsigned int j=0; j<nTaus; ++j)
    {

      const pat::Tau* tau = & ((*patTaus)[j]);
      
      TRootTau localTau( tau->px()
			,tau->py()
			,tau->pz()
			,tau->energy()
			,tau->vx()
			,tau->vy()
			,tau->vz()
			,tau->pdgId()
			,tau->charge()
			);
     
     if(useMC_)
       {
	 // MC truth associator index
	 if ((tau->genParticleRef()).isNonnull()) {
	   localTau.setGenParticleIndex((tau->genParticleRef()).index());
	 } else {
	   localTau.setGenParticleIndex(-1);
	 }
       }
     
     new( (*rootTaus)[j] ) TRootTau(localTau);
     if(verbosity_>2 && verbosity_<4) cout << "   ["<< setw(3) << j << "] " << localTau << endl;
     if(verbosity_>=4) { cout << "   ["<< setw(3) << j << "] ";  localTau.Print(); cout << endl; }

    }
   
   return true;
}
