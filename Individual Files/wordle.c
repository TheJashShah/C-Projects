# include <stdio.h>
# include <stdlib.h>

# define TEST "DEATH"

int isPresent(int len, char arr[len], char letter){

    for(int i = 0; i < len; i++){
        if(arr[i] == letter){
            return 1;
        }
    }

    return 0;
}

void check(char word[5], char guess[5]){

    char green[5] = {0};
    int pos = 0;

    int matched[5] = {0};

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(word[i] == guess[j] && i == j){
                printf("%c at %d --> GREEN \n", guess[j], (j + 1));
                green[pos++] = guess[j];
            }
            if(word[i] == guess[j] && i != j && isPresent(pos + 1, green, guess[j]) == 0 && !matched[j]){
                printf("%c at %d --> YELLOW \n", guess[j], (j + 1));
                matched[j] = 1;
            }
        }
    }

    printf("Rest are GREY. \n\n");
}

void Game(){

    int won = 0;

    for(int i = 0; i < 6; i++){

        char guess[6];

        printf("\nEnter your guess[ONLY CAPITAL]: \n");
        scanf("%5s", guess);
        printf("\n");

        if(strcmp(guess, TEST) == 0){
            printf("You have correctly guessed the word! \n");
            won = 1;
            break;
        }
        else{
            check(TEST, guess);
        }

        if(i == 5 && won == 0){
            printf("\nYou Failed to guess %s! \n", TEST);
        }
    }
}

int main(){

    printf("Welcome to Wordle! \n");

    int loop = 1, choice;

    while(loop){
        printf("\n");
        printf("1. A New Game. \n");
        printf("2. Exit. \n");
        printf("\n");

        scanf("%d", &choice);

        switch(choice){

        case 1:{
            Game();
            break;
        }

        case 2:{

            loop = 0;
            break;
        }

        default:{
            printf("Enter an appropriate choice. \n");
            break;
        }

        }
    }

    return 0;
}


/*
QUICK IMPLEMENTATION OF WORDLE AS A TEXT-BASED GAME, HAVE NOT MADE A RANDOM WORD GENERATOR FUCNTION.
*/
