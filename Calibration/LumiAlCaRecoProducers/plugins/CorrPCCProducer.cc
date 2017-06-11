/**_________________________________________________________________
class:   CorrPCCProducer.cc
description: Creates a LumiInfo object that will contain the luminosity per bunch crossing
             Along with the total lumi and the statistical error... (standard sqrt(N) stats) 
authors:Sam Higginbotham (shigginb@cern.ch) and Chris Palmer (capalmer@cern.ch) 
________________________________________________________________**/


// C++ standard
#include <string>
#include <vector>
// CMS
#include "DataFormats/Luminosity/interface/PixelClusterCounts.h"
#include "DataFormats/Luminosity/interface/LumiInfo.h"
#include "DataFormats/Luminosity/interface/LumiConstants.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
// CMS
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/Run.h"
#include "TMath.h"

class CorrPCCProducer : public edm::one::EDProducer<edm::EndRunProducer,edm::one::WatchRuns,edm::EndLuminosityBlockProducer,edm::one::WatchLuminosityBlocks> {
  public:
    explicit CorrPCCProducer(const edm::ParameterSet&);
    ~CorrPCCProducer();

  private:
    void MakeCorrectionTemplate ();
    float GetMaximum(std::vector<float>&);
    std::pair< float, std::vector<float>> CalculateCorrections (std::vector<float> &);
    std::vector<float>& MakeCorrections (std::vector<float>&);
    virtual void beginRun(edm::Run const& runSeg, const edm::EventSetup& iSetup) override final;
    virtual void beginLuminosityBlock(edm::LuminosityBlock const& lumiSeg, const edm::EventSetup& iSetup);
    virtual void endLuminosityBlock(edm::LuminosityBlock const& lumiSeg, const edm::EventSetup& iSetup);
    virtual void endRun(edm::Run const& runSeg, const edm::EventSetup& iSetup)override final;
    virtual void endLuminosityBlockProduce(edm::LuminosityBlock& lumiSeg, const edm::EventSetup& iSetup) override final;
    virtual void endRunProduce(edm::Run& runSeg, const edm::EventSetup& iSetup);
    virtual void produce                  (edm::Event& iEvent, const edm::EventSetup& iSetup) override final;
 
    //Old input object
    edm::EDGetTokenT<LumiInfo>  LumiToken;
    std::string   PCCsrc_;//input file EDproducer module label 
    std::string   ProdInst_;//input file product instance 

    std::string trigstring_; //specifies the trigger Rand or ZeroBias 
    std::vector<float> rawlumiBX_;//new vector containing clusters per bxid 
    std::vector<float> errOnLumiByBX_;//standard error per bx
    std::vector<float> totalLumiByBX_;//summed lumi
    std::vector<float> correctionTemplate_;
    std::vector<float> corrected_tmp_;
    std::vector<float> correctionList_;//list of scale factors to apply.
    float totalLumi_;//The total raw luminosity from the pixel clusters - not scaled
    float statErrOnLumi_;//the statistical error on the lumi - large num ie sqrt(N)
    int countLumi_;//The lumisection count... the size of the lumiblock
    int resetNLumi_;//The number of lumisections per block.

    double type1_; //Initial type 1 correction factor
    double type2_a_;//amplitude for the type 2 correction 
    double type2_b_;//decay width for the type 2 correction

    
    //New output object
    std::unique_ptr<LumiInfo> outLumiOb;


};

//--------------------------------------------------------------------------------------------------
CorrPCCProducer::CorrPCCProducer(const edm::ParameterSet& iConfig)
{
    //Config Parameters from the config file
    PCCsrc_ = iConfig.getParameter<edm::ParameterSet>("CorrPCCProducerParameters").getParameter<std::string>("inLumiObLabel");
    ProdInst_ = iConfig.getParameter<edm::ParameterSet>("CorrPCCProducerParameters").getParameter<std::string>("ProdInst");
    trigstring_ = iConfig.getParameter<edm::ParameterSet>("CorrPCCProducerParameters").getUntrackedParameter<std::string>("trigstring","alcaLumi");
    resetNLumi_=iConfig.getParameter<edm::ParameterSet>("CorrPCCProducerParameters").getParameter<int>("resetEveryNLumi");
    type1_= iConfig.getParameter<edm::ParameterSet>("CorrPCCProducerParameters").getParameter<double>("type1");
    type2_a_ = iConfig.getParameter<edm::ParameterSet>("CorrPCCProducerParameters").getParameter<double>("type2_a");
    type2_b_ = iConfig.getParameter<edm::ParameterSet>("CorrPCCProducerParameters").getParameter<double>("type2_b");
    //Initialization of Params
    countLumi_=0;
    for(unsigned int bx=0;bx<LumiConstants::numBX;bx++){
        totalLumiByBX_.push_back(0);
    }
  
    //Initialization of Temparory Corrected PCC
     
    for (size_t bx=0; bx<LumiConstants::numBX; bx++){
        corrected_tmp_.push_back(0);    
   
    } 
    //Generate a pseudo correction list:Add function to created list here?
    for(unsigned int bx=0;bx<LumiConstants::numBX;bx++){
        correctionList_.push_back(1.0);
    }
   
    for(unsigned int bx=0;bx<LumiConstants::numBX;bx++){
        correctionTemplate_.push_back(1.0);
    
    }

    //Input tag for raw lumi
    edm::InputTag PCCInputTag_(PCCsrc_, ProdInst_);

    LumiToken=consumes<LumiInfo, edm::InLumi>(PCCInputTag_);
    produces<LumiInfo, edm::InLumi>(trigstring_);
}

//--------------------------------------------------------------------------------------------------
CorrPCCProducer::~CorrPCCProducer(){
}
//--------------------------------------------------------------------------------------------------
std::vector<float>& CorrPCCProducer::MakeCorrections(std::vector<float>& corrected_){
        
    for(unsigned int bx=0;bx<LumiConstants::numBX;bx++){
        corrected_.at(bx)=corrected_.at(bx)*correctionList_.at(bx);//Applying the corrections
    } 
    return corrected_;
}

void  CorrPCCProducer::MakeCorrectionTemplate (){
    for(unsigned int bx=1;bx<LumiConstants::numBX;bx++){
       correctionTemplate_.at(bx)=type2_a_*exp(-(bx-1)*type2_b_);
    }

}

float CorrPCCProducer::GetMaximum(std::vector<float>& lumi_vector){
    float max_lumi=0;
    for(size_t i=0; i<lumi_vector.size(); i++){
        if(lumi_vector.at(i)>max_lumi)  max_lumi = lumi_vector.at(i);
    }   
    return max_lumi;
}

std::pair<float, std::vector<float> > CorrPCCProducer::CalculateCorrections (std::vector<float> &uncorrected){

    //Find the abort gap and calculate the noise
    //std::vector<float> corrected_tmp_;
    for(size_t i=0; i<corrected_tmp_.size(); i++){
        corrected_tmp_.at(i)=uncorrected.at(i);
    }
    bool gap=false;
    int idl=0;
    int num_cut=20;
    float noise=0;
    for(int l=0; l<500; l++){
        if (corrected_tmp_.at(l)==0 && corrected_tmp_.at(l+1)==0 && corrected_tmp_.at(l+2)==0){
            gap=true;
        }
        if(gap && corrected_tmp_.at(l)!=0 && idl<num_cut){
            noise+=corrected_tmp_.at(l);
            idl+=1;
        }

    }
  
    if(idl!=0){
        noise=noise/idl;
    }

    else{
        noise=0;

    }

    //Apply initial type 1 correction
   for(size_t k=0;k<LumiConstants::numBX-1; k++){ 
       float bin_k = corrected_tmp_.at(k);
       corrected_tmp_.at(k+1)=corrected_tmp_.at(k+1)-type1_*bin_k;
  
   }
 

   //Apply type 2 correction
   for(size_t i=0; i<LumiConstants::numBX-1; i++){
       for(size_t j=i+1; j<i+LumiConstants::numBX-1; j++){
           float bin_i = corrected_tmp_.at(i);
           if (j<LumiConstants::numBX){
               corrected_tmp_.at(j)=corrected_tmp_.at(j)-bin_i*correctionTemplate_.at(j-i);
           } 
           
           else{
               corrected_tmp_.at(j-LumiConstants::numBX) = corrected_tmp_.at(j-LumiConstants::numBX)-bin_i*correctionTemplate_.at(j-i);
           }
       }

    }
  
    //Apply additional iteration for type 1 correction
    float lumiMax = GetMaximum(corrected_tmp_);
    float threshold = lumiMax*0.2;  //need to be changed to GetMaximum()*0.2
   
    float mean_type1 = 0;  //Calculate the mean value of the type 1 residual 
    int nTrain = 0;
    for(size_t ibx=2; ibx<LumiConstants::numBX-5; ibx++){
        //float lumiM1 = corrected_tmp_.at(ibx-1);
        float lumi   = corrected_tmp_.at(ibx);
        float lumiP1 = corrected_tmp_.at(ibx+1);
        float lumiP2 = corrected_tmp_.at(ibx+2);
        float lumiP3 = corrected_tmp_.at(ibx+3);
        float lumiP4 = corrected_tmp_.at(ibx+4);
        float lumiP5 = corrected_tmp_.at(ibx+5);
   
        if(lumi>threshold && lumiP1<threshold && lumiP2<threshold){
            mean_type1+=(lumiP1-(lumiP3+lumiP4+lumiP5)/3)/lumi;
            nTrain+=1;
        }
    } 
  
    mean_type1 = mean_type1/nTrain;
  
    for (size_t ibx=0; ibx<LumiConstants::numBX-1; ibx++){
        float bin_i = corrected_tmp_.at(ibx);
        corrected_tmp_.at(ibx+1) = corrected_tmp_.at(ibx+1)-bin_i*mean_type1;

    }
   
   float Integral_Uncorr=0;
   float Integral_Corr = 0;
   //Calculate Per-BX correction factor and overall correction factor
   for (size_t ibx=0; ibx<corrected_tmp_.size(); ibx++){
       if(corrected_tmp_.at(ibx)>threshold){
           Integral_Uncorr+=uncorrected.at(ibx);
           Integral_Corr+=corrected_tmp_.at(ibx);
       }
       
       corrected_tmp_.at(ibx) = corrected_tmp_.at(ibx)/uncorrected.at(ibx);

   }
    
   std::pair <float, std::vector<float>> corr_pair_ = std::make_pair(Integral_Corr/Integral_Uncorr, corrected_tmp_); 
   return corr_pair_;
}

//--------------------------------------------------------------------------------------------------
void CorrPCCProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
    //namespaces

    //std::cout<<"A Print Statement"<<std::endl;

      
}

//--------------------------------------------------------------------------------------------------
void CorrPCCProducer::beginLuminosityBlock(edm::LuminosityBlock const& lumiSeg, const edm::EventSetup& iSetup){
    std::cout<<"Begin Lumi-Block"<<std::endl;
    //outLumiOb = std::make_unique<LumiInfo>(); 
    //LumiInfo outLumiOb; 
    countLumi_++;

}
//--------------------------------------------------------------------------------------------------
void CorrPCCProducer::beginRun(edm::Run const& runSeg, const edm::EventSetup& iSetup){
    std::cout<<"Begin Run"<<std::endl;
    outLumiOb = std::make_unique<LumiInfo>(); 
    //LumiInfo outLumiOb; 

}

//--------------------------------------------------------------------------------------------------
void CorrPCCProducer::endLuminosityBlock(edm::LuminosityBlock const& lumiSeg, const edm::EventSetup& iSetup){
    //check to see if end of lumiblock

    edm::Handle<LumiInfo> PCCHandle; 
    lumiSeg.getByToken(LumiToken,PCCHandle);
    
    const LumiInfo& inLumiOb = *(PCCHandle.product()); 

    //Making the vectors to loop over the lumisections for each run    
    rawlumiBX_= inLumiOb.getInstLumiAllBX();
    std::cout<<"The total Luminosity "<<inLumiOb.totalrawLuminosity()<<std::endl;
    //Example of forloop
    //for (unsigned int i=0;i<modID_.size();i++){
        
    //summing over lumisections
    for(unsigned int bx=0;bx<LumiConstants::numBX;bx++){
        totalLumiByBX_[bx]+=rawlumiBX_[bx];
    }
    outLumiOb->setInstLumi(totalLumiByBX_);   
    
    std::cout<<"Print end Lumi Block"<<std::endl;


}
//--------------------------------------------------------------------------------------------------
void CorrPCCProducer::endRun(edm::Run const& runSeg, const edm::EventSetup& iSetup){
    //std::cout<<"End Run"<<std::endl;
    //outLumiOb = std::make_unique<LumiInfo>(); 
    //LumiInfo outLumiOb; 
    //sum over the lumi sections
}
//--------------------------------------------------------------------------------------------------
void CorrPCCProducer::endLuminosityBlockProduce(edm::LuminosityBlock& lumiSeg, const edm::EventSetup& iSetup){
    //Save if # of lumisections are reached then save
    if (resetNLumi_ > 0 && countLumi_%resetNLumi_!=0) return;
    lumiSeg.put(std::move(outLumiOb), std::string(trigstring_));  
    for(unsigned int bx=0;bx<LumiConstants::numBX;bx++){
        totalLumiByBX_[bx]=0;//reset the total after the save
    }

}
//--------------------------------------------------------------------------------------------------
void CorrPCCProducer::endRunProduce(edm::Run& runSeg, const edm::EventSetup& iSetup){
    std::cout<<"End Run"<<std::endl;
    //outLumiOb = std::make_unique<LumiInfo>(); 
    //LumiInfo outLumiOb; 
    //place a save here.
    runSeg.put(std::move(outLumiOb), std::string(trigstring_)); 
    for(unsigned int bx=0;bx<LumiConstants::numBX;bx++){
        totalLumiByBX_[bx]=0;//reset the total after the save
    }

}


DEFINE_FWK_MODULE(CorrPCCProducer);

