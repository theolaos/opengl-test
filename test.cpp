#include <iostream>

int main(int argv, char *argc[]){

    int s {};

    for(int i = 0; 100 >= i; i++){
        s+=i;
    }
    
    std::cout << "hello world "<< s << std::endl;

    return 0;
}