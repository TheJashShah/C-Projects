/*
    DEALER GETS TWO CARDS - ONE UP, ONE DOWN.
    EACH PLYER GETS TWO CARDS, BOTH FACE UP.
    EACH PLAYER IS ASKED TO HIT, OR STAND.

    IF PLAYER > DEALER, OR DEALER GETS BUST, PLAYER WINS.
    IF PLAYER GETS BLACKJACK, PLAYER IS PAID 3/2 TIMES.
    IF PLAYER == DEALER == BLACKJACK, NO CHANGE.

    IF PLAYER < DEALER, OR PLAYER GETS BUST, DEALER WINS.

    INITIALLY, --- ONLY ONE PLAYER GAME.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK 52

typedef struct card{

    char suit[10];
    char value[3];
    int numerical_val;

}card;

typedef struct Person{

    int pool;
    card Cards[3];

}Person;

void LoadFromFile(card Deck[DECK]){

    FILE *ptr = fopen("cards.txt", "r");

    if(ptr == NULL){
        printf("Error in Loading Cards.");
        return;
    }

    for(int i = 0; i < DECK; i++){
        fscanf(ptr, "%s %s %d", Deck[i].suit, Deck[i].value, &Deck[i].numerical_val);
    }

    fclose(ptr);

    for(int i = 0; i < DECK; i++){

        if(Deck[i].numerical_val > 10 && Deck[i].numerical_val < 14){
            Deck[i].numerical_val = 10;
        }
        else if(Deck[i].numerical_val == 14){
            Deck[i].numerical_val = 11;
        }
    }
}

int generateRandom(){

    return rand() % 52;
}

void GiveInitialCards(card Deck[DECK], Person *Dealer, Person *player){

    int indices[6] = {-1, -1, -1, -1, -1, -1};

    int distributed = 0;

    while(distributed != 3){
        int index = generateRandom();

        if(!Find(indices, index)){
            player->Cards[distributed] = Deck[index];
            indices[distributed] = index;
            distributed++;
        }
    }

    while(distributed != 6){
        int index = generateRandom();

        if(!Find(indices, index)){
            Dealer->Cards[distributed - 3] = Deck[index];
            indices[distributed] = index;
            distributed++;
        }
    }
}

int Find(int indices[6], int num){

    for(int i = 0; i < 6; i++){
        if(indices[i] == num){
            return 1;
        }
    }
    return 0;
}

void PrintInitialCards(Person *Dealer, Person *player){

    printf("Dealer's Card: \n");
    printf("%s OF %s and 2 cards kept down. \n", Dealer->Cards[0].value, Dealer->Cards[0].suit);
    printf("\n");

    printf("Player's Card: \n");
    printf("\n");
    for(int i = 0; i < 2; i++){
        printf("%s OF %s.\n", player->Cards[i].value, player->Cards[i].suit);
    }
}

void PrintPlayerThirdCard(Person player){

    printf("\n");
    printf("Your Third Card is: %s OF %s. \n", player.Cards[2].value, player.Cards[2].suit);
    printf("\n");

}

void DealerCards(Person Dealer){

    printf("\n");
    printf("The Dealer's Next Two Cards are: \n");
    for(int i = 1; i < 3; i++){
        printf("%s OF %s. \n", Dealer.Cards[i].value, Dealer.Cards[i].suit);
    }
    printf("\n");
}

int getValueOfCards(Person person){

    int value = 0;

    for(int i = 0; i < 3; i++){
        value += (person.Cards[i].numerical_val);
    }

    return value;
}

void DisplayTable(Person player, Person Dealer, int round){

    printf("\n");
    printf("|---NAME---|---POOL---| \n");
    printf("| Player   |  %-4d \n", player.pool);
    printf("| Dealer   |  %-4d \n", Dealer.pool);
    printf("----------------------- \n");
    printf("\n");

}

int main(){

    srand(time(NULL));

    card Deck[DECK];
    LoadFromFile(Deck);

    Person player;
    Person Dealer;

    printf("Welcome to BlackJack!\n");
    int pool;

    printf("\n");

    printf("Enter the amount in your pool[The Dealer will have twice as much]: \n");
    scanf("%d", &pool);

    player.pool = pool;
    Dealer.pool = (2 * pool);

    int loop = 1, choice, rounds = 0;

    DisplayTable(player, Dealer, 0);

    while(loop && player.pool > 0 && Dealer.pool > 0){
        printf("\n");
        printf("1. A New BlackJack Game.\n");
        printf("2. Exit.\n");
        printf("\n");

        scanf("%d", &choice);

        if(player.pool <= 0){
            printf("Sorry, you're out of money.\n");
            loop = 0;
        }

        if(Dealer.pool <= 0){
            printf("The Dealer is out of money. You Win! \n");
            loop = 0;
        }

        switch(choice){

            case 1:{

                rounds++;

                int bet;
                printf("Player, enter your bet: \n");
                scanf("%d", &bet);
                printf("\n");

                if(bet > player.pool){
                    printf("Enter an amount under or equal to your pool.");
                    printf("\n");
                    break;
                }

                GiveInitialCards(Deck, &Dealer, &player);

                int PlayVal = getValueOfCards(player);
                int DealerVal = getValueOfCards(Dealer);

                PrintInitialCards(&Dealer, &player);

                printf("\n");

                char option;
                printf("Player, do you want to hit or stand[H/S]: \n");
                scanf(" %c", &option);

                if(option == 'H'){
                    PrintPlayerThirdCard(player);
                    DealerCards(Dealer);
                }
                else if(option == 'S'){
                    DealerCards(Dealer);
                    PlayVal -= player.Cards[2].numerical_val;
                }
                else{
                    printf("Enter an appropriate option. \n");
                    break;
                }

                if(PlayVal == DealerVal){
                 player.pool -= 0;
                 Dealer.pool -= 0;
                }
                else if(PlayVal == 21 && DealerVal == 21){
                    player.pool -= 0;
                    Dealer.pool -= 0;
                }
                else if(PlayVal == 21){
                    player.pool += (1.5 * bet);
                    Dealer.pool -= (1.5 * bet);
                }
                else if(PlayVal > DealerVal || DealerVal > 21){
                    player.pool += bet;
                    Dealer.pool -= bet;
                }
                else if(PlayVal < DealerVal || PlayVal < 21){
                    player.pool -= bet;
                    Dealer.pool += bet;
                }

                printf("The Dealer scores %d and the Player scores %d. \n", DealerVal, PlayVal);

                DisplayTable(player, Dealer, rounds);

                break;
            }

            case 2:{
                printf("Thank you for Playing!");
                loop = 0;
                break;
            }

            default:{
                printf("Enter an appropriate number.");
                break;
            }
        }
    }

    return 0;
}
