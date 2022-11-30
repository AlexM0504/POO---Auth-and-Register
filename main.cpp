#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

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

        fileUser<< username <<"," << password <<","<< email << "\n";


        fileUser.close();
    }

};


class Trains{
private:
    string orasPlecare;
    string orasDestinatie;
    int oraPlecare;
    int oraDestinatie;
    int nrTren;

public: 
    Trains(int nrT, string op , string od, int orap, int orad )
    {
    this->orasPlecare = op;
    this->orasDestinatie = od;
    this->oraPlecare = orap;
    this->oraDestinatie = orad;
    this->nrTren = nrT;
    }
    
    void writeTrains(){
        fstream fileTrains;

        fileTrains.open("trains.csv",ios::out | ios::app);

        fileTrains <<nrTren<<","<< orasPlecare << ","<< orasDestinatie<< "," << oraPlecare << "," << oraDestinatie<<"\n";

        fileTrains.close();
    }

};


void afisareCursa(){

    fstream myfile;

    myfile.open("trains.csv",ios::in);

    cout<<"Introduceti locul de plecare:";
    string findCursa;

    cin>>findCursa;

    string line,word,cursa1;
    vector<string> row;


    while(!myfile.eof())
    {
        row.clear();
        getline(myfile,line);
        stringstream s(line);

        while(getline(s,word,','))
        {
            row.push_back(word);
        }
         cursa1 = row[1];

        if(cursa1 == findCursa)
        {
            cout<<row[0]<< " "<< row[1]<< " "<< row[2]<<" "<< row[3]<<" "<<row[4]<<"\n";
        }
       
    }


}

void adaugaCursa()
{
    string op,od;
    int orap, oradest, nrT;

    cout<<"Introduceti numarul trenului:";
    cin>> nrT;
    cout<<"Introduceti oras plecare:";
    cin>> op;
    cout<<"Introduceti oras destinatie: ";
    cin>> od;
    cout<<"Introduceti ora plecare:";
    cin>> orap;
    cout<<"Introduceti ora destinatie:";
    cin>>oradest;

    Trains train1(nrT,op,od,orap,oradest);
    train1.writeTrains();

}


void deleteCursa()
{
    fstream fin, fout;
    fin.open("trains.csv",ios::in);
    fout.open("trainsNew.csv",ios::out);

    int nr_tren,nrtren1,i,count =0 ;

    cout<<"Introduceti nr trenului pe care vreti sa il stergeti:";
    cin>> nr_tren;

    string line,word;
    vector<string> row;

    while(!fin.eof())
    {
        row.clear();
        getline(fin,line);
        stringstream s(line);

        while(getline(s,word,','))
        {
            row.push_back(word);
        }

        int row_size = row.size();

        nrtren1 = stoi(row[0]); //conversie char to int 

        if(nrtren1 != nr_tren ){
            if(!fin.eof()){
                for (i = 0; i < row_size-1 ; i++) {
                    fout<<row[i]<<",";
                }
                fout<< row[row_size-1] << "\n";
            }
        }
        else{
            count =1;
        }
        if(fin.eof()) break;
    }

    if(count ==1 ) cout<<"Cursa cu nr  \n"<<row[0]<<"a fost stearsa";
    else cout<<"Nu s-a putut gasi cursa cu nr "<< nr_tren ;

    fin.close();
    fout.close();

    remove("trains.csv");
    rename("trainsNew.csv","trains.csv");

}


bool isValid(const string& email)
{
  
    // Regular expression definition
    const regex pattern(
        "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  
    // Match the string pattern
    // with regular expression
    return regex_match(email, pattern);
}
  

void Register()
{
        string username,parola,email,parola2;

        cout<<"Introduceti username: ";
        cin>>username;
        cout<<"Introduceti parola: ";
        cin>>parola;
        cout<<"Reintroduceti parola: ";
        cin>>parola2;

        

        cout<<"Introduceti emailul: ";
        cin>>email;

        if(parola==parola2){
            bool ans = isValid(email);
            if(ans){
                User User1(username,parola,email);
                User1.writeFile();
                 }
            else cout<<"Email gresit!";
        }
        else {
            cout<<"Parolele nu sunt indentice";
        }
        
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

    string username,password;

    cout<<"Introduceti username: ";
    cin>>username;
    cout<<"Introduceti parola: ";
    cin>>password;
    
    int adevarat=0;


    if(myFileUser.is_open())
    {
        string line;
        while(getline(myFileUser,line))
        {
            stringstream ss(line);
            string token;
            vector <string> temp;
            while(getline(ss,token,','))
            {
                temp.push_back(token);
            }
    
           
            if(username == temp[0] && password == temp[1]) adevarat = 1;
            
        } 

        

        myFileUser.close();
    }

    if(adevarat) return true;
        else return false;
    
   

}

int main() {

   int optiune;

   cout<<"Va rugam alegeti o optiune(introduceti cifra corespunzatoare)";
   cout<<" \n 0. ADMIN";
   cout<<"\n 1. USER LOGIN";
   cout<<"\n 2. REGISTER USER \n";
   cout<<"Introduceti o varianta (0,1,2):";
   cin>> optiune;

   switch(optiune)
   {
       case 0:
       {
           if(loginAdmin()) {
               cout<<"Autentificare reusita";

               cout<<"\n ALEGETI OPTIUNI ADMIN:";

               cout<<"\n 1. Adaugare curse";
               cout<<"\n 2. Stergere curse \n";
               cout<<"Introduceti o varianta (1,2): ";

               int optiuneAdmin;
               cin>> optiuneAdmin;

               switch(optiuneAdmin)
               {
                   case 1:
                   {
                       adaugaCursa();
                       break;
                   }
                   case 2:
                   {
                        deleteCursa();
                        break;
                   }
               }
           }

           else cout<<"Parola sau username gresit";
           break;
       }
       case 1:
       {
           
           if(loginUser()) {
            cout<<"\n AUTENTIFICARE REUSITA \n";
            cout<<"\n ALEGETI OPTIUNI USER:";

            cout<<"\n 1. Afisare curse";
            cout<<"\n 2. Rezervare \n";
            cout<<"Introduceti o varianta (1,2): ";

            int optiuneUser;
            cin>>optiuneUser;

            switch(optiuneUser)
            {
                case 1:
                {
                    afisareCursa();
                }
                case 2:
                {
                    
                }
            }
           }
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
