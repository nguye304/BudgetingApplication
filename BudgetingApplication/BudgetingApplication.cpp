// BudgetingApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This program is a budgeting software that calculates expenses

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Prototype Declarations
bool checkUserInput();


class Account {//Class 
public:
	float Budget; //budget of account
	vector<string> ExpenseNames;
	vector<float> Expenses; //a vector list of expenses	

	void printAll();
	float totalAfter;
	float calculateBudget();
	void printExpenses();//friend functions allow said function to access class variables
	bool checkIfIStillHaveMoney(float,float);
};


float Account::calculateBudget() {

	float total = Budget, temp = 0, totalExpenses = 0;
	bool doIHaveMoney;
	for (vector<float>::const_iterator i = Expenses.begin(); i != Expenses.end(); i++){
		totalExpenses = totalExpenses + *i;
		total = total - totalExpenses;
		doIHaveMoney = checkIfIStillHaveMoney(totalExpenses,total);
	}
	total = Budget - totalExpenses;
	return total;
}

bool Account::checkIfIStillHaveMoney(float cost, float total)
{
	bool doI;
	if (cost > Budget) {
		doI= false;
		cout << "Please Reconsider. You have " << total << " left";
	}
	else{
		doI= true;
	}
	return doI;
}

void Account::printAll(){
	cout <<"Beginning Budget: "<<Budget<<"\n";
	cout << "Expenses: \n";
	printExpenses();
	cout << "Total After: " << totalAfter;
}

void Account::printExpenses(){
	string *x = &ExpenseNames.front();// assign the address to pointer x
	cout << "+-----Name--------|-------Cost-------+\n";
	cout << "|------------------------------------|\n";
	for (vector<float>::const_iterator i = Expenses.begin(); i != Expenses.end(); i++)//for loop prints out all elements in vector
	{

		cout << "|\t" << *x << "\t|\t" << *i << "\t|\n";//prints out the expense from vector using a pointer
	
		x++;//move pointer x by 1 
	}
	cout << "+-----------------------------------+\n";
}

int main(){
	float budget;
	float expense;
	string userReply;
	string expName;
	bool reply = true;
	
	Account user;
	try
	{
		cout << "Enter a your budget: ";
		cin >> budget;

	}
	catch(const char* msg){
		cout << "Error: "<< msg <<"\n"; 
	}
	user.Budget = budget;

	cout << "\n You have a budget of $" << user.Budget;
	cin.ignore();
	do {
	
		cout << "\n Enter the Expenses name : ";
		getline(cin, expName);
		user.ExpenseNames.push_back(expName);
		
		cout << "\n Enter "<< expName <<"'s expense cost: ";
		cin >> expense;
		reply = checkUserInput();
		user.Expenses.push_back(expense);

		user.totalAfter = user.calculateBudget();
		

	} while (reply == true);

	
	user.printAll();
}


bool checkUserInput(){ // checks if user input was valid
	bool valid;
	bool goAgain;;
	string userReply;
	cin.ignore();//this gets rid of whitespace before getline is called
	do {
		cout << "\n Have another expense? (Y or N): ";
		getline(cin, userReply);

		//User Input Check

		if (userReply == "Yes" || userReply == "Y")
		{
			valid = true;
			goAgain = true;
		}
		else if (userReply == "No" || userReply == "N")
		{
			valid = true;
			goAgain = false;
		}
		else
		{
			cout << "\n The Input: " << userReply << " was not valid. Please Enter Y or N: ";
			valid = false;
		}
	} while (valid == false);
	
	return goAgain;
}

