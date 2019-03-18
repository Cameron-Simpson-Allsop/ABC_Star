#include <vector>
#include <iostream>

void fitTest()
{
  for(int n{0}; n<10; ++n)
    {
      std::vector<double> x;
      std::vector<double> y;
      int npoints = n+20;
      for(int i{0}; i<npoints; ++i)
	{
	  x.push_back(i);
	  if(i<=(npoints*1.)/4.)
	    {
	      y.push_back(10);
	    }
	  else if(i>(npoints*1./4.))
	    {
	      y.push_back(10+(npoints*1./4.)-i);
	    }
	}

      TString cantitle = "c"+std::to_string(npoints);
      TCanvas *can = new TCanvas(cantitle,cantitle,600,600);
  
      TF1 *fitlower = new TF1("fitlower","pol1",0,(npoints*1./4.));
      TF1 *fitupper = new TF1("fitupper","pol1",(npoints*1./4.),20);
  
      TGraph *g = new TGraph(x.size(), &(x[0]), &(y[0]));
      g->SetTitle("");
      g->SetMarkerStyle(20);
      g->Draw("AP");
      g->Fit(fitlower,"RN");
      g->Fit(fitupper,"RN");
      fitlower->Draw("same");
      fitupper->Draw("same");

      double xint = (fitupper->GetParameter(0)-fitlower->GetParameter(0))/(fitlower->GetParameter(1)-fitupper->GetParameter(1));
      double yint = (fitlower->GetParameter(0)*fitupper->GetParameter(1)-fitlower->GetParameter(1)*fitupper->GetParameter(0))/(fitupper->GetParameter(1)-fitlower->GetParameter(1));

      std::cout<<"\n"<<cantitle<<"\nx fit intercept = "<<xint<<"\ny fit intercept = "<<yint<<std::endl;
    }
}
