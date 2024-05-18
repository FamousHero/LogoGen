#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
/*Takes two arguments:
* The logo to be generated
* whether the file should be a sh or txt
*/
//No need to do so many try-catch blocks. Use blocks only when unexpected occurs (i.e communicating with a 3rd party
// or something neither you nor the user have control over (other device/program, multi-threading, internet based comms).
//Handle the event, i.e reset states, release resources (should be using RAII anyways) so that program doesn't crash/have unexpected side-effect.
//https://youtu.be/Oy-VTqz1_58?t=1553 for a good example

//To see just how expensive try-catch is read https://en.cppreference.com/w/cpp/language/throw

//try-catch is expensive when actual error occurs compared to if-else statements 


//Since this is a command line program i'll keep as is. :)
namespace LogoGen{
    void GenerateLogoFile(int argc, char* argv[])
    {
    //TODO: 
        try{
            if(std::strcmp(argv[1], "txt") != 0 && std::strcmp(argv[1], "sh") != 0){
                throw(std::runtime_error("incorrect file type: Please type txt or sh"));
            }
            
        }
        catch(const std::runtime_error& er){
            std::cerr << er.what() << std::endl;
            std::exit(-1);
        }

        std::cout << "creating file" << std::endl;
        std::ostringstream fileName;
        fileName << argv[0] << "." << argv[1];
        try {
            std::ofstream file(fileName.str());
            if (!std::strcmp(argv[1], "txt"))
            {
                file << "Hello World";
            }
            else if (!std::strcmp(argv[1], "sh"))
            {  
                file << "#! /bin/bash\n\n";
                file << "echo \"Hello World\"";
            }
            file.close();
        }
        //files dont throw exceptions, instead they use flag bits and we check ourself whether raised or not
        catch (...)
        {
            std::exit(-1);
        }
        return;
    }
}

//Takes in 3 args: 1)name of the exe 2) Logo to write 3) the type of file (md or sh)
int main(int argc, char* argv[])
{
//TODO: remove try block. check with an if statement and return 2/-1 otherwise.
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
        return -1;
    }
    //Call file generator with program argument stripped
    LogoGen::GenerateLogoFile(--argc, ++argv);

    return 0;
}