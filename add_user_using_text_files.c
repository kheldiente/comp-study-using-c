#include <stdio.h>
 
#define FNAME_LENGTH 30
#define LNAME_LENGTH 30
#define BDAY_LENGTH 9
#define GENDER_LENGTH 2
#define FAVCOLOR_LENGTH 15
#define FILE_PATH "./user-file.txt"

#define USER_START_TAG "<user>"
#define USER_END_TAG "</user>"
#define FIRST_NAME_START_TAG "<firstName>"
#define FIRST_NAME_END_TAG "</firstName>"
#define LAST_NAME_START_TAG "<lastName>"
#define LAST_NAME_END_TAG "</lastName>"
#define BDAY_START_TAG "<birthday>"
#define BDAY_END_TAG "</birthday>"
#define GENDER_START_TAG "<gender>"
#define GENDER_END_TAG "</gender>"
#define FAVCOLOR_START_TAG "<favColor>"
#define FAVCOLOR_END_TAG "</favColor>"
#define AGE_START_TAG "<age>"
#define AGE_END_TAG "</age>"

struct Node {
  char firstName[FNAME_LENGTH];
  char lastName[LNAME_LENGTH];
  char birthday[BDAY_LENGTH];
  char gender[GENDER_LENGTH];
  char favColor[FAVCOLOR_LENGTH];
  int age;
};

typedef struct Node DATA_NODE;

void remove_substring();
void write_file();
void read_file();
void insert_user();
void delete_user();
void update_user();
void search_user();
void display_users();
void bubble_sort();

void remove_substring(char *string, char *sub) {
    char *match;
    int len = strlen(sub);
    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(string, match+len);
    }
}

void insert_user() {
    DATA_NODE *tempNode = (DATA_NODE *) malloc(sizeof(DATA_NODE));

    printf("\n\n----------Input user----------\n");

    printf("First name: ");
    fgets(tempNode->firstName, sizeof(tempNode->firstName), stdin);
    strtok(tempNode->firstName, "\n");

    printf("Last name: ");
    fgets(tempNode->lastName, sizeof(tempNode->lastName), stdin);
    strtok(tempNode->lastName, "\n");

    printf("Birthday (eg: 05/02/1992): ");
    scanf("%s", tempNode->birthday);

    printf("Age: ");
    scanf("%d", &tempNode->age);

    printf("Gender (M/F): ");
    scanf("%s", tempNode->gender);
    getchar();

    printf("Favorite color (eg: blue, yellow, midnight blue, etc.): ");
    fgets(tempNode->favColor, sizeof(tempNode->favColor), stdin);
    strtok(tempNode->favColor, "\n");

    write_file(tempNode);
}

void delete_user() {

}

void update_user() {

}

void search_user() {

}

void display_users() {
    read_file();
}

void bubble_sort() {

}

void read_file() {
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen(FILE_PATH, "r");

    while (fgets(buffer, bufferLength, filePointer)) {
        if (strstr(buffer, USER_START_TAG) != NULL) {
            printf("\n-------------------------");    
        }
        if (strstr(buffer, FIRST_NAME_START_TAG) != NULL) {
            remove_substring(buffer, FIRST_NAME_START_TAG);
            remove_substring(buffer, FIRST_NAME_END_TAG);
            printf("\nFirst name: %s", buffer);
        }
        if (strstr(buffer, LAST_NAME_START_TAG) != NULL) {
            remove_substring(buffer, LAST_NAME_START_TAG);
            remove_substring(buffer, LAST_NAME_END_TAG);
            printf("\nLast name: %s", buffer);
        }
        if (strstr(buffer, BDAY_START_TAG) != NULL) {
            remove_substring(buffer, BDAY_START_TAG);
            remove_substring(buffer, BDAY_END_TAG);
            printf("\nBirthday: %s", buffer);
        }
        if (strstr(buffer, GENDER_START_TAG) != NULL) {
            remove_substring(buffer, GENDER_START_TAG);
            remove_substring(buffer, GENDER_END_TAG);
            printf("\nGender: %s", buffer);
        }
        if (strstr(buffer, FAVCOLOR_START_TAG) != NULL) {
            remove_substring(buffer, FAVCOLOR_START_TAG);
            remove_substring(buffer, FAVCOLOR_END_TAG);
            printf("\nFavorite color: %s", buffer);
        }
        if (strstr(buffer, AGE_START_TAG) != NULL) {
            remove_substring(buffer, AGE_START_TAG);
            remove_substring(buffer, AGE_END_TAG);
            printf("\nAge: %s", buffer);
        }
        if (strstr(buffer, USER_END_TAG) != NULL) {
            printf("\n-------------------------\n\n");
        }
    }
    fclose(filePointer);
}


void write_file(DATA_NODE *node) {
    FILE * fp;
    fp = fopen (FILE_PATH,"a");
    
    fprintf(fp, "%s\n", USER_START_TAG);
    fprintf(fp, "   %s%s%s\n", FIRST_NAME_START_TAG, node->firstName, FIRST_NAME_END_TAG);
    fprintf(fp, "   %s%s%s\n", LAST_NAME_START_TAG, node->lastName, LAST_NAME_END_TAG);
    fprintf(fp, "   %s%s%s\n", BDAY_START_TAG, node->birthday, BDAY_START_TAG);
    fprintf(fp, "   %s%d%s\n", AGE_START_TAG, node->age, AGE_END_TAG);
    fprintf(fp, "   %s%s%s\n", GENDER_START_TAG, node->gender, GENDER_END_TAG);
    fprintf(fp, "   %s%s%s\n", FAVCOLOR_START_TAG, node->favColor, FAVCOLOR_END_TAG);
    fprintf(fp, "%s\n", USER_END_TAG);

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