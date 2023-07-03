#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa{
protected:
    char coach[101];
    int goals[10];
public:
    FudbalskaEkipa()=default;
    FudbalskaEkipa(char coach[],int goals[]){
        for(int i=0;i<10;i++){
            this->goals[i]=goals[i];
        }
        strcpy(this->coach,coach);
    }
    FudbalskaEkipa(const FudbalskaEkipa& ref){
        for(int i=0;i<10;i++){
            this->goals[i]=ref.goals[i];
        }
        strcpy(this->coach,ref.coach);
    }
    virtual int uspeh() const=0;
    bool operator >(FudbalskaEkipa *pointer){
        if(this->uspeh()>pointer->uspeh())
            return true;
        return false;
    }
    FudbalskaEkipa& operator +=(const int goals_lg) {
        int i;
        for(i=0;i<9;i++){
            goals[i]=goals[i+1];
        }
        goals[i]=goals_lg;
        return *this;
    }

    friend ostream &operator<<(ostream &os,  FudbalskaEkipa &ekipa);
    virtual ~FudbalskaEkipa(){};
};



class Klub:public FudbalskaEkipa{
    char name[100];
    int trophies;
public:
    Klub(char coach[],int goals[],char name[],int trophies):FudbalskaEkipa(coach,goals),trophies(trophies){
        strcpy(this->name,name);
    }
    Klub(const Klub & ref):FudbalskaEkipa(ref),trophies(ref.trophies){
        strcpy(this->name,ref.name);
    }

    friend ostream& operator <<(ostream& os,const Klub& ref){
        os<<ref.name<<endl<<ref.coach<<endl<<ref.trophies<<endl;
    }


    int uspeh() const override {
        int uspeh=0;
        for(int i=0;i<10;i++){
            uspeh+=goals[i];
        }

        return uspeh*3+trophies*1000;
    }

};

class Reprezentacija:public FudbalskaEkipa{
private:
    char name[100];
    int games;
public:
    Reprezentacija()=default;
    Reprezentacija(char coach[],int goals[],char name[],int games):FudbalskaEkipa(coach,goals),games(games){
        strcpy(this->name,name);
    }
    Reprezentacija(const Reprezentacija& ref):FudbalskaEkipa(ref),games(ref.games){
        strcpy(this->name,ref.name);
    }
    friend ostream& operator <<(ostream& os,const Reprezentacija& ref){
        os<<ref.name<<endl<<ref.coach<<endl<<ref.uspeh()<<endl;
    }

    int uspeh() const override{
        int uspeh=0;
        for(int i=0;i<10;i++){
            uspeh+=goals[i];
        }

        return uspeh*3+games*50;
    }
};



ostream &operator<<(ostream &os,  FudbalskaEkipa &ekipa) {
    Klub *tmp=dynamic_cast<Klub*>(&ekipa);
    if(tmp!=NULL){
        cout<<*tmp;
    }else{
        Reprezentacija * rep=dynamic_cast<Reprezentacija*>(&ekipa);
        cout<<*rep;
    }
}

void najdobarTrener(FudbalskaEkipa** niza,int n){
    FudbalskaEkipa* ptr=niza[0];
    int max=niza[0]->uspeh();
    for(int i=1;i<n;i++){
        if(niza[i]->uspeh()>max){
            max=niza[i]->uspeh();
            ptr=niza[i];
        }
    }
    cout<<*ptr;
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}