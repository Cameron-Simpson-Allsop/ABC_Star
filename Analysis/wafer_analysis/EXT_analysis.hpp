#include <iostream>
#include <algorithm>

void EXT_analysis(std::vector<TString> EXTfiles)
{
  TString filePrefix = "../../wafer/";
  TString padPrefix = "pad_plot_";
  Data_vs_TID_EXT datavTID_EXT_8;
  Data_vs_TID_EXT datavTID_EXT_9;
  int filecount{0};
  int processedfilecount{0};
  int padcount{0};
  int processedpadcount{0};
  std::string line{""};
  ofstream acceptedFiles;
  acceptedFiles.open("Accepted_EXT_Files.txt");
  ofstream rejectedFiles;
  rejectedFiles.open("Rejected_EXT_Files.txt");
	  
  //For each file...
  for(int filenumber{0}; filenumber<EXTfiles.size(); ++filenumber)
    {
      line = EXTfiles[filenumber]; 
      std::string fileName = line;	  
      TString filePath = filePrefix+fileName;  

      //Define graph names for each pad
      std::vector<TString> graphName = {"Graph","Graph","gTRDAC","gVRef","gIRef","gR8B","gVCD","gCALLINE","gTHDAC","gVTHTEST","gCOM","gDRIVE","gVB","gVTHREF"}; //gVB(same pad as gVCD) gVTHREF(same pad as gVTHTEST)
      TFile *inFile = new TFile(filePath);
      if(inFile->IsZombie()){}
      else if(!inFile->IsZombie())
	{

	  ++filecount;
	  for(int i{0}; i<graphName.size()-1; ++i)
	    {
	      ++padcount;
	      Data data;
	      TID_Data TID;
	      TString padName;
	      if(i<graphName.size()-2) 
		{
		  padName = padPrefix + std::to_string(i+1);
		  data = ProcessRootFile(fileName,padName,graphName[i],i);
		}
	      else if(i == graphName.size()-2)
		{
		  padName = "pad_plot_7";
		  data = ProcessRootFile(fileName,padName,graphName[i],i);
		}
	      else if(i == graphName.size()-1)
		{
		  padName = "pad_plot_10";
		  data = ProcessRootFile(fileName,padName,graphName[i],i);
		}

	      //Manipulate data for each pad
	      std::size_t chip008 = line.find("008");
	      std::size_t chip009 = line.find("009");
	      switch(i)
		{
		case 0:
		  TID = Functions(data,i,"EXT");
		  //limits to ignore any uninitialised variables (Some files have no TID data)
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.VDDA_vs_LDOA_disc_x.push_back(TID.disc_x);
		      datavTID_EXT_8.VDDA_vs_LDOA_disc_y.push_back(TID.disc_y);
		      datavTID_EXT_8.timeStamp.push_back(TID.timeStamp);
		      datavTID_EXT_8.MRad.push_back(TID.MRad);
		      datavTID_EXT_8.marker_xcoord_VDDA.push_back(TID.marker_xcoord);
		      datavTID_EXT_8.marker_ycoord_VDDA.push_back(TID.marker_ycoord);
		      ++processedfilecount;
		      ++processedpadcount;
		      acceptedFiles<<fileName<<std::endl;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.VDDA_vs_LDOA_disc_x.push_back(TID.disc_x);
		      datavTID_EXT_9.VDDA_vs_LDOA_disc_y.push_back(TID.disc_y);
		      datavTID_EXT_9.timeStamp.push_back(TID.timeStamp);
		      datavTID_EXT_9.MRad.push_back(TID.MRad);
		      datavTID_EXT_9.marker_xcoord_VDDA.push_back(TID.marker_xcoord);
		      datavTID_EXT_9.marker_ycoord_VDDA.push_back(TID.marker_ycoord);
		      ++processedfilecount;
		      ++processedpadcount;
		      acceptedFiles<<fileName<<std::endl;
		    }
		  else
		    {
		      rejectedFiles<<fileName<<std::endl;
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;
		  
		case 1:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.VDDD_vs_LDOD_disc_x.push_back(TID.disc_x);
		      datavTID_EXT_8.VDDD_vs_LDOD_disc_y.push_back(TID.disc_y);
		      datavTID_EXT_8.marker_xcoord_VDDD.push_back(TID.marker_xcoord);
		      datavTID_EXT_8.marker_ycoord_VDDD.push_back(TID.marker_ycoord);
		      //std::cout<<"Chip 008"<<std::endl;
		      ++processedpadcount;			  
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.VDDD_vs_LDOD_disc_x.push_back(TID.disc_x);
		      datavTID_EXT_9.VDDD_vs_LDOD_disc_y.push_back(TID.disc_y);
		      datavTID_EXT_9.marker_xcoord_VDDD.push_back(TID.marker_xcoord);
		      datavTID_EXT_9.marker_ycoord_VDDD.push_back(TID.marker_ycoord);
		      //std::cout<<"Chip 009"<<std::endl;
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 2:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.TRDACfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.TRDACfitp1.push_back(TID.redfitp1);
		      ++processedpadcount;			  
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.TRDACfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.TRDACfitp1.push_back(TID.redfitp1);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 3:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.VReffitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.VReffitp1.push_back(TID.redfitp1);
		      datavTID_EXT_8.marker_xcoord_VRef.push_back(TID.marker_xcoord);
		      datavTID_EXT_8.marker_ycoord_VRef.push_back(TID.marker_ycoord);
		      ++processedpadcount;			  
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.VReffitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.VReffitp1.push_back(TID.redfitp1);
		      datavTID_EXT_9.marker_xcoord_VRef.push_back(TID.marker_xcoord);
		      datavTID_EXT_9.marker_ycoord_VRef.push_back(TID.marker_ycoord);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 4:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.IReffitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.IReffitp1.push_back(TID.redfitp1);
		      datavTID_EXT_8.marker_xcoord_IRef.push_back(TID.marker_xcoord);
		      datavTID_EXT_8.marker_ycoord_IRef.push_back(TID.marker_ycoord);
		      ++processedpadcount;			  
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.IReffitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.IReffitp1.push_back(TID.redfitp1);
		      datavTID_EXT_9.marker_xcoord_IRef.push_back(TID.marker_xcoord);
		      datavTID_EXT_9.marker_ycoord_IRef.push_back(TID.marker_ycoord);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 5:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.R8Bfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.R8Bfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_8.marker_xcoord_R8B.push_back(TID.marker_xcoord);
		      datavTID_EXT_8.marker_ycoord_R8B.push_back(TID.marker_ycoord);
		      ++processedpadcount;			  
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.R8Bfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.R8Bfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_9.marker_xcoord_R8B.push_back(TID.marker_xcoord);
		      datavTID_EXT_9.marker_ycoord_R8B.push_back(TID.marker_ycoord);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 6:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.VCDfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.VCDfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_8.VCDfitp2.push_back(TID.redfitp2);
		      datavTID_EXT_8.VCDfitp3.push_back(TID.redfitp3);
		      ++processedpadcount;			  
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.VCDfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.VCDfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_9.VCDfitp2.push_back(TID.redfitp2);
		      datavTID_EXT_9.VCDfitp3.push_back(TID.redfitp3);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 7:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.CALLINEfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.CALLINEfitp1.push_back(TID.redfitp1);
		      ++processedpadcount;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.CALLINEfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.CALLINEfitp1.push_back(TID.redfitp1);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 8:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.THDACfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.THDACfitp1.push_back(TID.redfitp1);
		      ++processedpadcount;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.THDACfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.THDACfitp1.push_back(TID.redfitp1);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 9:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.VTHTESTfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.VTHTESTfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_8.VTHTESTfitp2.push_back(TID.redfitp2);
		      datavTID_EXT_8.VTHTESTfitp3.push_back(TID.redfitp3);
		      ++processedpadcount;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {			  
		      datavTID_EXT_9.VTHTESTfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.VTHTESTfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_9.VTHTESTfitp2.push_back(TID.redfitp2);
		      datavTID_EXT_9.VTHTESTfitp3.push_back(TID.redfitp3);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 10:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.COMfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.COMfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_8.marker_xcoord_COM.push_back(TID.marker_xcoord);
		      datavTID_EXT_8.marker_ycoord_COM.push_back(TID.marker_ycoord);
		      ++processedpadcount;			  
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {
		      datavTID_EXT_9.COMfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.COMfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_9.marker_xcoord_COM.push_back(TID.marker_xcoord);
		      datavTID_EXT_9.marker_ycoord_COM.push_back(TID.marker_ycoord);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 11:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.DRIVEfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.DRIVEfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_8.DRIVEfitp2.push_back(TID.redfitp2);
		      datavTID_EXT_8.DRIVEfitp3.push_back(TID.redfitp3);
		      ++processedpadcount;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {			  
		      datavTID_EXT_9.DRIVEfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.DRIVEfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_9.DRIVEfitp2.push_back(TID.redfitp2);
		      datavTID_EXT_9.DRIVEfitp3.push_back(TID.redfitp3);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;

		case 12:
		  TID = Functions(data,i,"EXT");
		  if(TID.init_check == true && chip008 != std::string::npos && chip009 == std::string::npos)
		    {
		      datavTID_EXT_8.VBfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_8.VBfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_8.VBfitp2.push_back(TID.redfitp2);
		      datavTID_EXT_8.VBfitp3.push_back(TID.redfitp3);
		      ++processedpadcount;
		    }
		  else if(TID.init_check == true && chip009 != std::string::npos && chip008 == std::string::npos)
		    {			  
		      datavTID_EXT_9.VBfitp0.push_back(TID.redfitp0);
		      datavTID_EXT_9.VBfitp1.push_back(TID.redfitp1);
		      datavTID_EXT_9.VBfitp2.push_back(TID.redfitp2);
		      datavTID_EXT_9.VBfitp3.push_back(TID.redfitp3);
		      ++processedpadcount;
		    }
		  else
		    {
		      //std::cout<<"Error processing file '"+line+"' "+padName+"..."<<std::endl;
		    }
		  break;
		}
	    }
	}
    }
  acceptedFiles.close();
  rejectedFiles.close();
  std::cout<<"================================================================================================"<<std::endl;
  
  PlotFunctions(datavTID_EXT_8, datavTID_EXT_9);
  
  std::cout<<"================================================================================================\nEXT\n"<<std::endl;	      
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
  std::cout<<"================================================================================================\n"<<std::endl;	      
}
