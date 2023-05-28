#include <string>
#include <iostream>
#include <experimental/filesystem>
namespace fs = std::filesystem;

int main()
{
    std::string path = "C:\\Users\\Aravo\\OneDrive\\Desktop\\Games";
    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}