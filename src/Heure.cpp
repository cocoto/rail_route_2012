#include "Heure.hpp"
Heure::Heure():minutes(0){}
Heure::Heure(const int &h,const int &m){
  minutes=(h*60+m);
}

Heure::Heure(const int &m)
{
  minutes=m;
}
Heure::Heure(const int &h,const int &m, const int &d)
{
  minutes=((d*24+h)*60+m);
}
Heure Heure::operator+(const Heure &b)const{
  return Heure(minutes+b.minutes);
}
Heure Heure::operator+(const int &m)const{
  return Heure(minutes+m);
}

Heure Heure::operator-(const Heure &b)const
{
    return Heure(minutes-b.minutes);
}

Heure Heure::operator-(const int &m)const
{
    return Heure(minutes-m);
}

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

void Heure::set(const int &h, const int &m){
  minutes=(h*60+m)%1440;
}

std::ostream& operator<<(std::ostream &flux, const Heure &heure)
{
  flux<<((heure.heure()<10)?"0":"")<< heure.heure()<<":"<<((heure.minute()<10)?"0":"")<<heure.minute();
  return flux;
}