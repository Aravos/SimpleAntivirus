#include <iostream>
#include <windows.h>
using namespace std;

void Scan(const std::string& directoryPath) {
    WIN32_FIND_DATA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    std::string searchPath = directoryPath + "\\*";         
    
    //forming a complete search path using wildcard ch '*' in order to match multiple files or directories

    hFind = FindFirstFile(searchPath.c_str(), &findData);

    // Using the Windows API to search for file in the specified directory

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "Error opening directory: " << directoryPath << std::endl;
        return;
    }

    //Initiate loop to idetate over all files
    while (1){

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

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // DIR
            std::cout << "[DIR] " << findData.cFileName << std::endl;
            // Recursive call to scan subdirectory Scan(fullPath);
        } else {
            // FILE
            std::cout << "[FILE] " << findData.cFileName << std::endl;
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

    Scan(directoryPath);

    return 0;
}
