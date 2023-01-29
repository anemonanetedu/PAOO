#include<iostream>
#include <memory>

using namespace std;


class Uncopyable
{
    protected:
        Uncopyable() {}
        ~Uncopyable() {}

    private:
        Uncopyable(const Uncopyable&);
        Uncopyable& operator=(const Uncopyable&);
};

 
class Masina
{   
    private:
        std::string culoare;
        std::string tara;
        int an;
        bool primProp;

    public:
        /* Default Constructor */
        Masina(): culoare("Inexistent"),tara("Inexistent"),an(0), primProp(false){}

        /* Constructor */
        Masina(const std::string& culoare, const std::string& tara, const int &an,const bool &primProp)
        :culoare(culoare), 
        tara(tara), 
        an(an), 
        primProp(primProp)
        {}
        
        /* Custom Copy Constructor, commented due to Item 6 */
        Masina(const Masina& other) :culoare(other.culoare), tara(other.tara), an(other.an), primProp(other.primProp)
        {}

        /* Custom assignment operator */
        Masina& operator=(const Masina& rhs)
        {
            if(this == &rhs)
            {
                std::cout<<"Obiectele sunt identice!\n";
                return *this;
            }
            this->tara = rhs.tara;
            this->culoare = rhs.culoare;
            this->an= rhs.an;
            this->primProp = rhs.primProp;
            return *this;
        }

        /* Custom Destructor */
        ~Masina()
        {
            std::cout<<"Object has been completely removed from memory!\n";
        }

        void show()
        {
            std::cout<<"Masina: " << this->culoare << "\nTara: " << this->tara << "\n" << this->an << "\n";
        }


        bool getPrimProp()
        {
            return this->primProp;
        }

        void setPrimProp(bool value)
        {
            this->primProp = value;
        }

        string getCuloare(){
          return culoare;

        }

    
};


//Metoda care returneaza un pointer la un obiect Masina alocat dinamic
Masina* createMasina(const std::string& culoare, const std::string& tara, const int &an,const bool &primProp)
{
    return new Masina(culoare, tara, an,primProp);
}

void printNewMasina(const std::string& culoare, const std::string& tara, const int &an,const bool &primProp)
{   //primim resursa in momentul crearii la auto_ptr
    std::auto_ptr<Masina> pMasina(createMasina(culoare,tara,an,primProp));
    pMasina -> show();
}//la iesire, stergem resursa pMasina prin destructorul auto_ptr

//item14
void lockObject(Masina& masina)
{
    masina.setPrimProp(true);
    std::cout<<"Blocam masina.\n";//blocheaza Masina indicata de masina
};

void unlockObject(Masina& masina)
{
    masina.setPrimProp(false);
    std::cout<<"Deblocam masina.\n";
};

class LockedMasina: private Uncopyable
{
    public:
         LockedMasina(Masina& other): pMasina(other)
        {
            //blocam masina
            lockObject(pMasina);
        }
        ~LockedMasina()
        {
            //unlock obj masina automatically by destructor
            unlockObject(pMasina);
            std::cout<<"Object has been completely removed from memory!\n";
        }
    private:
        Masina& pMasina;
};

int main()
{
    //item 13 with "auto_ptr"
    std::auto_ptr<Masina> Masina1(createMasina("Audi","Germania",2013,false));
    Masina1 -> show();

    auto_ptr<Masina> Masina2(Masina1); // Masina2 pointeaza acum spre obiectul creat
    Masina2 -> show();  
    
    //item 13 "shared_ptr"
    shared_ptr<Masina> Masina3(createMasina("BMW","Franta",2002,false));
    Masina3->show();

    shared_ptr<Masina> Masina4(Masina3);   // Masina3 si Masina4 pointeaza acum spre acelasi obiect returnat de createMasina
   Masina4->show();  

    //item 14
    Masina Masina5("Nissan","Franta", 2012, false);
    {
        LockedMasina Masina6(Masina5);     
        
    }
    cout<<'\n'<<"Culoare: "<<Masina5.getCuloare()<<" Locked value: "<<Masina5.getPrimProp()<<'\n';


    
    return 0;
}