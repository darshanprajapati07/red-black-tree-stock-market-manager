#include <iostream>
#include <string>
#include <limits>
#include "RedBlackTree.h"
#include "FileManager.h"

using namespace std;

// Display menu for user options
void displayMenu() {
    cout << "\n========== Stock Market Management System (RB-Tree) ==========\n";
    cout << "1.  Insert Stock\n";
    cout << "2.  Delete Stock\n";
    cout << "3.  Search Stock\n";
    cout << "4.  Update Stock Price\n";
    cout << "5.  Display Stocks (Inorder)\n";
    cout << "6.  Save to File\n";
    cout << "7.  Load from File\n";
    cout << "8.  Display Tree Structure\n";
    cout << "9.  Exit\n";
    cout << "==============================================================\n";
    cout << "Enter your choice: ";
}

int main() {
    RedBlackTree stockTree;  
    FileManager fileManager;
    int choice;             
    string stockSymbol, date;
    double high, low, open, close;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:  
                cout << "Enter Stock Symbol (e.g., AAPL): ";
                cin >> stockSymbol;
                cout << "Enter Date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Enter High Price: ";
                cin >> high;
                cout << "Enter Low Price: ";
                cin >> low;
                cout << "Enter Open Price: ";
                cin >> open;
                cout << "Enter Close Price: ";
                cin >> close;

                stockTree.insert(stockSymbol, date, high, low, open, close);  // Insert stock data
                cout << "Stock inserted successfully. Don't forget to save to file!\n";
                break;

            case 2:  // Delete Stock
                cout << "Enter Stock Symbol to Delete: ";
                cin >> stockSymbol;
                stockTree.remove(stockSymbol);  
                cout << "Deletion process complete (if stock was found).\n";
                break;

            case 3:  // Search Stock
                cout << "Enter Stock Symbol to Search: ";
                cin >> stockSymbol;
                stockTree.searchStock(stockSymbol); 
                break;

            case 4:  // Update Stock Price
                cout << "Enter Stock Symbol to Update: ";
                cin >> stockSymbol;
                cout << "Enter New Date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Enter New High Price: ";
                cin >> high;
                cout << "Enter New Low Price: ";
                cin >> low;
                cout << "Enter New Open Price: ";
                cin >> open;
                cout << "Enter New Close Price: ";
                cin >> close;

                stockTree.updateStockPrice(stockSymbol, date, high, low, open, close);  // Update stock price
                break;

            case 5:  // Display Stocks (Inorder Traversal)
                cout << "\n Stock List (Inorder Traversal):\n";
                stockTree.displayInOrder();  
                break;

            case 6:  // Save to File
                fileManager.saveToFile("data/stock_dataset.txt", stockTree);  
                cout << "Stock data saved successfully!\n";
                break;

            case 7:  // Load from File
                fileManager.loadFromFile("data/stock_dataset.txt", stockTree);
                cout << "Stock data loaded successfully!\n";
                break;

            case 8:  // Display Tree Structure
                cout << "\nDisplaying Red-Black Tree Structure:\n";
                stockTree.displayTreeStructure();  
                break;

            case 9:  // Exit
                cout << "Exiting program. Goodbye!\n";
                return 0; 

            default:  // Invalid choice handling
                cout << "Invalid choice! Please enter a number between 1 and 9.\n";
        }

        cin.clear();  // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore extra input
    }
}
