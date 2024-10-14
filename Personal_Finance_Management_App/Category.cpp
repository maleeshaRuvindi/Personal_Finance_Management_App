#include <string>
#include "Transaction.h"

using std::string;
class Category {
public:
    int categoryId;
    string categoryName;
    int categoryType; // "Income" or "Expense"

    Category(string name, int type);
    static void addCategory(string name,int type);
    static void viewCategory();
    static void editCategory(int id, string newName, int newType);
    static void deleteCategory(int id);
};
Category::Category(string name, int type) {
    categoryName = name;
    categoryType = type;
};
void Category::addCategory( string name, int type){
    sql::PreparedStatement* prep_stmt;

    prep_stmt = con->prepareStatement("INSERT INTO test.category(category_name,category_type) VALUES (?, ?)");

    prep_stmt->setString(1, name);
    prep_stmt->setInt(2, type);
    prep_stmt->execute();

    delete prep_stmt;
}
void Category::viewCategory(){
    sql::Statement* stmt;
    sql::ResultSet* res;
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM test.category LIMIT 0, 10");
    while (res->next()) {
        cout << "category name = " << res->getString("category_name");
        cout << ", type = '" << res->getInt("category_type") << "'" << endl;
    }

    delete res;
    delete stmt;
}
void Category::editCategory(int id, string newName, int newType) {
    sql::PreparedStatement* prep_stmt;
    prep_stmt = con->prepareStatement("UPDATE test.category SET category_name = ?, category_type = ? WHERE category_id = ?");

    prep_stmt->setString(1, newName);        // New type to set
    prep_stmt->setInt(2, newType);
    prep_stmt->setInt(3, id);  // transaction_id to identify the row to update

    // Execute the update query
    int rowsAffected = prep_stmt->executeUpdate();

    // Check how many rows were affected
    if (rowsAffected > 0) {
        cout << "Category with ID " << id << " updated successfully!" << endl;
    }
    else {
        cout << "No transaction found with ID " << id << endl;
    }

    // Clean up
    delete prep_stmt;
}
void Category::deleteCategory(int id){
    sql::PreparedStatement* prep_stmt;
    prep_stmt = con->prepareStatement("DELETE FROM transaction WHERE category_id = ?");
    prep_stmt->setInt(1, id);

    int rowsAffected = prep_stmt->executeUpdate();
    if (rowsAffected > 0) {
        cout << "Transaction with ID " << id << " deleted successfully!" << endl;
    }
    else {
        cout << "No transaction found with ID " << id << endl;
    }

    delete prep_stmt;
}
