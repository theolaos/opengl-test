#include <iostream>
#include <cstring>


// 68 bytes
struct Person {
    char name[64];
    int age;
};


int main(int argc, char *argv[]){
    int x = 2;

    int *px = &x;

    struct Person people[100];

    struct Person *p_person = (struct Person *)&people;

    for(int i = 0; i < 100; i++){
        p_person->age = i;
        p_person += 1;
    }

    p_person = (struct Person *)&people;

    for(int i = 0; i < 100; i++){
        std::cout << p_person->age << " ";
        p_person += 1;
    }

    std::cout << std::endl;

    char *buffer = new char[8];

    memset(buffer, 1, 8);

    char **ptr = &buffer;

    std::cout << buffer << std::endl;

    delete[] buffer;

    std::cout << x << " " << *px << " " << px << std::endl;
    
    return 0;
}