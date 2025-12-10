#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

class Student {
  private:
  string nume;
  int nota;
  //materie - vector alocat dinamic pentru materiile pe care le-a studiat studentul (siruri de caractere)
  char* materii;
  int nrMaterii;
  int anStudiu; //util pentru clasificare si afisarea progresului academic
  bool bursier; // util in sistemele universitare pentru evidenta si filtrare

  public:

  //constructor fara parametrii

  Student() {
    this->nume="";
    this->nota = 1;
    this->materii = "";
    this->nrMaterii = 0;
    this->anStudiu = 0;
    this->bursier = false;
  };

 
};