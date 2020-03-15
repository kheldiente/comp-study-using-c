#include <stdio.h>
 
#define LEN 256

void insert_user() {

}

void delete_user() {

}

void update_user() {

}

void search_user() {

}

void display_users() {

}

void bubble_sort() {

}

void read_file() {
    int num;
    FILE *fptr;

    if ((fptr = fopen("C:\\program.txt","r")) == NULL){
        printf("Error! opening file");
        return;
    }

    fscanf(fptr,"%d", &num);

    printf("Value of n=%d", num);
    fclose(fptr); 
}


void write_in_file() {
    FILE * fp;
    int i;
    /* open the file for writing*/
    fp = fopen ("user-file.txt","w");

    /* write 10 lines of text into the file stream*/
    for(i = 0; i < 10;i++){
        fprintf (fp, "This is line %d\n",i + 1);
    }

    /* close the file*/  
    fclose (fp);
}

int main() {
    int command = -1;
    while (command != 0) {
        printf("\n--------------------");
        printf("\nCommands -- Text file");
        printf("\n 1 - Add user");
        printf("\n 2 - Delete user");
        printf("\n 3 - Update user");
        printf("\n 4 - Search user");
        printf("\n 5 - Display users");
        printf("\n 6 - Sort users");
        printf("\n 0 - Exit");
        printf("\n--------------------");

        printf("\nEnter command: ");
        scanf("%d", &command);
        getchar();

        switch (command) {
        case 1:
            insert_user();
            break;
        case 2:
            delete_user();
            break;
        case 3:
            update_user();
            break;
        case 4:
            search_user();
            break;
        case 5:
            display_users();
            break;
        case 6:
            bubble_sort();
            break;
        default:
            break;
        }
    }
    return 0;
}