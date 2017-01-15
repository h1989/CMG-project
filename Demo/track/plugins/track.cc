// -*- C++ -*-
//
// Package:    Demo/track
// Class:      track
// 
/**\class track track.cc Demo/track/plugins/track.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Hadi Mehrabpour
//         Created:  Sat, 08 Oct 2016 11:28:23 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include <TH1.h>
#include <TFile.h>
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class track : public edm::EDAnalyzer {
   public:
      explicit track(const edm::ParameterSet&);
      ~track();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
edm::InputTag trackTags_; //used to select what tracks to read from configuration file
  TFile * file;
  TH1F * histo;
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
track::track(const edm::ParameterSet& iConfig)
:trackTags_(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))
{
   //now do what ever initialization is needed
   usesResource("TFileService");

}


track::~track()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
track::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using reco::TrackCollection;

/*#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
*/
Handle<TrackCollection> tracks;
  iEvent.getByLabel(trackTags_,tracks);
  for(TrackCollection::const_iterator itTrack = tracks->begin();
      itTrack != tracks->end();                      
      ++itTrack) {
    histo->Fill(itTrack->pt());
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
track::beginJob()
{
 file = new TFile("outfile.root","recreate"); 
 const bool oldAddDir = TH1::AddDirectoryStatus(); 
 TH1::AddDirectory(true); 
 histo = new TH1F("pt","pt",1000,0,100); 
 TH1::AddDirectory(oldAddDir); 
}

// ------------ method called once each job just after ending the event loop  ------------
void 
track::endJob() 
{
 file->Write(); 
 file->Close();
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
track::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(track);
