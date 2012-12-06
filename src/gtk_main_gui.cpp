#include <gtkmm/main.h>
#include <gtkmm/filechooserdialog.h>
#include "gtk_Fenetre.hpp"
#include "Bdd.hpp"
#include "Gtk_main_gui.hpp"
 Gtk_main_gui::Gtk_main_gui(Bdd *bdd, Fenetre *fenetre)
 {
   _bdd=bdd;
   _fenetre=fenetre;
   _fenetre->signal_file_selected().connect(sigc::mem_fun(*this,&Gtk_main_gui::load_file));
   _fenetre->signal_file_ville_selected().connect(sigc::mem_fun(*this,&Gtk_main_gui::load_file_ville));
   _fenetre->signal_clear_instances().connect(sigc::mem_fun(*this,&Gtk_main_gui::clear_problem));
   _fenetre->signal_rechercher().connect(sigc::mem_fun(*this,&Gtk_main_gui::rechercher));
 }
 void Gtk_main_gui::load_file(std::string file)
 {
   _bdd->load_routes_file(file);
   _fenetre->set_gares(_bdd->gare_list());
 }
 void Gtk_main_gui::load_file_ville(std::string file)
 {
   _bdd->load_gares_file(file);
   _fenetre->set_gares(_bdd->gare_list());
 }
  void Gtk_main_gui::clear_problem()
  {
    _bdd->effacer();
    _fenetre->vider_ville();
  }
  /*
   * Fonction récupérant les informations de la fenêtre, lance la résolution du problème, et formatte la chaîne à afficher dans "résultats"
   */
  void Gtk_main_gui::rechercher()
  {
    bool ar=_fenetre->is_ar();
    std::ostringstream str_out; //Sortie
    std::string ville_arrivee=_fenetre->gare_a();
    //Résolution
    std::set<Etape, Comparator_Etape> resultat=Calcul_trajet(_fenetre->gare_d(),ville_arrivee,Heure(_fenetre->h_d(),_fenetre->m_d(),_fenetre->day_d()),_fenetre->rapport(),*_bdd,ar,Heure(_fenetre->h_a(),_fenetre->m_a(),_fenetre->day_a()),_fenetre->travel_class());
    str_out<<resultat.size()<<" trajets ont étés trouvés :\n";
  
    
    /*
     * 
     * Affichage (cf main.cpp)
     */
  std::list<Ligne_Bdd*>::const_iterator it;
  std::set<Etape, Comparator_Etape>::reverse_iterator rit=resultat.rbegin();
  while(rit!=resultat.rend())
  {
    //Affichage de la solution
    str_out<<"\n\n=================================\nArrivée le "<<Glib::Date(rit->heure.jour()).format_string("%x")<<" à "<<(*rit).heure<<" coût : "<<(*rit).prix_total<<"\n\n";
    if(ar)
    {
     str_out<<"\n-------------  Trajet Aller :   -------------\n"; 
    }
    it=((*rit).trajets_effectues.begin());
    while(it!=(*rit).trajets_effectues.end())
    {
      if((*it)->est_pieton())
      {
	str_out<<"Se rendre à pied à "<<(*it)->gare_arrivee()<<" (env."<<(*it)->h_arrivee().value()<<" minutes)\n";
      }
      else
      {
	str_out<<"Prendre le train de "<<(*it)->h_depart()<<" en direction de "<<(*it)->gare_arrivee()<<" (arrivée à "<<(*it)-> h_arrivee()<<")\n";
      }
      if((*it)->gare_arrivee()==ville_arrivee && ar)
      {
	str_out<<"\n-------------  Trajet Retour :   -------------\n";
      }
      it++;
    }
    str_out<<"=================================\n";
    
    rit++;
  }
  //Commande de mise à jour des résultats
  _fenetre->set_resultats(str_out.str());
  }
  
//Fonction allouant une fenêtre, une base de donnée, et un contrôleur les reliants
int main(int argc, char* argv[]) {
    Gtk::Main app(argc, argv); //Initialisation de GTK
    Fenetre fenetre;
    Bdd bdd;
    Gtk_main_gui main(&bdd,&fenetre);
    Gtk::Main::run(fenetre); //Lancement de la fenêtre
    return 0;
}


