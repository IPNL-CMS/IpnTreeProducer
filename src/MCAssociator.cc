#include "../interface/MCAssociator.h"


MCAssociator::MCAssociator(): verbosity_(0), nMC_(0), mcParticles_(0), genParticles_(), mcParticlesMap_()
{
}


MCAssociator::MCAssociator(const edm::ParameterSet& producersNames, int verbosity) : verbosity_(verbosity), nMC_(0), mcParticles_(0), genParticles_(), mcParticlesMap_()
{
   genParticlesProducer_ = producersNames.getParameter<edm::InputTag>("genParticlesProducer");
}



void MCAssociator::init(const edm::Event& iEvent, TClonesArray* mcParticles)
{
   // FIXME - Protect against no genParticles collection in PoolSource
   iEvent.getByLabel( genParticlesProducer_, genParticles_ );
   
   // fill map<igen,imc> where igen=index in genParticle collection and imc=index in mcParticles TClonesArray
   if(verbosity_>1) cout << endl << "Matching recoParticles to mcParticles... " << endl;
   int igen;
   mcParticles_ = mcParticles;
   nMC_ = mcParticles_->GetEntriesFast();
   for (int imc=0; imc<nMC_; imc++)
   {
      // TODO - remove indexInList in TRootMCParticle
      //igen = ( (TRootParticle*)mcParticles_->At(imc))->genParticleIndex_();
      igen = ( (TRootMCParticle*)mcParticles_->At(imc))->indexInList();
      mcParticlesMap_[igen]=imc;
   }
}


void MCAssociator::matchGenParticlesTo(TClonesArray* recoParticles)
{
   int igen;
   std::map<int,int>::iterator it;
   
   for (int ipart=0; ipart<recoParticles->GetEntriesFast(); ipart++)
   {
      TRootParticle* recoParticle = (TRootParticle*)recoParticles->At(ipart);
      igen = recoParticle->genParticleIndex();
      if(igen<0)
      {
         if(verbosity_>2) cout <<"   "<< recoParticle->typeName() << "[" << ipart << "] not matched (at CMSSW level)" << endl;
         continue;
      }
      
      it=mcParticlesMap_.find(igen);
      if(it==mcParticlesMap_.end())
      {
         if(verbosity_>2) cout <<"   "<< recoParticle->typeName() << "[" << ipart << "] not matched (at TotoAna level)... add new TRootMCParticle..." << endl;
         // if igen not found in mcParticles[], add genParticle in mcParticles[]
         const reco::GenParticle & p = (*genParticles_)[igen];
         //find the mother ID
         Int_t motherID = 0; Int_t grannyID = 0; Int_t oldgrannyID = 0;
         if (p.numberOfMothers() > 0 )
         {
            //sanity check
            const reco::Candidate * mom = p.mother();
            motherID = mom->pdgId();
            if (mom->numberOfMothers() > 0)
            {
               const reco::Candidate * granny = mom->mother();
               grannyID = granny->pdgId();
	       if (granny->numberOfMothers() > 0) oldgrannyID = (granny->mother())->pdgId();
               if ( motherID == p.pdgId() )
               {
                  //check if the particle is "daugther of itself"
                  motherID = granny->pdgId();
                  if (granny->numberOfMothers() > 0) grannyID = (granny->mother())->pdgId();
               }
            }
         }
         
         TRootMCParticle localMCParticle( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, oldgrannyID, 0, 0, 0, 0, igen );
         new( (*mcParticles_)[nMC_] ) TRootMCParticle(localMCParticle);
         recoParticle->setGenParticle( (TObject*)mcParticles_->At(nMC_) );
         if(verbosity_>2) cout <<"      ===> now matched to mcParticle["<< nMC_<<"] "<< localMCParticle << endl;
         nMC_++;
      }
      else
      {
         if(verbosity_>2) cout <<"   "<< ( (TRootParticle*)recoParticles->At(ipart))->typeName() << "[" << ipart << "] matched to mcParticles[" << it->second << "]" << endl;
         recoParticle->setGenParticle( (TObject*)mcParticles_->At(it->second) );
      }
   }
}


void MCAssociator::printParticleAssociation(TClonesArray* recoParticles)
{
   std::map<int,int>::iterator it;
   for (int ipart=0; ipart<recoParticles->GetEntriesFast(); ipart++)
   {
      TRootParticle* localParticle = (TRootParticle*)recoParticles->At(ipart);
      it=mcParticlesMap_.find(localParticle->genParticleIndex());
      int imc = it->second;
      cout << endl <<"                     "<< localParticle->typeName() <<"["<< setw(3) << ipart << "] - Charge=" << setw(2) << localParticle->charge()
      << " (Et,eta,phi)=("<< setw(9) << localParticle->Et() <<","<< setw(9) << localParticle->Eta() <<","<< setw(9) << localParticle->Phi() << ")"
      << " vertex(x,y,z)=("<< setw(11) << localParticle->vx() <<","<< setw(11) << localParticle->vy() <<","<< setw(11) << localParticle->vz() << ")" << endl;
      if(it==mcParticlesMap_.end())
      {
         cout <<"   ===> not matched" << endl;
      } else {
         cout << "   ===> matched to mcParticles[" << setw(3) << imc << "] - Charge=" << setw(2) << localParticle->genParticle()->charge()
         << " (Et,eta,phi)=("<< setw(9) << localParticle->genParticle()->Et() <<","<< setw(9) << localParticle->genParticle()->Eta() <<","<< setw(9) << localParticle->genParticle()->Phi() << ")"
         << " vertex(x,y,z)=("<< setw(11) << localParticle->genParticle()->vx() <<","<< setw(11) << localParticle->genParticle()->vy() <<","<< setw(11) << localParticle->genParticle()->vz() << ")" << endl;
      }
   }
}


void MCAssociator::processGenJets(TClonesArray* genJets, TClonesArray* recoJets)
{
   
   TRootJet* localJet;
   TRootParticle* localGenJet;
   if(verbosity_>1) cout << endl << "Matching genJets to recoJets... " << endl;
   
   Double_t energy;
   map<Double_t,Int_t> genMap;
   map<Double_t,Int_t>::iterator it;
   
   for (int igen=0; igen<genJets->GetEntriesFast(); igen++)
   {
      energy= ((TRootParticle*) genJets->At(igen))->Energy();
      genMap.insert ( pair<Double_t,Int_t>(energy,igen) );
   }
   
   for (int irec=0; irec<recoJets->GetEntriesFast(); irec++)
   {
      localJet = (TRootJet*) recoJets->At(irec);
      energy = localJet->genJetEnergy();
      if(energy<0)
      {
         if(verbosity_>2) cout <<"   "<< "TRootJet[" << irec << "] not matched to GenJet (at CMSSW level)" << endl;
         continue;
      }
      it=genMap.find(energy);
      if(it==genMap.end())
      {
         if(verbosity_>2) cout <<"   "<< "TRootJet[" << irec << "] not matched (at TotoAna level)" << endl;
         // TODO - add missing GenJet
         continue;
      }
      else
      {
         if(verbosity_>2) cout <<"   "<< "TRootJet[" << irec << "] matched to GenJet[" << it->second << "]" << endl;
         localGenJet = (TRootParticle*) genJets->At((*it).second);
         localJet->setGenJetIndex( (*it).second );
         localJet->setGenJet( localGenJet );
         //TODO - Add TRef in GenJet pointing to TRootJet ?
         // localGenJet->setRecoJet( localJet );
      }
   }
   
   genMap.clear();
}


void MCAssociator::printJetAssociation(TClonesArray* recoJets)
{
   std::map<int,int>::iterator it;
   for(int ipart=0; ipart<recoJets->GetEntriesFast(); ipart++)
   {
      
      TRootJet* localJet = (TRootJet*)recoJets->At(ipart);
      it=mcParticlesMap_.find(localJet->genParticleIndex());
      int imc = it->second;
      cout << endl << "                      TRootJet[" << setw(3) << ipart << "] - Charge=" << setw(2) << localJet->charge()
      << " (Et,eta,phi)=("<< setw(9) << localJet->Et() <<","<< setw(9) << localJet->Eta() <<","<< setw(9) << localJet->Phi() << ")"
      << " vertex(x,y,z)=("<< setw(11) << localJet->vx() <<","<< setw(11) << localJet->vy() <<","<< setw(11) << localJet->vz() << ")" << endl;
      
      if( localJet->genJet()!=0 )
      {
         cout << "   ===>      matched to genJet[" << setw(3) << localJet->genJetIndex() << "] - Charge=" << setw(2) << localJet->genJet()->charge()
         << " (Et,eta,phi)=("<< setw(9) << localJet->genJet()->Et() <<","<< setw(9) << localJet->genJet()->Eta() <<","<< setw(9) << localJet->genJet()->Phi() << ")"
         << " vertex(x,y,z)=("<< setw(11) << localJet->genJet()->vx() <<","<< setw(11) << localJet->genJet()->vy() <<","<< setw(11) << localJet->genJet()->vz() << ")" << endl;
      } else {
         cout <<"    ===> not matched to genJet" << endl;
      }
      
      if(it==mcParticlesMap_.end())
      {
         cout <<"    ===> not matched to mcParticles" << endl;
      } else {
         cout << "   ===> matched to mcParticles[" << setw(3) << imc << "] - Charge=" << setw(2) << localJet->genParticle()->charge()
         << " (Et,eta,phi)=("<< setw(9) << localJet->genParticle()->Et() <<","<< setw(9) << localJet->genParticle()->Eta() <<","<< setw(9) << localJet->genParticle()->Phi() << ")"
         << " vertex(x,y,z)=("<< setw(11) << localJet->genParticle()->vx() <<","<< setw(11) << localJet->genParticle()->vy() <<","<< setw(11) << localJet->genParticle()->vz() << ")" << endl;
      }
      
   }
}
