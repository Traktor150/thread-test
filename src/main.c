#include <stdio.h> // gcc main.c; .\a.exe
#include <pthread.h>
// print hello world2 with a new line using a function
void *print_hello_world2()
{
    printf("Hello World2!\n");
    while (1);
}

int main(int argc, char const *argv[])
{
    printf("Hello World!\n");
    // start a new thread to print hello world2
    pthread_t thread;
    pthread_create(&thread, NULL, print_hello_world2, NULL);
    
    // wait for the thread to finish
    pthread_join(thread, NULL);
    
    return 0;
}
