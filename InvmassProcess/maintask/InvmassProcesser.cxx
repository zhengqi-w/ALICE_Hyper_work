#include "../config/config.h"
#include "../include/toollib.h"
#include "../include/toollib.cpp"
#include "../include/InvmassProcesser.h"

#include "TLorentzVector.h"

//init steeings



void InvmassProcesser(TString dataset, TString target)
{  
  //----------------histogram initialization---------------------
  //----------for the reason we need to init TH set inside the main func-------------
  std::vector<TH1F*> h_centrality(3);
  for(int i= 0; i < 3; i++)
  {
    TString tytle[3];
    tytle[0] = "FT0A";
    tytle[1] = "FT0C";
    tytle[2] = "FT0M";
    h_centrality[i] = new TH1F(Form("h_centrality_%s",tytle[i].Data()),"",100,0,100);
  }
  TH1F* h_cen_FT0C_after = new TH1F("h_cen_FT0C_after","",100,0,100);
  std::vector<TH1F*> h_ITSclustersize_Avg;
  for(int i= 0; i < 2; i++)
  {
    TString tytle[2];
    tytle[0] = "Pion";
    tytle[1] = "He3";
    h_ITSclustersize_Avg.push_back(new TH1F(Form("h_ITSclustersize_Avg_%s",tytle[i].Data()),"",15,0,15));
  }
  std::vector<std::vector<TH1F*>> h_Invmass_matter(config::nCenbin, std::vector<TH1F*>(config::nPtbin));
  for(int i= 0; i < config::nCenbin; i++)
  {
    for(int j= 0; j < config::nPtbin; j++)
    {
      h_Invmass_matter[i][j]=new TH1F(Form("h_Invmass_matter_%d_%d",i,j),"",massbinnum,massmin,massmax);
    }
  }
  std::vector<std::vector<TH1F*>> h_Invmass_anti(config::nCenbin, std::vector<TH1F*>(config::nPtbin));
  for(int i= 0; i < config::nCenbin; i++)
  {
    for(int j= 0; j < config::nPtbin; j++)
    {
      h_Invmass_anti[i][j]=new TH1F(Form("h_Invmass_anti_%d_%d",i,j),"",massbinnum,massmin,massmax);
    }
  }
  std::vector<std::vector<TH1F*>> h_Invmass_total(config::nCenbin, std::vector<TH1F*>(config::nPtbin));
  for(int i= 0; i < config::nCenbin; i++)
  {
    for(int j= 0; j < config::nPtbin; j++)
    {
      h_Invmass_total[i][j]=new TH1F(Form("h_Invmass_total_%d_%d",i,j),"",massbinnum,massmin,massmax);
    }
  }
  //QA_histogram_parameters
  TH1F* h_Eta_Pion = new TH1F("h_Eta_Pion","Eta_Pion",100,-1.1,1.1);
  h_Eta_Pion->GetXaxis()->SetTitle("#eta_{#pi}");
  h_Eta_Pion->GetYaxis()->SetTitle("counts");
  TH1F* h_Eta_He3 = new TH1F("h_Eta_He3","Eta_He3",100,-1.1,1.1);
  h_Eta_He3->GetXaxis()->SetTitle("#eta_{He3}");
  h_Eta_He3->GetYaxis()->SetTitle("counts");
  TH1F* h_Phi_Pion = new TH1F("h_Phi_Pion","Phi_Pion",100,-4,4);
  h_Phi_Pion->GetXaxis()->SetTitle("#phi_{#pi}");
  h_Phi_Pion->GetYaxis()->SetTitle("counts");
  TH1F* h_Phi_He3 = new TH1F("h_Phi_He3","Phi_He3",100,-4,4);
  h_Phi_He3->GetXaxis()->SetTitle("#phi_{He3}");
  h_Phi_He3->GetYaxis()->SetTitle("counts");
  TH1F* h_CPA = new TH1F("h_CPA","CosofPointingangle_calculaterd",100,0.5,1);
  h_CPA->GetXaxis()->SetTitle("cos#theta_{pointing}");
  h_CPA->GetYaxis()->SetTitle("counts");
  TH1F* h_ct = new TH1F("h_ct","ct_calculaterd",1000,0,100);
  h_ct->GetXaxis()->SetTitle("ct (cm)");
  h_ct->GetYaxis()->SetTitle("counts");
  TH1F* h_nSigmaHe3 = new TH1F("h_nSigmaHe3","nSigmaHe3",100,-5,5);
  h_nSigmaHe3->GetXaxis()->SetTitle("n#sigma_{He3}");
  h_nSigmaHe3->GetYaxis()->SetTitle("counts");
  TH1F* h_DCApi = new TH1F("h_DCApi","DCApi",100,0,10);
  h_DCApi->GetXaxis()->SetTitle("DCA_{#pi} (cm)");
  h_DCApi->GetYaxis()->SetTitle("counts");
  TH1F* h_DCAHe3 = new TH1F("h_DCAHe3","DCAHe3",100,0,10);
  h_DCAHe3->GetXaxis()->SetTitle("DCA_{He3} (cm)");
  h_DCAHe3->GetYaxis()->SetTitle("counts");
  TH1F* h_ptPion = new TH1F("h_ptPion","ptPion",100,0,10);
  h_ptPion->GetXaxis()->SetTitle("pt_{#pi} (GeV/c)");
  h_ptPion->GetYaxis()->SetTitle("counts");
  TH1F* h_ptHe3 = new TH1F("h_ptHe3","ptHe3",100,0,10);
  h_ptHe3->GetXaxis()->SetTitle("pt_{He3} (GeV/c)");
  h_ptHe3->GetYaxis()->SetTitle("counts");
  TH1F* h_pt_mother = new TH1F("h_pt_mother","pt_mother",100,0,10);
  h_pt_mother->GetXaxis()->SetTitle("pt_{mother} (GeV/c)");
  h_pt_mother->GetYaxis()->SetTitle("counts");
  TH1F* h_eta_mother = new TH1F("h_eta_mother","eta_mother",100,-1,1);
  h_eta_mother->GetXaxis()->SetTitle("#eta_{mother}");
  h_eta_mother->GetYaxis()->SetTitle("counts");
  TH1F* h_TPCNcls_pi = new TH1F("h_TPCNcls_pi","TPCNcls_pi",160,0,160);
  h_TPCNcls_pi->GetXaxis()->SetTitle("TPC Ncls_{#pi}");
  h_TPCNcls_pi->GetYaxis()->SetTitle("counts");
  TH1F* h_TPCNcls_He3 = new TH1F("h_TPCNcls_He3","TPCNcls_He3",160,0,160);
  h_TPCNcls_He3->GetXaxis()->SetTitle("TPC Ncls_{He3}");
  h_TPCNcls_He3->GetYaxis()->SetTitle("counts");
  TH1F* h_pinTPCpi = new TH1F("h_pinTPCpi","pinTPCpi",100,0,20);
  h_pinTPCpi->GetXaxis()->SetTitle("pinTPC_{#pi}");
  h_pinTPCpi->GetYaxis()->SetTitle("counts");
  TH1F* h_pinTPCHe3 = new TH1F("h_pinTPCHe3","pinTPCHe3",100,0,20);
  h_pinTPCHe3->GetXaxis()->SetTitle("pinTPC_{He3}");
  h_pinTPCHe3->GetYaxis()->SetTitle("counts");
  TH1F* h_ITSclusterSize_pi = new TH1F("h_ITSclusterSize_pi","ITSclusterSize_pi",15,0,15);
  h_ITSclusterSize_pi->GetXaxis()->SetTitle("ITSclusterSize_{#pi}");
  h_ITSclusterSize_pi->GetYaxis()->SetTitle("counts");
  TH1F* h_ITSclusterSize_He3 = new TH1F("h_ITSclusterSize_He3","ITSclusterSize_He3",15,0,15);
  h_ITSclusterSize_He3->GetXaxis()->SetTitle("ITSclusterSize_{He3}");
  h_ITSclusterSize_He3->GetYaxis()->SetTitle("counts");
  TH1F* h_TPCsignal_pi = new TH1F("h_TPCsignal_pi","TPCsignal_pi",1e4,0,1e4);
  h_TPCsignal_pi->GetXaxis()->SetTitle("TPCsignal_{#pi}");
  h_TPCsignal_pi->GetYaxis()->SetTitle("counts");
  TH1F* h_TPCsignal_He3 = new TH1F("h_TPCsignal_He3","TPCsignal_He3",1e4,0,1e4);
  h_TPCsignal_He3->GetXaxis()->SetTitle("TPCsignal_{He3}");
  h_TPCsignal_He3->GetYaxis()->SetTitle("counts");
  TH1F* h_InvmassQA = new TH1F("h_InvmassQA","InvmassQA",massbinnum,massmin,massmax);
  h_InvmassQA->GetXaxis()->SetTitle("M_{#pi He3} (GeV/c^{2})");
  h_InvmassQA->GetYaxis()->SetTitle("counts");
  TH1F* h_InvmassQA_cut = new TH1F("h_InvmassQA_cut","InvmassQA_aftercut",massbinnum,massmin,massmax);
  h_InvmassQA_cut->GetXaxis()->SetTitle("M_{#pi He3} (GeV/c^{2})");
  h_InvmassQA_cut->GetYaxis()->SetTitle("counts");
  //---------------------QA_histogram_parameters-----------------
  std::vector<TH1F*> h_QA_Parameter_distribution;
  h_QA_Parameter_distribution.push_back(h_Eta_Pion);
  h_QA_Parameter_distribution.push_back(h_Eta_He3);
  h_QA_Parameter_distribution.push_back(h_Phi_Pion);
  h_QA_Parameter_distribution.push_back(h_Phi_He3);
  h_QA_Parameter_distribution.push_back(h_CPA);
  h_QA_Parameter_distribution.push_back(h_ct);
  h_QA_Parameter_distribution.push_back(h_nSigmaHe3);
  h_QA_Parameter_distribution.push_back(h_DCApi);
  h_QA_Parameter_distribution.push_back(h_DCAHe3);
  h_QA_Parameter_distribution.push_back(h_ptPion);
  h_QA_Parameter_distribution.push_back(h_ptHe3);
  h_QA_Parameter_distribution.push_back(h_pt_mother);
  h_QA_Parameter_distribution.push_back(h_eta_mother);
  h_QA_Parameter_distribution.push_back(h_TPCNcls_pi);
  h_QA_Parameter_distribution.push_back(h_TPCNcls_He3);
  h_QA_Parameter_distribution.push_back(h_pinTPCpi);
  h_QA_Parameter_distribution.push_back(h_pinTPCHe3);
  h_QA_Parameter_distribution.push_back(h_ITSclusterSize_pi);
  h_QA_Parameter_distribution.push_back(h_ITSclusterSize_He3);
  h_QA_Parameter_distribution.push_back(h_TPCsignal_pi);
  h_QA_Parameter_distribution.push_back(h_TPCsignal_He3);
  h_QA_Parameter_distribution.push_back(h_InvmassQA);
  h_QA_Parameter_distribution.push_back(h_InvmassQA_cut);
  //---------------------main process----------------------------
  gStyle->SetOptStat(0000);
  gStyle->SetImageScaling(50.);
  ifstream initxt;
  initxt.open("../input/pathtoinputfile.txt");
  if (!initxt.is_open()) { cout << "::: Error ::: Unable to open input text file" << endl;return;}
  std::vector<TString> rootFiles;
  std::string  line = "";
  while (std::getline(initxt, line)) 
  {
    if (!line.empty()) // 检查是否为空行
    {  
      rootFiles.push_back(TString(line));
    }
  }
  initxt.close();
  cout << "number of root files: " << rootFiles.size() << endl;
  int i =1;
  for(const auto& pathtofile : rootFiles)
  {
    cout << "processing file " << i << " " << pathtofile << endl;
    i++;
    TFile* inputfile = tool::FileReader(pathtofile.Data());
    if (inputfile == NULL) { cout << "::: Error ::: inputfile not found" << endl; continue; }
    TList   *keyList = inputfile->GetListOfKeys();    // 获取文件中的对象列表
    TIter   next(keyList);                     // 创建一个迭代器来遍历列表
    TKey    *key;                              // 定义一个指针，用于存储当前遍历到的对象的键
    while((key = (TKey*)next())) 
    {             
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("TDirectoryFile")) continue;
      TString dirName = (TString ) key->GetName();
      TTree *TreeCandidate_1=NULL;
      TDirectory *dir = (TDirectory*)inputfile->Get(Form("%s:/%s",inputfile->GetName(),dirName.Data()));
      dir->GetObject(TreeName_1.Data(),TreeCandidate_1);
      if(!TreeCandidate_1) continue;
      else
      {
        fTreeChain = TreeCandidate_1;
        tool::SetTreeBranchAddress(fTreeChain,Hypertriton_BranchAddress_int,Hypertriton_BranchAddress_float,Hypertriton_BranchAddress_double,Hypertriton_BranchAddress_uchar,Hypertriton_BranchAddress_ushort,Hypertriton_BranchAddress_uint,Hypertriton_BranchAddress_bool,Hypertriton_Branches);
        Long64_t nEntries = fTreeChain->GetEntries();
        for(Long64_t i = 0; i < nEntries; ++i)
        { 
          fTreeChain->GetEntry(i);
          if(fCentralityFT0C > config::Cen_max_FT0C) continue;
          h_cen_FT0C_after->Fill(fCentralityFT0C);
          /*TLorentzVector v_pion, v_he3, v_hyper;
          v_pion.SetPtEtaPhiM(fPtPi, fEtaPi, fPhiPi, PionMass);
          v_he3.SetPtEtaPhiM(fPtHe3, fEtaHe3, fPhiHe3, He3Mass);//stay cautious if we have to dot the charge 2 into pt_he3
          v_hyper = v_pion + v_he3;
          Float_t Eta_mother = v_hyper.Eta();
          Float_t Pt_mother = v_hyper.Pt();
          Float_t P_mother = v_hyper.P();
          Float_t Px_mother = v_hyper.Px();
          Float_t Py_mother = v_hyper.Py();
          Float_t Pz_mother = v_hyper.Pz();
          Float_t Mass_mother = v_hyper.M();*/

          Float_t Pion_Px = fPtPi*std::cos(fPhiPi);
          Float_t Pion_Py = fPtPi*std::sin(fPhiPi);
          Float_t Pion_Pz = fPtPi*std::sinh(fEtaPi);
          Float_t He3_Px = fPtHe3*std::cos(fPhiHe3);
          Float_t He3_Py = fPtHe3*std::sin(fPhiHe3);
          Float_t He3_Pz = fPtHe3*std::sinh(fEtaHe3);
          Float_t Px_mother = Pion_Px + He3_Px;
          Float_t Py_mother = Pion_Py + He3_Py;
          Float_t Pz_mother = Pion_Pz + He3_Pz;
          Float_t Pion_Mom[3] = {Pion_Px,Pion_Py,Pion_Pz};
          Float_t He3_Mom[3] = {He3_Px,He3_Py,He3_Pz};
          Float_t Mother_Mom[3] = {Px_mother,Py_mother,Pz_mother};
          Float_t Pi_P2 = Pion_Px*Pion_Px + Pion_Py*Pion_Py + Pion_Pz*Pion_Pz;
          Float_t He3_P2 = He3_Px*He3_Px + He3_Py*He3_Py + He3_Pz*He3_Pz;
          Float_t PiE = std::sqrt(Pi_P2 + PionMass*PionMass);
          Float_t He3E = std::sqrt(He3_P2 + He3Mass*He3Mass);
          Float_t E_mother = PiE + He3E;
          Float_t Pt_mother = std::hypot(Px_mother,Py_mother);
          Float_t Eta_mother = std::asinh(Mother_Mom[2]/ Pt_mother);
          Float_t P_mother = std::hypot(Px_mother,Py_mother,Pz_mother);
          Float_t Mass_mother = std::sqrt(E_mother*E_mother - Mother_Mom[0]*Mother_Mom[0] - Mother_Mom[1]*Mother_Mom[1] - Mother_Mom[2]*Mother_Mom[2]);
          //calculate the average cluster size
          Float_t clSizeHeAvg = 0, clSizePiAvg = 0;
          Int_t nHitsHe = 0, nHitsPi = 0;
          for(int iLayer = 0; iLayer < 7; ++iLayer)
          {
            UInt_t shiftedHe = (fITSclusterSizesHe >> (4*iLayer)) & 0b1111;
            UInt_t shiftedPi = (fITSclusterSizesPi >> (4*iLayer)) & 0b1111;
            clSizeHeAvg += shiftedHe;
            clSizePiAvg += shiftedPi;
            nHitsHe += (shiftedHe > 0);
            nHitsPi += (shiftedPi > 0);
          }
          if(nHitsHe > 0) clSizeHeAvg /= nHitsHe;
          if(nHitsPi > 0) clSizePiAvg /= nHitsPi;

          //Float_t L_hyper = std::hypot((fXDecVtx-fXPrimVtx),(fYDecVtx-fYPrimVtx),(fZDecVtx-fZPrimVtx));//something wrong!
          Float_t L_hyper = std::hypot(fXDecVtx,fYDecVtx,fZDecVtx);
          Float_t ct = L_hyper*HypertritonMass/P_mother;
          //Float_t CPA = tool::CalculateCosPointingAngle(fXPrimVtx,fYPrimVtx,fZPrimVtx,fXDecVtx,fYDecVtx,fZDecVtx,Px_mother,Py_mother,Pz_mother);
          Float_t CPA = tool::CalculateCosPointingAngle(fXDecVtx,fYDecVtx,fZDecVtx,Px_mother,Py_mother,Pz_mother);
          //cout << "TPCNclsPion:" << static_cast<int>(fNTPCclusPi) << " ITScusterSizePi: " << fITSclusterSizesPi <<" Flags:" << static_cast<int>(fFlags) << " IsMatter: " << static_cast<int>(fIsMatter)<< " Tracked: "<<static_cast<int>(fTracked) <<" ITSclusterSizesHe: "<<fITSclusterSizesHe<<"\n" <<endl;
          h_ITSclustersize_Avg[0]->Fill(clSizePiAvg);
          h_ITSclustersize_Avg[1]->Fill(clSizeHeAvg);
          h_Eta_Pion->Fill(fEtaPi);
          h_Eta_He3->Fill(fEtaHe3);
          h_Phi_Pion->Fill(fPhiPi);
          h_Phi_He3->Fill(fPhiHe3);
          h_CPA->Fill(CPA);
          h_ct->Fill(ct);
          h_nSigmaHe3->Fill(fNSigmaHe);
          h_DCApi->Fill(fDcaPi);
          h_DCAHe3->Fill(fDcaHe);
          h_ptPion->Fill(fPtPi);
          h_ptHe3->Fill(fPtHe3);
          h_pt_mother->Fill(Pt_mother);
          h_eta_mother->Fill(Eta_mother);
          h_TPCNcls_pi->Fill((Float_t)fNTPCclusPi);
          h_TPCNcls_He3->Fill((Float_t)fNTPCclusHe);
          h_pinTPCpi->Fill(fTPCmomPi);
          h_pinTPCHe3->Fill(fTPCmomHe);
          h_ITSclusterSize_pi->Fill(clSizePiAvg);
          h_ITSclusterSize_He3->Fill(clSizeHeAvg);
          h_TPCsignal_pi->Fill((Float_t)fTPCsignalPi);
          h_TPCsignal_He3->Fill((Float_t)fTPCsignalHe);
          h_InvmassQA->Fill(Mass_mother);
          std::vector<Float_t> values = {Pt_mother,ct,CPA,fNSigmaHe,static_cast<Float_t>(fNTPCclusHe),fTPCmomHe,clSizeHeAvg,Eta_mother,static_cast<Float_t>(fTPCsignalPi),fPtPi};
          Bool_t Pass_static_cuts = kFALSE;
          Pass_static_cuts = CandidateSelectiom(config::statical_cuts,values,config::swich_point);

          if(Pt_mother < config::pt_min_mother) continue;
          if(ct < config::ct_min) continue;
          if(CPA < config::cpa_min) continue;
          if(fNSigmaHe < config::nsigma_min_he3) continue;
          if(static_cast<Float_t>(fNTPCclusHe) < config::TPCncls_min_he3) continue;
          if(fTPCmomHe < config::pinTPC_min_he3) continue;
          if(Eta_mother > config::eta_max_mother) continue;
          if(static_cast<Float_t>(fTPCsignalPi) > config::TPCsignal_max_pion) continue;
          if(fPtPi > config::pt_max_pion) continue;
          if(clSizeHeAvg < config::clustersize_min_he3) continue;

          //if(!Pass_static_cuts) continue;
          //if(fDcaPi < config::DCAPi_min)continue;
          //if(fDcaHe < config::DCAHe3_min)continue;
          //if((Float_t)fNTPCclusPi < config::TPCNcls_min_pi)continue;
          h_InvmassQA_cut->Fill(Mass_mother);
          h_centrality[0]->Fill(fCentralityFT0A);
          h_centrality[1]->Fill(fCentralityFT0C);
          h_centrality[2]->Fill(fCentralityFT0M);
          int i_pos = -99;
          int j_pos = -99;
          for(int i = 0; i < config::nCenbin; i++)
          {
            for(int j = 0; j < config::nPtbin; j++)
            {
              if((fCentralityFT0C > config::Cenbin[i]) && (fCentralityFT0C <= config::Cenbin[i+1]) && (Pt_mother > config::Ptbin[j]) && (Pt_mother <= config::Ptbin[j+1]))
              {
                i_pos = i;
                j_pos = j;
              }
            }
          }
          if(i_pos >-1 && j_pos > -1)
          {
            h_Invmass_total[i_pos][j_pos]->Fill(Mass_mother);
            if(fIsMatter)
            {
              h_Invmass_matter[i_pos][j_pos]->Fill(Mass_mother);
            }
            else
            {
              h_Invmass_anti[i_pos][j_pos]->Fill(Mass_mother);
            }
          }
        }//end of tree leaf loop 
      }//end of else 
    }//end of while loop_2
    inputfile->Close();
  }//end of while loop_1
  //========================================Draw the histograms========================================
  Plot_QA_Parameter_distributions(h_QA_Parameter_distribution,dataset.Data(),target.Data());  
  ypos += 100;
  xpos = 20;
  DrawCen_FT0C_After(h_cen_FT0C_after,dataset.Data(),target.Data());
  xpos += 50;
  DrawCenFT0A_C_M(h_centrality[0],h_centrality[1],h_centrality[2],dataset.Data(),target.Data());
  xpos += 50;
  Draw_Compare_ITSClustersize(h_ITSclustersize_Avg[0],h_ITSclustersize_Avg[1],dataset.Data(),target.Data());
  ypos += 100;
  xpos = 20;
  ProcessInvmass(h_Invmass_matter,h_Invmass_anti,h_Invmass_total,config::nCenbin,config::nPtbin,1,0,1,dataset.Data(),target.Data());
  cout<<"====================="<<Form("End of InvmassProcess for : %s_%s",dataset.Data(),target.Data())<<"====================="<<endl;
}//end of main function

//-------------------below is the function achievment-------------------
//------------------functions used in the main func---------------------
void DrawSignalvsBKG(TH1* h_signal,TH1* h_signal_anti,TH1* h_bkg,TH1* h_bkg_anti,TString dataset,TString target)
{
  tool::SetTitleTH1(h_signal,"counts",0.1,0.6,"Mass#pi+K+D (GeV/c^{2})",0.07,0.8);
  tool::SetTitleTH1(h_signal_anti,"counts",0.1,0.6,"Mass#pi+K+D (GeV/c^{2})",0.07,0.8);
  tool::SetTitleTH1(h_bkg,"counts",0.1,0.6,"Mass#pi+K+D (GeV/c^{2})",0.07,0.8);
  tool::SetTitleTH1(h_bkg_anti,"counts",0.1,0.6,"Mass#pi+K+D (GeV/c^{2})",0.07,0.8);
  tool::SetAxisTH1(h_signal,0.0,0.0,massmin,massmax,0.06,0.04);
  tool::SetAxisTH1(h_signal_anti,0.0,0.0,massmin,massmax,0.06,0.04);
  tool::SetAxisTH1(h_bkg,0.0,0.0,massmin,massmax,0.06,0.04);
  tool::SetAxisTH1(h_bkg_anti,0.0,0.0,massmin,massmax,0.06,0.04);
  tool::SetMarkerTH1(h_signal,"Matter",27,1.5,2,2);
  tool::SetMarkerTH1(h_signal_anti,"AntiMatter",27,1.5,2,2);
  tool::SetMarkerTH1(h_bkg,"",33,1.5,1,1);
  tool::SetMarkerTH1(h_bkg_anti,"",33,1.5,1,1);
  TCanvas *canvas = tool::GetCanvas(Form("c1_%s_%s",dataset.Data(),target.Data()),xpos,ypos,cansizeX,cansizeY,0,1,0.02,0.02,0.14,0.01);
  canvas->cd();
  TPad* padleft = tool::GetPad(Form("padleft%s",dataset.Data()),0.0,0.0,0.48,1.0,0.07,0.15,0.14,0.10);
  padleft->Draw();
  padleft->cd();
  padleft->SetTicks();
  padleft->SetGridy();
  double yMax = std::max(h_signal->GetMaximum(), h_bkg->GetMaximum());
  h_signal->SetMaximum(yMax * 1.1); 
  h_bkg->SetMaximum(yMax * 1.1);
  h_signal->Draw("PE0");
  h_bkg->Draw("SAMEPE0");
  TLegend* legendleft = new TLegend(0.65,0.75,0.875,0.95);
  legendleft->SetBorderSize(0);
  legendleft->SetFillColor(0);
  legendleft->SetTextFont(42);
  legendleft->SetTextSize(0.05);
  legendleft->AddEntry(h_signal,Form("signal:%s",dataset.Data()),"P");
  legendleft->AddEntry(h_bkg,Form("bkg:%s",dataset.Data()),"P");
  legendleft->Draw();  

  canvas->cd();
  TPad* padright = tool::GetPad(Form("padright%s",dataset.Data()),0.52,0.0,0.98,1.0,0.07,0.15,0.14,0.10);
  padright->Draw();
  padright->cd();
  padright->SetTicks();
  padright->SetGridy();
  yMax = std::max(h_signal_anti->GetMaximum(), h_bkg_anti->GetMaximum());
  h_signal_anti->SetMaximum(yMax * 1.1); 
  h_bkg_anti->SetMaximum(yMax * 1.1);
  h_signal_anti->Draw("PE0");
  h_bkg_anti->Draw("SAMEPE0");
  TLegend* legendright = new TLegend(0.65,0.75,0.875,0.95);
  legendright->SetBorderSize(0);
  legendright->SetFillColor(0);
  legendright->SetTextFont(42);
  legendright->SetTextSize(0.05);
  legendright->AddEntry(h_signal_anti,Form("signal_anti:%s",dataset.Data()),"P");
  legendright->AddEntry(h_bkg_anti,Form("bkg_anti:%s",dataset.Data()),"P");
  legendright->Draw();  
 
  TString saving_path = Form("../output/%s_%s/",dataset.Data(),target.Data());
  saving_path = tool::create_folder(saving_path);
  TString saving_name = Form("SignalvsRotationBKG_total.pdf");
  canvas->SaveAs(Form("%s%s",saving_path.Data(),saving_name.Data()));
}//func used for finding other hypernucleis


Bool_t CandidateSelectiom(const std::vector<Float_t> cuts, std::vector<Float_t> values, int swich_point)
{
  if(cuts.size() != values.size()) 
  {
    cout<<"::: Candiadate Selection Error::: cuts and values size not match"<<endl;
    return kFALSE;
  }
  for(int i=0;i<swich_point;i++)
  {
    if(values[i] < cuts[i]) return kFALSE;
  }
  for(int i=swich_point;i<cuts.size();i++)
  {
    if(values[i] > cuts[i]) return kFALSE;
  }
  return kTRUE;
}

void DrawCen_FT0C_After(TH1* h_cen_FT0C_after, TString dataset, TString target)
{
  TCanvas *c_cent_FT0C_after = tool::GetCanvas(Form("c_cent_FT0C_after_%s_%s",dataset.Data(),target.Data()),xpos,ypos,cansizeX,cansizeY,0,1,0.05,0.08,0.14,0.03);
  c_cent_FT0C_after->cd();
  h_cen_FT0C_after->SetLineColor(46);
  tool::SetTitleTH1(h_cen_FT0C_after,"counts",0.07,0.8,"Centrality_FT0C",0.048,0.7);
  TLegend* leg_cent_FT0C_after = new TLegend(0.42,0.82,0.94,0.94);
  leg_cent_FT0C_after->AddEntry((TObject*)0,Form("FT0C < %.2f_%s",config::Cen_max_FT0C,dataset.Data()), "");
  leg_cent_FT0C_after->SetBorderSize(0);
  leg_cent_FT0C_after->SetFillStyle(0);
  leg_cent_FT0C_after->SetTextSize(0.04);
  leg_cent_FT0C_after ->SetTextFont(22);
  h_cen_FT0C_after->Draw();
  leg_cent_FT0C_after->Draw("SAME");
  TString saving_path_temp = Form("../output/%s_%s/",dataset.Data(),target.Data());
  tool::create_folder(saving_path_temp);
  TString saving_name_temp = Form("Cent_FT0C_after_%s_%s.pdf",dataset.Data(),target.Data());
  c_cent_FT0C_after->SaveAs(Form("%s%s",saving_path_temp.Data(),saving_name_temp.Data()));
}

void DrawCenFT0A_C_M(TH1* h_CenFT0A,TH1* h_CenFT0C,TH1* h_CenFT0M, TString dataset, TString target)
{
  TCanvas *canvas_cenFT0A_C_M = tool::GetCanvas(Form("Cen_compare_canvas_%s_%s",dataset.Data(),target.Data()),xpos,ypos,cansizeX,cansizeY,0,1,0.05,0.08,0.14,0.03);
  tool::SetTitleTH1(h_CenFT0A,"counts_candiadates",0.07,1,"percentile_FT0A_C_M",0.06,0.65);
  tool::SetTitleTH1(h_CenFT0C,"counts_candiadates",0.07,1,"percentile_FT0C_C_M",0.06,0.65);
  tool::SetTitleTH1(h_CenFT0M,"counts_candiadates",0.07,1,"percentile_FT0M_C_M",0.06,0.65);
  tool::SetAxisTH1(h_CenFT0A,0,0,0,0,0.05,0.05);
  tool::SetAxisTH1(h_CenFT0C,0,0,0,0,0.05,0.05);
  tool::SetAxisTH1(h_CenFT0M,0,0,0,0,0.05,0.05);
  h_CenFT0A->SetLineColorAlpha(kBlue,0.8);
  h_CenFT0C->SetLineColorAlpha(kRed,0.8);
  h_CenFT0M->SetLineColorAlpha(kGreen,0.8);
  canvas_cenFT0A_C_M->cd();
  h_CenFT0A->Draw();
  h_CenFT0C->Draw("SAME");
  h_CenFT0M->Draw("SAME");
  double ymax = TMath::Max(TMath::Max(h_CenFT0A->GetMaximum(),h_CenFT0C->GetMaximum()),h_CenFT0M->GetMaximum());
  h_CenFT0A->SetMaximum(ymax*1.2);
  h_CenFT0C->SetMaximum(ymax*1.2);
  h_CenFT0M->SetMaximum(ymax*1.2);

  TLegend *legend_cenFT0A_C_M = new TLegend(0.42,0.7,0.92,0.92);
  legend_cenFT0A_C_M->AddEntry(h_CenFT0A,Form("FT0A_selected:%s",dataset.Data()),"l");
  legend_cenFT0A_C_M->AddEntry(h_CenFT0C,Form("FT0C_selected:%s",dataset.Data()),"l");
  legend_cenFT0A_C_M->AddEntry(h_CenFT0M,Form("FT0M_selected:%s",dataset.Data()),"l");
  legend_cenFT0A_C_M->SetBorderSize(0);
  legend_cenFT0A_C_M->SetFillStyle(0);
  legend_cenFT0A_C_M->SetTextSize(0.04);
  legend_cenFT0A_C_M ->SetTextFont(22);
  legend_cenFT0A_C_M->Draw("SAME");

  TString saving_path = Form("../output/%s_%s/",dataset.Data(),target.Data());
  saving_path = tool::create_folder(saving_path);
  TString saving_name = Form("Candidatecen_compare_%s_%s.pdf",dataset.Data(),target.Data());
  canvas_cenFT0A_C_M->SaveAs(Form("%s%s",saving_path.Data(),saving_name.Data()));
}

void Draw_Compare_ITSClustersize(TH1* h_ITSclustersize_Pi, TH1* h_ITSclustersize_He3, TString dataset, TString target)
{
  TCanvas *canvas_ITSclustersize = tool::GetCanvas(Form("ITSclustersize_canvas_%s_%s",dataset.Data(),target.Data()),xpos,ypos,cansizeX,cansizeY,0,1,0.05,0.08,0.14,0.03);
  tool::SetTitleTH1(h_ITSclustersize_Pi,"Counts",0.07,1,"<ITSclustersize_Avg>",0.06,0.65);
  tool::SetTitleTH1(h_ITSclustersize_He3,"Counts",0.07,1,"<ITSclustersize_Avg>",0.06,0.65);
  tool::SetAxisTH1(h_ITSclustersize_Pi,0,0,0,0,0.05,0.05);
  tool::SetAxisTH1(h_ITSclustersize_He3,0,0,0,0,0.05,0.05);
  tool::SetMarkerTH1(h_ITSclustersize_Pi,"",86,1.5,2,2);
  tool::SetMarkerTH1(h_ITSclustersize_He3,"", 86,1.5,4,4);
  canvas_ITSclustersize->cd();
  h_ITSclustersize_Pi->Draw("");
  h_ITSclustersize_He3->Draw("SAME");
  TLegend *legend_ITSclustersize = new TLegend(0.42,0.7,0.92,0.92);
  legend_ITSclustersize->AddEntry(h_ITSclustersize_Pi,Form("#pi #leftarrow ^{3}_{#Lambda}H:%s",dataset.Data()),"l");
  legend_ITSclustersize->AddEntry(h_ITSclustersize_He3,Form("^{3}He #leftarrow ^{3}_{#Lambda}H:%s",dataset.Data()),"l");
  legend_ITSclustersize->SetBorderSize(0);
  legend_ITSclustersize->SetFillStyle(0);
  legend_ITSclustersize->SetTextSize(0.04);
  legend_ITSclustersize ->SetTextFont(22);
  legend_ITSclustersize->Draw("SAME");

  TString saving_path = Form("../output/%s_%s/",dataset.Data(),target.Data());
  saving_path = tool::create_folder(saving_path);
  TString saving_name = Form("ITSclustersize_compare_%s_%s.pdf",dataset.Data(),target.Data());
  canvas_ITSclustersize->SaveAs(Form("%s%s",saving_path.Data(),saving_name.Data()));
}

void ProcessInvmass(std::vector<std::vector<TH1F*>> h_mass_matter, std::vector<std::vector<TH1F*>> h_mass_anti, std::vector<std::vector<TH1F*>> h_mass_total, int isize, int jsize, Int_t Processmod,Bool_t PlotOnly, Bool_t DoProduction, TString dataset, TString target)
{
  for(int i=0;i<isize;i++)
  {
    for(int j=0;j<jsize;j++)
    {
      tool::SetTitleTH1(h_mass_matter[i][j],"Counts",0.07,1,"mass he3+#pi (Gev/c^{2})",0.06,0.65);
      tool::SetTitleTH1(h_mass_anti[i][j],  "Counts",0.07,1,"mass he3+#pi (Gev/c^{2})",0.06,0.65);
      tool::SetTitleTH1(h_mass_total[i][j], "Counts",0.07,1,"mass he3+#pi (Gev/c^{2})",0.06,0.65);
      tool::SetAxisTH1(h_mass_matter[i][j], 0.0,0.0,massmin,massmax,0.06,0.04);
      tool::SetAxisTH1(h_mass_anti[i][j],   0.0,0.0,massmin,massmax,0.06,0.04);
      tool::SetAxisTH1(h_mass_total[i][j],  0.0,0.0,massmin,massmax,0.06,0.04);
      tool::SetMarkerTH1(h_mass_matter[i][j],"Matter",86,1.5,2,2);
      tool::SetMarkerTH1(h_mass_anti[i][j],"Antimatter",  86,1.5,9,9);
      tool::SetMarkerTH1(h_mass_total[i][j],"Total", 86,1.5,4,4);
    }
  }
  double InitParam[10] = {20,2.99,0.0015,1,1,5,5,600,-200,50};
  TF1* fitfunc[isize][jsize];
  for(int i=0;i<isize;i++)
  {
    for(int j=0;j<jsize;j++)
    {
      fitfunc[i][j] = new TF1(Form("fitfunc_%d_%d", i, j),tool::DoubleSidedCrystalballFunctionPol2,massmin,massmax,10);
      fitfunc[i][j]->SetParameters(InitParam);
      fitfunc[i][j]->SetParLimits(0,0,1e5);
      fitfunc[i][j]->SetParLimits(1,2.985,2.992);
      fitfunc[i][j]->SetParLimits(2,0.001,0.0024);
      fitfunc[i][j]->SetParLimits(3,0.7,5);
      fitfunc[i][j]->SetParLimits(4,0.7,5);
      fitfunc[i][j]->SetParLimits(5,4.95,5);
      fitfunc[i][j]->SetParLimits(6,4.95,5);
    }
  }
  double rawyield[isize][jsize];
  double yieldmax_cen[isize];
  double fit_mean[isize][jsize];
  double fit_sigma[isize][jsize];
  double fit_mean_error[isize][jsize];
  double fit_sigma_error[isize][jsize];
  for(int i = 0; i < isize ; i++)
  {
    yieldmax_cen[i] = 0;
    for(int j = 0; j < jsize ; j++)
    {
      rawyield[i][j] = 0;
    }
  }
  if(Processmod == 1)
  {
    TCanvas *canvas_mass_total = tool::GetCanvas(Form("canvas_mass_total_%s_%s",dataset.Data(),target.Data()),xpos,ypos,1200,600,0,1,0.05,0.08,0.14,0.03);
    canvas_mass_total->Divide(jsize,isize);
    TF1* fitfunc_clone[isize][jsize];
    TF1* signal_func[isize][jsize];
    TF1* back_func[isize][jsize];
    TLegend *leg[isize][jsize];
    for(int i=0;i<isize;i++)
    {
      for(int j=0;j<jsize;j++)
      {
        canvas_mass_total->cd(jsize*i+j+1);
        gPad->SetGridy();
        double y_max = h_mass_total[i][j]->GetMaximum();
        h_mass_total[i][j]->SetMaximum(y_max*1.2);
        h_mass_total[i][j]->Draw("PE0");
        if(PlotOnly)
        {
          leg[i][j] = new TLegend(0.5,0.7,0.9,0.9);
          leg[i][j]->SetBorderSize(0);
          leg[i][j]->SetFillColor(0);
          leg[i][j]->SetTextFont(42);
          leg[i][j]->SetTextSize(0.05);
          leg[i][j]->AddEntry((TObject*)0,Form("%s",dataset.Data()),"");
          leg[i][j]->AddEntry(h_mass_total[i][j],"Matter + Antimatter","lep");
          leg[i][j]->Draw("SAME");
          tool::drawMyTextNDC(0.5,0.6,0.05,Form("Cen: %.2f-%.2f",config::Cenbin[i],config::Cenbin[i+1]),kRed);
          tool::drawMyTextNDC(0.5,0.5,0.05,Form("P_{t}: %.2f-%.2f",config::Ptbin[j],config::Ptbin[j+1]),kRed);
        }
        if(!PlotOnly)
        {
          ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(60000);
          h_mass_total[i][j]->Fit(fitfunc[i][j],"MREX0Q","I",massmin,massmax);
          double fitpara[10] = {0,};
          fitfunc[i][j]->GetParameters(fitpara);
          std::cout << "Fit parameters for fitfunc[" << i << "][" << j << "]:" << std::endl;
          for (int k = 0; k < 10; ++k) 
          {
            if (!(k == 9)) std::cout << "Parameter " << k << ": " << fitpara[k] <<std::endl;
            else std::cout << "Parameter " << k << ": " << fitpara[k] << "\n" <<std::endl;
          }
          double singnalpara[7] = {fitpara[0],fitpara[1],fitpara[2],fitpara[3],fitpara[4],fitpara[5],fitpara[6]};
          double backpara[3] = {fitpara[7],fitpara[8],fitpara[9]};
          fitfunc_clone[i][j] = (TF1*)fitfunc[i][j]->Clone(Form("fitfunc_clone_%d_%d",i,j));
          fitfunc_clone[i][j]->SetLineColor(4);
          fitfunc_clone[i][j]->SetLineStyle(1);
          fitfunc_clone[i][j]->SetLineWidth(2);
          signal_func[i][j] = new TF1(Form("singal_func_%d_%d",i,j),tool::SignalFunctionDoubleSidedCrystalball,massmin,massmax,7);
          signal_func[i][j]->SetParameters(singnalpara);
          signal_func[i][j]->SetLineColor(2);
          signal_func[i][j]->SetLineStyle(1);
          signal_func[i][j]->SetLineWidth(2);
          back_func[i][j] = new TF1(Form("back_func_%d_%d",i,j),tool::BackgroundFunctionPol2,massmin,massmax,3);
          back_func[i][j]->SetParameters(backpara);
          back_func[i][j]->SetLineColor(2);
          back_func[i][j]->SetLineStyle(2);
          back_func[i][j]->SetLineWidth(2);
          fitfunc_clone[i][j]->Draw("SAME");
          signal_func[i][j]->Draw("SAME");
          back_func[i][j]->Draw("SAME");
          //Legend
          leg[i][j] = new TLegend(0.6,0.5,0.9,0.7);
          leg[i][j]->SetBorderSize(0);
          leg[i][j]->SetFillColor(0);
          leg[i][j]->SetTextFont(42);
          leg[i][j]->SetTextSize(0.05);
          leg[i][j]->AddEntry(fitfunc_clone[i][j],"signal + bkg","l");
          leg[i][j]->AddEntry(signal_func[i][j],"signal","l");
          leg[i][j]->AddEntry(back_func[i][j],"bkg","l");
          leg[i][j]->Draw("SAME");
          tool::drawMyTextNDC(0.5,0.8,0.05,Form("PbPb, #sqrt{s_{NN}}=5.36 TeV, %.2f-%.2f%%",config::Cenbin[i],config::Cenbin[i+1]),kBlack);
          tool::drawMyTextNDC(0.5,0.7,0.05,Form("%.2f (Gev/c)< P_{t} <%.2f (Gev/c)",config::Ptbin[j],config::Ptbin[j+1]),kBlack);
          if(DoProduction)
          {
            double mean = fitfunc[i][j]->GetParameter(1);   
            double sigma = fitfunc[i][j]->GetParameter(2);
            double mean_error = fitfunc[i][j]->GetParError(1);
            double sigma_error = fitfunc[i][j]->GetParError(2);
            fit_mean[i][j] = mean;
            fit_sigma[i][j] = sigma;
            fit_mean_error[i][j] = mean_error;
            fit_sigma_error[i][j] = sigma_error;
            double signalMin = mean - 3 * sigma;
            double signalMax = mean + 3 * sigma;
            double totalCounts = h_mass_total[i][j]->Integral(h_mass_total[i][j]->FindBin(signalMin), h_mass_total[i][j]->FindBin(signalMax));
            double backgroundCounts = back_func[i][j]->Integral(signalMin, signalMax) / h_mass_total[i][j]->GetBinWidth(1);
            double signalCounts = totalCounts - backgroundCounts;
            rawyield[i][j] = signalCounts;
          }
        }
      }
    }
    TString saving_path = Form("../output/%s_%s/",dataset.Data(),target.Data());
    saving_path = tool::create_folder(saving_path);
    TString saving_name = Form("InvmassSpectrum_total_%s_%s.pdf",target.Data(),dataset.Data());
    canvas_mass_total->SaveAs(Form("%s%s",saving_path.Data(),saving_name.Data()));
  }
  else if(Processmod == 2)
  {
    
  }
  else if(Processmod == 3)
  {
    
  }
  if(DoProduction)
  {
    //plot fit mean and sigma
    xpos += 50;
    TCanvas* canvas_meansigma = tool::GetCanvas(Form("canvas_meansigma_%s_%s",dataset.Data(),target.Data()),xpos,ypos,900,800,0,0,0.05,0.08,0.14,0.03);
    canvas_meansigma->Divide(isize,2);
    TGraphErrors* E_mean[isize];
    TGraphErrors* E_sigma[isize];
    TH1D* h_mean_empty[isize];
    TH1D* h_sigma_empty[isize];
    for(int i = 0; i < isize; i++)
    {
      h_mean_empty[i] = new TH1D(Form("meanempty_cen_%d",i),"",config::nPtbin,config::Pt_bining);
      E_mean[i] = new TGraphErrors();
      h_sigma_empty[i] = new TH1D(Form("sigmaempty_cen_%d",i),"",config::nPtbin,config::Pt_bining);
      E_sigma[i] = new TGraphErrors();
    }
    for(int i =0; i < isize; i++)
    {
      canvas_meansigma->cd(i+1);
      for(int j = 0; j < jsize; j++)
      {
        E_mean[i]->SetPoint(j+1,h_mean_empty[i]->GetBinCenter(j+1),fit_mean[i][j]);
        E_mean[i]->SetPointError(j+1,h_mean_empty[i]->GetBinWidth(j+1)/2.0,fit_mean_error[i][j]);
      }
      tool::SetTitleTH1(h_mean_empty[i],"#mu_DSCB",0.07,0.5,"p_{t} (Gev/c^{2})",0.06,0.65);
      tool::SetAxisTH1(h_mean_empty[i],2.989,2.992,config::Ptbin[0],config::Ptbin[config::nPtbin],0.04,0.05);
      tool::SetMarkerTH1(E_mean[i],"",47,1.5,4,4);
      h_mean_empty[i]->Draw();
      E_mean[i]->Draw("SAMEPE0");
      tool::drawMyTextNDC(0.2,0.8,0.05,Form("PbPb, #sqrt{s_{NN}}=5.36 TeV"),kBlack);
      tool::drawMyTextNDC(0.2,0.7,0.05,Form("Cen: %.2f-%.2f",config::Cenbin[i],config::Cenbin[i+1]),kBlack);
      canvas_meansigma->cd(isize+i+1);
      for(int j = 0; j < jsize; j++)
      {
        E_sigma[i]->SetPoint(j+1,h_sigma_empty[i]->GetBinCenter(j+1),fit_sigma[i][j]);
        E_sigma[i]->SetPointError(j+1,h_sigma_empty[i]->GetBinWidth(j+1)/2.0,fit_sigma_error[i][j]);
      }
      tool::SetTitleTH1(h_sigma_empty[i],"#sigma_DSCB",0.07,0.5,"p_{t} (Gev/c^{2})",0.06,0.65);
      tool::SetAxisTH1(h_sigma_empty[i],0.0008,0.0024,config::Ptbin[0],config::Ptbin[config::nPtbin],0.04,0.05);
      tool::SetMarkerTH1(E_sigma[i],"",45,1.5,4,4);
      h_sigma_empty[i]->Draw();
      E_sigma[i]->Draw("SAMEPE0");
      tool::drawMyTextNDC(0.2,0.8,0.05,Form("PbPb, #sqrt{s_{NN}}=5.36 TeV"),kBlack);
      tool::drawMyTextNDC(0.2,0.7,0.05,Form("Cen: %.2f-%.2f",config::Cenbin[i],config::Cenbin[i+1]),kBlack);
    }
    TString saving_path_meansigma = Form("../output/%s_%s/",dataset.Data(),target.Data());
    saving_path_meansigma = tool::create_folder(saving_path_meansigma);
    TString saving_name_meansigma = Form("Fit_meansigma_pt_%s_%s.pdf",dataset.Data(),target.Data());
    canvas_meansigma->SaveAs(Form("%s%s",saving_path_meansigma.Data(),saving_name_meansigma.Data()));
    //plot raw yield
    xpos += 50;
    TCanvas* canvas_yield = tool::GetCanvas(Form("canvas_yield_%s_%s",dataset.Data(),target.Data()),xpos,ypos,900,400,0,0,0.05,0.08,0.14,0.03);
    canvas_yield->Divide(isize,1);
    TGraphErrors* E_yield[isize];
    TH1D* h_yield_empty[isize];
    for(int i = 0; i < isize; i++)
    {
      h_yield_empty[i] = new TH1D(Form("empty_cen_%d",i),"",config::nPtbin,config::Pt_bining);
      E_yield[i] = new TGraphErrors();
      yieldmax_cen[i] = *max_element(rawyield[i], rawyield[i] + jsize);
    }
    for(int i =0; i < isize; i++)
    {
      canvas_yield->cd(i+1);
      for(int j = 0; j < jsize; j++)
      {
        E_yield[i]->SetPoint(j+1,h_yield_empty[i]->GetBinCenter(j+1),rawyield[i][j]);
        E_yield[i]->SetPointError(j+1,h_yield_empty[i]->GetBinWidth(j+1)/2.0,sqrt(rawyield[i][j]));
      }
      tool::SetTitleTH1(h_yield_empty[i],"raw_yield",0.07,0.5,"p_{t} (Gev/c^{2})",0.06,0.65);
      //h_yield_empty[i]->GetXaxis()->SetTitleAlign(12);
      //h_yield_empty[i]->GetYaxis()->SetTitleAlign(12);
      h_yield_empty[i]->SetMaximum(2.0*yieldmax_cen[i]);
      tool::SetAxisTH1(h_yield_empty[i],0,2.0*yieldmax_cen[i],config::Ptbin[0],config::Ptbin[config::nPtbin],0.04,0.05);
      tool::SetMarkerTH1(E_yield[i],"",43,1.5,4,4);
      h_yield_empty[i]->Draw();
      E_yield[i]->Draw("SAMEPE0");
      //Legend 
      tool::drawMyTextNDC(0.2,0.8,0.05,Form("PbPb, #sqrt{s_{NN}}=5.36 TeV"),kBlack);
      tool::drawMyTextNDC(0.2,0.7,0.05,Form("Cen: %.2f-%.2f",config::Cenbin[i],config::Cenbin[i+1]),kBlack);
    }
    TString saving_path = Form("../output/%s_%s/",dataset.Data(),target.Data());
    saving_path = tool::create_folder(saving_path);
    TString saving_name = Form("Rawyield_pt_%s_%s.pdf",target.Data(),dataset.Data());
    canvas_yield->SaveAs(Form("%s%s",saving_path.Data(),saving_name.Data()));
  }
  
}

void Plot_QA_Parameter_distributions(std::vector<TH1F*> h_QA, TString dataset, TString target)
{
  for(int i = 0; i < h_QA.size(); i++)
  {
    TCanvas * canvas_QA = tool::GetCanvas(Form("canvas_QA_%s_%s_%d",dataset.Data(),target.Data(),i),xpos,ypos,500,400,0,1,0.05,0.08,0.14,0.03);
    h_QA[i]->Draw();
    TString hist_name = (TString)h_QA[i]->GetTitle(); 
    TString saving_path = Form("../output/%s_%s/Parameter_QA/",dataset.Data(),target.Data());
    saving_path = tool::create_folder(saving_path);
    TString saving_name = Form("%s_%s_%s.pdf",hist_name.Data(),dataset.Data(),target.Data());
    canvas_QA->SaveAs(Form("%s%s",saving_path.Data(),saving_name.Data()));
    xpos += 50;
  }
}


