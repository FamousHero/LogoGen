#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
/*Takes two arguments:
* The logo to be generated
* whether the file should be a sh or txt
*/

namespace LogoGen{
    void GenerateLogoFile(int argc, char* argv[])
    {
        try{
            if(std::strcmp(argv[1], "txt") != 0 && std::strcmp(argv[1], "sh") != 0){
                throw(std::runtime_error("incorrect file type: Please type txt or sh"));
            }
        }
        catch(const std::runtime_error& er){
            std::cerr << er.what() << std::endl;
            throw;
        }
        if(!std::strcmp(argv[1], "txt"))
        {
            std::cout << "creating file" << std::endl;
            std::ostringstream fileName;
            fileName <<  argv[0] << "." << argv[1];
            std::ofstream file(fileName.str());
            file << "Hello World";
            file.close();
        }
        else if(!std::strcmp(argv[1], "sh"))
        {
            std::cout << "creating file" << std::endl;
            std::ostringstream fileName;
            fileName <<  argv[0] << "." << argv[1];
            std::ofstream file(fileName.str());
            file << "#! /bin/bash\n\n";
            file << "echo \"Hello World\"";
            file.close();

        }
        return;
    }
}

int main(int argc, char* argv[])
{
    try{
        if(argc != 3)
        {
            std::ostringstream errMsg;
            errMsg << "Program requires 2 arguments provided " << argc;
            throw(std::runtime_error(errMsg.str()));
        }
    }
    catch(const std::runtime_error& er){
        std::cerr << er.what() << std::endl;
        throw;
    }
    //Call file generator with program argument stripped
    LogoGen::GenerateLogoFile(--argc, ++argv);

    return 0;
}