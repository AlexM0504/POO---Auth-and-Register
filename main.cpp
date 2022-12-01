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
    int zi;
    int luna;
    int an;
    int NRCURSA;

public: 
    Trains(int z, int l , int a, string op , string od, int orap, int orad, int nrc)
    {
    this->zi = z;
    this->luna = l;
    this->an = a;
    this->orasPlecare = op;
    this->orasDestinatie = od;
    this->oraPlecare = orap;
    this->oraDestinatie = orad;
    this->NRCURSA = nrc;
    }
    
    void writeTrains(){
        fstream fileTrains;

        fileTrains.open("trains.csv",ios::out | ios::app);

        fileTrains <<zi<<","<< luna << ","<< an << "," << orasPlecare << "," << orasDestinatie<<","<<oraPlecare<<","<<oraDestinatie<<","<<NRCURSA<<"\n";

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

         cursa1 = row[3];

        if(cursa1 == findCursa)
        {
            cout<<row[0]<< "-"<< row[1]<< "-"<< row[2]<<"|| "<< row[3]<<" -> "<<row[4]<<"  ||  "<<row[5]<<"->"<<row[6]<<"|| NR CURSA:"<<row[7]<<"\n";
            
            
        }
        else {
            throw "Cursa nu a fost gasita";
       
        }
       
    }

    myfile.close();

}

void rezervareCursa()
{
    afisareCursa();


    fstream myfile;
    fstream fileTickets;

    fileTickets.open("bilete.csv",ios::out | ios::app);
    myfile.open("trains.csv",ios::in );

    string line1,word1,cursa1;
    vector<string> row1;

    int nrCursaRez;

    cout<<"Introduceti nr cursei pe care vreti sa o rezervati:  ";
    cin>>nrCursaRez;

    string nume,prenume;

    cout<<"Introduceti prenumele de rezervare:  ";
    
    cin>>prenume;

    cout<<"Introduceti numele de rezervare:  ";
    
    cin>>nume;
    
    int rezervare = 0;
    
    int nrcursadorita;


    while(!myfile.eof())
    {
        row1.clear();
        getline(myfile,line1);
        stringstream s1(line1);

        while(getline(s1,word1,','))
        {
            row1.push_back(word1);
        }

         nrcursadorita = stoi(row1[7]);

        if(nrcursadorita == nrCursaRez)
        {
            fileTickets<< nume <<" "<<prenume << " a rezervat un bilet pt cursa " << nrcursadorita <<"\n";
            rezervare = 1;
            break;
        }
    
       
       
    }
  
    if(rezervare)
    {
        cout<<"Rezervarea s-a facut cu succes";
    }
    else
    {
        cout<<"Cursa nu a fost gasita";
    }
    fileTickets.close();
    myfile.close();
}

void adaugaCursa()
{
    string op,od;
    int orap, oradest, ziua, luna ,an, nrc;

    cout<<"Introduceti ziua :";
    cin>> ziua;
    cout<<"Introduceti luna :";
    cin>> luna;
    cout<<"Introduceti an :";
    cin>> an;
    cout<<"Introduceti oras plecare:";
    cin>> op;
    cout<<"Introduceti oras destinatie: ";
    cin>> od;
    cout<<"Introduceti ora plecare:";
    cin>> orap;
    cout<<"Introduceti ora destinatie:";
    cin>>oradest;
    cout<<"Introduceti un nr de cursa:";
    cin>>nrc;

    fstream myfile;

    myfile.open("trains.csv",ios::in);

    int nrcursa1;
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

         nrcursa1 = stoi(row[7]);

        if(nrcursa1 == nrc)
        {
            cout<<"Exista deja o cursa cu numarul de cursa introdus. ("<<nrc<<")";
            break;
        }
        else {
             if( orap < oradest ){
            Trains train1(ziua,luna,an,op,od,orap,oradest,nrc);
             train1.writeTrains();
             break;
             if(myfile.eof()) break;
             }
        else {
        cout<<"Ora gresita";
        }
       
        }
       
    }
   

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

        nrtren1 = stoi(row[7]); //conversie char to int 

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

    if(count ==1 ) cout<<"Cursa cu nr  \n"<<row[7]<<"a fost stearsa";
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
        std::string username,parola,email,parola2;

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

        

       
    }

    if(adevarat) return true;
        else return false;
    
    myFileUser.close();

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
                    rezervareCursa();
                }
            }
           }
           else cout<<"User sau parola introduse gresit";
           break;
       }
       case 2:
       {
           Register();
           break;
       }
      
   }

}
