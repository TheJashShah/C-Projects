#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
    int num, guess;
    int tries = 0;

    srand(time(0));
    num = rand() % 100 + 1;

    printf("Guess the number!");
    printf("\n NOTE: The number will be a positive integer less than or equal to 100.\n");

    do{
        printf("Enter your guess: \n");
        scanf("%d", &guess);
        tries++;

        if(guess < num){
            printf("\nLOW! Try again.\n");
        }
        else if(guess > num){
            printf("\nHIGH! Try again.\n");
        }
        else{
            printf("\nCongratulations! You got it correct in %d tries.\n", tries);
        }

    }while(guess != num);

    return 0;
}

//I've finally learned how to generate a random number, and also how to use a do-while.
