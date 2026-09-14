#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::ifstream originalfile(argv[1]);
    if (!originalfile)
    {
        std::cout << "Error: could not open file " << argv[1] << std::endl;
        return 1;
    }
    std::string content;
    std::string line;
    while (std::getline(originalfile, line))
    {
        content += line + "\n";
    }

    std::string result;
    std::string s1 = argv[2];
    if (s1.empty())
    {
        std::cout << "Error: s1 cannot be empty" << std::endl;
        return 1;
    }
    std::string s2 = argv[3];
    size_t pos = 0;
    size_t found;

    while ((found = content.find(s1, pos)) != std::string::npos)
    {
    result += content.substr(pos, found - pos);
    result += s2;
    pos = found + s1.length();
    }
    result += content.substr(pos);

    std::string filename = argv[1];
    std::string newFilename = filename + ".replace";
    std::ofstream newFile(newFilename.c_str());
    if (!newFile)
    {
        std::cout << "Error: could not create file " << newFilename << std::endl;
        return 1;
    }
    newFile << result;

    return 0;
}