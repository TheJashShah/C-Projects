#include <stdio.h>
#include <stdlib.h>

void Load_Board(int board[][9], int set_rows[30], int set_cols[30]){

    FILE *ptr = fopen("sudoku.txt", "r");

    if(ptr == NULL){
        printf("error.\n");
        exit(1);
    }

    int num, row, col;

    for(int i = 0; i < 30; i++){
        fscanf(ptr, "%d %d %d", &num, &row, &col);
        board[row][col] = num;
        set_rows[i] = row;
        set_cols[i] = col;
    }

    fclose(ptr);
}

void printBoard(int board[][9]){

    printf("\nDisplaying Board...\n");

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                printf("|    ");
            }
            else{
                printf("| %2d ", board[i][j]);
            }
        }
        printf("\n---------------------------------------------\n");
    }
}

void calculate_bound(int pos, int *lower, int *upper){

    int mod = (pos % 3);

    switch(mod){
    case 0:
        *lower = pos;
        *upper = (pos + 2);
        break;

    case 1:
        *lower = (pos - 1);
        *upper = (pos + 1);
        break;

    case 2:
        *lower = (pos - 2);
        *upper = pos;
        break;
    }
    //CALCULATING INITIAL AND FINAL VALUES TO USE IN FOR LOOP TO CHECK FOR VALIDITY IN A (3x3) GRID.
}

int validPosition(int num, int row, int col, int board[][9]){

    for(int i = 0; i < 9; i++){
        if(board[row - 1][i] == num){
            return 0;
        }
    }// ROW

    for(int j = 0; j < 9; j++){
        if(board[j][col - 1] == num){
            return 0;
        }
    }
    // COLUMN

    int row_lower, row_upper, col_lower, col_upper;

    int arr_row = (row - 1);
    int arr_col = (col - 1);

    calculate_bound(arr_row, &row_lower, &row_upper);
    calculate_bound(arr_col, &col_lower, &col_upper);

    for(int a = row_lower; a <= row_upper; a++){
        for(int b = col_lower; b <= col_upper; b++){
            if(board[a][b] == num){
                return 0;
            }
        }
    }
    // BOX

    return 1;
}

void TakeInput(int board[][9], int *moves, int rows[30], int cols[30]){

    int num, row, col;

    printf("Enter row[1-9]: \n");
    scanf("%d", &row);
    printf("Enter column[1-9]: \n");
    scanf("%d", &col);

    int flag = 0;

    for(int i = 0; i < 30; i++){
        if(rows[i] == (row - 1) && cols[i] == (col - 1)){
            flag = 1;
            break;
            // USER CAN ONLY CHANGE THE NUMBER WHICH WAS INPUT BY THE USER, NOT AN INITIAL NUMBER.
        }
        else{
            flag = 0;
        }
    }

    if(flag){
        printf("You cannot change an initial number.\n");
        TakeInput(board, moves, rows, cols);
    }
    else{
        printf("Enter a number[1-9]: \n");
        scanf("%d", &num);

        if(validPosition(num, row, col, board)){
            board[row - 1][col - 1] = num;
        }
        else{
            printf("Wrong Move.\n");
            TakeInput(board, moves, rows, board);
        }
    }

    printBoard(board);
    (*moves)++;
}


int SolveSudoku(int board[][9], int row, int col){

    if(row == 8 && col == 9){
        return 1;
    }

    if(col == 9){
        row++;
        col = 0;
    }

    if(board[row][col] != 0){
        return SolveSudoku(board, row, col + 1);
    }

    for(int i = 1; i  <= 9; i++){
        if(validPosition(i, row + 1, col + 1, board)){
            board[row][col] = i;

            if(SolveSudoku(board, row, col + 1)){
                return 1;
            }
        }
        board[row][col] = 0;
    }

    return 0;

// NAIVE APPROACH - USED RECURSIVE BACKTRACKING
}

int Counter(int board[][9]){

    int counter = 0;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                counter++;
            }
        }
    }

    return counter;
}

int main(){

    int board[9][9] = {0};
    int set_rows[30];
    int set_cols[30];

    Load_Board(board, set_rows, set_cols);

    int moves = 0, choice;

    printf("\n-----Welcome to Sudoku Console!-----\n");
    printf("-----This is a solvable board.------\n");

    printBoard(board);
    printf("\n");

    printf("1. Solve it Yourself.\n");
    printf("2. Let the Computer Solve.\n");
    scanf("%d",&choice);

    switch(choice){

    case 1:
        while(Counter(board) != 0){
            TakeInput(board, &moves, set_rows, set_cols);
        }

        printf("\nYou completed the Game in %d moves.\n", moves);
        break;

    case 2:

        if(SolveSudoku(board, 0, 0)){
            printBoard(board);
            printf("\nThe Board is solved.\n");
        }else{
            printf("The Board is not solvable.\n");
        }
        break;

    default:
        printf("Enter a proper number.\n");
        break;
    }

    return 0;
}
