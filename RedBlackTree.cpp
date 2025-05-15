#include "RedBlackTree.h"
#include <fstream>
#include <sstream>

RedBlackTree::RedBlackTree() {
    NIL = new Node("", "", 0.0, 0.0, 0.0, 0.0);
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;
    root = NIL;
}

RedBlackTree::~RedBlackTree() {
    deleteTree(root);
    delete NIL;
}

void RedBlackTree::deleteNode(Node* node, const string& symbol) {
    Node* z = NIL;
    Node* x, *y;
    while (node != NIL) {
        if (node->stockSymbol == symbol)
            z = node;
        node = (symbol < node->stockSymbol) ? node->left : node->right;
    }

    if (z == NIL) return;

    y = z;
    Color yOriginalColor = y->color;
    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;
    if (yOriginalColor == BLACK)
        fixDelete(x);
}

void RedBlackTree::insert(string symbol, string date, double open, double high, double low, double close) {
    Node* newNode = new Node(symbol, date, open, high, low, close);
    Node* parent = nullptr;
    Node* current = root;

    while (current != NIL) {
        parent = current;
        if (symbol < current->stockSymbol)
            current = current->left;
        else if (symbol > current->stockSymbol)
            current = current->right;
        else {
            // Update if symbol exists
            current->date = date;
            current->openPrice = open;
            current->highPrice = high;
            current->lowPrice = low;
            current->closePrice = close;
            delete newNode;
            return;
        }
    }

    newNode->parent = parent;
    if (parent == nullptr) {
        root = newNode;
    } else if (symbol < parent->stockSymbol) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    newNode->left = NIL;
    newNode->right = NIL;
    newNode->color = RED;

    fixInsert(newNode);
}

void RedBlackTree::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string symbol, date;
        double open, high, low, close;
        if (iss >> symbol >> date >> open >> high >> low >> close) {
            insert(symbol, date, open, high, low, close);
        }
    }

    file.close();
}

void RedBlackTree::fixInsert(Node* node) {
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;
            if (uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->left;
            if (uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != NIL)
        rightChild->left->parent = node;

    rightChild->parent = node->parent;
    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != NIL)
        leftChild->right->parent = node;

    leftChild->parent = node->parent;
    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->right)
        node->parent->right = leftChild;
    else
        node->parent->left = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

Node* RedBlackTree::search(string symbol) const {
    Node* current = root;
    while (current != NIL) {
        if (symbol == current->stockSymbol)
            return current;
        else if (symbol < current->stockSymbol)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

void RedBlackTree::inorderHelper(Node* node) const {
    if (node != NIL) {
        inorderHelper(node->left);
        cout << node->stockSymbol << " | Date: " << node->date
             << " | Open: " << node->openPrice
             << " | High: " << node->highPrice
             << " | Low: " << node->lowPrice
             << " | Close: " << node->closePrice << endl;
        inorderHelper(node->right);
    }
}

void RedBlackTree::printTreeHelper(Node* node, string indent, bool last) const {
    if (node != NIL) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }

        string color = node->color == RED ? "RED" : "BLACK";
        cout << node->stockSymbol << "(" << color << ")" << endl;
        printTreeHelper(node->left, indent, false);
        printTreeHelper(node->right, indent, true);
    }
}
void RedBlackTree::saveToFile(std::ofstream& file) const {
    saveTreeNode(file, root);
}

void RedBlackTree::saveTreeNode(std::ofstream& file, Node* node) const {
    if (node == NIL || node == nullptr) return;

    saveTreeNode(file, node->left);
    file << node->stockSymbol << " "
         << node->date << " "
         << node->openPrice << " "
         << node->highPrice << " "
         << node->lowPrice << " "
         << node->closePrice << "\n";
    saveTreeNode(file, node->right);
}

void RedBlackTree::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        saveToFile(file); // Call the other saveToFile function to handle the file writing
        file.close();
    } else {
        cout << "Error opening file to save data." << endl;
    }
}

void RedBlackTree::saveHelper(Node* node, std::ofstream& file) const {
    if (node != NIL) {
        file << node->stockSymbol << " " << node->date << " "
             << node->openPrice << " " << node->highPrice << " "
             << node->lowPrice << " " << node->closePrice << "\n";
        saveHelper(node->left, file);
        saveHelper(node->right, file);
    }
}

void RedBlackTree::remove(string symbol) {
    Node* node = search(symbol);
    if (node == nullptr || node == NIL) {
        cout << "Stock not found.\n";
        return;
    }
    deleteNode(root, symbol);
}

void RedBlackTree::searchStock(string symbol) {
    Node* node = search(symbol);
    if (node) {
        cout << "Found: " << node->stockSymbol << " | Date: " << node->date
             << " | Open: " << node->openPrice
             << " | High: " << node->highPrice
             << " | Low: " << node->lowPrice
             << " | Close: " << node->closePrice << endl;
    } else {
        cout << "Stock not found.\n";
    }
}

void RedBlackTree::updateStockPrice(string stockSymbol, string newDate, double newHigh, double newLow, double newOpen, double newClose) {
    // Search for the stock using its symbol
    Node* node = search(stockSymbol);
    
    // Check if the stock exists in the tree
    if (node) {
        // Update the stock details with the new values
        node->date = newDate;
        node->highPrice = newHigh;
        node->lowPrice = newLow;
        node->openPrice = newOpen;
        node->closePrice = newClose;

        cout << "Updated stock " << stockSymbol << " details:\n";
        cout << "Date: " << newDate << ", High: " << newHigh << ", Low: " << newLow
             << ", Open: " << newOpen << ", Close: " << newClose << endl;
    } else {
        cout << "Stock not found to update.\n";
    }
}

void RedBlackTree::displayInOrder() const {
    inorderHelper(root);
    cout << endl;
}

void RedBlackTree::displayTreeStructure() const {
    printTreeHelper(root, "", true);
}

void RedBlackTree::deleteTree(Node* node) {
    if (node != NIL) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

Node* RedBlackTree::minimum(Node* node) const {
    while (node->left != NIL)
        node = node->left;
    return node;
}

void RedBlackTree::fixDelete(Node* x) {
    Node* s;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rotateRight(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == BLACK && s->left->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    rotateLeft(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}
