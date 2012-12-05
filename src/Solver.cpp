#include "Solver.hpp"
std::set<Etape, Comparator_Etape> Calcul_trajet(const std::string &depart,const std::string &arrivee,const Heure &heure_depart, const float &preference,Bdd &bdd, const bool &retour, const Heure &heure_retour)
{
  std::priority_queue<Etape, std::vector<Etape>, Comparator> traitement((Comparator(preference)));
  std::list<Ligne_Bdd*> trajets;
  Etape etape;
  etape.heure=heure_depart;
  etape.ville=depart;
  etape.gares_traverses.insert(depart);
  etape.prix_total=0;
  traitement.push(etape);
  Ligne_Bdd* trajet;
  Comparator_Etape competape(preference);
  std::set<Etape, Comparator_Etape> resultats(competape);
  
  
  while(!traitement.empty())
  {
    
    etape=traitement.top(); //traitement de la première Etape de la liste
    traitement.pop();
    trajets=bdd.get_disponibles(etape.ville,etape.heure,true); // récupération de la liste des trajets découlant de cette étape
    
    while(!trajets.empty()) // pour chaque trajet récupéré, on l'ajoute sous forme d'Etape à la liste des Etapes à traiter
    {
      trajet=trajets.front();
      trajets.pop_front();
      
      //On vérifie que nous ne sommes pas déjà passés par cette vie
      if(etape.gares_traverses.find((*trajet).gare_arrivee())==etape.gares_traverses.end())
      {
	
	Etape etape2=etape;
	if((*trajet).est_pieton())
	{
	  
	  etape2.heure+=(*trajet).h_arrivee();
	  etape2.ville=(*trajet).gare_arrivee();
	  etape2.trajets_effectues.push_back(trajet);	
	  etape2.gares_traverses.insert(etape2.ville);
	}
	else
	{
	  //Si l'heure de départ du train est déjà passée
	  if(etape2.heure>(trajet->h_depart()+1440*etape2.heure.jour()))
	  {
	    //On prend ce même train, mais le lendemain
	    //std::cout<<etape2.heure.jour()<<"\n";
	    etape2.heure=trajet->h_arrivee()+1440*(1+etape2.heure.jour());
	  }
	  else
	  {
	   etape2.heure=(*trajet).h_arrivee()+1440*etape2.heure.jour(); 
	  }
	  etape2.prix_total+=(*trajet).prix()*((*trajet).h_arrivee()-(*trajet).h_depart()).value()/60;
	  etape2.ville=(*trajet).gare_arrivee();
	  etape2.trajets_effectues.push_back(trajet);
	  etape2.gares_traverses.insert(etape2.ville);
	}
	
	//On vérifie que l'étape actuelle ne dépasse pas le "pire" du top X
	if(resultats.size()<TAILLE_TOP_SCORE || !competape(etape2,*resultats.begin()))
	{
	  if(etape2.ville==arrivee)//// si on est arrivé à la bonne ville
	  {
	    //Et que c'est un aller simple
	    if(!retour)
	    {
	      //On met à jour le TOPX
	      resultats.insert(etape2);
	      //Condition de premier "remplissage" du TOP X
	      if(resultats.size()> TAILLE_TOP_SCORE)
	      {
		resultats.erase(resultats.begin());
	      }
	    }
	    
	    //Cas d'arrivée à la ville (mais retour à faire)
	    else
	    {
	      //Si on est arrivé avant l'heure de retour, on se place à cette heure de retour
	      if(etape2.heure<heure_retour)
	      {
		etape2.heure=heure_retour;
	      }
	      //On vide les villes traversés
	      etape2.gares_traverses.clear();
	      etape2.gares_traverses.insert(arrivee);
	    }
	    
	  }// fin ville arrivee
	  
	  //Si on est revenu à la ville de départ (cas aller-retour)
	  else if(etape2.ville==depart)
	  {
	      resultats.insert(etape2);
	      //Condition de premier "remplissage" du TOP X
	      if(resultats.size()> TAILLE_TOP_SCORE)
	      {
		resultats.erase(resultats.begin());
	      }
	  }
	  //Si on est encore dans le chemin
	  else
	  {
	    traitement.push(etape2);
	  } 
	}
      }
    }
  }
  return resultats;
  
}