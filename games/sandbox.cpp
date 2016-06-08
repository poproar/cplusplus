//libraries
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

template <typename PData>					//XoaX lesson 19 templates review for specialization
void swap(PData& xrItem1, PData& xrItem2){
	PData xTemp = xrItem1;
	xrItem1 = xrItem2;
	xrItem2 = xTemp;
}

template <typename PData>
void PrintArray(PData xaArray[], int iLength) {
	using namespace std;
	for (int iIndex = 0; iIndex < iLength; ++iIndex) {
		cout << xaArray[iIndex] << "  ";
	}
	cout << endl;
}

template <typename PData>					//XoaX lesson 20 sample
void Bubblesort(PData xaArray[], int iLength) {
	for (int iEnd = iLength - 1; iEnd > 0; --iEnd) {
		for (int iIndex = 0; iIndex < iEnd; ++iIndex) {
			if (xaArray[iIndex] > xaArray[iIndex + 1]) {
				Swap(xaArray[iIndex], xaArray[iIndex + 1]);
			}
		}
	}
}

using namespace std;						//XoaX lesson 15 namespace
//prototypes
void header();								//

void header(){

	cout << "\t\t\t**********************************\n"
		 << "\t\t\t*   Enter the Program Name here  *\n"
		 << "\t\t\t*          by Andrew ATP         *\n"
		 << "\t\t\t*  Long Beach City College LBCC  *\n"
		 << "\t\t\t*      January 30th,  2010       *\n"
		 << "\t\t\t**********************************\n"
		 << endl;
}


int main()
{
	cout << RAND_MAX << endl;

//load variables
	//int iNum;				//prefix i = int [hungarian notation] d = double k = const(ant)
	//iNum = 0;				//assignment notation
	//const int kiNum = 1;	//constants must be assigned at declaration
	//double dNum(1.5);		//constructor notation
	//char cCharacter ='A';	//char use single quotes
	//bool bTrue = true;		//True = 1
	//bool bFalse = false;	//False = 0
	//int iaArray[] = {,,};	//first is always[0]


	// 
	//cout << bTrue << " " << bFalse << " " << (bTrue && !bFalse) << endl;
	//cout << bTrue << " " << bFalse << " " << (!bTrue || bFalse) << endl;
	//cout << ((bTrue && bFalse)||(!bTrue || bFalse)) << endl;

	//if (iNum >= kiNum)
	//{
	//	cout << "iNum >= kiNum" << endl;
	//} else {
	//	cout << "iNum < kiNum" <<endl;
	//}

	return 0;
}
