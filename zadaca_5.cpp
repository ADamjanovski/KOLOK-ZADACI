#include <iostream>
#include <cstring>
using namespace std;

enum typeC{
    standard,
    loyal,
    vip
};

class UserExistsException{
    char text[50];
public:
    UserExistsException()=default;
    UserExistsException(char * text){
        strcpy(this->text,text);
    }
    void print(){
        cout<<text;
    }
};
class Customer{
protected:
    char name[50];
    char email[50];
    typeC type;
    static int base_sale;
    int bought;
    static const int additional_sale=20;
public:
    Customer()=default;
    Customer(char  name[],char email[],typeC type,int bought):type(type),bought(bought){
        strcpy(this->name,name);
        strcpy(this->email,email);
    }
    Customer(const Customer & ref):type(ref.type),bought(ref.bought){
        strcpy(this->name,ref.name);
        strcpy(this->email,ref.email);
    }
    friend ostream& operator <<(ostream & os,const Customer& ref){
        os<<ref.name<<endl<<ref.email<<endl<<ref.bought<<endl;
        if(ref.type==0){
            os<<"standard"<<endl;
        }else if(ref.type==1){
            os<<"loyal "<<base_sale<<endl;
        }else{
            os<<"vip "<<additional_sale+base_sale<<endl;
        }
        return os;
    }

    void settypeC(typeC type);

    const char *getEmail() const;

    int getBought() const;

    typeC gettypeC() const;

    static void setDiscount1(int baseSale);
};

class FINKI_bookstore{
private:
    Customer* niza;
    int num_costumer=0;
public:
    FINKI_bookstore()=default;
    FINKI_bookstore& operator +=(const Customer& ref){
        if(num_costumer==0){
            niza=new Customer[num_costumer+1];
            niza[0]=ref;
            num_costumer++;
        }else if(num_costumer>0){
            int i;
            try {
                for ( i = 0; i < num_costumer; i++) {
                    if (strcmp(niza[i].getEmail(),ref.getEmail())==0){
                        throw UserExistsException("The user already exists in the list");
                    }
                }
                Customer *tmp=new Customer[num_costumer+1];
                for ( i = 0; i < num_costumer; i++) {
                    tmp[i]=niza[i];
                }
                tmp[i]=ref;
                delete [] niza;
                niza=tmp;
                num_costumer++;
            }catch(UserExistsException i){
                i.print();
            }
        }
    }
    void update(){
        for(int i=0;i<num_costumer;i++){
            if(niza[i].gettypeC()==0 && niza[i].getBought()>5){
                niza[i].settypeC((typeC) 1);
            }else if(niza[i].gettypeC()==1 && niza[i].getBought()>10){
                niza[i].settypeC((typeC) 2);
            }
        }
    }

    friend ostream& operator <<(ostream &os,const FINKI_bookstore& ref){
        for(int i=0;i<ref.num_costumer;i++){
            os<<ref.niza[i];
        }
        return os;
    }

    void setCustomers(Customer *niza,int n) {
        num_costumer=n;
        this->niza=new Customer[num_costumer];
        for(int i=0;i<n;i++){
            this->niza[i]=niza[i];
        }
    }
    ~FINKI_bookstore(){
        delete [] niza;
    }
};

int Customer::base_sale=10;

const char *Customer::getEmail() const {
    return email;
}

void Customer::settypeC(typeC type) {
    Customer::type = type;
}

typeC Customer::gettypeC() const {
    return type;
}

int Customer::getBought() const {
    return bought;
}

void Customer::setDiscount1(int baseSale) {
    base_sale = baseSale;
}

const int MAX=50;

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception!!!) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name,email,(typeC)tC,numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }
        fc.setCustomers(customers, n);
        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
