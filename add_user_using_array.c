#include <stdio.h>
#include <stdlib.h>

#define FNAME_LENGTH 30
#define LNAME_LENGTH 30
#define BDAY_LENGTH 9
#define GENDER_LENGTH 2
#define FAVCOLOR_LENGTH 15
#define LEN(arr) ((int) (sizeof(arr) / sizeof (arr)[0]))

size_t recordSize = 3;

int *userId;
char (*firstName)[FNAME_LENGTH];
char (*lastName)[LNAME_LENGTH];
char (*birthday)[BDAY_LENGTH];
char (*gender)[GENDER_LENGTH];
char (*favColor)[FAVCOLOR_LENGTH];
int *age;

int n = 0;
int command = -1;

int sorted_number_binary_search(int arr[], int size, int element) {
    int start = 0;
    int end = size - 1;
    while (start <= end) {
        int mid = (start + end) / 2;
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

    while (start <= end) {
        mid = (start + end) / 2;
        memcpy(tempValue, arr + (mid * length), length);
        printf("\nsorted_char_binary: %s to %s", tempValue, element);

        int result = strcmp(tempValue, element);
        if (result == 0) {
            printf("\nMatched element %s", element);
            return mid;
        } else if (result > 0) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    printf("\nHas no matched :(");
    return -1;
}

char* bubble_sort_char(char *arr, int length, int n) {
    char *tempArr = malloc(n * sizeof(char[length]));
    char tempString[length]; 
    char prevString[length];
    char currString[length];
    
    int j = 0;
    memcpy(tempArr, arr, n * length);

    while(j != (n - 1)) {
        for (int i=j+1;i<n;i++) { 
            strcpy(prevString, tempArr + (j * length));
            strcpy(currString, tempArr + (i * length));
            if (strcmp(prevString, currString) > 0) {
                // Swap char array
                strcpy(tempString, prevString); 
                strcpy(tempArr + (j * length), currString); 
                strcpy(tempArr + (i * length), tempString); 
            }
        }
        j++;
    }

    // Check if sorted. Comment out for debugging
    // int x = 0;
    // while(x != n) {
    //     printf("\n %s", tempArr + (x * length));   
    //     x++; 
    // }
    return tempArr;
}

void bubble_sort_users() { 
    char prevFullName[LNAME_LENGTH + FNAME_LENGTH];
    char fullName[LNAME_LENGTH + FNAME_LENGTH];
    char tempFname[FNAME_LENGTH];
    char tempLname[LNAME_LENGTH];
    char tempBday[BDAY_LENGTH];
    char tempGender[GENDER_LENGTH];
    char tempFavColor[FAVCOLOR_LENGTH];
    int tempAge;
    int tempUserId;

    for (int j=0; j<n-1; j++) { 
        for (int i=j+1; i<n; i++) { 
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

void display_users() {
    printf("\n\n----------------------------------------\n");
    printf("               Users: %d            ", n);
    printf("\n----------------------------------------\n");
    
    for(int x=0;x<n;x++) {
        printf("\n-------------------------");
        printf("\nUser id: %d", userId[x]);
        printf("\nFirst name: %s", firstName[x]);
        printf("\nLast name: %s", lastName[x]);
        printf("\nBirthday: %s", birthday[x]);
        printf("\nAge: %d", age[x]);
        printf("\nGender: %s", gender[x]);
        printf("\nFavorite color: %s", favColor[x]);
        printf("\n-------------------------\n\n");
    }
    
}

void add_user() {
    printf("\n\n----------Input user----------\n");

    printf("First name: ");
    fgets(firstName[n], sizeof(firstName[n]), stdin);

    printf("Last name: ");
    fgets(lastName[n], sizeof(lastName[n]), stdin);

    printf("Birthday (eg: 05/02/1992): ");
    scanf("%s", birthday[n]);

    printf("Age: ");
    scanf("%d", &age[n]);

    printf("Gender (M/F): ");
    scanf("%s", gender[n]);
    getchar();

    printf("Favorite color (eg: blue, yellow, midnight blue, etc.): ");
    fgets(favColor[n], sizeof(favColor[n]), stdin);

    userId[n] = 1000 + (n + 1);

    printf("----------Added user!---------- \n\n");
    n++;

    if (n == recordSize) {
        recordSize = recordSize * 2;
        char (*tmpFname) = realloc(firstName, recordSize * sizeof(char[FNAME_LENGTH]));
        if (tmpFname != NULL) {
            firstName = tmpFname;
        }
        free(tmpFname);
    }
}

void delete_user() {
    char *attribute;
    char keyword[20];

    while (strcmp(keyword, "exit") != 0) {
        printf("\nEnter keyword, or else type exit: ");
        scanf("%s", keyword);
        
        printf("\n\nSearching for keyword(s): %s", keyword);

        char *sortedFavColor = bubble_sort_char(favColor, FAVCOLOR_LENGTH, n);
        int foundIndex = sorted_char_binary_search(sortedFavColor, FAVCOLOR_LENGTH, n, keyword);
        // char *sortedLastName = bubble_sort_char(lastName, LNAME_LENGTH, n);

        printf("\n");
    }
}

void input_sample_data() {
    userId[0] = 1001;
    strcpy(firstName[0], "Michael John");
    strcpy(lastName[0], "Diente");
    strcpy(birthday[0], "5/2/1992");
    strcpy(gender[0], "M");
    strcpy(favColor[0], "yellow");
    age[0] = 27;

    n = 1;

    userId[1] = 1002;
    strcpy(firstName[1], "Ali baba");
    strcpy(lastName[1], "Alvarez");
    strcpy(birthday[1], "4/8/1998");
    strcpy(gender[1], "F");
    strcpy(favColor[1], "blue");
    age[1] = 20;

    n = 2;

    userId[2] = 1003;
    strcpy(firstName[2], "Will");
    strcpy(lastName[2], "Johnson");
    strcpy(birthday[2], "2/9/1965");
    strcpy(gender[2], "F");
    strcpy(favColor[2], "white");
    age[2] = 30;

    n = 3;

    userId[3] = 1004;
    strcpy(firstName[3], "Freud");
    strcpy(lastName[3], "Hill");
    strcpy(birthday[3], "1/2/1989");
    strcpy(gender[3], "M");
    strcpy(favColor[3], "magenta");
    age[3] = 65;

    n = 4;
}

int main() {
    userId = malloc(recordSize * sizeof(int));
    firstName = malloc(recordSize * sizeof(char[FNAME_LENGTH]));
    lastName = malloc(recordSize * sizeof(char[LNAME_LENGTH]));
    birthday = malloc(recordSize * sizeof(char[BDAY_LENGTH]));
    gender = malloc(recordSize * sizeof(char[GENDER_LENGTH]));
    favColor = malloc(recordSize * sizeof(char[FAVCOLOR_LENGTH]));
    age = malloc(recordSize * sizeof(int));

    input_sample_data();

    while (command != 0) {
        printf("\n--------------------");
        printf("\nCommands:");
        printf("\n 1 - Add user");
        printf("\n 2 - Display users");
        printf("\n 3 - Delete user");
        printf("\n 4 - Sort");
        printf("\n 0 - Exit");
        printf("\n--------------------");

        printf("\nEnter command: ");
        scanf("%d", &command);
        getchar();

        if (command == 1) {
            add_user();
        } else if (command == 2) {
            display_users();
        } else if (command == 3) {
            delete_user();
        } else if (command == 4) {
            bubble_sort_users();
        } else if (command == 0) {
            free(firstName);
            free(lastName);
            free(birthday);
            free(gender);
            free(favColor);
            free(age);
        }
    }
    return 0;
}
