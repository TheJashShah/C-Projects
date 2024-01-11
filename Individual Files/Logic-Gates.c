#include<stdio.h>

int AND(int a, int b){
    return(a & b);
}

int OR(int a, int b){
    return(a | b);
}

int NAND(int a, int b){
    return(!AND(a, b));
}

int NOR(int a, int b){
    return(!OR(a, b));
}

int EX_OR(int a, int b){
    return(OR(AND(!a, b), AND(a, !b)));
}

int EX_NOR(int a, int b){
    return(OR(AND(!a, !b), AND(a, b)));
}

void get_num(int arr[4]){
    for(int i = 0; i < 4; i++){
        scanf("%d", &arr[i]);
    }
}

int main(){

    printf("1. AND.\n");
    printf("2. OR.\n");
    printf("3. NAND.\n");
    printf("4. NOR.\n");
    printf("5. EX-OR.\n");
    printf("6. EX-NOR.\n");

    int option;

    printf("Enter your choice: \n");
    scanf("%d", &option);

    int arr_a[4];
    int arr_b[4];

    switch(option){
    case 1:{
        printf("Enter all desired values of a: \n");
        get_num(arr_a);
        printf("Enter all desired values of b: \n");
        get_num(arr_b);

        printf("The Table is: \n");

        printf("\nA | B | Y\n");
        for(int i = 0; i < 4; i++){
            printf("%d   %d   %d \n", arr_a[i], arr_b[i], AND(arr_a[i], arr_b[i]));
        }
        break;
    }

    case 2:{
        printf("Enter all desired values of a: \n");
        get_num(arr_a);
        printf("Enter all desired values of b: \n");
        get_num(arr_b);

        printf("The Table is: \n");

        printf("\nA | B | Y\n");
        for(int i = 0; i < 4; i++){
            printf("%d   %d   %d \n", arr_a[i], arr_b[i], OR(arr_a[i], arr_b[i]));
        }
        break;
    }

    case 3:{
        printf("Enter all desired values of a: \n");
        get_num(arr_a);
        printf("Enter all desired values of b: \n");
        get_num(arr_b);

        printf("The Table is: \n");

        printf("\nA | B | Y\n");
        for(int i = 0; i < 4; i++){
            printf("%d   %d   %d \n", arr_a[i], arr_b[i], NAND(arr_a[i], arr_b[i]));
        }
        break;
    }

    case 4:{
        printf("Enter all desired values of a: \n");
        get_num(arr_a);
        printf("Enter all desired values of b: \n");
        get_num(arr_b);

        printf("The Table is: \n");

        printf("\nA | B | Y\n");
        for(int i = 0; i < 4; i++){
            printf("%d   %d   %d \n", arr_a[i], arr_b[i], NOR(arr_a[i], arr_b[i]));
        }
        break;
    }

     case 5:{
        printf("Enter all desired values of a: \n");
        get_num(arr_a);
        printf("Enter all desired values of b: \n");
        get_num(arr_b);

        printf("The Table is: \n");

        printf("\nA | B | Y\n");
        for(int i = 0; i < 4; i++){
            printf("%d   %d   %d \n", arr_a[i], arr_b[i], EX_OR(arr_a[i], arr_b[i]));
        }
        break;
    }

     case 6:{
        printf("Enter all desired values of a: \n");
        get_num(arr_a);
        printf("Enter all desired values of b: \n");
        get_num(arr_b);

        printf("The Table is: \n");

        printf("\nA | B | Y\n");
        for(int i = 0; i < 4; i++){
            printf("%d   %d   %d \n", arr_a[i], arr_b[i], EX_NOR(arr_a[i], arr_b[i]));
        }
        break;
    }

    default:{
        printf("Enter an appropriate number. \n");
        break;
    }

    }

    return 0;
}
