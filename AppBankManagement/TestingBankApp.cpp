/*
 * TestingBankApp.cpp
 *
 *  Created on: Jul 3, 2013
 *      Author: Vijaywargi
 */

#include <fstream>
#include "BankingSystem.h"
#include <iostream>

using namespace std;

void write_account();
void deposit(int);
void withdraw(int);
void balanceEnquiry(int);
void showAll();
void modifyAccount(int);

int main() {

	cout << "\tWelcome to Banking system !" << endl ;


	int accno;
	int option;

	while(1)
		{

		cout << "\n\n\n\n\n\t1. Create an account." << endl;
		cout << "\t2. Deposit amount " << endl;
		cout << "\t3. Withdraw amount " << endl;
		cout << "\t4. Balance Enquiry" << endl;
		cout << "\t5. Show all account details " << endl;
		cout << "\t6. Modify Account Details" << endl;
		cout << "\t7. Close an account " << endl;
		cout << "\t8. Exit " << endl;
		cout << "\nEnter your choice: " ;
		cin >> option;


	switch(option)
	{
	case 1:

		write_account();
		break;

	case 2:

		cout << "Enter A/C no. : ";
		cin >> accno;
		deposit(accno);
		break;

	case 3:

		cout << "Enter A/C no. : ";
		cin >> accno;
		withdraw(accno);
		break;

	case 4:

		cout << "Enter A/C no.:" ;
		cin >> accno;
		balanceEnquiry(accno);
		break;

	case 5:

		showAll();
		break;

	case 6:

		cout << "Enter A/C no. :" ;
		cin >> accno;
		modifyAccount(accno);
		break;

	case 7:

		cout << "A/C no. to be deleted : " ;
		cin >> accno;
		Account acc;
		acc.deleteAccount(accno);
		break;

	case 8:
		cout << "\n\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t THANK YOU";
		cout << "\n\n\n\t\t Good Bye !" ;
		return 0;
		break;

	default:
		cout << "Invalid choice";
		break;

	}
	cin.ignore();
	cin.get();
	}
	return 0;
}

//Create an account
void write_account()
{
	Account ac;
	ofstream fout;
	fout.open("account.dat",ios::binary|ios::app);
	ac.createAccount();
	fout.write(reinterpret_cast<char *> (&ac), sizeof(Account));
	fout.close();
}


//Deposit
void deposit(int n)
{
	int amt;
	bool found=false;
	Account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not open!! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.returnAccno()==n)
		{
			ac.showAccount();
			cout<<"Enter The amount to be deposited";
			cin>>amt;
			ac.deposit(amt);
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n ! Record Updated !";
			found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<" \n\n ! Record Not Found !";
}


//withdraw
void withdraw(int n)
{
  int amt;
  bool found=false;
  Account ac;
  fstream File;
  File.open("account.dat", ios::binary|ios::in|ios::out);
  if(!File)
  {
	  cout<<"File could not open!! Press any Key...";
    return;
  }
  while(!File.eof() && found==false)
  {
    File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
    if(ac.returnAccno()==n)
    {
    	ac.showAccount();
        cout<<"Enter The amount to be withdrawn";
        cin>>amt;
        int bal=ac.returnBalance()-amt;
        if((ac.returnType()=='S' && bal < 500) || (ac.returnType()=='C' && bal < 1000))
        {  cout<<"\n\n ! Insufficient balance !";
        	return; }
        else
          ac.withdraw(amt);
        int pos=(-1)*static_cast<int>(sizeof(ac));
        File.seekp(pos,ios::cur);
        File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
        cout<<"\n\n ! Record Updated !";
        found=true;
    }
  }
    File.close();
    if(found==false)
    	cout<<" \n\n ! Record Not Found !";
}


//Balance enquiry

void balanceEnquiry(int n)
{
	Account ac;
	bool flag=false;
	ifstream fin;
  	fin.open("account.dat",ios::binary);
  	if(!fin)
  	{
  		cout<<"File could not open!! Press any Key...";
  		return;
  	}
  	cout<<"\n\tBALANCE DETAILS\n";

  	while(fin.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
  	{
  		if(ac.returnAccno()==n)
  		{
  			ac.showAccount();
  			flag=true;
  		}
  }
    fin.close();
    if(flag==false)
    	cout<<"\n\n !Account number does not exist!";
}


//Display all
void showAll()
{
	Account ac;
	ifstream fin;
	fin.open("account.dat",ios::binary);
	if(!fin)
	{
		cout<<"File could not open!! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDERS LIST\n\n";
	cout << "A/C no.     |	Holder's Name		| Balance  | Type   " << endl;
	cout << "==============================================================" << endl;


	while(fin.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		ac.report();
	}
	fin.close();
}


//modify

void modifyAccount(int n)
{
	bool found=false;
	Account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
    	cout<<"File could not open!! Press any Key...";
    	return;
    }
    while(!File.eof() && found==false)
    {
    	File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.returnAccno()==n)
		{
			ac.showAccount();
			cout<<"Enter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(Account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n ! Record Updated !";
			found=true;
		 }
    }
    File.close();
    if(found==false)
    	cout<<" \n\n ! Record Not Found !";
}
