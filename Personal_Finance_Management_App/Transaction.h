#pragma once
#include <cppconn/driver.h> 
#include <cppconn/exception.h> 
#include <cppconn/statement.h> 
#include <iostream> 
#include <mysql_connection.h> 
#include <mysql_driver.h> 
#include <cppconn/prepared_statement.h>

using namespace std;
extern sql::Connection* con;

class Transaction {
public:
	int amount;
	int type;
	Transaction(int amt, int typ);

	static void addTransaction(int amount, int type);
	static void viewTransaction();
	static void editTransaction(int newAmount, int newType, int transactionId);
	static void deletetransaction(int transactionId);

};
