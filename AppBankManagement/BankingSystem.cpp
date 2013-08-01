
/*
 * BankingSystem.cpp
 *
 *  Created on: Jul 1, 2013
 *      Author: Vijaywargi
 */

//Implementation file

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include "BankingSystem.h"

using namespace std;

void Account::setType()
{
	bool correct =false;

	while(!correct)
	{
		cout << "A/C type: (C/S) ";
		char t;
		cin >> t;
		t=toupper(t);
		if(t=='C' || t =='S') {
			type=t;
			correct = true;
			return;
		}
		else {
			cerr << "Incorrect A/C type. \nTry Again.."<< endl ;
		}
	}
}

void Account::setBalance(){
	bool check=false;

	while(!check) {
		cout << "Balance: ";
		double amt;
		cin >> amt;
		if ( (type == 'C' && amt >=1000) || (type == 'S' && amt >=500) ) {
			balance=amt;
			check=true;
		}
		else {
			cerr << "Incorrect balance input. \n Try Again.." << endl;
		}
	}
}
void Account::createAccount() {

	cout << endl << endl;
	cout << "Fill up the details:" << endl;
	cout << "A/C no.: ";
	cin >> acno;
	cout << "A/C Holder Name: ";
	cin.ignore();
	cin.getline(name,50);

	setType();
	setBalance();

	cout << "\n\n ! Account Created !";
}

void Account::showAccount() {

	cout << "\n\t";
	 cout<< endl << "Account No. : "<< acno << endl;
	 cout<<"Holder's Name : " << name << endl;
	 cout<<"Account Type : "<< type << endl;
	 cout<<"Balance Amount : "<< balance << endl;

}

void Account::deposit(double credit) {

	balance += credit;
}

void Account::withdraw(double debit) {
	balance -= debit;
}

double Account::returnBalance() const {

	return balance;
}

int Account::returnAccno() const {

	return acno;
}

char Account::returnType() const {
	return type;

}

void Account::modify()
{
  cout<<" Holder's Name : ";
  cin.ignore();
  cin.getline(name,50);
  setType();
  setBalance();
  /*cout<<"Account Type : " << endl;
  cin>>type;
  type=toupper(type);
  cout<<"Balance Amount : " << endl;
  cin>>balance;*/
}


 void Account::deleteAccount(int acno) {

	Account ac;
	ifstream fin;
	fin.open("account.dat",ios::binary);
	ofstream fout;
	fout.open("temp.dat",ios::out|ios::binary);

	  while(fin.read((char*) &ac, sizeof(ac))){
	    		if(ac.returnAccno() != acno)
	    			fout.write((char*) &ac, sizeof(ac));

	    	}

	    fin.close();
	    fout.close();

	    remove("account.dat");
	    rename("temp.dat","account.dat");
	    cout << "\n\n ! Account Closed !";

}

 void Account::report() const
 {
   cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<balance<<setw(8)<<type<<endl;
 }
