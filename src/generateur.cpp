#include <iostream>
#include <list>
#include<vector>
#include <fstream>
#include "Heure.hpp"
#include <stdlib.h>
#include <algorithm>

/*
 * Programme générant des parcours de trains aléatoirement
 * Toutes les feuilles générées partent et arrivent le MEME jour (départ limite = 23h)
 * Le prix varie entre 1 et 100
 * Il peut y avoir une feuille d'une seule ligne (inutile)
 * 
 * arg1 = Fichier sous la forme "VILLE GARE"
 * arg2 = Nombre de trains à générer
 * arg3 = Nombre maximum de trajets par train
 * arg4 = Temps maximum de trajet entre 2 gares
 * arg5 = Temps maximum d'arrêt en gare
 */
int main(const int argc, const char** argv)
{
  (void)argc;
  std::vector<std::string> liste_gares;
  std::ifstream ficher_gares(argv[1]);
  int i;
  int nb_gares;
  int max;
  Heure heure;
  std::string gare;
  std::string temp;
  srand(time(NULL));
  int old_gare,new_gare;
  
  //Lecture de la liste des gares
  if(ficher_gares)
  {
    //Lecture du nombre de villes
    ficher_gares>>nb_gares;
    for(i=0;i<nb_gares;i++)
    {
      ficher_gares>>gare;
      ficher_gares>>temp;
      gare+=" "+temp;
      liste_gares.push_back(gare);
    }
    
    //Création des feuilles
    for(i=0;i<atoi(argv[2]);i++)
    {
      std::cout<<"Feuille :\n";
      //Situation de la première ligne
      std::cout<<"25:00 ";
      heure.set(rand()%24,rand()%60);
      std::cout<<heure<<" ";
      old_gare=rand()%liste_gares.size();
      std::cout<<liste_gares[old_gare]<<"\n";
      
      //Établissement de la taille maximum de la feuille (entre 3 et arg3)
      max=rand()%atoi(argv[3]-3)+3;
      
      //On ajoute des trajets à la feuille si la dernière arrivée était avant 23h
      while(heure.heure() <23 && max>0)
      {
	//Selection du temps de trajet
	heure+= rand()%std::min(atoi(argv[4]),(24*60-heure.value()));
	std::cout<<heure<<" ";
	
	//Selection du temps d'attente en gare
	heure+=rand()%std::min(24*60-heure.value(),atoi(argv[5]));
	std::cout<<heure<<" ";
	
	//Selection de la gare d'arrivée (différente de la gare de départ
	do
	{
	  new_gare=rand()%liste_gares.size();
	}while(old_gare==new_gare);
	std::cout<<liste_gares[new_gare]<<"\n";
	old_gare=new_gare;
	max--;
      }
      std::cout<<"prixh : "<<rand()%99+1<<"\n\n";
    }
  }
  else
  {
    std::cout<<"Error during opening file "<<argv[1]<<"\n";
    return 0;
  }
  return 0;
}
