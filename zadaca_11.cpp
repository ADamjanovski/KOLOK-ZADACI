#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код
class Delo{
    char name[51];
    int year;
    char country[51];
public:
    Delo()=default;
    Delo(char name[],int year,char country[]):year(year){
        strcpy(this->name,name);
        strcpy(this->country,country);
    }
    Delo(const Delo& ref):year(ref.year){
        strcpy(this->name,ref.name);
        strcpy(this->country,ref.country);
    }

    const char *getIme() const {
        return name;
    }

    int getYear() const {
        return year;
    }

    void setYear(int year) {
        Delo::year = year;
    }

    const char *getCountry() const {
        return country;
    }

    bool operator ==(const Delo& ref){
        if(strcmp(this->name,ref.name)==0)
            return true;
        return false;
    }

};

class Pretstava{
    Delo onscreen;
    int sold_tickets;
    char date[16];
public:
    Pretstava(Delo onscreen,int sold_tickets,char date[]):sold_tickets(sold_tickets),onscreen(onscreen){
        strcpy(this->date,date);
    }
    Pretstava(const Pretstava& ref):onscreen(ref.onscreen),sold_tickets(ref.sold_tickets){
        strcpy(this->date,ref.date);

    }
    virtual int cena() {
        int cena = 0;
        if (onscreen.getYear()>=1900) {
            cena += 50;
        } else if (onscreen.getYear()>=1800)
            cena += 75;
        else
            cena += 100;
        if (strcmp(onscreen.getCountry(), "Italija") == 0)
            cena += 100;
        else if (strcmp(onscreen.getCountry(), "Rusija") == 0)
            cena += 150;
        else
            cena += 80;
        return cena;
    }

    const Delo &getDelo() const {
        return onscreen;
    }

    int getSoldTickets() const {
        return sold_tickets;
    }

    const char *getDate() const {
        return date;
    }

};

class Balet:public Pretstava{
    static int balet_price;
public:
    Balet()=default;
    Balet(Delo d,int sold_tickets,char date[]): Pretstava(d,sold_tickets,date){}
    Balet(const Balet& ref): Pretstava(ref){}

    int cena() override{
        return Pretstava::cena()+balet_price;
    }

    static void setCenaBalet(int baletPrice) {
        balet_price = baletPrice;
    }
};
class Opera:public Pretstava{
public:
    Opera()=default;
    Opera(Delo d,int sold_tickets,char date[]): Pretstava(d,sold_tickets,date){}
    Opera(const Opera& ref): Pretstava(ref){}

};

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}

int prihod(Pretstava **niza,int n){
    int vkupen_prihod=0;
    for(int i=0;i<n;i++)
        vkupen_prihod+=(niza[i]->cena()*niza[i]->getSoldTickets());
    return vkupen_prihod;
}

int brojPretstaviNaDelo(Pretstava** niza,int n, Delo f){
    int broj_pretstavi=0;
    for(int i=0;i<n;i++){
        if(f==niza[i]->getDelo()){
            broj_pretstavi++;
        }
    }
    return broj_pretstavi;
};

int Balet::balet_price=150;
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
