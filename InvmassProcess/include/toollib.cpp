#include "../include/toollib.h"
#include <iostream>

using namespace std;
tool ::tool()
{

}
//_______________________________________________________________________________________________________________________
tool ::~tool()
{
    
}
//_______________________________________________________________________________________________________________________
TFile* tool::FileReader(const TString &filename)
{
  cout<< "\n Reading File: " << filename.Data() << endl;
  TFile *f1 = TFile::Open(Form("%s",filename.Data()),"READ");
  if(!f1)
  {
    cout<<" ::: ERROR ::: \n Could not find the file, Check name or Path! \n Exit!"<<endl; return nullptr;
  }
  if(f1->IsOpen())
  {
    cout<<" Opening File: "<<f1->GetName()<<endl;
  }
  else
  {
    cout<<" ::: WARNING ::: \n Could not open the file! check path or if file is corrupt? \n Exit!"<<endl; return nullptr;
  }
  return f1;
}
//_______________________________________________________________________________________________________________________
void tool::SetTreeBranchAddress(TTree *tree, std::vector<Int_t*>BranchAddress_int, std::vector<Float_t*>BranchAddress_float, std::vector<Double_t*>BranchAddress_double, std::vector<UChar_t*> BranchAddress_uchar, std::vector<UShort_t*> BranchAddress_ushort, std::vector<UInt_t*> BranchAddress_uint, std::vector<Bool_t*> BranchAddress_bool,std::vector<TBranch*>Branches)
{
  size_t intIdx = 0, floatIdx = 0, doubleIdx = 0, ucharIdx = 0, ushortIdx = 0, uintIdx = 0, boolIdx = 0;
  TObjArray *branches = tree->GetListOfBranches();
  if((BranchAddress_int.size()+BranchAddress_float.size()+BranchAddress_double.size()+BranchAddress_uchar.size()+BranchAddress_ushort.size()+BranchAddress_uint.size()+BranchAddress_bool.size()) != branches->GetEntries() || Branches.size() != branches->GetEntries())
  {
    cout<<" ::: ERROR ::: \n Branch Address and Branches size does not match the given Tree! \n Exit!"<<endl; return;
  }
  for(Int_t i=0; i<branches->GetEntries(); ++i)
  {
    TBranch *branch = (TBranch*)branches->At(i);
    std::string branchName = branch->GetName();
    TLeaf *leaf = branch->GetLeaf(branchName.c_str());
    std::string leafType = leaf->GetTypeName();
    if(leafType == "Int_t")
    {
      tree->SetBranchAddress(branchName.c_str(), BranchAddress_int[intIdx], &Branches[i]);
      intIdx++;
    }
    else if(leafType == "Float_t")
    {
      tree->SetBranchAddress(branchName.c_str(), BranchAddress_float[floatIdx], &Branches[i]);
      floatIdx++;
    }
    else if(leafType == "Double_t")
    {
      tree->SetBranchAddress(branchName.c_str(), BranchAddress_double[doubleIdx], &Branches[i]);
      doubleIdx++;
    }
    else if(leafType == "UChar_t")
    {
      tree->SetBranchAddress(branchName.c_str(), BranchAddress_uchar[ucharIdx], &Branches[i]);
      ucharIdx++;
    }
    else if(leafType == "UShort_t")
    {
      tree->SetBranchAddress(branchName.c_str(), BranchAddress_ushort[ushortIdx], &Branches[i]);
      ushortIdx++;
    }
    else if(leafType == "UInt_t")
    {
      tree->SetBranchAddress(branchName.c_str(), BranchAddress_uint[uintIdx], &Branches[i]);
      uintIdx++;
    }
    else if(leafType == "Bool_t")
    {
      tree->SetBranchAddress(branchName.c_str(), BranchAddress_bool[boolIdx], &Branches[i]);
      boolIdx++;
    }
    else
    {
      cout<<" ::: ERROR ::: \n Branch Type not supported! \n Exit!"<<endl; return;
    }
  }
  //cout<< " Branch Address set successfully!" << endl;
}
//_______________________________________________________________________________________________________________________
TString tool::create_folder(const TString& path) 
{
  std::filesystem::path folder_path((std::string)path);
  if (!std::filesystem::exists(folder_path)) 
  {
    std::filesystem::create_directories(folder_path);
  }
  return (TString)path;
}
//_______________________________________________________________________________________________________________________
TCanvas* tool::GetCanvas(TString title,int xpos,int ypos,int sizeX,int sizeY,Bool_t gridx,Bool_t gridy,float topMgn,float botMgn,float leftMgn,float rightMgn)
{
  TCanvas *c1 = new TCanvas(title,title,xpos,ypos,sizeX,sizeY);
  //c1->SetCanvasSize(sizeX,sizeY);
  //c1->SetTitle(title);
  c1->SetTopMargin(topMgn);
  c1->SetRightMargin(rightMgn);
  c1->SetLeftMargin(leftMgn);
  c1->SetBottomMargin(botMgn);
  if(gridx)
    c1->SetGridx();
  if(gridy)
    c1->SetGridy();
  return c1;
}
//_______________________________________________________________________________________________________________________
TPad* tool::GetPad(TString name,float xpos1,float ypos1,float xpos2,float ypos2,float topMar,float botMar,float leftMar,float rightMar)
{
  TPad *tpad = new TPad(name,"",xpos1,ypos1,xpos2,ypos2);
  //tpad->Draw();
  //tpad->cd();
  tpad->SetFillColor(0);
  tpad->SetBorderMode(0);
  tpad->SetBorderSize(2);
  tpad->SetTicks(1,1);
  tpad->SetFrameBorderMode(0);
  tpad->SetFrameBorderMode(0);

  tpad->SetRightMargin(rightMar);
  tpad->SetTopMargin(topMar);
  tpad->SetLeftMargin(leftMar);
  tpad->SetBottomMargin(botMar);
  return tpad;
}
//_______________________________________________________________________________________________________________________
void tool::SetMarkerTH1(TH1 *h1,TString hTitle,int markSyle,float markSize,int markColor,int lineColor)
{
  h1->SetTitle(hTitle);
  h1->SetMarkerStyle(markSyle);
  h1->SetMarkerSize(markSize);
  h1->SetMarkerColor(markColor);
  h1->SetLineColor(lineColor);
}
//_______________________________________________________________________________________________________________________
void tool::SetMarkerTH1(TGraphErrors *h1,TString hTitle,int markSyle,float markSize,int markColor,int lineColor)
{
  h1->SetTitle(hTitle);
  h1->SetMarkerStyle(markSyle);
  h1->SetMarkerSize(markSize);
  h1->SetMarkerColor(markColor);
  h1->SetLineColor(lineColor);
}
//_______________________________________________________________________________________________________________________
void tool::SetMarkerTH1(TH2 *h1,TString hTitle,int markSyle,float markSize,int markColor,int lineColor)
{
  h1->SetTitle(hTitle);
  h1->SetMarkerStyle(markSyle);
  h1->SetMarkerSize(markSize);
  h1->SetMarkerColor(markColor);
  h1->SetLineColor(lineColor);
}
//_______________________________________________________________________________________________________________________
void tool::SetTitleTH1(TH1 *h1,TString yTitle,float yTileSize,float yOffset,TString xTitle,float xTileSize,float xOffset)
{
  h1->GetYaxis()->SetTitle(yTitle);
  h1->GetYaxis()->SetTitleSize(yTileSize);
  h1->GetYaxis()->SetTitleOffset(yOffset);
  h1->GetYaxis()->CenterTitle(true);
  h1->GetYaxis()->SetTitleFont(42);
  h1->GetXaxis()->SetTitle(xTitle);
  h1->GetXaxis()->SetTitleSize(xTileSize);
  h1->GetXaxis()->SetTitleOffset(xOffset);
  h1->GetXaxis()->CenterTitle(true);
  h1->GetXaxis()->SetTitleFont(42);
}
//_______________________________________________________________________________________________________________________
void tool::SetTitleTH1(TH2 *h1,TString yTitle,float yTileSize,float yOffset,TString xTitle,float xTileSize,float xOffset)
{
  h1->GetYaxis()->SetTitle(yTitle);
  h1->GetYaxis()->SetTitleSize(yTileSize);
  h1->GetYaxis()->SetTitleOffset(yOffset);
  h1->GetYaxis()->CenterTitle(true);
  h1->GetYaxis()->SetTitleFont(42);
  h1->GetXaxis()->SetTitle(xTitle);
  h1->GetXaxis()->SetTitleSize(xTileSize);
  h1->GetXaxis()->SetTitleOffset(xOffset);
  h1->GetXaxis()->CenterTitle(true);
  h1->GetXaxis()->SetTitleFont(42);
}
//_______________________________________________________________________________________________________________________
void tool::SetAxisTH1(TH1 *h1,float yAxisLow,float yAxisHigh,float xAxisLow,float xAxisHigh,float yLabelsize,float xLabelsize)
{
  if(!((xAxisLow == 0) && (xAxisHigh == 0)))
  {
    h1->GetXaxis()->SetRangeUser(xAxisLow,xAxisHigh);
  }
  if(!((yAxisLow == 0) && (yAxisHigh == 0)))
  {
    h1->GetYaxis()->SetRangeUser(yAxisLow,yAxisHigh);
  }
  h1->GetXaxis()->SetLabelFont(42);
  h1->GetXaxis()->SetLabelSize(xLabelsize);
  h1->GetYaxis()->SetLabelFont(42);
  h1->GetYaxis()->SetLabelSize(yLabelsize);
}
//_______________________________________________________________________________________________________________________
void tool::SetAxisTH1(TH2 *h1,float yAxisLow,float yAxisHigh,float xAxisLow,float xAxisHigh,float yLabelsize,float xLabelsize)
{
  h1->GetYaxis()->SetRangeUser(yAxisLow,yAxisHigh);
  h1->GetXaxis()->SetRangeUser(xAxisLow,xAxisHigh);
  h1->GetXaxis()->SetLabelFont(42);
  h1->GetXaxis()->SetLabelSize(xLabelsize);
  h1->GetYaxis()->SetLabelFont(42);
  h1->GetYaxis()->SetLabelSize(yLabelsize);
}
//_______________________________________________________________________________________________________________________
void tool::SetAxisTH1(TH2 *h1,float yAxisLow,float yAxisHigh,float xAxisLow,float xAxisHigh,float yLabelsize,float xLabelsize,float zLabelsize,float zLabOffset)
{
  h1->GetYaxis()->SetRangeUser(yAxisLow,yAxisHigh);
  if(!((xAxisLow == 0) && (xAxisHigh == 0)))
  {
    h1->GetXaxis()->SetRangeUser(xAxisLow,xAxisHigh);
  }
  h1->GetXaxis()->SetLabelFont(42);
  h1->GetXaxis()->SetLabelSize(xLabelsize);
  h1->GetYaxis()->SetLabelFont(42);
  h1->GetYaxis()->SetLabelSize(yLabelsize);
  h1->GetZaxis()->SetLabelFont(42);
  h1->GetZaxis()->SetLabelSize(zLabelsize);
  h1->GetZaxis()->SetLabelOffset(zLabOffset);  
  }
//_______________________________________________________________________________________________________________________
void tool::drawMyline(Float_t xstrt,Float_t ystrt,Float_t xend,Float_t yend,Int_t iStyle,Int_t iWidth,Int_t icol)
{

  TLine *line = new TLine(xstrt, ystrt, xend, yend);
  line->SetLineStyle(iStyle);
  line->SetLineWidth(iWidth);
  line->SetLineColor(icol);
  line->Draw();
 
}
//_______________________________________________________________________________________________________________________
void tool::drawMyText(Float_t xPos, Float_t yPos, Float_t size, TString text)
{
  TLatex *tex = new TLatex(xPos,yPos,text.Data());
  tex->SetTextFont(42);
  tex->SetTextSize(size);
  tex->SetLineWidth(2);
  tex->Draw();
}
//_______________________________________________________________________________________________________________________
void tool::drawMyTextNDC(Float_t xPos, Float_t yPos, Float_t size, TString text)
{
  TLatex *tex = new TLatex();
  tex->SetTextFont(42);
  tex->SetTextSize(size);
  tex->SetLineWidth(2);
  tex->DrawLatexNDC(xPos,yPos,text.Data());
}
//_______________________________________________________________________________________________________________________
void tool::drawMyTextNDC(Float_t xPos, Float_t yPos, Float_t size, TString text,Color_t col)
{
  TLatex *tex = new TLatex();
  tex->SetTextFont(42);
  tex->SetTextSize(size);
  tex->SetLineWidth(2);
  tex->SetTextColor(col);
  tex->DrawLatexNDC(xPos,yPos,text.Data());
}
//_______________________________________________________________________________________________________________________
void tool::drawBox(Float_t xstart,Float_t ystart,Float_t xstop,Float_t ystop, Int_t color, Int_t style)
{

  /// bottom edge:
  TLine *line1 = new TLine(xstart,ystart,xstop,ystart);
  line1->SetLineColor(color);
  line1->SetLineStyle(style);
  line1->Draw();
  /// top edge:
  TLine *line2 = new TLine(xstart,ystop,xstop,ystop);
  line2->SetLineColor(color);
  line2->SetLineStyle(style);
  line2->Draw();
  /// left edge:
  TLine *line3 = new TLine(xstart,ystart,xstart,ystop);
  line3->SetLineColor(color);
  line3->SetLineStyle(style);
  line3->Draw();
  /// right edge:
  TLine *line4 = new TLine(xstop,ystart,xstop,ystop);
  line4->SetLineColor(color);
  line4->SetLineStyle(style);
  line4->Draw();  
}
//_______________________________________________________________________________________________________________________
Float_t tool::CalculateCosPointingAngle(Float_t x1,Float_t y1,Float_t z1, Float_t px, Float_t py, Float_t pz)
{
  Float_t x = x1;
  Float_t y = y1;
  Float_t z = z1;
  Float_t norm = TMath::Sqrt(x*x + y*y + z*z);
  Float_t norm_v = TMath::Sqrt(px*px + py*py + pz*pz);
  Float_t dotproduct = x*px + y*py + z*pz;
  Float_t cosPointingAngle = dotproduct/(norm*norm_v);
  return cosPointingAngle;
}
//_______________________________________________________________________________________________________________________
Double_t tool::DoubleSidedCrystalballFunctionPol2(double *x, double *par) 
{
  // CB parameters
  double norm   = par[0];
  double mean   = par[1];
  double sigma  = par[2];
  double alpha_l = par[3];
  double alpha_h = par[4];
  double n_l    = par[5];
  double n_h    = par[6];
  
  // Pol2 parameters
  double c0 = par[7];
  double c1 = par[8];
  double c2 = par[9];

  // CB for signal
  double t = (x[0] - mean) / sigma;
  double signal = 0.0;

  if (-alpha_l <= t && t <= alpha_h) 
  {
      // Gaussian core
      signal = norm * TMath::Exp(-0.5 * t * t);
  } else if (t < -alpha_l) 
  {
      // Left tail
      double Alow = TMath::Power(n_l / alpha_l, n_l) * TMath::Exp(-0.5 * alpha_l * alpha_l);
      double Blow = (n_l / alpha_l) - alpha_l;
      signal = norm * Alow * TMath::Power(Blow - t, -n_l);
  } else if (t > alpha_h) 
  {
      // Right tail
      double Ahigh = TMath::Power(n_h / alpha_h, n_h) * TMath::Exp(-0.5 * alpha_h * alpha_h);
      double Bhigh = (n_h / alpha_h) - alpha_h;
      signal = norm * Ahigh * TMath::Power(Bhigh + t, -n_h);
  }

  // Pol2 for background
  double bkg = c2 * x[0] * x[0] + c1 * x[0] + c0;

  // Return the sum of signal and background
  return signal + bkg;
}
//_______________________________________________________________________________________________________________________
Double_t tool::SignalFunctionDoubleSidedCrystalball(double *x, double *par) 
{
  double norm   = par[0];
  double mean   = par[1];
  double sigma  = par[2];
  double alpha_l = par[3];
  double alpha_h = par[4];
  double n_l    = par[5];
  double n_h    = par[6];
  double t = (x[0] - mean) / sigma;
  double signal = 0.0;
  if (-alpha_l <= t && t <= alpha_h) 
  {
      // Gaussian core
      signal = norm * TMath::Exp(-0.5 * t * t);
  } else if (t < -alpha_l) 
  {
      // Left tail
      double Alow = TMath::Power(n_l / alpha_l, n_l) * TMath::Exp(-0.5 * alpha_l * alpha_l);
      double Blow = (n_l / alpha_l) - alpha_l;
      signal = norm * Alow * TMath::Power(Blow - t, -n_l);
  } else if (t > alpha_h) 
  {
      // Right tail
      double Ahigh = TMath::Power(n_h / alpha_h, n_h) * TMath::Exp(-0.5 * alpha_h * alpha_h);
      double Bhigh = (n_h / alpha_h) - alpha_h;
      signal = norm * Ahigh * TMath::Power(Bhigh + t, -n_h);
  }
  return signal;
}
//_______________________________________________________________________________________________________________________
Double_t tool::BackgroundFunctionPol2(double *x, double *par) 
{
  double c0 = par[0];
  double c1 = par[1];
  double c2 = par[2];

  return c2 * x[0] * x[0] + c1 * x[0] + c0;
}
//_______________________________________________________________________________________________________________________


