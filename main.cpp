#include <iostream>
#include <cstring>
using namespace std;

class Vozac{
protected:
    char name[100];
    int age;
    int races;
    bool veteran;
public:
    Vozac()=default;
    Vozac(char name[],int age, int races, bool veteran):age(age),races(races),veteran(veteran){
        strcpy(this->name,name);
    }
    virtual int getSalary()=0;
    virtual int danok()=0;
    friend ostream& operator<<(ostream& os,const Vozac& ref) {
        if (ref.veteran) {
            os << ref.name << endl << ref.age << endl << ref.races << endl << "VETERAN" << endl;
        } else {
            os << ref.name << endl << ref.age << endl << ref.races << endl;
        }
        return os;
    }
    virtual ~Vozac(){};
    bool operator==( Vozac& ref){
        if(this->getSalary()==ref.getSalary()){
            return true;
        }
        return false;
    }
};

class Avtomobilist:public Vozac{
private:
    int price;
public:
    Avtomobilist()=default;
    Avtomobilist(char name[],int age, int races,bool veteran,int price):Vozac(name,age,races,veteran),price(price){

    }
    int getSalary(){
        return price/5;
    }

    int danok(){
        if(races>10){
            return getSalary()*0.15;
        }else{
            return getSalary()*0.10;
        }
    }

};

class Motociklist:public Vozac{
private:
    int power;
public:
    Motociklist()=default;
    Motociklist(char name[],int age,int races, bool  veteran,int power):Vozac(name,age,races,veteran),power(power){}
    int getSalary(){
        return power*20;
    }

    int danok(){
        if(veteran){
            return getSalary()*0.25;
        }else{
            return getSalary()*0.2;
        }
    }
};

int soIstaZarabotuvachka(Vozac* pointer[],int n,Vozac* eden){
    int i,ista_zarabotuvacka=0;
    for(i=0;i<n;i++){
        if(eden->getSalary()==pointer[i]->getSalary())
            ista_zarabotuvacka++;
    }
    return ista_zarabotuvacka;
}


int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}