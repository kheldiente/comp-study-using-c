#include <stdio.h>
#include <math.h>
#include "user_define.h"
#include "string_formatter.h"

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

struct CharHolder {
    char value[CHAR_HOLDER_VALUE_LENGTH];
};
struct RowColHolder {
    int row;
    int col;
};

typedef struct User DATA_USER;
typedef struct CharHolder DATA_CHAR;
typedef struct RowColHolder DATA_ROW_COL;

DATA_USER userTable[MAX_USERS_ROW][MAX_USER_COL];
int currentRow = 0;
int currentCol = 0;

int* sorted_char_binary_search(DATA_CHAR arr[MAX_USERS_ROW][MAX_USER_COL], int length, char *element) {
    char tempValue[length];
    int start = 0;
    int mid, row, col;
    int foundRowAndCol[2];
    int tempCurrentRow = currentRow + 1;
    int tempCurrentCol = currentCol + 1;
    int end = tempCurrentRow * tempCurrentCol - 1;
    char fullName[LNAME_LENGTH + FNAME_LENGTH];
    // printf("\nbinary_search start: %d, end: %d", start, end);
    while (start <= end){
        mid = ceil(start + (end - start) / 2);
        row = ceil(mid / tempCurrentCol);
        col = ceil(mid % tempCurrentCol);
        strcpy(tempValue, arr[row][col].value);
    
        int result = strcmp(tempValue, element);
        if (result == 0) {
            foundRowAndCol[0] = row;
            foundRowAndCol[1] = col;
            return foundRowAndCol;
        } else if (result > 0) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    foundRowAndCol[0] = -1;
    foundRowAndCol[1] = -1;
    return foundRowAndCol;
}

DATA_USER* bubble_sort_and_bsearch_char(DATA_CHAR arr[MAX_USERS_ROW][MAX_USER_COL], int length, char *keyword) {
    DATA_USER *user;
    char tempString[length]; 
    char prevString[length];
    char currString[length];

    DATA_ROW_COL tempRowCol;
    DATA_ROW_COL origRowCol[MAX_USERS_ROW][MAX_USER_COL];
    for (int col=0;col<=currentCol;col++) {
        for (int row=0;row<=currentRow;row++) {
            origRowCol[row][col].row = row;
            origRowCol[row][col].col = col;
        }
    }

    for(int i=0; i<=currentCol;i++){
        for(int j=0; j<=currentRow;j++) {
            strcpy(prevString, arr[j][i].value);
            strcpy(currString, arr[j + 1][i].value);
            
            if (strcmp(prevString, "") != 0 && strcmp(currString, "") != 0) {
                // printf("\nbubble_sort prevString: %s, currString: %s", prevString, currString);
                if (strcmp(prevString, currString) > 0) {
                    strcpy(tempString, arr[j][i].value);
                    strcpy(arr[j][i].value, arr[j+1][i].value);
                    strcpy(arr[j+1][i].value, tempString);

                    tempRowCol = origRowCol[j][i];
                    origRowCol[j][i] = origRowCol[j+1][i];
                    origRowCol[j+1][i] = tempRowCol;
                }
            }
        }
    }
    int *foundRowCol = sorted_char_binary_search(arr, length, keyword);
    int row = foundRowCol[0];
    int col = foundRowCol[1];
    if (row != -1 && col != -1) {
        DATA_ROW_COL resultRowCol = origRowCol[row][col];
        return &userTable[resultRowCol.row][resultRowCol.col];
    }
    return NULL;
}

DATA_USER* find_user(char *keyword) {
    DATA_USER *user = NULL;
    char tempString[LNAME_LENGTH + FNAME_LENGTH]; 
    char prevString[LNAME_LENGTH + FNAME_LENGTH];
    char currString[LNAME_LENGTH + FNAME_LENGTH];

    DATA_CHAR tempFname[MAX_USERS_ROW][MAX_USER_COL];
    DATA_CHAR tempLname[MAX_USERS_ROW][MAX_USER_COL];
    DATA_CHAR tempGender[MAX_USERS_ROW][MAX_USER_COL];
    int tempAge[MAX_USERS_ROW][MAX_USER_COL];

    for (int col=0;col<=currentCol;col++) {
        for (int row=0;row<=currentRow;row++) {
            DATA_USER user = userTable[row][col];
            if (user.isValid == 1) {
                strcpy(tempFname[row][col].value, user.firstName);
                strcpy(tempLname[row][col].value, user.lastName);
                strcpy(tempGender[row][col].value, user.gender);
                tempAge[row][col] = user.age;
                printf("\nfind_user: %s", tempFname[row][col]);
            }
        }
    }

    if (user == NULL) {
        user = bubble_sort_and_bsearch_char(tempFname, FNAME_LENGTH, keyword);
    }
    if (user == NULL) {
        user = bubble_sort_and_bsearch_char(tempLname, LNAME_LENGTH, keyword);
    }
    if (user == NULL) {
        user = bubble_sort_and_bsearch_char(tempGender, GENDER_LENGTH, keyword);
    }
    return user;
}

void sort_users() {
    DATA_USER tempUser;
    char prevFullName[LNAME_LENGTH + FNAME_LENGTH];
    char fullName[LNAME_LENGTH + FNAME_LENGTH];
    for(int i=0; i<=currentCol;i++){
        for(int j=0; j<=currentRow;j++) {
            strcpy(prevFullName, userTable[j][i].lastName);
            strcat(prevFullName, userTable[j][i].firstName);
            strcpy(fullName, userTable[j + 1][i].lastName);
            strcat(fullName, userTable[j + 1][i].firstName);
            
            if (userTable[j][i].isValid) {
                printf("\nsort_users prevString: %s, currString: %s", prevFullName, fullName);
                if (strcmp(prevFullName, fullName) > 0) {
                    tempUser = userTable[j][i];
                    userTable[j][i] = userTable[j+1][i];
                    userTable[j+1][i] = tempUser;
                }
            }
        }
    }
}

void display_user(DATA_USER *user) {
    printf("\n-------------------------");
    printf("\nFirst name: %s", user->firstName);
    printf("\nLast name: %s", user->lastName);
    printf("\nBirthday: %s", user->birthday);
    printf("\nGender: %s", user->gender);
    printf("\nFavorite color: %s", user->favColor);
    printf("\n-------------------------\n\n");
}

void display_users() {
    for (int col=0;col<=currentCol;col++) {
        for (int row=0;row<=currentRow;row++) {
            DATA_USER user = userTable[row][col];
            if (user.isValid == 1) {
                printf("\ndisplay_users row: %d, col: %d", row, col);
                display_user(&user);
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
        if (user == NULL) {
            printf("\nDoes not match any user");
        } else {
            display_user(user);
        }
        printf("\n");
    }
}

void add_user() {
    DATA_USER tempUser;

    printf("\n\n----------Input user----------\n");

    printf("First name: ");
    fgets(tempUser.firstName, sizeof(tempUser.firstName), stdin);
    strtok(tempUser.firstName, "\n");

    printf("Last name: ");
    fgets(tempUser.lastName, sizeof(tempUser.lastName), stdin);
    strtok(tempUser.lastName, "\n");

    printf("Birthday (eg: 05/02/1992): ");
    scanf("%s", tempUser.birthday);

    printf("Age: ");
    scanf("%d", &tempUser.age);

    printf("Gender (M/F): ");
    scanf("%s", tempUser.gender);
    getchar();

    printf("Favorite color (eg: blue, yellow, midnight blue, etc.): ");
    fgets(tempUser.favColor, sizeof(tempUser.favColor), stdin);
    strtok(tempUser.favColor, "\n");

    tempUser.id = generate_random_id();
    tempUser.isValid = 1;
    
    if (currentRow < MAX_USERS_ROW) {
        if (currentCol < MAX_USER_COL) {
            userTable[currentRow][currentCol] = tempUser;
            currentRow++;
        } else {
            printf("\n Failed to add user. TAble is full");
        }
    } else {
        currentCol++;
        userTable[currentRow][currentCol] = tempUser;
    }
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
            for (int col=0;col<=currentCol;col++) {
                for (int row=0;row<=currentRow;row++) {
                    DATA_USER tempUser = userTable[row][col];
                    if (tempUser.isValid == 1) {
                        if (tempUser.id == user->id) {
                            userTable[row][col].isValid = 0;
                        }
                    }
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

                for (int col=0;col<=currentCol;col++) {
                    for (int row=0;row<=currentRow;row++) {
                        DATA_USER tempUser = userTable[row][col];
                        if (tempUser.isValid == 1) {
                            if (matchedUserId == tempUser.id) {
                                if (attribute == 1) {
                                    strcpy(tempUser.firstName, value);
                                } else if (attribute == 2) {
                                    strcpy(tempUser.lastName, value);
                                } else if (attribute == 3) {
                                    strcpy(tempUser.birthday, value);
                                } else if (attribute == 4) {
                                    strcpy(tempUser.gender, value);
                                } else if (attribute == 5) {
                                    strcpy(tempUser.favColor, value);
                                }
                                userTable[row][col] = tempUser;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int command = -1;
    while (command != 0) {
        printf("\n--------------------");
        printf("\nCommands -- Table");
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
            add_user();
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
