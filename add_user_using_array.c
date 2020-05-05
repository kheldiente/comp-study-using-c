#include <stdio.h>
#include <math.h>
#include "user_define.h"
#include "string_formatter.h"

int *userId;
char (*firstName)[FNAME_LENGTH];
char (*lastName)[LNAME_LENGTH];
char (*birthday)[BDAY_LENGTH];
char (*gender)[GENDER_LENGTH];
char (*favColor)[FAVCOLOR_LENGTH];
int *age;

int currentSize = 0;
int *isAvailable; // 0 = false, 1 = true

int sorted_number_binary_search(int arr[], int size, int element) {
    int start = 0;
    int end = size - 1;
    while (start <= end) {
        int mid = ceil((start + end) / 2);
        if (arr[mid] == element) {
            return mid;
        } else if (element < arr[mid]) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return -1;
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
        // printf("\nsorted_char_binary_search 1: %s, 2: %s, size: %d", tempValue, element, size);
        if (result == 0) {
            return mid;
        } else if (result > 0) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
        // printf("\nsorted_char_binary_seawrch AFTER start: %d, mid: %d, end: %d", start, mid, end);
        // printf("\nsorted_char_binary_search 1: %s, 2: %s, size: %d", tempValue, element, size);
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

void sort_users() { 
    char prevFullName[LNAME_LENGTH + FNAME_LENGTH];
    char fullName[LNAME_LENGTH + FNAME_LENGTH];
    char tempFname[FNAME_LENGTH];
    char tempLname[LNAME_LENGTH];
    char tempBday[BDAY_LENGTH];
    char tempGender[GENDER_LENGTH];
    char tempFavColor[FAVCOLOR_LENGTH];
    int tempAge;
    int tempUserId;

    for (int j=0; j<currentSize-1; j++) { 
        for (int i=j+1; i<currentSize; i++) { 
            if (userId[j] != -1) {
                strcpy(prevFullName, lastName[j]);
                strcat(prevFullName, firstName[j]);
                strcpy(fullName, lastName[i]);
                strcat(fullName, firstName[i]);

                if (strcmp(prevFullName, fullName) > 0) {
                    // Swap userId
                    tempUserId = userId[j];
                    userId[j] = userId[i];
                    userId[i] = tempUserId;

                    // Swap firstName
                    strcpy(tempFname, firstName[j]); 
                    strcpy(firstName[j], firstName[i]); 
                    strcpy(firstName[i], tempFname); 

                    // Swap lastName
                    strcpy(tempLname, lastName[j]);
                    strcpy(lastName[j], lastName[i]);
                    strcpy(lastName[i], tempLname);

                    // Swap birthday
                    strcpy(tempBday, birthday[j]);
                    strcpy(birthday[j], birthday[i]);
                    strcpy(birthday[i], tempBday);

                    // Swap gender
                    strcpy(tempGender, gender[j]);
                    strcpy(gender[j], gender[i]);
                    strcpy(gender[i], tempGender);

                    // Swap favColor
                    strcpy(tempFavColor, favColor[j]);
                    strcpy(favColor[j], favColor[i]);
                    strcpy(favColor[i], tempFavColor);

                    // Swap age
                    tempAge = age[j];
                    age[j] = age[i];
                    age[i] = tempAge;
                }
            }
        } 
    } 
}

void display_user(int index) {
    int tempUserId;
    char tempFirstName[FNAME_LENGTH];
    char tempLastName[LNAME_LENGTH];
    char tempBirthday[BDAY_LENGTH];
    char tempGender[GENDER_LENGTH];
    char tempFavColor[FAVCOLOR_LENGTH];
    int tempAge;

    tempUserId = userId[index];
    strcpy(tempFirstName, firstName[index]);
    strcpy(tempLastName, lastName[index]);
    strcpy(tempBirthday, birthday[index]);
    strcpy(tempGender, gender[index]);
    strcpy(tempFavColor, favColor[index]);
    tempAge = age[index];

    strtok(tempFirstName, "\n");
    strtok(tempLastName, "\n");
    strtok(tempBirthday, "\n");
    strtok(tempGender, "\n");
    strtok(tempFavColor, "\n");

    printf("\n-------------------------");
    printf("\nUser id: %d", tempUserId);
    printf("\nFirst name: %s", tempFirstName);
    printf("\nLast name: %s", tempLastName);
    printf("\nBirthday: %s", tempBirthday);
    printf("\nAge: %d", tempAge);
    printf("\nGender: %s",tempGender);
    printf("\nFavorite color: %s", tempFavColor);
    printf("\n-------------------------\n\n");
}

void display_users() {
    int deletedUsers = 0;
    for(int x=0;x<currentSize;x++) {
        if (isAvailable[x] == 1) {
            display_user(x);
        } else {
            deletedUsers++;
        }
    }
    printf("----------------------------------------\n");
    printf("               Users: %d            ", currentSize - deletedUsers);
    printf("\n----------------------------------------\n");
}

int find_user(char *keyword) {
    int foundIndex = -1;

    if (foundIndex == -1) {
        foundIndex = bubble_sort_and_bsearch_char(firstName, FNAME_LENGTH, currentSize, keyword);
    }

    if (foundIndex == -1) {
        foundIndex = bubble_sort_and_bsearch_char(lastName, LNAME_LENGTH, currentSize, keyword);
    }

    if (foundIndex == -1) {
        foundIndex = bubble_sort_and_bsearch_char(gender, GENDER_LENGTH, currentSize, keyword);
    }
    
    if (foundIndex != -1) {
        display_user(foundIndex);
    } else {
        printf("\nHas no match for keyword: %s", keyword);
    }
    return foundIndex;
}

void search_user() {
    char keyword[30];

    while (strcmp(keyword, "exit") != 0) {
        printf("\nEnter keyword, or else type exit: ");
        scanf("%s", keyword);
        
        printf("\n\nSearching for keyword(s): %s", keyword);
        find_user(keyword);
        printf("\n");
    }
}

void add_user() {
    printf("\n\n----------Input user----------\n");
    int tempUserId;
    char tempFirstName[FNAME_LENGTH];
    char tempLastName[LNAME_LENGTH];
    char tempBirthday[BDAY_LENGTH];
    char tempGender[GENDER_LENGTH];
    char tempFavColor[FAVCOLOR_LENGTH];
    int tempAge;

    printf("First name: ");
    fgets(tempFirstName, sizeof(tempFirstName), stdin);

    printf("Last name: ");
    fgets(tempLastName, sizeof(tempLastName), stdin);

    printf("Birthday (eg: 05/02/1992): ");
    scanf("%s", tempBirthday);

    printf("Age: ");
    scanf("%d", &tempAge);

    printf("Gender (M/F): ");
    scanf("%s", tempGender);
    getchar();

    printf("Favorite color (eg: blue, yellow, midnight blue, etc.): ");
    fgets(tempFavColor, sizeof(tempFavColor), stdin);

    strcpy(firstName[currentSize], tempFirstName);
    strcpy(lastName[currentSize], tempLastName);
    strcpy(birthday[currentSize], tempBirthday);
    strcpy(gender[currentSize], tempGender);
    strcpy(favColor[currentSize], tempFavColor);
    age[currentSize] = tempAge;
    userId[currentSize] = 1000 + (currentSize + 1);
    isAvailable[currentSize] = 1;

    printf("----------Added user!---------- \n\n");
    currentSize++;
}

void delete_user() {
    char keyword[30];
    char yes[2] = "n";

    while (strcmp(keyword, "exit") != 0) {
        printf("\nEnter keyword, or else type exit: ");
        scanf("%s", keyword);
        
        printf("\n\nSearching for keyword(s): %s", keyword);
        int userIndex = find_user(keyword);
        
        if (userIndex != -1) {
            printf("\nDelete user %d? Y/N ", userId[userIndex]);
            scanf("%s", yes);

            if (strcmp(yes, "Y") == 0 || strcmp(yes, "y" == 0)) {
                printf("Deleting: %s", firstName[userIndex]);
                printf("\ndeleting index: %d", userIndex);
                strcpy(firstName[userIndex], "\0");
                strcpy(lastName[userIndex], "\0");
                strcpy(birthday[userIndex], "\0");
                strcpy(gender[userIndex], "\0");
                strcpy(favColor[userIndex], "\0");
                userId[userIndex] = -1;
                age[userIndex] = -1;
                isAvailable[userIndex] = 0;
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
            int userIndex = find_user(keyword);
            if (userIndex != -1) {
                printf("\nAttribute number");
                printf("\n 1 - First name");
                printf("\n 2 - Last name");
                printf("\n 3 - Birthday (eg: 05/02/1992)");
                printf("\n 4 - Gender (M/F)");
                printf("\n 5 - Favorite color (eg: blue, yellow, midnight blue, etc.)");

                printf("\nEnter attribute number: ");
                scanf("%d", &attribute);
                printf("Enter new value: ");
                scanf("%s", value);

                if (attribute == 1) {
                    strcpy(firstName[userIndex], value);
                } else if (attribute == 2) {
                    strcpy(lastName[userIndex], value);
                } else if (attribute == 3) {
                    strcpy(birthday[userIndex], value);
                } else if (attribute == 4) {
                    strcpy(gender[userIndex], value);
                } else if (attribute == 5) {
                    strcpy(favColor[userIndex], value);
                }
            }
        }
        printf("\n");
    }
}

int main() {
    userId = malloc(MAX_USERS * sizeof(int));
    firstName = malloc(MAX_USERS * sizeof(char[FNAME_LENGTH]));
    lastName = malloc(MAX_USERS * sizeof(char[LNAME_LENGTH]));
    birthday = malloc(MAX_USERS * sizeof(char[BDAY_LENGTH]));
    gender = malloc(MAX_USERS * sizeof(char[GENDER_LENGTH]));
    favColor = malloc(MAX_USERS * sizeof(char[FAVCOLOR_LENGTH]));
    age = malloc(MAX_USERS * sizeof(int));
    isAvailable = malloc(MAX_USERS * sizeof(int));

    int command = -1;
    while (command != 0) {

        printf("\n--------------------");
        printf("\nCommands -- Arrays");
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
