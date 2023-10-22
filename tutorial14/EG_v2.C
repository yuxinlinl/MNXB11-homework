// include C++ STL headers 
#include <iostream>
// include the fstream header
#include <fstream> 

using namespace std;
// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

void rootfuncgenerate(Int_t nEvents,Int_t nTracks,Double_t v2); // ROOT method (a bit dangerous since we don't know exactly what happens!)


//________________________________________________________________________
void rootfuncgenerate(Int_t nEvents,Int_t nTracks,Double_t v2) 
{
  cout << "Generating " << nEvents << " events" << endl << endl;
  
  // create histogram that we will fill with random values
  TH1D* hPhi = new TH1D("hPhi", "ROOT func generated v2 distribution;φ ; Counts", 
			100, 0, 2*TMath::Pi());
  
  // Define the function we want to generate
  TString funcString = Form("1+2*%f*cos(2*x)", v2);
  TF1* v2Func = new TF1("v2Func", funcString, 0, 2*TMath::Pi());
  
  Double_t phi[nTracks];//array to store phi angles

  //generate nTracks phi angles
  for(Int_t nt = 0; nt < nTracks; nt++){

    //Fill the array
    phi[nt] = v2Func->GetRandom();
  }
  // make a loop for the number of events
  for (Int_t n = 0; n < nEvents; n++){
    for(Int_t i = 0; i < nTracks; i++){
       hPhi->Fill(phi[i]);
       cout << n << " : " << phi[i] << endl;
  }
 }
  // Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // create canvas for hPhi
  TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
  hPhi->SetMinimum(0);
  hPhi->Draw();
  
  // create 1d function that we will use to fit our generated data to ensure
  // that the generation works
  TF1* fitFunc = new TF1("fitFunc", "[0]*(1+2*[1]*cos(2*x))", 0, 2*TMath::Pi());
  fitFunc->SetParameter(0, 1000);
  fitFunc->SetParameter(1,v2);
  fitFunc->SetLineColor(kRed);
  hPhi->Fit(fitFunc);
  
  // Save the canvas as a picture
  c1->SaveAs("v2_rootfunc.jpg");
  //Open output file
  ofstream file("phi_dist.dat");

  //Loop over events and tracks to write data to the file
  for (Int_t ne = 0; ne < nEvents; ne++){
    file << "Event " << ne << endl;
    for (Int_t nt = 0; nt < nTracks; nt++){
      file << nt << " : " << phi[nt] << endl;
    }
  }
  //CLose the file
  file.close();
}
