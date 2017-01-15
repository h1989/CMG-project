//
//

#ifndef PhysicsTools_PatUtils_LeptonJetIsolationAngle_h
#define PhysicsTools_PatUtils_LeptonJetIsolationAngle_h

/**
  \class    pat::LeptonJetIsolationAngle LeptonJetIsolationAngle.h "PhysicsTools/PatUtils/interface/LeptonJetIsolationAngle.h"
  \brief    Calculates a lepton's jet isolation angle

   LeptonJetIsolationAngle calculates an isolation angle w.r.t. a list of
   given jets as the minimal angle to a jet in Euclidean space, as defined in
   CMS Note 2006/024

  \author   Steven Lowette
*/


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "CLHEP/Vector/LorentzVector.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "PhysicsTools/PatUtils/interface/TrackerIsolationPt.h"


namespace pat {


  class LeptonJetIsolationAngle {

    public:

      LeptonJetIsolationAngle(edm::ConsumesCollector && iC);
      ~LeptonJetIsolationAngle();

      float calculate(const Electron & anElectron, const edm::Handle<edm::View<reco::Track> > & trackHandle, const edm::Event & iEvent);
      float calculate(const Muon & aMuon, const edm::Handle<edm::View<reco::Track> > & trackHandle, const edm::Event & iEvent);

    private:

      float calculate(const CLHEP::HepLorentzVector & aLepton, const edm::Handle<edm::View<reco::Track> > & trackHandle, const edm::Event & iEvent);
      float spaceAngle(const CLHEP::HepLorentzVector & aLepton, const reco::CaloJet & aJet);

    private:

      TrackerIsolationPt trkIsolator_;
      edm::EDGetTokenT<reco::CaloJetCollection>         jetToken_;
      edm::EDGetTokenT<std::vector<reco::GsfElectron> > electronsToken_;

  };


}

#endif

