#include "../interface/TRootSignalEvent.h"

ClassImp(TRootSignalEvent)


TRootSignalEvent::TRootSignalEvent() : nZ_(0), nMuplus_(0), nMuminus_(0), nFSR_(0), nISR_(0)
{
	//cout << "Constructor TRootSignalEvent" << endl;
	bosonZ_ = 0;
	muplus_ = 0;
	muminus_ = 0;
	photonFSR_ = new TObjArray();
	photonISR_ = new TObjArray();
}

TRootSignalEvent::~TRootSignalEvent()
{
	//cout << "Destructor TRootSignalEvent" << endl;
	if (bosonZ_) delete bosonZ_;
	if (muminus_) delete muminus_;
	if (muplus_) delete muplus_;
	photonFSR_->Delete();
	delete photonFSR_;
	photonISR_->Delete();
	delete photonISR_;
}


void TRootSignalEvent::addBosonZ(TRootParticle* part)
{
	if (nZ_>0)
	{
		cout << "*** WARNING TRootSignalEvent *** More than one Z boson has been found" << endl;
		delete part;
	}
	else
	{
		bosonZ_ = part;
	}
	nZ_++;
}

void TRootSignalEvent::addMuplus(TRootParticle* part)
{
	if (nMuplus_>0)
	{
		cout << "*** WARNING TRootSignalEvent *** More than one mu+ coming from Z boson has been found" << endl;
		delete part;
	}
	else
	{
		muplus_ = part;
	}
	nMuplus_++;
}

void TRootSignalEvent::addMuminus(TRootParticle* part)
{
	if (nMuminus_>0)
	{
		cout << "*** WARNING TRootSignalEvent *** More than one mu- coming from Z boson has been found" << endl;
		delete part;
	}
	else
	{
		muminus_ = part;
	}
	nMuminus_++;
}

void TRootSignalEvent::addFSR(TRootParticle* part)
{
	photonFSR_->AddLast(part);
	nFSR_++;
}


void TRootSignalEvent::addISR(TRootParticle* part)
{
	photonISR_->AddLast(part);
	nISR_++;
}


TRootParticle* TRootSignalEvent::photonFSR(Int_t iFSR)
{
	if (iFSR<nFSR_)
	{
		return (TRootParticle*)(photonFSR_->At(iFSR));
	}
	else
	{
		cout << "*** ERROR in TRootSignalEvent::photonFSR *** iFSR >= nFSR_" << endl;
		return 0;
	}	
}

TRootParticle* TRootSignalEvent::photonISR(Int_t iISR)
{
	if (iISR<nISR_)
	{
		return (TRootParticle*)(photonISR_->At(iISR));
	}
	else
	{
		cout << "*** ERROR in TRootSignalEvent::photonISR *** iISR >= nISR_" << endl;
		return 0;
	}
}

