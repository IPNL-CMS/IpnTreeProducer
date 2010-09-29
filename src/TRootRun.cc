#include "../interface/TRootRun.h"

ClassImp(TRootRun)

void TRootRun::printL1Summary()
{
	cout << dec << endl;
	cout << endl << "L1TriggerAnalyzer-Summary ------------------------------------ Event  Summary ------------------------------------------\n";
	cout << "L1TriggerAnalyzer-Summary"
	<< "   Events total = " << nL1Events_
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
		if (nL1Events_>0) efficiency = 100*float(physicsL1Pass(bitNumber)) /float( nL1Events_);
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
		if (nL1Events_>0) efficiency = 100*float(technicalL1Pass(bitNumber)) /float( nL1Events_);
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
}


void TRootRun::printHLTSummary()
{
	const unsigned int n(hltNames_.size());
	
	cout << dec << endl;
	cout << "HLTAnalyzer-Summary " << "---------- Event  Summary ------------\n";
   cout << "HLTAnalyzer-Summary Table name:  " << hltTableName_ << endl;
   cout << "HLTAnalyzer-Summary"
	<< " Events total = " << nHLTEvents_
	<< " wasrun = " << nHLTWasRun_
	<< " passed = " << nHLTAccept_
	<< " errors = " << nHLTErrors_
	<< "\n";
	
   cout << endl;
   cout << "HLTAnalyzer-Summary " << "---------- HLTrig Summary ------------\n";
   cout << "HLTAnalyzer-Summary "
   << right << setw(7) << "HLT #" << " "
   << right << setw(7) << "WasRun" << " "
   << right << setw(7) << "L1S" << " "
   << right << setw(7) << "Pre" << " "
   << right << setw(7) << "HLT" << " "
   << right << setw(9) << "%L1sPre" << " "
   << right << setw(7) << "Errors" << " "
   << "Name" << endl;
   
   for (unsigned int i=0; i!=n; ++i)
   {
      cout << "HLTAnalyzer-Summary "
      << right << setw(7) << i << " "
      << right << setw(7) << hltWasRun_[i] << " "
      << right << setw(7) << hltL1s_[i] << " "
      << right << setw(7) << hltPre_[i] << " "
      << right << setw(7) << hltAccept_[i] << " "
      << right << setw(9) << fixed << setprecision(5)
      << static_cast<float>(100*hltAccept_[i])/static_cast<float>(max(hltPre_[i],1u)) << " "
      << right << setw(7) << hltErrors_[i] << " "
      << hltNames_[i] << endl;
   }
   
   cout << endl;
   cout << "HLTAnalyzer-Summary end!" << endl;
   cout << endl;

   return;
}
