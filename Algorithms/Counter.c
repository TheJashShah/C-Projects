#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Counter{

    int* key;
    int* count;
    int len;
    int* arr;

}Counter;

int hash(int N, int num){

    return num % N;
}

void initialize(int len, int arr[len], Counter* counter){

    counter->key = (int*)malloc(len * sizeof(int));
    counter->count = (int*)malloc(len * sizeof(int));
    counter->len = len;
    counter->arr = arr;

    for(int i = 0; i < len; i++){
        counter->key[i] = INT_MAX;
        counter->count[i] = 0;
    }
}

int fill_hashmap(Counter* counter){

    int size_of_map = 0;

    for(int i = 0; i < counter->len; i++){
        int num = counter->arr[i];

        int hash_index = hash(counter->len, num);

        if(counter->key[hash_index] == INT_MAX){
            counter->key[hash_index] = num;
            counter->count[hash_index]++;
        }
        else{
            counter->count[hash_index]++;
        }

        size_of_map++;
    }

    return size_of_map;
}

int main(){

    int len;
    printf("Enter the Length of your array: \n");
    scanf("%d", &len);

    int arr[len];
    printf("Enter the elements of your array: \n");

    for(int i = 0; i < len; i++){
        scanf("%d", &arr[i]);
    }

    Counter counter;
    initialize(len, arr, &counter);
    int size = fill_hashmap(&counter);

    printf("The Counter is: \n");
    printf("{\n");
    for(int i = 0; i < counter.len; i++){
        if(counter.key[i] != INT_MAX){
            printf("%d : %d \n", counter.key[i], counter.count[i]);
        }
    }
    printf("}\n");

    return 0;
}

/*
A Program to replicate the Counter() in Python in-built hashmap. Best and Average case is O(N), with the Worst case being O(N^2), and that is for collision.
*/
