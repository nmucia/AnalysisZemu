#define AnalyzerPS_cxx
// The class definition in AnalyzerPS.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("AnalyzerPS.C")
// Root > T->Process("AnalyzerPS.C","some options")
// Root > T->Process("AnalyzerPS.C+")
//

#include "AnalyzerPS.h"
#include <TH2.h>
#include <TStyle.h>


void AnalyzerPS::Begin(TTree * /*tree*/)
{
  filetype=0;
  IS_DATA=false;
  larks=0;
  //MCfile=1; 
  muCorrector = new rochcor2012();
 

 if(filetype==2)
    {
      long a,b;
      cout<<"ddddddddd"<<endl;
      std::ifstream infile("/uscms_data/d3/nmucia2/dblcountfiles/SMD.txt");
      if(infile.is_open())
	{
	  while (infile>>a>>b)  
	    {
	      //	      cout<<a<<" "<<b<<endl;
	      foo=make_pair(a,b);
	      oldevents.push_back(foo);
	    }
	}
      sort(oldevents.begin(), oldevents.end());
    }
  f_muisorewe = new TFile("MuonEfficiencies_ISO_Run_2012ReReco_53X.root", "OPEN"); 
  _isorewe[0] = (TGraphErrors*)f_muisorewe->Get("DATA_over_MC_combRelIsoPF04dBeta<012_Tight_pt_abseta<0.9");
  _isorewe[1] = (TGraphErrors*)f_muisorewe->Get("DATA_over_MC_combRelIsoPF04dBeta<012_Tight_pt_abseta0.9-1.2");
  _isorewe[2] = (TGraphErrors*)f_muisorewe->Get("DATA_over_MC_combRelIsoPF04dBeta<012_Tight_pt_abseta1.2-2.1");
  _isorewe[3] = (TGraphErrors*)f_muisorewe->Get("DATA_over_MC_combRelIsoPF04dBeta<012_Tight_pt_abseta2.1-2.4");
  f_muisorewe->Close();

  f_muidrewe = new TFile("MuonEfficiencies_Run2012ReReco_53X.root", "OPEN"); 
  _idrewe[0] = (TGraphErrors*)f_muidrewe->Get("DATA_over_MC_Tight_pt_abseta<0.9");
  _idrewe[1] = (TGraphErrors*)f_muidrewe->Get("DATA_over_MC_Tight_pt_abseta0.9-1.2");
  _idrewe[2] = (TGraphErrors*)f_muidrewe->Get("DATA_over_MC_Tight_pt_abseta1.2-2.1");
      _idrewe[3] = (TGraphErrors*)f_muidrewe->Get("DATA_over_MC_Tight_pt_abseta2.1-2.4");  
  f_muidrewe->Close();       
  f_elrewe = new TFile("electrons_scale_factors.root", "OPEN"); 
  _elrewe = (TH2F*)f_elrewe->Get("electronsDATAMCratio_FO_ID_ISO");

 //Madgraph forr 2012 DoubleMu C
  

  f = new TFile("rootfiles/outfileTW.root","RECREATE");           



  /*
if(MCfile==1)
  {
    weights[70]={
      0.291545,
      0.227707,
      0.335468,
      0.302465,
      0.297379,
      0.522843,
      0.415166,
      0.420852,
      0.594346,
      0.885749,
      1.26379,
      1.60555,
      1.66451,
      1.48817,
      1.28037,
      1.12133,
      1.04736,
      1.02398,
      1.04326,
      1.09364,
      1.13989,
      1.17122,
      1.18878,
      1.19121,
      1.17746,
      1.13489,
      1.06959,
      0.979838,
      0.872769,
      0.751919,
      0.626006,
      0.505877,
      0.393746,
      0.300135,
      0.217398,
      0.150956,
      0.100377,
      0.064226,
      0.0392567,
      0.0238096,
      0.014123,
      0.00832263,
      0.0049879,
      0.00305456,
      0.00197542,
      0.0013562,
      0.000976246,
      0.000750864,
      0.000606018,
      0.000491019,
      0.00043391,
      0.000375931,
      0.0003277,
      0.000306953,
      0.000284736,
      0.000246177,
      0.000211898,
      0.000204152,
      0.000158951,
      0.000341641,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0

    };
  }

if(MCfile==2)
  {
     weights[70]={
      0.203918,
0.280091,
0.38974,
0.331493,
0.298871,
0.520424,
0.411246,
0.419909,
0.591984,
0.89478,
1.27703,
1.61219,
1.66609,
1.50169,
1.28773,
1.1272,
1.04556,
1.02812,
1.04819,
1.09716,
1.14222,
1.17487,
1.1923,
1.19424,
1.17847,
1.1297,
1.06873,
0.977302,
0.868024,
0.746,
0.622732,
0.504105,
0.392784,
0.298446,
0.213667,
0.149793,
0.0996344,
0.0627497,
0.0389887,
0.0232458,
0.0138045,
0.00809082,
0.00485627,
0.00298571,
0.0019049,
0.00131002,
0.000948511,
0.000722666,
0.000561008,
0.000491535,
0.000403371,
0.000347891,
0.000298485,
0.000287582,
0.000240339,
0.000219928,
0.000222314,
0.000164859,
0.000175731,
0.000268827,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0

     };
  }
if(MCfile==3)
  {
      weights[70]={
      0,
      0,
      0,
      0.0950039,
      0.138936,
      1.12509,
      0.394119,
      0.405007,
      0.52372,
      0.829041,
      1.18514,
      1.60989,
      1.59931,
      1.32782,
      1.14246,
      1.1097,
      0.965382,
      0.986245,
      1.00461,
      1.06121,
      1.10876,
      1.10133,
      1.18908,
      1.22836,
      1.22658,
      1.13908,
      1.14918,
      1.09031,
      0.885819,
      0.866404,
      0.674173,
      0.550461,
      0.419268,
      0.31741,
      0.289055,
      0.174235,
      0.113551,
      0.0735609,
      0.05367,
      0.02649,
      0.0163259,
      0.00954841,
      0.00574519,
      0.00304637,
      0.00238975,
      0.00175508,
      0.00151187,
      0.00103393,
      0.000679137,
      0.000741847,
      0.000572557,
      0.000476274,
      0.000447927,
      0.000562008,
      0,
      0.000218372,
      6.72257e-05,
      0,
      4.91738e-05,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0

     };
  }
if(MCfile==4)
  {
  weights[70]={
0.137415,
0.121636,
0.258258,
0.630441,
0.329276,
0.479959,
0.445799,
0.409461,
0.58484,
0.917204,
1.24911,
1.61568,
1.62394,
1.52692,
1.30098,
1.12894,
1.04155,
1.00775,
1.05177,
1.08248,
1.13499,
1.16518,
1.21073,
1.19456,
1.17526,
1.12911,
1.06196,
0.977012,
0.875399,
0.7461,
0.628265,
0.510214,
0.40089,
0.295261,
0.224149,
0.147102,
0.0973747,
0.0664454,
0.0401442,
0.0247427,
0.013659,
0.00832307,
0.00491053,
0.00294335,
0.00185624,
0.00141246,
0.000940566,
0.000762343,
0.000573969,
0.000576897,
0.000356199,
0.000302604,
0.000228648,
0.000174818,
0.00023322,
0.000181138,
0.000148702,
9.05215e-05,
0.000163157,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0
 };
  }
if(MCfile==5)
  {
      weights[70]={
      0,
      0.199772,
      0.377027,
      0.31859,
      0.302844,
      0.510915,
      0.429537,
      0.404236,
      0.570785,
      0.884785,
      1.28372,
      1.57436,
      1.66374,
      1.46586,
      1.28369,
      1.11761,
      1.02756,
      1.01015,
      1.04675,
      1.08372,
      1.13925,
      1.1707,
      1.18621,
      1.19017,
      1.19504,
      1.12823,
      1.0563,
      0.976784,
      0.893089,
      0.761551,
      0.638589,
      0.516794,
      0.397877,
      0.312445,
      0.214385,
      0.157585,
      0.101942,
      0.0655436,
      0.0413829,
      0.0236911,
      0.0148912,
      0.00834674,
      0.00519986,
      0.00303758,
      0.00185546,
      0.00150179,
      0.000964531,
      0.000713192,
      0.000686755,
      0.000481259,
      0.000396198,
      0.000458008,
      0.000250349,
      0.000226857,
      0.000255355,
      0.000297496,
      0.000293068,
      0.000178404,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0
     };     
    }
    if(MCfile==6)
      {
	  weights[70]={
	  0.222879,
0,
0.418879,
0.383451,
0.287574,
0.518976,
0.420828,
0.43071,
0.606598,
0.917725,
1.25825,
1.60116,
1.68683,
1.49599,
1.28237,
1.12865,
1.02961,
1.02369,
1.03271,
1.10677,
1.12371,
1.17705,
1.20257,
1.20393,
1.1676,
1.14101,
1.06661,
0.973378,
0.871803,
0.759375,
0.627964,
0.506604,
0.394131,
0.291779,
0.213238,
0.147696,
0.101908,
0.0646001,
0.0378155,
0.0237596,
0.01391,
0.00839865,
0.0048184,
0.00311466,
0.00191139,
0.00136989,
0.000973103,
0.000806397,
0.00057372,
0.000499036,
0.000366089,
0.000397721,
0.000336355,
0.000362937,
0.000246697,
0.000220346,
0.000197334,
0.000220231,
0.000158779,
0.000470117,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0

	 };
      }
    if(MCfile==7)
      {
	  weights[70]={
	  0.201523,
	  0.356767,
	  0.27545,
	  0.34671,
	  0.38267,
	  0.513241,
	  0.4329,
	  0.434912,
	  0.590702,
	  0.903646,
	  1.2679,
	  1.61852,
	  1.65907,
	  1.48784,
	  1.29171,
	  1.12613,
	  1.05215,
	  1.02827,
	  1.05083,
	  1.09413,
	  1.15072,
	  1.16145,
	  1.17603,
	  1.1804,
	  1.16907,
	  1.13198,
	  1.07001,
	  0.977125,
	  0.863408,
	  0.74564,
	  0.626435,
	  0.504273,
	  0.39217,
	  0.298674,
	  0.215021,
	  0.150707,
	  0.102891,
	  0.0643313,
	  0.0381549,
	  0.0243249,
	  0.0142938,
	  0.00806898,
	  0.00487656,
	  0.00306445,
	  0.0020701,
	  0.00135217,
	  0.000932531,
	  0.000749032,
	  0.000573792,
	  0.000458868,
	  0.000407709,
	  0.000359613,
	  0.000315119,
	  0.000321727,
	  0.000213765,
	  0.000335551,
	  0.000206598,
	  0.000298693,
	  0.000205093,
	  0.000425072,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0
	  
	 };
      }

*/
  //  float xlow[8] = {.0035,.0035,.030,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.025,.01,.01,.01,.01,.01,.05,.1,.5,1};

   Float_t xlow[35] = {0.00,0.004,0.008,0.012,0.016,0.020,0.024,0.029,0.034,0.039,0.045,0.051,0.057,0.064,0.072,0.081,0.091,0.102,0.114,0.128,0.145,0.165,0.189,0.219,0.258,0.312,.391,.524,.695,.918,1.153,1.496,1.947,2.522,3.277};
  Float_t invmassmm[31] ={52,56,60,64,68,72,76,80,82,84,85,86,87,88,89,90,91,92,93,94,95,96,98,100,104,108,112,116,120,124,128};
  h_jet_pt = new TH1D("h_jet_pt","jet pt", 100, 0, 1000.);
  // h_jet_pt_50 = new TH1D("h_jet_pt_50","jet pt, qT>50", 100, 0, 1000.);
  // h_jet_pt_100 = new TH1D("h_jet_pt_100","jet pt, qT>100", 100, 0, 1000.);
  // h_jet_pt_200 = new TH1D("h_jet_pt_200","jet pt, qT>200", 100, 0, 1000.);
  // h_jet_pt_300 = new TH1D("h_jet_pt_300","jet pt, qT>300", 100, 0, 1000.);
  // h_jet_pt_500 = new TH1D("h_jet_pt_500","jet pt, qT>500", 100, 0, 1000.);
  //  h_jet_pt_700 = new TH1D("h_jet_pt_700","jet pt, qT>700", 100, 0, 1000.);
  h_jet_lead_pt = new TH1D("h_jet_lead_pt","lead jet pt", 100, 0, 1000.);
  // h_jet_lead_pt_50 = new TH1D("h_jet_lead_pt_50","lead jet pt, qT>50", 100, 0, 1000.);
  // h_jet_lead_pt_100 = new TH1D("h_jet_lead_pt_100","lead jet pt, qT>100", 100, 0, 1000.);
  // h_jet_lead_pt_200 = new TH1D("h_jet_lead_pt_200","lead jet pt, qT>200", 100, 0, 1000.);
  // h_jet_lead_pt_300 = new TH1D("h_jet_lead_pt_300","lead jet pt, qT>300", 100, 0, 1000.);
  // h_jet_lead_pt_500 = new TH1D("h_jet_lead_pt_500","lead jet pt, qT>500", 100, 0, 1000.);
  //  h_jet_lead_pt_700 = new TH1D("h_jet_lead_pt_700","lead jet pt, qT>700", 100, 0, 1000.);

   h_mET = new TH1D("h_mET","mET", 50, 0, 300.);

  
  h_ZpT_log = new TH1D("h_ZpT_log","log plot of qT", 140, 0, 700);
  h_InvMass = new TH1D("h_InvMass","Invariant Mass of the Z", 100, 50, 150);
  h_MCinvmass = new TH1D("h_MCinvmass","Invariant Mass of the Z", 100, 50, 150);

  h_ZpT = new TH1D("h_ZpT","ZpT", 75, 0., 150);
  h_numJets = new TH1D("h_numJets","number of jets", 11, -.5, 10.5);


  h_extra_electrons = new TH1D("h_extra_electrons", "# of extra electrons", 6, -.5, 5.5);
  h_extra_muons = new TH1D("h_extra_muons", "# of extra muons", 6, -.5, 5.5);
  
  //  h_electron_pt = new TH1D("h_electron_pt", "electron pt", 200,0,200);
  // h_muon_pt = new TH1D("h_muon_pt", "muon pt", 200,0,200);



  
  h_nPUVertices = new TH1D("PUVertices", "PUVertices", 70, 0, 70);
  h_nPUVerticesTrue = new TH1D("PUVerticesTrue", "PUVerticesTrue", 70, 0, 70);
  h_vtxCount = new TH1D("h_vtxCount", "vertex count", 70, 0, 70); 
  h_vtxCountmm = new TH1D("h_vtxCountmm", "vertex count", 70, 0, 70); 
  h_vtxCountem = new TH1D("h_vtxCountem", "vertex count", 70, 0, 70); 
  
  h_vtxCountSLN = new TH1D("h_vtxCountSLN", "vertex count", 70, 0, 70); 
  h_vtxCountSL1 = new TH1D("h_vtxCountSL1", "vertex count", 70, 0, 70); 
  h_vtxCountSMN = new TH1D("h_vtxCountSMN", "vertex count", 70, 0, 70); 
  h_vtxCountSM1 = new TH1D("h_vtxCountSM1", "vertex count", 70, 0, 70); 
  h_vtxCountSSN = new TH1D("h_vtxCountSSN", "vertex count", 70, 0, 70); 
  h_vtxCountSS1 = new TH1D("h_vtxCountSS1", "vertex count", 70, 0, 70); 
  
 // h_vtxCountmm= new TH1D("vertex countmm", "vertex count mm", 70, 0, 70); 
  h_InvMassnone = new TH1D("h_InvMassnone", "InvMass loose cuts", 100, 50, 250);
  
  // h_dReEm1 = new TH1D("h_dReEm1", "dR between elec and first muon", 100, 0, 6);
  //h_dReEm2 = new TH1D("h_dReEm2", "dR between elec and second muon", 100, 0, 6);
  
  // h_rMET = new TH1D("h_rMET", "reduced MET", 50,0,300);
  //h_rMETx = new TH1D("h_rMETx", "reduced MET parallel", 100,-100,300);
 //h_rMETy = new TH1D("h_rMETy", "reduced MET perpendiculat", 50,-100,100);
 // h_changeMET = new TH1D("h_changeMET", "change between MET and rMET", 100,-50,50);
 h_METcomponents = new TH2D("h_METcomponents","MET perp vs MET parallel", 200,-100,100,200,-100,100);
 h_METcomparison = new TH2D("h_METcomparison","rMET vs MET ", 200,0,100,200,0,100);
 h_InvMassnoIso = new TH1D("h_InvMassnoIso", "InvMass with no iso", 100,50,250);
 h_InvmassvsMET = new TH2D("h_InvmassvsMET", "MET vs Inv Mass",60,60,120,100,0,100);
 h_InvmassvsMsig = new TH2D("h_InvmassvsMsig", "MET vs Inv Mass",60,60,120,10,0,10);
 h_qTvsM = new TH2D("h_qTvsM", "qT vs M", 200, 0, 1000, 200, 0, 1000);
 h_X = new TH1D("h_X","sqrt(M*M + qT*qT)", 500, 0, 1000);
 // h_XoverM = new TH1D("XoverM"," X over M", 100, 0, 10);


 h_Zrapid = new TH1D("h_Zrapid","Z rapidity",60, -3, 3);
 //h_BarreltestNick = new TH1D("h_BarreltestNick","Invariant Mass Barrel mm",34, invmassmm);
 // h_BarreltestNickBB = new TH1D("h_BarreltestNickBB","Invariant Mass Barrel mm",34, invmassmm);
 // h_BarreltestNickBE = new TH1D("h_BarreltestNickBE","Invariant Mass Barrel mm",34, invmassmm);
 // h_BarreltestNickEE = new TH1D("h_BarreltestNickEE","Invariant Mass Barrel mm",34, invmassmm);

  h_InvMassee = new TH1D("h_InvMassee","Invariant Mass of the Z ee", 70, 60, 130);
 h_InvMasseeinner = new TH1D("h_InvMasseeinner","Invariant Mass of the Z ee", 70, 60, 130);
 h_InvMasseeouter = new TH1D("h_InvMasseeouter","Invariant Mass of the Z ee", 70, 60, 130);
  h_InvMassee2 = new TH1D("h_InvMassee2","Invariant Mass of the Z ee", 70, 60, 130);
  h_InvMassbase = new TH1D("h_InvMassbase","Invariant Mass of the Z mm", 70, 60, 130);
 h_InvMassbase2 = new TH1D("h_InvMassbase2","Invariant Mass of the Z mm", 70, 60, 130);
 h_InvMassbase3 = new TH1D("h_InvMassbase3","Invariant Mass of the Z mm", 70, 60, 130);
 h_InvMassbase4 = new TH1D("h_InvMassbase4","Invariant Mass of the Z mm", 70, 60, 130);
  h_InvMassmm = new TH1D("h_InvMassmm","Invariant Mass of the Z mm", 70, 60, 130);
 h_IMmm = new TH1D("h_IMmm","Invariant Mass of the Z mm", 115, 15, 130);
 h_IMmmvtx1 = new TH1D("h_IMmmvtx1","Invariant Mass of the Z mm",30, invmassmm);
 h_IMmmvtx2 = new TH1D("h_IMmmvtx2","Invariant Mass of the Z mm",30, invmassmm);
 h_IMmmvtx3 = new TH1D("h_IMmmvtx3","Invariant Mass of the Z mm",30, invmassmm);
 h_IMmmvtx4 = new TH1D("h_IMmmvtx4","Invariant Mass of the Z mm",30, invmassmm);
h_IMmmvtx5 = new TH1D("h_IMmmvtx5","Invariant Mass of the Z mm",30, invmassmm);
 h_IMmmvtx6 = new TH1D("h_IMmmvtx6","Invariant Mass of the Z mm",30, invmassmm);

  h_InvMassmminner = new TH1D("h_InvMassmminner","Invariant Mass of the Z mm", 70, 60, 130);
  h_InvMassmmouter = new TH1D("h_InvMassmmouter","Invariant Mass of the Z mm", 70, 60, 130);

  h_InvMassem = new TH1D("h_InvMassem","Invariant Mass of the Z em", 70, 60, 130);
  h_InvMasseminner = new TH1D("h_InvMasseminner","Invariant Mass of the Z em", 70, 60, 130); 
  h_InvMassemouter = new TH1D("h_InvMassemouter","Invariant Mass of the Z em", 70, 60, 130);
  h_InvMassbelow = new TH1D("h_InvMassbelow","Invariant Mass of the Z em", 70, 60, 130);
  h_InvMassabove = new TH1D("h_InvMassabove","Invariant Mass of the Z em", 70, 60, 130);


  h_IMmmnocuts = new TH1D("h_IMmmnocuts","Invariant Mass of the Z em", 70, 60, 130);
  h_IMmmJetres = new TH1D("h_IMmmJetres","Invariant Mass of the Z em", 70, 60, 130);
  h_IMmmVtexres = new TH1D("h_IMmmVtexres","Invariant Mass of the Z em", 70, 60, 130);
  h_IMmmacolres = new TH1D("h_IMmmacolres","Invariant Mass of the Z em", 70, 60, 130);
  h_IMmmSumptres = new TH1D("h_IMmmSumptres","Invariant Mass of the Z em", 70, 60, 130);
  h_NJmmJetres = new TH1D("h_NJmmJerres","number of jets", 11, -.5, 10.5);
  h_Vtexmmres = new TH1D("h_Vtexmmres","vertex probability", 80, 0, 4);
  h_acolmmres = new TH1D("h_acolmmres","pi - acolineariry", 32, 0, 3.2);
   h_sumptmmres = new TH1D("h_Sumptmmres","scalar sum of both lepton pt", 100, 0, 500.);

   h_IMeenocuts = new TH1D("h_IMeenocuts","Invariant Mass of the Z em", 70, 60, 130);
  h_IMeeJetres = new TH1D("h_IMeeJetres","Invariant Mass of the Z em", 70, 60, 130);
  h_IMeeVtexres = new TH1D("h_IMeeVtexres","Invariant Mass of the Z em", 70, 60, 130);
  h_IMeeacolres = new TH1D("h_IMeeacolres","Invariant Mass of the Z em", 70, 60, 130);
  h_IMeeSumptres = new TH1D("h_IMeeSumptres","Invariant Mass of the Z em", 70, 60, 130);
  h_NJeeJetres = new TH1D("h_NJeeJerres","number of jets", 11, -.5, 10.5);
  h_Vtexeeres = new TH1D("h_Vtexeeres","vertex probability", 80, 0, 4);
  h_acoleeres = new TH1D("h_acoleeres","pi - acolineariry", 32, 0, 3.2);
   h_sumpteeres = new TH1D("h_Sumpteeres","scalar sum of both lepton pt", 100, 0, 500.);

 h_IMemnocuts = new TH1D("h_IMemnocuts","Invariant Mass of the Z em", 70, 60, 130);
 h_IMemJetres = new TH1D("h_IMemJetres","Invariant Mass of the Z em", 70, 60, 130);
 h_IMemVtexres = new TH1D("h_IMemVtexres","Invariant Mass of the Z em", 70, 60, 130);
  h_IMemacolres = new TH1D("h_IMemacolres","Invariant Mass of the Z em", 70, 60, 130);
  h_IMemSumptres = new TH1D("h_IMemSumptres","Invariant Mass of the Z em", 70, 60, 130);
  h_NJemJetres = new TH1D("h_NJemJerres","number of jets", 11, -.5, 10.5);
  h_Vtexemres = new TH1D("h_Vtexemres","vertex probability", 80, 0, 4);
  h_acolemres = new TH1D("h_acolemres","pi - acolineariry", 32, 0, 3.2);
   h_sumptemres = new TH1D("h_Sumptemres","scalar sum of both lepton pt", 100, 0, 500.);


   h_ZpTee = new TH1D("h_ZpTee","ZpT", 75, 0., 150);
   h_ZpTmm = new TH1D("h_ZpTmm","ZpT", 75, 0., 150);
   h_ZpTem = new TH1D("h_ZpTem","ZpT", 75, 0., 150);
   h_ZpTCutee = new TH1D("h_ZpTCutee","ZpT", 75, 0., 150);
   h_ZpTCutmm = new TH1D("h_ZpTCutmm","ZpT", 75, 0., 150);
   h_ZpTCutem = new TH1D("h_ZpTCutem","ZpT", 75, 0., 150);
  h_numJetsee = new TH1D("h_numJetsee","number of jets", 11, -.5, 10.5);
  h_numJetsmm = new TH1D("h_numJetsmm","number of jets", 11, -.5, 10.5);
  h_numJetsem = new TH1D("h_numJetsem","number of jets", 11, -.5, 10.5);
  h_numJetseminner = new TH1D("h_numJetseminner","number of jets", 11, -.5, 10.5);
  h_numJetsemouter = new TH1D("h_numJetsemouter","number of jets", 11, -.5, 10.5);
 h_numJetseeinner = new TH1D("h_numJetseeinner","number of jets", 11, -.5, 10.5);
  h_numJetseeouter = new TH1D("h_numJetseeouter","number of jets", 11, -.5, 10.5);
 h_numJetsmminner = new TH1D("h_numJetsmminner","number of jets", 11, -.5, 10.5);
  h_numJetsmmouter = new TH1D("h_numJetsmmouter","number of jets", 11, -.5, 10.5);
   h_METSignificance = new TH1D("h_METSignificance","MET significance", 51, -.5, 50.5);
   h_METSignificanceee = new TH1D("h_METSignificanceee","MET significance", 51, -.5, 50.5);
   h_METSignificancemm = new TH1D("h_METSignificancemm","MET significance", 51, -.5, 50.5);
   h_METSignificanceem = new TH1D("h_METSignificanceem","MET significance", 51, -.5, 50.5);
   h_METSignificance2 = new TH1D("h_METSignificance2","MET significance2", 51, -.5, 50.5);
 h_Cutmm = new TH1D("h_Cutmm","Invariant Mass with cuts MM", 60, 60, 120);
 h_Cutee = new TH1D("h_Cutee","Invariant Mass with cuts ee", 60, 60, 120);
 h_Cutem = new TH1D("h_Cutem","Invariant Mass with cuts eM", 60, 60, 120);
 h_CutQTmm = new TH1D("h_CutQTmm","Invariant Mass with cuts MM", 60, 60, 120);
 h_CutQTee = new TH1D("h_CutQTee","Invariant Mass with cuts ee", 60, 60, 120);
 h_CutQTem = new TH1D("h_CutQTem","Invariant Mass with cuts eM", 60, 60, 120);
 h_Cutem2 = new TH1D("h_Cutem2","Invariant Mass with cuts eM", 70, 60, 120);

h_acol = new TH1D("h_acol","pi - acolineariry", 32, 0, 3.2);
h_acolee = new TH1D("h_acolee","pi - acolineariry", 32, 0, 3.2);
h_acolmm = new TH1D("h_acolmm","pi - acolineariry", 32, 0, 3.2);
h_acolem = new TH1D("h_acolem","pi - acolineariry", 32, 0, 3.2);
h_delphi = new TH1D("h_delphi","phi angle between leps", 50, 0, 3.2);
h_delphiee = new TH1D("h_delphiee","phi angle between leps", 50, 0, 3.2);
h_delphimm = new TH1D("h_delphimm","phi angle between leps", 50, 0, 3.2);
h_delphiem = new TH1D("h_delphiem","phi angle between leps", 50, 0, 3.2);
   h_Sumpt = new TH1D("h_Sumpt","scalar sum of both lepton pt", 100, 0, 1000.);
   h_Sumptee = new TH1D("h_Sumptee","scalar sum of both lepton pt", 100, 0, 1000.);
   h_Sumptmm = new TH1D("h_Sumptmm","scalar sum of both lepton pt", 100, 0, 1000.);
   h_Sumptem = new TH1D("h_Sumptem","scalar sum of both lepton pt", 60, 20, 140.);
   h_lep1dxy = new TH1D("h_lep1dxy","beam spot information", 100, 0, 0.5);
   h_lep2dxy = new TH1D("h_lep2dxy","beam spot information", 100, 0, 0.5);
   h_lep1dxyee = new TH1D("h_lep1dxyee","beam spot information", 100, 0, 0.5);
   h_lep2dxyee = new TH1D("h_lep2dxyee","beam spot information", 100, 0, 0.5);
   h_lep1dxymm = new TH1D("h_lep1dxymm","beam spot information", 100, 0, 0.05);
   h_lep2dxymm = new TH1D("h_lep2dxymm","beam spot information", 100, 0, 0.05);
   h_lep1dxyem = new TH1D("h_lep1dxyem","beam spot information", 100, 0, 0.05);
   h_lep2dxyem = new TH1D("h_lep2dxyem","beam spot information", 100, 0, 0.5); 
   h_Michael1 = new TH1D("h_Michael1","Invariant Mass of the mumu", 70, 60, 130); 
   h_Michael2 = new TH1D("h_Michael2","Invariant Mass of the emu", 70, 60, 130);
   h_lepton1pt = new TH1D("h_lepton1pt","lepton pt", 60, 0, 60.);
   h_lepton2pt = new TH1D("h_lepton2pt","lepton pt", 60, 0, 60.);
   h_leadptem = new TH1D("h_leadptem","lepton pt", 100, 0, 100.);
   h_subptem = new TH1D("h_subptem","lepton pt", 100, 0, 100.);
   h_leadptmm = new TH1D("h_leadptmm","lepton pt", 100, 0, 100.);
   h_subptmm = new TH1D("h_subptmm","lepton pt", 100, 0, 100.); 
   h_leadptee = new TH1D("h_leadptee","lepton pt", 100, 0, 100.);
   h_subptee = new TH1D("h_subptee","lepton pt", 100, 0, 100.);
   h_leptonbothpt = new TH1D("h_leptonbothpt","lepton pt", 60, 0, 60.);
   h_leptonsmalleta = new TH1D("h_leptonsmalleta","lepton pt", 60, 0, 60.);
   h_lepton1smalleta = new TH1D("h_lepton1smalleta","lepton pt", 60, 0, 60.);
   h_lepton2smalleta = new TH1D("h_lepton2smalleta","lepton pt", 60, 0, 60.);
   h_vertexProb = new TH1D("h_vertexProb","vertex probability", 80, 0, 4);
   h_vertexProbmm = new TH1D("h_vertexProbmm","vertex probability", 80, 0, 4);
   h_vertexProbem = new TH1D("h_vertexProbem","vertex probability", 80, 0, 4);
   h_liso1mm = new TH1D("h_liso1mm","liso1 mm", 100, 0.0, 1.0);
   h_liso2mm = new TH1D("h_liso2mm","liso2 mm", 100, 0.0, 1.0);
   h_leta1mm = new TH1D("h_leta1mm","leta1", 100, -2.5, 2.5);
   h_leta2mm = new TH1D("h_leta2mm","leta2", 100, -2.5, 2.5);
   h_lphi1mm = new TH1D("h_lphi1mm","lphi1", 100, 0.0, 3.2);
   h_lphi2mm = new TH1D("h_lphi2mm","lphi2", 100, 0.0, 3.2);
   h_leta1ee = new TH1D("h_leta1ee","leta1", 100, -2.5, 2.5);
   h_leta2ee = new TH1D("h_leta2ee","leta2", 100, -2.5, 2.5);
   h_lphi1ee = new TH1D("h_lphi1ee","lphi1", 100, 0.0, 3.2);
   h_lphi2ee = new TH1D("h_lphi2ee","lphi2", 100, 0.0, 3.2);
   h_liso1ee = new TH1D("h_liso1ee","liso1 ee", 100, 0.0, 0.15);
   h_liso2ee = new TH1D("h_liso2ee","liso2 ee", 100, 0.0, 0.15);

  h_METresee = new TH1D("h_METresee","MET significance", 51, -.5, 50.5);
  h_VPresee = new TH1D("h_VPresee","vertex probability", 80, 0, 4);
 h_NJresee = new TH1D("h_NJresee","number of jets", 11, -.5, 10.5);
 h_SPresee = new TH1D("h_SPresee","scalar sum of both lepton pt", 100, 0, 500.);

 h_METresmm = new TH1D("h_METresmm","MET significance", 51, -.5, 50.5);
  h_VPresmm = new TH1D("h_VPresmm","vertex probability", 80, 0, 4);
 h_NJresmm = new TH1D("h_NJresmm","number of jets", 11, -.5, 10.5);
 h_SPresmm = new TH1D("h_SPresmm","scalar sum of both lepton pt", 100, 0, 500.);

 h_METresem = new TH1D("h_METresem","MET significance", 51, -.5, 50.5);
  h_VPresem = new TH1D("h_VPresem","vertex probability", 80, 0, 4);
 h_NJresem = new TH1D("h_NJresem","number of jets", 11, -.5, 10.5);
 h_SPresem = new TH1D("h_SPresem","scalar sum of both lepton pt", 100, 0, 500.);


 h_phiStar = new TH1D("phiStar","phiStar",34, xlow);
 h_phiStarbiso = new TH1D("phiStarbiso","phiStar",34, xlow);
 h_phiStarem = new TH1D("phiStarem","phiStar",34, xlow);
 h_phiStarRapid1 = new TH1D("h_phiStarRapid1","phiStar with 0.0< ZRapidity< 0.5",34, xlow);
 h_phiStarRapid2 = new TH1D("h_phiStarRapid2","phiStar with 0.5< ZRapidity< 1.0",34, xlow);
 h_phiStarRapid3 = new TH1D("h_phiStarRapid3","phiStar with 1.0< ZRapidity< 1.5",34, xlow);
 h_phiStarRapid4 = new TH1D("h_phiStarRapid4","phiStar with 1.5< ZRapidity< 1.9",34, xlow);
 h_phiStarRapid5 = new TH1D("h_phiStarRapid5","phiStar with 1.9< ZRapidity< 2.4",34, xlow);
 h_RapidphiStar1 = new TH1D("h_RapidphiStar1","Z rapidity with 0.0< phistar< 0.01",100,-2.4,2.4);
h_RapidphiStar2 = new TH1D("h_RapidphiStar2","Z rapidity with 0.01< phistar< 0.1",100,-2.4,2.4);
h_RapidphiStar3 = new TH1D("h_RapidphiStar3","Z rapidity with 0.1< phistar< 0.3",100,-2.4,2.4);
h_RapidphiStar4 = new TH1D("h_RapidphiStar4","Z rapidity with 0.3< phistar< 3.277",100,-2.4,2.4);
 h_phiStarMC = new TH1D("h_phiStarMC","phiStar", 34, xlow);
 h_phiStarMCN = new TH1D("h_phiStarMCN","phiStar", 34, xlow);
 h_phiStarMCB = new TH1D("h_phiStarMCB","phiStar", 34, xlow);
 h_phiStarMCD = new TH1D("h_phiStarMCD","phiStar", 34, xlow);

h_phiStarMCN2 = new TH1D("h_phiStarMCN2","phiStar", 34, xlow);
 h_phiStarMCB2 = new TH1D("h_phiStarMCB2","phiStar", 34, xlow);
 h_phiStarMCD2 = new TH1D("h_phiStarMCD2","phiStar", 34, xlow);

 h_phiStarMC2 = new TH1D("h_phiStarMC2","phiStar", 34, xlow);
 h_phiStarMC3 = new TH1D("h_phiStarMC3","phiStar", 34, xlow);

 h_phistardiff = new TH1D("h_phistardiff","Difference between MC and reco phi star",100, -.1, .1);
 h_phistardiff1 = new TH1D("h_phistardiff1","Difference between MC and reco phi star",100, -.0050, .0050);
 h_phistardiff2 = new TH1D("h_phistardiff2","Difference between MC and reco phi star",100, -.0050, .0050);
 h_phistardiff3 = new TH1D("h_phistardiff3","Difference between MC and reco phi star",100, -.0050, .0050);
 h_phistardiff4 = new TH1D("h_phistardiff4","Difference between MC and reco phi star",100, -.0050, .0050);
 h_phistardiff5 = new TH1D("h_phistardiff5","Difference between MC and reco phi star",100, -.0050, .0050);
 h_phistardiff6 = new TH1D("h_phistardiff6","Difference between MC and reco phi star",100, -.1, .1);
 h_phistardiff7 = new TH1D("h_phistardiff7","Difference between MC and reco phi star",500, -1, 1);

 h_phiStar2D1 = new TH2D("h_phiStar2D1","phistar RECO vs phiStar true", 34,xlow,34,xlow);
 h_phiStar2D2 = new TH2D("h_phiStar2D2","phistar diff vs phiStar true", 100,-.1,.1,100,0,3.14);
 h_phiStar2D3 = new TH2D("h_phiStar2D3","phistar diff vs phiStar true", 100,-.1,.1,60,-3,3);

 // h_phiStarvsZpT = new TH2D("h_phiStarvsZpT","phistar vs qT", 34,xlow,100,ZpTlow);
 h_phiStarvsZpT = new TH2D("h_phiStarvsZpT","phistar vs qT", 1000,0,100,500,0,500);


 

   //same sign plots
   h_InvMassSS = new TH1D("h_InvMassSS","Invariant Mass of the Z Same Sign", 100, 50, 150);
   h_leadptSS = new TH1D("h_leadptSS","lepton pt same sign", 100, 0, 100.);
   h_subptSS = new TH1D("h_subptSS","lepton pt same sign", 100, 0, 100.);
   h_phiStarSS = new TH1D("phiStarSS","phiStar same sign",34, xlow);
   //following plots for Wisolation study 803
 h_phiStarWiso1 = new TH1D("h_phiStarWiso1","phiStar", 34, xlow);
 h_phiStarWiso2 = new TH1D("h_phiStarWiso2","phiStar", 34, xlow);
 h_phiStarWiso3 = new TH1D("h_phiStarWiso3","phiStar", 34, xlow);
 h_phiStarWiso4 = new TH1D("h_phiStarWiso4","phiStar", 34, xlow);
 h_phiStarWiso5 = new TH1D("h_phiStarWiso5","phiStar", 34, xlow);
 h_drjetWiso1 = new TH1D("h_drjetWiso1","distance to closest jet", 150, 0.0, 3.14);
 h_drjetWiso2 = new TH1D("h_drjetWiso2","distance to closest jet", 150, 0.0, 3.14);
 h_drjetWiso3 = new TH1D("h_drjetWiso3","distance to closest jet", 150, 0.0, 3.14);
 h_Nisolation1 = new TH1D("h_Nisolation1","isolation", 100, 0.0, 1.0);
 h_Nisolation2 = new TH1D("h_Nisolation2","isolation", 100, 0.0, 1.0);
 h_Nisolation3 = new TH1D("h_Nisolation3","isolation", 100, 0.0, 1.0);


  h_EMPSLleadpt = new TH1D("h_EMPSLleadpt","lepton pt same sign", 100, 0, 100.);
   h_EMPSLsubpt = new TH1D("h_EMPSLsubpt","lepton pt same sign", 100, 0, 100.);
    h_EMPSLl1eta = new TH1D("h_EMPSLl1eta","leta1", 100, -2.5, 2.5);
    h_EMPSLl2eta = new TH1D("h_EMPSLl2eta","leta1", 100, -2.5, 2.5);
   h_EMPSLIM = new TH1D("h_EMPSLIM","Invariant Mass of the Z Same Sign", 100, 50, 150);
   h_EMPSLZpT = new TH1D("h_EMPSLZpT","ZpT", 75, 0., 150);
   h_EMPSLNJ = new TH1D("h_EMPSLNJ","number of jets", 11, -.5, 10.5);


   h_EMPSLNmET = new TH1D("h_EMPSLNmET","mET", 50, 0, 300.);
   h_EMPSLNIM = new TH1D("h_EMPSLNIM","Invariant Mass of the Z Same Sign", 100, 50, 150);
   h_EMPSL1mET = new TH1D("h_EMPSL1mET","mET", 50, 0, 300.);
   h_EMPSL1IM = new TH1D("h_EMPSL1IM","Invariant Mass of the Z Same Sign", 100, 50, 150);
			

   h_EMPSMleadpt = new TH1D("h_EMPSMleadpt","lepton pt same sign", 100, 0, 100.);
   h_EMPSMsubpt = new TH1D("h_EMPSmsubpt","lepton pt same sign", 100, 0, 100.);
   h_EMPSMl1eta = new TH1D("h_EMPSMl1eta","leta1", 100, -2.5, 2.5);
   h_EMPSMl2eta = new TH1D("h_EMPSml2eta","leta1", 100, -2.5, 2.5);
   h_EMPSMIM = new TH1D("h_EMPSMIM","Invariant Mass of the Z Same Sign", 100, 50, 150);
   h_EMPSMZpT = new TH1D("h_EMPSMZpT","ZpT", 75, 0., 150);
   h_EMPSMNJ = new TH1D("h_EMPSMNJ","number of jets", 11, -.5, 10.5);

   h_EMPSMNmET = new TH1D("h_EMPSMNmET","mET", 50, 0, 300.);
   h_EMPSMNIM = new TH1D("h_EMPSMNIM","Invariant Mass of the Z Same Sign", 100, 50, 150);
   h_EMPSM1mET = new TH1D("h_EMPSM1mET","mET", 50, 0, 300.);
   h_EMPSM1IM = new TH1D("h_EMPSM1IM","Invariant Mass of the Z Same Sign", 100, 50, 150);

   h_EMPSSleadpt = new TH1D("h_EMPSSleadpt","lepton pt same sign", 100, 0, 100.);
   h_EMPSSsubpt = new TH1D("h_EMPSSsubpt","lepton pt same sign", 100, 0, 100.);
   h_EMPSSl1eta = new TH1D("h_EMPSSl1eta","leta1", 100, -2.5, 2.5);
   h_EMPSSl2eta = new TH1D("h_EMPSSl2eta","leta1", 100, -2.5, 2.5);
   h_EMPSSIM = new TH1D("h_EMPSSIM","Invariant Mass of the Z Same Sign", 100, 50, 150);
   h_EMPSSZpT = new TH1D("h_EMPSSZpT","ZpT", 75, 0., 150);
   h_EMPSSNJ = new TH1D("h_EMPSSNJ","number of jets", 11, -.5, 10.5);

   h_EMPSSNmET = new TH1D("h_EMPSSNmET","mET", 50, 0, 300.);
   h_EMPSSNIM = new TH1D("h_EMPSSNIM","Invariant Mass of the Z Same Sign", 100, 50, 150);
   h_EMPSS1mET = new TH1D("h_EMPSS1mET","mET", 50, 0, 300.);
   h_EMPSS1IM = new TH1D("h_EMPSS1IM","Invariant Mass of the Z Same Sign", 100, 50, 150);




  cout<<"Ok so far ..."<<endl;
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void AnalyzerPS::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t AnalyzerPS::Process(Long64_t entry)
{
  GetEntry(entry);
	 notdoublecounted=true;
  ZpTcut=METcut=invmasscutabove=invmasscutbelow=Sumptcut=NumJetscut=acolcut=vtxprobcut= false;
  weighta=weightb=weightc=1.0;
  lep1pt=l14vector->Pt();
  lep2pt=l24vector->Pt();

  larks++;
      if((larks%100000)==0)
	 cout<<larks<<endl;
  if(-log10(vertexProb)>4)
    vertexProb=.00009;

    if(!(IS_DATA))
      {    
	//			weight=weights[nPUVerticesTrue];
      }
 h_nPUVerticesTrue->Fill(nPUVerticesTrue, 1);  	
 WisolationStudy();
   if(acol<5)
     acolcut=true;
   if((lep1pt+lep2pt)<95)
     Sumptcut=true;
   if(METSignificance<5)
     METcut=true;
   if(numberjets==0)
     NumJetscut=true;
   if((-log10(vertexProb))<.9)
     vtxprobcut=true;
   if(InvMass>88)
     invmasscutbelow=true;
   if(InvMass<96)
     invmasscutabove=true;
   if(ZpT<20)
     ZpTcut=true;
   // fill(h_InvMassmm, InvMass);
   //   delphi=3.14159265359-DeltaPhiX(lep1phi,lep2phi);

   //This is for the acceptance study, not needed normally
    
      InvMass2=get_mass(*l14vector+*l24vector);
      //              cout<<MC14vector->M()<<" , "<<MC14vector->Pt()<<endl;
      /*      InvMass3=get_mass(*MC14vector+*MC24vector);
       cout<<eff1<<endl;
       if(eff1==1)
	 {
	   fill(h_InvMassbase, InvMass3);
	   if(MC14vector->Pt()>30 && MC24vector->Pt()>20 && fabs(MC14vector->Eta())<2.1 && fabs(MC24vector->Eta()) <2.1 &&InvMass3<130 && InvMass3>60)
	     {
	       fill(h_InvMassbase2, InvMass3);
	       if(DiLeptonType==5)
		   {
		     fill(h_InvMassbase3, InvMass3);
		     if((SingleMuonTriggeriso==1||SingleElectronTrigger==1))
		     {
		       fill(h_InvMassbase4, InvMass3);

		     }
		   }
	     }
	 }
      */
      

       if(!(IS_DATA))
	 {
	  
	   /*
	   if(MC14vector->Pt()>20)
	     {
	   double MCapt, MCbpt;
	   double acopMC2, thetaMC2;
	   double phiStarMC3;
	   if(MC14vector->Pt()>MC24vector->Pt())
	     {
	       MCapt=MC14vector->Pt();
	       MCbpt=MC24vector->Pt();
	     }
	   else
	     {
	       MCapt=MC24vector->Pt();
	       MCbpt=MC14vector->Pt();
	     }
	   if(MCapt>30 && MCbpt>20 && fabs(MC14vector->Eta())<2.4 && fabs(MC24vector->Eta())<2.4)
	     {
	       acopMC2=3.14159265359-DeltaPhiX(MC14vector->Phi(),MC24vector->Phi());
   if(MC1Q<MC2Q)
     thetaMC2=acos(tanh((MC14vector->Eta()-MC24vector->Eta())/2));
   else
     thetaMC2=acos(tanh((MC24vector->Eta()-MC14vector->Eta())/2));
	   phiStarMC3=tan(acopMC2/2)*sin(thetaMC2);
	      h_phiStarMC3->Fill(phiStarMC3);
   
	     }
	   */
	   if(MCN14vector->Pt()>0.0 && MCD14vector->Pt()>0.0 && MCB14vector->Pt()>0.0)
		 {
   acopMCN=3.14159265359-DeltaPhiX(MCN14vector->Phi(),MCN24vector->Phi());
   if(MCN1Q<MCN2Q)
     thetaMCN=acos(tanh((MCN14vector->Eta()-MCN24vector->Eta())/2));
   else
     thetaMCN=acos(tanh((MCN24vector->Eta()-MCN14vector->Eta())/2));
	   phiStarMCN=tan(acopMCN/2)*sin(thetaMCN);

   acopMCD=3.14159265359-DeltaPhiX(MCD14vector->Phi(),MCD24vector->Phi());
   if(MCD1Q<MCD2Q)
     thetaMCD=acos(tanh((MCD14vector->Eta()-MCD24vector->Eta())/2));
   else
     thetaMCD=acos(tanh((MCD24vector->Eta()-MCD14vector->Eta())/2));
	   phiStarMCD=tan(acopMCD/2)*sin(thetaMCD);
   acopMCB=3.14159265359-DeltaPhiX(MCB14vector->Phi(),MCB24vector->Phi());
   if(MCB1Q<MCB2Q)
     thetaMCB=acos(tanh((MCB14vector->Eta()-MCB24vector->Eta())/2));
   else
     thetaMCB=acos(tanh((MCB24vector->Eta()-MCB14vector->Eta())/2));
	   phiStarMCB=tan(acopMCB/2)*sin(thetaMCB);
		 }


	   //	   cout<<phiStarMCN<<" ,"<<phiStarMCB<<" ,"<<phiStarMCD<<endl;


	   if(MC1pt>30 &&MC2pt>20)
	 {
	   h_MCinvmass->Fill(MCinvmass);
     acopMC=3.14159265359-DeltaPhiX(MC1phi,MC2phi);
   if(MC1Q<MC2Q)
     thetaMC=acos(tanh((MC1eta-MC2eta)/2));
   else
     thetaMC=acos(tanh((MC2eta-MC1eta)/2));

   phiStarMC=tan(acopMC/2)*sin(thetaMC);
   h_phiStarMC->Fill(phiStarMC);
	 }
	 }

 if(lep1Q==lep2Q)
	 {


	  if( DiLeptonType==1 && DoubleMuonTrigger==true && fabs(lep1eta) <2.4 && fabs(lep2eta)<2.4 && InvMass>60&& InvMass<120 && extraElectrons<1 && extraMuons<1 && liso1<0.12 &&liso2<0.12)
	 {
 fill(h_InvMassSS, InvMass);
 fill(h_leadptSS, l14vector->Pt());
 fill(h_subptSS, l24vector->Pt());
    acop=3.14159265359-DeltaPhiX(l14vector->Phi(),l24vector->Phi());
	      if(lep1Q<lep2Q)
		theta=acos(tanh((lep1eta-lep2eta)/2));
	      else
		theta=acos(tanh((lep1eta-lep2eta)/2));
	      
	      phiStar=tan(acop/2)*sin(theta);
	      fill(h_phiStarSS, phiStar);
	 }
	 }
      //    if( (SingleMuonTriggeriso==1||SingleElectronTrigger==1))
      if(lep1Q==-lep2Q)
	 {
	 
  if(filetype==1)
	{
	  //  cout<<runid<<" "<<eventid<<endl;
	 	 ss << runid << " " << eventid << "\n";
		 //    string mySting = ss.str();
			//string hellos;
			//hellos <<runid;
			//cout<<hellos<<endl;
		 //			       		 cout<<mySting<<endl;
	 }
       //checks if event was used before
   

          if(filetype==2)
	 {
	       runida=runid;
	     eventida=eventid;

	     	   foo=make_pair(runida,eventida);
		   //cout<<foo.first<<" "<<foo.second<<endl;
		   //for use in unsorted array
		   //		   if(find(oldevents.begin(), oldevents.end(), foo) != oldevents.end())
		   //for use if oldevents is sorted
		   if(binary_search(oldevents.begin(), oldevents.end(), foo))

	      {notdoublecounted=false;
		cout<<larks<<" duplicate event found"<<endl;
	      }


	 }	 

	  //	        if(notdoublecounted)
		   if(true)
	 {
	 
   if(DoubleMuonTrigger==1 && DiLeptonType==1) 
     {
       if(IS_DATA)
	 {
	    muCorrector->momcor_data(*l14vector,lep1Q,0,qter); 
	    muCorrector->momcor_data(*l24vector,lep2Q,0,qter);  
	   lep1pt=l14vector->Pt();
	   lep2pt=l24vector->Pt();
	   lep1eta=l14vector->Eta();
	   lep2eta=l24vector->Eta();
	 }
       else
	 {
	   //	  cout<<endl<<endl<<weight<<endl;
	   
	   //	    cout<<weighta<<" , "<<l14vector->Pt()<<" , "<<l14vector->Eta()<<" , "<<weight<<endl;
	   
	   
	    muCorrector->momcor_mc(*l14vector,lep1Q,0,qter); 
	   muCorrector->momcor_mc(*l24vector,lep2Q,0,qter); 
	   //  cout<<l14vector->Pt();
	   lep1pt=l14vector->Pt();
	   lep2pt=l24vector->Pt();
	   lep1eta=l14vector->Eta();
	   lep2eta=l24vector->Eta();	    
	   
	   	    weighta=GetMuEff(lep1pt, lep1eta);
	        	weightb=GetMuEff(lep2pt, lep2eta);
			

			weightc=TriggerMuEff(lep1pt, lep1eta);
	   //	      cout<<weight<<" , ";
			//apply single muon or single electron or both trigger weights to the MC files
			/*	
		      if(SingleMuonTriggeriso==1 && !(SingleElectronTrigger==1))
				{
				  weightc=TriggerMuEff(lep1pt, lep1eta);
	}
      else if(!(SingleMuonTriggeriso==1) && (SingleElectronTrigger==1))
	{
	  weightc=TriggerElEff(lep1pt, lep1eta);
	    }
      else if(SingleMuonTriggeriso==1 && (SingleElectronTrigger==1))
	{
	  weightc=TriggerMuEff(lep1pt, lep1eta)*TriggerElEff(lep1pt, lep1eta);
	}
			*/
			//weightc=triggerEff(lep1pt, lep1eta, lep2pt, lep2eta);

	         weight=weight*weighta*weightb*weightc;
	   // weight=1.0;
	   //cout<<weight<<endl;

	 }
            InvMass2=get_mass(*l14vector+*l24vector);

       if( fabs(lep1eta)<2.1 && fabs(lep2eta)<2.4 && lep1pt>30 && lep2pt>20 && InvMass2>60&& InvMass2<120 && extraElectrons<1 && extraMuons<1)
	 {

	   fill(h_IMmm, InvMass2);
	   
	      acop=3.14159265359-DeltaPhiX(l14vector->Phi(),l24vector->Phi());
	      if(lep1Q<lep2Q)
		theta=acos(tanh((lep1eta-lep2eta)/2));
	      else
		theta=acos(tanh((lep1eta-lep2eta)/2));
	      
	      phiStar=tan(acop/2)*sin(theta);
	      fill(h_liso1mm, liso1);
	      fill(h_liso2mm, liso2);
	   if(liso1<0.12 && liso2<0.15)
	     {
	       if(phiStarMCN>0.0 && phiStarMCB>0.0 && phiStarMCD>0.0 && phiStar>0.0)
		 {
		   fill(h_phiStarMCN, phiStarMCN);
		   fill(h_phiStarMCB, phiStarMCB);
		   fill(h_phiStarMCD, phiStarMCD);
		   fill(h_phiStar, phiStar);
		   if(liso2<0.12)
		     
		     {
		       fill(h_phiStarMCN2, phiStarMCN);
		       fill(h_phiStarMCB2, phiStarMCB);
		       fill(h_phiStarMCD2, phiStarMCD);
		       fill(h_phiStarbiso, phiStar);
		     }	  
		 }
	     }
	   if(liso1<0.12 &&liso2<0.12)
	     {
	       
	       h_vtxCountmm->Fill(Vertices, weight);
	       
	       if(Vertices<=5)
		 {
	       	   fill(h_IMmmvtx1, InvMass2);
		 }
	       if(Vertices>5 && Vertices<=10)
		 {
	       	   fill(h_IMmmvtx2, InvMass2);
		 }
	       if(Vertices>10 && Vertices<=15)
		 {
	       	   fill(h_IMmmvtx3, InvMass2);
		 }
	       if(Vertices>15 && Vertices<=20)
		 {
	       	   fill(h_IMmmvtx4, InvMass2);
		 }
	       if(Vertices>20 && Vertices<=25)
		 {
	       	   fill(h_IMmmvtx5, InvMass2);
		 }
	       if(Vertices>25)
		 {
	       	   fill(h_IMmmvtx6, InvMass2);
		 }
	       
	   

	   fill(h_leadptmm, lep1pt);
	   fill(h_subptmm, lep2pt);


	       fill(h_leta1mm, lep1eta);
	       fill(h_leta2mm, lep2eta);
	       fill(h_lphi1mm, l14vector->Phi());
	       fill(h_lphi2mm, l24vector->Phi());
	       
	       // fill(h_vtxCountmm, vtxCount);
	       fill(h_leadptmm, lep1pt);
	       fill(h_subptmm, lep2pt);
	      //   fill(h_lepton1pt, lep1pt);
	      //    fill(h_lepton2pt, lep2pt);
	      //    fill(h_leptonbothpt, lep1pt);
	      //   fill(h_leptonbothpt, lep2pt);
	      // if(fabs(lep1eta)<1)
	      //	{	
	      //  fill(h_leptonsmalleta, lep1pt);
	      //	  fill(h_lepton1smalleta, lep1pt);
	      //	}
	      //   if(fabs(lep2eta)<1)
	      //	{
	      //  fill(h_leptonsmalleta, lep2pt);
	      //  fill(h_lepton2smalleta, lep2pt);
	      //	} 
	      fill(h_InvMassmm, InvMass2);
	      Zrapid=get_rapid(*l14vector+*l24vector);
	  

			       //cout<<Zrapid<<endl;
	      fill(h_Zrapid, Zrapid);
	     	      fill(h_numJetsmm, numberjets);
		      //double hello= sqrt((l14vector->Px()+l24vector->Px())**2+(l14vector->Py()+l24vector->Py())**2);
	      



	      if(phiStar<0.01)
		{fill(h_RapidphiStar1, Zrapid);
		}
	      if(0.01<phiStar && phiStar<0.1)
		{fill(h_RapidphiStar2, Zrapid);
		}
	      if(0.1<phiStar && phiStar<0.3)
		{fill(h_RapidphiStar3, Zrapid);
		}
	      if(0.3<phiStar&& phiStar<3.277)
		{fill(h_RapidphiStar4, Zrapid);
		}

	   if(fabs(Zrapid)<0.5)
	     {fill(h_phiStarRapid1,phiStar); 
	     }
	   if(fabs(Zrapid)>0.5 && fabs(Zrapid)<1.0)
	     {fill(h_phiStarRapid2,phiStar); 
	     }
	   if(fabs(Zrapid)>1.0 && fabs(Zrapid)<1.5)
	     {fill(h_phiStarRapid3,phiStar); 
	     }
	   if(fabs(Zrapid)>0.5 && fabs(Zrapid)<1.9)
	     {fill(h_phiStarRapid4,phiStar); 
	     }
	   if(fabs(Zrapid)>1.9)
	     {fill(h_phiStarRapid5,phiStar); 
	     }
	    



	      if(!(IS_DATA))
		{
		  //  h_phiStarMC2->Fill(phiStarMC);
		  //   fill(h_phistardiff, phiStarMC-phiStar);
		       //fill(h_phiStar2D1, phiStarMC-phiStar, phiStarMC);
		       // fill(h_phiStar2D2, phiStar, phiStarMC);
		       //   h_phiStar2D1->Fill(phiStar, phiStarMC, weight);
	  //  h_phiStar2D2->Fill(phiStarMC-phiStar, phiStarMC, weight);
	  // h_phiStar2D3->Fill(phiStarMC-phiStar, Zrapid, weight);

	  /*
 if(phiStarMC<0.05&& phiStarMC>0.0)
      	       fill(h_phistardiff1, phiStarMC-phiStar);

 if(phiStarMC<3.14 && phiStarMC>0.5)
      	       fill(h_phistardiff6, phiStarMC-phiStar);

 if(phiStarMC<0.5&& phiStarMC>0.2)
      	       fill(h_phistardiff4, phiStarMC-phiStar);

 if(phiStarMC<0.2&& phiStarMC>0.1)
      	       fill(h_phistardiff3, phiStarMC-phiStar);

 if(phiStarMC<0.1&& phiStarMC>0.05)
   fill(h_phistardiff2, phiStarMC-phiStar);
if(phiStarMC<3.277)
      	       fill(h_phistardiff5, phiStarMC-phiStar);
 if(phiStarMC>3.277)
   fill(h_phistardiff7, phiStarMC-phiStar);
	  */
		}

		        fill(h_ZpTmm,ZpT);
	       fill(h_METSignificancemm, METSignificance);
	       fill(h_delphimm, delphi); 
	        fill(h_Sumptmm, (lep1pt+lep2pt));
	      //  fill(h_lep1dxymm, lep1dxy);
	           fill(h_vertexProbmm, -log10(vertexProb));
	      //fill(h_lep2dxymm, lep2dxy);
	       fill(h_acolmm, acol);
	
	       //       double hello= sqrt((l14vector->Px()+l24vector->Px())**2+(l14vector->Py()+l24vector->Py())**2);
	      
	       h_phiStarvsZpT->Fill(phiStar, ZpT, weight);

		      
	     }
	 }
     }
	 
	 


       //  if(DiLeptonType==3  && aftertrigger==3)
 
	 
  //  if(DiLeptonType==5 && aftertrigger==5)
       if(DiLeptonType==5 && SingleMuonTriggeriso==1)
	 {weighta=weightb=weightc=1.0;
	 
      if(IS_DATA)
	{
	  muCorrector->momcor_data(*l14vector,lep1Q,0,qter); 
	   lep1pt=l14vector->Pt();

	}
      else
	{
	  
	  muCorrector->momcor_mc(*l14vector,lep1Q,0,qter);
	  lep1pt=l14vector->Pt();
	   lep1eta=l14vector->Eta();

	  weighta=GetMuEff(lep1pt, lep1eta);
	  weightb=GetElEff(lep2pt, lep2eta);
	  weightc=TriggerMuEff(lep1pt, lep1eta);

	  //weightc=triggerEff(lep1pt, lep1eta, lep2pt, lep2eta);
	  //	      cout<<weight<<" , ";
			//apply single muon or single electron or both trigger weights to the MC files
	    /*
      if(SingleMuonTriggeriso==1 && !(SingleElectronTrigger==1))
	{
	  weightc=TriggerMuEff(lep1pt, lep1eta);
	}
      else if(!(SingleMuonTriggeriso==1) && (SingleElectronTrigger==1))
	{
	  weightc=TriggerElEff(lep1pt, lep1eta);
	    }
      else if(SingleMuonTriggeriso==1 && (SingleElectronTrigger==1))
	{
	  weightc=TriggerMuEff(lep1pt, lep1eta)*TriggerElEff(lep1pt, lep1eta);
	}
	    */
	  weight=weight*weighta*weightb*weightc; 
	}
	   lep1eta=l14vector->Eta();
	   lep2eta=l24vector->Eta();
	   lep1phi=l14vector->Phi();
	   lep2phi=l24vector->Phi();
    
	   if(liso1<0.12 && liso2<0.5 && l14vector->Pt()>30 && l24vector->Pt()>20 )
	     {
	       
	       if(l14vector->Pt()>l24vector->Pt())
		 {
		   leadeta=l14vector->Eta(); 
		 }
	       else
		 {
		   leadeta=l24vector->Eta(); 
		 }
	       if(fabs(leadeta)<2.1 && fabs(l14vector->Eta())<2.4 && fabs(l14vector->Eta())<2.4 )
		 {
		   
	   if(fabs(lep2eta)<1.44 || fabs(lep2eta)>1.57)
	     {
             InvMass2=get_mass(*l14vector+*l24vector);
	     if( InvMass2>60&& InvMass2<120 && extraElectrons<1 && extraMuons<1)
	       {
		 //		 cout<<"HERESONE"<<endl;
	      

		 acop=3.14159265359-DeltaPhiX(l14vector->Phi(),l24vector->Phi());
		 if(lep1Q<lep2Q)
		   theta=acos(tanh((lep1eta-lep2eta)/2));
		 else
		   theta=acos(tanh((lep1eta-lep2eta)/2));
		 
		 phiStar=tan(acop/2)*sin(theta);
		 fill(h_phiStarem, phiStar);
		 
		 
		 fill(h_leadptem, l14vector->Pt());
		 fill(h_subptem, l24vector->Pt());
		 fill(h_InvMassem, InvMass2);
		 		 h_vtxCountem->Fill(Vertices, weight);

		 if(phiStar>1.153 && phiStar<3.277)
		   {
		    
		     fill(h_EMPSLleadpt, l14vector->Pt());
		     fill(h_EMPSLsubpt, l24vector->Pt());
		     fill(h_EMPSLl1eta, l14vector->Eta());
		     fill(h_EMPSLl2eta, l24vector->Eta());
		     fill(h_EMPSLIM, InvMass2);
		     fill(h_EMPSLZpT, ZpT);
		     fill(h_EMPSLNJ, numberjets);
		     if(numberjets==0)
		       {
			 h_vtxCountSLN->Fill(Vertices, weight);

			 fill(h_EMPSLNmET, met);
			 fill(h_EMPSLNIM, InvMass2);


		       }
		     if(numberjets>0)
		       {
			 fill(h_EMPSL1mET, met);
			 fill(h_EMPSL1IM, InvMass2);
			 h_vtxCountSL1->Fill(Vertices, weight);

		       }

		   }
		 if(phiStar>0.524 && phiStar<1.153)
		   {
		     
		     fill(h_EMPSMleadpt, l14vector->Pt());
		     fill(h_EMPSMsubpt, l24vector->Pt());
		     fill(h_EMPSMl1eta, l14vector->Eta());
		     fill(h_EMPSMl2eta, l24vector->Eta());
		     fill(h_EMPSMIM, InvMass2);
		     fill(h_EMPSMZpT, ZpT);
		     fill(h_EMPSMNJ, numberjets);

		     if(numberjets==0)
		       {
			 fill(h_EMPSMNmET, met);
			 fill(h_EMPSMNIM, InvMass2);
			 h_vtxCountSMN->Fill(Vertices, weight);

		       }
		     if(numberjets>0)
		       {
			 fill(h_EMPSM1mET, met);
			 fill(h_EMPSM1IM, InvMass2);
			 h_vtxCountSM1->Fill(Vertices, weight);

		       }

		   }

		 if(phiStar>0.258 && phiStar<0.524)
		   {
		     
		     fill(h_EMPSSleadpt, l14vector->Pt());
		     fill(h_EMPSSsubpt, l24vector->Pt());
		     fill(h_EMPSSl1eta, l14vector->Eta());
		     fill(h_EMPSSl2eta, l24vector->Eta());
		     fill(h_EMPSSIM, InvMass2);
		     fill(h_EMPSSZpT, ZpT);
		     fill(h_EMPSSNJ, numberjets);

		     if(numberjets==0)
		       {
			 fill(h_EMPSSNmET, met);
			 fill(h_EMPSSNIM, InvMass2);
			 h_vtxCountSSN->Fill(Vertices, weight);


		       }
		     if(numberjets>0)
		       {
			 fill(h_EMPSS1mET, met);
			 fill(h_EMPSS1IM, InvMass2);
			 h_vtxCountSS1->Fill(Vertices, weight);

		       }

		   }
		 //  cout<<"hello"<<endl;
		 
		 
		 
		 fill(h_ZpTem, ZpT);
		 // fill(h_delphiem, delphi); 
		 //   fill(h_lep1dxyem, lep1dxy);
		 // fill(h_lep2dxyem, lep2dxy);
		 
		 
	       }
	     }	     
	   
		 }
	     }
	 }
	 }
	 }

    h_vtxCount->Fill(Vertices, weight);

	
	 
  // cout<<eventid<<endl;
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either AnalyzerPS::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

	 
   return kTRUE;
}

void AnalyzerPS::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void AnalyzerPS::Terminate()
{

   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  for(int i=0; i<36 ;i++)
    {
      Double_t bin = h_phiStar->GetBinContent(i);
      Double_t error = h_phiStar->GetBinError(i);
      Double_t width = h_phiStar->GetBinWidth(i);
      h_phiStar->SetBinContent(i, bin/width);
      h_phiStar->SetBinError(i, error/width);
      bin=error=width=0.0;
      bin = h_phiStarMC->GetBinContent(i);
      error = h_phiStarMC->GetBinError(i);
      width = h_phiStarMC->GetBinWidth(i);
      h_phiStarMC->SetBinContent(i, bin/width);
      h_phiStarMC->SetBinError(i, error/width);
      bin=error=width=0.0;

      bin = h_phiStarMCB->GetBinContent(i);
      error = h_phiStarMCB->GetBinError(i);
      width = h_phiStarMCB->GetBinWidth(i);
      h_phiStarMCB->SetBinContent(i, bin/width);
      h_phiStarMCB->SetBinError(i, error/width);
      bin=error=width=0.0;

      bin = h_phiStarMCD->GetBinContent(i);
      error = h_phiStarMCD->GetBinError(i);
      width = h_phiStarMCD->GetBinWidth(i);
      h_phiStarMCD->SetBinContent(i, bin/width);
      h_phiStarMCD->SetBinError(i, error/width);

      bin=error=width=0.0;
      bin = h_phiStarMCN->GetBinContent(i);
      error = h_phiStarMCN->GetBinError(i);
      width = h_phiStarMCN->GetBinWidth(i);
      h_phiStarMCN->SetBinContent(i, bin/width);
      h_phiStarMCN->SetBinError(i, error/width);

      bin=error=width=0.0;

      bin = h_phiStarMCB2->GetBinContent(i);
      error = h_phiStarMCB2->GetBinError(i);
      width = h_phiStarMCB2->GetBinWidth(i);
      h_phiStarMCB2->SetBinContent(i, bin/width);
      h_phiStarMCB2->SetBinError(i, error/width);

      bin=error=width=0.0;
      bin = h_phiStarMCD2->GetBinContent(i);
      error = h_phiStarMCD2->GetBinError(i);
      width = h_phiStarMCD2->GetBinWidth(i);
      h_phiStarMCD2->SetBinContent(i, bin/width);
      h_phiStarMCD2->SetBinError(i, error/width);
      bin=error=width=0.0;

      bin = h_phiStarMCN2->GetBinContent(i);
      error = h_phiStarMCN2->GetBinError(i);
      width = h_phiStarMCN2->GetBinWidth(i);
      h_phiStarMCN2->SetBinContent(i, bin/width);
      h_phiStarMCN2->SetBinError(i, error/width);
      bin=error=width=0.0;
      
      bin = h_phiStarMC2->GetBinContent(i);
      error = h_phiStarMC2->GetBinError(i);
      width = h_phiStarMC2->GetBinWidth(i);
      h_phiStarMC2->SetBinContent(i, bin/width);
      h_phiStarMC2->SetBinError(i, error/width);
    }
  
      if(filetype==1)
	 {
      myfile.open("/uscms_data/d3/nmucia2/dblcountfiles/SMD.txt");
       string mySting = ss.str();

       myfile<< mySting;

      myfile.close();
	 }
  f_elrewe->Close();

   f->Write();
   f->Close();


}
//===================================================================//

void AnalyzerPS::fill(TH1D* h, int value)
{
  fill(h, (double)(value));
}

//===================================================================//

void AnalyzerPS::fill(TH1D* h, double value)
{
  //  cout<<weight<<endl;

  h->Fill(value, weight);
}

//===================================================================//

double AnalyzerPS::get_pT(TLorentzVector v)
{
  return sqrt(v.Px()*v.Px() + v.Py()*v.Py());
}
////
double AnalyzerPS::get_mass(TLorentzVector pll)
{
  return pll.M();
}
double AnalyzerPS::get_rapid(TLorentzVector pll)
{
  return pll.Rapidity();
}
float AnalyzerPS::GetMuEff(double pt, double eta) const
{ // TGraphErrors *_isorewe[4];
  //  TFile* f_muisorewe = new TFile("MuonEfficiencies_ISO_Run_2012ReReco_53X.root", "OPEN"); 
    //    _isorewe[0] = (TGraphErrors*)f_muisorewe->Get("DATA_over_MC_combRelIsoPF04dBeta<012_Tight_pt_abseta<0.9");
     //    _isorewe[1] = (TGraphErrors*)f_muisorewe->Get("DATA_over_MC_combRelIsoPF04dBeta<012_Tight_pt_abseta0.9-1.2");
      //      _isorewe[2] = (TGraphErrors*)f_muisorewe->Get("DATA_over_MC_combRelIsoPF04dBeta<012_Tight_pt_abseta1.2-2.1");
  //   _isorewe[3] = (TGraphErrors*)f_muisorewe->Get("DATA_over_MC_combRelIsoPF04dBeta<012_Tight_pt_abseta2.1-2.4");
    int etaBin = 0;
    float binningEta[] = {0., 0.9, 1.2, 2.1, 2.4};
    float weighta = 1.;
 
    for (int i = 0; i < 4; ++i) {
        if (fabs(eta) > binningEta[i] && fabs(eta) <= binningEta[i+1]) {
            etaBin = i;
            break;
        }
    }

    if (pt < 500.)
      {
	//	cout<<weighta<<endl;
	weighta =_isorewe[etaBin]->Eval(pt);
	//      cout<<weighta<<endl;
	weighta=weighta*_idrewe[etaBin]->Eval(pt);
	//    cout << etaBin << "\t" << lep.Pt() << "\t" << weighta << endl;
      }
    else
      weighta = 1;
    
    return weighta;
}

float AnalyzerPS::GetElEff(double pt, double eta) 
{

  float weighta=1.0;
  int etaBin=0;
  int ptBin=0;
  float binningEta[] = {0.0,0.8,1.4442,2.0,2.5};
  float binningPt[] = {10.,15.,20.,30.,40. ,50.,9999999999999.,};
  if(pt<15)
    { return 1.0;
    }

  for(int i=0; i<4; i++)
    {
      if(fabs(eta)> binningEta[i] && fabs(eta)<= binningEta[i+1])
	{
	etaBin= i;
	break;
	}
    }
  for(int i=0; i<6; i++)
    {
      if(pt>binningPt[i] && pt<binningPt[i+1])
	{
	  ptBin = i;
	  break;
	}

    }
  weighta = _elrewe->GetBinContent(etaBin+1, ptBin+1);
 


  //  cout<<endl<<endl; 
 //_elrewe->Print("elerewe.eps");

  

  return weighta;

}
//==================================================================//
 float AnalyzerPS::TriggerMuEff(double pt, double eta)
 {

  if(pt<25)
    return 1.;
 if(fabs(eta)<0.9)
   return 0.9837;
 if(fabs(eta)>0.9 &&fabs(eta)<1.2)
   return 0.9656;
 if(fabs(eta)>1.2)
   return 0.9962;
 else
   return 1.;

   

 }
//===================================================================//
 float AnalyzerPS::TriggerElEff(double pt, double eta)
 {

  if(pt<30)
    return 1.;
 if(fabs(eta)<0.8)
   {
     if(pt>30 && pt<40)
       return 0.987;
  if(pt>40 && pt<50)
       return 0.997;
  if(pt>50)
       return 0.998;
   }

 if(fabs(eta)>0.9 &&fabs(eta)<1.2)
   {
  if(pt>30 && pt<40)
       return 0.964;
  if(pt>40 && pt<50)
       return 0.980;
  if(pt>50)
       return 0.988;
   }
 if(fabs(eta)>1.2)   
   {
     if(pt>30 && pt<40)
       return 1.004;
     if(pt>40 && pt<50)
       return 1.033;
     if(pt>50)
       return 0.976;
   }
 else
   return 1.;

   
 return 1.; 
 }


double AnalyzerPS::DeltaPhiX(double phi1, double phi2)
{
  double dphi = (phi1 - phi2);

  while(dphi > 3.14159265359)      dphi -= 2.*3.14159265359;
  while(dphi <= -3.14159265359)    dphi += 2.*3.14159265359;
  
  return fabs(dphi);
}

//====================================================================//

void AnalyzerPS::WisolationStudy()
{
  double acopW=0.0;
  double thetaW=0.0;
  double phiStarW=0.0;
  if(Mpt>30 && Npt>20 && Mpt>Npt && fabs(Neta) < 2.4 && fabs(Meta)<2.4 )
    {
      
      acopW=3.14159265359-DeltaPhiX(Mphi,Nphi);
      //if(MC1Q<MC2Q)
      thetaW=acos(tanh((Meta-Neta)/2));
      // else
      // thetaMC=acos(tanh((MC2eta-MC1eta)/2));
      
      phiStarW=tan(acopW/2)*sin(thetaW);

      fill(h_phiStarWiso1, phiStarW);
      fill(h_drjetWiso1, Njetd);
      fill(h_Nisolation1, Nisolation);

      //  cout<<Nisolation<<endl;
      if(Nisolation < 0.12)
	{
	  //  cout<<Nisolation<<endl;
	  fill(h_phiStarWiso2, phiStarW);
	  fill(h_drjetWiso2, Njetd);
	}
      else
	{
	  fill(h_phiStarWiso3, phiStarW);
	  fill(h_drjetWiso3, Njetd);
	}


      if(Njetd<0.3)
	{
	  fill(h_phiStarWiso4, phiStarW);
	  fill(h_Nisolation2, Nisolation);

	}
      else
	{
	  fill(h_phiStarWiso5, phiStarW);
	  fill(h_Nisolation3, Nisolation);
	}



    } 
  
  
}
//========================================================================//
float AnalyzerPS::triggerEff(double pt1, double eta1, double pt2, double eta2)
{
    float binningEta[] = {0., 0.9, 1.2, 2.1, 2.4};
    double weight=1;
    int eta1Bin, eta2Bin;
    for (int i = 0; i < 4; ++i) {
        if (fabs(eta1) > binningEta[i] && fabs(eta1) <= binningEta[i+1]) {
            eta1Bin = i;
            break;
        }
    }  
    for (int i = 0; i < 4; ++i) {
        if (fabs(eta2) > binningEta[i] && fabs(eta2) <= binningEta[i+1]) {
            eta2Bin = i;
            break;
        }
	if(eta1Bin<eta2Bin)
	  {
	    if(pt1<20)
	      {
		if(eta1Bin<2 && eta2Bin<2)
		  weight=.979; 
		else if(eta1Bin>1 && eta2Bin<2)
		  weight=.980;
		else if(eta1Bin<2 && eta2Bin>1)
		  weight=.992;
		else if(eta1Bin>1 && eta2Bin>1)
		  weight=1.030;
	      }
	    else
	      {if(eta1Bin==1 && eta2Bin==1)
		  weight=0.987;
		else if(eta1Bin==2 && eta2Bin==2)
		  weight=0.997;
		else if(eta1Bin==3 && eta2Bin==3)
		  weight=1.014;
		else if(eta1Bin==4 && eta2Bin==4)
		  weight=1.036;
		else if(eta1Bin==1 && eta2Bin==2)
		  weight=0.987;
		else if(eta1Bin==1 && eta2Bin==3)
		  weight=1.007;
		else if(eta1Bin==1 && eta2Bin==4)
		  weight=1.023;
		else if(eta1Bin==2 && eta2Bin==3)
		  weight=1.008;
		else if(eta1Bin==2 && eta2Bin==4)
		  weight=1.007;
		else if(eta1Bin==3 && eta2Bin==4)
		  weight=1.010;
	      }
	  }	  
	else
	  {
	    if( pt2<20)
	      {	if(eta1Bin<2 && eta2Bin<2)
		  weight=.979;
		else if(eta1Bin>1 && eta2Bin<2)
		  weight=.992;
		else if(eta1Bin<2 && eta2Bin>1)
		  weight=.980;
		else if(eta1Bin>1 && eta2Bin>1)
		  weight=1.030;
	      }
	    else
	      {if(eta1Bin==1 && eta2Bin==1)
		  weight=0.987;
		else if(eta1Bin==2 && eta2Bin==2)
		  weight=0.997;
		else if(eta1Bin==3 && eta2Bin==3)
		  weight=1.014;
		else if(eta1Bin==4 && eta2Bin==4)
		  weight=1.036;
		else if(eta1Bin==2 && eta2Bin==1)
		  weight=0.987;
		else if(eta1Bin==3 && eta2Bin==1)
		  weight=1.007;
		else if(eta1Bin==4 && eta2Bin==1)
		  weight=1.023;
		else if(eta1Bin==3 && eta2Bin==2)
		  weight=1.008;
		else if(eta1Bin==4 && eta2Bin==2)
		  weight=1.007;
		else if(eta1Bin==4 && eta2Bin==3)
		  weight=1.010;
	      }
	  }

    }
 
    return weight;
}
//===================================================================
