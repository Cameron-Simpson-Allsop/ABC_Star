#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Data
{
  std::vector<double> TID; //Dose rate x time
  std::vector<double> VDDA; //Analogue voltage 
  std::vector<double> VDDD; //Digital voltage
  std::vector<double> IDDA; //Analogue current
  std::vector<double> IDDD; //Digital current
  // std::vector<double> IDDD1; //Digital current (lower line one)
  std::vector<double> Vset; //Set voltage
  std::vector<double> Vact; //Actual voltage
  std::vector<double> Iset; //Set current
  std::vector<double> Iact; //Actual current
  //Units for currents and voltages are all SI
};

Data ProcessFile(std::string filePath)
{
  Data data;
  std::string errorMsg{"Error opening file '"+filePath+"'..."};
  std::string successMsg{"File '"+filePath+"' succesfully processed..."};
  std::string fileLine{""};
  std::size_t TID_marker;
  std::size_t VDDA_IDDA_marker;
  std::size_t VDDD_IDDD_marker;
  std::size_t Vset_Vact_marker;
  std::size_t Iset_Iact_marker;
  ifstream inFile;
  inFile.open(filePath);
  if(!inFile.good())
    {
      std::cout<<errorMsg<<std::endl;
      return data;
    }
  while(!inFile.eof())
    {
      getline(inFile,fileLine);
      TID_marker = fileLine.find("TOTAL TID");
      VDDA_IDDA_marker = fileLine.find("VDDA");
      VDDD_IDDD_marker = fileLine.find("VDDD");
      Vset_Vact_marker = fileLine.find("V(set)");
      Iset_Iact_marker = fileLine.find("I(set)");
      if(TID_marker != std::string::npos)
	{
	  std::string tmp1,tmp2,tmp3;
	  double TID;
	  stringstream ss(fileLine);
	  ss >> tmp1 >> tmp2 >> tmp3 >> TID;
	  data.TID.push_back(TID);
	}
      else if(VDDA_IDDA_marker != std::string::npos)
	{
	  std::string tmp1,tmp2,tmp3,tmp4;
	  double VDDA,IDDA;
	  stringstream ss(fileLine);
	  ss >> tmp1 >> tmp2 >> VDDA >> tmp3 >> tmp4 >> IDDA;
	  data.VDDA.push_back(VDDA);
	  data.IDDA.push_back(IDDA);
	}
      else if(VDDD_IDDD_marker != std::string::npos)
	{
	  std::string tmp1,tmp2,tmp3,tmp4;
	  double VDDD,IDDD;
	  stringstream ss(fileLine);
	  ss >> tmp1 >> tmp2 >> VDDD >> tmp3 >> tmp4 >> IDDD;
	  data.VDDD.push_back(VDDD);
	  data.IDDD.push_back(IDDD);
	}
      else if(Vset_Vact_marker != std::string::npos)
	{
	  std::string tmp1,tmp2,tmp3,tmp4;
	  double Vset,Vact;
	  stringstream ss(fileLine);
	  ss >> tmp1 >> tmp2 >> Vset >> tmp3 >> tmp4 >> Vact;
	  data.Vset.push_back(Vset);
	  data.Vact.push_back(Vact);	  
	}
      else if(Iset_Iact_marker != std::string::npos)
	{
	  std::string tmp1,tmp2,tmp3,tmp4;
	  double Iset,Iact;
	  stringstream ss(fileLine);
	  ss >> tmp1 >> tmp2 >> Iset >> tmp3 >> tmp4 >> Iact;
	  data.Iset.push_back(Iset);
	  data.Iact.push_back(Iact);	  
	}
    }
  std::cout<<"\n\n Beginning file '"+filePath+"'..."<<"\n\n"<<std::endl;
  // for(int i{0}; i<data.Total_TID.size(); ++i)
  //   {
  //     std::cout<<"=============================="<<std::endl;
  //     std::cout<<"TOTAL TID = "<<data.Total_TID[i]<<std::endl;
  //     std::cout<<"VDDA = "<<data.VDDA[i]<<"\t"<<"IDDA = "<<data.IDDA[i]<<std::endl;
  //     std::cout<<"VDDD = "<<data.VDDD[i]<<"\t"<<"IDDD = "<<data.IDDD[i]<<std::endl;
  //     std::cout<<"V(set) = "<<data.Vset[i]<<"\t"<<"V(act) = "<<data.Vact[i]<<std::endl;
  //     std::cout<<"I(set) = "<<data.Iset[i]<<"\t"<<"I(act) = "<<data.Iact[i]<<std::endl;
  //     std::cout<<"=============================="<<std::endl;
  //   }
  std::cout<<successMsg<<std::endl;
  return data;
}

void PlotSettings(TGraph *g,TString xtitle,TString ytitle)
{
  g->SetTitle("");
  g->GetXaxis()->SetTitle(xtitle);
  g->GetYaxis()->SetTitle(ytitle);
}

void Plotter(Data chipdata,TString canTitle)
{
  TGraph *VDDA_vs_TID = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.VDDA[0]));
  PlotSettings(VDDA_vs_TID,"TID [MRad]","VDDA [V]");
  TGraph *VDDD_vs_TID = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.VDDD[0]));
  PlotSettings(VDDD_vs_TID,"TID [MRad]","VDDD [V]");
  TGraph *IDDA_vs_TID = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.IDDA[0]));
  PlotSettings(IDDA_vs_TID,"TID [MRad]","IDDA [A]");
  TGraph *IDDD_vs_TID = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.IDDD[0]));
  PlotSettings(IDDD_vs_TID,"TID [MRad]","IDDD [A]");
  TGraph *Vset_vs_TID = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.Vset[0]));
  PlotSettings(Vset_vs_TID,"TID [MRad]","V(set) [V]");
  TGraph *Vact_vs_TID = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.Vact[0]));
  PlotSettings(Vact_vs_TID,"TID [MRad]","V(act) [V]");
  TGraph *Iset_vs_TID = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.Iset[0]));
  PlotSettings(Iset_vs_TID,"TID [MRad]","I(set) [A]");
  TGraph *Iact_vs_TID = new TGraph(chipdata.TID.size(),&(chipdata.TID[0]),&(chipdata.Iact[0]));
  PlotSettings(Iact_vs_TID,"TID [MRad]","I(act) [A]");

  TCanvas *canvas = new TCanvas(canTitle,canTitle,600,600);
  canvas->Divide(4,2);
  canvas->cd(1);
  VDDA_vs_TID->Draw("AL");
  canvas->cd(2);
  VDDD_vs_TID->Draw("AL");
  canvas->cd(3);
  IDDA_vs_TID->Draw("AL");
  canvas->cd(4);
  IDDD_vs_TID->Draw("AL");
  canvas->cd(5);
  Vset_vs_TID->Draw("AL");
  canvas->cd(6);
  Vact_vs_TID->Draw("AL");
  canvas->cd(7);
  Iset_vs_TID->Draw("AL");
  canvas->cd(8);
  Iact_vs_TID->Draw("AL");

  TString IDDDTitle = canTitle + " IDDD";
  TCanvas *canvasIDDD = new TCanvas(IDDDTitle,IDDDTitle,600,600);
  IDDD_vs_TID->Draw("AL");
}

void XRY_analysis()
{
  Data chip190 = ProcessFile("../logs/XRY_monitoring_190.txt");
  Data chip204 = ProcessFile("../logs/XRY_monitoring_204.txt");
  Plotter(chip190,"ABCStar 190");
  Plotter(chip204,"ABCStar 204");
}
