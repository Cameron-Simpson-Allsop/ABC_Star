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
  int rejectfilecount{0};
  std::string line{""};
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
	  bool fileReject = false;
	  double timeStamp_8, MRad_8, VDDA_vs_LDOA_disc_x_8, VDDA_vs_LDOA_disc_y_8, VDDD_vs_LDOD_disc_x_8, VDDD_vs_LDOD_disc_y_8, TRDACfitp0_8, TRDACfitp1_8, VReffitp0_8, VReffitp1_8;
	  double timeStamp_9, MRad_9, VDDA_vs_LDOA_disc_x_9, VDDA_vs_LDOA_disc_y_9, VDDD_vs_LDOD_disc_x_9, VDDD_vs_LDOD_disc_y_9, TRDACfitp0_9, TRDACfitp1_9, VReffitp0_9, VReffitp1_9;
	  std::size_t chip008 = line.find("008");
	  std::size_t chip009 = line.find("009");
	  ++filecount;
	  int N = 4;
	  for(int i{0}; i<N; ++i)
	    {
	      ++padcount;
	      Data data;
	      TID_Data TID;
	      TString padName;
	      padName = padPrefix + std::to_string(i+1);
	      data = ProcessRootFile(fileName,padName,graphName[i],i);

	      if(data.init_check==false){++rejectfilecount; break;}
	      
	      //Manipulate data for each pad	      
	      switch(i)
		{
		case 0:
		  TID = Functions(data,i,"INT",fileName);
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      timeStamp_8=TID.timeStamp;
		      MRad_8=TID.MRad;
		      VDDA_vs_LDOA_disc_x_8=TID.disc_x;
		      VDDA_vs_LDOA_disc_y_8=TID.disc_y;	
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      timeStamp_9=TID.timeStamp;
		      MRad_9=TID.MRad;
		      VDDA_vs_LDOA_disc_x_9=TID.disc_x;
		      VDDA_vs_LDOA_disc_y_9=TID.disc_y;	
		    }
		  else if(TID.init_check==false)
		    {
		      rejectedFiles<<fileName<<"\t"<<padName<<std::endl;
		      fileReject=true;
		    }
		  break;

		case 1:
		  TID = Functions(data,i,"INT",fileName);
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      VDDD_vs_LDOD_disc_x_8=TID.disc_x;
		      VDDD_vs_LDOD_disc_y_8=TID.disc_y;			      
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      VDDD_vs_LDOD_disc_x_9=TID.disc_x;
		      VDDD_vs_LDOD_disc_y_9=TID.disc_y;
		    }		  
		  else if(TID.init_check==false)
		    {
		      rejectedFiles<<fileName<<"\t"<<padName<<std::endl;
		      fileReject=true;
		    }
		  break;

		  case 2:
		  TID = Functions(data,i,"INT",fileName);
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {		      
		      TRDACfitp0_8=TID.redfitp0;
		      TRDACfitp1_8=TID.redfitp1;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      TRDACfitp0_9=TID.redfitp0;
		      TRDACfitp1_9=TID.redfitp1;
		    }		  
		  else if(TID.init_check==false)
		    {
		      rejectedFiles<<fileName<<"\t"<<padName<<std::endl;
		      fileReject=true;
		    }
		  break;

		case 3:
		  TID = Functions(data,i,"INT",fileName);
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {		      
		      VReffitp0_8=TID.redfitp0;
		      VReffitp1_8=TID.redfitp1;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      VReffitp0_9=TID.redfitp0;
		      VReffitp1_9=TID.redfitp1;
		    }		  
		  else if(TID.init_check==false)
		    {
		      rejectedFiles<<fileName<<"\t"<<padName<<std::endl;
		      fileReject=true;
		    }
		  break;
		}
	    }

	  for(int i{0}; i<N; ++i)
	    {
	      if(fileReject==false && chip008!=std::string::npos && chip009==std::string::npos)
		{
		  ++processedpadcount;
		  switch(i)
		    {
		    case 0:
		      datavTID_INT_8.fileName.push_back(fileName);
		      datavTID_INT_8.timeStamp.push_back(timeStamp_8);
		      datavTID_INT_8.MRad.push_back(MRad_8);
		      datavTID_INT_8.VDDA_vs_LDOA_disc_x.push_back(VDDA_vs_LDOA_disc_x_8);
		      datavTID_INT_8.VDDA_vs_LDOA_disc_y.push_back(VDDA_vs_LDOA_disc_y_8);
		      break;
		      
		    case 1:
		      datavTID_INT_8.VDDD_vs_LDOD_disc_x.push_back(VDDD_vs_LDOD_disc_x_8);
		      datavTID_INT_8.VDDD_vs_LDOD_disc_y.push_back(VDDD_vs_LDOD_disc_y_8);
		      break;

		    case 2:
		      datavTID_INT_8.TRDACfitp0.push_back(TRDACfitp0_8);
		      datavTID_INT_8.TRDACfitp1.push_back(TRDACfitp1_8);
		      break;

		    case 3:
		      datavTID_INT_8.VReffitp0.push_back(VReffitp0_8);
		      datavTID_INT_8.VReffitp1.push_back(VReffitp1_8);
		      break;		      
		    }
		}
	      else if(fileReject==false && chip009!=std::string::npos && chip008==std::string::npos)
		{
		  ++processedpadcount;
		  switch(i)
		    {
		    case 0:
		      datavTID_INT_9.fileName.push_back(fileName);
		      datavTID_INT_9.timeStamp.push_back(timeStamp_9);
		      datavTID_INT_9.MRad.push_back(MRad_9);
		      datavTID_INT_9.VDDA_vs_LDOA_disc_x.push_back(VDDA_vs_LDOA_disc_x_9);
		      datavTID_INT_9.VDDA_vs_LDOA_disc_y.push_back(VDDA_vs_LDOA_disc_y_9);
		      break;
		      
		    case 1:
		      datavTID_INT_9.VDDD_vs_LDOD_disc_x.push_back(VDDD_vs_LDOD_disc_x_9);
		      datavTID_INT_9.VDDD_vs_LDOD_disc_y.push_back(VDDD_vs_LDOD_disc_y_9);
		      break;
		      
		    case 2:
		      datavTID_INT_9.TRDACfitp0.push_back(TRDACfitp0_9);
		      datavTID_INT_9.TRDACfitp1.push_back(TRDACfitp1_9);
		      break;
		      
		    case 3:
		      datavTID_INT_9.VReffitp0.push_back(VReffitp0_9);
		      datavTID_INT_9.VReffitp1.push_back(VReffitp1_9);
		      break;		      
		    }
		}
	    }
	}
    }
  rejectedFiles.close();
  std::cout<<"================================================================================================"<<std::endl;	        

  PlotFunctionsINT(datavTID_INT_8, datavTID_INT_9);
  
  std::cout<<"================================================================================================\nINT\n"<<std::endl;	      
  std::cout<<"Total number of files read = "<<filecount<<std::endl;
  std::cout<<"Total number of files rejected before analysis = "<<rejectfilecount<<std::endl;
  std::cout<<"Total number of pads read = "<<padcount<<std::endl;
  std::cout<<"Ratio pads/files read = "<<(padcount*1.)/(filecount*1.)<<std::endl;
  //std::cout<<"Ratio pads/files read after initial rejection = "<<(padcount*1.)/((filecount-rejectfilecount)*1.)<<std::endl;
  std::cout<<"Total number of pads processed = "<<processedpadcount<<std::endl;
  std::cout<<"Total number of pads rejected  = "<<padcount-processedpadcount<<std::endl;
  std::cout<<"\n";
  // std::cout<<"Total number of pads read = "<<padcount<<std::endl;
  // std::cout<<"Total number of pads processed = "<<processedpadcount<<std::endl;
  // std::cout<<"Total number of pads rejected = "<<padcount-processedpadcount<<std::endl;
  // std::cout<<"\n";
  // std::cout<<"Ratio pads:files read = " << (padcount*1.)/(filecount*1.)<<std::endl;
  // std::cout<<"Ratio pads:files processed = " << (processedpadcount*1.)/(processedfilecount*1.)<<std::endl;
  // std::cout<<"Ratio pads:files rejected = " << ((padcount-processedpadcount)*1.)/((filecount-processedfilecount)*1.)<<std::endl;
  // std::cout<<"\n";
  std::cout<<"================================================================================================"<<std::endl;

  ofstream dataFile;
  dataFile.open("Datafile_INT.txt");

  dataFile<<"FileName\ttimeStamp\tTID\tVDDA_vs_LDOA_disc_x\tVDDA_vs_LDOA_disc_y\tVDDD_vs_LDOD_disc_x\tVDDD_vs_LDOD_disc_y\tTRDACp0\tTRDACp1\tVRefp0\tVRefp1"<<std::endl;
  for(int i{0}; i<datavTID_INT_8.fileName.size(); ++i)
    {
      dataFile<<datavTID_INT_8.fileName[i]<<"\t"<<datavTID_INT_8.timeStamp[i]<<"\t"<<datavTID_INT_8.MRad[i]<<"\t"<<datavTID_INT_8.VDDA_vs_LDOA_disc_x[i]<<"\t"<<datavTID_INT_8.VDDA_vs_LDOA_disc_y[i]<<"\t"<<datavTID_INT_8.VDDD_vs_LDOD_disc_x[i]<<"\t"<<datavTID_INT_8.VDDD_vs_LDOD_disc_y[i]<<"\t"<<datavTID_INT_8.TRDACfitp0[i]<<"\t"<<datavTID_INT_8.TRDACfitp1[i]<<"\t"<<datavTID_INT_8.VReffitp0[i]<<"\t"<<datavTID_INT_8.VReffitp1[i]<<std::endl;
    }
  for(int i{0}; i<datavTID_INT_9.fileName.size(); ++i)
    {
      dataFile<<datavTID_INT_9.fileName[i]<<"\t"<<datavTID_INT_9.timeStamp[i]<<"\t"<<datavTID_INT_9.MRad[i]<<"\t"<<datavTID_INT_9.VDDA_vs_LDOA_disc_x[i]<<"\t"<<datavTID_INT_9.VDDA_vs_LDOA_disc_y[i]<<"\t"<<datavTID_INT_9.VDDD_vs_LDOD_disc_x[i]<<"\t"<<datavTID_INT_9.VDDD_vs_LDOD_disc_y[i]<<"\t"<<datavTID_INT_9.TRDACfitp0[i]<<"\t"<<datavTID_INT_9.TRDACfitp1[i]<<"\t"<<datavTID_INT_9.VReffitp0[i]<<"\t"<<datavTID_INT_9.VReffitp1[i]<<std::endl;
    }
  
  std::cout<<"vector sizes (chip 8): "<<datavTID_INT_8.fileName.size()<<"\t"<<datavTID_INT_8.timeStamp.size()<<"\t"<<datavTID_INT_8.MRad.size()<<"\t"<<datavTID_INT_8.VDDA_vs_LDOA_disc_x.size()<<"\t"<<datavTID_INT_8.VDDA_vs_LDOA_disc_y.size()<<"\t"<<datavTID_INT_8.VDDD_vs_LDOD_disc_x.size()<<"\t"<<datavTID_INT_8.VDDD_vs_LDOD_disc_y.size()<<"\t"<<datavTID_INT_8.TRDACfitp0.size()<<"\t"<<datavTID_INT_8.TRDACfitp1.size()<<"\t"<<datavTID_INT_8.VReffitp0.size()<<"\t"<<datavTID_INT_8.VReffitp1.size()<<std::endl;
  
  std::cout<<"vector sizes (chip 9): "<<datavTID_INT_9.fileName.size()<<"\t"<<datavTID_INT_9.timeStamp.size()<<"\t"<<datavTID_INT_9.MRad.size()<<"\t"<<datavTID_INT_9.VDDA_vs_LDOA_disc_x.size()<<"\t"<<datavTID_INT_9.VDDA_vs_LDOA_disc_y.size()<<"\t"<<datavTID_INT_9.VDDD_vs_LDOD_disc_x.size()<<"\t"<<datavTID_INT_9.VDDD_vs_LDOD_disc_y.size()<<"\t"<<datavTID_INT_9.TRDACfitp0.size()<<"\t"<<datavTID_INT_9.TRDACfitp1.size()<<"\t"<<datavTID_INT_9.VReffitp0.size()<<"\t"<<datavTID_INT_9.VReffitp1.size()<<std::endl;
  
  dataFile.close();
}
