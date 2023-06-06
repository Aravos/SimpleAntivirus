#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

void quarantineFile(const string& filePath) {
    const int length = filePath.length();
    char* charArray = new char[length + 1];
    strcpy(charArray, filePath.c_str());
    const char* lastOccurrence = strrchr(charArray, '\\');
    string newFilePath = "C:\\Users\\Aravo\\OneDrive\\Desktop\\Antivirus\\" + string(lastOccurrence + 1);
    delete[] charArray;

    // Move the file to the quarantine location
    // c_str is used to obtain a pointer to the character array
    BOOL moveFileSuccess = MoveFileEx(filePath.c_str(), newFilePath.c_str(), MOVEFILE_REPLACE_EXISTING);

    if(moveFileSuccess){

    }
    //enc file
    //Change file perm
}

struct Node {
    string path;
    bool isDirectory;
    struct Node* Parent;
    vector<Node*> children;
    // So as to vary the number of children
};

void PrintTree(Node* node, string prefix, bool isLast = true) {
    cout << prefix ;
    if (isLast) {
        cout << "└─";
        prefix += "  ";
    } else {
        cout << "├─";
        prefix += "│ ";
    }
    if (node->isDirectory) {
        cout << "[DIR] ";
    } else {
        cout << "[FILE] ";
    }
    
    string path = node->path;
    
    const int length = path.length();
    char* char_array = new char[length + 1];
    strcpy(char_array, path.c_str());
    const char* lastOccurrence = strrchr(char_array, '\\');
    cout << lastOccurrence+1 << endl;
    

    for (size_t i = 0; i < node->children.size(); i++) {
        bool isLastChild = (i == node->children.size() - 1);
        PrintTree(node->children[i], prefix, isLastChild);
    }

    if (prefix.length() >= 3) {
        prefix.erase(prefix.length() - 3);
    }
}




void Scan(const string& directoryPath, Node *node) {
    WIN32_FIND_DATA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;           
    string searchPath = directoryPath + "\\*"; 
    //cout << "PASS 1" << endl;
    
    //forming a complete search path using wildcard ch '*' in order to match multiple files or directories

    hFind = FindFirstFile(searchPath.c_str(), &findData);
    // hFind was Initially set to INVALID_HANDLE_VALUE it will not be updated unless there an existing DIR
    // Additionally FindNextFile will return 0 when the search is over i.e all files are exhausted
    // Using the Windows API to search for file in the specified directory

    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "Error opening directory: " << directoryPath << endl;
        //cout << "FAIL 1" << endl;
        return;
    }

    //Initiate loop to idetate over all files
    while (1){

        //cout << "PASS 2" << endl;
        
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
            //cout << "[DIR] " << findData.cFileName << endl;
            newNode->path = directoryPath + "\\" + findData.cFileName;
            newNode->isDirectory = true;
            node->children.push_back(newNode);
            Scan(newNode->path,newNode);
        } else {
            // FILE
            //cout << "[FILE] " << findData.cFileName << endl;
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
    string directoryPath;
    //cin >> directoryPath;

    directoryPath = "C:\\Users\\Aravo\\OneDrive\\Desktop";
    // Creating pointer to the Parent node and assigning it space
    Node* node = new Node;
    node->isDirectory = true;
    node->path = directoryPath;
    Scan(directoryPath,node);
    PrintTree(node,"",true);

    //quarantineFile("C:\\Users\\Aravo\\OneDrive\\Desktop\\Hello.txt");
    return 0;
}
