#include <iostream>
#include <cstring>
using namespace std;

class Book{
protected:
    char ISBN[20];
    char title[50];
    char author[30];
    float price;
public:
    Book()=default;
    Book(char ISBN[],char title[],char author[],float price):price(price){
        strcpy(this->ISBN,ISBN);
        ::strcpy(this->title,title);
        strcpy(this->author,author);
    }
    Book(const Book& ref){
        price=ref.price;
        strcpy(this->ISBN,ref.ISBN);
        ::strcpy(this->title,ref.title);
        strcpy(this->author,ref.author);
    }
    virtual float bookPrice()=0;
    bool operator >(Book& ref){
        if(this->bookPrice()>ref.bookPrice())
            return true;
        return false;
    }
    friend ostream& operator <<(ostream& os, Book &ref){
        float price=ref.bookPrice();
        os<<ref.ISBN<<": "<<ref.title<<", "<<ref.author<<" "<<price<<endl;
        return os;
    };

    void setISBN(char ISBN[]){
        strcpy(this->ISBN,ISBN);
    }
    virtual  ~Book(){};
};

class OnlineBook:public Book{
    char *url;
    int MB;
public:
    OnlineBook()=default;
    OnlineBook(char ISBN[],char title[],char author[],float price,char url[],int MB):Book(ISBN,title,author,price),MB(MB){
        this->url=new char[strlen(url)+1];
        strcpy(this->url,url);
    }
    OnlineBook(const OnlineBook& ref):Book(ref),MB(ref.MB){
        this->url=new char[strlen(ref.url)+1];
        strcpy(this->url,ref.url);
    }

    OnlineBook & operator =(const OnlineBook& ref){
        if(this==&ref)
            return *this;
        price=ref.price;
        MB=ref.MB;
        strcpy(this->ISBN,ref.ISBN);
        ::strcpy(this->title,ref.title);
        strcpy(this->author,ref.author);
        this->url=new char[strlen(url)+1];
        strcpy(this->url,url);
        return *this;
    }

    float bookPrice() override{
        if(MB>20)
            return price*1.2;
        return price;
    }
    ~OnlineBook(){
        delete[] url;
    }
};

class PrintBook:public Book{
    bool avaliable;
    float weight;
public:
    PrintBook()=default;
    PrintBook(char ISBN[],char title[],char author[],float price,float weight,bool available):Book(ISBN,title,author,price),weight(weight),avaliable(available){}
    PrintBook(const PrintBook& ref):Book(ref),avaliable(ref.avaliable),weight(ref.weight){}

    PrintBook& operator=(const PrintBook& ref){
        if(this==&ref)
            return *this;
        price=ref.price;
        strcpy(this->ISBN,ref.ISBN);
        ::strcpy(this->title,ref.title);
        strcpy(this->author,ref.author);
        avaliable=ref.avaliable;
        weight=ref.weight;
        return *this;
    }
    float bookPrice() override{
        if(weight>0.7)
            return price*1.15;
        return price;
    }
    ~PrintBook(){};
};

void mostExpensiveBook (Book** books, int n){
    OnlineBook* pointer;
    cout<<"FINKI-Education"<<endl;
    int i=0,printed=0;
    float max_price=books[0]->bookPrice();
    pointer=dynamic_cast<OnlineBook*>(books[i]);
    if(pointer==0){
        printed++;
    }
    Book* max=books[0];
    for(i=1;i<n;i++){
        pointer=dynamic_cast<OnlineBook*>(books[i]);
        if(pointer==0){
            printed++;
        }
        if(books[i]->bookPrice()>max_price){
            max=books[i];
            max_price=books[i]->bookPrice();
        }
    }
    cout<<"Total number of online books: "<<n-printed<<endl;
    cout<<"Total number of print books: "<<printed<<endl;
    cout<<"The most expensive book is: "<<endl<<*max;
}



int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
