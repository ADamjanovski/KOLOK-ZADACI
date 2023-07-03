#include <iostream>
#include <cstring>
using namespace std;

class ExistingGame{
private:
    char msg[256];
public:
    ExistingGame()=default;
    ExistingGame(char msg[]){
        strcpy(this->msg,msg);
    }
    void message(){
        cout<<msg<<endl;
    }
};
class Game{
protected:
    char name[100];
    float price;
    bool bought_on_sale;
public:
    Game()=default;
    Game(char name[],float price, bool bought_on_sale):bought_on_sale(bought_on_sale),price(price){
        strcpy(this->name,name);
    }
    Game(const Game& ref):price(ref.price),bought_on_sale(ref.bought_on_sale){
        strcpy(this->name,ref.name);
    }

    bool operator ==(const Game& ref){
        if(strcmp(this->name,ref.name)==0){
            return true;
        }
        return false;
    }
    friend ostream& operator<<( ostream& os,const Game& ref){
        os<<"Game: "<<ref.name<<", regular price: $"<<ref.price;
        if(ref.bought_on_sale)
            os<<", bought on sale";
        return os;
    }

    friend istream& operator >>(istream & is, Game& ref){
        is.get();
        is.getline(ref.name,100);
        is >>ref.price>>ref.bought_on_sale;
        return is;
    }

    const char *getName() const {
        return name;
    }

    float getPrice() const {
        return price;
    }

    void setPrice(float price) {
        Game::price = price;
    }

    bool isBoughtOnSale() const {
        return bought_on_sale;
    }

    void setBoughtOnSale(bool boughtOnSale) {
        bought_on_sale = boughtOnSale;
    }
    virtual void none(){};
};

class SubscriptionGame:public Game{
private:
    float monthly_fee;
    int month_b,year_b;
public:
    SubscriptionGame()=default;
    SubscriptionGame(char name[],float price, bool bought_on_sale,float monthly_fee,int month_b,int year_b): Game(name,price,bought_on_sale),monthly_fee(monthly_fee),month_b(month_b),year_b(year_b){}
    SubscriptionGame(const SubscriptionGame& ref):Game(ref),month_b(ref.month_b),monthly_fee(ref.monthly_fee),year_b(ref.year_b){}
    friend ostream& operator<<( ostream& os,const SubscriptionGame& ref){
        os<<"Game: "<<ref.name<<", regular price: $"<<ref.price<<", ";
        if(ref.bought_on_sale)
            os<<"bought on sale, ";
        os<<"monthly fee: $"<<ref.monthly_fee<<", purchased: "<<ref.month_b<<"-"<<ref.year_b;
        return os;
    }
    friend istream& operator >>(istream & is, SubscriptionGame& ref){
        is.get();
        is.getline(ref.name,100);
        is >> ref.price>>ref.bought_on_sale;
        is>> ref.monthly_fee>>ref.month_b>>ref.year_b;
        return is;
    }
    void none() override{};
    float getMonthlyFee() const {
        return monthly_fee;
    }

    void setMonthlyFee(float monthlyFee) {
        monthly_fee = monthlyFee;
    }

    int getMonthB() const {
        return month_b;
    }

    void setMonthB(int monthB) {
        month_b = monthB;
    }

    int getYearB() const {
        return year_b;
    }

    void setYearB(int yearB) {
        year_b = yearB;
    }
};

class User{
private:
    char name[100];
    Game** niza;
    int num=0;
public:
    User()=default;
    User(char name[]){
        strcpy(this->name,name);
    }
    User(const User& ref){
        strcpy(this->name,ref.name);
    }
    User & operator +=(Game &ref){
        if(num==0){
            niza=new Game*[num+1];
            niza[0]=&ref;
            num++;
            return *this;
        }else if(num>0) {
                int i;
                for ( i = 0; i < num; i++) {
                    if (*niza[i] == ref) {
                        throw ExistingGame((char *) "The game is already in the collection");

                    }
                }
                Game **tmp=new Game*[num+1];
                for(i=0;i<num;i++){
                    tmp[i]=niza[i];
                }
                tmp[i]=&ref;
                delete [] niza;
                niza=tmp;
                num++;
                return *this;
        }
    }

    float total_spent() {
        int i,months;
        int money_spent=0;
        SubscriptionGame *tmp;
        for (i = 0; i < num; i++) {
            tmp=static_cast<SubscriptionGame*>(niza[i]);
            if(tmp==NULL){
                if(niza[i]->isBoughtOnSale()){
                    money_spent+=niza[i]->getPrice()*0.7;
                }
                money_spent+=niza[i]->getPrice();
            }else{
                if(tmp->getYearB()==2018){
                    months=5-tmp->getMonthB();
                }else{
                    if(tmp->getMonthB()==5){
                        months=11;
                    }else if(tmp->getMonthB()>5){
                        months=(12+5-tmp->getMonthB())+(2018-tmp->getYearB()-1)*12;
                    }else{
                        months=(5-tmp->getMonthB())+((2018-tmp->getYearB())*12);
                    }
                }
                if(tmp->isBoughtOnSale()){
                    money_spent+=(tmp->getPrice()*0.7+months*tmp->getMonthlyFee());
                }else{
                    money_spent+=(tmp->getPrice()+months*tmp->getMonthlyFee());
                }
            }
        }
        return money_spent;
    }

    friend ostream& operator <<(ostream& os, User& ref){
        os<<endl<<"User: "<<ref.name<<endl;
        SubscriptionGame *tmp=NULL;
        for(int i=0;i<ref.num;i++){
            tmp=dynamic_cast<SubscriptionGame*>(ref.niza[i]);
            if(tmp==NULL){
                os<<"- "<<*ref.niza[i]<<endl;
            }
            else{
                os<<"- "<<*tmp<<endl;
            }
        }
        cout<<endl;
        return os;
    }
};



int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
