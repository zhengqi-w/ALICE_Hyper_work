#include <iostream>
namespace config
{
  //bins for topological cuts
  //Centrality max
  const Float_t Cen_max_FT0C = 90;
  //Centralitybin
  const std::vector<Float_t> Cenbin = {0, 20, 60};
  const int nCenbin = 2;
  const Float_t Cen_bining[nCenbin+1] = {0, 20, 60};
  //Ptbin
  const std::vector<Float_t> Ptbin= {2, 3.5, 5, 8};
  const int nPtbin = 3;
  const Float_t Pt_bining[nPtbin+1] = {2, 3.5, 5, 8};
  //statical cut sets
  const Float_t eta_max_mother = 0.9;
  const Float_t pt_min_mother = 2;
  const Float_t ct_min = 1;//1
  const Float_t cpa_min = 0.99995;//0.99985
  const Float_t nsigma_min_he3 = -3;//-3
  const Float_t TPCsignal_max_pion = 1000;
  const Float_t TPCncls_min_he3 = 100;//100
  const Float_t pinTPC_min_he3 = 1;//1
  const Float_t pt_max_pion = 1.5;
  const Float_t clustersize_min_he3 = 4;
  const std::vector<Float_t> statical_cuts = {pt_min_mother, ct_min, cpa_min, nsigma_min_he3, TPCncls_min_he3, pinTPC_min_he3, clustersize_min_he3, eta_max_mother, TPCsignal_max_pion, pt_max_pion};
  const int swich_point = 7;
  const Float_t DCAPi_min = 0;
  const Float_t DCAHe3_min = 0;
  const Float_t TPCNcls_min_pi = 0; 

  
}