#include "Heure.hpp"

/*
 * Constructeur de base 00:00
 */
Heure::Heure():minutes(0){}

/*
 * Constructeur de l'heure h:m du jour 0
 */
Heure::Heure(const int &h,const int &m){
  minutes=(h*60+m);
}

/*
 * Constructeur de l'heure à partir du nombre de minutes écoulés depuis 00:00 du jour 0
 */
Heure::Heure(const int &m)
{
  minutes=m;
}

/*
 * Constructeur de l'heure h:m du jour d
 */
Heure::Heure(const int &h,const int &m, const int &d)
{
  minutes=((d*24+h)*60+m);
}

/*
 * Opérateur d'addition de deux heures
 */
Heure Heure::operator+(const Heure &b)const{
  return Heure(minutes+b.minutes);
}

/*
 * Opérateur d'augmentation d'une heure de m minutes
 */
Heure Heure::operator+(const int &m)const{
  return Heure(minutes+m);
}

/*
 * Opérateur de soustraction de deux heures
 */
Heure Heure::operator-(const Heure &b)const
{
    return Heure(minutes-b.minutes);
}

/*
 * Opérateur de soustraction de m minutes à l'heure
 */
Heure Heure::operator-(const int &m)const
{
    return Heure(minutes-m);
}

/*
 * Opérateur d'auto augmentation/soustraction
 */
 Heure& Heure::operator+=(const Heure &b)
{
  minutes=(minutes+b.minutes);
  return *this;
}
Heure& Heure::operator-=(const Heure &b)
{
   minutes=(minutes-b.minutes); 
  return *this;
}
Heure& Heure::operator+=(const int &m)
{
  minutes=(minutes+m);
  return *this;
}
Heure& Heure::operator-=(const int &m)
{
   minutes=(minutes-m);
  return *this;
}

//Opérateur d'affectation
Heure& Heure::operator=(const Heure &h)
{
  minutes=h.minutes;
  return *this;
}

//Accesseurs
int Heure::jour() const
{
  return (minutes/60)/24;
}
int Heure::heure()const{
  return minutes/60%24;
}
int Heure::minute()const{
  return minutes%60;
}
int Heure::value()const{
  return minutes;
}

/*
 * Opérateurs de comparaison
 */
bool Heure::operator==(const Heure&b)const
{
  return minutes==b.minutes;
}
bool Heure::operator<(const Heure&b)const
{
  return minutes<b.minutes;
}
bool Heure::operator>(const Heure&b)const
{
  return minutes>b.minutes;
}
bool Heure::operator<=(const Heure&b)const
{
  return minutes<=b.minutes;
}
bool Heure::operator>=(const Heure&b)const
{
  return minutes>=b.minutes;
}
bool Heure::operator!=(const Heure&b)const
{
  return minutes!=b.minutes;
}

/*
 * Changement d'une heure
 */
void Heure::set(const int &h, const int &m){
  minutes=(h*60+m)%1440;
}

/*
 * Opérateur de flux
 * retourne l'heure sous la forme hh:mm
 */
std::ostream& operator<<(std::ostream &flux, const Heure &heure)
{
  flux<<((heure.heure()<10)?"0":"")<< heure.heure()<<":"<<((heure.minute()<10)?"0":"")<<heure.minute();
  return flux;
}