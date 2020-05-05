#include <stdio.h>
#include "user_define.h"
#include "string_formatter.h"

#define FILE_PATH "./user-file.bin"

struct User {
    int id;
    char firstName[FNAME_LENGTH];
    char lastName[LNAME_LENGTH];
    char birthday[BDAY_LENGTH];
    char gender[GENDER_LENGTH];
    char favColor[FAVCOLOR_LENGTH];
    int age;
};

typedef struct User DATA_USER;
int userSize = 0;

void insert_user();
void delete_user();
void update_user();
void search_user();
void display_users();

void write_file(DATA_USER *node, const char *command);
DATA_USER* get_users();
DATA_USER* find_user(char *keyword);
int get_size();
int sorted_char_binary_search(DATA_USER *users, char *element);

DATA_USER* bubble_sort_and_bsearch_char(char *keyword);

void write_file(DATA_USER *node, const char *command) {
    FILE *fp;
    fp = fopen(FILE_PATH, command);
    if (fp != NULL) {
        fwrite(node, sizeof(DATA_USER), 1, fp);
    }
    fclose(fp);
}

void delete_user() {

}

void update_user() {

}

void search_user() {

}

void display_users() {
    FILE * fp;
    DATA_USER userList[MAX_USERS];
    DATA_USER *user;

    fp = fopen(FILE_PATH, "rb");
    if (fp != NULL) {
        fread(userList, sizeof(userList), MAX_USERS, fp);
    }
    
    int userId = generate_random_id();
    int index = 0;
    while (userId > 0) {
        user = &userList[index];
        userId = user->id;

        if (userId > 0) {
            printf("\nUser id: %d", user->id);  
            printf("\nFirst name: %s", user->firstName);
            printf("\nLast name: %s", user->lastName);
            printf("\nBirthday (e.g: 05/02/1992): %s", user->birthday);
            printf("\nAge: %d", user->age);
            printf("\nGender (M/F): %s", user->gender);
            printf("\nFavorite color (eg: blue, yellow, midnight blue, etc.): %s", user->favColor);
        }

        index++;
    }

    userSize = index + 1;
    fclose (fp);
}

void insert_user() {
    DATA_USER *tempUser = (DATA_USER *) malloc(sizeof(DATA_USER));

    printf("\n\n----------Input user----------\n");

    printf("First name: ");
    fgets(tempUser->firstName, sizeof(tempUser->firstName), stdin);
    strtok(tempUser->firstName, "\n");

    printf("Last name: ");
    fgets(tempUser->lastName, sizeof(tempUser->lastName), stdin);
    strtok(tempUser->lastName, "\n");

    printf("Birthday (eg: 05/02/1992): ");
    scanf("%s", tempUser->birthday);

    printf("Age: ");
    scanf("%d", &tempUser->age);

    printf("Gender (M/F): ");
    scanf("%s", tempUser->gender);
    getchar();

    printf("Favorite color (eg: blue, yellow, midnight blue, etc.): ");
    fgets(tempUser->favColor, sizeof(tempUser->favColor), stdin);
    strtok(tempUser->favColor, "\n");

    tempUser->id = generate_random_id();

    write_file(tempUser, "ab");
}

int main() {
    int command = -1;
    while (command != 0) {
        printf("\n--------------------");
        printf("\nCommands -- Binary file");  
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
            break;
        default:
            break;
        }
    }
    return 0;   
}