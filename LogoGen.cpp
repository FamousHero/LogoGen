#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <limits>
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
        if(std::strcmp(argv[1], "txt") != 0 && std::strcmp(argv[1], "sh") != 0){
           std::cerr << "incorrect file type: Please type txt or sh";
           std::exit(-1);
        }

        std::cout << "creating file" << std::endl;
        std::ostringstream fileName;
        fileName << argv[0] << "." << argv[1];
        //files dont throw exceptions, instead they use flag bits and we check ourself whether raised or not
        //if you really care check the flags
        std::ofstream file(fileName.str());
        //Letters begin at row 6, and are separated every 7 lines
        //to get to the start of any letter just take 6 + 7 *(letter index)
        std::ifstream formatFile("Letter Format.txt");

        if(file.is_open() && formatFile.is_open())
        {
            std::string text = "";
            char* charp = argv[0];
            for(int i = 0; i < 6; ++i)
            {
                if(!std::strcmp(argv[1], "sh")){
                    text += "echo \"";
                }
                char* tcp = charp;
                while (*tcp)
                {
                    //Iterate through each character, and write its corresponding text to temp base on current row i    
                    int letterIndex = std::tolower(*tcp) - 'a';
                    std::string temp;
                    if(letterIndex == 32 - 97){ //Only Non-Alpha character allowed is ' ' (Can add # in future)

                        temp += "    ";
                    }
                    else if(letterIndex < 0 ||letterIndex > 26){
                        ++tcp;
                        continue;
                    }
                    else{
                        int filePosition = 5 + 7 * letterIndex + i;
                        while (filePosition != 0){
                            formatFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            --filePosition;
                        }
                        std::getline(formatFile, temp, '\r');
                    }
                    text = text + temp + " ";

                    formatFile.seekg(0, formatFile.beg);
                    ++tcp;
                }
                if(!std::strcmp(argv[1], "sh")){
                    text += "\"";
                }
                text += "\n";   
            }
            std::cout << "final text is: \n" << text << std::endl;
            



            if (!std::strcmp(argv[1], "txt"))
            {
                file << text;
            }
            else if (!std::strcmp(argv[1], "sh"))
            {
                file << "#! /bin/bash\n\n";
                file << text; //"echo \"Hello World\"";
            }
            file.close();
            
        }
        else {
            std::cerr << "File could not be opened";
            std::exit(-1);
        }
        
    }
}

//Takes in 3 args: 1)name of the exe 2) Logo to write 3) the type of file (md or sh)
int main(int argc, char* argv[])
{
//TODO: remove try block. check with an if statement and return 2/-1 otherwise.
    if(argc != 3)
    {
        std::cerr << "Program requires 2 arguments provided " << argc;
        return -1;
    }
    //Call file generator with program argument stripped
    LogoGen::GenerateLogoFile(--argc, ++argv);

    return 0;
}