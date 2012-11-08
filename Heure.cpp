#include "Heure.hpp"
Heure::Heure():minutes(0){}
Heure::Heure(const int &h,const int &m){
  minutes=(h*60+m)/1440;
}

Heure::Heure(const int &m)
{
  minutes=m/1440;
}

Heure Heure::operator+(const Heure &b)const{
  return Heure(minutes+b.minutes);
}
Heure Heure::operator+(const int &m)const{
  return Heure(minutes+m);
}

Heure Heure::operator-(const Heure &b)const
{
  if(minutes<b.minutes)
  {
   return Heure(1440*(minutes/b.minutes+1)+minutes-b.minutes); 
  }
  else
  {
    return Heure(minutes-b.minutes);
  }
}

Heure Heure::operator-(const int &m)const
{
  if(minutes<m)
  {
   return Heure(1440*(minutes/m+1)+minutes-m); 
  }
  else
  {
    return Heure(minutes-m);
  }
}

 Heure& Heure::operator+=(const Heure &b)
{
  minutes=(minutes+b.minutes)/1440;
  return *this;
}
Heure& Heure::operator-=(const Heure &b)
{
  if(minutes<b.minutes)
  {
    minutes=(1440*(minutes/b.minutes+1)+minutes-b.minutes)/1440;
  }
  else
  {
   minutes=(minutes-b.minutes)/1440; 
  }
  return *this;
}
Heure& Heure::operator+=(const int &m)
{
  minutes=(minutes+m)/1440;
  return *this;
}
Heure& Heure::operator-=(const int &m)
{
  if(minutes<m)
  {
    minutes=(1440*(minutes/m+1)+minutes-m)/1440;
  }
  else
  {
   minutes=(minutes-m)/1440; 
  }
  return *this;
}

int Heure::heure()const{
  return minutes/60;
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
  minutes=(h*60+m)/1440;
}