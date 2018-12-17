#include "Neurone.h"
#include "random.h"
#include <cmath>
#include <iostream>


Neurone::Neurone (Type t)
:type(t),state(allTypesValues[t]), fire(false),  dT(0), potentiel(-65), thalamic(0)
{

	initialiser_state();
	initialiser_type();
	calcul_thalamic();
	courant=thalamic;
	relaxation=b*potentiel;
}

void Neurone::initialiser_state(){
	double r = RNG.uniform_double(0,1);
	if (state){
		a=0.02;
		b=0.2;
		c = -65 + 15 * r*r;
		d = 2 + 6 * (1 - r*r);
		w=7;
		coeff=0.5;
	} else {
		a= 0.02 + 0.08*r;
		b = 0.20 + 0.05*(1-r);
		c=-65;
		d=2;
		w=4;
		coeff=-1.0;
	}
}

void Neurone::initialiser_type(){
	switch(type){
		case RS:
		break;

		case IB:
			c=-55.0;
			d=4.0;
		break;

		case CH:
			c=-50.0;
			d=2.0;

		case FS:
		break;

		case LTS:
			a=0.02;
			b=0.25;
		break;
	}
}

void Neurone::calcul_thalamic(){
		thalamic= w * RNG.normal(0,1);
		//thalamic = 5;
}

void Neurone::calcul_potentiel(){
	potentiel +=0.5*(0.04*potentiel*potentiel + 5*potentiel + 140 - relaxation + courant);
}

void Neurone::calcul_relaxation(){
	relaxation += a*(b*potentiel-relaxation);
}

bool Neurone::firing(){
	if(potentiel>30) {
		firing_courant=courant;
		fire=true;
		return true;
	} else {
		firing_courant=0.0;
		fire=false;
		return false;
	}
}

void Neurone::after_firing(){
	if(firing()){
		potentiel = c;
		relaxation += d;
	}
}
double Neurone::get_thalamic() const{
	return thalamic;
}
double Neurone::get_potentiel() const{
	return potentiel;
}
double Neurone::get_relaxation() const{
	return relaxation;
}
double Neurone::get_firing_courant()const{
	return firing_courant;
}

double Neurone::get_coeff() const{
	return coeff;
}
double Neurone::get_courant() const{
	return courant;
}
double Neurone::get_a() const{
    return a;
}
double Neurone::get_b() const{
    return b;
}
double Neurone::get_c() const{
	return c;
}
double Neurone::get_d() const{
	return d;
}
bool Neurone::get_fire() const{
	return fire;
}

Type Neurone::get_type() const{
	return type;
}
void Neurone::update(double dt){
	dT+=dt;
	after_firing();
	calcul_thalamic();
	calcul_potentiel();
	calcul_potentiel();
	calcul_relaxation();
}

void Neurone::set_courant(double I){
	courant=I;
}
void Neurone::set_potentiel(double pi){
	potentiel = pi;
}
