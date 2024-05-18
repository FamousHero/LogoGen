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
        std::cout << argc << " " << argv[0] << std::endl;
        std::cout << argc << " " << argv[1] << std::endl;

            std::cout << "creating file" << std::endl;
            std::ostringstream fileName;
            fileName <<  argv[0] << "." << argv[1];
            std::ofstream file(fileName.str());
            file << "Hello World";
            file.close();
        
        return;
    }
}

int main(int argc, char* argv[])
{
    try{
        if(argc != 3)
        {
            std::ostringstream errMsg;
            errMsg << "Program requires 2 arguments\nLogo Text\nFile Type (sh or txt) provided " << argc;
            throw(std::runtime_error(errMsg.str()));
        }
    }
    catch(const std::runtime_error& er){
        std::cout << er.what() << std::endl;
    }
    //Call file generator with program argument stripped
    LogoGen::GenerateLogoFile(--argc, ++argv);

    return 0;
}