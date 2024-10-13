#include "Transaction.h"

sql::mysql::MySQL_Driver* driver;
sql::Connection* con;

void connectToDatabase() {
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "");
	con->setSchema("test");
}

int main()
{
	connectToDatabase();
	
	//Transaction transaction(100, 1);
	/*Transaction::addTransaction(900,1);
	Transaction::viewTransaction();
	Transaction::editTransaction(200,0,2);
	Transaction::deletetransaction(4);*/
	
	return 0;
}


	

	