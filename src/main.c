#include <stdio.h> // gcc main.c; .\a.exe
#include <stdlib.h> // malloc
// #include <pthread.h>

// print hello world2 with a new line using a function
void *print_hello_world2()
{
    printf("Hello World2!\n");
    while (1);
}

#pragma pack(push, 1)
typedef struct
{
    int a;
    int b;
    char c[10];
} test_struct;
#pragma pack(pop)

void print_read_as_int(void *args)
{
    int *num = (int *)args;
    printf("num: %d\n", *num);
}

int main(int argc, char const *argv[])
{
    printf("Hello World!\n");
    // start a new thread to print hello world2
    // pthread_t thread;
    // pthread_create(&thread, NULL, print_hello_world2, NULL);
    
    // wait for the thread to finish
    // pthread_join(thread, NULL);

    test_struct *stru = (test_struct *)malloc(sizeof(test_struct));
    printf("num: %lld\n", sizeof(char));
    printf("num: %lld\n", sizeof(int));
    printf("num: %lld\n", sizeof(test_struct));

    stru->a = 42;
    stru->b = 2;
    
    // use loop to fill the rest of the array with the the alphabet
    for (int i = 0; i < 10; i++)
    {
        stru->c[i] = 'a' + i;
    }

    print_read_as_int(stru);
    
    return 0;
}
