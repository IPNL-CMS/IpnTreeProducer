#include "../interface/AmbiguitySolver.h"

using namespace std;

AmbiguitySolver::AmbiguitySolver(const edm::ParameterSet& config, int verbosity):verbosity_(verbosity)
{
   //doPhotonMC_ = config.getUntrackedParameter<bool>("doPhotonMC", false);
}


AmbiguitySolver::~AmbiguitySolver()
{
}


void AmbiguitySolver::processElectronsPhotons(TClonesArray* superClusters, TClonesArray* electrons, TClonesArray* photons)
{
   // Mark photon and electron as duplicated if they share the same supercluster
   for (int isc=0; isc<superClusters->GetEntriesFast(); isc++)
   {
      TRootSuperCluster* mySC = (TRootSuperCluster*) superClusters->At(isc);
      if(verbosity_>4) cout << "SC[" << isc << "] isPhoton=" << mySC->isPhoton() << " isElectron=" << mySC->isElectron() << endl;
      if ( mySC->isPhoton() && mySC->isElectron() )
      {
         TRootPhoton* photon = mySC->photon();
         TRootElectron* electron = mySC->electron();
         //cout << " is associated to photon Et=" << photon->Et() << endl;
         //cout << " is associated to electron Et" << electron->Et() << endl;
         photon->setIsAlsoElectron(true);
         electron->setIsAlsoPhoton(true);
      }
   }

   // TODO - Code to remove the ambiguity goes here....
   // First, remove photon with pixel hits ?
   
}
