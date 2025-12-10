#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

/*3p) Se consideră o aplicatie pentru gestionarea activitäții unui furnizor de energie
lectrică. Se vor urmari atribute specifice, precum: nume/denumire client, consum lunar
efectiv, consum lunar estimat, număr contract, durată contract, pret kWh etc. Datele memb
sunt private şi sunt puse la dispozitie metode de acces. Clasa contine cel puțin patru câmpı.dintre care unul este alocat dinamic, constructori, metodele specifice claselor cu membri
alocati dinamic si operatorul de afişare. Folositi un membru static sau const.
(1p) Se va defini operatorul index [] pentrua returna şi modifica valoarea consumului lunaefectiv dintr-o anumita luna din contract.
(1p) Definiti operatorul de conversie la double, care va returma valoarea totală a
diferentelor lunare de consum.
(2p) Scrieti două metode o metodă pentru determinarea lunii cu cea mai mica diferenţa de
consum si o metoda care calculeaza valoarea totala consumului efectiv.
(2p) Exemplificati conceptul de virtualizare prin utilizarea unei clase abstracte
(1p) Propuneti un container STL carea permite efectuarea rapidă a operatiilor de regasire
după numarul contractuli
Punctul din oficiu este inclus in prima cerinta. Neimplementarea acesteia va conduce la
notarea examenului cu 1
Pentru a fi luate in considerare, solutiile trebuie să nu contină erori de compilare
Implementarea solutiel trebuie să fie însotita de descrierea conceptelor folosite*/


class Energie{
  private:
    char *numeClient;
    float consumLunarEfectiv;
    float consumLunarEstimat;
    int idContract;
    float pretKwh;

    static const int durata_contract;

    public:

    //constructorul fara parametrii

    Energie(){
      this->numeClient = nullptr;
      this->consumLunarEfectiv = 0;
      this->consumLunarEstimat = 0;
      this->idContract = 1;
      this->pretKwh = 1;
    }

    //constructorul cu parametrii

    Energie(const char *numeClient, float consumLunarEfectiv, float consumLunarEstimat, int idContract, float pretKwh){
      if(numeClient !=nullptr){
          this->numeClient = new char[strlen(numeClient) + 1];
          strcpy_s(this->numeClient, strlen(numeClient) + 1, numeClient);
      }
      else{
        this->numeClient = nullptr;
      }
      this->consumLunarEfectiv = consumLunarEfectiv;
      this->consumLunarEstimat = consumLunarEstimat;
      this->idContract = idContract;
      this->pretKwh = pretKwh;
    }

    //constructorul de copiere

    Energie(const Energie& e){
      if(e.numeClient != nullptr){
        this->numeClient = new char[strlen(e.numeClient) + 1];
        strcpy_s(this->numeClient, strlen(e.numeClient) + 1, e.numeClient);
      }
      else{
        this->numeClient = nullptr;
      }

      this->consumLunarEfectiv = e.consumLunarEfectiv;
      this->consumLunarEstimat = e.consumLunarEstimat;
      this->idContract = e.idContract;
      this->pretKwh = e.pretKwh;
    }

    //destructorul

     ~Energie(){
      if(this->numeClient!=nullptr){
        delete[] this->numeClient;
      }
      else{
        this->numeClient = nullptr;
      }

     }

     //operatorul =

    Energie& operator=(const Energie &e ){
      if(this == &e){
        return *this;
      }

      if (this-> numeClient !=nullptr){
        delete[] this->numeClient;
      }

      //deep copy pt nume 

      if(e.numeClient != nullptr){
        this->numeClient = new char[strlen(e.numeClient) + 1];
        strcpy_s(this->numeClient, strlen(e.numeClient) + 1, e.numeClient);
      }
      else{
        this->numeClient = nullptr;
      }
      return *this;

      //copiem atributele simple

      this->consumLunarEfectiv = e.consumLunarEfectiv;
      this->consumLunarEstimat = e.consumLunarEstimat;
      this->idContract = e.idContract;
      this->pretKwh = e.pretKwh;
    }








};