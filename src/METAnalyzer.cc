#include "../interface/METAnalyzer.h"

/*
 * Modification by Stephane -- 22/04/2010
 * - add support for pfMet
 * - pfMET specific variables are not stored (like NeutralEMEt(), ...
 * - when runnning on RECO, only MET 4-vector is calculated
 * - when running on PAT with PF only MET 4-vector is stored
 *   see DataFormats/METReco/interface/PFMET.h
 * This class should be reviewed more seriously
 */

using namespace std;
using namespace reco;
using namespace edm;


METAnalyzer::METAnalyzer(const edm::InputTag& metProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
   dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
   metProducer_ = metProducer;
   useMC_ = myConfig.getUntrackedParameter<bool>("doMETMC");
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}

METAnalyzer::~METAnalyzer()
{
}

bool METAnalyzer::process(const edm::Event& iEvent, TClonesArray* rootMET)
{
   
   unsigned int nMETs=0;
   
   //------------------------------
   // reco:CaloMet or reco::PFMET ?
   //------------------------------
   
   std::string metType = "BASIC";
   if (metProducer_.label()=="corMetGlobalMuons"
      || metProducer_.label()== "met"
      || metProducer_.label()== "metHO"
      || metProducer_.label()== "metNoHF"
      || metProducer_.label()== "metNoHFHO"
      || metProducer_.label()== "metOpt"
      || metProducer_.label()== "metOptHO"
      || metProducer_.label()== "metOptNoHF"
      || metProducer_.label()== "metOptNoHFHO"
   ) metType="CALO";
   
   if ( metProducer_.label()== "pfMet" ) metType="PF";
   
   //----------------
   // try collections
   //----------------
   
   
   //reco:CaloMet
   //------------
   
   edm::Handle < std::vector <reco::CaloMET> > recoMETs;
   if (dataType_=="RECO" && metType=="CALO")
   {
      {
         try
         {
            iEvent.getByLabel(metProducer_, recoMETs);
            nMETs = recoMETs->size();
         }
         catch (cms::Exception& exception)
         {
            if ( !allowMissingCollection_ )
            {
               cout << "  ##### ERROR IN  METAnalyzer::process => reco::CaloMET collection is missing #####"<<endl;
               throw exception;
            }
            if(verbosity_>1) cout <<  "   ===> No reco::CaloMET collection, skip MET info" << endl;
            return false;
         }
      }
   }
   
   
   //reco::PFMET
   //-----------
   
   edm::Handle <std::vector <reco::PFMET> > recoPFMETs;
   if (dataType_=="RECO" && metType=="PF")
   {
      {
         try
         {
            iEvent.getByLabel(metProducer_, recoPFMETs);
            nMETs = recoPFMETs->size();
         }
         catch (cms::Exception& exception)
         {
            if ( !allowMissingCollection_ )
            {
               cout << "  ##### ERROR IN  METAnalyzer::process => reco::PFMET collection is missing #####"<<endl;
               throw exception;
            }
            if(verbosity_>1) cout <<  "   ===> No reco::PFMET collection, skip MET info" << endl;
            return false;
         }
      }
   }
   
   
   //pat::MET
   //--------
   
   edm::Handle < std::vector <pat::MET> > patMETs;
   if( dataType_=="PAT" )
   {
      try
      {
         iEvent.getByLabel(metProducer_, patMETs);
         nMETs = patMETs->size();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  METAnalyzer::process => pat::MET collection is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No pat::MET collection, skip MET info" << endl;
         return false;
      }
   }
   
   if(verbosity_>1) std::cout << "   Number of MET objects = " << nMETs << "   Label: " << metProducer_.label() << "   Instance: " << metProducer_.instance() << std::endl;
   
   
   //----------
   // get infos
   //----------
   
   for (unsigned int j=0; j<nMETs; j++)
   {
      const reco::Candidate* met = 0;
      
      // metType ?
      //----------
      
      if( dataType_=="RECO" && metType=="CALO" ) met = (const reco::Candidate*) ( & ((*recoMETs)[j]) );
      
      if( dataType_=="RECO" && metType=="PF" ) met = (const reco::Candidate*) ( & ((*recoPFMETs)[j]) );
      
      if( dataType_=="PAT" )
      {
         met = (const reco::Candidate*) ( & ((*patMETs)[j]) );
         if( (*patMETs)[j].isCaloMET() ) metType="CALO";
         if( (*patMETs)[j].isRecoMET() ) metType="PF"; // not sure - isRecoMET means pat::MET was NOT made from a reco::CaloMET
      }
      
      TRootMET localMET(
         met->px()
         ,met->py()
         ,met->pz()
         ,met->energy()
         ,met->vx()
         ,met->vy()
         ,met->vz()
      );
      
      // filling infos
      //--------------
      
      //RECO
      if( dataType_=="RECO" )
      {
         const reco::CaloMET *recoMET = dynamic_cast<const reco::CaloMET*>(&*met);
         const reco::PFMET *recoPFMET = dynamic_cast<const reco::PFMET*>(&*met);
         if (metType=="CALO")
         {
            localMET.setCaloMETFraction(
               recoMET->maxEtInEmTowers()
               ,recoMET->maxEtInHadTowers()
               ,recoMET->hadEtInHO()
               ,recoMET->hadEtInHB()
               ,recoMET->hadEtInHF()
               ,recoMET->hadEtInHE()
               ,recoMET->emEtInEB()
               ,recoMET->emEtInEE()
               ,recoMET->emEtInHF()
               ,recoMET->etFractionHadronic()
               ,recoMET->emEtFraction()
               ,recoMET->metSignificance()
               ,recoMET->CaloMETInpHF()
               ,recoMET->CaloMETInmHF()
               ,recoMET->CaloSETInpHF()
               ,recoMET->CaloSETInmHF()
               ,recoMET->CaloMETPhiInpHF()
               ,recoMET->CaloMETPhiInmHF()
            );
            localMET.setSumEt(recoMET->sumEt());
            
         }
         
         if (metType=="PF")
         {
            
            localMET.setHadronicEtFraction(
               recoPFMET->NeutralHadEtFraction()
               ,recoPFMET->NeutralHadEt()
               ,recoPFMET->ChargedHadEtFraction()
               ,recoPFMET->ChargedHadEt()
            );
            localMET.setEMEtFraction(
               recoPFMET->NeutralEMEtFraction()
               ,recoPFMET->NeutralEMEt()
               ,recoPFMET->ChargedEMEtFraction()
               ,recoPFMET->ChargedEMEt()
            );
            localMET.setMuonstFraction(
               recoPFMET->MuonEtFraction()
               ,recoPFMET->MuonEt()
            );
            localMET.setTypesFraction(
               recoPFMET->Type6EtFraction(),
               recoPFMET->Type6Et(),
               recoPFMET->Type7EtFraction(),
               recoPFMET->Type7Et()
            );
            localMET.setSumEt(recoPFMET->sumEt());
         }
      }
      
      //PAT
      if( dataType_=="PAT" )
      {
         // Some specific methods to pat::MET
         const pat::MET *patMET = dynamic_cast<const pat::MET*>(&*met);
         if (metType=="CALO")
         {
            
            localMET.setCaloMETFraction(
               patMET->maxEtInEmTowers()
               ,patMET->maxEtInHadTowers()
               ,patMET->hadEtInHO()
               ,patMET->hadEtInHB()
               ,patMET->hadEtInHF()
               ,patMET->hadEtInHE()
               ,patMET->emEtInEB()
               ,patMET->emEtInEE()
               ,patMET->emEtInHF()
               ,patMET->etFractionHadronic()
               ,patMET->emEtFraction()
               ,patMET->metSignificance()
               ,patMET->CaloMETInpHF()
               ,patMET->CaloMETInmHF()
               ,patMET->CaloSETInpHF()
               ,patMET->CaloSETInmHF()
               ,patMET->CaloMETPhiInpHF()
               ,patMET->CaloMETPhiInmHF()
            );
         }
         //pat::MET::UncorectionType ix;
         //ix = pat::MET::uncorrALL;
         localMET.setCorExALL(patMET->corEx(pat::MET::uncorrALL));
         localMET.setCorExJES(patMET->corEx(pat::MET::uncorrJES));
         localMET.setCorExMUON(patMET->corEx(pat::MET::uncorrMUON));
         
         localMET.setCorEyALL(patMET->corEy(pat::MET::uncorrALL));
         localMET.setCorEyJES(patMET->corEy(pat::MET::uncorrJES));
         localMET.setCorEyMUON(patMET->corEy(pat::MET::uncorrMUON));
         
         localMET.setCorSumEtALL(patMET->corSumEt(pat::MET::uncorrALL));
         localMET.setCorSumEtJES(patMET->corSumEt(pat::MET::uncorrJES));
         localMET.setCorSumEtMUON(patMET->corSumEt(pat::MET::uncorrMUON));
         
         localMET.setUncorrectedPhiALL(patMET->uncorrectedPhi(pat::MET::uncorrALL));
         localMET.setUncorrectedPhiJES(patMET->uncorrectedPhi(pat::MET::uncorrJES));
         localMET.setUncorrectedPhiMUON(patMET->uncorrectedPhi(pat::MET::uncorrMUON));
         
         localMET.setUncorrectedPtALL(patMET->uncorrectedPt(pat::MET::uncorrALL));
         localMET.setUncorrectedPtJES(patMET->uncorrectedPt(pat::MET::uncorrJES));
         localMET.setUncorrectedPtMUON(patMET->uncorrectedPt(pat::MET::uncorrMUON));
         
         localMET.setSumEt(patMET->sumEt());
         
         if(useMC_)
         {
            // MC truth associator index
            if ((patMET->genParticleRef()).isNonnull()) {
               localMET.setGenParticleIndex((patMET->genParticleRef()).index());
            } else {
               localMET.setGenParticleIndex(-1);
            }
         }
      }
      
      new( (*rootMET)[j] ) TRootMET(localMET);
      if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localMET << endl;
      
   }
   
   return true;
}
