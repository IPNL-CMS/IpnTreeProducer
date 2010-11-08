#include "../interface/ZeeVertexAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

ZeeVertexAnalyzer::ZeeVertexAnalyzer(const edm::ParameterSet& iConfig, const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity), config_(iConfig)
{
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
   primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
   beamSpotProducer_ = producersNames.getParameter<edm::InputTag>("beamSpotProducer");
   trackProducer_ = producersNames.getParameter<edm::InputTag>("trackProducer");
   electronProducer_ = producersNames.getParameter<edm::InputTag>("electronProducerForZeeVertex");
}


ZeeVertexAnalyzer::~ZeeVertexAnalyzer()
{
}


bool ZeeVertexAnalyzer::getVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup, TClonesArray* rootVertices, TRootBardak* rootBardak)
{
   using namespace edm;
   int iRootVertex = 0;
   
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //    Very simple Zee selection: at least 2 electrons pT>10 GeV, |eta|<2.5,  60 < Mee < 120
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   edm::Handle< reco::GsfElectronCollection > electrons;
   iEvent.getByLabel(electronProducer_, electrons);
   int nElectrons = electrons->size();
   
   if(verbosity_>4) std::cout  << std::endl << "   Number of electrons = " << nElectrons << "   (" << electronProducer_.label() << " producer)" << std::endl;
   if(nElectrons<2) return false;
   
   // Highest ET electron
   Float_t maxPt = 0;
   unsigned int iElectron1 = 999999;
   for (unsigned int j=0; j<electrons->size(); j++)
   {
      const reco::GsfElectron* electron = & (electrons->at(j));
      if ( electron->pt() > maxPt && abs(electron->eta()) < 2.5 )
      {
         maxPt = electron->pt();
         iElectron1 = j;
      }
   }
   if(iElectron1==999999) return false;
   
   
   // Second highest ET electron
   maxPt = 0;
   unsigned int iElectron2 = 999999;
   for (unsigned int j=0; j<electrons->size(); j++)
   {
      const reco::GsfElectron* electron = & (electrons->at(j));
      if ( electron->pt() > maxPt && abs(electron->eta()) < 2.5 && j!=iElectron1 )
      {
         maxPt = electron->pt();
         iElectron2 = j;
      }
   }
   if(iElectron2==999999) return false;
   
   
   // Z mass
   ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > p4Electron1= (electrons->at(iElectron1)).p4();
   ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > p4Electron2= (electrons->at(iElectron2)).p4();
   ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > p4Z = p4Electron1 + p4Electron2;
   
   if(verbosity_>4) std::cout << "     Electron 1 - (Et,eta,phi)=(" << electrons->at(iElectron1).pt() << "," << electrons->at(iElectron1).eta() << "," << electrons->at(iElectron1).phi() << ")" << std::endl;
   if(verbosity_>4) std::cout << "     Electron 2 - (Et,eta,phi)=(" << electrons->at(iElectron2).pt() << "," << electrons->at(iElectron2).eta() << "," << electrons->at(iElectron2).phi() << ")" << std::endl;
   if(verbosity_>4) std::cout << "     Mee=" << p4Z.mass() << std::endl;
   
   //if( p4Z.mass()<60.0 || p4Z.mass()>120.0) return false;
   
   // Find CTF track best matching the GSF track assoicated to the electron
   // We will remove these tracks in the track collection for the primary vertex reconstruction
   reco::TrackRef tk1 = (electrons->at(iElectron1)).closestCtfTrackRef();
   reco::TrackRef tk2 = (electrons->at(iElectron2)).closestCtfTrackRef();

   if(tk1.isNull() || tk2.isNull())
   {
      if(verbosity_>4) std::cout << "  ##### ERROR IN  ZeeVertexAnalyzer::getVertices => Electron.closestCtfTrackRef() isNull  #####"<<endl;
      return false;
   }
   
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //    Private Primary Vertex reconstruction with all CTF tracks
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   // Get BeamSpot
   reco::BeamSpot vertexBeamSpot;
   edm::Handle<reco::BeamSpot> recoBeamSpotHandle;
   iEvent.getByLabel(beamSpotProducer_, recoBeamSpotHandle);
   if (recoBeamSpotHandle.isValid()) vertexBeamSpot = *recoBeamSpotHandle;
   
   // Get Track Collection
   edm::Handle<reco::TrackCollection> recoTracks;
   iEvent.getByLabel(trackProducer_, recoTracks);
   
   // Get Transient Track Collection
   edm::ESHandle<TransientTrackBuilder> trackBuilder;
   iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder);
   vector<reco::TransientTrack> transientTracks = (*trackBuilder).build(recoTracks, vertexBeamSpot);
   
   // Call Primary Vertex Reconstruction using all tracks in the event
   PrimaryVertexProducerAlgorithm theVertexProducer(config_);
   vector<TransientVertex> transientZeeVertices = theVertexProducer.vertices(transientTracks, vertexBeamSpot);
   
   reco::VertexCollection zeeVertices;
   for (vector<TransientVertex>::const_iterator vertex = transientZeeVertices.begin(); vertex != transientZeeVertices.end(); vertex++)
   {
      reco::Vertex v = *vertex;
      zeeVertices.push_back(v);
   }
   
   if(verbosity_>4) std::cout  << std::endl << "   Private Primary Vertex reconstruction with all tracks - Number of vertices = " << zeeVertices.size() << std::endl;
   
   for (unsigned int j=0; j<zeeVertices.size(); j++)
   {
      reco::Vertex* vertex = & (zeeVertices.at(j));
      
      // Put your vertex selection here....
      if (! vertex->isValid() ) continue;
      if ( vertex->isFake() ) continue;
      
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
      
      localVertex.setAlgoName("AllTracksFit");
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
   
   
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //    Private Primary Vertex reconstruction with all CTF tracks except the 2 two tracks matching selected electrons
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   // Remove the two CTF tracks matching the two electron GSF tracks from the transientTracks collection
   // Keep the two CTF electron tracks in a separate vector (eeTransientTracks)
   unsigned int itk1 = 999999;
   unsigned int itk2 = 999999;
   
   if(verbosity_>5) std::cout << std::endl << recoTracks->size() << "  tracks in recoTracks" << std::endl;
   if(verbosity_>5) std::cout << std::endl << "   Looping on " << transientTracks.size() << "  transientTracks" << std::endl;
   
   for (unsigned int j=0; j<transientTracks.size(); j++)
   {
      const reco::Track* tk = & (transientTracks.at(j).track());
      if(verbosity_>5) std::cout << "     Tk[" << j << "] (pt,eta,phi)=(" << tk->pt() << "," << tk->eta() << "," << tk->phi() << ")" << std::endl;
      if ( tk->pt()==tk1->pt() && tk->eta()==tk1->eta() && tk->phi()==tk1->phi() )
      {
         itk1 = j;
         if(verbosity_>5) std::cout << "     ===> this is tk1" << std::endl;
      }
      if ( tk->pt()==tk2->pt() && tk->eta()==tk2->eta() && tk->phi()==tk2->phi() )
      {
         itk2 = j;
         if(verbosity_>5) std::cout << "     ===> this is tk2" << std::endl;
      }
   }
   if (itk1==999999 || itk2==999999)
   {
      std::cout << "   ***** NO CTF TRACKS MATCHING THE ELECTRON *****" << std::endl;
      return false;
   }
   
   if(verbosity_>4)
   {
      std::cout << "     CTF Track 1 - (Et,eta,phi)=(" << transientTracks.at(itk1).track().pt() << "," << transientTracks.at(itk1).track().eta() << "," << transientTracks.at(itk1).track().phi() << "  -  Fraction of common hits with GSF =" <<  (electrons->at(iElectron1)).shFracInnerHits();
      if (!transientTracks.at(itk1).stateAtBeamLine().isValid()) std::cout << " IPSig=-1";
      else std::cout << " IPSig=" << transientTracks.at(itk1).stateAtBeamLine().transverseImpactParameter().significance();
      std::cout << " normChi2=" << transientTracks.at(itk1).normalizedChi2() << "  nSiHits=" <<  transientTracks.at(itk1).hitPattern().numberOfValidHits() << "  nPxlHits=" <<  transientTracks.at(itk1).hitPattern().numberOfValidPixelHits() << std::endl;
      
      std::cout << "     CTF Track 2 - (Et,eta,phi)=(" << transientTracks.at(itk2).track().pt() << "," << transientTracks.at(itk2).track().eta() << "," << transientTracks.at(itk2).track().phi() << "  -  Fraction of common hits with GSF =" <<  (electrons->at(iElectron2)).shFracInnerHits();
      if (!transientTracks.at(itk2).stateAtBeamLine().isValid()) std::cout << " IPSig=-1";
      else std::cout << " IPSig=" << transientTracks.at(itk2).stateAtBeamLine().transverseImpactParameter().significance();
      std::cout << " normChi2=" << transientTracks.at(itk2).normalizedChi2() << "  nSiHits=" <<  transientTracks.at(itk2).hitPattern().numberOfValidHits() << "  nPxlHits=" << transientTracks.at(itk2).hitPattern().numberOfValidPixelHits()<< std::endl;
   }
   
   
   rootBardak->setEle1(
      TRootTrack(
         transientTracks.at(itk1).track().px()
         ,transientTracks.at(itk1).track().py()
         ,transientTracks.at(itk1).track().pz()
         ,transientTracks.at(itk1).track().p()
         ,transientTracks.at(itk1).track().vx()
         ,transientTracks.at(itk1).track().vy()
         ,transientTracks.at(itk1).track().vz()
         ,0
         ,transientTracks.at(itk1).track().charge()
         ,transientTracks.at(itk1).hitPattern().pixelLayersWithMeasurement()
         ,transientTracks.at(itk1).hitPattern().stripLayersWithMeasurement()
         ,transientTracks.at(itk1).track().chi2()
         ,transientTracks.at(itk1).track().d0()
         ,transientTracks.at(itk1).track().d0Error()
         ,transientTracks.at(itk1).track().dz()
         ,transientTracks.at(itk1).track().dzError()
      )
      ,transientTracks.at(itk1).hitPattern().numberOfValidHits()
      ,transientTracks.at(itk1).hitPattern().numberOfValidPixelHits()
      ,transientTracks.at(itk1).stateAtBeamLine().transverseImpactParameter().significance()
      ,transientTracks.at(itk1).normalizedChi2()
   );
   
   rootBardak->setEle2(
      TRootTrack(
         transientTracks.at(itk2).track().px()
         ,transientTracks.at(itk2).track().py()
         ,transientTracks.at(itk2).track().pz()
         ,transientTracks.at(itk2).track().p()
         ,transientTracks.at(itk2).track().vx()
         ,transientTracks.at(itk2).track().vy()
         ,transientTracks.at(itk2).track().vz()
         ,0
         ,transientTracks.at(itk2).track().charge()
         ,transientTracks.at(itk2).hitPattern().pixelLayersWithMeasurement()
         ,transientTracks.at(itk2).hitPattern().stripLayersWithMeasurement()
         ,transientTracks.at(itk2).track().chi2()
         ,transientTracks.at(itk2).track().d0()
         ,transientTracks.at(itk2).track().d0Error()
         ,transientTracks.at(itk2).track().dz()
         ,transientTracks.at(itk2).track().dzError()
      )
      ,transientTracks.at(itk2).hitPattern().numberOfValidHits()
      ,transientTracks.at(itk2).hitPattern().numberOfValidPixelHits()
      ,transientTracks.at(itk2).stateAtBeamLine().transverseImpactParameter().significance()
      ,transientTracks.at(itk2).normalizedChi2()
   );
   
   vector<reco::TransientTrack> eeTransientTracks;
   eeTransientTracks.push_back(transientTracks.at(itk1));
   eeTransientTracks.push_back(transientTracks.at(itk2));
   if (itk1<itk2) itk2--;
   transientTracks.erase (transientTracks.begin()+itk1);
   transientTracks.erase (transientTracks.begin()+itk2);
   
   if(verbosity_>5)
   {
      for (unsigned int j=0; j<transientTracks.size(); j++)
      {
         const reco::Track* tk = & (transientTracks.at(j).track());
         std::cout << "     New Tk[" << j << "] (Et,eta,phi)=(" << tk->pt() << "," << tk->eta() << "," << tk->phi() << ")" << std::endl;
      }
   }
   
   // Call Primary Vertex Reconstruction using all tracks in the event except the two electrons
   vector<TransientVertex> transientNoEEVertices = theVertexProducer.vertices(transientTracks, vertexBeamSpot);
   
   reco::VertexCollection noEEVertices;
   for (vector<TransientVertex>::const_iterator vertex = transientNoEEVertices.begin(); vertex != transientNoEEVertices.end(); vertex++)
   {
      reco::Vertex v = *vertex;
      noEEVertices.push_back(v);
   }
   
   if(verbosity_>4) std::cout  << std::endl << "   Private Primary Vertex reconstruction with all tracks except the two electrons - Number of vertices = " << noEEVertices.size() << std::endl;
   
   for (unsigned int j=0; j<noEEVertices.size(); j++)
   {
      reco::Vertex* vertex = & (noEEVertices.at(j));
      
      // Put your vertex selection here....
      if (! vertex->isValid() ) continue;
      if ( vertex->isFake() ) continue;
      
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
      
      localVertex.setAlgoName("NoEEFit");
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
   
   
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //    Private Primary Vertex reconstruction with only the two CTF tracks matched to the selected electrons
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   vector<TransientVertex> transientOnlyEEVertices = theVertexProducer.vertices(eeTransientTracks, vertexBeamSpot);
   reco::VertexCollection onlyEEVertices;
   
   for (vector<TransientVertex>::const_iterator vertex = transientOnlyEEVertices.begin(); vertex != transientOnlyEEVertices.end(); vertex++)
   {
      reco::Vertex v = *vertex;
      onlyEEVertices.push_back(v);
   }
   
   if(verbosity_>4) std::cout  << std::endl << "   Private Primary Vertex reconstruction using only the two electron CTF tracks - Number of vertices = " << onlyEEVertices.size() << std::endl;
   
   for (unsigned int j=0; j<onlyEEVertices.size(); j++)
   {
      reco::Vertex* vertex = & (onlyEEVertices.at(j));
      
      // Put your vertex selection here....
      if (! vertex->isValid() ) continue;
      if ( vertex->isFake() ) continue;
      
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
      
      localVertex.setAlgoName("OnlyEEFit");
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
