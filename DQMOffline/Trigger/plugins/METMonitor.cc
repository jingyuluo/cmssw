#include "DQMOffline/Trigger/plugins/METMonitor.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DQM/TrackingMonitor/interface/GetLumi.h"

#include "CommonTools/TriggerUtils/interface/GenericTriggerEventFlag.h"

#include "DataFormats/Math/interface/deltaPhi.h"

double MAX_PHI = 3.2;
int N_PHI = 64;
const MEbinning phi_binning_{
  N_PHI, -MAX_PHI, MAX_PHI
};
// -----------------------------
//  constructors and destructor
// -----------------------------

METMonitor::METMonitor( const edm::ParameterSet& iConfig ) : 
  folderName_             ( iConfig.getParameter<std::string>("FolderName") )
  , metToken_             ( consumes<reco::PFMETCollection>      (iConfig.getParameter<edm::InputTag>("met")       ) )   
  , jetToken_             ( mayConsume<reco::PFJetCollection>      (iConfig.getParameter<edm::InputTag>("jets")      ) )   
  , eleToken_             ( mayConsume<reco::GsfElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons") ) )   
  , muoToken_             ( mayConsume<reco::MuonCollection>       (iConfig.getParameter<edm::InputTag>("muons")     ) )   
  , vtxToken_             ( mayConsume<reco::VertexCollection>      (iConfig.getParameter<edm::InputTag>("vertices")      ) )
  , met_variable_binning_ ( iConfig.getParameter<edm::ParameterSet>("histoPSet").getParameter<std::vector<double> >("metBinning") )
  , met_binning_          ( getHistoPSet   (iConfig.getParameter<edm::ParameterSet>("histoPSet").getParameter<edm::ParameterSet>   ("metPSet")    ) )
  , ls_binning_           ( getHistoLSPSet (iConfig.getParameter<edm::ParameterSet>("histoPSet").getParameter<edm::ParameterSet>   ("lsPSet")     ) )
  , ht_variable_binning_ ( iConfig.getParameter<edm::ParameterSet>("histoPSet").getParameter<std::vector<double> >("htBinning") )
  , ht_binning_          ( getHistoPSet   (iConfig.getParameter<edm::ParameterSet>("histoPSet").getParameter<edm::ParameterSet>   ("htPSet")    ) )
  , num_genTriggerEventFlag_(new GenericTriggerEventFlag(iConfig.getParameter<edm::ParameterSet>("numGenericTriggerEventPSet"),consumesCollector(), *this))
  , den_genTriggerEventFlag_(new GenericTriggerEventFlag(iConfig.getParameter<edm::ParameterSet>("denGenericTriggerEventPSet"),consumesCollector(), *this))
  , metSelection_ ( iConfig.getParameter<std::string>("metSelection") )
  , jetSelection_ ( iConfig.getParameter<std::string>("jetSelection") )
  , eleSelection_ ( iConfig.getParameter<std::string>("eleSelection") )
  , muoSelection_ ( iConfig.getParameter<std::string>("muoSelection") )
  , jetSelection_HT_ ( iConfig.getParameter<std::string>("jetSelection_HT") )
  , njets_      ( iConfig.getParameter<int>("njets" )      )
  , nelectrons_ ( iConfig.getParameter<int>("nelectrons" ) )
  , nmuons_     ( iConfig.getParameter<int>("nmuons" )     )
{

  htME_.numerator   = nullptr;
  htME_.denominator = nullptr;
  htME_variableBinning_.numerator   = nullptr;
  htME_variableBinning_.denominator = nullptr;
  htVsLS_.numerator   = nullptr;
  htVsLS_.denominator = nullptr;
  deltaphimetj1ME_.numerator   = nullptr;
  deltaphimetj1ME_.denominator = nullptr;
  deltaphij1j2ME_.numerator   = nullptr;
  deltaphij1j2ME_.denominator = nullptr;
  metME_.numerator   = nullptr;
  metME_.denominator = nullptr;
  metME_variableBinning_.numerator   = nullptr;
  metME_variableBinning_.denominator = nullptr;
  metVsLS_.numerator   = nullptr;
  metVsLS_.denominator = nullptr;
  metPhiME_.numerator   = nullptr;
  metPhiME_.denominator = nullptr;
  
}

METMonitor::~METMonitor()
{
  if (num_genTriggerEventFlag_) delete num_genTriggerEventFlag_;
  if (den_genTriggerEventFlag_) delete den_genTriggerEventFlag_;
}

MEbinning METMonitor::getHistoPSet(edm::ParameterSet pset)
{
  return MEbinning{
    pset.getParameter<int32_t>("nbins"),
      pset.getParameter<double>("xmin"),
      pset.getParameter<double>("xmax"),
      };
}

MEbinning METMonitor::getHistoLSPSet(edm::ParameterSet pset)
{
  return MEbinning{
    pset.getParameter<int32_t>("nbins"),
      0.,
      double(pset.getParameter<int32_t>("nbins"))
      };
}

void METMonitor::setMETitle(METME& me, std::string titleX, std::string titleY)
{
  me.numerator->setAxisTitle(titleX,1);
  me.numerator->setAxisTitle(titleY,2);
  me.denominator->setAxisTitle(titleX,1);
  me.denominator->setAxisTitle(titleY,2);

}

void METMonitor::bookME(DQMStore::IBooker &ibooker, METME& me, const std::string& histname, const std::string& histtitle, int nbins, double min, double max)
{
  me.numerator   = ibooker.book1D(histname+"_numerator",   histtitle+" (numerator)",   nbins, min, max);
  me.denominator = ibooker.book1D(histname+"_denominator", histtitle+" (denominator)", nbins, min, max);
}
void METMonitor::bookME(DQMStore::IBooker &ibooker, METME& me, const std::string& histname, const std::string& histtitle, const std::vector<double>& binning)
{
  int nbins = binning.size()-1;
  std::vector<float> fbinning(binning.begin(),binning.end());
  float* arr = &fbinning[0];
  me.numerator   = ibooker.book1D(histname+"_numerator",   histtitle+" (numerator)",   nbins, arr);
  me.denominator = ibooker.book1D(histname+"_denominator", histtitle+" (denominator)", nbins, arr);
}
void METMonitor::bookME(DQMStore::IBooker &ibooker, METME& me, const std::string& histname, const std::string& histtitle, int nbinsX, double xmin, double xmax, double ymin, double ymax)
{
  me.numerator   = ibooker.bookProfile(histname+"_numerator",   histtitle+" (numerator)",   nbinsX, xmin, xmax, ymin, ymax);
  me.denominator = ibooker.bookProfile(histname+"_denominator", histtitle+" (denominator)", nbinsX, xmin, xmax, ymin, ymax);
}
void METMonitor::bookME(DQMStore::IBooker &ibooker, METME& me, const std::string& histname, const std::string& histtitle, int nbinsX, double xmin, double xmax, int nbinsY, double ymin, double ymax)
{
  me.numerator   = ibooker.book2D(histname+"_numerator",   histtitle+" (numerator)",   nbinsX, xmin, xmax, nbinsY, ymin, ymax);
  me.denominator = ibooker.book2D(histname+"_denominator", histtitle+" (denominator)", nbinsX, xmin, xmax, nbinsY, ymin, ymax);
}
void METMonitor::bookME(DQMStore::IBooker &ibooker, METME& me, const std::string& histname, const std::string& histtitle, const std::vector<double>& binningX, const std::vector<double>& binningY)
{
  int nbinsX = binningX.size()-1;
  std::vector<float> fbinningX(binningX.begin(),binningX.end());
  float* arrX = &fbinningX[0];
  int nbinsY = binningY.size()-1;
  std::vector<float> fbinningY(binningY.begin(),binningY.end());
  float* arrY = &fbinningY[0];

  me.numerator   = ibooker.book2D(histname+"_numerator",   histtitle+" (numerator)",   nbinsX, arrX, nbinsY, arrY);
  me.denominator = ibooker.book2D(histname+"_denominator", histtitle+" (denominator)", nbinsX, arrX, nbinsY, arrY);
}

void METMonitor::bookHistograms(DQMStore::IBooker     & ibooker,
				 edm::Run const        & iRun,
				 edm::EventSetup const & iSetup) 
{  
  
  std::string histname, histtitle;

  std::string currentFolder = folderName_ ;
  ibooker.setCurrentFolder(currentFolder.c_str());

  histname = "ht"; histtitle = "HT";
  bookME(ibooker,htME_,histname,histtitle,ht_binning_.nbins,ht_binning_.xmin, ht_binning_.xmax);
  setMETitle(htME_,"HT [GeV]","events / [GeV]");

  histname = "ht_variable"; histtitle = "HT";
  bookME(ibooker,htME_variableBinning_,histname,histtitle,ht_variable_binning_);
  setMETitle(htME_variableBinning_,"HT [GeV]","events / [GeV]");

  histname = "htVsLS"; histtitle = "HT vs LS";
  bookME(ibooker,htVsLS_,histname,histtitle,ls_binning_.nbins, ls_binning_.xmin, ls_binning_.xmax,ht_binning_.xmin, ht_binning_.xmax);
  setMETitle(htVsLS_,"LS","HT [GeV]");

  histname = "deltaphi_metjet1"; histtitle = "DPHI_METJ1";
  bookME(ibooker,deltaphimetj1ME_,histname,histtitle,phi_binning_.nbins, phi_binning_.xmin, phi_binning_.xmax);
  setMETitle(deltaphimetj1ME_,"delta phi (met, j1)","events / 0.1 rad");

  histname = "deltaphi_jet1jet2"; histtitle = "DPHI_J1J2";
  bookME(ibooker,deltaphij1j2ME_,histname,histtitle,phi_binning_.nbins, phi_binning_.xmin, phi_binning_.xmax);
  setMETitle(deltaphij1j2ME_,"delta phi (j1, j2)","events / 0.1 rad");

  histname = "met"; histtitle = "PFMET";
  bookME(ibooker,metME_,histname,histtitle,met_binning_.nbins,met_binning_.xmin, met_binning_.xmax);
  setMETitle(metME_,"PF MET [GeV]","events / [GeV]");

  histname = "met_variable"; histtitle = "PFMET";
  bookME(ibooker,metME_variableBinning_,histname,histtitle,met_variable_binning_);
  setMETitle(metME_variableBinning_,"PF MET [GeV]","events / [GeV]");

  histname = "metVsLS"; histtitle = "PFMET vs LS";
  bookME(ibooker,metVsLS_,histname,histtitle,ls_binning_.nbins, ls_binning_.xmin, ls_binning_.xmax,met_binning_.xmin, met_binning_.xmax);
  setMETitle(metVsLS_,"LS","PF MET [GeV]");

  histname = "metPhi"; histtitle = "PFMET phi";
  bookME(ibooker,metPhiME_,histname,histtitle, phi_binning_.nbins, phi_binning_.xmin, phi_binning_.xmax);
  setMETitle(metPhiME_,"PF MET #phi","events / 0.1 rad");

  // Initialize the GenericTriggerEventFlag
  if ( num_genTriggerEventFlag_ && num_genTriggerEventFlag_->on() ) num_genTriggerEventFlag_->initRun( iRun, iSetup );
  if ( den_genTriggerEventFlag_ && den_genTriggerEventFlag_->on() ) den_genTriggerEventFlag_->initRun( iRun, iSetup );

}

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "Geometry/Records/interface/TrackerTopologyRcd.h"
void METMonitor::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup)  {
  std::cout<<"debug0"<<std::endl;
  // Filter out events if Trigger Filtering is requested
  if (den_genTriggerEventFlag_->on() && ! den_genTriggerEventFlag_->accept( iEvent, iSetup) ) return;
  std::cout<<"debug1"<<std::endl;
  edm::Handle<reco::PFMETCollection> metHandle;
  iEvent.getByToken( metToken_, metHandle );
  reco::PFMET pfmet = metHandle->front();
  if ( ! metSelection_( pfmet ) ) return;

  float ht = 0.0; 
  float met = pfmet.pt();
  float phi = pfmet.phi();
  std::cout<<"debug2"<<std::endl;
  edm::Handle<reco::PFJetCollection> jetHandle;
  iEvent.getByToken( jetToken_, jetHandle );
  std::vector<reco::PFJet> jets;   std::cout<<"debug2a"<<std::endl;
  jets.clear();
  if ( int(jetHandle->size()) < njets_ ) return;
  std::cout<<"debug2b"<<std::endl;
  for ( auto const & j : *jetHandle ) {   std::cout<<"debug2c"<<std::endl;
    if ( jetSelection_(j) ) {   std::cout<<"debug2d"<<std::endl;
      jets.push_back(j);   std::cout<<"debug2e"<<std::endl;
      if ( jetSelection_HT_(j)) ht += j.pt();   std::cout<<"debug2f"<<std::endl;
    }
  }   std::cout<<"debug2g"<<std::endl;
  if ( int(jets.size()) < njets_ ) return;
  std::cout<<"debug3"<<std::endl;
  float deltaPhi_met_j1= 10.0;
  float deltaPhi_j1_j2 = 10.0;

  if (int(jets.size()) >= 1) deltaPhi_met_j1 = fabs( deltaPhi( pfmet.phi(),  jets[0].phi() ));
  if (int(jets.size()) >= 2) deltaPhi_j1_j2 = fabs( deltaPhi( jets[0].phi(),  jets[1].phi() ));
  std::cout<<"debug4"<<std::endl;
  edm::Handle<reco::GsfElectronCollection> eleHandle;
  iEvent.getByToken( eleToken_, eleHandle );
  std::vector<reco::GsfElectron> electrons;
  electrons.clear();
  if ( int(eleHandle->size()) < nelectrons_ ) return;
  for ( auto const & e : *eleHandle ) {
    if ( eleSelection_( e ) ) electrons.push_back(e);
  }
  if ( int(electrons.size()) < nelectrons_ ) return;
  
  edm::Handle<reco::VertexCollection> vtxHandle;
  iEvent.getByToken(vtxToken_, vtxHandle);

  reco::Vertex vtx;
  math::XYZPoint pv(0, 0, 0);
  for (vector<reco::Vertex>::const_iterator v = vtxHandle->begin(); v != vtxHandle->end(); ++v) {
    bool isFake =  v->isFake() ;
    
    if (!isFake) {
      pv.SetXYZ(v->x(), v->y(), v->z());
      vtx = *v;
      break;
    }
  }

  edm::Handle<reco::MuonCollection> muoHandle;
  iEvent.getByToken( muoToken_, muoHandle );
  if ( int(muoHandle->size()) < nmuons_ ) return;
  std::vector<reco::Muon> muons;
  muons.clear();
  for ( auto const & m : *muoHandle ) {
    if ( muoSelection_( m ) && m.isGlobalMuon() && m.isPFMuon() && m.globalTrack()->normalizedChi2() < 10. && m.globalTrack()->hitPattern().numberOfValidMuonHits() > 0 && m.numberOfMatchedStations() > 1 && fabs(m.muonBestTrack()->dxy(pv)) < 0.2 && fabs(m.muonBestTrack()->dz(pv)) < 0.5 && m.innerTrack()->hitPattern().numberOfValidPixelHits() > 0 && m.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5 ) muons.push_back(m);
  }
  if ( int(muons.size()) < nmuons_ ) return;

  // filling histograms (denominator)  
  htME_.denominator -> Fill(ht);
  htME_variableBinning_.denominator -> Fill(ht);
  metME_.denominator -> Fill(met);
  metME_variableBinning_.denominator -> Fill(met);
  metPhiME_.denominator -> Fill(phi);
  deltaphimetj1ME_.denominator -> Fill(deltaPhi_met_j1);
  deltaphij1j2ME_.denominator -> Fill(deltaPhi_j1_j2);

  int ls = iEvent.id().luminosityBlock();
  htVsLS_.denominator -> Fill(ls, ht);
  metVsLS_.denominator -> Fill(ls, met);
  std::cout<<"debug5"<<std::endl;
  // applying selection for numerator
  if (num_genTriggerEventFlag_->on() && ! num_genTriggerEventFlag_->accept( iEvent, iSetup) ) return;

  // filling histograms (num_genTriggerEventFlag_)  
  htME_.numerator -> Fill(ht);
  htME_variableBinning_.numerator -> Fill(ht);
  htVsLS_.numerator -> Fill(ls, ht);
  metME_.numerator -> Fill(met);
  metME_variableBinning_.numerator -> Fill(met);
  metPhiME_.numerator -> Fill(phi);
  metVsLS_.numerator -> Fill(ls, met);
  deltaphimetj1ME_.numerator  -> Fill(deltaPhi_met_j1); 
  deltaphij1j2ME_.numerator  -> Fill(deltaPhi_j1_j2); 
  std::cout<<"debug6"<<std::endl;
}

void METMonitor::fillHistoPSetDescription(edm::ParameterSetDescription & pset)
{
  pset.add<int>   ( "nbins");
  pset.add<double>( "xmin" );
  pset.add<double>( "xmax" );
}

void METMonitor::fillHistoLSPSetDescription(edm::ParameterSetDescription & pset)
{
  pset.add<int>   ( "nbins", 2500);
}

void METMonitor::fillDescriptions(edm::ConfigurationDescriptions & descriptions)
{
  edm::ParameterSetDescription desc;
  desc.add<std::string>  ( "FolderName", "HLT/MET" );

  desc.add<edm::InputTag>( "met",      edm::InputTag("pfMet") );
  desc.add<edm::InputTag>( "jets",     edm::InputTag("ak4PFJetsCHS") );
  desc.add<edm::InputTag>( "electrons",edm::InputTag("gedGsfElectrons") );
  desc.add<edm::InputTag>( "muons",    edm::InputTag("muons") );
  desc.add<edm::InputTag>( "vertices",edm::InputTag("offlinePrimaryVertices") );
  desc.add<std::string>("metSelection", "pt > 0");
  desc.add<std::string>("jetSelection", "pt > 0");
  desc.add<std::string>("eleSelection", "pt > 0");
  desc.add<std::string>("muoSelection", "pt > 0");
  desc.add<std::string>("jetSelection_HT", "pt > 30 && eta < 2.5");
  desc.add<int>("njets",      0);
  desc.add<int>("nelectrons", 0);
  desc.add<int>("nmuons",     0);

  edm::ParameterSetDescription genericTriggerEventPSet;
  genericTriggerEventPSet.add<bool>("andOr");
  genericTriggerEventPSet.add<edm::InputTag>("dcsInputTag", edm::InputTag("scalersRawToDigi") );
  genericTriggerEventPSet.add<std::vector<int> >("dcsPartitions",{});
  genericTriggerEventPSet.add<bool>("andOrDcs", false);
  genericTriggerEventPSet.add<bool>("errorReplyDcs", true);
  genericTriggerEventPSet.add<std::string>("dbLabel","");
  genericTriggerEventPSet.add<bool>("andOrHlt", true);
  genericTriggerEventPSet.add<edm::InputTag>("hltInputTag", edm::InputTag("TriggerResults::HLT") );
  genericTriggerEventPSet.add<std::vector<std::string> >("hltPaths",{});
  genericTriggerEventPSet.add<std::string>("hltDBKey","");
  genericTriggerEventPSet.add<bool>("errorReplyHlt",false);
  genericTriggerEventPSet.add<unsigned int>("verbosityLevel",1);

  desc.add<edm::ParameterSetDescription>("numGenericTriggerEventPSet", genericTriggerEventPSet);
  desc.add<edm::ParameterSetDescription>("denGenericTriggerEventPSet", genericTriggerEventPSet);

  edm::ParameterSetDescription histoPSet;
  edm::ParameterSetDescription metPSet;
  fillHistoPSetDescription(metPSet);
  histoPSet.add<edm::ParameterSetDescription>("metPSet", metPSet);
  edm::ParameterSetDescription htPSet;
  fillHistoPSetDescription(htPSet);
  histoPSet.add<edm::ParameterSetDescription>("htPSet", htPSet);
  std::vector<double> bins = {0.,20.,40.,60.,80.,90.,100.,110.,120.,130.,140.,150.,160.,170.,180.,190.,200.,220.,240.,260.,280.,300.,350.,400.,450.,1000.};
  histoPSet.add<std::vector<double> >("metBinning", bins);
  histoPSet.add<std::vector<double> >("htBinning", bins);

  edm::ParameterSetDescription lsPSet;
  fillHistoLSPSetDescription(lsPSet);
  histoPSet.add<edm::ParameterSetDescription>("lsPSet", lsPSet);

  desc.add<edm::ParameterSetDescription>("histoPSet",histoPSet);

  descriptions.add("metMonitoring", desc);
}

// Define this as a plug-in
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(METMonitor);
