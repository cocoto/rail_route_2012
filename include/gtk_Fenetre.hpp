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
#include <gtkmm/calendar.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/radiobutton.h>
#include <glibmm/date.h>
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
  Gtk::Label _gare_depart;
  Gtk::Label _gare_arrivee;
  
  Gtk::VBox _depart_box;
  Gtk::HBox _radio_box;
  Gtk::RadioButtonGroup _radio_groupe;
  Gtk::RadioButton _prem_classe, _sec_classe;
  Gtk::Calendar _calendrier_depart;
  
  Gtk::HBox _box_heure_depart;
  Glib::RefPtr<Gtk::Adjustment> _ajustement_heure_d;
  Glib::RefPtr<Gtk::Adjustment> _ajustement_minute_d;
  Gtk::SpinButton _heure_depart;
  Gtk::SpinButton _minute_depart;
  
  
  Gtk::VBox _arrivee_box;
  Gtk::CheckButton _check_ar;
  Gtk::Calendar _calendrier_arrivee;
  Gtk::HBox _box_heure_arrivee;
  Glib::RefPtr<Gtk::Adjustment> _ajustement_heure_a;
  Glib::RefPtr<Gtk::Adjustment> _ajustement_minute_a;
  Gtk::SpinButton _heure_arrivee;
  Gtk::SpinButton _minute_arrivee;
  
  Gtk::HBox _box_scale;
  Gtk::HScale _rapport;
  Gtk::Label _label_coeff;
  Gtk::Label _label_prix;
  Gtk::Label _label_temps;
  Gtk::Button _bouton_recherche;
  
  Gtk::Label _label_resultat;
  
  Gtk::VBox _box_resultats;
  Gtk::ScrolledWindow _barresDeDefilement_resultat;
  
  void activer_retour();
  void ouvrir_fichier();
  void ouvrir_fichier_ville();
  void clear_instances();

  sigc::signal<void,std::string> _signal_file_selected;
  sigc::signal<void,std::string> _signal_file_ville_selected;
  sigc::signal<void> _signal_clear_instances;
  sigc::signal<void> _signal_rechercher;
  
public :
  Fenetre();
  sigc::signal<void,std::string> signal_file_selected();
  sigc::signal<void,std::string> signal_file_ville_selected();
  sigc::signal<void> signal_rechercher();
  sigc::signal<void> signal_clear_instances();
  void set_resultats(const std::string &res);
  void set_gares(const std::set< std::string >&);
  bool is_ar();
  int travel_class();
  int day_d();
  int day_a();
  int h_d();
  int h_a();
  int m_a();
  int m_d();
  std::string gare_d();
  std::string gare_a();
  float rapport();
  void vider_ville();
  void rechercher();
};


#endif