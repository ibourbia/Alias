#include "Network.h"
#include "random.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include "types.h"
#include <time.h>

Network::Network(std::vector<double> typesProp, int n, double Pex, double lambda){
	inizialize(typesProp, n, Pex, lambda);
}

void Network::inizialize(std::vector<double> typesProp, int n, double Pex, double lambda){
	neurones.clear();

	for(size_t i(0); i<typesProp.size(); i++){
		(allTypesValues[keys[i]])? addNeurones(n, Pex, typesProp[i], keys[i]) : addNeurones(n,1-Pex, typesProp[i], keys[i]);
	}
	std::cout << "nombre de neurones " << neurones.size() << std:: endl;
	clear_links();

	random_connect(lambda);
	//print_links();
}

Network::~Network(){
	for(auto n: neurones){
		delete n;
		n=nullptr;
	}
}

size_t Network::random_connect(const double& lambda){

	size_t counter = 0;

	// determine le nombre de connexions que va avoir chaque neurone
	std::vector<int> degrees(neurones.size());
	RNG.poisson(degrees,lambda);
	std::vector <int> NewNeighbors;

	//clock_t start=clock();
	for ( size_t i = 0; i < neurones.size() ;++i){
		RNG.uniform_intR(NewNeighbors,(size_t) degrees[i], 0, neurones.size());

		for (unsigned int j(0); j < NewNeighbors.size(); ++j){
			size_t a(i);
			size_t b(NewNeighbors[j]);
			if(add_link(a,b)){
				++counter;
			}
		}
	}
	//std::cout<<"Time Taken :"<< (double)(clock() - start)/CLOCKS_PER_SEC<<std::endl;
	return counter;
}



size_t Network::size() const {
	return neurones.size();
}

double Network::calcul_courant(const size_t n){ //on peut faire appel à la fonction firing de la classe neuron pour prendre que les voisins qui sont en firing
	try{
		double I (neurones[n]->get_thalamic());

		double courant_voisins(0);
		for (size_t i = 0; i< neurones_firing.size();  ++i){
			courant_voisins += links[n][neurones_firing[i]];
		}
		//std::cout<<courant_voisins<<"neurone : "<< n<<std::endl;
		I += courant_voisins;
		neurones[n]->set_courant(I);

		return I;

	}catch(std::out_of_range &e){
		std::cerr<<"Out of Range error : "<<e.what()<<std::endl;
		return 0;
	}
}

bool Network::add_link(const size_t& a,const size_t& b){

	if(a==b or a>=neurones.size() or b>=neurones.size() or a<0 or b<0 or links[a][b]!=0.0){
		return false;
	}

	links[a][b] = neurones[a]->get_coeff()*RNG.uniform_double(0,1);
	//std::cout << "coeff " << neurones[a]->get_coeff() << std:: endl;
	//std::cout << "links " << links[a][b] << std::endl;
	return true;
}

std::vector<size_t> Network::firing_neurones() {
	neurones_firing.clear();
	for(size_t i(0); i< neurones.size(); i++){
		if (neurones[i]->get_fire()) neurones_firing.push_back(i);
	}
	return neurones_firing;
}

void Network::update(double dt){
	this->firing_neurones();
	for (size_t i(0); i<neurones.size(); ++i){
		calcul_courant(i);
		//appel a la fonction update des neurones.
		neurones[i]->update(dt);
	}
  //modification de la liste des neurones firing:
}

std::vector<Neurone*> Network::get_neurones() const {
	return neurones;
}

std::vector<std::vector<double>> Network::get_links() const {
	return links;
}


void Network:: clear_links() {
	links = std::vector<std::vector<double>> (neurones.size(),std::vector<double> (neurones.size(),0));
}

void Network::addNeurones(int totalNumber, double globalProp, double preciseProp, Type t){
	for(int i(0); i<std::round(totalNumber*globalProp*preciseProp); i++){
		if (neurones.size()<(size_t)totalNumber) neurones.push_back(new Neurone(t));
	}
}
std::vector<double> Network::get_degree_valence(size_t n){
    double degree(0);
    double valence(0);
    std::vector<double> out;
    for(size_t j(0); j<links[n].size(); ++j){
        if(links[n][j]!=0){
            degree+=1;
            valence+=links[n][j];
            }
    }
    out.push_back(degree);
    out.push_back(valence);
    return out;
}


//void Network:: print_links() const{
	/*for (unsigned int i(0); i < links.size() ; ++ i ) {
		for (unsigned int j(0); j < links[i].size() ; ++ j ) {
			std:: cout << "intensite du lien " << links[i][j] << std:: endl;
		}
	}*/
	//std::cout << "nombre de links " << links.size() << std:: endl;
//}
