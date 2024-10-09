#include <iostream>
#include <vector>
#include <TH1F.h>
#include <TRandom3.h>
#include <TCanvas.h>

namespace config {
    const int nCenbin = 3;
    const int nPtbin = 4;
}

int main() {
    // 参数设置
    int massbinnum = 100;
    float massmin = 0.0;
    float massmax = 10.0;

    // 初始化TH1F指针的二维数组
    std::vector<std::vector<TH1F*>> h_Invmass_total(config::nCenbin, std::vector<TH1F*>(config::nPtbin));

    // 初始化每个TH1F
    for (int i = 0; i < config::nCenbin; i++) {
        for (int j = 0; j < config::nPtbin; j++) {
            h_Invmass_total[i][j] = new TH1F(Form("h_Invmass_total_%d_%d", i, j),
                                             Form("Invariant Mass Distribution Cenbin %d Ptbin %d", i, j),
                                             massbinnum, massmin, massmax);
        }
    }

    // 随机生成一些数据并填充到直方图
    TRandom3 rand;
    for (int i = 0; i < config::nCenbin; i++) {
        for (int j = 0; j < config::nPtbin; j++) {
            for (int k = 0; k < 1000; k++) {
                h_Invmass_total[i][j]->Fill(rand.Uniform(massmin, massmax));
            }
        }
    }

    // 打印每个TH1F的名称和内容检查
    for (int i = 0; i < config::nCenbin; i++) {
        for (int j = 0; j < config::nPtbin; j++) {
            std::cout << "Histogram name: " << h_Invmass_total[i][j]->GetName() << std::endl;
            std::cout << "Entries: " << h_Invmass_total[i][j]->GetEntries() << std::endl;
        }
    }

    // 可视化每个TH1F
    TCanvas* c = new TCanvas("c", "Histograms", 800, 600);
    c->Divide(config::nPtbin, config::nCenbin);
    for (int i = 0; i < config::nCenbin; i++) {
        for (int j = 0; j < config::nPtbin; j++) {
            c->cd(i * config::nPtbin + j + 1);
            h_Invmass_total[i][j]->Draw();
        }
    }
    c->SaveAs("histograms.png");

    return 0;
}
