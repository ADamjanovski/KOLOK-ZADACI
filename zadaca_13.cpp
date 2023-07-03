#include <iostream>
#include <cstring>
#include<cmath>
using namespace std;

class Image{
protected:
    char *name;
    char owner[50];
    int height,width;
public:
    Image(char name[]="untitled",char owner[]="unknown",int width=800,int height=800):width(width),height(height){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->owner,owner);
    }
    Image(const Image & ref):width(ref.width),height(ref.height){
        this->name=new char[strlen(ref.name)+1];
        strcpy(this->name,ref.name);
        strcpy(this->owner,ref.owner);
    }

    virtual int fileSize() const{
        return height*width*3;
    };
    friend ostream& operator<<(ostream& os,const Image& ref){
        os<<ref.name<<" "<<ref.owner<<" "<<ref.fileSize()<<endl;
    }
    bool operator >(const Image& ref){
        if(this->fileSize()>ref.fileSize())
            return true;
        return false;
    }
    ~Image(){
        delete [] name;
    }
};

class TransparentImage:public Image{
private:
    bool transparent;
public:
    TransparentImage(char name[]="untitled",char owner[]="unknown",int width=800,int height=800,bool transparent=true):Image(name,owner,width,height),transparent(transparent){}
    TransparentImage(const TransparentImage & ref): Image(ref),transparent(ref.transparent){}
    int fileSize() const override{
        if(!transparent)
            return width*height+(width*height)/8;
        return width*height*4;
    }
};

class Folder{
protected:
    char name[255];
    char owner[50];
    Image *niza[100];
    int n=0;
public:
    Folder(char name[]="user",char owner[]="unknown"){
        ::strcpy(this->name,name);
        strcpy(this->owner,owner);
    }
    Folder& operator +=( Image&ref){
        if(n<100){
            TransparentImage *tmp=dynamic_cast<TransparentImage*>(&ref);
            if(tmp!=NULL)
                niza[n]=tmp;
            else
                niza[n]=&ref;
            n++;
        }
        return *this;
    }

    friend ostream& operator<<(ostream&os,const Folder& ref){
        os<<ref.name<<" "<<ref.owner<<endl<<"--"<<endl;
        for(int i=0;i<ref.n;i++){
            os<<*ref.niza[i];
        }
        os<<"--"<<endl<<"Folder size: "<<ref.folderSize()<<endl;
        return os;
    }
    Image* operator[](int i){
        if(i<n)
            return niza[i];
        return NULL;
    }
    int folderSize() const{
        int max=0;
        for(int i=0;i<n;i++){
            max+=niza[i]->fileSize();
        }
        return max;
    }
    Image* getMaxFile(){
        Image * pointer=niza[0];
        int max=niza[0]->fileSize();
        for(int i=1;i<n;i++){
            if(niza[i]->fileSize()>max){
                pointer=niza[i];
                max=niza[i]->fileSize();
            }
        }
        return pointer;
    }
};

Folder& max_folder_size(Folder niza[],int n){
    Folder *pointer=&niza[0];
    int max=niza[0].folderSize();
    for(int i=1;i<n;i++){
        if(niza[i].folderSize()>max){
            max=niza[i].folderSize();
            pointer=&niza[i];
        }
    }
    return *pointer;
}


int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};

