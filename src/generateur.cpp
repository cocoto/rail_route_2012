#include <iostream>
#include <list>
#include<vector>
#include <fstream>
#include "Heure.hpp"
#include <stdlib.h>
#include <algorithm>

/*
 * Programme générant des parcours de trains aléatoirement
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
  if(ficher_gares)
  {
    ficher_gares>>nb_gares;
    for(i=0;i<nb_gares;i++)
    {
      ficher_gares>>gare;
      ficher_gares>>temp;
      gare+=" "+temp;
      liste_gares.push_back(gare);
    }
    for(i=0;i<atoi(argv[2]);i++)
    {
      std::cout<<"Feuille :\n";
      std::cout<<"25:00 ";
      heure.set(rand()%24,rand()%60);
      std::cout<<heure<<" ";
      old_gare=rand()%liste_gares.size();
      std::cout<<liste_gares[old_gare]<<"\n";
      max=rand()%atoi(argv[3]);
      while(heure.heure() <23 && max>0)
      {
	heure+= rand()%std::min(atoi(argv[4]),(24*60-heure.value()));
	std::cout<<heure<<" ";
	heure+=rand()%std::min(24*60-heure.value(),atoi(argv[5]));
	std::cout<<heure<<" ";
	do
	{
	  new_gare=rand()%liste_gares.size();
	}while(old_gare==new_gare);
	std::cout<<liste_gares[new_gare]<<"\n";
	old_gare=new_gare;
	max--;
      }
      std::cout<<"prixh : "<<rand()%100<<"\n\n";
    }
  }
  else
  {
    std::cout<<"Error during opening file "<<argv[1]<<"\n";
    return 0;
  }
  return 0;
}
