#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<windows.h>

using namespace std;

void gotoxy(int x, int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

class view
{
	public:
		void login();
		void title();
		void welcome();
		void menu();
		void ex_it();
};

class Bus
{
	protected:
		string name;
		string bus_no;
		string from;
		string to;
		string departure_time;
		string arrival_time;
			
	public:
		Bus()
		{
			name = "";
			bus_no = "";
			from = "";
			to = "";
			departure_time = "";
			arrival_time = "";
		}
	
		void getdata();		
};

class passenger:public Bus
{
	private:
		char cnic[20];
		int seat_no;
		
	public:
		passenger()
		{
			seat_no = 0;
		}
		
		void getdata();
		
		void passenger_info();
};

class seat:public Bus
{	
	public:
		seat(){	}
		
		view v;
		
		void set_empty(string bus_no)
		{
			ofstream file;
			
			file.open(bus_no.c_str(),ios::app);
			
			for(int i=0;i<32;i++)
			{
				file << "Empty\n";
			}
			file.close();
		}
		
		void allot_seat(string bus_no,int seat_no,string passenger_name)
		{
			string b;
			int i;
			
			ifstream file1;
			
			file1.open(bus_no.c_str(),ios::in);
			
			ofstream file;
			
			file.open("temp.txt",ios::out);
			
			while(!file1.eof())
			{
				getline(file1,b);
				i++;
	
				if(i==seat_no)
				{
					file << passenger_name << endl;
				}
				else
				file << b << endl;
			}
			
			file.close();
			file1.close();
			
			remove(bus_no.c_str());
			rename("temp.txt",bus_no.c_str());
		}
		
		void show_seat()
		{
			int k=1;
			string b;
			char c;
			
			v.title();
			
			q:
				cout << "\n\n\n\t\t\t\t\t\t\t   Enter Bus No : ";
				cin >> bus_no;
	
				ifstream file5;
	
				file5.open(bus_no.c_str(),ios::in);
	
				if(!file5)
				{
					cout << "\n\t\t\t\t\t\t\t   * THIS BUS DOES NOT EXIST";
					file5.close();
					
					k:
					cout << "\n\n\n\t\t\t\t\t\t\t   Do You Want To Go Back To Menu (Y/N) : ";
					cin >> c;
			
					if(c=='Y' || c=='y')
					{
						system("cls");
						v.title();
						v.menu();
					}
			
					else if(c=='N' || c=='n')
					{
						goto q;
					}
			
					else
					{
						cout << "\n\t\t\t\t\t\t\t   * INVALID ENTRY";
						goto k;
					}
				}
				
				else
				{
					cout << "\n\n\n\n\n";
					
					for(int i=0;i<8;i++)
					{
						for(int j=0;j<4;j++)
						{
							getline(file5,b);
							cout << "\t" << k++ << ") " << b << "\t\t";
						}
						cout << endl << endl;
					}
					
					file5.close();
					
					cout << "\n\n\n\t\t\t\t\t\t\t   Press Any Key To Go Back To Menu";
					
					system("pause>nul");
					system("cls");
					v.title();
					v.menu();
				}
		}
}; 

class Bus_Info:public Bus
{
	public:
		Bus_Info()
		{}
		
		void info()
		{
			view v;
			v.title();
			
			ifstream filee;
			
			filee.open("Bus Information.txt",ios::in);
			
			if(filee)
			{
				while(!filee.eof())
				{
					filee >> bus_no >> name >> from >> to >> departure_time >> arrival_time;
					cout << "\n\n\n\n\n\t\t\t\t\t       ________________________________________________________________________";
					cout << "\n\t\t\t\t\t        BUS NO : " << bus_no << "\t  DRIVER'S NAME : " << name << "\t  FROM : " << from << "\n\n\n\t\t\t\t\t          TO : " << to << "\t  DEPARTURE TIME : " << departure_time << "\t  ARRIVAL TIME : " << arrival_time << endl;
					cout << "\t\t\t\t\t       ________________________________________________________________________";
				}
			}
			
			else
			{
				cout<< "\n\n\n\n\n\t\t\t\t\t\t\t\t * RECORD NOT FOUND";
			}
			
			filee.close();
			
			cout << "\n\n\n\n\n\t\t\t\t\t\t\t     Press Any Key To Go Back To Menu";
					
			system("pause>nul");
			system("cls");
			v.title();
			v.menu();
		}
};

void view::menu()
{
	char choice;
	int valid=1;
	
	Bus b;
	passenger p;
	Bus_Info bi;
	seat s;
	
	do
	{
		cout << "\n\n\n\t\t\t\t\t\t\t   PRESS 1 FOR BUS INSTALLATION";
		cout << "\n\n\n\t\t\t\t\t\t\t   PRESS 2 FOR SEAT RESERVATION";
		cout << "\n\n\n\t\t\t\t\t\t\t   PRESS 3 FOR SEAT MAP";
		cout << "\n\n\n\t\t\t\t\t\t\t   PRESS 4 FOR BUSES AVAILABLE";
		cout << "\n\n\n\t\t\t\t\t\t\t   PRESS 5 FOR PASSENGER INFORMATION";
		cout << "\n\n\n\t\t\t\t\t\t\t   PRESS 6 TO TERMINATE PROGRAM";
		
		cout << "\n\n\n\n\n\t\t\t\t\t\t\t   CHOOSE FROM 1 TO 5 : ";
		cin >> choice;
		
        switch(choice)
		{
			case '1':
				system("cls");
			    b.getdata();
				break;
			
			case '2':
	        	system("cls");
				p.getdata();
				break;  
					 
	        case '3':
	        	system("cls");
				s.show_seat();
				break;
				
			case '4':
				system("cls");
				bi.info();
				break;
				
	        case '5':
	        	system("cls");
	        	p.passenger_info();
				break;
				
			case '6':
	        	view::ex_it();
				break;
				
	        default:
	        	system("cls");	
				view::title();			
				printf("\n\n\t\t\t\t\t\t\t* OPPS! YOU HAVE ENTERED INVALID CHARACTER");
				valid=0;
				break;
				getch();
	    }
	} 
	while(valid==0);
}

void view::welcome()
{
	int k=14,l=34,n=14,d=34;
	
	system("Color 6");
	
	for(int i=1; i<=60; i++)
	{
		cout << "\e[?25l";
		Sleep(50);
		gotoxy(l,13);
		cout << "@",
		gotoxy(l,14);
		cout << "_";
		l++;
	}
	
	for(int m=1; m<12; m++)
	{
		cout << "\e[?25l";
		Sleep(50);
		gotoxy(33,k);
		cout << "|";
		gotoxy(32,k);
		cout << "@",
		k++;
	}
		
	for(int m=1; m<12; m++)
	{
		cout << "\e[?25l";
		Sleep(50);
		gotoxy(94,n);
		cout << "|";
		gotoxy(95,n);
		cout << "@",
		n++;
	}
	
	for(int p=1; p<=60; p++)
	{
		cout << "\e[?25l";
		Sleep(50);
		gotoxy(d,24);
		cout << "_";
		gotoxy(d,25);
		cout << "@",
		d++;
	}
		
	Sleep(1000);
	gotoxy(47,19);
	system("Color 6");
	cout << "WELCOME TO BUS RESERVATION SYSTEM\n\n\n\n";
	Sleep(500);
	gotoxy(100,30);
	cout << "D";
	Sleep(500);
	gotoxy(101,30);
	cout << "E";
	Sleep(500);
	gotoxy(102,30);
	cout << "V";
	Sleep(500);
	gotoxy(103,30);
	cout << "E";
	Sleep(500);
	gotoxy(104,30);
	cout << "L";
	Sleep(500);
	gotoxy(105,30);
	cout << "O";
	Sleep(500);
	gotoxy(106,30);
	cout << "P";
	Sleep(500);
	gotoxy(107,30);
	cout << "E";
	Sleep(500);
	gotoxy(108,30);
	cout << "D";
	Sleep(500);
	gotoxy(111,30);
	cout << "B";
	Sleep(500);
	gotoxy(112,30);
	cout << "Y";
	Sleep(500);
	gotoxy(114,30);
	cout << ":";
	Sleep(500);
	gotoxy(104,32);
	cout << "H";
	Sleep(500);
	gotoxy(105,32);
	cout << "A";
	Sleep(500);
	gotoxy(106,32);
	cout << "S";
	Sleep(500);
	gotoxy(107,32);
	cout << "S";
	Sleep(500);
	gotoxy(108,32);
	cout << "A";
	Sleep(500);
	gotoxy(109,32);
	cout << "N";
	Sleep(500);
	gotoxy(112,32);
	cout << "M";
	Sleep(500);
	gotoxy(113,32);
	cout << "U";
	Sleep(500);
	gotoxy(114,32);
	cout << "R";
	Sleep(500);
	gotoxy(115,32);
	cout << "T";
	Sleep(500);
	gotoxy(116,32);
	cout << "A";
	Sleep(500);
	gotoxy(117,32);
	cout << "Z";
	Sleep(500);
	gotoxy(118,32);
	cout << "A";
	Sleep(500);
	gotoxy(111,34);
	cout << "&";
	Sleep(500);
	gotoxy(105,36);
	cout << "D";
	Sleep(500);
	gotoxy(106,36);
	cout << "E";
	Sleep(500);
	gotoxy(107,36);
	cout << "H";
	Sleep(500);
	gotoxy(108,36);
	cout << "Y";
	Sleep(500);
	gotoxy(109,36);
	cout << "A";
	Sleep(500);
	gotoxy(112,36);
	cout << "K";
	Sleep(500);
	gotoxy(113,36);
	cout << "H";
	Sleep(500);
	gotoxy(114,36);
	cout << "U";
	Sleep(500);
	gotoxy(115,36);
	cout << "R";
	Sleep(500);
	gotoxy(116,36);
	cout << "R";
	Sleep(500);
	gotoxy(117,36);
	cout << "A";
	Sleep(500);
	gotoxy(118,36);
	cout << "I";
	Sleep(500);
	gotoxy(119,36);
	cout << "M";
}

void view::title()
{
	system("Color F0");
	cout << "\n\n\t\t\t\t\t\t    *****************************************************";
	cout << "\n\n\t\t\t\t\t\t                  BUS RESERVATION SYSTEM";
	cout << "\n\n\t\t\t\t\t\t    *****************************************************";
}

void view::login()
{
	int chances;
	string name;
	char ch;
	
    for(chances=1; chances<=3; chances++)
    {
    	string pass = "";
    	
    	cout << "\n\n\n\t\t\t\t\t\t\t    USERNAME : ";
    	cin >> name;
	    cout << "\n\n\t\t\t\t\t\t\t    PASSWORD : ";
	    ch=getch();
        
        while(ch != 13)
		{
			pass.push_back(ch);  //push_back() function is used to push elements into a vector from the back.
			cout << '*';
			ch = getch();
		}
        
    	if(name=="Bus" && pass=="123456")
        {
        	cout << "\n\n\n\t\t\t\t\t\t\t    Login Successful";
        	cout << "\n\n\t\t\t\t\t\t\t    Loading";
        	
        	for(int j=1;j<=5;j++)
        	{
        		cout << "\e[?25l";  //hide cursor
        		Sleep(500);
        		cout << ".";
			}
			break;
        }
	
        else
        {
        	if(chances==3)
            {
            	cout << "\n\n\n\t\t\t\t\t\t\t  You have crossed the limit.You can't Login";
            	view::ex_it();
            	break;
			}
			
        	system("cls");
        	view::title();
        	
        	cout << "\n\n\n\t\t\t\t\t\t\t   Incorrect Password OR Username Entered\n\n";
        	cout << "\t\t\t\t\t\t\t\t        TRY AGAIN!\n";
        }	
    }
}

void Bus::getdata()
{
	view v;
	v.title();
	
	x:
		cout << "\n\n\n\t\t\t\t\t\t\t   Enter Bus No : ";
		cin >> bus_no;
	
		ifstream file1;
	
		file1.open(bus_no.c_str(),ios::in);
	
		if(file1)
		{
			cout << "\n\t\t\t\t\t\t\t   * THIS BUS ALREADY EXISTS";
			file1.close();
			goto x;
		}
	
		else
		{
			file1.close();
			
			cout << "\n\n\t\t\t\t\t\t\t   Enter Driver's Name : ";
			cin >> name;
			cout << "\n\n\t\t\t\t\t\t\t   From : ";
			cin >> from;
			cout << "\n\n\t\t\t\t\t\t\t   To : ";
			cin >> to;
			cout << "\n\n\t\t\t\t\t\t\t   Departure Time : ";
			cin >> departure_time;
			cout << "\n\n\t\t\t\t\t\t\t   Arrival Time : ";
			cin >> arrival_time;
			
			ofstream file;
	
			file.open("Bus Information.txt",ios::app);
	
			file << endl << bus_no << "\t" << name << "\t" << from << "\t" << to << "\t" << departure_time << "\t" << arrival_time;
	
			file.close();
			
			cout << "\n\n\t\t\t\t\t\t\t   Data Storing";
					
			for(int j=1; j<=5; j++)
        	{
        		cout << "\e[?25l";
        		Sleep(500);  //sleep () function causes the program or the process in which it is called, to suspend its execution temporarily for a period of time in seconds specified by the function parameter.
        		cout << ".";
			}
					
			cout << "\n\n\t\t\t\t\t\t\t   Successfully Stored";
	
			seat s1;
	
			s1.set_empty(bus_no);	
			
			cout << "\n\n\n\t\t\t\t\t\t\t   Press Any Key To Go Back To Menu";
					
			system("pause>nul");  //to hold the user screen. 
			system("cls");  //Clearing the Screen
			v.title();
			v.menu();
		}
}

void passenger::getdata()
{
	view v;
	v.title();
	
	string sample;
	char c;
	
	y:
		cout << "\n\n\n\t\t\t\t\t\t\t   Enter Bus No : ";
		cin >> bus_no;
	
		ifstream file1;
	
		file1.open(bus_no.c_str(),ios::in);
	
		if(!file1)
		{
			cout << "\n\t\t\t\t\t\t\t   * THIS BUS DOES NOT EXIST";
			file1.close();
			
			j:
			cout << "\n\n\n\t\t\t\t\t\t\t   Do You Want To Go Back To Menu (Y/N) : ";
			cin >> c;
			
			if(c=='Y' || c=='y')
			{
				system("cls");
				v.title();
				v.menu();
			}
			
			else if(c=='N' || c=='n')
			{
				goto y;
			}
			
			else
			{
				cout << "\n\t\t\t\t\t\t\t   * INVALID ENTRY";
				goto j;
			}
		}
		
		else
		{
			file1.close();
			
			cout << "\n\n\t\t\t\t\t\t\t   Enter Passenger's Name : ";
			cin >> name;
			
			c:
				cout << "\n\n\t\t\t\t\t\t\t   Enter Passenger's CNIC NO : ";
				cin >> cnic;
			
				if(strlen(cnic)>13 || strlen(cnic)!=13)
    			{
    				cout << "\n\t\t\t\t\t\t\t   * INVALID NUMBER\n";
	    			goto c;
				}
			
			q:
				cout << "\n\n\t\t\t\t\t\t\t   Enter Seat No : ";
				cin >> seat_no;
				
				if(seat_no>32)
				{
					cout << "\n\t\t\t\t\t\t\t   * MAXIMUM 32 SEATS AVAILABLE" << endl;
					goto q;
				}
				
				int i=1;
				ifstream file2;
		
				file2.open(bus_no.c_str(),ios::in);
				
				while(!file2.eof())
				{
					file2 >> sample;
					
					if(i==seat_no && sample!="Empty")
					{
						cout << "\n\t\t\t\t\t\t\t   * ALREADY RESERVED" <<endl;
						goto q;
						break;
					}
					
					else
					{
						i++;	
					}
				}
				
				file2.close();
	
				ofstream file;
	
				file.open("Passenger Information.txt",ios::app);
	
				file << endl << bus_no << "\t" << name << "\t" << cnic << "\t" << seat_no;
	
				file.close();
	
				cout << "\n\n\t\t\t\t\t\t\t   Data Storing";
					
				for(int j=1; j<=5; j++)
        		{
        			cout << "\e[?25l";
        			Sleep(500);
        			cout << ".";
				}
					
				cout << "\n\n\t\t\t\t\t\t\t   Successfully Stored";
					
				seat s;
					
				s.allot_seat(bus_no,seat_no,name);
					
				cout << "\n\n\n\t\t\t\t\t\t\t   Press Any Key To Go Back To Menu";
					
				system("pause>nul");
				system("cls");
				v.title();
				v.menu();
		}
}

void passenger::passenger_info()
{
	view v;
	v.title();
		
	string n,b;
	int i=14,j=17,found=0;
		
	ifstream file3,file4;
			
	file3.open("Passenger Information.txt",ios::in);
		
	cout << "\n\n\t\t\t\t\t\t\t   Enter Passenger Name : ";
	cin >> n;
	
	if(file3)
	{
		while(!file3.eof())
		{
			file3 >> bus_no >> name >>  cnic >> seat_no;
			
			if(name==n)
			{
				found=1;
				file4.open("Bus Information.txt",ios::in);
			
				while(!file4.eof())
				{
					file4 >> b  >> name >> from >> to >> departure_time >> arrival_time;
					
					if(bus_no==b)
					{
						cout << "\n\n\n\n\t\t\t\t\t    __________________________________________________________________________________";
						gotoxy(48,i);
						cout << "NAME : " << n;
						gotoxy(68,i);
						cout << "CNIC : " << cnic;  
						gotoxy(92,i);
						cout << "SEAT NO : " << seat_no;
						gotoxy(107,i);
						cout << "BUS NO : " << bus_no;
						gotoxy(44,j);
						cout << "FROM : " << from;
						gotoxy(64,j);
						cout << "TO : " << to;
						gotoxy(80,j);
						cout << "DEPARTURE TIME : "	<< departure_time;	
						gotoxy(106,j);
						cout << "ARRIVAL TIME : " << arrival_time;			
						cout << "\n\t\t\t\t\t    __________________________________________________________________________________";
						i+=10;
						j+=10;
					}
				}
				
				file4.close();
			}
		}
		file3.close();
		
		if(found==0)
		{
			cout << "\n\n\n\t\t\t\t\t\t\t   * RECORD NOT FOUND";
		}
	}
	
	else
	{
		cout << "\n\n\n\t\t\t\t\t\t\t   * FILE DOES NOT EXIST";
	}
	
	cout << "\n\n\n\t\t\t\t\t\t\t   Press Any Key To Go Back To Menu";
					
	system("pause>nul");
	system("cls");
	v.title();
	v.menu();	
}

void view::ex_it()
{
	cout << "\n\n\n\t\t\t\t\t\t\t  THANKS FOR VISTING US";
    cout << "\n\n\n\t\t\t\t\t\t\t  PRESS ANY KEY TO TERMINATE PROGRAM...\n";
	exit(0);
}

int main()
{
	view v;
	v.welcome();
	system("pause>nul");
	system("cls");
	v.title();
	v.login();
	system("cls");
	v.title();
	v.menu();
	
	return 0;
}
