// file: gnuplot.h

#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <iostream>	// may remove later
#include <string>	// idk

class gnuplot {			// a class gnuplot is created containing related member functions
	public:
		gnuplot();
		~gnuplot();
		void operator () (const std::string & command);
	protected:
		FILE *gnuplotpipe;		// a file pointer
};

gnuplot::gnuplot(){
	gnuplotpipe = popen("gnuplot -persist","w");	// it is using the popen library function to open gnuplot
	if (!gnuplotpipe)
		std::cerr << ("Gnuplot not found !");
}

gnuplot::~gnuplot(){
	fprintf(gnuplotpipe, "exit\n");
	pclose(gnuplotpipe);
}

void gnuplot::operator() (const std::string & command){
	fprintf(gnuplotpipe, "%s\n", command.c_str());	// how the gnuplot command will be used, that is described in the :
	fflush(gnuplotpipe);
}

#endif
