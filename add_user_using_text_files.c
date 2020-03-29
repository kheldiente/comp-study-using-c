#include <stdio.h>
 
#define FNAME_LENGTH 30
#define LNAME_LENGTH 30
#define BDAY_LENGTH 9
#define GENDER_LENGTH 2
#define FAVCOLOR_LENGTH 15
#define FILE_PATH "./user-file.xml"
#define MAX_USERS 1000

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

struct User {
  char firstName[FNAME_LENGTH];
  char lastName[LNAME_LENGTH];
  char birthday[BDAY_LENGTH];
  char gender[GENDER_LENGTH];
  char favColor[FAVCOLOR_LENGTH];
  int age;
};

typedef struct User DATA_USER;
int userSize = 0;

char* remove_substring();
void write_file(DATA_USER *node, const char *command);
DATA_USER* get_users();
DATA_USER* find_user(char *keyword);
void insert_user();
void delete_user();
void update_user();
void search_user();
void display_users();
void bubble_sort_and_bsearch_char();

char* remove_substring(char *input, char *sub) {
    char *match;
    char *output = input;
    int len = strlen(sub);
    while ((match = strstr(output, sub))) {
        *match = '\0';
        strcat(output, match + len);
    }
    return output;
}
char* remove_leading_spaces(char* input) {
    int i, j;
    char *output = input;
    for (i = 0, j = 0;i<strlen(input); i++,j++){
        if (input[i] != ' ') {                          
            output[j] = input[i];                     
        } else {
            j--;
        }                                     
    }
    output[j] = 0;
    return output;
}

char* remove_trailing_spaces(char* input) {
    int len = strlen(input);
    char *output = input;
    if (output[len - 1] == '\n') {
        output[len - 1] = 0;
    }
    return output;
}

char* normalize_data(char* buffer, char *startTag, char* endTag) {
    char *formatted1 = remove_substring(buffer, startTag);
    // printf("\nnormalize_data->formatted1: %s", formatted1);
    char *formatted2 = remove_substring(formatted1, endTag);
    // printf("\nnormalize_data->formatted2: %s", formatted2);
    char *formatted3 = remove_leading_spaces(formatted2);
    // printf("\nnormalize_data->formatted3: %s", formatted3);
    char *output = remove_trailing_spaces(formatted3);
    // printf("\nnormalize_data->output: %s", output);
    return output;
}

DATA_USER* find_user(char *keyword) {

}

DATA_USER* get_users() {
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    DATA_USER userList[MAX_USERS];
    int userIndex = -1;

    filePointer = fopen(FILE_PATH, "r");

    while (fgets(buffer, bufferLength, filePointer)) {
        if (strstr(buffer, USER_START_TAG) != NULL) {
            userIndex++;
        }

        if (strstr(buffer, FIRST_NAME_START_TAG) != NULL) {
            char *firstName = normalize_data(buffer, FIRST_NAME_START_TAG, FIRST_NAME_END_TAG);
            strcpy(&userList[userIndex].firstName, firstName);
        }
        if (strstr(buffer, LAST_NAME_START_TAG) != NULL) {
            char *lastName = normalize_data(buffer, LAST_NAME_START_TAG, LAST_NAME_END_TAG);
            strcpy(&userList[userIndex].lastName, lastName);
        }
        if (strstr(buffer, BDAY_START_TAG) != NULL) {
            char *birthday = normalize_data(buffer, BDAY_START_TAG, BDAY_END_TAG);
            strcpy(&userList[userIndex].birthday, birthday);
        }
        if (strstr(buffer, GENDER_START_TAG) != NULL) {
            char *gender = normalize_data(buffer, GENDER_START_TAG, GENDER_END_TAG);
            strcpy(&userList[userIndex].gender, gender);
        }
        if (strstr(buffer, FAVCOLOR_START_TAG) != NULL) {
            char *favColor = normalize_data(buffer, FAVCOLOR_START_TAG, FAVCOLOR_END_TAG);
            strcpy(&userList[userIndex].favColor, favColor);
        }
        // if (strstr(buffer, AGE_START_TAG) != NULL) {
        //     remove_substring(buffer, AGE_START_TAG);
        //     remove_substring(buffer, AGE_END_TAG);
        //     tempUser->age = buffer
        // }
    }
    userSize = userIndex + 1;

    fclose(filePointer);
    return userList;
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

    write_file(tempUser, "a");
}

void delete_user() {
    char keyword[30];
    char yes[2] = "n";

    printf("\nEnter keyword, or else type exit: ");
    scanf("%s", keyword);

    DATA_USER *userList = get_users();

    // Rewrite file. Do not include matched user
    for (int i=0; i<userSize; i++) {
        DATA_USER *user = &userList[i];
        
        if (strstr(keyword, user->firstName) == NULL) {
            write_file(user, "w");
        }
    }
}

void update_user() {
    char keyword[30];
    char value[30];
    int attribute = -1;

    while (strcmp(keyword, "exit") != 0) {
        printf("\nEnter keyword to search user, or else type exit: ");
        scanf("%s", keyword);

        if (strcmp(keyword, "exit") != 0) {
            
        }
    }
}

void search_user() {

}

void display_users() {
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen(FILE_PATH, "r");

    while (fgets(buffer, bufferLength, filePointer)) {
        if (strstr(buffer, USER_START_TAG) != NULL) {
            printf("\n-------------------------");    
        }
        if (strstr(buffer, FIRST_NAME_START_TAG) != NULL) {
            char *firstName = normalize_data(buffer, FIRST_NAME_START_TAG, FIRST_NAME_END_TAG);
            printf("\nFirst name: %s", firstName);
        }
        if (strstr(buffer, LAST_NAME_START_TAG) != NULL) {
            char *lastName = normalize_data(buffer, LAST_NAME_START_TAG, LAST_NAME_END_TAG);
            printf("\nLast name: %s", lastName);
        }
        if (strstr(buffer, BDAY_START_TAG) != NULL) {
            char *birthday = normalize_data(buffer, BDAY_START_TAG, BDAY_END_TAG);
            printf("\nBirthday: %s", birthday);
        }
        if (strstr(buffer, GENDER_START_TAG) != NULL) {
            char *gender = normalize_data(buffer, GENDER_START_TAG, GENDER_END_TAG);
            printf("\nGender: %s", gender);
        }
        if (strstr(buffer, FAVCOLOR_START_TAG) != NULL) {
            char *favColor = normalize_data(buffer, FAVCOLOR_START_TAG, FAVCOLOR_END_TAG);
            printf("\nFavorite color: %s", favColor);
        }
        // if (strstr(buffer, AGE_START_TAG) != NULL) {
        //     remove_substring(buffer, AGE_START_TAG);
        //     remove_substring(buffer, AGE_END_TAG);
        //     char * formatted = remove_leading_spaces(buffer);
        //     printf("\nAge: %s", buffer);
        // }
        if (strstr(buffer, USER_END_TAG) != NULL) {
            printf("\n-------------------------\n\n");
        }
    }
    fclose(filePointer);
}

void bubble_sort_and_bsearch_char() {

}

void write_file(DATA_USER *node, const char *command) {
    FILE * fp;
    fp = fopen(FILE_PATH, command);
    
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