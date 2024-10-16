#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TASKS 15

typedef struct{

    int priority;
    char task[100];
    int isComplete;
    int id;

}Task;

int read_from_file(Task list[MAX_TASKS]){

    FILE *ptr = fopen("file.txt", "r");

    if(ptr == NULL){
        printf("No such file found.\n");
        return;
    }

    char content[100];
    int priority;
    int completed;
    int i = 0;

    while(fgets(content, sizeof(content), ptr) != NULL){
        if(sscanf(content, "\"%[^\"]\" %d %d", content, &priority, &completed) == 3){
            if(strcmp(content, "") != 0){
               strncpy(list[i].task, content, 100);
                list[i].priority = priority;
                list[i].isComplete = completed;
                list[i].id = generate_id();
            }
            else{
                i--;
            }
        }
        i++;
    }

    fclose(ptr);

    return i;
}

void write_to_file(Task list[MAX_TASKS], int num_tasks){
    FILE *ptr = fopen("file.txt", "w");

    if(ptr == NULL){
        printf("No such file found.\n");
        return;
    }

    for(int i = 0; i < num_tasks; i++){
        fprintf(ptr, "\"%s\" %d %d\n", list[i].task, list[i].priority, list[i].isComplete);
    }

    fclose(ptr);
}

int generate_id(){
    int N = 10000;

    int id = rand() % N + 1;

    return id;
}

void display_list(Task list[MAX_TASKS], int num_tasks){

    char completed[10];

    printf("\n| %-40s | %-10s | %-10s | %-10s |\n", "TASK", "PRIORITY", "COMPLETED", "ID");
    printf("|------------------------------------------|------------|------------|------------|\n");

    for(int i = 0; i < num_tasks; i++){
        if (list[i].isComplete == 0){
            strncpy(completed, "False", 10);
        }
        else{
            strncpy(completed, "True", 10);
        }

        printf("| %-40s | %-10d | %-10s | %-10d |\n", list[i].task, list[i].priority, completed, list[i].id);
    }

    printf("|------------------------------------------|------------|------------|------------|\n");
}

void update_priority(Task list[MAX_TASKS], int num_tasks){

    for(int i = 0; i < num_tasks; i++){
        for(int j = i+1; j < num_tasks; j++){
            if(list[i].priority > list[j].priority){
                Task temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

void delete_task(Task list[MAX_TASKS], int num_tasks, int index){

    for(int i = index; i < num_tasks - 1; i++){
        list[i] = list[i + 1];
    }
}

int main(){

    Task list[MAX_TASKS];

    int loop = 1, choice, num_tasks = 0, id, index = -1;

    bool flag = false;
    char update;

    num_tasks = read_from_file(list);

    while(loop == 1){
        printf("\n");
        printf("1. Add Task.\n");
        printf("2. Update a particular Task.\n");
        printf("3. Delete a particular Task.\n");
        printf("4. Watch the List.\n");
        printf("5. Exit.\n");

        scanf("%d", &choice);

        switch(choice){
        case 1:

            getchar();
            printf("Enter the task: \n");
            scanf("%[^\n]%*c", list[num_tasks].task);

            printf("\nEnter the priority: [1-5]\n");
            scanf("%d", &list[num_tasks].priority);

            list[num_tasks].isComplete = 0;
            list[num_tasks].id = generate_id();

            printf("The Task with id %d is added.\n", list[num_tasks].id);
            num_tasks++;

            break;

        case 2:

            printf("Enter ID: \n");
            scanf("%d", &id);

            for(int i = 0; i < num_tasks; i++){

                if(list[i].id == id){
                    flag = true;
                    printf("What do you want to update [C]ontent/[P]riority/[c]ompleted:\n");
                    scanf(" %c", &update);

                    switch(update){
                    case 'C':

                        getchar();
                        printf("Enter New Task: \n");
                        scanf("%[^\n]%*c", list[i].task);
                        break;

                    case 'P':

                        printf("Enter new priority: [1-5]\n");
                        scanf("%d", &list[i].priority);
                        break;

                    case 'c':

                        printf("Enter completion status: [0/1]\n");
                        scanf("%d", &list[i].isComplete);
                        break;
                    }

                    printf("The Task is Updated.\n");
                    break;;
                }
            }

            if(!flag){
                printf("No Such Task in the List.\n");
            }

            break;

        case 3:

            printf("Enter ID: \n");
            scanf("%d", &id);

            for(int i = 0; i < num_tasks; i++){
                if(list[i].id == id){
                    index = i;
                    break;
                }
            }

            if(index == -1){
                printf("No Such Task in the List.\n");
            }
            else{
                delete_task(list, num_tasks, index);
                num_tasks--;
            }

            break;

        case 4:

            update_priority(list, num_tasks);
            display_list(list, num_tasks);
            break;

        case 5:

            loop = 0;
            write_to_file(list, num_tasks);
            printf("Tasks are saved.\n");
            break;

        default:
            printf("Enter an appropriate number.\n");
            break;
        }

    }

    return 0;
}
