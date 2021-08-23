/*Name: FS Miniproject
Author: Maithri Hebbar
Date:10/08/2021
*/
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
using namespace std;
COORD coord = {0, 0};
class pass
{
public:
    char p[20];
    void password(int x)
    {
       if(x==1234)
       {
           cout<<"\nEnter password(less than 10 characters)";
           cin.ignore();
           cin.getline(p,20);
           fstream wr;
           wr.open("pass.txt",ios::out);
           wr.write((char*)this,sizeof(pass));
           wr.close();
       }
       else
       {
           cout<<"\nCode Error";
       }
    }
};
pass obj1;
void gotoxy (int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void welcome_dance()
{
	system("color CC");
	int j,i,x,y;
	for(i=0;i<27;i++)
	{
		gotoxy(i,13);
		cout<<" ";
		cout<<"Glisten & Glean";
		Sleep(40);
	}
	for(j=67;j>44;j--)
	{
		gotoxy(j,13);
		cout<<" WELCOMES YOU";cout<<"            ";
		Sleep(40);
	}
	gotoxy(27,13);cout<<"Glisten & Glean";
	gotoxy(45,13);cout<<" WELCOMES YOU";
	for(int j=78;j>=0;j--)
	{
		gotoxy(j,20);cout<<"#";
		gotoxy(j,4);cout<<"V";
		Sleep(30);
	}
	gotoxy(56,23);cout<<"MAITHRI HEBBAR  4SF15IS049";
	gotoxy(56,24);cout<<"MICHEL          4SF15IS054";
	gotoxy(56,25);cout<<"RASHEEM ISMAIL  4SF15IS077";

	Sleep(2000);
}


class car
{
public:
    int car_no;
    char date[15];
    char date1[15];
    char name[30];
    char mob[15];
    char wash_type[20];
    char adress[50];
    void accept()
    {
        cin.ignore();
        cout<<"\nEnter date: ";
        cin.getline(date,15);
        cout<<"\nEnter full name: ";
        cin.getline(name,30);
        cout<<"\nEnter mobile number: ";
        cin>>mob;
        cin.ignore();
        cout<<"\nPlease type anyone from the list \n1. Handwashing\n2. Waterless Washing\n3. Rinseless Washing\n4. Automatic Washing\n ";
        cin.getline(wash_type,20);
        cout<<"\nEnter address: ";
        cin.getline(adress,50);
    }
    void display()
    {
         cout<<"\n----------------------------";
         cout<<"\nCar number       "<<car_no;
        cout<<"\nName              "<<name;
        cout<<"\nMobile number     "<<mob;
        cout<<"\nWash type         "<<wash_type;
        cout<<"\nBooking Date      "<<date;
        cout<<"\nAddress           "<<adress;
        cout<<"\n----------------------------";
    }
};
car obj;
int check(int r)
{
    int flag=1;
    fstream rd;
    rd.open("record.txt",ios::in);
    rd.seekg(0,ios::end);
    int n=rd.tellg();
    n=n/sizeof(obj);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        if(r==obj.car_no)
        {
            flag=0;
            break;
        }
    }
    return flag;
}
void alotroom()
{
    int r,c;
    cout<<"\nEnter car number [Enter Last 4 digits of your number plate]: ";
    cin>>r;
    c=check(r);
    if(c==0)
    {
        cout<<"\nSorry..!!!You have already booked with same Car Number";
        cout<<"\n----------------------------";
        cout<<"";
    }
    else
    {
        obj.car_no=r;
        obj.accept();
        fstream wr;
        wr.open("record.txt",ios::app);
        wr.write((char*)&obj,sizeof(obj));
    }
}
void roomstatus()
{
    char p1[20];
    fstream rdp;
    rdp.open("pass.txt",ios::in);
    rdp.read((char*)&obj1,sizeof(pass));
    cout<<"\nEnter password ";
    for(int i=0;i<strlen(obj1.p);i++)
    {
        p1[i]=getch();
        cout<<"*";
    }
    p1[strlen(obj1.p)]='\0';
    if(stricmp(p1,obj1.p)==0)
     {
      fstream rd;
      rd.open("record.txt",ios::in);
      rd.seekg(0,ios::end);
      int n=rd.tellg();
      n=n/sizeof(obj);
      rd.seekg(0,ios::beg);
      for(int i=1;i<=n;i++)
       {
        rd.read((char*)&obj,sizeof(obj));
        obj.display();
       }
     }
    else
     {
        cout<<"\nPassword Mismatch";
     }
}
void rstatus()
{
       fstream rd;
      rd.open("record.txt",ios::in);
      rd.seekg(0,ios::end);
      int n=rd.tellg();
      n=n/sizeof(obj);
      rd.seekg(0,ios::beg);
      for(int i=1;i<=n;i++)
       {
        rd.read((char*)&obj,sizeof(obj));
         cout<<"\n----------------------------";
        cout<<"\n CAR Number       "<<obj.car_no;
        cout<<"\n Name            "<<obj.name;
        cout<<"\n Mobile number   "<<obj.mob;
        cout<<"\n Wash Type       "<<obj.wash_type;
        cout<<"\n----------------------------";
       }
}
void edit()
 {
        int rno;
        cout<<"\nEnter car number: ";
        cin>>rno;
        fstream wr,rd;
        rd.open("record.txt",ios::in);
        wr.open("temp.txt",ios::out);
        rd.seekg(0,ios::end);
        int n=rd.tellg();
        n=n/sizeof(obj);
        rd.seekg(0,ios::beg);
        for(int i=1;i<=n;i++)
        {
            rd.read((char*)&obj,sizeof(obj));
            if (obj.car_no==rno)
            {
                cout<<"\nTo modify the booking details please enter the details below \n";
                cout<<"\nEnter car number: ";
                cin>>rno;
                obj.car_no=rno;
                obj.accept();
                wr.write((char*)&obj,sizeof(obj));
            }
            else
            {
                wr.write((char*)&obj,sizeof(obj));
            }
        }
        rd.close();
        wr.close();
        remove("record.txt");
        rename("temp.txt","record.txt");
 }
  void customerinfo()
    {


	int c,flag;
	cout<<"\n Enter Car no: ";
	cin>>c;
	 fstream rd;
        rd.open("record.txt",ios::in);
        rd.seekg(0,ios::end);
        int n=rd.tellg();
        n=n/sizeof(obj);
        rd.seekg(0,ios::beg);
	for (int i=1;i<=n;i++)
        {
             rd.read((char*)&obj,sizeof(obj));
		if(obj.car_no==c)
		{
			cout<<"\n Customer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Car no:        "<<obj.car_no;
			cout<<"\n Name:            "<<obj.name;
            cout<<"\n Wash Type:       "<<obj.wash_type;
			cout<<"\n Phone no:        "<<obj.mob;
			cout<<"\n----------------------------";
            cout<<"";
			flag=1;
			break;
		}
	}

	if(flag==0)
	{

		cout<<"\n Sorry Car number not found ....!!";
		cout<<"\n----------------------------";
        cout<<"";

	}
    }

void leaveroom()
{
    int rno;
    cout<<"\nEnter car number: ";
    cin>>rno;
    fstream rd,wr,nwr;
    rd.open("record.txt",ios::in);
    wr.open("temp.txt",ios::app);
    nwr.open("prevreco.txt",ios::app);
    rd.seekg(0,ios::end);
    int n=rd.tellg();
    n=n/sizeof(obj);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
        { rd.read((char*)&obj,sizeof(obj));
            if (obj.car_no==rno)
            {
                cin.ignore();
                cout<<"\nEnter Booking date: ";
                cin.getline(obj.date1,15);
                nwr.write((char*)&obj,sizeof(obj));
                cout<<"\nRecord Sucessfully deleted\n";
                cout<<"\n----------------------------";
                cout<<"\n";
                system("PAUSE");
            }
            else
            {
                wr.write((char*)&obj,sizeof(obj));

            }
        }
     rd.close();
     wr.close();
     remove("record.txt");
     rename("temp.txt","record.txt");
}
main()
{
 int e=1,x;
  welcome_dance();
    system("cls");
	cout<<"\n\t\t\t***************************************************";
	cout<<"\n\t\t\t*             CAR WASH MANAGEMENT PROJECT ";
	cout<<"\n\t\t\t***************************************************";
	cout<<"\n\n\n\n FILE STRUCTURE MINIPROJECT BY:";
	cout<<"\n\t\t Maithri Hebbar 4SF18IS049\n\t\t Michel 4SF18IS054\n\t\t Rasheem Ismail 4SF18IS077\n\n";
       cout<<"\t\t\t\t\t";
	system("pause");
	system("cls");
 while(e!=0)
 {
     cout<<"\n\t\tWELCOME TO CAR WASH MANAGEMENT PROJECT\n ";
     cout<<"\t\t_______________________________________ ";
     cout<<"\n\t\t1.Press 1 to book a Slot              ";
     cout<<"\n\t\t2.Press 2 to view all Slot booking status ";
     cout<<"\n\t\t3.Press 3 to edit the data            ";
     cout<<"\n\t\t4.Press 4 to delete the data       ";
     cout<<"\n\t\t5.Enter 0 to exit "   ;
     cout<<"\n\t\t6.To view Specific customer information(search)";
     cout<<"\n\t\t7.To view Complete Details of the Customer booking                  ";
     cout<<"\n\t\t______________________________________";
     cout<<"\nSelect your choice: ";
     cin>>x;
     switch(x)
     {
         case 1:
         {
             alotroom();
             break;
         }
         case 2:
         {
             rstatus();
             break;
         }
         case 3:
         {
             edit();
             break;
         }
         case 4:
         {
             leaveroom();
             break;
         }
          case 1212:
         {
             customerinfo();
             break;
         }
         case 1313:
         {
             roomstatus();
             break;
         }
         case 0:
         {
             e=0;
             break;
         }
         }
         }


     cout<<"\nThank you for choosing us,\nVisit us again !!!\n\n";
}

