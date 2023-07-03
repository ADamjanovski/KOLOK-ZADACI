#include <iostream>
#include <cstring>
using namespace std;

class StudentKurs{
protected:
    char ime[30];
    int grade;
    bool daliUsno;

public:
    StudentKurs(char* ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->grade=finalenIspit;
        this->daliUsno=false;
    }
    //дополни ја класата
    StudentKurs(const StudentKurs& ref):grade(ref.grade){
        strcpy(this->ime,ref.ime);
        daliUsno=ref.daliUsno;
    }

    const char *getIme() const {
        return ime;
    }


    void setOcenka(int ocenka) {
        StudentKurs::grade = ocenka;
    }

    bool getDaliUsno() const {
        return daliUsno;
    }

    void setDaliUsno(bool daliUsno) {
        StudentKurs::daliUsno = daliUsno;
    }
    virtual int ocenka(){
        return grade;
    }
    friend ostream& operator <<(ostream& os, const StudentKurs& ref){
        os<<ref.ime<<" --- "<<ref.grade<<endl;
        return os;
    }
};

class StudentKursUsno :public StudentKurs{

public:
    StudentKursUsno()=default;
    StudentKursUsno(char name[],int test_grade): StudentKurs(name,test_grade){
        daliUsno=true;
    }
    int ocenka() override{
        return grade;
    }
    StudentKursUsno& operator +=(char grade[]){
        if(getDaliUsno()){
            if(strcmp(grade,"odlicen")==0){
                this->grade+=2;
            }else if(strcmp(grade,"dobro")==0){
                this->grade+=1;

            }else if(strcmp(grade,"losho")==0)
                this->grade-=1;
        }
        return *this;
        
    }
};



class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }

    //дополни ја класата
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        programiranje.postaviOpisnaOcenka(ime,opisna);
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
