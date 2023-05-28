#include <iostream>
#include <windows.h>
using namespace std;

void Scan(const std::string& directoryPath) {
    WIN32_FIND_DATA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    std::string searchPath = directoryPath + "\\*";

    hFind = FindFirstFile(searchPath.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "Error opening directory: " << directoryPath << std::endl;
        return;
    }

    std::cout << "Files in directory: " << directoryPath << std::endl;
    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // Skip directories
            continue;
        }
        std::cout << findData.cFileName << std::endl;
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
}

int main() {
    std::string directoryPath;
    cin >> directoryPath;
    // = "C:\\Users\\Aravo\\OneDrive\\Desktop\\Antivirus";
    Scan(directoryPath);

    return 0;
}
