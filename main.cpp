#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

struct Node {
    std::string path;
    bool isDirectory;
    struct Node* Parent;
    std::vector<Node*> children;
    // So as to vary the number of children
};


void Scan(const std::string& directoryPath, Node *node) {
    WIN32_FIND_DATA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;           
    std::string searchPath = directoryPath + "\\*"; 
    
    //std::cout << "PASS 1" << std::endl;
    
    //forming a complete search path using wildcard ch '*' in order to match multiple files or directories

    hFind = FindFirstFile(searchPath.c_str(), &findData);
    // hFind was Initially set to INVALID_HANDLE_VALUE it will not be updated unless there an existing DIR
    // Additionally FindNextFile will return 0 when the search is over i.e all files are exhausted
    // Using the Windows API to search for file in the specified directory

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "Error opening directory: " << directoryPath << std::endl;
        //std::cout << "FAIL 1" << std::endl;
        return;
    }

    //Initiate loop to idetate over all files
    while (1){

        //std::cout << "PASS 2" << std::endl;
        
        // Due to the fact that Windows lists oth current and parent dir of the file within the DIR itself
        // If left unchecked and allowed to read them will cause confusion and may lead to an Infinite loop
        // They will be excluded
        // these files start with a '.' for current DIR and '..' for the parent DIR

        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) {
            if (!FindNextFile(hFind, &findData)) {
                break;    
            }
            continue; //Will Skip the rest of the loop
        }

        Node* newNode = new Node;
        newNode->Parent = node;
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // DIR
            std::cout << "[DIR] " << findData.cFileName << std::endl;
            newNode->path = directoryPath + "\\" + findData.cFileName;
            newNode->isDirectory = true;
            node->children.push_back(newNode);
            Scan(newNode->path,newNode);
        } else {
            // FILE
            std::cout << "[FILE] " << findData.cFileName << std::endl;
            newNode->path = directoryPath + "\\" + findData.cFileName;
            newNode->isDirectory = false;
            node->children.push_back(newNode);
        }

        // Updating Data of findData if it's = to 0 terminate the loop
        if (FindNextFile(hFind, &findData) == 0) {
            break;    
        }
    }
    FindClose(hFind);
}

int main() {
    std::string directoryPath;
    std::cin >> directoryPath;

    // C:\\Users\\Aravo\\OneDrive\\Desktop\\Antivirus
    // Creating pointer to the Parent node and assigning it space
    Node* node = new Node;
    node->isDirectory = true;
    node->path = directoryPath;
    Scan(directoryPath,node);
    return 0;
}
