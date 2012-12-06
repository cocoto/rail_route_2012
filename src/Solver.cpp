#include "Solver.hpp"
/*
 * Fonction de calcul des TAILLE_TOP_SCORE meilleures solutions 
 * Au départ de la gare "depart" vers "arrivee" à l'"heure_depart" 
 * Selon le ratio (temps/cout) de préférence
 * En repartant au plus tôt à heure_retour dans le cadre d'un aller-retour (booléen retour)
 */
std::set<Etape, Comparator_Etape> Calcul_trajet(const std::string &depart,const std::string &arrivee,const Heure &heure_depart, const float &preference,Bdd &bdd, const bool &retour, const Heure &heure_retour, const int &classe)
{
  //traitement est la liste des étapes à traiter (cf Comparator)
  std::priority_queue<Etape, std::vector<Etape>, Comparator> traitement((Comparator(preference)));
  std::list<Ligne_Bdd*> trajets; //Liste des trajets disponibles depuis une gare de départ à une certaine heure
  Etape etape; //Étape initiale ou récupérée depuis la file de traitement
  
  /*Mise en place du problème initial et ajout de la première étape à la file de traitement
   */
  etape.heure=heure_depart;
  etape.ville=depart;
  etape.gares_traverses.insert(depart);
  etape.prix_total=0;
  traitement.push(etape);
  
  
  Ligne_Bdd* trajet; //Un trajet parmis les trajets possibles
  /*
   * Création de du topX (résultat)
   */
  Comparator_Etape competape(preference);
  std::set<Etape, Comparator_Etape> resultats(competape);

    // Tant qu'il reste des tâches à traiter
    while(!traitement.empty())
    {
	
	//Récupération et retrait de la première tâche à traiter
        etape=traitement.top();
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
                    //Traitement de la classe
                    if(classe==1)
                    {
                        etape2.prix_total+=(float)(*trajet).prix()*((*trajet).h_arrivee()-(*trajet).h_depart()).value()/60;
                    }
                    else
                    {
                        etape2.prix_total+=((float)(*trajet).prix()/2)*((*trajet).h_arrivee()-(*trajet).h_depart()).value()/60;
                    }
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
                            traitement.push(etape2);
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
            }//Fin Cas ville non visitée
        }//Fin de parcourt des trajets possibles
    }//Liste des tâches vides
    return resultats;

}
