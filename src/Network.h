#include <iostream>
#include <vector>
#include "Neurone.h"
#include "types.h"

#ifndef NETWORK_H
#define NETWORK_H

/*! \mainpage Neural Network
 *
 * \section intro_sec Introduction
 * ADD README
 */

//! Network class
/*!
 *  class responsible for the interactions between neurons
 */

class Network {

public:
/*! @brief constructor in charge of initalizing the weight matrix and creating random links between each neuron.
*   Each box {a,b} of the matrix either contains 0 if a is not linked to be or contains a number uniformely distributed between 0 and 1 if there is a link
*   @param [typesProp] the precise proportion of Neuron types
*   @param [n] the number of neurons
*   @param [Pex] the proportion of excitatory neurons
*   @param [lambda] the average number of connections made by each neuron
*/
  Network(std::vector<double> typesProp, int n, double Pex, double lambda);
/*!\ @brief destructor for a Network object
*/
  ~Network();
  /*! @brief this method is called by the class constructor for the initialization of the Network
*   @param [typesProp] the precise proportion of Neuron types
*   @param [n] the number of neurons
*   @param [Pex] the proportion of excitatory neurons
*   @param [lambda] the average number of connections made by each neuron
*   @see Network()
*/
  void inizialize(std::vector<double> typesProp, int n, double Pex, double lambda);
/*! @brief Calculates the total current received by specific neuron by summing the currents of the firig connected neurons
*   The current received is added if the neuron is excitatory and substracted if the neuron is inhibitory
*   @param [n] the indice of the neuron
*   @return the value of the current for the neuron at the n position
*/
  double calcul_courant(size_t n);  //seulement trouver les neighbors qui sont "firing"
/*! \brief function that creates random connections between neurons in the weight matrix
*   @param [lambda] the average number of connections made by each neuron
*   @return the number of connection
*/
  size_t random_connect(const double& lambda);
/*! @brief method called in random_connect to make a unidirectional link between a and b (from a to b).
*   Verifies that the neurons at positions a and b exist and whether the link between them is there.
*   @param [a] indice of the first neuron of the link
*   @param [b] indice of the second neuron of the link
*   @return if the inverse link is already made returns false and the link is not added else add the link and return true
*   @see calcul_courant()
*/
  bool add_link(const size_t& a,const size_t& b);
/*! @brief getter for the network size
*   @return returns the size of the neuron vector;
*/
  size_t size() const;
/*! @brief getter for the list of neurons
*   @return returns a pointer on the vector of neurons
*/
  std::vector<Neurone*> get_neurones() const; //dans les attributs neurones n'est pas un vecteur sur des pointeurs! mème chose pour links et neurone_firing
/*! @brief getter for the number of links
*   @return returns a pointer on the weight matrix
*/
  std::vector<std::vector<double>> get_links() const;
/*! @brief getter for the list of firing neurones
*   @return returns a pointer on the vector of firing neurons
*/
std::vector<size_t> firing_neurones(); //cette methode est const aussi
/*! @brief updates each neuron by calling the update function in the Neuron class for each neuron of the attribute neurons
*   @param [dt] the step of time of the update
*/
void update(double dt);
/*! @brief clear all links
*/
  void clear_links() ;

/*! @brief method used in the inizialize() method, adds the neurons the the neurons list
*   @param [totalNumber] total number of neurons
*   @param [globalProp] global proportion
*   @param [preciseProp] precise proportion
*   @param [t] type of the neuron
*   @param [n] total number of neurones
*   @see inizialize()
*/
  void addNeurones(int totalNumber, double globalProp, double preciseProp, Type t);

  //void print_links() const;

  std::vector<double> get_degree_valence(size_t n);

private:

std::vector<Neurone*> neurones;
std::vector<std::vector<double>> links;
std::vector<size_t> neurones_firing;

};

#endif
