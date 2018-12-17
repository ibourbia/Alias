#include "Network.h"
#include <array>
#include <iostream>

#ifndef SIMULATION_H
#define SIMULATION_H

//! Simulation class
/*!
 *  class responsable for the interactions between neurons
 */

class Simulation {
public:
	/*! @brief constructor in charge of initalizing
    *   @param [n] the number of neurons
    *   @param [Pex] the proportion of excitatory neurons
    *   @param [t] duration of the simulation
    *   @param [c] the average number of connections made by each neuron
    *   @param [p] the precise proportion of Neuron types
    */
	Simulation(double n, double Pex, double t, double c, std::vector<double> p);
	/*! @brief method used by the constructor to initalize the simultation
    *   @param [simTime] duration of the simulation
    *   @param [n_neurons] number of neurons of the simulation
    */
	void initialize(double simTime, int n_neurons);
	/*! @brief add at the output matrix the state of the neurons
    */
	void run();
	/*! @brief create and write an output txt document
	*   representing the matrix of all the states of the neurons at each step of time
    */
	void create_doc();
	void create_outputR();
	void create_outputParams();
	void create_neuronvector();

private:
	Network net;
	double dt;
	double simTime;
	std::vector<std::vector< int>>matrix;
	size_t n_neurons;
	std::vector<Neurone*> neurons_types;
	std::vector<std::vector<double>> matrix_potential;
};


#endif
