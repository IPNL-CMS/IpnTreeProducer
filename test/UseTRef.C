#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>

using namespace std;

void UseTRef() {
   

   bool isCSA07Soup              = false;
   bool doHLT                    = true;
   bool doMC                     = true;
   bool doJetMC                  = true;
   bool doMETMC                  = true;
   bool doPDFInfo                = true;
   bool doSignalMuMuGamma        = false;
   bool doSignalTopTop           = false;
   bool doPhotonConversionMC     = false;
   bool doBeamSpot               = true;
   bool doPrimaryVertex          = true;
   bool doTrack                  = true;
   bool doJet                    = true;
   bool doMuon                   = true;
   bool doElectron               = true;
   bool doPhoton                 = true;
   bool doCluster                = true;
   bool doMET                    = true;
   bool doPhotonVertexCorrection = false;
   bool doPhotonIsolation        = true;
   bool doPhotonConversion       = true;
   
   TFile* f=new TFile("RecoAna.root");
   TTree* runTree = (TTree*) f->Get("runTree");
   TTree* eventTree = (TTree*) f->Get("eventTree");
   
   TBranch* run_br = (TBranch *) runTree->GetBranch("runInfos");
   TRootRun* runInfos = 0;
   run_br->SetAddress(&runInfos);
   
   TBranch* event_br = (TBranch *) eventTree->GetBranch("Event");
   TRootEvent* event = 0;
   event_br->SetAddress(&event);
   
   if(doMC)
   {
      TBranch* mcParticles_br = (TBranch *) eventTree->GetBranch("MCParticles");
      TClonesArray* mcParticles = new TClonesArray("TRootMCParticle", 0);
      mcParticles_br->SetAddress(&mcParticles);
   }
   
   if(doJetMC)
   {
      TBranch* genJets_br = (TBranch *) eventTree->GetBranch("genJets");
      TClonesArray* genJets = new TClonesArray("TRootParticle", 0);
      genJets_br->SetAddress(&genJets);
   }
   
   if(doMETMC)
   {
      TBranch* genMETs_br = (TBranch *) eventTree->GetBranch("genMETs");
      TClonesArray* genMETs = new TClonesArray("TRootParticle", 0);
      genMETs_br->SetAddress(&genMETs);
   }
   
   if(doSignalMuMuGamma)
   {
      TBranch* MuMuGamma_br = (TBranch *) eventTree->GetBranch("MuMuGamma");
      TRootSignalEvent* mcMuMuGammaEvent = 0;
      MuMuGamma_br->SetAddress(&mcMuMuGammaEvent);
   }
   
   if(doSignalTopTop)
   {
      TBranch* mcTopTop_br = (TBranch *) eventTree->GetBranch("rootMCTopTop");
      TClonesArray* mcTopTop = new TClonesArray("TRootTopTop", 0);
      mcTopTop_br->SetAddress(&mcTopTop);
   }
   
   if(doPhotonConversionMC)
   {
      TBranch* mcPhotons_br = (TBranch *) eventTree->GetBranch("MCPhotons");
      TClonesArray* mcPhotons = new TClonesArray("TRootMCPhoton", 0);
      mcPhotons_br->SetAddress(&mcPhotons);
   }
   
   if(doBeamSpot)
   {
      TBranch* BeamSpot_br = (TBranch *) eventTree->GetBranch("BeamSpot");
      TRootBeamSpot* beamSpot = 0;
      BeamSpot_br->SetAddress(&beamSpot);
   }
   
   if(doPrimaryVertex)
   {
      TBranch* vertices_br = (TBranch *) eventTree->GetBranch("Vertices");
      TClonesArray* vertices = new TClonesArray("TRootVertex", 0);
      vertices_br->SetAddress(&vertices);
      
   }
   
   if(doTrack)
   {
      TBranch* tracks_br = (TBranch *) eventTree->GetBranch("Tracks");
      TClonesArray* tracks = new TClonesArray("TRootTrack", 0);
      tracks_br->SetAddress(&tracks);
      
   }
   
   if(doJet)
   {
      TBranch* jets_br = (TBranch *) eventTree->GetBranch("Jets");
      TClonesArray* jets = new TClonesArray("TRootJet", 0);
      jets_br->SetAddress(&jets);
   }
   
   
   if(doMuon)
   {
      TBranch* muons_br = (TBranch *) eventTree->GetBranch("Muons");
      TClonesArray* muons = new TClonesArray("TRootMuon", 0);
      muons_br->SetAddress(&muons);
   }
   
   if(doElectron)
   {
      TBranch* electrons_br = (TBranch *) eventTree->GetBranch("Electrons");
      TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
      electrons_br->SetAddress(&electrons);
   }
   
   if(doPhoton)
   {
      TBranch* photons_br = (TBranch *) eventTree->GetBranch("Photons");
      TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
      photons_br->SetAddress(&photons);
   }
   
   if(doCluster)
   {
      TBranch* clusters_br = (TBranch *) eventTree->GetBranch("BasicClusters");
      TClonesArray* clusters = new TClonesArray("TRootCluster", 0);
      clusters_br->SetAddress(&clusters);
      
      TBranch* superClusters_br = (TBranch *) eventTree->GetBranch("SuperClusters");
      TClonesArray* superClusters = new TClonesArray("TRootSuperCluster", 0);
      superClusters_br->SetAddress(&superClusters);
   }
   
   if(doPhotonConversion)
   {
      TBranch* conversions_br = (TBranch *) eventTree->GetBranch("ConversionTracks");
      TClonesArray* conversionTracks = new TClonesArray("TRootTrack", 0);
      conversions_br->SetAddress(&conversionTracks);
   }
   
   if(doMET)
   {
      TBranch* met_br = (TBranch *) eventTree->GetBranch("MET");
      TClonesArray* met = new TClonesArray("TRootMET", 0);
      met_br->SetAddress(&met);
   }
   
   
   cout << "runTree->GetEntries()="<<runTree->GetEntries()<<endl;
   runTree->GetEvent(0);
   
   // Dataset infos
   cout << "Dataset desciption:"<<runInfos->description()<<endl;
   cout << "Dataset xsection:"<<runInfos->xsection()<<endl;
   
   // HLT Run Summary
   if (doHLT)
   {
      cout << dec << endl;
      cout << "HLT-Report " << "---------- Event  Summary ------------\n";
      cout << "HLT-Report"
      << " Events total = " << runInfos->nHLTEvents()
      << "  wasrun = " << runInfos->nHLTWasRun()
      << "  passed = " << runInfos->nHLTAccept()
      << "  errors = " << runInfos->nHLTErrors()
      << "\n";
      
      cout << endl;
      cout << "HLT-Report " << "---------- HLTrig Summary ------------\n";
      cout << "HLT-Report   HLT Bit#     WasRun     Passed     Errors  Name\n";
      
      for (unsigned int i=0; i!=runInfos->nHLTPaths(); ++i)
      {
         printf("HLT-Report %10u %10u %10u %10u  ", i, runInfos->hltWasRun(i), runInfos->hltAccept(i), runInfos->hltErrors(i));
         cout << runInfos->hltNames(i) << endl;
      }
      
      cout << endl;
   }
   
   unsigned int nEvents = (int)eventTree->GetEntries();
   //unsigned int nEvents = 2;
   
   for(unsigned int ievt=0; ievt<nEvents; ievt++)
   {
      eventTree->GetEvent(ievt);
      cout<<"Event #"<<event->nb()<<"  - Number of processed events: "<<ievt+1<<endl;
      
      if (doHLT)
      {
         //for(unsigned int ipath=0; ipath<event->nHLTPaths(); ipath++) cout << "   " << runInfos->hltNames(ipath) << " decision=" << event->trigHLT(ipath) <<endl;
         //for(unsigned int ipath=0; ipath<5; ipath++) cout << "   " << runInfos->hltNames(ipath) << " decision=" << event->trigHLT(ipath) <<endl;
      }
      
      
      if(doPhoton && doCluster)
      {
         cout << endl << "Photon list..." << endl;
         TRootPhoton* myphoton;
         for (int iphoton=0; iphoton< photons->GetEntriesFast(); iphoton++)
         {
            myphoton = (TRootPhoton*) photons->At(iphoton);
            cout << endl << "   [" << iphoton << "]"; myphoton->Print(); cout << " nConvTracks=" << myphoton->convNTracks() << endl;
            if (myphoton->convNTracks()>0)
            {
               TRootTrack* convtrack1 = myphoton->convTrack1();
               cout <<"            First Conversion Track pt=" << convtrack1->Pt() << endl;
               if (myphoton->convNTracks()>1)
               {
                  TRootTrack* convtrack2 = myphoton->convTrack2();
                  cout <<"            Second Conversion Track pt=" << convtrack2->Pt() << endl;
               }
            }
            // Look for the default supercluster associated to the photon
            // (Default SC collection for photon producer defined in RecoEgamma/EgammaPhotonProducers/python/photons_cfi.py)
            if( myphoton->superCluster() !=0 ) cout << "            Associated by default to to SC[" << myphoton->scIndex() <<"] with Et=" << myphoton->superCluster()->Pt() << " of type " << myphoton->superCluster()->type() << ": " << myphoton->superCluster()->typeName() << endl;
            // Or look for a particular type of supercluster associated to the photon (Type definition in TRootSuperCluster.h)
            if( myphoton->superClusterOfType(210) !=0 ) cout << "            Associated to Hybrid SC[" << myphoton->scIndexOfType(210) <<"] with Et=" << myphoton->superClusterOfType(210)->Pt() << endl;
            if( myphoton->superClusterOfType(211) !=0 ) cout << "            Associated to Corrected Hybrid SC[" << myphoton->scIndexOfType(211) <<"] with Et=" << myphoton->superClusterOfType(211)->Pt() << endl;
            if( myphoton->superClusterOfType(320) !=0 ) cout << "            Associated to Multi5x5 SC[" << myphoton->scIndexOfType(320) <<"] with Et=" << myphoton->superClusterOfType(320)->Pt() << endl;
            if( myphoton->superClusterOfType(322) !=0 ) cout << "            Associated to Corrected Multi5x5 with preshower SC[" << myphoton->scIndexOfType(322) <<"] with Et=" << myphoton->superClusterOfType(322)->Pt() << endl;
            if( myphoton->superClusterOfType(323) !=0 ) cout << "            Associated to Multi5x5 with preshower SC[" << myphoton->scIndexOfType(323) <<"] with Et=" << myphoton->superClusterOfType(323)->Pt() << endl;
            // Or loop over all superclusters associated to the photon
            for (unsigned int i=0; i<myphoton->nSuperClusters(); ++i)
               if( myphoton->superClusterAt(i) !=0 )  cout << "            " << (i+1) << "th supercluster associated to photon is SC[" << myphoton->scIndexAt(i) <<"] Et=" << myphoton->superClusterAt(i)->Pt() << " of type " << myphoton->superClusterAt(i)->type() << ": " << myphoton->superClusterAt(i)->typeName() << endl;
         }
      }
      
      if(doElectron && doCluster)
      {
         cout << endl << "Electron list..." << endl;
         TRootElectron* myelectron;
         for (int ielectron=0; ielectron< electrons->GetEntriesFast(); ielectron++)
         {
            myelectron = (TRootElectron*) electrons->At(ielectron);
            cout << endl << "   [" << ielectron << "]"; myelectron->Print(); cout << endl;
            // Look for the default supercluster associated to the photon
            // (Default SC collection for electron producer defined in RecoEgamma/EgammaElectronProducers/python/pixelMatchGsfElectrons_cfi )
            if( myelectron->superCluster() !=0 ) cout << "            Associated by default to to SC[" << myelectron->scIndex() <<"] with Et=" << myelectron->superCluster()->Pt() << " of type " << myelectron->superCluster()->type() << ": " << myelectron->superCluster()->typeName() << endl;
            // Or look for a particular type of supercluster associated to the photon (Type definition in TRootSuperCluster.h)
            if( myelectron->superClusterOfType(210) !=0 ) cout << "            Associated to Hybrid SC[" << myelectron->scIndexOfType(210) <<"] with Et=" << myelectron->superClusterOfType(210)->Pt() << endl;
            if( myelectron->superClusterOfType(211) !=0 ) cout << "            Associated to Corrected Hybrid SC[" << myelectron->scIndexOfType(211) <<"] with Et=" << myelectron->superClusterOfType(211)->Pt() << endl;
            if( myelectron->superClusterOfType(320) !=0 ) cout << "            Associated to Multi5x5 SC[" << myelectron->scIndexOfType(320) <<"] with Et=" << myelectron->superClusterOfType(320)->Pt() << endl;
            if( myelectron->superClusterOfType(322) !=0 ) cout << "            Associated to Corrected Multi5x5 with preshower SC[" << myelectron->scIndexOfType(322) <<"] with Et=" << myelectron->superClusterOfType(322)->Pt() << endl;
            if( myelectron->superClusterOfType(323) !=0 ) cout << "            Associated to Multi5x5 with preshower SC[" << myelectron->scIndexOfType(323) <<"] with Et=" << myelectron->superClusterOfType(323)->Pt() << endl;
            // Or loop over all superclusters associated to the photon
            for (unsigned int i=0; i<myelectron->nSuperClusters(); ++i)
               if( myelectron->superClusterAt(i) !=0 )  cout << "            " << (i+1) << "th supercluster associated to photon is SC[" << myelectron->scIndexAt(i) <<"] Et=" << myelectron->superClusterAt(i)->Pt() << " of type " << myelectron->superClusterAt(i)->type() << ": " << myelectron->superClusterAt(i)->typeName() << endl;
         }
      }
      
      if(doCluster)
      {
         cout << endl << "SuperClusters list..." << endl;
         TRootSuperCluster* mySC;
         for (int isc=0; isc< superClusters->GetEntriesFast(); isc++)
         {
            mySC = (TRootSuperCluster*) superClusters->At(isc);
            cout << "  SC[" << isc << "] of type " << mySC->type() << ": "<< mySC->typeName() << " with Et=" << mySC->Pt();
            if (mySC->isPhoton() )
            {
               TRootPhoton* phot = mySC->photon();
               cout << " is associated to TRootPhoton[" << mySC->photonIndex() << "] Et=" << phot->Et();
            }
            else
            {
               cout << " is not a photon";
            }
            if (mySC->isElectron() )
            {
               TRootElectron* ele = mySC->electron();
               cout << " and is associated to TRootElectron[" << mySC->electronIndex() << "] Et=" << ele->Et();
            }
            else
            {
               cout << " and is not a electron";
            }
            cout << endl << "            and is composed of";
            std::vector<Int_t> clustersIndex = mySC->subBasicClusterIndexVector();
            for (iclus=0; iclus<clustersIndex.size(); iclus++)
            {
               if ( clustersIndex[iclus]==mySC->seedBasicClusterIndex() ) cout << " seedBC[" << clustersIndex[iclus] << "] (Et=" <<  mySC->seedBasicCluster()->Pt() << ")";
               else cout << " BC[" << clustersIndex[iclus] << "] (Et=" <<  mySC->subBasicClusterAt(iclus)->Pt() << ")";
            }
            cout << endl;
         }
      }
      
      
   } // fin boucle sur evts
   
}
