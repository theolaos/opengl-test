#include <stdio.h>

struct Person{
    char name[64];
    int age;
}

int main(int argc, char *argv[]){
    struct Person people[100];
    struct Person *p_Person = &people;
}