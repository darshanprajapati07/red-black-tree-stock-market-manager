#include "FileManager.h"
#include <fstream>
#include <iostream>

void FileManager::saveToFile(const string& filename, RedBlackTree& tree) {
    ofstream file(filename, ios::app);  // Open file in append mode
    if (file.is_open()) {
        tree.saveToFile(file); // Call the RedBlackTree's saveToFile method
        file << "\n"; // Optional: Add newline for separation between sessions
        file.close();
        cout << "Data successfully appended to " << filename << endl;
    } else {
        logError("Unable to open file for saving: " + filename);
    }
}

void FileManager::loadFromFile(const string& filename, RedBlackTree& tree) {
    if (fileExists(filename)) {
        ifstream file(filename);
        if (file.is_open()) {
            tree.loadFromFile(filename); // Call internal function to load data
            file.close();
            cout << "Stock data successfully loaded from " << filename << endl;
        } else {
            logError("Unable to open file for reading: " + filename);
        }
    } else {
        logError("File does not exist: " + filename);
    }
}

bool FileManager::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void FileManager::logError(const string& errorMessage) {
    cerr << "Error: " << errorMessage << endl;
}

void FileManager::logInfo(const string& infoMessage) {
    cout << "Info: " << infoMessage << endl;
}
