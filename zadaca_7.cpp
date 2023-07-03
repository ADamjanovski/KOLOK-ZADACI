#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException{
    char text[50];
public:
    OutOfBoundException()=default;
    OutOfBoundException(char text[]){
        strcpy(this->text,text);
    }

    void print(){
        cout<<text;
    }
};
class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
    const static int P=4;
public:
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    // дополниете ја класата
    Karticka(const Karticka& ref){
        strcpy(this->smetka,ref.smetka);
        this->pin=ref.pin;
        this->povekjePin=ref.povekjePin;
    }
    Karticka(char* smetka,int pin, bool povekjePin):povekjePin(povekjePin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }

    virtual int tezinaProbivanje() const{
        int n=pin,i=0;
        while(n>0){
            i++;
            n/=10;
        }
        return i;
    }

    friend ostream& operator <<(ostream& os,const Karticka& ref){
        os<<ref.smetka<<": "<<ref.tezinaProbivanje()<<endl;
    }

    bool getDopolnitelenPin() const {
        return povekjePin;
    }

    const char *getSmetka() const {
        return smetka;
    }
    ~Karticka(){}
};

class SpecijalnaKarticka:public Karticka{
private:
    int *dopolnitelnipin;
    int num_pin=0;
public:
    SpecijalnaKarticka()=default;
    SpecijalnaKarticka(char smetka[],int pin): Karticka(smetka,pin){
        povekjePin=true;
    }
    SpecijalnaKarticka(const SpecijalnaKarticka& ref): Karticka(ref){
        if(num_pin>0)
             delete [] dopolnitelnipin;
        dopolnitelnipin=new int[ref.num_pin];
        num_pin=ref.num_pin;
        for(int i=0;i<num_pin;i++){
            dopolnitelnipin[i]=ref.dopolnitelnipin[i];
        }
        povekjePin=true;
    }
    SpecijalnaKarticka& operator +=(const int pin){
        if(num_pin==4){
            throw OutOfBoundException("Brojot na pin kodovi ne moze da go nadmine dozvolenoto");
        }
        int *tmp=new int[num_pin+1];
        int i=0;
        for(i=0;i<num_pin;i++){
            tmp[i]=dopolnitelnipin[i];
        }
        tmp[i]=pin;
        if(num_pin>0){
            delete [] dopolnitelnipin;
        }

        num_pin++;
        dopolnitelnipin=tmp;
        return *this;
    }
    int tezinaProbivanje() const override{
        return Karticka::tezinaProbivanje()+num_pin;
    }

    friend ostream& operator <<(ostream& os,const SpecijalnaKarticka& ref){
        os<<ref.smetka<<": "<<ref.tezinaProbivanje()<<endl;
    }

    ~SpecijalnaKarticka(){
        delete [] dopolnitelnipin;
    }

};



class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }

    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    //да се дополни класата
    void dodadiDopolnitelenPin(char * smetka, int novPin){
        int i=0;
        for(i;i<broj;i++){
            //cout<<*karticki[i];
            if(strcmp(karticki[i]->getSmetka(),smetka)==0){
                if(karticki[i]->getDopolnitelenPin()){
                    try{
                        SpecijalnaKarticka* tmp=dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                        *tmp+=novPin;
                        karticki[i]=tmp;
                    }catch (OutOfBoundException i){
                        i.print();
                    }
                }

            }
        }
    }

    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite: "<<endl;
        for(int i=0;i<broj;i++){
            SpecijalnaKarticka* tmp=dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
            if(tmp==NULL){
                if(karticki[i]->tezinaProbivanje()<=LIMIT)
                    cout<<*karticki[i];
            }else{
                if(tmp->tezinaProbivanje()<=LIMIT)
                    cout<<*tmp;
            }
        }
    }

    static void setLIMIT(int limit);
};

int Banka::LIMIT=7;

void Banka::setLIMIT(int limit) {
    LIMIT = limit;
}

int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else{
            niza[i]=new SpecijalnaKarticka(smetka,pin);
        }
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.dodadiDopolnitelenPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
