#include<stdio.h>
#include<string.h>
#include<stdbool.h>

void DisplayBoard(char board[10]){
    printf("The Board is: \n");

    printf("%c  | %c  | %c\n", board[1], board[2], board[3]);
    printf("---|--- |---\n");
    printf("%c  | %c  | %c\n", board[4], board[5], board[6]);
    printf("---|--- |---\n");
    printf("%c  | %c  | %c\n", board[7], board[8], board[9]);
    printf("---|--- |---\n");
}

int count(char board[10]){
    int count_ = 0;
    for(int i = 0; i < 10; i++){
        if(board[i] == ' '){
            ++count_;
        }
    }
    return count_;
}

void Get_Player_one_input(char board[10], char L_1, char L_2){
    int pos, pos_2;
    printf("Player 1, Enter the position where you'd want to place your marker: \n");
    scanf("%d", &pos);
    if(board[pos] == L_2){
        printf("There is already a marker present there!\n");
        printf("Enter another position:\n");
        scanf("%d", &pos_2);
        board[pos_2] = L_1;
    }
    else{
     board[pos] = L_1;
    }
    DisplayBoard(board);
}

void Get_Player_two_input(char board[10], char L_2, char L_1){
    int pos, pos_2;
    printf("Player 2, Enter the position where you'd want to place your marker: \n");
    scanf("%d", &pos);
    if(board[pos] == L_1){
        printf("There is already a marker present there!\n");
        printf("Enter another position:\n");
        scanf("%d", &pos_2);
        board[pos_2] = L_2;
    }
    else{
     board[pos] = L_2;
    }
    DisplayBoard(board);
}


int Check_Player_1_Wins(char board[10], char letter){
    if((board[1] == letter && board[2] == letter && board[3] == letter) || (board[4] == letter && board[5] == letter && board[6] == letter) || (board[7] == letter && board[8] == letter && board[9] == letter) || (board[1] == letter && board[4] == letter && board[7] == letter) || (board[2] == letter && board[5] == letter && board[8] == letter) || (board[3] == letter && board[6] == letter && board[9] == letter) || (board[1] == letter && board[5] == letter && board[9] == letter) || (board[3] == letter && board[5] == letter && board[7] == letter)){
        return 1;
    }
    else{
        return 0;
    }
}


int Check_Player_2_Wins(char board[10], char letter){
    if((board[1] == letter && board[2] == letter && board[3] == letter) || (board[4] == letter && board[5] == letter && board[6] == letter) || (board[7] == letter && board[8] == letter && board[9] == letter) || (board[1] == letter && board[4] == letter && board[7] == letter) || (board[2] == letter && board[5] == letter && board[8] == letter) || (board[3] == letter && board[6] == letter && board[9] == letter) || (board[1] == letter && board[5] == letter && board[9] == letter) || (board[3] == letter && board[5] == letter && board[7] == letter)){
        return 1;
    }
    else{
        return 0;
    }
}

int Check_For_Draw(char board[10], char L_1, char L_2){
    if((Check_Player_1_Wins(board, L_1) == 0) && (Check_Player_2_Wins(board, L_2) == 0) && (count(board) == 1)){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    int InfiniteLoop = 1;
    int option;
    char Letter_1, Letter_2;

    printf("Welcome to Terminal Tic-Tac-Toe!\n");
    while(InfiniteLoop){
        printf("Choose Your Option.\n");
        printf("1. Two-Player Tic-Tac-Toe.\n");
        printf("2. Exit.\n");
        scanf("%d", &option);

        switch(option){
        case 1:
            {
                bool GameOver = false;
                char Board[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                int cycle = 0;
                printf("Player 1, enter your letter:(X/O)\n");
                scanf(" %c", &Letter_1);

                if(Letter_1 == 'X'){
                    Letter_2 = 'O';
                }
                else if(Letter_1 == 'O'){
                    Letter_2 = 'X';
                }
                else{
                    printf("Input an appropriate letter.\n");
                }

                printf("%c represents Player one, while %c represents Player two.\n", Letter_1, Letter_2);

                DisplayBoard(Board);

                do{
                    Get_Player_one_input(Board, Letter_1, Letter_2);

                    if(Check_Player_1_Wins(Board, Letter_1) == 1){
                        printf("Player one wins!\n");
                        GameOver = true;
                        break;
                    }

                    if(Check_Player_2_Wins(Board, Letter_2) == 1){
                        printf("Player two wins!\n");
                        GameOver = true;
                        break;
                    }

                    if(Check_For_Draw(Board, Letter_1, Letter_2) == 1){
                        printf("Its a draw!\n");
                        GameOver = true;
                        break;

                    }

                    Get_Player_two_input(Board, Letter_2, Letter_1);

                    if(Check_Player_1_Wins(Board, Letter_1) == 1){
                        printf("Player one wins!\n");
                        GameOver = true;
                        break;
                    }

                    if(Check_Player_2_Wins(Board, Letter_2) == 1){
                        printf("Player two wins!\n");
                        GameOver = true;
                        break;
                    }

                    if(Check_For_Draw(Board, Letter_1, Letter_2) == 1){
                        printf("Its a draw!\n");
                        GameOver = true;
                        break;

                    }

                }while(GameOver != true);

                break;
            }
        case 2:
            {
                printf("Exiting Game.....");
                InfiniteLoop = 0;
                break;
            }
        default:
            {
                printf("Enter an appropriate option.\n");
                break;
            }

        }
    }

    return 0;
}

// Somehow, this feels a lot cooler than the one I made in python.
