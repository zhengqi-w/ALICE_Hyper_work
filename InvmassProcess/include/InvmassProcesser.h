// varibles defines here
//const TString TreeName_1 = "O2hypcands";
const TString TreeName_1 = "O2hypcandsflow";
TTree* fTreeChain;
const Double_t PionMass = 0.1395704;
const Double_t KaonMass = 0.493677;
const Double_t DeuteronMass = 1.87561294257;
const Double_t ProtonMass = 0.9382720813;
const Double_t He3Mass = 2.80839160743;
const Double_t HypertritonMass = 2.99177;
const Int_t massbinnum = 70;
const Float_t massmin = 2.96;
const Float_t massmax = 3.03;
Int_t xpos=20, ypos=20;
Int_t cansizeX=580, cansizeY=500;
//Branchs and BranchAddresses Setting
Float_t  fCentralityFT0A; 
Float_t  fCentralityFT0C; 
Float_t  fCentralityFT0M; 
Float_t  fPsiFT0A; 
Float_t  fMultFT0A; 
Float_t  fPsiFT0C; 
Float_t  fMultFT0C; 
Float_t  fPsiTPC; 
Float_t  fMultTPC; 
Float_t  fXPrimVtx; 
Float_t  fYPrimVtx; 
Float_t  fZPrimVtx; 
Bool_t   fIsMatter; 
Float_t  fPtHe3; 
Float_t  fPhiHe3; 
Float_t  fEtaHe3; 
Float_t  fPtPi; 
Float_t  fPhiPi; 
Float_t  fEtaPi; 
Float_t  fXDecVtx; 
Float_t  fYDecVtx; 
Float_t  fZDecVtx; 
Float_t  fDcaV0Daug; 
Float_t  fDcaHe; 
Float_t  fDcaPi; 
Float_t  fNSigmaHe; 
UChar_t  fNTPCclusHe; 
UChar_t  fNTPCclusPi; 
Float_t  fTPCmomHe; 
Float_t  fTPCmomPi; 
UShort_t fTPCsignalHe; 
UShort_t fTPCsignalPi;
Float_t  fTPCChi2He;//added
UInt_t   fITSclusterSizesHe; 
UInt_t   fITSclusterSizesPi; 
UChar_t  fFlags; 
//Bool_t   fTracked; 
Int_t fTrackedClSize;//added
//Branches
TBranch* b_CentralityFT0A; 
TBranch* b_CentralityFT0C; 
TBranch* b_CentralityFT0M; 
TBranch* b_PsiFT0A; 
TBranch* b_MultFT0A; 
TBranch* b_PsiFT0C; 
TBranch* b_MultFT0C; 
TBranch* b_PsiTPC; 
TBranch* b_MultTPC; 
TBranch* b_XPrimVtx; 
TBranch* b_YPrimVtx; 
TBranch* b_ZPrimVtx; 
TBranch* b_IsMatter; 
TBranch* b_PtHe3; 
TBranch* b_PhiHe3; 
TBranch* b_EtaHe3; 
TBranch* b_PtPi; 
TBranch* b_PhiPi; 
TBranch* b_EtaPi; 
TBranch* b_XDecVtx; 
TBranch* b_YDecVtx; 
TBranch* b_ZDecVtx; 
TBranch* b_DcaV0Daug; 
TBranch* b_DcaHe; 
TBranch* b_DcaPi; 
TBranch* b_NSigmaHe; 
TBranch* b_NTPCclusHe; 
TBranch* b_NTPCclusPi; 
TBranch* b_TPCmomHe; 
TBranch* b_TPCmomPi; 
TBranch* b_TPCsignalHe; 
TBranch* b_TPCsignalPi; 
TBranch* b_TPCChi2He;//added
TBranch* b_ITSclusterSizesHe; 
TBranch* b_ITSclusterSizesPi; 
TBranch* b_Flags; 
//TBranch* b_Tracked; 
TBranch* b_TrackedClSize;//added
//vectors for branchaddress
std::vector<Int_t*> Hypertriton_BranchAddress_int = 
{
  &fTrackedClSize
};

std::vector<Float_t*> Hypertriton_BranchAddress_float = 
{
  &fCentralityFT0A,
  &fCentralityFT0C,
  &fCentralityFT0M,
  &fPsiFT0A,
  &fMultFT0A,
  &fPsiFT0C,
  &fMultFT0C,
  &fPsiTPC,
  &fMultTPC,
  &fXPrimVtx, 
  &fYPrimVtx, 
  &fZPrimVtx,
  &fPtHe3, 
  &fPhiHe3, 
  &fEtaHe3, 
  &fPtPi, 
  &fPhiPi, 
  &fEtaPi, 
  &fXDecVtx, 
  &fYDecVtx, 
  &fZDecVtx, 
  &fDcaV0Daug,
  &fDcaHe, 
  &fDcaPi, 
  &fNSigmaHe,
  &fTPCmomHe, 
  &fTPCmomPi,
  &fTPCChi2He  

};

std::vector<Double_t*> Hypertriton_BranchAddress_double = 
{

};

std::vector<UChar_t*> Hypertriton_BranchAddress_uchar =
{
  &fNTPCclusHe, 
  &fNTPCclusPi,
  &fFlags 
};

std::vector<UShort_t*> Hypertriton_BranchAddress_ushort =
{
  &fTPCsignalHe, 
  &fTPCsignalPi 
};

std::vector<UInt_t*> Hypertriton_BranchAddress_uint =
{
  &fITSclusterSizesHe, 
  &fITSclusterSizesPi 
};

std::vector<Bool_t*> Hypertriton_BranchAddress_bool =
{
  &fIsMatter,
  //&fTracked
};
//vector for branches
std::vector<TBranch*> Hypertriton_Branches = 
{
  b_CentralityFT0A, 
  b_CentralityFT0C, 
  b_CentralityFT0M,
  b_PsiFT0A, 
  b_MultFT0A, 
  b_PsiFT0C, 
  b_MultFT0C, 
  b_PsiTPC, 
  b_MultTPC, 
  b_XPrimVtx, 
  b_YPrimVtx, 
  b_ZPrimVtx, 
  b_IsMatter, 
  b_PtHe3, 
  b_PhiHe3, 
  b_EtaHe3, 
  b_PtPi, 
  b_PhiPi, 
  b_EtaPi, 
  b_XDecVtx, 
  b_YDecVtx, 
  b_ZDecVtx, 
  b_DcaV0Daug, 
  b_DcaHe, 
  b_DcaPi, 
  b_NSigmaHe, 
  b_NTPCclusHe, 
  b_NTPCclusPi, 
  b_TPCmomHe, 
  b_TPCmomPi, 
  b_TPCsignalHe, 
  b_TPCsignalPi,
  b_TPCChi2He,//added 
  b_ITSclusterSizesHe, 
  b_ITSclusterSizesPi, 
  b_Flags, 
  //b_Tracked
  b_TrackedClSize//added 
};
//functions
void DrawSignalvsBKG(TH1* h_signal,TH1* h_signal_anti,TH1* h_bkg,TH1* h_bkg_anti,TString dataset,TString target);
Bool_t CandidateSelectiom(const std::vector<Float_t> cuts, std::vector<Float_t> values, int swich_point);//put this into tool?
void DrawCen_FT0C_After(TH1* h_cen_FT0C_after, TString dataset, TString target);
void DrawCenFT0A_C_M(TH1* h_CenFT0A,TH1* h_CenFT0C,TH1* h_CenFT0M,TString dataset, TString target);
void Draw_Compare_ITSClustersize(TH1* h_ITSclustersize_Pi, TH1* h_ITSclustersize_He3, TString dataset, TString target);
void ProcessInvmass(std::vector<std::vector<TH1F*>> h_mass_matter, std::vector<std::vector<TH1F*>> h_mass_anti, std::vector<std::vector<TH1F*>> h_mass_total, int isize, int jsize, Int_t Processmod,Bool_t PlotOnly, Bool_t DoProduction, TString dataset, TString target);//bin counting extract the production
void Plot_QA_Parameter_distributions(std::vector<TH1F*> h_QA, TString dataset, TString target);
