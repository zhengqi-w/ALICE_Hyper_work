#include "../include/toollib.h"
#include "../include/toollib.cpp"

#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TLeaf.h>

void listTreeAndLeafNames(const TString sDataset) {
    // Open the ROOT file
   ifstream initxt;
   initxt.open("../input/pathtoinputfile.txt");
   TString pathtofile = "";
   initxt >> pathtofile;
   TFile* inputfile = tool::FileReader(pathtofile.Data());
   if (inputfile == NULL) { cout << "::: Error ::: inputfile not found" << endl; return; }

    // Open output file
    std::ofstream outFile(Form("../output/treeandleafname_%s.txt",sDataset.Data()));
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open output file " << Form("../output/treeandleafname_%s.txt",sDataset.Data()) << std::endl;
        return;
    }

    // Access the first directory (file or subdirectory)
    TList   *keyList_file = inputfile->GetListOfKeys();
    TObject* obj_file = keyList_file->At(0);
    TKey* key_file = dynamic_cast<TKey*>(obj_file);
    TString dirName = (TString ) key_file->GetName();
    TDirectory *firstDir = (TDirectory*)inputfile->Get(Form("%s:/%s",inputfile->GetName(),dirName.Data()));
    if (!firstDir) {
        std::cerr << "Error: No directories found in the ROOT file" << std::endl;
        inputfile->Close();
        return;
    }

    // Iterate through the list of keys in the first directory
    TList* keyList = firstDir->GetListOfKeys();
    for (int i = 0; i < keyList->GetSize(); ++i) {
        TObject* obj = keyList->At(i);
        TKey* key = dynamic_cast<TKey*>(obj);
        if (key) {
            TObject* item = key->ReadObj();
            TTree* tree = dynamic_cast<TTree*>(item);
            if (tree) {
                // Print the tree name
                outFile << "Tree Name: " << tree->GetName() << " \n"<< std::endl;

                // Iterate through leaves and print their names
                TObjArray *branches = tree->GetListOfBranches();
                for (int j = 0; j < branches->GetEntries(); ++j) {
                    TBranch *branch = (TBranch*)branches->At(j);
                    std::string branchName = branch->GetName();
                    TLeaf *leaf = branch->GetLeaf(branchName.c_str());
                    if (leaf) {
                        std::string leafType = leaf->GetTypeName();
                        std::string leafName = leaf->GetName();
                        outFile << Form("Leaf_%03d Type and Name: ",j)<< Form("%s  %s;", leafType.c_str(), leafName.c_str()) << " \n" <<std::endl;
                    }
                }
            }
        }
    }

    // Clean up
    outFile.close();
    inputfile->Close();
}

