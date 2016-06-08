/*	Author:		Andrew P
	Program:	CS11 - 34025 Final Project
	Date:		May 21, 2010
	Descri:		menu driven program collects employee data, sorts, calculates, and prints- see README.TXT for further details
*/
//***********************************************************************************************************************************************
// LIBRARIES
//***********************************************************************************************************************************************

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cctype>
#include <windows.h> 
#include <conio.h> 
#include <time.h>

using namespace std;

//***********************************************************************************************************************************************
// PROTYPES			-		DEFINITIONS CAN BE FOUND AT FUNCTIONS
//***********************************************************************************************************************************************

void gotoxy			(int,int); 
void header			();
void login			();
void accessLog		(string, int);
void mainMenu		(int&);
void displayMenu	(int&);
void searchMenu		(int&);
void sortMenu		(int&);
double getTax		();
void getFile		(ifstream&);
void makeFile		(ofstream&);

void readRecords	(int&, 
					vector<string>&, 
					vector<string>&, 
					vector<char>&, 
					vector<int>&, 
					vector<string>&, 
					vector<int>&, 
					vector<double>&, 
					vector<double>&, 
					vector<double>&);

void errorLog		(string, int);
void dataCheck		(int);

void displayRecords	(int, vector<string>, 
					vector<string>, 
					vector<char>, 
					vector<int>, 
					vector<string>, 
					vector<int>, 
					vector<double>, 
					vector<double>, 
					vector<double>);

void saveRecords	(int, vector<string>, 
					vector<string>, 
					vector<char>, 
					vector<int>, 
					vector<string>, 
					vector<int>, 
					vector<double>, 
					vector<double>, 
					vector<double>);

int findLowest	(const int, const vector<double>);
int findHighest	(const int, const vector<double>);
int searchName		(const int, const vector<string>);
int searchID		(const int, const vector<int>);

void displayResult	(int, vector<string>, 
					vector<string>, 
					vector<char>, 
					vector<int>, 
					vector<string>, 
					vector<int>, 
					vector<double>, 
					vector<double>, 
					vector<double>);

void sortLast		(int, 
					vector<string>&, 
					vector<string>&, 
					vector<char>&, 
					vector<int>&, 
					vector<string>&, 
					vector<int>&, 
					vector<double>&, 
					vector<double>&, 
					vector<double>&);

void sortID			(int, vector<string>&, 
					vector<string>&, 
					vector<char>&, 
					vector<int>&, 
					vector<string>&, 
					vector<int>&, 
					vector<double>&, 
					vector<double>&, 
					vector<double>&);

void findTotals		(const int, const vector<double>, const vector<double>);
void goodBye		();

//***********************************************************************************************************************************************
// MAIN -   PRIMARY CONTROL THRU MENUS
//***********************************************************************************************************************************************

int main()
{

//***********************************************************************************************************************************************
// Variables
//***********************************************************************************************************************************************

//vector length and highlight
	int size		= int();
	int index		= int();

//records
	vector<string> fName(size);
	vector<string> lName(size);
	vector<char> initial(size);
	vector<int> employeeID(size);
	vector<string> state(size);
	vector<int> zip(size);
	vector<double> hours(size);
	vector<double> rate(size);
	vector<double> net(size);

//menu selection
	int select		= int();
	int display		= int();
	int search		= int();
	int sort		= int();

//***********************************************************************************************************************************************
// Begin Function
//***********************************************************************************************************************************************

	header();					//DISPLAYS PROGRAM NAME

	gotoxy(25,22); 
	cout << "Please view README.txt located in program directory\n\n"; 
								//ADD DISPLAY README OPTION

	login();					//RUN LOGIN WITH ENCRIPTION

	while (true)				//THIS LOOP KEEPS YOU IN MAIN MENU
	{

	mainMenu(select);			//TO MAIN MENU DISPLAY

	if (select == 1)			//OPTION IMPORT FILES
		{
			readRecords(size, fName, lName, initial, employeeID, state, zip, hours, rate, net);
		}
		else if (select == 2)	//OPTION DISPLAY RECORDS
		{
			while (true)
			{
				displayMenu(display);
				 
				if (display == 1)
				{
					index = findLowest(size, net);
					displayResult(index, fName, lName, initial, employeeID, state, zip, hours, rate, net); 
				}
				else if (display == 2)
				{
					index = findHighest(size, net);
					displayResult(index, fName, lName, initial, employeeID, state, zip, hours, rate, net); 
				}
				else if (display == 3)
				{
					findTotals(size, hours, net);
				}
				else if (display == 4)
				{
					displayRecords(size, fName, lName, initial, employeeID, state, zip, hours, rate, net);
				}
				else if (display == 5)
				{
					break;
				}
				else
				{
					goodBye();
				}
			}
			
		}
		else if (select == 3)	//OPTION SEARCH RECORDS 
		{
			while (true)
			{
				searchMenu(search);
				 
				if (search == 1)
				{
					index = searchName(size, lName);
					displayResult(index, fName, lName, initial, employeeID, state, zip, hours, rate, net); 
				}
				else if (search == 2)
				{
					index = searchID(size, employeeID);
					displayResult(index, fName, lName, initial, employeeID, state, zip, hours, rate, net); 
				}
				else if (search == 3)
				{
					break;
				}
				else
				{
					goodBye();
				}
			}
		}
		else if (select == 4)	//OPTION SORT RECORDS
		{
			while (true)
			{
				sortMenu(sort);
				 
				if (sort == 1)
				{
					sortLast(size, fName, lName, initial, employeeID, state, zip, hours, rate, net);
				}
				else if (sort == 2)
				{
					sortID(size, fName, lName, initial, employeeID, state, zip, hours, rate, net);
				}
				else if (sort == 3)
				{
					break;
				}
				else
				{
					goodBye();
				}
			}			
		}
		else if (select == 5)	//OPTION PRINT/SAVE RECORDS
		{
			saveRecords(size, fName, lName, initial, employeeID, state, zip, hours, rate, net);
		}
		else					//EXIT PROGRAM
		{
			goodBye();
		}
	}
	return 0;
}

//***********************************************************************************************************************************************
// FUNCTIONS  - SEE DEFINITIONS
//***********************************************************************************************************************************************
//
//
//***********************************************************************************************************************************************
// GOTOXY  - ALLOWS CURSOR OUT MANIPULATION 
//***********************************************************************************************************************************************
void gotoxy			(int x,int y) 
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y }; 

	SetConsoleCursorPosition( hStdout, position );
}
//***********************************************************************************************************************************************
// HEADER  - DISPLAYS PROGRAM NAME FOR INSTITUTION, HEADS LOGIN SCREEN
//***********************************************************************************************************************************************
void header			()
{ 
	cout << "\t\t\t**********************************\n"
		 << "\t\t\t*  Employee Record System (ERS)  *\n"
		 << "\t\t\t*  Long Beach City College LBCC  *\n"
		 << "\t\t\t*     4901 East Carson Street    *\n"
		 << "\t\t\t*      Long Beach, CA 90808      *\n"
		 << "\t\t\t**********************************\n"
		 << endl;
}
///***********************************************************************************************************************************************
// LOGIN  - READS USER DIRECTORY, DECRYPTS PASSWORDS, ALLOWS/DENIES USER ACCESS TO MENUS 
//***********************************************************************************************************************************************
void login			()
{
	int list	= int();
	int y		= 9;
	char dummy[9];
	char match[9];
	string fileword = string();
	string userName = string();
	vector<string> users;
	vector<string> admit;

	string mark = string();
	
	bool flag = true;
	bool loop = true;
	bool hit = false;

	int counter = int();

	ifstream privy;
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	privy.open("G:\\ERS\\userDir.txt");
	//privy.open("C:\\Users\\Alias\\Desktop\\CS_11\\Final\\userDir.txt");

	while(!privy.eof())
		do 
		{
		privy >> userName;						
			if (privy.eof() || privy.fail())
			{
				loop = false;
			}
			else
			{
				users.push_back(userName);
			}
		
		privy >> fileword;						
			if (privy.eof() || privy.fail())
			{
				privy.clear();
				privy.ignore(1000, '\n');
				loop = false;
			}
			else
			{
				admit.push_back(fileword);
				list++;					
			}
		}
		while (loop);


	privy.close();
	

	while(counter<3 && flag == true )
	{
		char password[9];
		userName.clear();
		SetConsoleTextAttribute(hConsole, 6);//gold
		gotoxy(25, 10); cout << "User Name: ";
		gotoxy(25, 11); cout << " --------- ";
		gotoxy(25, 12); cout << "|         |";
		gotoxy(25, 13); cout << " --------- ";
		gotoxy(45, 10); cout << "Password: ";
		gotoxy(45, 11); cout << " --------- ";
		gotoxy(45, 12); cout << "|         |";
		gotoxy(45, 13); cout << " --------- ";
		gotoxy(26, 12);
		cin >> userName;
		

		for (int i= 0; i<list; ++i)
		{
				if(userName == users[i])
				{
					strcpy_s(match, admit[i].c_str());
					y = strlen(match);
					gotoxy(46, 12);
										
					for (int j=0; j < y; j++)
					{
						password[j] = _getch();
						password[j] = password[j] + 99 + j;
						cout << '*';
					}
					password[y] = '\0';
					hit = true;
				}
				
		}
		if(!hit)
			{
				gotoxy(46, 12);
				for (int j=0; j < 3; j++)
				{
					dummy[j] = _getch();
					cout << '*';
				}
			}

		if (strcmp(password, match)==0)
		{
			mark = userName + " succesfully logged in ";
			errorLog(mark, counter);
			accessLog(mark, counter);
			SetConsoleTextAttribute(hConsole, 10);//green
			gotoxy(25, 14); cout << "Login successful...          " << endl;
			gotoxy(25, 15); cout << "                                  " << endl;
			gotoxy(25, 16);	system("pause");
			flag = false;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 14);//yellow
			if (counter == 1)SetConsoleTextAttribute(hConsole, 12);//red
			if (counter == 2)SetConsoleTextAttribute(hConsole, 4);//dark red
			gotoxy(25, 14); cout << "Invalid User-Name or password" << endl;
			gotoxy(25, 15); cout << "Try entering the information again" << endl;
			gotoxy(25, 16); cout << ++counter << " of 3 attempts remaining!" << endl;
		}
	}

	if (flag == true)
	{
		mark = userName + " was denied access to the ERS ";
		errorLog(mark, counter);
		SetConsoleTextAttribute(hConsole, 12);//red
		cout << "\nPermission to access the system denied!" << endl;
		cout << "Please see your administrator for user-name and password help." << endl;
		cout << "\n\nProgram will terminate!" << endl;
		exit(1);
	}
}
//***********************************************************************************************************************************************
// ACCESS LOG  - RECORDS ACCESS PERMISSIONS AND USE
//***********************************************************************************************************************************************
void accessLog		(string access, int index)
{
	ofstream printaccess;
	time_t currentTime;
	time(&currentTime);
	//extern string user;

	printaccess.open("G:\\ERS\\logs\\accessLog.txt",ios::app);
	//printaccess.open("C:\\Users\\Alias\\Desktop\\CS_11\\Final\\logs\\accessLog.txt",ios::app);
	printaccess << asctime(localtime(&currentTime)) << "\t" << " - " << access <<  index+1 << endl;
	printaccess.close();
}
//***********************************************************************************************************************************************
// MAIN MENU  - BASE PROGRAM OPTIONS MENU
//***********************************************************************************************************************************************
void mainMenu		(int& select)
{
	system("cls");
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 7);//default
	cout << "\n\t\t M A I N   M E N U\t- Description"
		 << "\n\t\t===================\n";
	SetConsoleTextAttribute(hConsole, 6);//gold
	cout << "\n\t\t  1. IMPORT\t\t- loads file to be processed";
	SetConsoleTextAttribute(hConsole, 9);//blue
	cout << "\n\t\t  2. DISPLAY\t\t- shows records from import file";
	SetConsoleTextAttribute(hConsole, 10);//green
	cout << "\n\t\t  3. SEARCH\t\t- searches records per user";
	SetConsoleTextAttribute(hConsole, 11);//aqua
	cout << "\n\t\t  4. SORT\t\t- sorts records per user";
	SetConsoleTextAttribute(hConsole, 13);//pink
	cout << "\n\t\t  5. PRINT\t\t- prints file to user's desktop";
	SetConsoleTextAttribute(hConsole, 14);//yellow
	cout << "\n\t\t  6. EXIT\t\t- exits program";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "\n\t\t-------------------"
		<< endl;

		cout << "\n\n\tPlease enter your selection: ";
		cin >> select;
		if (cin.fail())			//then quit
		{
			cin.clear();
			cin.ignore(1000, '\n');
			select = 6;			//force quit
		}
}
//***********************************************************************************************************************************************
// DISPLAY MENU  - OPTIONS MENU TO DISPLAY RECORDS
//***********************************************************************************************************************************************
void displayMenu	(int& display)
{
	system("cls");
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "\n\t\t   D I S P L A Y "
		<< "\n\t\t===================\n";
	SetConsoleTextAttribute(hConsole, 9);
	cout << "\n\t\t  1. LOWEST SALARY"
		 << "\n\t\t  2. HIGHEST SALARY"
		 << "\n\t\t  3. TOTAL HOURS & INCOME"
		 << "\n\t\t  4. ALL RECORDS"
		 << "\n\t\t  5. RETURN to MAIN MENU"
		 << "\n\t\t  6. EXIT";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "\n\t\t-------------------"
		<< endl;

		cout << "\n\n\tPlease enter your selection: ";
		cin >> display;
		if (cin.fail())			//then quit
		{
			cin.clear();
			cin.ignore(1000, '\n');
			display = 5;			//force quit
		}
}
//***********************************************************************************************************************************************
// SEARCH MENU  - OPTIONS MENU TO SEARCH RECORDS
//***********************************************************************************************************************************************
void searchMenu		(int& search)
{
	system("cls");
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	

	cout << "\n\t\t    S E A R C H  "
		 << "\n\t\t===================\n";
	SetConsoleTextAttribute(hConsole, 10);
	cout << "\n\t\t  1. by LAST NAME"
		 << "\n\t\t  2. by ID"
		 << "\n\t\t  3. RETURN to MAIN MENU"
		 << "\n\t\t  4. EXIT";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "\n\t\t-------------------"
		<< endl;

		cout << "\n\n\tPlease enter your selection: ";
		cin >> search;
		if (cin.fail())			//then quit
		{
			cin.clear();
			cin.ignore(1000, '\n');
			search = 3;			//force quit
		}
}
//***********************************************************************************************************************************************
// SORT MENU  - OPTIONS MENU TO SORT RECORDS
//***********************************************************************************************************************************************
void sortMenu		(int& sort)
{
	system("cls");
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	

	cout << "\n\t\t      S O R T   "
		 << "\n\t\t===================\n";
	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n\t\t  1. by LAST NAME"
		 << "\n\t\t  2. by ID"
		 << "\n\t\t  3. RETURN to MAIN MENU"
		 << "\n\t\t  4. EXIT";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "\n\t\t-------------------"
		<< endl;

		cout << "\n\n\tPlease enter your selection: ";
		cin >> sort;
		if (cin.fail())			//then quit
		{
			cin.clear();
			cin.ignore(1000, '\n');
			sort = 3;			//force quit
		}
}
//***********************************************************************************************************************************************
// GET TAX  - LOAD TAX RATE PER DOCUMENT
//***********************************************************************************************************************************************
double getTax()
{
	double tax = double();
	string mark = string();

	ifstream getTax;

	getTax.open("G:\\ERS\\tax.txt");
	//getTax.open("C:\\Users\\Alias\\Desktop\\CS_11\\Final\\tax.txt");

	if (!getTax)							//if no file then goes to the failed state
	{
		cout << "\nTax file does not exist or is not located in corresponding directory" << endl;
		getTax.clear();
		mark = " Missing TAX document. ";
		errorLog(mark, -1);
		tax = 0;
	}
	else
	{
		getTax.peek();

		if(getTax.eof())
		{
			cout << "\nTax file is EMPTY, tax will not be deducted from net pay." << endl;
			tax = 0;
			mark = "Tax document empty file ";
			errorLog(mark, -1);
		}
		else
		{
			getTax >> tax;

		if (getTax.fail() || tax >= 100 || tax < 0)
		{
			cout << "\nTax data is CORRUPT, tax will not be deducted from net pay. " << endl;
			getTax.clear();
			tax = 0;
			mark = " Tax DATA fail! ";
			errorLog(mark, -1);
		}
			tax = tax/100;
		}
	}

	getTax.close();

	return tax;	
}
//***********************************************************************************************************************************************
// GET FILE  - FILE REQUEST FOR READ RECORDS
//***********************************************************************************************************************************************
void getFile		(ifstream& fin)
{
	string fileName = string();
	bool error = false;
	
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		do
		{
			SetConsoleTextAttribute(hConsole, 7);
			cout << "\nEnter input filename: ";
			cin >> fileName;
//CHANGE DIRECTORY
			fileName = "G:\\ERS\\" + fileName + ".txt";
			//fileName = "C:\\Users\\Alias\\Desktop\\" + fileName + ".txt";

			
			fin.open(fileName.c_str());
					if (!fin)
					{
						SetConsoleTextAttribute(hConsole, 12);
						system("cls");
						errorLog("Attempt to open " + fileName + " FAIL ", 80);
						cout << "Cannot Open the input file.\nPlease try again..." << endl;
						fin.clear();
						error = true;
					}

					else
					{
						SetConsoleTextAttribute(hConsole, 10);
						cout << "\nFANTASTIC! Your file was found.\n\n" << fileName << endl;
						SetConsoleTextAttribute(hConsole, 7);
						accessLog(fileName, 0);
						
						error = false;
					}
		}
		while(error);
	
}
void makeFile		(ofstream& fout)
{
	string fileName = string();

			cout << "\nEnter input filename: ";
			cin >> fileName;
//CHANGE DIRECTORY
			fileName = "G:\\ERS\\print\\" + fileName + ".txt";
			//fileName = "C:\\Users\\Alias\\Desktop\\CS_11\\Final\\print\\" + fileName + ".txt";
			fout.open(fileName.c_str());
}
//***********************************************************************************************************************************************
// READ RECORDS  - LOADS RECORDS FROM TXT (see - GET FILE) INTO VECTORS FOR PROCESSING
//***********************************************************************************************************************************************
void readRecords	(int& size, 
					vector<string>& fname, 
					vector<string>& lname, 
					vector<char>& initial, 
					vector<int>& employeeID, 
					vector<string>& state, 
					vector<int>& zip, 
					vector<double>& hours, 
					vector<double>& rate, 
					vector<double>& net)
{
	string mark		= string();				//error marks
	ifstream in;
	
	bool flag		= bool();
	bool error		= bool();
	bool loop		= bool();

	double tax		= double();
	int errorCount	= int();
	int counter		= int();

	string name;							//string input
	char mi			= char();				//char input
	int num			= int();				//int input
	double val		= double();				//double input

	
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	tax = getTax();							//loads tax value from document

	getFile(in);

	in.peek();

	if (!in)								//if no file then goes to the failed state
	{
		cout << "File does not exist" << endl;
		in.clear();
		mark = "Open attempt on non-existing file";
		errorLog(mark, -1);
	}

	else if(in.eof())
	{
		cout << "File is empty" << endl;
		mark = "Open attempt on empty file";
		errorLog(mark, -1);
	}
	else
	{
		while(!flag)
		{
		error = false;						//reset error flag

//get first name
		do 
		{
		in >> name;						
			if (in.fail())
			{
				mark = "first name input FAIL - line : ";
				errorLog(mark, size);
				in.clear();
				in.ignore(1, ' ');
				loop = true;
				error = true;
			}
			else
				loop = false;
		}
		while (loop);

		name[0] = toupper(name[0]);			//ensure capitalized	
		fname.push_back(name);

//get last name
		do
		{
		in >> name;
			if (in.fail())
			{
				mark = "last name input FAIL - line : ";
				errorLog(mark, size);
				in.clear();
				in.ignore(1, ' ');
				loop = true;
				error = true;
			}
			else
				loop = false;
		}
		while (loop);

		name[0] = toupper(name[0]);			//ensure capitalized	
		lname.push_back(name);

//get middle initial
		do
		{
		in >> mi;
			if (in.fail())
			{
				mark = "middle initial input FAIL - line : ";
				errorLog(mark, size);
				in.clear();
				in.ignore(1, ' ');
				loop = true;
				error = true;
			}
			else
				loop = false;
		}
		while (loop);

		mi = toupper(mi);					//ensure capitalized	
		initial.push_back(mi);

//get employee ID
		do
		{
		in >> num;
			if (in.fail())
			{
				mark = "employee ID input FAIL - line : ";
				errorLog(mark, size);
				in.clear();
				in.ignore(1, ' ');
				loop = true;
				error = true;
			}
			else
				loop = false;
		}
		while (loop);

		employeeID.push_back(num);

//get state
		do
		{
		in >> name;
			if (in.fail())
			{
				mark = "state input FAIL - line : ";
				errorLog(mark, size);
				in.clear();
				in.ignore(1, ' ');
				loop = true;
				error = true;
			}
			else
				loop = false;
		}
		while (loop);
		
			for(unsigned int i=0;i<name.length();i++)
			{
			name[i] = toupper(name[i]);			//ALL CAPS for STATE
			}

		state.push_back(name);

//get ZIP
		do
		{
		in >> num;
			if (in.fail())
			{
				mark = "Zipcode input FAIL - line : ";
				errorLog(mark, size);
				in.clear();
				in.ignore(1, ' ');
				loop = true;
				error = true;
			}
			else
				loop = false;
		}
		while (loop);

		zip.push_back(num);

//get hours worked
		do
		{
		in >> val;
			if (in.fail())
			{
				mark = "hours worked input FAIL - line : ";
				errorLog(mark, size);
				in.clear();
				in.ignore(1, ' ');
				loop = true;
				error = true;
			}
			else
				loop = false;
		}
		while (loop);

		hours.push_back(val);

//get payrate
		do
		{
		in >> val;
			if (in.fail())
			{
				mark = "pay rate input FAIL - line : ";
				errorLog(mark, size);
				in.clear();
				in.ignore(1, ' ');
				loop = true;
				error = true;
			}
			else
				loop = false;
		}
		while (loop);

		rate.push_back(val);
		net.push_back(rate[size]*hours[size]-(rate[size]*hours[size]*tax));

		size++;
		counter++;

		if (error)
		{
			errorCount++;
		}

		in.peek();
			if (in.eof())
			{
				flag = true;
			}

		}//exit loop
	}//end else

	dataCheck(counter);
	
	SetConsoleTextAttribute(hConsole, 12);
	cout << endl << errorCount << " records contain bad data!" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	system("pause");

	in.close();
}
//***********************************************************************************************************************************************
// ERROR LOG  - RECORDS PROGRAM ERRORS WHILE IN USE
//***********************************************************************************************************************************************
void errorLog		(string error, int index)
{
	ofstream printerror;
	time_t currentTime;
	time(&currentTime);
	

	printerror.open("G:\\ERS\\logs\\errorLog.txt",ios::app);
	//printerror.open("C:\\Users\\Alias\\Desktop\\CS_11\\Final\\logs\\errorLog.txt",ios::app);
	printerror << asctime(localtime(&currentTime)) << "\t - " << error <<  index+1 << endl;
	printerror.close();
}
//***********************************************************************************************************************************************
// DATA CHECK  - REQUEST RECORD LIMIT
//***********************************************************************************************************************************************
void dataCheck		(int qty)
{
	int desired = 30;

	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "\nPlease Enter the expectant # of RECORDS [default = 30] : ";
	cin >> desired;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
	}

	if (qty > desired)
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << endl << "# of Records read exceeds expectant by " << qty - desired << endl << endl;
		SetConsoleTextAttribute(hConsole, 7);
		errorLog("# of Records read exceeds expectant by ", qty - desired- 1);
	}

	else if (qty < desired)
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << endl << "# of Records read does not meet expectant by " << desired - qty << endl << endl;
		SetConsoleTextAttribute(hConsole, 7);
		errorLog("# of Records read short expectant by ", desired - qty - 1);
	}
	else 
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << endl << "# of Records meet expectant. Data check PASSED. " << endl << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}

	accessLog("# of Records imported: ", qty);


}
//***********************************************************************************************************************************************
// DISPLAY RECORDS  - SCREEN OUTPUT OF ALL RECORDS OPTION 4 (see - DISPLAY MENU)
//***********************************************************************************************************************************************
void displayRecords	(int size, 
					vector<string> fname, 
					vector<string> lname, 
					vector<char> initial, 
					vector<int> employeeID, 
					vector<string> state, 
					vector<int> zip, 
					vector<double> hours, 
					vector<double> rate, 
					vector<double> net)
{
	system("cls");

//header
	cout << endl	<< setw(9)	<< left << "FIRST"
					<< setw(13) << left << "LAST"
					<< setw(2)	<< left << "I"
					<< setw(9)	<< right << "ID #"
					<< setw(7)	<< right << "STATE"
 << fixed			<< setw(6)	<< right << "ZIP"
 << setprecision(0) << setw(10) << right << "HOURS"
 << setprecision(2) << setw(8)	<< right << "RATE"
					<< setw(8)	<< right << "NET"	<< endl;

//horizontal line
	for (int j=1; j < 75; j++)
	{
		cout << "_";
	}
	cout << endl;

//data
	for (int i = 0; i<size; i++)
	{
	cout << endl	<< setw(9)	<< left	 << fname[i]
					<< setw(13) << left  << lname[i]
					<< setw(2)	<< left  << initial[i]
					<< setw(10) << right << employeeID[i]
					<< setw(5)	<< right << state[i]
 << fixed			<< setw(8)	<< right << zip[i]
 << setprecision(0) << setw(8)	<< right << hours[i]
 << setprecision(2) << setw(9)	<< right << rate[i]
					<< setw(10) << right << net[i] << endl;
	}

//horizontal line
	for (int j=1; j < 75; j++)
	{
		cout << "_";
	}
	cout << endl << endl;

	system("pause");
}
//***********************************************************************************************************************************************
// SAVE RECORDS  - OUTPUTS FORMATTED TXT FILE
//***********************************************************************************************************************************************
void saveRecords	(int size, 
					vector<string> fname, 
					vector<string> lname, 
					vector<char> initial, 
					vector<int> employeeID, 
					vector<string> state, 
					vector<int> zip, 
					vector<double> hours, 
					vector<double> rate, 
					vector<double> net)
{
	ofstream out;
	makeFile(out);
	
	system("cls");

//header
	out << endl		<< setw(9)	<< left	 << "FIRST"
					<< setw(13) << left  << "LAST"
					<< setw(2)	<< left  << "I"
					<< setw(9)	<< right << "ID #"
					<< setw(7)	<< right << "STATE"
<< fixed			<< setw(6)	<< right << "ZIP"
<< setprecision(0)	<< setw(10)	<< right << "HOURS"
<< setprecision(2)	<< setw(8)	<< right << "RATE"
					<< setw(8)	<< right << "NET"	<< endl;

//horizontal line
	for (int j=1; j < 75; j++)
	{
		out << "_";
	}
	out << endl;

//data
	for (int i = 0; i<size; i++)
	{
	out << endl		<< setw(9)	<< left  << fname[i]
					<< setw(13) << left  << lname[i]
					<< setw(2)	<< left  << initial[i]
					<< setw(10) << right << employeeID[i]
					<< setw(5)	<< right << state[i]
<< fixed			<< setw(8)	<< right << zip[i]
<< setprecision(0)	<< setw(8)	<< right << hours[i]
<< setprecision(2)	<< setw(9)	<< right << rate[i]
					<< setw(10) << right << net[i]	<< endl;
	}

//horizontal line
	for (int j=1; j < 75; j++)
	{
		out << "_";
	}
	out << endl << endl;

	cout << "File Saved." << endl;
	accessLog("Printed File ", 100);
	out.close();
	system("pause");

}
//***********************************************************************************************************************************************
// FIND LOWEST  - INDEX LOWEST NET VALUE TO DISPLAY RESULT (see - DISPLAY RESULT)
//***********************************************************************************************************************************************
int findLowest	(const int size, const vector<double> net)
{
	int index	= int();
	int lowest	= 0;

		for (index = 1; index < size; index++)
		if (net[lowest] > net[index])
		{		
			lowest = index;
		}
	accessLog("Found LOWEST ", -11);	
	return lowest;
}
//***********************************************************************************************************************************************
// FIND HIGHEST  - INDEX HIGHEST NET VALUE TO DISPLAY RESULT (see - DISPLAY RESULT)
//***********************************************************************************************************************************************
int findHighest	(const int size, const vector<double> net)
{
	int index = int();
	int highest = 0;

		for (index = 1; index < size; index++)
		if (net[highest] < net[index])
		{		
			highest = index;
		}
	accessLog("Found HIGHEST ", 9);
	return highest;
}
//***********************************************************************************************************************************************
// SEARCH NAME  - SCANS RECORDS for NAME, INDEX TO DISPLAY RESULT (see - DISPLAY RESULT)
//***********************************************************************************************************************************************
int searchName		(const int size, const vector<string> lName)
{
	string compare	= string();
	int index		= -1;
	int counter		= 0;

	cout << "\n\nPlease Enter a Last NAME : ";
	cin >> compare;
	accessLog("Searched Last NAME: " + compare + " ", 60);

//match case
						//for(unsigned int x=0;x<compare.length();x++)
						//{
						//compare[x] = toupper(compare[x]);						    //ALL CAPS CASE match for search
						//}
						//for(unsigned int x=0;x<lName[i].length();x++)
						//{
						//lName[i][x] = toupper(lName[i][x]);						//ALL CAPS CASE match for search
						//}
			
			for (int i= 0; i<size; ++i)
			{
				if(lName[i] == compare)
				{
					index = i;
					counter++;
				}
			}
			if (counter > 1)
				{
					cout << "More than one record found. Please try search by ID" << endl;
					system("pause");
				}

	return index;
}
//***********************************************************************************************************************************************
// SEARCH ID  - SCANS RECORDS by ID, INDEX TO DISPLAY RESULT (see - DISPLAY RESULT)
//***********************************************************************************************************************************************
int searchID		(const int size, const vector<int> employeeID)
{
	int compare		= int();
	int index		= -1;
	
	cout << "\n\nPlease Enter Employee ID : ";
	cin >> compare;
	accessLog("Searched ID#: ",compare-1);

			for (int i= 0; i<size; ++i)
			{
				if(employeeID[i] == compare)
				{
					index = i;
				}
			}
			
	return index;
}
//***********************************************************************************************************************************************
// DISPLAY RESULT  - DISPLAYS RESULT OF REQUEST SEARCH OR INDEX
//***********************************************************************************************************************************************
void displayResult	(int index, 
					vector<string> fname, 
					vector<string> lname, 
					vector<char> initial, 
					vector<int> employeeID, 
					vector<string> state, 
					vector<int> zip, 
					vector<double> hours, 
					vector<double> rate, 
					vector<double> net)
{
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (index == -1)
	{
		errorLog("Searched Record NOT FOUND ", -2);
		SetConsoleTextAttribute(hConsole, 12);
		cout << "No record found!" << endl << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
	else
	{
//header
	cout << endl	<< setw(9)	<< left  << "FIRST"
					<< setw(13) << left  << "LAST"
					<< setw(2)	<< left  << "I"
					<< setw(9)	<< right << "ID #"
					<< setw(7)	<< right << "STATE"
<< fixed			<< setw(6)	<< right << "ZIP"
<< setprecision(0)	<< setw(10) << right << "HOURS"
<< setprecision(2)	<< setw(8)	<< right << "RATE"
					<< setw(8)	<< right << "NET"	<< endl;

//horizontal line
	for (int j=1; j < 75; j++)
	{
		cout << "_";
	}
	cout << endl;

//data
	cout << endl	<< setw(9)	<< left  << fname[index]
					<< setw(13) << left  << lname[index]
					<< setw(2)  << left  << initial[index]
					<< setw(10) << right << employeeID[index]
					<< setw(5)	<< right << state[index]
<< fixed			<< setw(8)	<< right << zip[index]
<< setprecision(0)	<< setw(8)  << right << hours[index]
<< setprecision(2)	<< setw(9)	<< right << rate[index]
					<< setw(10) << right << net[index]		<< endl << endl;
	}
	accessLog("Displayed result RECORD #", index);
	system("pause");
}

//***********************************************************************************************************************************************
// SORT LAST  - SORTS RECORDS ALPHABETICALLY BY LAST NAME FOR PRINT/DISPLAY
//***********************************************************************************************************************************************
void sortLast		(int size, 
					vector<string>& fname, 
					vector<string>& lname, 
					vector<char>& initial, 
					vector<int>& employeeID, 
					vector<string>& state, 
					vector<int>& zip, 
					vector<double>& hours, 
					vector<double>& rate, 
					vector<double>& net)
{
	system("cls");
	string tempFIRST	= string();
	string tempLAST		= string();
	char tempCH			= char();
	int tempID			= int();
	string tempSTATE	= string();
	int tempZIP			= int();
	double tempHRS		= double();
	double tempRT		= double();
	double tempNET		= double();
		
	for (int i=1; i<size; i++) 
	{
		for (int j=0; j<(size-i); j++)
		{
			if (lname[j] > lname[j+1])				// compare the two neighbors 
			{  
				tempID			= employeeID[j];         
				employeeID[j]	= employeeID[j+1];	// swap sort employeeID
				employeeID[j+1] = tempID;	

				tempFIRST		= fname[j];
				fname[j]		= fname[j+1];		//sort first name
				fname[j+1]		= tempFIRST;

				tempLAST		= lname[j];
				lname[j]		= lname[j+1];		//sort last name
				lname[j+1]		= tempLAST;

				tempCH			= initial[j];
				initial[j]		= initial[j+1];		//sort middle initial
				initial[j+1]	= tempCH;

				tempSTATE		= state[j];
				state[j]		= state[j+1];		//sort state
				state[j+1]		= tempSTATE;

				tempZIP			= zip[j];
				zip[j]			= zip[j+1];			//sort zip
				zip[j+1]		= tempZIP;

				tempHRS			= hours[j];
				hours[j]		= hours[j+1];		//sort hours
				hours[j+1]		= tempHRS;

				tempRT			= rate[j];
				rate[j]			= rate[j+1];		//sort rate
				rate[j+1]		= tempRT;

				tempNET			= net[j];
				net[j]			= net[j+1];			//sort net
				net[j+1]		= tempNET;
				
			}
		}
	}
	accessLog("Records Sorted by NAME ", 20);
	cout << "\nRecords have been Updated.";system("pause");
}
//***********************************************************************************************************************************************
// SORT ID  - SORTS RECORDS NUMERICALLY BY ASCENDING ID#  FOR PRINT/DISPLAY
//***********************************************************************************************************************************************
void sortID			(int size, 
					vector<string>& fname, 
					vector<string>& lname, 
					vector<char>& initial, 
					vector<int>& employeeID, 
					vector<string>& state, 
					vector<int>& zip, 
					vector<double>& hours, 
					vector<double>& rate, 
					vector<double>& net)
{
	system("cls");
	string tempFIRST	= string();
	string tempLAST		= string();
	char tempCH			= char();
	int tempID			= int();
	string tempSTATE	= string();
	int tempZIP			= int();
	double tempHRS		= double();
	double tempRT		= double();
	double tempNET		= double();
		
	for (int i=1; i<size; i++) 
	{
		for (int j=0; j<(size-i); j++)
		{
			if (employeeID[j] > employeeID[j+1])	// compare the two neighbors 
			{  
				tempID			= employeeID[j];         
				employeeID[j]	= employeeID[j+1];	// swap sort employeeID
				employeeID[j+1]	= tempID;	

				tempFIRST		= fname[j];
				fname[j]		= fname[j+1];		//sort first name
				fname[j+1]		= tempFIRST;

				tempLAST		= lname[j];
				lname[j]		= lname[j+1];		//sort last name
				lname[j+1]		= tempLAST;

				tempCH			= initial[j];
				initial[j]		= initial[j+1];		//sort middle initial
				initial[j+1]	= tempCH;

				tempSTATE		= state[j];
				state[j]		= state[j+1];		//sort state
				state[j+1]		= tempSTATE;

				tempZIP			= zip[j];
				zip[j]			= zip[j+1];			//sort zip
				zip[j+1]		= tempZIP;

				tempHRS			= hours[j];
				hours[j]		= hours[j+1];		//sort hours
				hours[j+1]		= tempHRS;

				tempRT			= rate[j];
				rate[j]			= rate[j+1];		//sort rate
				rate[j+1]		= tempRT;

				tempNET			= net[j];
				net[j]			= net[j+1];			//sort net
				net[j+1]		= tempNET;
				
			}
		}
	}
	accessLog("Records Sorted by ID ", 21);
	cout << "\nRecords have been Updated.";system("pause");
}
//***********************************************************************************************************************************************
// FIND TOTALS  - CALCULATES AND DISPLAYS TOTAL HOURSS WORKED BY ALL EMPLOYEES AND TOTAL PAYOUT (see - DISPLAY RECORDS)
//***********************************************************************************************************************************************
void findTotals		(const int size, const vector<double> hours, const vector<double> net)
{
	double expense	= double();
	double ttlhrs	= double();

	
	for (int i=0; i<size; i++)
	{
		ttlhrs	+= hours[i];
		expense += net[i];
	}
	cout << fixed << setprecision(2) << "\n\nTotal hours worked and total cost of all employees = \n";
		
	for (int j=1; j < 75; j++)
	{
		cout << "_";
	}
	cout << "\n\n\t\t\t"			<< setw(25) << right	<< "Totals hours worked : " << setw(10) << right << ttlhrs	<< endl << endl
		<< "\t\t\t"					<< setw(26)				<< "Overall cost : $"		<< setw(9)	<< right << expense << endl;
		
	for (int j=1; j < 75; j++)
	{
		cout << "_";
	}
	cout << endl;

	accessLog("Displayed Totals ",29); 
	system("pause");
}
//***********************************************************************************************************************************************
// GOODBYE  - EXIT SCREEN UPON REQUESTED EXIT
//***********************************************************************************************************************************************
void goodBye()
{
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i<2; i++)
	{
	SetConsoleTextAttribute(hConsole, 137);
	system("cls");
	Sleep(250);     //time for text to stay on the console before the loops next pass
	SetConsoleTextAttribute(hConsole, 17); //gotoxy to create large text.
	gotoxy(6,5); cout << "    ";
	gotoxy(12,5); cout << "   ";
	gotoxy(18,5); cout << "   ";
	gotoxy(23,5); cout << "    ";
	gotoxy(29,5); cout << "    ";
	gotoxy(35,5); cout << " ";gotoxy(39,5); cout << " ";
	gotoxy(41,5); cout << "     ";

	gotoxy(5,6); cout << " ";
	gotoxy(11,6); cout << " ";gotoxy(15,6); cout << " ";
	gotoxy(17,6); cout << " ";gotoxy(21,6); cout << " ";
	gotoxy(23,6); cout << " ";gotoxy(27,6); cout << " ";
	gotoxy(29,6); cout << " ";gotoxy(33,6); cout << " ";
	gotoxy(36,6); cout << " ";gotoxy(38,6); cout << " ";
	gotoxy(41,6); cout << " ";

	gotoxy(5,7); cout << " ";gotoxy(7,7); cout << "   ";
	gotoxy(11,7); cout << " ";gotoxy(15,7); cout << " ";
	gotoxy(17,7); cout << " ";gotoxy(21,7); cout << " ";
	gotoxy(23,7); cout << " ";gotoxy(27,7); cout << " ";
	gotoxy(29,7); cout << "    ";
	gotoxy(37,7); cout << " ";
	gotoxy(41,7); cout << "    ";
		gotoxy(5,8); cout << " ";gotoxy(9,8); cout << " ";
	gotoxy(11,8); cout << " ";gotoxy(15,8); cout << " ";
	gotoxy(17,8); cout << " ";gotoxy(21,8); cout << " ";
	gotoxy(23,8); cout << " ";gotoxy(27,8); cout << " ";
	gotoxy(29,8); cout << " ";gotoxy(33,8); cout << " ";
	gotoxy(37,8); cout << " ";
	gotoxy(41,8); cout << " ";
		gotoxy(6,9); cout << "   ";
	gotoxy(12,9); cout << "   ";
	gotoxy(18,9); cout << "   ";
	gotoxy(23,9); cout << "    ";
	gotoxy(29,9); cout << "    ";
	gotoxy(37,9); cout << " ";
	gotoxy(41,9); cout << "     ";
	Sleep(100);    
	}
	SetConsoleTextAttribute(hConsole, 129);

	accessLog("Successfully Logged Out ",998); 

	gotoxy(5,11); cout << "\aThank you for using ERS (c) 2010.";
	gotoxy(5,13);
	exit(1);
}
