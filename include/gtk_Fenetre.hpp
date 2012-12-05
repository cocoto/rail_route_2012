#ifndef _FENETRE_H_
#define _FENETRE_H_
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/stock.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/scale.h>
#include <gtkmm/table.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>
#include <set>
class Fenetre: public Gtk::Window{
protected:
  Gtk::VBox _boitev;
  Gtk::Toolbar _toolbar;
  Gtk::ToolButton _ouvrir_instance;
  Gtk::ToolButton _ouvrir_villes;
  Gtk::ToolButton _reset_probleme;
  Gtk::Frame _frame_recherche;
  Gtk::Frame _frame_resultats;
  Gtk::Table _boite_recherche;
  Gtk::ComboBoxText _liste_gare_depart;
  Gtk::ComboBoxText _liste_gare_arrivee;
  Gtk::ComboBoxText _heure_depart;
  Gtk::ComboBoxText _minute_depart;
  Gtk::HScale _rapport;
  Gtk::Label _gare_depart;
  Gtk::Label _gare_arrivee;
  Gtk::Label _label_hdepart;
  Gtk::Label _label_coeff;
  Gtk::Label _label_prix;
  Gtk::Label _label_temps;
  Gtk::Label _label_resultat;
  Gtk::HBox _box_scale;
  Gtk::Button _bouton_recherche;
  Gtk::ScrolledWindow _barresDeDefilement_resultat;
  Gtk::VBox _box_resultats;
  void ouvrir_fichier();
  void ouvrir_fichier_ville();
  void clear_instances();

  sigc::signal<void,std::string> _signal_file_selected;
  sigc::signal<void,std::string> _signal_file_ville_selected;
  sigc::signal<void> _signal_clear_instances;
  sigc::signal<void,std::string,std::string,int,int,float> _signal_rechercher;
  
public :
  Fenetre();
  sigc::signal<void,std::string> signal_file_selected();
  sigc::signal<void,std::string> signal_file_ville_selected();
  sigc::signal<void,std::string,std::string,int,int,float> signal_rechercher();
  sigc::signal<void> signal_clear_instances();
  void set_resultats(const std::string &res);
  void set_gares(const std::set< std::string >&);
  void vider_ville();
  void rechercher();
};


#endif