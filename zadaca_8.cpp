#include <iostream>
#include <cstring>
using namespace std;

class Koncert{
private:
    char name[20];
    char lokacija[20];
    static float sale;
    float price;
public:
    Koncert()=default;
    Koncert(char name[],char location[],float price):price(price){
        strcpy(this->name,name);
        strcpy(lokacija,location);
    }
    virtual float cena(){
        return price*sale;
    }

    const char *getNaziv() const {
        return name;
    }

    static void setSezonskiPopust(float sale);

    static float getSezonskiPopust();

    virtual ~Koncert(){};

    float getPrice() const;
};

class ElektronskiKoncert:public Koncert{
private:
    char *dj_name;
    float duration;
    bool day_party;
public:
    ElektronskiKoncert()=default;
    ElektronskiKoncert(char name[],char location[],float price,char dj_name[],float duration,bool day_party): Koncert(name,location,price),day_party(day_party),duration(duration){
        this->dj_name=new char(strlen(dj_name)+1);
        strcpy(this->dj_name,dj_name);
    }

    float cena() override{
        float cena=getPrice();
        if(duration>7){
            cena+=360;
        }else if(duration>5){
            cena+=150;
        }
        if(day_party)
            return (cena-50)*getSezonskiPopust();
        else
            return (cena+100)*getSezonskiPopust();
    }

};

void najskapKoncert(Koncert ** koncerti, int n) {
    float max = 0;
    Koncert *najskap;
    int brojac = 0;
    for (int i = 0; i < n; i++) {
        ElektronskiKoncert *tmp = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if (tmp != NULL) {
            if (tmp->cena() > max) {
                max = tmp->cena();
                najskap = tmp;
            }
            brojac++;
        } else {
            if (koncerti[i]->cena() > max) {
                max = koncerti[i]->cena();
                najskap = koncerti[i];
            }
        }
    }
        cout << "Najskap koncert: " << najskap->getNaziv() << " " << najskap->cena() << endl;
        cout << "Elektronski koncerti: " << brojac << " od vkupno " << n << endl;
}
    bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
        bool flag=false;
        if(elektronski){
            for(int i=0;i<n;i++){
                ElektronskiKoncert *tmp=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
                if(tmp!=NULL){
                    if(strcmp(tmp->getNaziv(),naziv)==0){
                        cout<<tmp->getNaziv()<<" "<<tmp->cena()<<endl;
                        flag=true;
                    }
                }
            }
        }else{
            for(int i=0;i<n;i++){
                if(strcmp(koncerti[i]->getNaziv(),naziv)==0){
                    cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                    flag=true;
                }
            }
        }
        if(flag)
            return true;
        return false;
    }

    float Koncert::sale=0.2;

    float Koncert::getSezonskiPopust() {
        return sale;
    }

    void Koncert::setSezonskiPopust(float sale) {
        Koncert::sale = 1-sale;
    }

float Koncert::getPrice() const {
    return price;
}


int main(){

        int tip,n,novaCena;
        char naziv[100], lokacija[100], imeDJ[40];
        bool dnevna;
        float cenaBilet, novPopust;
        float casovi;

        cin>>tip;
        if (tip==1){//Koncert
            cin>>naziv>>lokacija>>cenaBilet;
            Koncert k1(naziv,lokacija,cenaBilet);
            cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
            Koncert k1(naziv,lokacija,cenaBilet);
            cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
            cin>>elektronski;
            if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
            najskapKoncert(koncerti,4);
        }

        return 0;
    }
