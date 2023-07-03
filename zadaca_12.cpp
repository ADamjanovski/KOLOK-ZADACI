#include <iostream>
#include <cstring>
using namespace std;
class InvalidProductionDate{
public:
    InvalidProductionDate()=default;
    void print(){
        cout<<"Невалидна година на производство"<<endl;
    }
};
enum tip{
    smartphone,
    kompjuter
};
class Device{
protected:
    char model[100];
    static float base_clean;
    tip type;
    int year_made;
    float additional_clean=0;
public:
    Device()=default;
    Device(char model[],tip type,int year_made):year_made(year_made),type(type){
        strcpy(this->model,model);
        if(type==1){
            additional_clean+=2;
        }
        if(year_made>2015)
            additional_clean+=2;
    }
    friend ostream& operator<<(ostream& os,const Device & ref){
        os<<ref.model<<endl;
        float time=ref.base_clean+ref.additional_clean;
        if(ref.type==1){
            os<<"Laptop "<<time<<endl;
        }else{
            os<<"Mobilen "<<time<<endl;
        }
        return os;
    }

    int getYearMade() const {
        return year_made;
    }

    static void setPocetniCasovi(float baseClean) {
        base_clean = baseClean;
    }
};

class MobileServis{
protected:
    char address[100];
    Device *niza;
    int num_devices=0;
public:
    MobileServis()=default;
    MobileServis(char address[]){
        strcpy(this->address,address);
    }
    MobileServis(const MobileServis& ref){
        if(num_devices>0)
            delete [ ] niza;
        num_devices=ref.num_devices;
        strcpy(this->address,ref.address);
        niza=new Device[num_devices];
        for(int i=0;i<num_devices;i++){
            niza[i]=ref.niza[i];
        }

    }
    MobileServis & operator +=(const Device& device){
        if(device.getYearMade()>2019 || device.getYearMade()<2000)
            throw InvalidProductionDate();
        Device *tmp=new Device[num_devices+1];
        int i;
        for( i=0;i<num_devices;i++){
            tmp[i]=niza[i];
        }
        tmp[i]=device;
        if(num_devices>0)
            delete [] niza;
        num_devices++;
        niza=tmp;
        return *this;
    }
   void pecatiCasovi(){
        cout<<"Ime: "<<address<<endl;
        for(int i=0;i<num_devices;i++){
            cout<<niza[i];
        }
    }

};

float Device::base_clean=1;
int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;

            }catch (InvalidProductionDate i){
                i.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;

            }catch (InvalidProductionDate i){
                i.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;

            }catch (InvalidProductionDate i){
                i.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;

            }catch (InvalidProductionDate i){
                i.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;

            }catch (InvalidProductionDate i){
                i.print();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

