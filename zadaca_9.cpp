#include <iostream>
#include <cstring>
#include <ctype.h>
using namespace std;

class Exception{
public:
    Exception()=default;
    void print(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud{
private:
    char type;
    int year;
public:
    Trud()=default;
    Trud(char type,int year):year(year),type(type){
    }

    char getType() const {
        return type;
    }

    int getYear() const {
        return year;
    }
    friend istream& operator>>(istream& is,Trud& ref){
        is>>ref.type>>ref.year;
        return is;
    }

};

class Student{
protected:
    char name[31];
    int index;
    int first_year;
    int *passed_ex;
    int num_passed;
public:
    Student()=default;
    Student(char name[],int index,int first_year,int passed_ex[],int num_passed):num_passed(num_passed),first_year(first_year),index(index){
        this->passed_ex=new int[num_passed];
        strcpy(this->name,name);
        for(int i=0;i<num_passed;i++){
            this->passed_ex[i]=passed_ex[i];
        }
    }
    Student(const Student& ref):num_passed(ref.num_passed),first_year(ref.first_year),index(ref.index){
        this->passed_ex=new int[num_passed];
        strcpy(this->name,ref.name);
        for(int i=0;i<num_passed;i++){
            this->passed_ex[i]=ref.passed_ex[i];
        }
    }

    virtual float rang() const{
        float avg=0;
        for(int i=0;i<num_passed;i++){
            avg+=passed_ex[i];
        }
        return avg/num_passed*1.0;
    }

    friend ostream& operator<<(ostream& os,const Student& ref){
        os<<ref.index<<" "<<ref.name<<" "<<ref.first_year<<" "<<ref.rang()<<endl;
        return os;
    }

    const char *getName() const {
        return name;
    }

    int getIndex() const {
        return index;
    }

    int getFirstYear() const {
        return first_year;
    }

    int *getPassedEx() const {
        return passed_ex;
    }

    int getNumPassed() const {
        return num_passed;
    }
};

class PhDStudent:public Student{
private:
    Trud* niza;
    int num_trud;
    static int conf_trud;
    static int spisanie_trud;
public:
    PhDStudent()=default;
    PhDStudent(char name[],int index,int first_year,int passed_ex[],int num_passed,Trud niza[],int num_trud):Student(name,index,first_year,passed_ex,num_passed),num_trud(num_trud){
        Trud *tmp=new Trud[num_trud];
        int j=0;
        for(int i=0;i<num_trud;i++){
            try {
                if (this->first_year > niza[i].getYear()) {
                    //num_trud--;
                    //cout<<i;
                    throw Exception();
                }else{
                    tmp[j] = niza[j];
                    j++;
                }
            }catch(Exception i){
                i.print();
            }
        }
        //cout<<j<<endl;
        num_trud=j;
        this->niza=new Trud[j];
        for(int i=0;i<j;i++){
            this->niza[i]=tmp[i];
        }
    }
    PhDStudent(const PhDStudent& ref):Student(ref),num_trud(ref.num_trud){
        this->niza=new Trud[ref.num_trud];
        for(int i=0;i<num_trud;i++){
            try {
                if (this->first_year > ref.niza[i].getYear()) {
                    throw Exception();
                }
                this->niza[i] = ref.niza[i];
            }catch(Exception i){
                i.print();
            }
        }
    }

    float rang() const override{
            int bodovi_trud=0;
            for(int i=0;i<num_trud;i++){
                //cout<<"here123 "<<niza->getType()<<endl;
                if(::toupper(niza[i].getType())=='C'){
                  // cout<<"here "<<bodovi_trud<<endl;
                    bodovi_trud+=conf_trud;
                }else if(toupper(niza[i].getType())=='J'){
                    //cout<<"Here2 "<<bodovi_trud<<endl;
                    bodovi_trud+=spisanie_trud;
                }
            }
            //cout<<Student::rang();
            return Student::rang()+bodovi_trud;
    }

    PhDStudent& operator +=(const Trud &ref){
        //cout<<this->first_year<<" "<<ref.getYear()<<endl;
        if(this->first_year>ref.getYear()){
            //cout<<"here";
            throw Exception();
            return *this;
        }
        Trud *tmp=new Trud[num_trud+1];
        int i=0;
        for(i=0;i<num_trud;i++){
            tmp[i]=niza[i];
        }
        if(num_trud>0)
            delete [] niza;
        tmp[i]=ref;
        num_trud++;
        niza=tmp;
        return *this;
    }

    static void setConfTrud(int confTrud);

    static void setSpisanieTrud(int spisanieTrud);
};


int PhDStudent::conf_trud=1;
int PhDStudent::spisanie_trud=3;

void PhDStudent::setConfTrud(int confTrud) {
    conf_trud = confTrud;
}

void PhDStudent::setSpisanieTrud(int spisanieTrud) {
    spisanie_trud = spisanieTrud;
}

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        try{
            for(int i=0;i<m;i++){
                if(niza[i]->getIndex()==indeks){
                    PhDStudent *tmp=dynamic_cast<PhDStudent*>(niza[i]);
                    if(tmp!=NULL){
                        *tmp+=t;
                    }else{
                        cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                    }
                }
            }
        }catch(Exception i){
            i.print();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        try{
            for(int i=0;i<m;i++){
                if(niza[i]->getIndex()==indeks){
                    PhDStudent *tmp=dynamic_cast<PhDStudent*>(niza[i]);
                    if(tmp!=NULL){
                        *tmp+=t;
                    }
                }
            }
        }catch(Exception i){
            i.print();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }

            PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
            cout << phd;

    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try{
            for(int i=0;i<m;i++){
                if(niza[i]->getIndex()==indeks){
                    PhDStudent *tmp=dynamic_cast<PhDStudent*>(niza[i]);
                    if(tmp!=NULL){
                        *tmp+=t;
                    }
                }
            }
        }catch(Exception i){
            i.print();
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setConfTrud(conf);
        PhDStudent::setSpisanieTrud(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}