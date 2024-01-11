#include <stdio.h>
#include <string.h>

struct Inventory {
    char name[20];
    int quant;
    int price;
};

void Display_Inventory(int size, struct Inventory Inv[size]) {
    printf("NAME----QUANT----PRICE\n");
    for (int i = 0; i < size; i++) {
        printf("%s    | %d    | %d\n", Inv[i].name, Inv[i].quant, Inv[i].price);
    }
    printf("--------------------------------\n");
}

int GetValue(int size, struct Inventory Inv[size]){
    int value = 0;
    for (int i = 0; i < size; i++) {
        value += (Inv[i].quant * Inv[i].price);
    }
    return value;
}

void ChangeInventory(int size, struct Inventory Inv[size]){
    printf("The current Inventory is: \n");
    Display_Inventory(size, Inv);

    int index, new_price, new_quant;
    printf("Enter the index of the product you want to change: \n");
    scanf("%d", &index);
    printf("Enter the new price: \n");
    scanf("%d", &new_price);
    printf("Enter the new quantity: \n");
    scanf("%d", &new_quant);

    Inv[index - 1].price = new_price;
    Inv[index - 1].quant = new_quant;

    printf("\nThe new inventory is: \n");
    Display_Inventory(size, Inv);
}

int main() {
    int size;
    int InfiniteLoop = 1;
    int option;

    printf("Enter the initial size of your inventory: \n");
    scanf("%d", &size);

    struct Inventory Inv[size];

    printf("Fill your inventory, for the first time.\n");
    printf("NAME----QUANT----PRICE\n");
    for (int i = 0; i < size; i++) {
        scanf("%s %d %d", Inv[i].name, &Inv[i].quant, &Inv[i].price);
    }
    printf("--------------------------------\n");

    printf("\nInitially, your inventory is: \n");
    Display_Inventory(size, Inv);

    while(InfiniteLoop){
        printf("1. Get the value of the Inventory. \n");
        printf("2. Change the details of a product in the Inventory. \n");
        printf("3. Exit. \n");
        printf("\nEnter your choice: \n");
        scanf("%d", &option);

        switch(option){
        case 1:
            {
                printf("Your Inventory is: \n");

                Display_Inventory(size, Inv);

                printf("\nThe current cost is: %d\n", GetValue(size, Inv));
                printf("\n");
                break;
            }
        case 2:
            {
                ChangeInventory(size, Inv);
                break;
            }
        case 3:
            {
                printf("Exiting Program.....\n");
                InfiniteLoop = 0;
                break;
            }
        default:
            {
                printf("Enter an appropriate number. \n");
                break;
            }
        }
    }

    return 0;
}
