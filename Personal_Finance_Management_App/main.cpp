#include <cppconn/driver.h> 
#include <cppconn/exception.h> 
#include <cppconn/statement.h> 
#include <iostream> 
#include <mysql_connection.h> 
#include <mysql_driver.h> 
#include <cppconn/prepared_statement.h>


using namespace std;
sql::mysql::MySQL_Driver* driver;
sql::Connection* con;

void connectToDatabase() {
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "");
	con->setSchema("test");
}

class Transaction {
public:
	int amount;
	int type;
	Transaction(int amt, int typ) {
		
		amount = amt;
		type = typ;
	}

	void addTransaction() {
		
		sql::PreparedStatement *prep_stmt;

		prep_stmt = con->prepareStatement("INSERT INTO transaction(amount,type) VALUES (?, ?)");

		prep_stmt->setInt(1, amount);
		prep_stmt->setInt(2, type);
		prep_stmt->execute();

		delete prep_stmt;
		
	};
	void viewTransaction() {

		sql::Statement *stmt;
		sql::ResultSet *res;
		stmt = con->createStatement();
		res= stmt->executeQuery("SELECT * FROM test.transaction LIMIT 0, 10");
		while (res->next()) {
		cout << "transaction_id = " << res->getInt("transaction_id");
		cout << ", amount = '" << res->getInt("amount");
		cout << ", type = '" << res->getInt("type") << "'" << endl;
	}

	delete res;
	delete stmt;

}
	void editTransaction(int newAmount,int newType,int transactionId) {
		sql::PreparedStatement* prep_stmt;
		prep_stmt = con->prepareStatement("UPDATE transaction SET amount = ?, type = ? WHERE transaction_id = ?");

		prep_stmt->setInt(1, newAmount);      // New amount to set
		prep_stmt->setInt(2, newType);        // New type to set
		prep_stmt->setInt(3, transactionId);  // transaction_id to identify the row to update

		// Execute the update query
		int rowsAffected = prep_stmt->executeUpdate();

		// Check how many rows were affected
		if (rowsAffected > 0) {
			cout << "Transaction with ID " << transactionId << " updated successfully!" << endl;
		}
		else {
			cout << "No transaction found with ID " << transactionId << endl;
		}

		// Clean up
		delete prep_stmt;
	}
	void deletetransaction(int transactionId) {
		sql::PreparedStatement* prep_stmt;
		prep_stmt = con->prepareStatement("DELETE FROM transaction WHERE transaction_id = ?");
		prep_stmt->setInt(1, transactionId);

		int rowsAffected = prep_stmt->executeUpdate();
		if (rowsAffected > 0) {
			cout << "Transaction with ID " << transactionId << " deleted successfully!" << endl;
		}
		else {
			cout << "No transaction found with ID " << transactionId << endl;
		}

		delete prep_stmt;
	}

};
int main()
{
	connectToDatabase();
	
	Transaction transaction(100, 1);
	/*transaction.addTransaction();
	transaction.viewTransaction();*/
	//transaction.editTransaction(200,0,2);
	//transaction.deletetransaction(4);

	delete con;
	return 0;
}


	

	