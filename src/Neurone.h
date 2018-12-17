#ifndef NEURONE_H
#define NEURONE_H
#include "types.h"

//! Neuron class
/*!
 *  class responsible for the creation of a neural cell
 */
 class Neurone {

 public:

 /*! @brief constructor of a neuron, initialize some attributes and uses other initializing methods
 *   @param [t] the type of the neuron
 */
 	Neurone (Type t);
 /*! @brief destructor
  */
  ~Neurone(){}
 /*! @brief initialize the attributes of a neuron depending if its excitatory or inhibitory
  */
  void initialiser_state();
 /*! @brief initialize the attributes of a neuron according to its type
  */
  void initialiser_type();
/*! @brief calculates the membrane potential
  */
 	void calcul_potentiel();
 /*! @brief calculate the relaxation value of the neuron
  */
 	void calcul_relaxation();
  /*! @brief calculate the thalamic input of the neuron
   */
  void calcul_thalamic();
 /*! @brief tels if a neuron is firing
  *  @return returns true if the neuron is firing namely when the potential is higher than a certain threshold
  */
 	bool firing();
/*! @brief method that updates the atributes potentiel and relaxation if the Neuron has fired
  */
  void after_firing();
 /*! @brief getter for the private attribute potential
  */
 	double get_potentiel()const;
  /*! @brief getter for the private attribute thalamic
   */
  double get_thalamic() const;
 /*! @brief getter for the private attribute relaxation
  */
 	double get_relaxation()const;
 /*! @brief getter for the private attribute firing_courant
  */
 	double get_firing_courant()const;
 /*! @brief getter for the private attribute coeff
  */
 	double get_coeff()const;
  /*! @brief getter for the private attribute courant
   */
  double get_courant()const;
  /*! @brief getter for the private attribute d
   */
  double get_d() const;
  /*! @brief getter for the private attribute c
   */
  double get_c() const;
   /*! @brief getter for the private attribute b
   */
  double get_b() const;
  /*! @brief getter for the private attribute a
   */
  double get_a() const;
  /*! @brief getter for the fire atribute
  */
  bool get_fire() const;
   /*! @brief  updates the relaxation (every ms) and the membrane potential (every 0.5 ms)
   * by calculating the differential equations for each parameter using Euler's method and calling the function get_firing_courant
   * if the neuron is firing, sets the parameters to specific values depedent of c and d.
   * @param [dt] step of time of the update
   */
   void update(double dt);
 /*! @brief setter for the attribute courant this method is redefined in the sub-classes Inhibiteur and Excitateur
  * @param [I] new value of courant
  */
  void set_courant(double I);
/*! @brief setter for the private attribute potentiel
*   @param [pi] the new potential
*/
  void set_potentiel(double pi);

  Type get_type() const;


private:
  Type type;
  bool state;
  bool fire;
  double coeff;
  int w;
  double dT;
 	double a;
 	double b;
 	double c;
 	double d;
  double potentiel;
 	double relaxation;
 	double firing_courant;
 	double courant;
  double thalamic;
 };

 #endif
