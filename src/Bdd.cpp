#include "Bdd.hpp"
#include<string>
#include<iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
  
  Bdd::Bdd(const std::string &routes_filename, const std::string &gares_filename){
    std::multimap< std::string,Ligne_Bdd >();
    load_routes_file(routes_filename);
    load_gares_file(gares_filename);
  }
  
  Bdd::Bdd(){
    std::multimap< std::string,Ligne_Bdd > ();
  }
  
  std::list<Ligne_Bdd*> Bdd::get_disponibles(const std::string &gare, const Heure &heure, const bool&multiday)
  {
      std::list<Ligne_Bdd*> resultat;
      std::pair< std::multimap<std::string,Ligne_Bdd >::iterator, std::multimap<std::string,Ligne_Bdd >::iterator > bornes = equal_range(gare);
      std::multimap<std::string,Ligne_Bdd >::iterator it=bornes.first;
      while(it!=bornes.second)
      {
	if((*it).second.disponible(gare,heure,multiday))
	{
	  //std::cout<<(*it).second.gare_arrivee()<<"\n";
	  resultat.push_back(&((*it).second));
	}
	it++;
      }
      return resultat;
  }
  
  void Bdd::load_gares_file(const std::string &gares_filename)
  {
    std::ifstream fichier_gares(gares_filename.c_str());
    std::string ligne("");
    Heure hdepart,harrive;
    std::string garrearrive, garredepart,ville,poubelle;
    std::pair< std::string, Ligne_Bdd> paire;
    std::streampos position;
    Ligne_Bdd ligneBdd;
    bool sortie=false;
    if(fichier_gares)
    {
      int temps;
      sortie=false;
      ville="";
      while(!sortie)
      {
	while(garredepart.compare(std::string("Ville")))
	{
	  if(!(fichier_gares>>garredepart))
	  {
	    sortie=true;
	    break;
	  }
	}
	fichier_gares>>poubelle;
	if(!sortie)
	{
	  fichier_gares>>ville;
	  fichier_gares>>garredepart;
	  while(garredepart!="Ville")
	  {
	    
	    fichier_gares>>garrearrive;
	    _gare_list.insert(ville+" "+garredepart);
	    _gare_list.insert(ville+" "+garrearrive);
	    fichier_gares>>temps;
	    
	    paire.first=ville+" "+garredepart;
	    ligneBdd.gare_arrivee(ville+" "+garrearrive);
	    ligneBdd.gare_depart(ville+" "+garredepart);
	    ligneBdd.h_depart(Heure(0,0));
	    ligneBdd.h_arrivee(Heure(temps));
	    ligneBdd.est_pieton(true);
	    paire.second=ligneBdd;
	    //std::cout<<"Trajet pieton de "<<paire.second.gare_depart()<<" à "<<paire.second.gare_arrivee()<<"\n";
	    insert(paire);
	    paire.first=ville+" "+garrearrive;
	    paire.second.gare_arrivee(ville+" "+garredepart);
	    paire.second.gare_depart(ville+" "+garrearrive);
	    //std::cout<<"Trajet pieton de "<<paire.second.gare_depart()<<" à "<<paire.second.gare_arrivee()<<"\n";
	    insert(paire);
	    if(!(fichier_gares>>garredepart))
	    {
	      sortie=true;
	      break;
	    }
	  }
	}
      }
    }
    else
    {
      std::cout<<"Error during opening "<<gares_filename<<"\n";
    }
  }
  
  void Bdd::load_routes_file(const std::string &routes_filename)
 {
    std::ifstream fichier_routes(routes_filename.c_str());
    std::string ligne("");
    Heure hdepart,harrive;
    int prix;
    std::string garrearrive, garredepart,ville;
    std::pair< std::string, Ligne_Bdd> paire;
    std::streampos position;
    Ligne_Bdd ligneBdd;
    bool sortie=false;
    if(fichier_routes)
    {
      while(!sortie)
      {
	while(ligne.compare(std::string("Feuille")))
	{
	  if(!(fichier_routes>>ligne))
	  {
	    sortie=true;
	    break;
	  }
	}
	fichier_routes>>ligne;
	if(!sortie)
	{
	  position=fichier_routes.tellg();
	  while(ligne.substr(0,5)!="prixh")
	  {
	    fichier_routes>>ligne;
	  }
	  fichier_routes>>ligne;
	  fichier_routes>>ligne;
	  
	  prix=atoi(ligne.c_str());
	  fichier_routes.seekg(position);
	  std::getline(fichier_routes,ligne); //Récupération de la première ligne
	  std::getline(fichier_routes,ligne); //Récupération de la première ligne
	  hdepart=Heure(atoi(ligne.substr(6,2).c_str()),atoi(ligne.substr(9,2).c_str()));
	  //std::cout<<hdepart.heure()<<"\n";
	  garredepart=ligne.substr(12);
	  std::getline(fichier_routes,ligne);
	  while(ligne.substr(0,5)!="prixh")
	  {
	    _gare_list.insert(garredepart);
	    harrive=Heure(atoi(ligne.substr(0,2).c_str()),atoi(ligne.substr(3,2).c_str()));
	    garrearrive=ligne.substr(12);
	    
	    paire.first=garredepart;
	    paire.second=Ligne_Bdd(garredepart,garrearrive,hdepart,harrive,prix);
	    insert(paire);
	    	    
	    hdepart=Heure(atoi(ligne.substr(6,2).c_str()),atoi(ligne.substr(9,2).c_str()));
	    garredepart=garrearrive;
	    std::getline(fichier_routes,ligne);
	  }
	  _gare_list.insert(garredepart);
	}
      }
      fichier_routes.close();
//       std::multimap< std::string,Ligne_Bdd >::iterator it=begin();
//       while(it!=end())
//       {
// 	std::cout<<"Départ de "<< (*it).second.gare_depart() <<" à "<< (*it).second.h_depart().heure()<< "h"<< (*it).second.h_depart().minute() <<" arrivée à "<< (*it).second.gare_arrivee() << "à "<< (*it).second.h_arrivee().heure()<<"h"<<(*it).second.h_arrivee().minute()<<"\n";
// 	it++;
//       }
      
    }
    else
    {
      std::cout<<"Error during opening "<<routes_filename<<"\n";
    }
 }
 
 std::set<std::string> Bdd::gare_list() const
 {
   return _gare_list;
 }
 
 void Bdd::effacer()
 {
   clear();
   _gare_list.clear();
 }
