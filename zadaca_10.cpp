#include <iostream>
#include <cstring>
using namespace std;

class NegativnaVrednost{
public:
    NegativnaVrednost()=default;
    void print(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};
class Oglas{
    char title[51];
    char category[31];
    char description[101];
    float price;
public:
    Oglas()=default;
    Oglas(char title[],char category[],char description[],float price):price(price){
        strcpy(this->title,title);
        strcpy(this->category,category);
        strcpy(this->description,description);
    }
    Oglas(const Oglas& ref):price(ref.price){
        strcpy(this->title,ref.title);
        strcpy(this->category,ref.category);
        strcpy(this->description,ref.description);
    }

    bool operator >(const Oglas& ref){
        if(this->price>ref.price)
            return true;
        return false;
    }
    friend ostream& operator <<(ostream& os,const Oglas& ref){
        os<<ref.title<<endl<<ref.description<<endl<<ref.price<<" evra"<<endl;
        return os;
    }

    const char *getTitle() const {
        return title;
    }

    const char *getCategory() const {
        return category;
    }

    const char *getDescription() const {
        return description;
    }

    float getPrice() const {
        return price;
    }
};

class Oglasnik{
    char name[21];
    Oglas *niza;
    int num_oglas=0;
public:
    Oglasnik()=default;
    Oglasnik(char name[]){
        strcpy(this->name,name);
    }
    Oglasnik& operator +=(const Oglas &ref){
        if(ref.getPrice()<0)
            throw NegativnaVrednost();
        Oglas *tmp=new Oglas[num_oglas+1];
        int i=0;
        for(i;i<num_oglas;i++){
            tmp[i]=niza[i];
        }
        tmp[i]=ref;
        if(num_oglas>0)
            delete [ ] niza;
        num_oglas++;
        niza=tmp;
        return *this;
    }
    friend ostream& operator<<(ostream& os,const Oglasnik &ref){
        os<<ref.name<<endl;
        for(int i;i<ref.num_oglas;i++){
            os<<ref.niza[i]<<endl;
        }
        return os;
    }
    void oglasiOdKategorija(const char *k){
        for(int i=0;i<num_oglas;i++){
            if(strcmp(niza[i].getCategory(),k)==0)
                cout<<niza[i]<<endl;
        }
    }
    void najniskaCena(){
        Oglas *least_expensive=&niza[0];
        int max=niza[0].getPrice();
        for(int i=1;i<num_oglas;i++){
            if(niza[i].getPrice()<max){
                max=niza[i].getPrice();
                least_expensive=&niza[i];
            }
        }
        cout<<*least_expensive;
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;

            }catch(NegativnaVrednost i){
                i.print();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;

            }catch(NegativnaVrednost i){
                i.print();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;

            }catch(NegativnaVrednost i){
                i.print();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;

            }catch(NegativnaVrednost i){
                i.print();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;

            }catch(NegativnaVrednost i){
                i.print();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
