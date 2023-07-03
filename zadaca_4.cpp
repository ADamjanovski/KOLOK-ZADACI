#include <iostream>
#include <cstring>
using namespace std;

enum Size{
    Mala,
    Golema,
    Familijarna,
};
class Pizza{
protected:
    char name[20];
    char ingredients[100];
    float base_price;
public:
    Pizza()=default;
    Pizza(char name[],char ingredients[],float price):base_price(price){
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
    }
    virtual float price() const =0;
};

class FlatPizza:public Pizza{
protected:
    Size type=Mala;
public:
    FlatPizza()=default;
    FlatPizza(char name[],char ingredients[],float price):Pizza(name,ingredients,price){}
    FlatPizza(char name[],char ingredients[],float price,Size s):Pizza(name,ingredients,price),type(s){}
    float price()const override{
        if(type==0)
            return base_price*1.1;
        else if(type==1)
            return base_price*1.3;
        else
            return base_price*1.5;
    }
    friend ostream& operator <<(ostream& os,const FlatPizza& ref){
        os<<ref.name<<": "<<ref.ingredients<<", ";
        if(ref.type==0){
            os<<"small ";
        }else if(ref.type==1){
            os<<"big ";
        }else if(ref.type==2){
            os<<"family ";
        }
        os<<"- "<<ref.price()<<endl;
        return os;
    }

    bool const operator <(const Pizza& ref){
        if(this->price()<ref.price())
            return true;
        return false;
    }
};

class FoldedPizza:public Pizza{
protected:
    bool WhiteFlour=true;
public:
   // FoldedPizza()=default;
    FoldedPizza(char name[],char ingredients[],float price):Pizza(name,ingredients,price){}
    FoldedPizza(const FoldedPizza& ref):Pizza(ref),WhiteFlour(ref.WhiteFlour){}

    float price() const override{
        if(WhiteFlour)
            return base_price*1.1;
        return base_price*1.3;
    }

    void setWhiteFlour(bool whiteWheat) {
        WhiteFlour = whiteWheat;
    }

    friend ostream& operator <<(ostream& os,const FoldedPizza& ref){
        os<<ref.name<<": "<<ref.ingredients<<", ";
        if(ref.WhiteFlour)
            os<<"wf ";
        else
            os<<"nwf ";
        os<<"- "<<ref.price()<<endl;
        return os;
    }
    bool const operator <(const Pizza& ref){
        if(this->price()<ref.price())
            return true;
        return false;
    }
};

void expensivePizza(Pizza ** pizzas,int n){
    Pizza* mostexpensive;
    int max;
    for(int i=0;i<n;i++){
        if(pizzas[i]->price()>max){
            max=pizzas[i]->price();
            mostexpensive=pizzas[i];
        }
    }
    cout<<mostexpensive;
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}

