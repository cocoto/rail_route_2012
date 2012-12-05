#ifndef _SOLVER_H_
#define _SOLVER_H_
#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<set>
#include<typeinfo>
#include"Bdd.hpp"
#include "Etape.hpp"
#include "Comparator.hpp"
#include "Comparator_Etape.hpp"
#define TAILLE_TOP_SCORE  5


std::set<Etape, Comparator_Etape> Calcul_trajet(const std::string &depart,const std::string &arrivee,const Heure &heure_depart, const float &preference,Bdd bdd);
#endif