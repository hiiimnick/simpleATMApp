#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int authname, auxauthname[256], authmoney[256], input, aux, value, registerPIN, auxPIN, cnt;

void putInVector()
{
    ifstream fin("auth.txt");
    ifstream fin1("money.txt");
    for(int i=1;i<=255;i++)
    {
        fin>>auxauthname[i];
        fin1>>authmoney[i];
    }
    fin.close();
    fin1.close();
}

int checkPIN(int PIN)
{
    int auxPIN=PIN;
    int nr=0;
    while(PIN!=0)
    {
        PIN=PIN/10;
        nr++;
    }
    if(nr==4)
    {
        cnt=0;
        for(int i=1;i<=256;i++)
        {
            if(auxauthname[i]==auxPIN)
            {
                cout<<auxauthname[i]<<endl;
                cnt=1;
            }
        }
        if(cnt>0)
            return 0;
        else
            return 1;
    }

}

void updateMoney()
{
    ofstream fin1("money.txt");
    for(int i=1;i<=256;i++)
    {
        fin1<<authmoney[i];
        if(authmoney[i+1]==0)
            break;
        fin1<<endl;
    }
    fin1.close();
}

int AuthCheck(int &aux)
{
    aux=0;
    cout<<"Please enter your user: ";
    cin>>authname;
    for(int i=1;i<=255;i++)
    {
        if(auxauthname[i]==authname)
        {
            aux=i;
            return 1;
        }
    }
        return 0;
}

int main()
{
    cout<<"Hello! Welcome to our bank!"<<endl<<"Do you wish to log-in(1) or register(2)?"<<endl;
    cout<<"Input: ";
    cin>>input;
    putInVector();
    if(input==1)
    {
        system("CLS");
        if(AuthCheck(aux))
        {
            while(input>0)
            {
            system("CLS");
            input=0;
            cout<<"Your account is "<<authname<<"."<<endl;
            cout<<"Check your balance(1)"<<" "<<"Add money(2)"<<" "<<"Take money(3)"<<endl;
            cout<<"Input: ";
            cin>>input;
            if(input==1)
            {
                system("CLS");
                cout<<"Your balance is "<<authmoney[aux]<<" LEI."<<endl;
                cout<<"Do you wish to go back? Press Yes(1) or No(0): ";
                cin>>input;
                system("CLS");
            }
            if(input==2)
            {
                system("CLS");
                cout<<"How much money do you wish to add?: ";
                cin>>value;
                authmoney[aux]=authmoney[aux]+value;
                updateMoney();
                system("CLS");
                cout<<"You now have "<<authmoney[aux]<<" LEI."<<endl;
                cout<<"Do you wish to go back? Press Yes(1) or No(0): ";
                cin>>input;
                system("CLS");
            }
            if(input==3)
                {
                system("CLS");
                cout<<"How much money do you wish to take?: ";
                cin>>value;
                if((authmoney[aux]-value)<0)
                {
                    system("CLS");
                    cout<<"You do not have enough money! Please subtract a smaller amount."<<endl;
                    system("PAUSE");
                }
                else authmoney[aux]=authmoney[aux]-value;
                updateMoney();
                system("CLS");
                cout<<"You now have "<<authmoney[aux]<<" LEI."<<endl;
                cout<<"Do you wish to go back? Press Yes(1) or No(0): ";
                cin>>input;
                system("CLS");
            }
        }
        }
        else
        {
            cout<<"Incorrect PIN. Restart the app and check the PIN before input or register a new account."<<endl;
        }
    }
    if(input==2)
    {
        while(input>0)
        {
        cout<<"Enter the PIN(user) you wish to have(The PIN needs to be 4 digit, and composed of numbers): "<<endl;
        cin>>registerPIN;
        if(checkPIN(registerPIN))
        {
            cout<<"The PIN is correct and it is not in our database"<<endl<<"Do you wish to register it? Press Yes(1) or No(0): ";
            cin>>input;
            if(input==1)
            {
                ofstream fout;
                ofstream fout1;
                fout.open("auth.txt", ios_base::app);
                fout1.open("money.txt", ios_base::app);
                fout<<endl;
                fout1<<endl;
                fout<<registerPIN;
                fout1<<"1";
                input=0;
                fout.close();
                fout1.close();
            }
        }
        else
        {
            system("CLS");
            cout<<"The PIN is already taken. Please try another PIN."<<endl;
            system("PAUSE");
            system("CLS");
        }
        }
    }
    if(input==0)
    {
        system("CLS");
        cout<<"Thank you for using our bank, relaunch the app if you need to do anymore operations. We hope to see you again soon.";
    }
    return 0;
    }

