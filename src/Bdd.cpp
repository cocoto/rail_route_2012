#include "Bdd.hpp"
#include<string>
#include<iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>

  /*
   * Constructeur avec parsing des deux fichiers
   */
  Bdd::Bdd(const std::string &routes_filename, const std::string &gares_filename){
    std::multimap< std::string,Ligne_Bdd >();
    load_routes_file(routes_filename);
    load_gares_file(gares_filename);
  }

  /*
   * Constructeur habituel
   */
  Bdd::Bdd(){
    std::multimap< std::string,Ligne_Bdd > ();
  }

  /*
   * Fonction retournant la liste des trajets possibles pour une étape donnée (lieu, heure)
   * Lorsque multiday=false, ne retourne que les trains partants avant la fin de la journée
   */
  std::list<Ligne_Bdd*> Bdd::get_disponibles(const std::string &gare, const Heure &heure, const bool&multiday)
  {
      std::list<Ligne_Bdd*> resultat; //Liste des résultats
      //Récupération d'un couple d'itérateurs entre le premier et le dernier trajet partant de la gare
      std::pair< std::multimap<std::string,Ligne_Bdd >::iterator, std::multimap<std::string,Ligne_Bdd >::iterator > bornes = equal_range(gare);
      std::multimap<std::string,Ligne_Bdd >::iterator it=bornes.first;
      //On parcours tous les trajets au départ de la ville
      while(it!=bornes.second)
      {
	//On ajoute ce trajet s'il correspond aux critères de choix (bonne vile, gestion multi-jours)
	if((*it).second.disponible(gare,heure,multiday))
	{
	  //std::cout<<(*it).second.gare_arrivee()<<"\n";
	  resultat.push_back(&((*it).second));
	}
	it++;
      }
      return resultat;
  }


  /*
   * Fonction de parsing d'un fichier de trajets piétons
   */
  void Bdd::load_gares_file(const std::string &gares_filename)
  {
    //Ouverture du fichier
    std::ifstream fichier_gares(gares_filename.c_str());
    std::string ligne(""); //Tampon de lecture
    std::string garrearrive, garredepart,ville,poubelle; //Gares de départ et d'arrivée // Variable stockant les caractère inutiles (:)
    std::pair< std::string, Ligne_Bdd> paire; //Paire formant un couple clé / valeurs de la bdd
    std::streampos position; // Sauvegarde de la position du curseur dans le fichier
    Ligne_Bdd ligneBdd;
    bool sortie=false;

    //On vérifie la bonne ouverture du fichier
    if(fichier_gares)
    {
      int temps;
      sortie=false;
      ville="";
      //On parcours le fichier jusqu'à la première ligne "Ville : " trouvée
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
	//On récupère le caractère ":" (inutilisé)
	fichier_gares>>poubelle;

	if(!sortie)
	{
	  //Récupération de la ville
	  fichier_gares>>ville;
	  //Récupération de la première gare
	  fichier_gares>>garredepart;

	  //On parcours le fichier jusqu'à retrouver une nouvelle Ville :
	  while(garredepart!="Ville")
	  {
	    //Récupération de la ville d'arrivée
	    fichier_gares>>garrearrive;
	    _gare_list.insert(ville+" "+garredepart);
	    _gare_list.insert(ville+" "+garrearrive);

	    //Récupération du temps de trajet
	    fichier_gares>>temps;

	    //Création du trajet
	    paire.first=ville+" "+garredepart;
	    ligneBdd.gare_arrivee(ville+" "+garrearrive);
	    ligneBdd.gare_depart(ville+" "+garredepart);
	    ligneBdd.h_depart(Heure(0,0)); //Variable non utilisée par la base de donnée
	    ligneBdd.h_arrivee(Heure(temps)); //Le temps de trajet correspond à l'heure d'arrivée si on partait à minuit
	    ligneBdd.est_pieton(true); //Important
	    paire.second=ligneBdd;
	    //std::cout<<"Trajet pieton de "<<paire.second.gare_depart()<<" à "<<paire.second.gare_arrivee()<<"\n";
	    insert(paire);

	    //Ajout dans la base de données
	    paire.first=ville+" "+garrearrive;
	    paire.second.gare_arrivee(ville+" "+garredepart);
	    paire.second.gare_depart(ville+" "+garrearrive);
	    //std::cout<<"Trajet pieton de "<<paire.second.gare_depart()<<" à "<<paire.second.gare_arrivee()<<"\n";
	    insert(paire);

	    //Lecture de la nouvelle gare de départ (ou de la nouvelle ligne Ville : )
	    if(!(fichier_gares>>garredepart))
	    {
	      sortie=true;
	      break;
	    }
	  }
	}
      }
      fichier_gares.close();
    }
    else
    {
      std::cout<<"Error during opening "<<gares_filename<<"\n";
    }
  }


  /*
   * Fonction de parsing d'un fichier de feuilles de routes (trains)
   */
  void Bdd::load_routes_file(const std::string &routes_filename)
 {
   //Ouverture du fichier d'instance
    std::ifstream fichier_routes(routes_filename.c_str());
    Heure hdepart,harrive; //Heure des trajets à ajouter dans la Bdd
    int prix;
    std::string ligne(""); //Tampon de lecture
    std::string garrearrive, garredepart,ville; //Gares de départ et d'arrivée // Variable stockant les caractère inutiles (:)
    std::pair< std::string, Ligne_Bdd> paire; //Paire formant un couple clé / valeurs de la bdd
    std::streampos position; // Sauvegarde de la position du curseur dans le fichier
    Ligne_Bdd ligneBdd;
    bool sortie=false;

    //On vérifie la bonne ouverture du fichier
    if(fichier_routes)
    {
      //On recherche la première ligne du fichier égale à "Feuille : "
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

	//On échape le caractère inutilisé (:)
	fichier_routes>>ligne;
	if(!sortie)
	{
	  //On sauvegarde la position de la première ligne de la feuille
	  position=fichier_routes.tellg();

	  //On recherche le prix de la feuille (pour l'ajouter dans toutes les lignes de la Bdd)
	  while(ligne.substr(0,5)!="prixh")
	  {
	    fichier_routes>>ligne;
	  }
	  //Échappement du caractère ":"
	  fichier_routes>>ligne;
	  //Récupération du prix
	  fichier_routes>>ligne;

	  prix=atoi(ligne.c_str());

	  //On retourne au début de la feuille
	  fichier_routes.seekg(position);
	  std::getline(fichier_routes,ligne); //On jette la fin de la ligne (après "Feuille")
	  std::getline(fichier_routes,ligne); //Récupération de la première ligne de la feuille

	  //Récupération de l'heure et la gare de départ par explosion de la ligne
	  hdepart=Heure(atoi(ligne.substr(6,2).c_str()),atoi(ligne.substr(9,2).c_str()));
	  //std::cout<<hdepart.heure()<<"\n";
	  garredepart=ligne.substr(12);

	  //Passage à la ligne suivante (contenant la nouvelle gare et heure d'arrivée
	  std::getline(fichier_routes,ligne);
	  //On boucle jusqu'à la fin de la feuille (retombée sur le prix)
	  while(ligne.substr(0,5)!="prixh")
	  {
	    _gare_list.insert(garredepart);

	    //Récupération de l'heure et de la gare d'arrivée
	    harrive=Heure(atoi(ligne.substr(0,2).c_str()),atoi(ligne.substr(3,2).c_str()));
	    garrearrive=ligne.substr(12);

	    //Constitution et ajout de la ligne dans la Bdd
	    paire.first=garredepart;
	    paire.second=Ligne_Bdd(garredepart,garrearrive,hdepart,harrive,prix);
	    insert(paire);

	    //Récupération des information du prochain départ
	    hdepart=Heure(atoi(ligne.substr(6,2).c_str()),atoi(ligne.substr(9,2).c_str()));
	    garredepart=garrearrive;
	    std::getline(fichier_routes,ligne);
	  }
	  _gare_list.insert(garredepart);
	}//Boucle de parcourt d'une feuille
      }//Boucle de parcourt des feuilles
      fichier_routes.close();
    }//Vérification de l'ouverture du fichier
    else
    {
      std::cout<<"Error during opening "<<routes_filename<<"\n";
    }
 }

 /*
  * Fonction retournant la liste des gares de la Bdd
  */
 std::set<std::string> Bdd::gare_list() const
 {
   return _gare_list;
 }

 /*
  * Fonction effacant la base de donnée (Bdd)
  */
 void Bdd::effacer()
 {
   clear();
   _gare_list.clear();
 }
