/*
 * loadgraph.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: tao
 */
#include "loadgraph.h"
#include "main.h"

LoadGraph::LoadGraph(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 750))
{
/*
 * To handle JPG images, we must initiate the wxJPEGHandler.
 */
  wxImage::AddHandler(new wxJPEGHandler);

/*
 * We create a scroll window and put a static bitmap into it.
 */
  wxScrolledWindow *sw = new wxScrolledWindow(this);

  wxString mystring;
  if (graph_seq == 0){	//mono graph created
  	  mystring = wxT("Mono_temp.jpg");
  }
  else if (graph_seq == 1){	//poly graph created
  	  mystring = wxT("Poly_temp.jpg");
  }
  else if (graph_seq == 6){	//paper gragh
	  mystring = wxT("./graph/IndepU-Topk_time.jpg");
  }
  else if (graph_seq == 7){
	  mystring = wxT("./graph/IndepU-Topk_depth.jpg");
  }
  else if (graph_seq == 8){
	  mystring = wxT("./graph/IndepU-kRanks_time.jpg");
  }
  else if (graph_seq == 9){
	  mystring = wxT("./graph/IndepU-kRanks_depth.jpg");
  }
  else if (graph_seq == 10){
	  mystring = wxT("./graph/IndepU-Topk_correlations.jpg");
  }
  else if (graph_seq == 11){
  	  mystring = wxT("./graph/IndepU-kRanks_correlations.jpg");
   }
  else if (graph_seq == 12){
  	  mystring = wxT("./graph/OPTU-Topk_depth.jpg");
  }
  else if (graph_seq == 13){
	  mystring = wxT("./graph/OPTU-Topk_time.jpg");
  }
  else{
	  mystring = wxT("./graph/Rule_set_complexity.jpg");
  }


  wxBitmap bmp(mystring, wxBITMAP_TYPE_JPEG);
  wxStaticBitmap *sb = new wxStaticBitmap(sw, -1, bmp);

  int width = bmp.GetWidth();
  int height = bmp.GetHeight();

/*
 * We set the scrollbars.
 */
  sw->SetScrollbars(10, 10, width/10, height/10);

/*
 * We scroll the window a bit.
 */
  sw->Scroll(50,10);

  Center();
}





