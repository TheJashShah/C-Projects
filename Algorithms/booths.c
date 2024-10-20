#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct{

    int top;
    int arr[MAX_SIZE];

}Stack;

void initialize(Stack * s){
    s->top = -1;
}

int isFull(Stack * s){
    return s->top == MAX_SIZE - 1;
}

int isEmpty(Stack * s){
    return s->top == -1;
}

void push(Stack * s, int data){

    if(isFull(s)){
        printf("FULL\n");
        exit(1);
    }

    s->arr[++(s->top)] = data;
}

int pop(Stack * s){

    if(isEmpty(s)){
        printf("EMPTY\n");
        exit(1);
    }

    return s->arr[(s->top)--];
}

int peek(Stack * s){
    return s->arr[s->top];
}

int get_size(Stack * s){
    return s->top + 1;
}

void printStack(Stack * s){

    for(int i = s->top; i > -1; i--){
        printf("%d", s->arr[i]);
    }
}

void toBinary(Stack * s, int num){

    while(num > 0){
        push(s, (num % 2));
        num = num/2;
    }

    push(s, 0);
}

void getComplement(Stack * s, int num, Stack * num_){

    int bits = get_size(num_);
    int complement = (int)(pow(2, bits)) - num;

    toBinary(s, complement);
    pop(s);
}

void LoadAccumulator(Stack * s, int bits){

    int i = 0;
    while(i < bits){
        push(s, 0);
        i++;
    }
}

void add_arrays(int bits, int accumulator[bits], int arr2[bits]){

    int carry = 0;

    for(int i = bits - 1; i >= 0; i--){
        int temp = accumulator[i];
        accumulator[i] = (accumulator[i] + arr2[i] + carry)%2;
        carry = (temp + arr2[i] + carry)/2;
    }
}

void load_from_stack_to_arr(Stack * s, int bits, int arr[bits]){

    for(int i = 0; i < bits; i++){
        arr[i] = pop(s);
    }
}

void rightShift(int bits, int accumulate[bits], int multiplier[bits]){

    int temp = accumulate[bits - 1];

    for(int i = bits - 1; i > 0; i--){
        accumulate[i] = accumulate[i - 1];
    }
    for(int j = bits - 1; j > 0; j--){
        multiplier[j] = multiplier[j - 1];
    }
    multiplier[0] = temp;
}

void BoothsAlgo(Stack * multiplier, Stack * multiplicand, Stack * complement, int bits){

    int accumulate[bits];
    int multiplier_arr[bits];
    int multiplicand_arr[bits];
    int complement_arr[bits];

    int Q_ = 0;

    for(int a = 0; a < bits; a++){
        accumulate[a] = 0;
    }

    load_from_stack_to_arr(multiplier, bits, multiplier_arr);
    load_from_stack_to_arr(multiplicand, bits, multiplicand_arr);
    load_from_stack_to_arr(complement, bits, complement_arr);

    for(int i = 0; i < bits; i++){
        if(multiplier_arr[bits - 1] == Q_){
            Q_ = multiplier_arr[bits - 1];
            rightShift(bits, accumulate, multiplier_arr);
        }
        else if(Q_ == 1){
            Q_ = multiplier_arr[bits - 1];
            add_arrays(bits, accumulate, multiplicand_arr);
            rightShift(bits, accumulate, multiplier_arr);
        }
        else if(Q_ == 0){
            Q_= multiplier_arr[bits - 1];
            add_arrays(bits, accumulate, complement_arr);
            rightShift(bits, accumulate, multiplier_arr);
        }

        for(int k = 0; k < bits; k++){
            printf("%d", accumulate[k]);
        }
        for(int l = 0; l < bits; l++){
            printf("%d", multiplier_arr[l]);
        }
        printf("  Q: %d  ", Q_);
        printf("\n");
    }
}

int main(){

    Stack multiplier_s;
    Stack multiplicand_s;
    Stack complement_s;
    Stack accumulator;
    Stack temp_;

    initialize(&multiplier_s);
    initialize(&multiplicand_s);
    initialize(&complement_s);
    initialize(&accumulator);
    initialize(&temp_);

    int multiplier, multiplicand;

    printf("Enter the multiplier: \n");
    scanf("%d", &multiplier);

    printf("Enter the multiplicand: \n");
    scanf("%d", &multiplicand);

    if(multiplier < 0 && multiplicand < 0){
        multiplier = -multiplier;
        multiplicand = -multiplicand;
    }

    else if(multiplicand < 0){
    	int temp = multiplicand * -1;

    	toBinary(&temp_, temp);
    	int bits = get_size(&temp_);
    	multiplicand = (int)pow(2, bits) - temp;
    }

    else if(multiplier < 0){
    	int temp = -multiplier;

    	toBinary(&multiplier_s, temp);
    	int bits = get_size(&multiplier_s);
    	multiplier = (int)pow(2, bits) - temp;

    	while(!isEmpty(&multiplier_s)){
    		pop(&multiplier_s);
    	}

    }

    toBinary(&multiplicand_s, multiplicand);
    toBinary(&multiplier_s, multiplier);

    getComplement(&complement_s, multiplicand, &multiplicand_s);

    int diff = (get_size(&multiplier_s) - get_size(&multiplicand_s));

    if(diff > 0){
        for(int i = 0; i < diff; i++){
            push(&multiplicand_s, 0);
            push(&complement_s, 1);
        }
    }
    else if(diff < 0){
        diff = abs(diff);
        for(int i = 0; i < diff; i++){
            push(&multiplier_s, 0);
        }
    }

    printf("Multiplier: \n");
    printStack(&multiplier_s);
    printf("\n");

    printf("Multiplicand: \n");
    printStack(&multiplicand_s);
    printf("\n");

    printf("Complement: \n");
    printStack(&complement_s);
    printf("\n");

    int loops = get_size(&multiplier_s);

    LoadAccumulator(&accumulator, loops);

    printf("Accumulator: \n");
    printStack(&accumulator);

    printf("\n");
    printf("---------------------------------\n");

    BoothsAlgo(&multiplier_s, &multiplicand_s, &complement_s, loops);

    return 0;

}


// THE PROBLEM ARISES WHEN ONE NUMBER IS NEGATIVE AND EITHER OF THE NUMBERS IS GREATER THAN 8.
