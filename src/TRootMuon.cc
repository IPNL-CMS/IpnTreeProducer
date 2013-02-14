#include "../interface/TRootMuon.h"

ClassImp(TRootMuon)


Bool_t TRootMuon::isTightMuonPerso() const
{
   if(!isPFMuon_ || !isGlobalMuon_ ) return false;
   
   bool muID =  normalizedChi2GlobalTrack_ < 10. && numberOfValidMuonHitsInGlobalTrack_ > 0 && numberOfMatchedStations_ > 1;
   bool hits = (pixelLayersWithMeasurementInInnerTrack_+stripLayersWithMeasurementInInnerTrack_) > 5 && numberOfValidPixelHitsInInnerTrack_ > 0; 
   bool ip = bestTrackDxy_ < 0.2 && bestTrackDz_ < 0.5;
   
   return muID && hits && ip;
}
