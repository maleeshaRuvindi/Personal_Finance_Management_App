#include "Transaction.h"

//class Transaction {
//public:
//	int amount;
//	int type;
	Transaction::Transaction(int amt, int typ) {

		amount = amt;
		type = typ;
	}

	void Transaction::addTransaction(int amount, int type) {

		sql::PreparedStatement* prep_stmt;

		prep_stmt = con->prepareStatement("INSERT INTO transaction(amount,type) VALUES (?, ?)");

		prep_stmt->setInt(1, amount);
		prep_stmt->setInt(2, type);
		prep_stmt->execute();

		delete prep_stmt;

	};
	void Transaction::viewTransaction() {

		sql::Statement* stmt;
		sql::ResultSet* res;
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM test.transaction LIMIT 0, 10");
		while (res->next()) {
			cout << "transaction_id = " << res->getInt("transaction_id");
			cout << ", amount = '" << res->getInt("amount");
			cout << ", type = '" << res->getInt("type") << "'" << endl;
		}

		delete res;
		delete stmt;

	}
	void Transaction::editTransaction(int newAmount, int newType, int transactionId) {
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
	void Transaction::deletetransaction(int transactionId) {
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

//};





