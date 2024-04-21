#include <iostream>
#include <limits>
#include <GLFW/glfw3.h>
// struct scene{
//     char[] name;
// };



int main(int argc, char *argv[]){

    //char[10] hello = "Hello World";
    std::cout << "Hello World";

    std::cin.clear(); // reset any error flags

    // ignore any characters in the input buffer until we find an enter character
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    std::cin.get(); // get one more char from the user
    
    return 0;
}