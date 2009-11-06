#include "../interface/ParticleTreeDrawer.h"

using namespace std;
using namespace edm;
using namespace reco;
//using namespace HepMC;


ParticleTreeDrawer::ParticleTreeDrawer(const edm::ParameterSet & config, const edm::ParameterSet & producersNames) :
   allowMissingCollection_(producersNames.getUntrackedParameter<bool>("allowMissingCollection", false) ),
   src_( producersNames.getParameter<InputTag>( "genParticlesProducer" ) ),
   printP4_( config.getUntrackedParameter<bool>( "mcTreePrintP4", false ) ),
   printPtEtaPhi_( config.getUntrackedParameter<bool>( "mcTreePrintPtEtaPhi", false ) ),
   printVertex_( config.getUntrackedParameter<bool>( "mcTreePrintVertex", false ) ),
   printStatus_( config.getUntrackedParameter<bool>( "mcTreePrintStatus", false ) ),
   printIndex_( config.getUntrackedParameter<bool>( "mcTreePrintIndex", false ) ),
   status_( config.getUntrackedParameter<vint>( "mcTreeStatus", vint() ) )
{
}


bool ParticleTreeDrawer::accept( const reco::Candidate & c ) const
{
   if ( status_.size() == 0 ) return true;
   return find( status_.begin(), status_.end(), c.status() ) != status_.end();
}


bool ParticleTreeDrawer::hasValidDaughters( const reco::Candidate & c ) const
{
   size_t ndau = c.numberOfDaughters();
   for( size_t i = 0; i < ndau; ++ i )
   {
      if ( accept( * c.daughter( i ) ) ) return true;
   }
   return false;
}


bool ParticleTreeDrawer::analyze( const Event & event, const EventSetup & es )
{
   try
   {
      es.getData( pdt_ );
      edm::Handle<View<Candidate> > particles;
      event.getByLabel( src_, particles );
      cands_.clear();
      for( View<Candidate>::const_iterator p = particles->begin(); p != particles->end(); ++ p )
      {
         cands_.push_back( & * p );
      }
      for( View<Candidate>::const_iterator p = particles->begin(); p != particles->end(); ++ p )
      {
         if ( accept( * p ) )
         {
            if ( p->mother() == 0 )
            {
               cout << "-- decay tree: --" << endl;
               printDecay( * p, "" );
            }
         }
      }
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  ParticleTreeDrawer::analyze => No genParticles #####"<<endl;
         throw exception;
      }
      return false;
   }
   
   return true;
}


void ParticleTreeDrawer::printInfo( const Candidate & c ) const
{
   if ( printP4_ ) cout << " (" << c.px() << ", " << c.py() << ", " << c.pz() << "; " << c.energy() << ")";
   if ( printPtEtaPhi_ ) cout << " [" << c.pt() << ": " << c.eta() << ", " << c.phi() << "]";
   if ( printVertex_ ) cout << " {" << c.vx() << ", " << c.vy() << ", " << c.vz() << "}";
   if ( printStatus_ ) cout << "{status: " << c.status() << "}";
   if ( printIndex_ ) {
      int idx = -1;
      vector<const Candidate *>::const_iterator found = find( cands_.begin(), cands_.end(), & c );
      if ( found != cands_.end() )
      {
         idx = found - cands_.begin();
         cout << " <idx: " << idx << ">";
      }
   }
}


void ParticleTreeDrawer::printDecay( const Candidate & c, const string & pre ) const
{
   int id = c.pdgId();
   const ParticleData * pd = pdt_->particle( id );
   cout << (pd != 0? pd->name():"???");
   printInfo( c );
   cout << endl;
   
   size_t ndau = c.numberOfDaughters(), validDau = 0;
   for( size_t i = 0; i < ndau; ++ i )
   {
      if ( accept( * c.daughter( i ) ) ) ++ validDau;
   }
   if ( validDau == 0 ) return;
   
   bool lastLevel = true;
   for( size_t i = 0; i < ndau; ++ i )
   {
      if ( hasValidDaughters( * c.daughter( i ) ) )
      {
         lastLevel = false;
         break;
      }
   }
   
   if ( lastLevel )
   {
      cout << pre << "+-> ";
      size_t vd = 0;
      for( size_t i = 0; i < ndau; ++ i )
      {
         const Candidate * d = c.daughter( i );
         if ( accept( * d ) )
         {
            const ParticleData * pd = pdt_->particle( d->pdgId() );
            cout << (pd != 0? pd->name():"???") << endl;
            printInfo( * d );
            if ( vd != validDau - 1 ) cout << " ";
            vd ++;
         }
      }
      cout << endl;
      return;
   }
   
   for( size_t i = 0; i < ndau; ++i )
   {
      const Candidate * d = c.daughter( i );
      assert( d != 0 );
      if ( accept( * d ) )
      {
         cout << pre << "+-> ";
         string prepre( pre );
         if ( i == ndau - 1 ) prepre += "    ";
         else prepre += "|   ";
         printDecay( * d, prepre );
      }
   }
}
