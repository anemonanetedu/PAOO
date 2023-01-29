#include <iostream>
using namespace std;

class Masini{
  public:
  Masini(string culoare, string tara, int an):
  culoare(culoare),
  tara(tara),
  an(an) { }

  Masini& operator=(const Masini& rhs){
    if(this != &rhs){
      this->culoare=rhs.culoare;
      this->tara=rhs.tara;
      this->an=rhs.an;
    }
    return *this;
  }
  Masini(const Masini& rhs) {
      this->culoare=rhs.culoare;
      this->tara=rhs.tara;
      this->an=rhs.an;
  }

  void date(){
    cout<<"Masina";
  }

  void zgomot(){

  }
  void descriere(){
    cout<<"Masina de culoare "<<culoare<<" provenita din "<<tara<<" an de fabricatie: "<<an<<endl;
  }

  protected:
  string getCuloare(){
    return culoare;
  }

  string getTara(){
    return tara;
  }

  int getAn(){
    return an;
  }

  private:
  string culoare;
  string tara;
  int an;
};

class Dacia : public Masini{
public:
Dacia(string culoare, string tara, int an, bool primProp) :
Masini(culoare, tara, an),
primProp(primProp) {}

Dacia& operator=(const Dacia& rhs) {
  if (this != &rhs){
    Masini::operator=(rhs);
    primProp=rhs.primProp;
  }
  return *this;
}
void date(){
  cout<<"Dacia";
}
void zgomot(){
  cout<<"vrum";
}

void descriere(){
  string proprietar="primul proprietar";
  if(!primProp){
    proprietar="au mai existat proprietari";
  }
  cout<<"Dacia de culoare "<<getCuloare()<<" provenita din "<<getTara()<<" din anul "<<getAn()<<endl;
}
private:
bool primProp;
};

int main() {
Masini masini=Masini("neagra", "Germania", 2014);
Dacia dacia=Dacia("alba", "Romania", 2008, true);
Dacia copyDacia=Dacia(dacia);
Dacia copyDacia2 = dacia;
masini.date();
masini.descriere();
dacia.date();
dacia.descriere();
copyDacia.descriere();
copyDacia2.descriere();

}