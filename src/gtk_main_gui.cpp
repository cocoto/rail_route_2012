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
  void Gtk_main_gui::rechercher(const std::string &depart,const std::string &arrivee, const int &hdepart, const int &mdepart, const float &rapport)
  {
    std::ostringstream str_out;
    std::set<Etape, Comparator_Etape> resultat=Calcul_trajet(depart,arrivee,Heure(hdepart,mdepart),rapport,*_bdd,false,Heure(0));
    str_out<<resultat.size()<<" trajets ont étés trouvés :\n";
  
  std::list<Ligne_Bdd*>::const_iterator it;
  std::set<Etape, Comparator_Etape>::reverse_iterator rit=resultat.rbegin();
  while(rit!=resultat.rend())
  {
    //Affichage de la solution
    str_out<<"=================================\nHeure d'arrivée : "<<(*rit).heure<<" coût : "<<(*rit).prix_total<<"\n-------------\n";
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
      it++;
    }
    str_out<<"=================================\n";
    
    rit++;
  }
  _fenetre->set_resultats(str_out.str());
  }
int main(int argc, char* argv[]) {
    Gtk::Main app(argc, argv);
    Fenetre fenetre;
    Bdd bdd;
    Gtk_main_gui main(&bdd,&fenetre);
    Gtk::Main::run(fenetre);
    return 0;
}


