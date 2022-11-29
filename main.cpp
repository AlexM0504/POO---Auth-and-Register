#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


class User{
private:

  string username;
  string password;
  string email;



public:
    User(string un, string pass, string em)
    {
        this->username = un;
        this->password = pass;
        this->email =em;
    }

    void writeFile(){

        fstream fileUser;
        fileUser.open("user.csv",ios::out | ios::app);

        fileUser<< username <<"," << password <<"|"<< email << "\n";


        fileUser.close();
    }

};



void Register()
{
        string username,parola,email;

        cout<<"Introduceti username:";
        cin>>username;
        cout<<"Introduceti parola:";
        cin>>parola;
        cout<<"Introduceti emailul:";
        cin>>email;

        User User1(username,parola,email);
        User1.writeFile();
}

int loginAdmin()
{
    cout<<"ADMIN LOGIN: \n";

    ifstream fileAdmin;
    fileAdmin.open("admin.csv");

    string usernameAdmin, passwordAdmin;

    cout<<"Enter username for admin:";
    cin>>usernameAdmin;
    cout<<"Enter password for admin:";
    cin>>passwordAdmin;

    string uAdmin, pAdmin;


    getline(fileAdmin, uAdmin ,',');
    getline(fileAdmin, pAdmin,',');

    if(uAdmin == usernameAdmin && pAdmin ==passwordAdmin) return true;
    else return false;

    fileAdmin.close();
}

 


int loginUser()
{
    ifstream myFileUser;
    myFileUser.open("user.csv");

    string username, password;

    cout<<"Enter username for user:";
    cin>>username;
    cout<<"Enter password for user:";
    cin>>password;

    string u,p;

    while(myFileUser.good())
    {
    getline(myFileUser, u ,',');
    getline(myFileUser, p ,'|');

    cout<< u << " aici pauza " << p << endl;
    cout<< username << " aici pauza " << password << endl;
   

    if(u == username && p == password ) 
    {
        return true;
       
    }
    else 
    {
        return false;
        
    }
      cout<< u << " aici pauza " << p << endl;

    }


    myFileUser.close();
    
}

int main() {

   int optiune;

   cout<<"Va rugam alegeti o optiune(introduceti cifra corespunzatoare)";
   cout<<" \n 0. ADMIN";
   cout<<"\n 1. USER LOGIN";
   cout<<"\n 2. REGISTER USER \n";
   cin>> optiune;

   switch(optiune)
   {
       case 0:
       {
           if(loginAdmin()) cout<<"Autentificare reusita";
           else cout<<"Parola sau username gresit";
           break;
       }
       case 1:
       {
           if(loginUser()) cout<<"Autentificare reusita";
           else cout<<"Autentificare nereusita";
           break;
       }
       case 2:
       {
           Register();
           break;
       }
   }

}
