//cat rescue app
//se acopera concepte de poo cum ar fi: definirea claselor, constructorul fara parametrii, constructorul cu parametrii, constructorul de copiere, destructorul, operatorul =, getteri si setteri
//am acoperit si 3 metode: feed, play, status, care modifica hunger si mood si afiseaza un rezumat al starii pisicii


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Cat{ //am creat o clasa, care modeleaza pisica dupa nume, rasa, varsta, mood, si hunger
  private: 
    char* name;
    char* breed;
    int age;
    bool rescued;
    int mood;
    int hunger;
  public:

  // constructor fara parametrii

    Cat(){
      this -> name = nullptr;
      this->breed = nullptr;
      this->age = 0 ;
      this->rescued = false;
      this->mood = 5;
      this->hunger = 5;
    }

    // constructor cu parametrii
    Cat( const char* name, const char* breed, int age, bool rescued, int mood, int hunger){
     if (name != nullptr){
       this->name = new char[strlen(name) + 1];
       strcpy_s(this->name, strlen(name) + 1, name);
     }else{
       this->name = nullptr;
     }

     if (breed != nullptr){
       this->breed = new char[strlen(breed) + 1];
       strcpy_s(this->breed, strlen(breed) + 1, breed);
     } else{
       this->breed = nullptr;
     }

     this->age = age;
     this->rescued = rescued;
     this->mood = mood;
     this->hunger = hunger;
    }
    
    //constructorul de copiere

    Cat(const Cat& c){
      if(c.name != nullptr){
        this->name = new char[strlen(c.name) + 1];
        strcpy_s(this->name, strlen(c.name) + 1, c.name);
      } else{
        this->name = nullptr;
      }

      if(c.breed != nullptr){
        this->breed = new char[strlen(c.breed) + 1];
        strcpy_s(this->breed, strlen(c.breed) + 1, c.breed);
      }else{
        this->breed = nullptr;
      }

      this->age = c.age;
      this->rescued = c.rescued;
      this->mood = c.mood;
      this->hunger = c.hunger;
    }

    //destructorul

    ~Cat(){
      if (this->name != nullptr){
        delete[] this->name;
      }

      if (this->breed != nullptr){
        delete[] this->breed;
      }
    }


    // getteri 

    char* getName() const{
      return this->name;
    }

    char* getBreed() const{
      return this->breed;
    }

    int getAge() const{
      return this->age;
    }

    bool isRescued() const{
      return this->rescued;
    }

    int getMood() const{
      return this->mood;
    }

    int getHunger() const{
      return this->hunger;
    } 

    //setteri
     //setter pentru atributul mood (0 pentru trist, 10 pentru foarte fericit)
     //cu aceasta metoda ne asiguram ca valoarea introdusa este in intervalul [0,10]
    void setMood (int mood){
      if(mood<0){ //nu permitem utilizatorului sa introduca valori negative
        this->mood = 0;
      }else if(mood>10){ //nu permitem utilizatorului sa introduca valori mai mari decat 10, daca face acest lucru, valoarea se va reseta la 10
        this->mood = 10;
      } else{
        this->mood = mood; // daca se introduce o valoare intre 0 si 10 o acceptam, este valida
      }
    }

    // setter pentru atributul hunger (0, pisica foarte flamand, 10 pentru satul)
    void setHunger(int hunger){
      if(hunger<0){ //nu permitem utilizatorului sa introduca valori negative, daca face acest lucru, hunger se va reseta la 0
        this->hunger = 0;
      }else if(hunger>10){ //nu pemitem utilizatorului sa introduca valori mai mari decat 10, daca face acest lucru valoarea se reseteaza la 10
        this->hunger = 10;
      }else{
        this->hunger = hunger; //orice valoare in intervalul 0-10 este acceptata
      }
    }

    void setRescued(bool rescued){
      this->rescued = rescued; //permite actualizarea statusului pisicii, daca aceasta este salvata sau nu
    }

    //operatorul =

    Cat& operator=(const Cat& c){

      if (this == &c){
        return *this;
      }

      if( this-> name != nullptr){
        delete[] this->name;
      }

      if(this->breed != nullptr){
        delete[] this->breed;
      }

      if(c.name != nullptr){
        this->name = new char[strlen(c.name) + 1];
        strcpy_s(this->name, strlen(c.name) + 1, c.name);
      }else{
        this->name = nullptr;
      } 


      if (c.breed !=nullptr){
        this->breed = new char[strlen(c.breed) + 1];
        strcpy_s(this->breed, strlen(c.breed) + 1, c.breed);
      } else {
        this->breed = nullptr;
      }

      this->age = c.age;
      this->rescued = c.rescued;
      this->mood = c.mood;
      this->hunger = c.hunger;

      return *this;
    }
    

    //cu aceasta functie putem hrani una din pisicile noastre, una din metode
    void feed(){ 
      this->hunger = this ->hunger + 1;
      if (this->hunger > 10) {
        this->hunger = 10;
      }
      if (this->hunger <=3){
        cout << "The cat was really hungry" << endl;
      }else if (this->hunger <=7){
        cout << "The cat is almost full" << endl;
      } else if (this->hunger < 10){
        cout << "The cat is full...." << endl;
      } else if (this->hunger ==10) {
          cout << "The cat can not eat anymore... \n";
      }
    }

    //functia play

    void play (){
      this->mood = this->mood + 1;
      if (this->mood >= 10){
        this->mood = 10;
      }
      // afisare de mesaje pentru a vedea un status legat de mood-ul picii

      if (this->mood <= 3){
        cout << "The cat is sad" << endl;
      } else if (this->mood <=7 ){
        cout << "The cat mood is ok-ish..." << endl;
      } else if ( this->mood > 7 && this->mood <=10) {
        cout << "The cat is happy, yeeeeey" << endl;
      }
    }

    //functia status, aflam in ce stare se afla pisica noastra
  

    void status () {
      cout << "-------Cat Status--------" << endl;
      cout << "Name:" << this->name << endl;
      cout << "Breed:" << this->breed << endl;
      cout << "Age:" << this->age << endl;
      if (this->rescued == true ){
        cout << "Rescued: YES" << endl;
      } else if (this->rescued == false){
        cout << "Rescued: NO" << endl;
      }
      cout << "Mood: " << this->mood << endl;
      cout << "Hunger :" << this->hunger << endl;
    }
};


int main(){
 
  Cat tom("Tom", "British Shorthair", 2, false, 5, 8);
  Cat garfield("The orange cat", "European", 4, false, 8, 5);
  Cat tomas("Tomas", "Siamese", 1, false, 1, 9);

  int option;
  do{
  cout << " Welcome to the pet rescue app. To continue please choose one of the following options: \n\n ";
  cout << "1) View pets" << endl;
  cout << "2) Feed a pet" << endl;
  cout << "3) Play with a pet" << endl;
  cout << "4) Check status" << endl;
  cout << "0) Exit" << endl;

  cout << "The option you are choosing is: ";
  cin >> option;

  switch (option){
    case 1:
      cout << "Tom: " << tom.getName() << endl;
      cout << "Garfield: " << garfield.getName() << endl;
      cout << "Tomas: " << tomas.getName() << endl;
    break;
    case 2:
      cout << "1) Tom" << endl;
      cout << "2)Garfield" << endl;
      cout << "3) Tomas" << endl;
      int catChoice;
      cout << " Choose which cat you want to feed: ";
      cin >> catChoice;
      if (catChoice == 1){
        tom.feed();
      } 
      else if (catChoice == 2){
        garfield.feed();
      } 
      else if (catChoice == 3){
        tomas.feed();
      }
      break;
    case 3:
      cout << "1) Tom" << endl;
      cout << "2) Garfield" << endl;
      cout << "3) Tomas" << endl;
      int playChoice;
      cout << " Which is the cat you want to play with?";
      cin >> playChoice;

      if (playChoice == 1){
        tom.play();
      }
      else if(playChoice == 2){
        garfield.play();
      }
      else if(playChoice == 3){
        tomas.play();
      }

    break;
    case 4:
      cout << "1) Tom" << endl;
      cout << "2) Garfield" << endl;
      cout << "3) Tomas" << endl;
      int catStatus;
      cout << "Which is the cat you want to see the status of? ";
      cin >> catStatus;

      if (catStatus == 1 ){
        tom.status();
      }
      else if(catStatus == 2){
        garfield.status();
      }
      else if( catStatus==3){
        tomas.status();
      }
      break;
    case 0:
      cout << "Exiting the Pet Rescue App... Goodbye!" << endl;
    break;
    default:
      cout << " Invalid Option!" << endl;
      break;
    };
  } while (option != 0);
};
