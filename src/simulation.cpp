#include "simulation.h"
#include <iostream>
#include <fstream>
#include "Neurone.h"
#include "types.h"

using namespace std;

Simulation::Simulation(double n,double Pex, double t, double c, vector<double> p):
net(Network(p,n,Pex,c)),dt(0), simTime(t),n_neurons(n) {
	initialize(t,n);
	create_neuronvector();
	matrix_potential = vector<vector<double>> ((simTime), vector<double>(3 * neurons_types.size()+1));

}

void Simulation::initialize(double simTime, int n_neurons){
	matrix = vector<vector<int>> ((simTime), vector<int>(n_neurons +1));

}

void Simulation::run(){

    size_t i(0);

	while(dt < simTime){

        net.update(1); //colonne vide au debut? mettre le update à la fin du while?
		matrix_potential[i][0] = i + 1;
		size_t indice_neuron(0);
		for( size_t j(1); j < matrix_potential[0].size(); j += 3){
			matrix_potential[i][j] = neurons_types[indice_neuron]->get_potentiel();
			matrix_potential[i][j + 1] = neurons_types[indice_neuron]->get_relaxation();
			matrix_potential[i][j + 2] = neurons_types[indice_neuron]->get_courant();
			++ indice_neuron;
		}

		vector<size_t> firing_neurons (net.firing_neurones());
		std::cout << net.firing_neurones().size() << std::endl;


		  //matrix Rasterplot
		    matrix[i][0] = i + 1;
		    for(size_t j(0); j< firing_neurons.size() ; ++j){
			matrix[i][firing_neurons[j]+1] = 1;
		    }
		   dt+=1;
		   ++i;
		 }

}

void Simulation::create_outputR(){

	ofstream myfile;
    myfile.open ("Rasterplot.txt");


    for(size_t i(0); i < simTime; ++i){
		for(size_t j(0); j <(n_neurons +1); ++j){
			myfile<< matrix[i][j] << " ";
		}
	    myfile<<std::endl;
    }
    myfile.close();
}

void Simulation::create_outputParams(){

    vector< Neurone*> neurons_ (net.get_neurones());
    ofstream myfile;
    myfile.open ("neuron_params.txt");
    myfile<< "Type"<<'\t'<<"a"<<'\t'<<"b"<<'\t'<<"c"<<'\t'<<"d"<<'\t'<<"Inhibitory"<<'\t'<<"degree"<<'\t'<<"valence"<<std::endl;
    for(size_t i(0); i<neurons_.size(); ++i){
            myfile<< display(neurons_[i]->get_type())<<'\t'<<neurons_[i]->get_a()<<'\t'<<neurons_[i]->get_b()<<'\t';
            myfile<<neurons_[i]->get_c()<<'\t'<<neurons_[i]->get_d()<<'\t'<<displayInhib(neurons_[i]->get_type())<<'\t';
            myfile<<net.get_degree_valence(i)[0]<<'\t'<<net.get_degree_valence(i)[1]<<std::endl;
    }
    myfile.close();
}

void Simulation::create_neuronvector(){

    //destructeur!!??
	vector< Neurone*> neurons_ (net.get_neurones());
	Type current_type (neurons_[0]->get_type());
	neurons_types.push_back(neurons_[0]);

	for(size_t i(0); i < neurons_.size(); ++i){
		if (neurons_[i]->get_type() != current_type){

			neurons_types.push_back(neurons_[i]);
			current_type = neurons_[i]->get_type();}
	}
}
