#include <stdio.h> // gcc main.c; .\a.exe

// print hello world2 with a new line using a function
void print_hello_world2()
{
    printf("Hello World2!\n");
}

int main(int argc, char const *argv[])
{
    printf("Hello World!\n");
    print_hello_world2();
    return 0;
}
