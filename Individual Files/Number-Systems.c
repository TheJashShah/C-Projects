#include<stdio.h>
#include<math.h>

void GetBinary(int num, int ar[1000]){
    int i = 0;

    while(num > 0){
        ar[i] = num % 2;
        num /= 2;
        i++;
    }

    for(int j = i - 1; j >= 0; j--){
        printf("%d", ar[j]);
    }
    printf("\n");
}

void GetOctal(int num, int ar[1000]){
    int i = 0;

    while(num > 0){
        ar[i] = num % 8;
        num /= 8;
        i++;
    }

    for(int j = i - 1; j >= 0; j--){
        printf("%d", ar[j]);
    }
    printf("\n");

}

void GetDecimalFromBinary(long long binary, int ar[100]){
    int x = 0;
    int i = 0;
    long long sum = 0;
    while(binary > 0){
        ar[i] = binary % 10;
        binary /= 10;
        i++;
    }

    for(int j = i - 1; j >= 0; j--){
        if(ar[j] < 0 || ar[j] > 1){
            printf("The number entered is not binary. \n");
            x = 1;
            break;
        }
        else{
            sum += (ar[j])*pow(2, j);
        }
    }

    if(x == 0){
        printf("The decimal equivalent is: %lld\n", sum);
    }

}

void GetDecimalFromOctal(long long octal, int ar[100]){
    int x = 0;
    int i = 0;
    long long sum = 0;
    while(octal > 0){
        ar[i] = octal % 10;
        octal /= 10;
        i++;
    }

    for(int j = i - 1; j >= 0; j--){
        if(ar[j] < 0 || ar[j] > 7){
            printf("The number entered is not octal. \n");
            x = 1;
            break;
        }
        else{
            sum += (ar[j])*pow(8, j);
        }
    }

    if(x == 0){
        printf("The decimal equivalent is: %lld\n", sum);
    }

}


void Reverse(int num, int ar[1000]){
    int i = 0;
    while(num > 0){
        ar[i] = num % 10;
        num /= 10;
        i++;
    }

    for(int j = 0; j < i; j++){
        printf("%d", ar[j]);
    }
}

int main(){

    int num, option;
    int ar[1000];
    int ExitProgram = 0;
    long long num_2;

    while(!ExitProgram){
    printf("\n1. Decimal to Binary.\n");
    printf("2. Decimal to Octal.\n");
    printf("3. Binary  to Decimal.\n");
    printf("4. Octal   to Decimal.\n");
    printf("5. Exit.\n");
    printf("--------------------------\n");
    printf("Enter your option: \n");
    scanf("%d", &option);


    switch(option){

    case 1:{
        printf("Enter your decimal: \n");
        scanf("%d", &num);
        printf("The Binary equivalent is: \n");
        GetBinary(num, ar);
        break;
        }

    case 2:{
        printf("Enter your decimal: \n");
        scanf("%d", &num);
        printf("The Octal equivalent is: \n");
        GetOctal(num, ar);
        break;
        }

    case 3:{
        printf("Enter your Binary \n");
        scanf("%lld", &num_2);
        GetDecimalFromBinary(num_2, ar);
        break;
        }

    case 4:{
        printf("Enter your Octal: \n");
        scanf("%lld", &num_2);
        GetDecimalFromOctal(num_2, ar);
        break;
        }

    case 5:{
        printf("Exiting Program.....\n");
        ExitProgram = 1;
        break;
        }

    default:{
        printf("ENTER AN APPROPRIATE NUMBER. \n");
        break;
        }

    }
}

    return 0;

}

// Finally, Ive got a hang of when and how to use the mod operator.
