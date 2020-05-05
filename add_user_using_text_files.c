#include <stdio.h>
#include <math.h>
#include "user_define.h"
#include "string_formatter.h"

#define FILE_PATH "./user-file.xml"

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
void reset_file();
DATA_USER* get_users();
DATA_USER* find_user(char *keyword);
int get_size();

int sorted_char_binary_search(char *arr, int length, int size, char *element) {
    int start = 0;
    int mid = 0;
    int end = size -1;
    char tempValue[length];

    strtok(element, "\n");
    while (start <= end) {
        mid = ceil((start + end) / 2);
        memcpy(tempValue, arr + (mid * length), length);
        strtok(tempValue, "\n");

        int result = strcmp(tempValue, element);
        // printf("\nsorted_char_binary_seawrch BEFORE start: %d, mid: %d, end: %d, result: %d", start, mid, end, result);
        // printf("\nsorted_char_binary_search BEFORE evaulting: %s, keyword: %s, size: %d", tempValue, element, size);
        if (result == 0) {
            return mid;
        } else if (result > 0) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
        // printf("\nsorted_char_binary_seawrch AFTER start: %d, mid: %d, end: %d", start, mid, end);
        // printf("\nsorted_char_binary_search AFTER evaluating: %s, keyword: %s, size: %d", tempValue, element, size);
    }
    return -1;
}

int bubble_sort_and_bsearch_char(char *arr, int length, int n, char *keyword) {
    char *tempArr = malloc(n * sizeof(char[length]));
    int tempIndexArr[n];
    char tempString[length]; 
    char prevString[length];
    char currString[length];
    int tempIndex = -1;

    char compPrevString[length];
    char compCurrString[length];
    int j = 0;

    memcpy(tempArr, arr, n * length);
    for (int x=0;x<n;x++) {
        tempIndexArr[x] = x;
        // printf("\nsorted index BEFORE: %d", tempIndexArr[x]);
    }
    
    while(j != (n - 1)) {
        for (int i=j+1;i<n;i++) { 
            strcpy(prevString, tempArr + (j * length));
            strcpy(currString, tempArr + (i * length));

            strcpy(compPrevString, prevString);
            strcpy(compCurrString, currString);
            strtok(compPrevString, "\n");
            strtok(compCurrString, "\n");

            if (strcmp(compPrevString, compCurrString) > 0) {
                // Swap char array
                strcpy(tempString, prevString); 
                strcpy(tempArr + (j * length), currString); 
                strcpy(tempArr + (i * length), tempString);

                // Swap indices
                tempIndex = tempIndexArr[j];
                tempIndexArr[j] = tempIndexArr[i];
                tempIndexArr[i] = tempIndex; 
            }
        }
        j++;
    }
    int foundIndex = sorted_char_binary_search(tempArr, length, n, keyword);
    // for (int x=0;x<n;x++) {
    //     printf("\nsorted index AFTER: %d", tempIndexArr[x]);
    // }
    // printf("\nfoundIndex: %d", foundIndex);
    if (foundIndex != -1) {
        int origIndex = tempIndexArr[foundIndex];
        return origIndex;    
    }
    return -1;   
}

DATA_USER* find_user(char *keyword) {
    DATA_USER *tempUserList = get_users();

    int tempUserSize = userSize;
    if (tempUserSize == 0) {
        tempUserSize = get_size();
    }

    char (*tempFname)[FNAME_LENGTH];
    char (*tempLname)[LNAME_LENGTH];
    char (*tempGender)[GENDER_LENGTH];
    int *tempAge;

    char prevFname[FNAME_LENGTH];
    char prevLname[LNAME_LENGTH];
    char prevGender[GENDER_LENGTH];
    int prevAge;

    tempFname = malloc(tempUserSize * sizeof(char[FNAME_LENGTH]));
    tempLname = malloc(tempUserSize * sizeof(char[LNAME_LENGTH]));
    tempGender = malloc(tempUserSize * sizeof(char[GENDER_LENGTH]));
    tempAge = malloc(tempUserSize * sizeof(int));

    // Original indices
    for(int x=0;x<tempUserSize;x++) {
        strcpy(tempFname[x], tempUserList[x].firstName);
        strcpy(tempLname[x], tempUserList[x].lastName);
        strcpy(tempGender[x], tempUserList[x].gender);
        tempAge[x] = tempUserList[x].age;
        // printf("\nsorted index: %s", tempFname[x]);
    }

    int foundIndex = -1;
    if (foundIndex == -1) {
        foundIndex = bubble_sort_and_bsearch_char(tempFname, FNAME_LENGTH, tempUserSize, keyword);
    }

    if (foundIndex == -1) {
        foundIndex = bubble_sort_and_bsearch_char(tempLname, LNAME_LENGTH, tempUserSize, keyword);
    }

    if (foundIndex == -1) {
        foundIndex = bubble_sort_and_bsearch_char(tempGender, GENDER_LENGTH, tempUserSize, keyword);
    }

    // printf("\nfoundIndex: %d", foundIndex);
    if (foundIndex != -1) {
        return &tempUserList[foundIndex];
    }
    return NULL;
}

int get_size() {
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];
    int userSize = 0;

    filePointer = fopen(FILE_PATH, "r");

    while (fgets(buffer, bufferLength, filePointer)) {
        if (strstr(buffer, USER_START_TAG) != NULL) {
            userSize++;
        }
    }
    fclose(filePointer);
    return userSize;
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

        if (strstr(buffer, ID_START_TAG) != NULL) {
            int id = normalize_int_data(buffer, ID_START_TAG, ID_END_TAG);
            userList[userIndex].id = id;
        }
        if (strstr(buffer, FIRST_NAME_START_TAG) != NULL) {
            char *firstName = normalize_char_data(buffer, FIRST_NAME_START_TAG, FIRST_NAME_END_TAG);
            strcpy(&userList[userIndex].firstName, firstName);
        }
        if (strstr(buffer, LAST_NAME_START_TAG) != NULL) {
            char *lastName = normalize_char_data(buffer, LAST_NAME_START_TAG, LAST_NAME_END_TAG);
            strcpy(&userList[userIndex].lastName, lastName);
        }
        if (strstr(buffer, BDAY_START_TAG) != NULL) {
            char *birthday = normalize_char_data(buffer, BDAY_START_TAG, BDAY_END_TAG);
            strcpy(&userList[userIndex].birthday, birthday);
        }
        if (strstr(buffer, GENDER_START_TAG) != NULL) {
            char *gender = normalize_char_data(buffer, GENDER_START_TAG, GENDER_END_TAG);
            strcpy(&userList[userIndex].gender, gender);
        }
        if (strstr(buffer, FAVCOLOR_START_TAG) != NULL) {
            char *favColor = normalize_char_data(buffer, FAVCOLOR_START_TAG, FAVCOLOR_END_TAG);
            strcpy(&userList[userIndex].favColor, favColor);
        }
        if (strstr(buffer, AGE_START_TAG) != NULL) {
            int age = normalize_int_data(buffer, AGE_START_TAG, AGE_END_TAG);
            userList[userIndex].age = age;
        }
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

    tempUser->id = generate_random_id();

    write_file(tempUser, "a");
}

void delete_user() {
    char keyword[30];
    char yes[2] = "n";

    printf("\nEnter keyword, or else type exit: ");
    scanf("%s", keyword);

    DATA_USER *user = find_user(keyword);
    if (user != NULL) {
        printf("\nDelete user %d? Y/N ", user->id);
        scanf("%s", yes);

        if (strcmp(yes, "Y") == 0 || strcmp(yes, "y" == 0)) {
            DATA_USER *userList = get_users();
            // Clear out file contents.
            reset_file();

            // Rewrite file. Do not include matched user
            for (int i=0; i<userSize; i++) {
                DATA_USER *tempUser = &userList[i];
                if (tempUser->id != user->id) {
                    write_file(tempUser, "a");
                }
            }
        }
        printf("\n");   
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
            DATA_USER *tempUser = find_user(keyword);
            if (tempUser != NULL) {
                printf("\nUpdating user->firstName: %s", tempUser->firstName);

                printf("\nAttribute number");
                printf("\n 1 - First name");
                printf("\n 2 - Last name");
                printf("\n 3 - Birthday (eg: 05/02/1992");
                printf("\n 4 - Gender (M/F)");
                printf("\n 5 - Favorite color (eg: blue, yellow, midnight blue, etc.)");

                printf("\nEnter attribute number: ");
                scanf("%d", &attribute);
                printf("\nEnter new value: ");
                scanf("%s", value);

                if (attribute == 1) {
                    strcpy(tempUser->firstName, value);
                } else if (attribute == 2) {
                    strcpy(tempUser->lastName, value);
                } else if (attribute == 3) {
                    strcpy(tempUser->birthday, value);
                } else if (attribute == 4) {
                    strcpy(tempUser->gender, value);
                } else if (attribute == 5) {
                    strcpy(tempUser->favColor, value);
                }
            }
        }
    }
}

void display_user(DATA_USER *user) {
    printf("\nFirst name: %s", user->firstName);
    printf("\nLast name: %s", user->lastName);
    printf("\nBirthday: %s", user->birthday);
    printf("\nGender: %s", user->gender);
    printf("\nFavorite color: %s", user->favColor);
}

void display_users() {
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];
    DATA_USER *tempUser = (DATA_USER *) malloc(sizeof(DATA_USER));
    
    filePointer = fopen(FILE_PATH, "r");

    while (fgets(buffer, bufferLength, filePointer)) {
        if (strstr(buffer, USER_START_TAG) != NULL) {
            printf("\n-------------------------");    
        }
        if (strstr(buffer, FIRST_NAME_START_TAG) != NULL) {
            char *firstName = normalize_char_data(buffer, FIRST_NAME_START_TAG, FIRST_NAME_END_TAG);
            strcpy(tempUser->firstName, firstName);
        }
        if (strstr(buffer, LAST_NAME_START_TAG) != NULL) {
            char *lastName = normalize_char_data(buffer, LAST_NAME_START_TAG, LAST_NAME_END_TAG);
            strcpy(tempUser->lastName, lastName);
        }
        if (strstr(buffer, BDAY_START_TAG) != NULL) {
            char *birthday = normalize_char_data(buffer, BDAY_START_TAG, BDAY_END_TAG);
            strcpy(tempUser->birthday, birthday);
        }
        if (strstr(buffer, GENDER_START_TAG) != NULL) {
            char *gender = normalize_char_data(buffer, GENDER_START_TAG, GENDER_END_TAG);
            strcpy(tempUser->gender, gender);
            
        }
        if (strstr(buffer, FAVCOLOR_START_TAG) != NULL) {
            char *favColor = normalize_char_data(buffer, FAVCOLOR_START_TAG, FAVCOLOR_END_TAG);
            strcpy(tempUser->favColor, favColor);
           
        }
        // if (strstr(buffer, AGE_START_TAG) != NULL) {
        //     remove_substring(buffer, AGE_START_TAG);
        //     remove_substring(buffer, AGE_END_TAG);
        //     char * formatted = remove_leading_spaces(buffer);
        //     printf("\nAge: %s", buffer);
        // }

        if (strstr(buffer, USER_END_TAG) != NULL) {
            display_user(tempUser);
            printf("\n-------------------------\n\n");
        }
    }
    fclose(filePointer);
}

void search_user() {
    char keyword[30];

    while (strcmp(keyword, "exit") != 0) {
        printf("\nEnter keyword, or else type exit: ");
        scanf("%s", keyword);

        printf("\n\nSearching for keyword(s): %s", keyword);
        DATA_USER *user = find_user(keyword);
        if (user != NULL) {
            printf("\n-------------------------");
            display_user(user);
            printf("\n-------------------------\n\n");
        } else {
            printf("\nHas no match for keyword: %s", keyword);
        }
    }
}

void write_file(DATA_USER *node, const char *command) {
    FILE * fp;
    fp = fopen(FILE_PATH, command);
    
    fprintf(fp, "%s\n", USER_START_TAG);
    fprintf(fp, "   %s%d%s\n", ID_START_TAG, node->id, ID_END_TAG);
    fprintf(fp, "   %s%s%s\n", FIRST_NAME_START_TAG, node->firstName, FIRST_NAME_END_TAG);
    fprintf(fp, "   %s%s%s\n", LAST_NAME_START_TAG, node->lastName, LAST_NAME_END_TAG);
    fprintf(fp, "   %s%s%s\n", BDAY_START_TAG, node->birthday, BDAY_START_TAG);
    fprintf(fp, "   %s%d%s\n", AGE_START_TAG, node->age, AGE_END_TAG);
    fprintf(fp, "   %s%s%s\n", GENDER_START_TAG, node->gender, GENDER_END_TAG);
    fprintf(fp, "   %s%s%s\n", FAVCOLOR_START_TAG, node->favColor, FAVCOLOR_END_TAG);
    fprintf(fp, "%s\n", USER_END_TAG);

    fclose (fp);
}

void reset_file() {
    FILE * fp;
    fp = fopen(FILE_PATH, "w");
    fclose(fp);
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
            break;
        default:
            break;
        }
    }
    return 0;
}