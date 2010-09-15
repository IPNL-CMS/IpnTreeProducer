#include "../interface/L1TriggerAnalyzer.h"

using namespace std;

L1TriggerAnalyzer::L1TriggerAnalyzer(const edm::ParameterSet& producersNames, int verbosity) :
verbosity_(verbosity)
,nEvents_(0)
,nL1Accept_(0)
,physicsL1Names_()
,physicsL1PrescaleFactors_()
,physicsL1Mask_()
,physicsL1MaskVeto_()
,nPhysicsL1Accept_(0)
,physicsL1CumulatedPass_(0)
,technicalL1Names_()
,technicalL1PrescaleFactors_()
,technicalL1Mask_()
,technicalL1MaskVeto_()
,nTechnicalL1Accept_(0)
,technicalL1CumulatedPass_(0)
{
	l1Producer_ = producersNames.getParameter<edm::InputTag> ("l1Producer");
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}


bool L1TriggerAnalyzer::init(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent)
{

	// Index of the physics DAQ partition
	int physicsDaqPartition = 0;

	// L1 GT Menu (Physics and Technical)
	edm::ESHandle<L1GtTriggerMenu> l1GtMenu;
	iSetup.get<L1GtTriggerMenuRcd>().get(l1GtMenu) ;
	const L1GtTriggerMenu* menu = l1GtMenu.product();
	(const_cast<L1GtTriggerMenu*>(l1GtMenu.product()))->buildGtConditionMap();

	//int printVerbosity = 2;
	//l1GtMenu->print(std::cout, printVerbosity);
	//std::cout << std::flush << std::endl;
	
	if(verbosity_>0)
	{
		cout << endl << "L1TriggerAnalyzer-Init ---------------------------- L1 Trigger Menu ----------------------------------\n";
		cout << "L1TriggerAnalyzer-Init " << left << setw(40) << "  L1 Trigger Menu Interface:" << left << setw(50) << l1GtMenu->gtTriggerMenuInterface() << endl;
		cout << "L1TriggerAnalyzer-Init " << left << setw(40) << "  L1 Trigger Menu Name:" << left << setw(50) << l1GtMenu->gtTriggerMenuName() << endl;
		cout << "L1TriggerAnalyzer-Init " << left << setw(40) << "  L1 Trigger Menu Implementation:" << left << setw(50) << l1GtMenu->gtTriggerMenuImplementation() << endl;
		cout << "L1TriggerAnalyzer-Init " << left << setw(40) << "  Associated L1 scale DB key:" << left << setw(50) << l1GtMenu->gtScaleDbKey() << endl << endl;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Get Physics Algos
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	// L1 GT prescale factors for physics triggers
	int indexPfSet = 0;	  // only the prescale factors from set index zero are save

	edm::ESHandle< L1GtPrescaleFactors> l1GtPfAlgo;
	iSetup.get< L1GtPrescaleFactorsAlgoTrigRcd>().get(l1GtPfAlgo);
	std::vector<int> transientPhysicsL1PrescaleFactors =(l1GtPfAlgo->gtPrescaleFactors()).at(indexPfSet);
	physicsL1CumulatedPass_.resize( transientPhysicsL1PrescaleFactors.size(), 0 );

	// L1 GT trigger masks for physics triggers
	edm::ESHandle< L1GtTriggerMask> l1GtTmAlgo;
	iSetup.get< L1GtTriggerMaskAlgoTrigRcd>().get(l1GtTmAlgo);
	std::vector<unsigned int> transientPhysicsL1Mask= l1GtTmAlgo->gtTriggerMask();

	// L1 GT trigger veto masks for physics triggers
	edm::ESHandle< L1GtTriggerMask> l1GtTmVetoAlgo;
	iSetup.get< L1GtTriggerMaskVetoAlgoTrigRcd>().get(l1GtTmVetoAlgo);
	std::vector<unsigned int> transientPhysicsL1MaskVeto = l1GtTmVetoAlgo->gtTriggerMask();

	// use a map <int, L1GtAlgorithm> to sort the physics L1 algorithms after bit number
	std::map<int, const L1GtAlgorithm*> algoBitToAlgo;
	for (CItAlgo algo = (menu->gtAlgorithmMap()).begin(); algo!=(menu->gtAlgorithmMap()).end(); ++algo)
	{
		int bitNumber = (algo->second).algoBitNumber();
		algoBitToAlgo[bitNumber] = &(algo->second);
	}

	// Save algorithms configurations
	for (std::map<int, const L1GtAlgorithm*>::const_iterator itBit = algoBitToAlgo.begin(); itBit != algoBitToAlgo.end(); itBit++)
	{
		int bitNumber = itBit->first;
		physicsL1Names_[bitNumber] = (itBit->second)->algoName();
		physicsL1PrescaleFactors_[bitNumber] =  transientPhysicsL1PrescaleFactors.at(bitNumber);
		physicsL1Mask_[bitNumber] =  (transientPhysicsL1Mask.at(bitNumber)) & (1 << physicsDaqPartition);
		physicsL1MaskVeto_[bitNumber] =  (transientPhysicsL1MaskVeto.at(bitNumber)) & (1 << physicsDaqPartition);
	}

	// Print L1 Physics trigger paths
	if(verbosity_>0)
	{
		cout << endl << "L1TriggerAnalyzer-Init ---------------------------- Physics L1 Menu ----------------------------------\n";
		cout << "L1TriggerAnalyzer-Init "
		<< right << setw(4) << "Bit#" << " "
		<<  left << setw(40) << "Name" << " "
		<< right << setw(10) << "Prescale" << " "
		<< right << setw(10) << "Mask" << " "
		<< right << setw(10) << "Veto" << "\n";
		for (std::map<int, std::string>::const_iterator itBit = physicsL1Names_.begin(); itBit != physicsL1Names_.end(); itBit++)
		{
			int bitNumber = itBit->first;
			cout << "L1TriggerAnalyzer-Init "
			<< right << setw(4) << itBit->first << " "
			<<  left << setw(40) << itBit->second << " "
			<< right << setw(10) << physicsL1PrescaleFactors_.find(bitNumber)->second << " "
			<< right << setw(10) << physicsL1Mask_.find(bitNumber)->second << " "
			<< right << setw(10) << physicsL1MaskVeto_.find(bitNumber)->second << "\n";
		}
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Get Technical triggers
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	// L1 GT prescale factors for technical triggers
	indexPfSet = 0;  // only the prescale factors from set index zero are save
	edm::ESHandle< L1GtPrescaleFactors> l1GtPfTech;
	iSetup.get< L1GtPrescaleFactorsTechTrigRcd>().get(l1GtPfTech);
	std::vector<int> transientTechnicalL1PrescaleFactors =(l1GtPfTech->gtPrescaleFactors()).at(indexPfSet);
	technicalL1CumulatedPass_.resize( transientTechnicalL1PrescaleFactors.size(), 0 );

	// L1 GT trigger masks for technical triggers
	edm::ESHandle< L1GtTriggerMask> l1GtTmTech;
	iSetup.get< L1GtTriggerMaskTechTrigRcd>().get(l1GtTmTech);
	std::vector<unsigned int> transientTechnicalL1Mask = l1GtTmTech->gtTriggerMask();

	// L1 GT trigger veto masks for technical triggers
	edm::ESHandle< L1GtTriggerMask> l1GtTmVetoTech;
	iSetup.get< L1GtTriggerMaskVetoTechTrigRcd>().get(l1GtTmVetoTech);
	std::vector<unsigned int> transientTechnicalL1MaskVeto = l1GtTmVetoTech->gtTriggerMask();

	// use a map <int, L1GtAlgorithm> to sort the technical L1 algorithms after bit number
	std::map<int, const L1GtAlgorithm*> techBitToAlgo;
	for (CItAlgo algo = (menu->gtTechnicalTriggerMap()).begin(); algo!=(menu->gtTechnicalTriggerMap()).end(); ++algo)
	{
		int bitNumber = (algo->second).algoBitNumber();
		techBitToAlgo[bitNumber] = &(algo->second);
	}

	// Save algorithms configurations
	for (std::map<int, const L1GtAlgorithm*>::const_iterator itBit = techBitToAlgo.begin(); itBit != techBitToAlgo.end(); itBit++)
	{
		int bitNumber = itBit->first;
		technicalL1Names_[bitNumber] = (itBit->second)->algoName();
		technicalL1PrescaleFactors_[bitNumber] =  transientTechnicalL1PrescaleFactors.at(bitNumber);
		technicalL1Mask_[bitNumber] =  (transientTechnicalL1Mask.at(bitNumber)) & (1 << physicsDaqPartition);
		technicalL1MaskVeto_[bitNumber] =  (transientTechnicalL1MaskVeto.at(bitNumber)) & (1 << physicsDaqPartition);
	}

	// Print L1 Technical trigger paths
	if(verbosity_>0)
	{
		cout << endl << "L1TriggerAnalyzer-Init --------------------------- Technical L1 Menu ---------------------------------\n";
		cout << "L1TriggerAnalyzer-Init "
		<< right << setw(4) << "Bit#" << " "
		<<   left << setw(40) << "Name" << " "
		<< right << setw(10) << "Prescale" << " "
		<< right << setw(10) << "Mask" << " "
		<< right << setw(10) << "Veto" << "\n";
		for (std::map<int, std::string>::const_iterator itBit = technicalL1Names_.begin(); itBit != technicalL1Names_.end(); itBit++)
		{
			int bitNumber = itBit->first;
			cout << "L1TriggerAnalyzer-Init "
			<< right << setw(4) << itBit->first << " "
			<<  left << setw(40) << itBit->second << " "
			<< right << setw(10) << technicalL1PrescaleFactors_.find(bitNumber)->second << " "
			<< right << setw(10) << technicalL1Mask_.find(bitNumber)->second << " "
			<< right << setw(10) << technicalL1MaskVeto_.find(bitNumber)->second << "\n";
		}
	}

   return true;
}


bool L1TriggerAnalyzer::process(const edm::Event& iEvent, TRootEvent* rootEvent)
{

	edm::Handle< L1GlobalTriggerReadoutRecord > gtReadoutRecord;
	iEvent.getByLabel( l1Producer_, gtReadoutRecord);

	nEvents_++;

	// Physics Decision word before mask
	std::vector<Bool_t> physicsL1Decision = gtReadoutRecord->decisionWord();

	if (physicsL1CumulatedPass_.size() != physicsL1Decision.size())
	{
		cout << "  ##### ERROR IN  L1TriggerAnalyzer::process =>Number of  Physics L1 Paths has changed #####"<<endl;
		return false;
	}
	
	bool passPhysicsL1 = false;
	for (unsigned int ibit = 0; ibit!=physicsL1Decision.size(); ibit++)
	{
		//cout << " physicsL1Decision.at(" << ibit << ")=" <<  physicsL1Decision.at(ibit) << endl;;
		if(physicsL1Decision.at(ibit))
		{
			passPhysicsL1 = true;
			physicsL1CumulatedPass_[ibit] ++;
		}
	}
	if(passPhysicsL1) nPhysicsL1Accept_++; 
	rootEvent->setPhysicsL1Accept(physicsL1Decision);
	
	
	// Technical Decision word before mask
	std::vector<Bool_t> technicalL1Decision = gtReadoutRecord->technicalTriggerWord();

	if (technicalL1CumulatedPass_.size() != technicalL1Decision.size())
	{
		cout << "  ##### ERROR IN  L1TriggerAnalyzer::process =>Number of  Technical L1 Paths has changed #####"<<endl;
		return false;
	}
	
	bool passTechnicalL1 = false;
	for (unsigned int ibit = 0; ibit!=technicalL1Decision.size(); ibit++)
	{
		//cout << " technicalL1Decision.at(" << ibit << ")=" <<  technicalL1Decision.at(ibit) << endl;
		if(technicalL1Decision.at(ibit))
		{
			passTechnicalL1 = true;
			technicalL1CumulatedPass_[ibit] ++;
		}
	}
	if(passTechnicalL1) nTechnicalL1Accept_++;
	rootEvent->setTechnicalL1Accept(technicalL1Decision);
	
	if(passPhysicsL1 || passTechnicalL1)
	{
		nL1Accept_++;
		rootEvent->setGlobalL1(true);
	}
	
	return true;
}


void L1TriggerAnalyzer::printSummary()
{

	// final printout of accumulated statistics

   cout << dec << endl;
	cout << endl << "L1TriggerAnalyzer-Summary ------------------------------------ Event  Summary ------------------------------------------\n";
	cout << "L1TriggerAnalyzer-Summary"
   << "   Events total = " << nEvents_
	<< "   L1Pass = " << nL1Accept_
	<< "   physicsL1Pass = " << nPhysicsL1Accept_
	<< "   technicalL1Pass = " << nTechnicalL1Accept_
	<< "\n";

	cout << endl << "L1TriggerAnalyzer-Summary ------------------------------------ Physics L1 Menu -----------------------------------------\n";
	cout << "L1TriggerAnalyzer-Summary "
	<< right << setw(4) << "Bit#"
	<<  left << setw(40) << "Name"
	<< right << setw(10) << "Prescale"
	<< right << setw(10) << "Mask"
	<< right << setw(10) << "Veto"
	<< right << setw(10) << "Pass"
	<< right << setw(10) << "Eff(%)"
	<< "\n";
	for (std::map<int, std::string>::const_iterator itBit = physicsL1Names_.begin(); itBit != physicsL1Names_.end(); itBit++)
	{
		int bitNumber = itBit->first;
		
		float efficiency = -1;
		if (nEvents_>0) efficiency = 100*float(physicsL1Pass(bitNumber)) /float( nEvents_);
		cout << "L1TriggerAnalyzer-Summary "
		<< right << setw(4) << itBit->first
		<<  left << setw(40) << itBit->second
		<< right << setw(10) << physicsL1PrescaleFactors(bitNumber)
		<< right << setw(10) << physicsL1Mask(bitNumber)
		<< right << setw(10) << physicsL1MaskVeto(bitNumber)
		<< right << setw(10) << physicsL1Pass(bitNumber)
		<< right << setw(10) << setprecision(4) << efficiency
		<< "\n";
	}
	
	cout << endl << "L1TriggerAnalyzer-Summary ----------------------------------- Technical L1 Menu ----------------------------------------\n";
	cout << "L1TriggerAnalyzer-Summary "
	<< right << setw(4) << "Bit#"
	<<  left << setw(40) << "Name"
	<< right << setw(10) << "Prescale"
	<< right << setw(10) << "Mask"
	<< right << setw(10) << "Veto"
	<< right << setw(10) << "Pass"
	<< right << setw(10) << "Eff(%)"
	<< "\n";
	for (std::map<int, std::string>::const_iterator itBit = technicalL1Names_.begin(); itBit != technicalL1Names_.end(); itBit++)
	{
		int bitNumber = itBit->first;
		
		float efficiency = -1;
		if (nEvents_>0) efficiency = 100*float(technicalL1Pass(bitNumber)) /float( nEvents_);
		cout << "L1TriggerAnalyzer-Summary "
		<< right << setw(4) << itBit->first
		<<  left << setw(40) << itBit->second
		<< right << setw(10) << technicalL1PrescaleFactors(bitNumber)
		<< right << setw(10) << technicalL1Mask(bitNumber)
		<< right << setw(10) << technicalL1MaskVeto(bitNumber)
		<< right << setw(10) << technicalL1Pass(bitNumber)
		<< right << setw(10) << setprecision(4) << efficiency
		<< "\n";
	}
	
	cout << endl;
   cout << "L1TriggerAnalyzer-Summary end!" << endl;
   cout << endl;

   return;
}

void L1TriggerAnalyzer::copySummary(TRootRun* runInfos)
{
	
   if(verbosity_>4) cout << "   Copying L1 Trigger Summary table in TRootRun" << endl;
	
   runInfos->setNL1Events(nEvents_) ;
	runInfos->setNL1Accept(nL1Accept_) ;
	runInfos->setNPhysicsL1Accept(nPhysicsL1Accept_) ;
	runInfos->setNTechnicalL1Accept(nTechnicalL1Accept_) ;
	
	runInfos->setPhysicsL1Names(physicsL1Names_) ;
	runInfos->setPhysicsL1PrescaleFactors(physicsL1PrescaleFactors_) ;
	runInfos->setPhysicsL1Mask(physicsL1Mask_) ;
	runInfos->setPhysicsL1MaskVeto(physicsL1MaskVeto_) ;
	runInfos->setPhysicsL1CumulatedPass(physicsL1CumulatedPass_) ;

	runInfos->setTechnicalL1Names(technicalL1Names_) ;
	runInfos->setTechnicalL1PrescaleFactors(technicalL1PrescaleFactors_) ;
	runInfos->setTechnicalL1Mask(technicalL1Mask_) ;
	runInfos->setTechnicalL1MaskVeto(technicalL1MaskVeto_) ;
	runInfos->setTechnicalL1CumulatedPass(technicalL1CumulatedPass_) ;
	
}
