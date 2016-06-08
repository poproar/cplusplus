/*	Author:		Andrew 0623706
	Program:	CS12 - 33853 Assignment 1
	Date:		January 30th, 2011
	Descri:		Exercise 4, from pages 646-647, from chapter 11
*/
//***********************************************************************************************************************************************
// LIBRARIES
//***********************************************************************************************************************************************
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
//***********************************************************************************************************************************************
// NAMESPACES and STRUCTURES
//***********************************************************************************************************************************************
using namespace std;

struct menuItemType
{
	string menuItem;		//Menu Item Name
	double menuPrice;		//Menu Item Price
};
//***********************************************************************************************************************************************
// PROTYPES			-		DEFINITIONS CAN BE FOUND AT FUNCTIONS
//***********************************************************************************************************************************************
void getData	(menuItemType list[], int&);
void showMenu	(menuItemType list[], const int );
void placeOrder	(int order[], int, menuItemType list[]);
bool cont		(bool&, int order[], int);
void printCheck	(menuItemType list[], const int, int order[]);
void border		(char b = '.');
void header		(string);
//***********************************************************************************************************************************************
// MAIN -   PRIMARY LOOP
//***********************************************************************************************************************************************
int main()
{
	menuItemType menuList[10];		//array holding menu data !!MAX items 10 update to 100 if needed
	int index		= 0;
	int order[10]	= {0};
	int select		= 0;
	bool stop		= false;
	bool flag		= false;

	getData(menuList, index);		//loads restaurant menu - NOTE: text file must be clean with new line per item new line per price

	while(!flag)					//enter menu select loop
	{
		while(!stop)
		{
			showMenu(menuList, index);
			
			cin >> select;

			if(cin.fail())			
			{
					cin.clear();
					cin.ignore(1000, '\n');
			}
			else if( (select > 0) && (select <= index) )
			{
				placeOrder(order, select, menuList);		//enter qty 
			
			}
			else 
			{
				stop = true;								//exit to print
			}
		}
	
		printCheck(menuList, index, order);
		flag = cont(stop, order, index);					//restart loop with or without current values
	}

	return 0;
}
//***********************************************************************************************************************************************
// FUNCTIONS  - SEE DEFINITIONS
//***********************************************************************************************************************************************


//***********************************************************************************************************************************************
// GETDATA  - loads data for menu selection and pricing stored as menuList.txt in local folder 
//***********************************************************************************************************************************************
void getData(menuItemType list[], int& i){

	ifstream menuData = ifstream();
	
	menuData.open("menuList.txt"); 
	if (!menuData)
	{
		cout << "Cannot Read menu file.\nProgram will end..." << endl;
	}

	while (!menuData.eof())
	{
		getline(menuData, list[i].menuItem);

		if(menuData.fail())
		{
			menuData.clear();
		}

		menuData >> list[i].menuPrice;

		if(menuData.fail())
		{
			menuData.clear();
		}
		else
		{
			++i;
		}
	}

	menuData.close();
	menuData.clear();
}
//***********************************************************************************************************************************************
// SHOW MENU  - shows different items offered and tells user how to select items
//***********************************************************************************************************************************************
void showMenu(menuItemType list[], const int i){
	
	int z = 0;
	
	header(" #  ");
	while(z < i)
	{
		cout << fixed << setprecision(2) << "\t\t\t " << z+1 << "   "			//added one to array identifier to avoid user confusion
			 << setw(19) << left << list[z].menuItem
		     << setw(6) << right << list[z].menuPrice << endl << endl;
		++z;
	}

	cout << "Please Select an Item from the Menu" << endl						//select item to be purchased
		<< "[ 1 - " << i << " ] or Press 0 to Print Check : " ;					//or to print check

}
//***********************************************************************************************************************************************
// PLACE ORDER  - fills order 
//***********************************************************************************************************************************************
//
void placeOrder(int order[], int select, menuItemType list[]){

	int tally;

	cout << endl << list[select-1].menuItem 
		 << " - Enter Quantity [Default = 0] : ";
	cin >> tally;									//adds to item quantity		
		if(cin.fail())
		{
			cin.clear();
			tally = 0;								//if error then value is zero
		}

	order[select-1] += tally;

	cout << endl << endl							//displays current ordered out of total ordered with sum
		 << "You Have ordered " << tally << " " 
		 << list[select-1].menuItem 
		 << " for a total of " << order[select-1] 
		 << " = $" << (order[select-1]*list[select-1].menuPrice) << endl;

}
//***********************************************************************************************************************************************
// PRINT CHECK  - calculates and prints check
//***********************************************************************************************************************************************
void printCheck(menuItemType list[], const int i, int order[]){

	int z = 0;
	double subtotal = 0;
	double tax = .05;
	
	header("QTY ");											//column label

	while(z < i)											//cycle thru order array
		if (order[z] == 0)									//if none
		{
			++z;											//then skip
		}
		else
		{
			cout << setprecision(0) << "\t\t\t " 
				 << order[z] << "   "						//quantity ordered
				 << setw(18) << left 
				 << list[z].menuItem						//item name
				 << setprecision(2) << setw(6) << right 
				 << (order[z]*list[z].menuPrice)			//line total
				 << endl << endl;
				subtotal += (order[z]*list[z].menuPrice);	//sum line totals
				++z;
		}

		border('_');

		cout << "\t\t\t" << setw(23) << right << "Subtotal = " 
			 << setw(6) << right << subtotal << endl;					//displays subtotal
		cout << "\t\t\t" << setw(23) << right << "Tax = " 
			 << setw(6) << right << (tax*subtotal) << endl << endl;		//calculates and displays tax total
		cout << "\t\t\t" << setw(23) << right << "TOTAL = " 
			 << setw(6) << right << ((tax*subtotal)+subtotal) << endl;	//sums subtotal and tax total for bill
}
//***********************************************************************************************************************************************
// CONTINUE  - allows program to loop, restart, or exit
//***********************************************************************************************************************************************
bool cont(bool& stop, int order[], int i)
{	
	char again = char();
	char reset = char();
	int z = 0;
	
	cout << "\nContinue? (y/n): ";
	cin >> again;

		if (again == 'Y' || again == 'y')			//if to run showMenu select loop
		{
			cout << "Clear order?" << endl;
			cin >> reset;
			if (reset == 'Y' || reset == 'y')		//then if to clear order
			{
				while(z < i)
				{
					order[z] = 0;
					++z;
				}
			}
			stop = false;
			return false;			
		}
		else										//otherwise end
		{
			//cout << "Print to file?" << endl;		//add function?
			return true;
		}	
}
//***********************************************************************************************************************************************
// HEADER  - prints basic header with ability to change first column label
//***********************************************************************************************************************************************

void header(string hd){

	border();

	cout << "\t\t\t: Welcome to Andrew's Eatery :" << endl;				//Restaurant Name

	border();

	cout << "\t\t\t"  << hd												//column label
		 << setw(19) << left  << " ITEM"								//column label
		 << setw(6)  << right << "AMT($)" << endl;						//column label

	border('_');

}
//***********************************************************************************************************************************************
// BORDER  - used to generate line fill
//***********************************************************************************************************************************************
void border(char b){

	cout << "\t\t\t";
	for (int j=1; j < 31; j++)
	{
		cout << b;
	}
	cout << endl << endl;
}
