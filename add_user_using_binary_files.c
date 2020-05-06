#include <stdio.h>
#include "user_define.h"
#include "string_formatter.h"

#define FILE_PATH "./user-file.bin"
#define TEMP_FILE_PATH "./temp-user-file.bin"

struct User {
    int id;
    char firstName[FNAME_LENGTH];
    char lastName[LNAME_LENGTH];
    char birthday[BDAY_LENGTH];
    char gender[GENDER_LENGTH];
    char favColor[FAVCOLOR_LENGTH];
    int age;
    int isValid;
};

typedef struct User DATA_USER;
int userSize = 0;

void insert_user();
void delete_user();
void update_user();
void search_user();
void display_users();


void write_file(DATA_USER *node, const char *command);
void write_file2(DATA_USER *node, FILE *fp);
DATA_USER* get_users();
DATA_USER* find_user(char *keyword);
int get_size();

void write_file(DATA_USER *node, const char *command) {
    FILE *fp;
    fp = fopen(FILE_PATH, command);
    if (fp != NULL) {
        fwrite(node, sizeof(DATA_USER), 1, fp);
    }
    fclose(fp);
}

void write_file2(DATA_USER *node, FILE *fp) {
    if (fp != NULL) {
        fwrite(node, sizeof(DATA_USER), 1, fp);
    }
}

int get_size() {
    FILE * fp;
    DATA_USER userList[MAX_USERS];
    DATA_USER *user;

    fp = fopen(FILE_PATH, "rb");
    if (fp != NULL) {
        fread(userList, sizeof(userList), MAX_USERS, fp);
    }
    
    int isValid = 1;
    int index = 0;
    while (isValid == 1) {
        user = &userList[index];
        isValid = user->isValid;

        if (isValid == 1) {
            index++;
        }
    }

    userSize = index + 1;
    fclose(fp);
    
    return userSize;
} 

DATA_USER* get_users() {
    FILE * fp;
    DATA_USER userList[MAX_USERS];
    DATA_USER *user;

    fp = fopen(FILE_PATH, "rb");
    if (fp != NULL) {
        fread(userList, sizeof(userList), MAX_USERS, fp);
    }
    fclose(fp);
    return userList;
}

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

void display_user(DATA_USER *user) {
    printf("\n-------------------------");
    printf("\nUser id: %d", user->id);  
    printf("\nFirst name: %s", user->firstName);
    printf("\nLast name: %s", user->lastName);
    printf("\nBirthday (e.g: 05/02/1992): %s", user->birthday);
    printf("\nAge: %d", user->age);
    printf("\nGender (M/F): %s", user->gender);
    printf("\nFavorite color (eg: blue, yellow, midnight blue, etc.): %s", user->favColor);
    printf("\n-------------------------\n");
}

void delete_user() {
    char keyword[30];
    char yes[2] = "n";

    printf("\nEnter keyword, or else type exit: ");
    scanf("%s", keyword);

    DATA_USER *user = find_user(keyword);
    if (user != NULL) {
        int userId = user->id;
        // printf("\ndelete_user matchedUserId: %d, name: %s", userId, user->firstName);

        printf("\nDelete user %d? Y/N ", userId);
        scanf("%s", yes);

        if (strcmp(yes, "Y") == 0 || strcmp(yes, "y" == 0)) {
            DATA_USER *userList = get_users();

            // Rewrite file. Do not include matched user
            // Temp file
            FILE *tmpFp;
            tmpFp = fopen(TEMP_FILE_PATH, "ab");
            
            for (int i=0; i<userSize; i++) {
                DATA_USER *tempUser = &userList[i];
                printf("\ndelete_user evaluting tempUser: %d, isValid: %d", tempUser->id, tempUser->isValid);
                if (tempUser->id != userId && tempUser->isValid == 1) {
                    printf("\ndelete_user does not userId: %d, matchedUserId: %d", userId, tempUser->id);
                    write_file2(tempUser, tmpFp);
                }
            }
            fclose(tmpFp);

            remove(FILE_PATH);
            rename(TEMP_FILE_PATH, FILE_PATH);

            printf("\nDeleted user with id: %d", userId);
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
            DATA_USER *matchedUser = find_user(keyword);
            if (matchedUser != NULL) {
                int matchedUserId = matchedUser->id;
                printf("\nUpdating user with id: %d", matchedUserId);

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

                DATA_USER *userList = get_users();

                // Rewrite file. Updated attribute for matched user.
                FILE *tmpFp;
                tmpFp = fopen(TEMP_FILE_PATH, "ab");

                for (int i=0; i<userSize; i++) {
                    DATA_USER *tempUser = &userList[i];
                    // printf("\nupdate_user writing -> id: %d, matchedUserId: %d", matchedUserId, tempUser->id);
                    if (matchedUserId == tempUser->id) {
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
                    write_file2(tempUser, tmpFp);
                }
                
                fclose(tmpFp);

                remove(FILE_PATH);
                rename(TEMP_FILE_PATH, FILE_PATH);
            }
        }
    }
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

void display_users() {
    DATA_USER *userList = get_users();
    DATA_USER *user;
    
    int isValid = 1;
    int index = 0;
    while (isValid == 1) {
        user = &userList[index];
        isValid = user->isValid;

        if (isValid == 1) {
            display_user(user);
        }
        index++;
    }
}

void sort_users() {
    DATA_USER *tempUserList = get_users();
    DATA_USER tempUser;

    char prevFullName[LNAME_LENGTH + FNAME_LENGTH];
    char fullName[LNAME_LENGTH + FNAME_LENGTH];
    int tempUserSize = userSize;
    if (tempUserSize == 0) {
        tempUserSize = get_size();
    }

    for (int j=0; j<tempUserSize-1; j++) { 
        for (int i=j+1; i<tempUserSize; i++) { 
            if (tempUserList[j].id != -1) {
                strcpy(prevFullName, tempUserList[j].lastName);
                strcat(prevFullName, tempUserList[j].firstName);
                strcpy(fullName, tempUserList[i].lastName);
                strcat(fullName, tempUserList[i].firstName);

                if (strcmp(prevFullName, fullName) > 0) {
                    tempUser = tempUserList[j];
                    tempUserList[j] = tempUserList[i];
                    tempUserList[i] = tempUser;
                }
            }
        } 
    }

    // Rewrite file with the new sequence
    FILE *fp;
    fp = fopen(FILE_PATH, "ab");

    for (int i=0; i<tempUserSize; i++) {
        DATA_USER *user = &tempUserList[i];
        write_file2(user, fp);
    }

    fclose(fp);
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
    tempUser->isValid = 1;
    
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
            sort_users();
            break;
        default:
            break;
        }
    }
    return 0;   
}