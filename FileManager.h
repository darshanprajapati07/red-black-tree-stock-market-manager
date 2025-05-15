#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "RedBlackTree.h"

using namespace std;

class FileManager {
public:
    FileManager() {}

    // Save Red-Black Tree data to a file
    void saveToFile(const string& filename, RedBlackTree& tree);
    
    // Load Red-Black Tree data from a file
    void loadFromFile(const string& filename, RedBlackTree& tree);
    
    // Check if a file exists
    bool fileExists(const string& filename);

    // Log error messages
    void logError(const string& errorMessage);
    
    // Log informational messages
    void logInfo(const string& infoMessage);

private:
    // Private helper function for error logging
    void logErrorToFile(const string& errorMessage);
};

#endif // FILEMANAGER_H
