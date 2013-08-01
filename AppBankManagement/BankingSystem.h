/*
 * BankingSystem.h
 *
 *  Created on: Jul 1, 2013
 *      Author: Vijaywargi
 */
//Header file for Banking System project
/*	---------------------------------------------------------------------
	A customer can create an Account, Deposit and Withdraw amount in his Account.
	A customer can also Modify details of his account or delete the account.
	---------------------------------------------------------------------*/

#ifndef BANKINGSYSTEM_H_
#define BANKINGSYSTEM_H_

#include <iostream>

class Account
{
	int acno;			//Account Number of a customer
	char name[50];		//Name of a customer
	double balance;		//Current Balance of an account
	char type;			//Type of account (C / S)

public:

	void createAccount(); 	//get data from user to create an account
	void showAccount();  	//show account details

	void deposit(double);	//deposit amount in the account
	void withdraw(double);  //withdraw amount from the account

	double returnBalance() const;
	int returnAccno() const;
	char returnType() const;

	void setType();
	void setBalance();

	void modify();			//modify data
	void deleteAccount(int);	//delete account
	void report() const;	//show transactions


};



#endif /* BANKINGSYSTEM_H_ */
