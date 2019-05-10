#include <iostream>
#include <algorithm>

void INT_analysis(std::vector<TString> INTfiles)
{
  TString filePrefix = "../../wafer/";
  TString padPrefix = "pad_plot_";
  Data_vs_TID_INT datavTID_INT_8;
  Data_vs_TID_INT datavTID_INT_9;
  int filecount{0};
  int processedfilecount{0};
  int padcount{0};
  int processedpadcount{0};
  std::string line{""};
  ofstream acceptedFiles;
  acceptedFiles.open("Accepted_INT_Files.txt");
  ofstream rejectedFiles;
  rejectedFiles.open("Rejected_INT_Files.txt");

  //For each file...
  for(int filenumber{0}; filenumber<INTfiles.size(); ++filenumber)
    {
      line = INTfiles[filenumber];      
      std::string fileName = line;	  
      TString filePath = filePrefix+fileName;

      //Define graph names for each pad
      std::vector<TString> graphName = {"Graph","Graph","gTRDAC","gVRef","gVCD","gCALLINE","gTHDAC","gVTHTEST","gCOM","Graph","Graph","Graph","gIRef","gR8B","gVB","Graph","Graph","Graph"};
      TFile *inFile = new TFile(filePath);
      if(inFile->IsZombie()){}
      else if(!inFile->IsZombie())
	{
	  ++filecount;
	  for(int i{0}; i<2; ++i)
	    {
	      ++padcount;
	      Data data;
	      TID_Data TID;
	      TString padName;
	      padName = padPrefix + std::to_string(i+1);
	      data = ProcessRootFile(fileName,padName,graphName[i],i);

	      if(data.init_check==false){break;}
	      
	      //Manipulate data for each pad
	      std::size_t chip008 = line.find("008");
	      std::size_t chip009 = line.find("009");	      
	      switch(i)
		{
		case 0:
		  TID = Functions(data,i,"INT",fileName);
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_INT_8.fileName.push_back(TID.fileName);
		      datavTID_INT_8.timeStamp.push_back(TID.timeStamp);
		      datavTID_INT_8.MRad.push_back(TID.MRad);
		      datavTID_INT_8.VDDA_vs_LDOA_disc_x.push_back(TID.disc_x);
		      datavTID_INT_8.VDDA_vs_LDOA_disc_y.push_back(TID.disc_y);
		      ++processedfilecount;
		      ++processedpadcount;
		      acceptedFiles<<fileName<<std::endl;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_INT_9.fileName.push_back(TID.fileName);
		      datavTID_INT_9.timeStamp.push_back(TID.timeStamp);
		      datavTID_INT_9.MRad.push_back(TID.MRad);
		      datavTID_INT_9.VDDA_vs_LDOA_disc_x.push_back(TID.disc_x);
		      datavTID_INT_9.VDDA_vs_LDOA_disc_y.push_back(TID.disc_y);
		      ++processedfilecount;
		      ++processedpadcount;
		      acceptedFiles<<fileName<<std::endl;
		    }
		  else
		    {
		      rejectedFiles<<fileName<<padName<<std::endl;
		    }
		  break;

		case 1:
		  TID = Functions(data,i,"INT",fileName);
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_INT_8.VDDD_vs_LDOD_disc_x.push_back(TID.disc_x);
		      datavTID_INT_8.VDDD_vs_LDOD_disc_y.push_back(TID.disc_y);
		      ++processedpadcount;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_INT_9.VDDD_vs_LDOD_disc_x.push_back(TID.disc_x);
		      datavTID_INT_9.VDDD_vs_LDOD_disc_y.push_back(TID.disc_y);
		      ++processedpadcount;
		    }
		  
		  else
		    {
		      rejectedFiles<<fileName<<padName<<std::endl;
		    }
		  break;

		case 2:
		  TID = Functions(data,i,"INT",fileName);
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_INT_8.TRDACfitp0.push_back(TID.redfitp0);
		      datavTID_INT_8.TRDACfitp1.push_back(TID.redfitp1);
		      ++processedpadcount;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_INT_9.TRDACfitp0.push_back(TID.redfitp0);
		      datavTID_INT_9.TRDACfitp1.push_back(TID.redfitp1);
		      ++processedpadcount;
		    }
		  else
		    {
		      rejectedFiles<<fileName<<padName<<std::endl;
		    }
		  break;

		case 3:
		  TID = Functions(data,i,"INT",fileName);
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_INT_8.VReffitp0.push_back(TID.redfitp0);
		      datavTID_INT_8.VReffitp1.push_back(TID.redfitp1);
		      ++processedpadcount;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_INT_9.VReffitp0.push_back(TID.redfitp0);
		      datavTID_INT_9.VReffitp1.push_back(TID.redfitp1);
		      ++processedpadcount;
		    }
		  else
		    {
		      rejectedFiles<<fileName<<padName<<std::endl;
		    }
		  break;
		}
	    }
	}
    }
  acceptedFiles.close();
  rejectedFiles.close();
  std::cout<<"================================================================================================"<<std::endl;	        

  PlotFunctionsINT(datavTID_INT_8, datavTID_INT_9);
  
  std::cout<<"================================================================================================\nINT\n"<<std::endl;	      
  std::cout<<"Total number of files read = "<<filecount<<std::endl;
  std::cout<<"Total number of files processed = "<<processedfilecount<<std::endl;
  std::cout<<"Total number of files rejected  = "<<filecount-processedfilecount<<std::endl;
  std::cout<<"\n";
  std::cout<<"Total number of pads read = "<<padcount<<std::endl;
  std::cout<<"Total number of pads processed = "<<processedpadcount<<std::endl;
  std::cout<<"Total number of pads rejected = "<<padcount-processedpadcount<<std::endl;
  std::cout<<"\n";
  std::cout<<"Ratio pads:files read = " << (padcount*1.)/(filecount*1.)<<std::endl;
  std::cout<<"Ratio pads:files processed = " << (processedpadcount*1.)/(processedfilecount*1.)<<std::endl;
  std::cout<<"Ratio pads:files rejected = " << ((padcount-processedpadcount)*1.)/((filecount-processedfilecount)*1.)<<std::endl;
  std::cout<<"\n";
  std::cout<<"================================================================================================"<<std::endl;
}
