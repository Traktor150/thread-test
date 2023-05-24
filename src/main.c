#include <stdio.h> // gcc main.c; .\a.exe
#include <stdlib.h> // malloc
#include <pthread.h>

// create a global lock
pthread_mutex_t lock;


// print hello world2 with a new line using a function
void *print_hello_world2()
{
    printf("Hello World2!\n");
    // while (1);
    return NULL;
}

// count to 1000000 safe
void *count_to_1000000_safe(void *num){
    int *num_ptr = (int *)num;
    for (int i = 0; i < 1000000; i++)
    {
        // lock the lock
        pthread_mutex_lock(&lock);
        *num_ptr += 1;
        // unlock the lock
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

// count to 1000000
void *count_to_1000000(void *num){
    int *num_ptr = (int *)num;
    for (int i = 0; i < 1000000; i++)
    {
        *num_ptr += 1;
    }
    return NULL;
}


// #pragma pack(push, 1)
// typedef struct
// {
//     int a;
//     int b;
//     char c[10];
// } test_struct;
// #pragma pack(pop)

// void print_read_as_int(void *args)
// {
//     int *num = (int *)args;
//     printf("num: %d\n", *num);
// }

int main(int argc, char const *argv[])
{
    printf("Hello World!\n");
    // start a new thread to print hello world2
    pthread_t thread;
    pthread_create(&thread, NULL, print_hello_world2, NULL);
    
    // wait for the thread to finish
    pthread_join(thread, NULL);

    // test_struct *stru = (test_struct *)malloc(sizeof(test_struct));
    // printf("num: %lld\n", sizeof(char));
    // printf("num: %lld\n", sizeof(int));
    // printf("num: %lld\n", sizeof(test_struct));

    // stru->a = 42;
    // stru->b = 2;
    
    // use loop to fill the rest of the array with the the alphabet
    // for (int i = 0; i < 10; i++)
    // {
    //     stru->c[i] = 'a' + i;
    // }

    // print_read_as_int(stru);

    // init the lock
    pthread_mutex_init(&lock, NULL);

    int num = 0;
    pthread_t thread2_safe;
    pthread_t thread3_safe;
    pthread_create(&thread2_safe, NULL, count_to_1000000_safe, &num);
    pthread_create(&thread3_safe, NULL, count_to_1000000_safe, &num);
    
    // wait for the thread to finish
    pthread_join(thread2_safe, NULL);
    pthread_join(thread3_safe, NULL);
    printf("safe num should be 2000000\n");
    printf("num: %d\n", num);

    // without lock
    int num2 = 0;
    pthread_t thread2;
    pthread_t thread3;
    pthread_create(&thread2, NULL, count_to_1000000, &num2);
    pthread_create(&thread3, NULL, count_to_1000000, &num2);
    
    // wait for the thread to finish
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    printf("unsafe num should be 2000000\n");
    printf("num: %d\n", num2);

    
    return 0;
}
