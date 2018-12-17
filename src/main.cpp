#include <iostream>
#include <tclap/CmdLine.h>
#include "Network.h"
#include "random.h"
#include "simulation.h"

using namespace TCLAP;

RandomNumbers RNG;


int main(int argc, char **argv){

	CmdLine cmd("Neural Network");
	// revoir les valeures par defaut de chaque entree.
	ValueArg< int > number("n", "neurons", "Nombre de neurones a générer", false, 100, "int");
	cmd.add(number);
	ValueArg< double > proportion("p", "proportion", "entrez la proportion de neurones excitateurs", false, 0.5, "double");
	cmd.add(proportion);
	ValueArg< int > time("t", "time", "entrez le temps de simulation en ms", false, 100, "int");
	cmd.add(time);
	ValueArg< double > connectivity("c", "connectivity", "entrez la connectivite moyenne de chaque neurone", false, 0.5, "double");
	cmd.add(connectivity);

	MultiArg<double> typesProportions("P","Proportion","Types propotions in given order :  RS, IB, CH, FS, LTS",true,"double between 0 and 1");
	cmd.add(typesProportions);


	cmd.parse(argc, argv);


	Simulation sim(number.getValue(),proportion.getValue(),time.getValue(),connectivity.getValue(),typesProportions.getValue());
    sim.run();
    sim.create_outputR();
    sim.create_outputParams();
    return 0;
}
