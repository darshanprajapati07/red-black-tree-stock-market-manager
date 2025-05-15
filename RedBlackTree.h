#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Define enum for Red-Black Tree colors
enum Color { RED, BLACK };

// Define the Node structure
struct Node {
    string stockSymbol;  // Stock symbol (e.g., AAPL)
    string date;         // Date of the stock data
    double highPrice;    // High price of the stock
    double lowPrice;     // Low price of the stock
    double openPrice;    // Opening price of the stock
    double closePrice;   // Closing price of the stock
    Node *left, *right, *parent;  // Left, right, and parent pointers
    Color color;         // Node color (RED or BLACK)

    Node(string symbol, string date, double high, double low, double open, double close)
        : stockSymbol(symbol), date(date), highPrice(high), lowPrice(low), openPrice(open), closePrice(close),
          left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RedBlackTree {
private:
    Node *root, *NIL;  // Root and NIL node pointers

    // Private helper functions for Red-Black Tree operations
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void fixInsert(Node* node);
    void fixDelete(Node* node);
    void transplant(Node* u, Node* v);
    void deleteNode(Node* node, const string& symbol);
    Node* minimum(Node* node) const;
    
    void inorderHelper(Node* node) const;
    void printTreeHelper(Node* node, string indent, bool last) const;
    void deleteTree(Node* node);
    
    void saveHelper(Node* node, ofstream& file) const;
    void saveTreeNode(std::ofstream& file, Node* node) const;  // recursive saver


    // Functions to calculate statistics
    int countStocks(Node* node) const;
    double calculateTotalStockValue(Node* node) const;
    Node* findMinStock(Node* node) const;
    Node* findMaxStock(Node* node) const;

public:
    RedBlackTree();  // Constructor
    ~RedBlackTree(); // Destructor

    // Public functions for stock management
    void insert(string symbol, string date, double high, double low, double open, double close);  // Insert a stock
    void remove(string stockSymbol);  // Remove a stock
    Node* search(string symbol) const;  // Search for a stock by symbol
    void searchStock(string stockSymbol);  // Search and display a stock by symbol
    void updateStockPrice(string stockSymbol, string newDate, double newHigh, double newLow, double newOpen, double newClose);  // Update stock data

    // Display functions
    void displayInOrder() const;  // Display stocks in Inorder Traversal
    void displayTreeStructure() const;  // Display Red-Black Tree structure

    // File operations
    void saveToFile(std::ofstream& file) const;  // Save tree data to file
    void saveToFile(const string& filename) const;  // Save tree data to file with filename
    void loadFromFile(const string& filename);  // Load data from file

    // Stock statistics functions
    int getTotalStocks() const;  // Get total number of stocks
    double getTotalStockValue() const;  // Get total stock value
    double calculateAverageStockPrice() const;  // Calculate average stock price
    void displayStockStatistics() const;  // Display stock statistics

    // Functions for min/max stock
    Node* getMaxStock() const;  // Get stock with highest value
    Node* getMinStock() const;  // Get stock with lowest value
};

#endif
