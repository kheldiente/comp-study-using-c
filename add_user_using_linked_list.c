#include <stdio.h>
#include <stdlib.h>

#define FNAME_LENGTH 30
#define LNAME_LENGTH 30
#define BDAY_LENGTH 9
#define GENDER_LENGTH 2
#define FAVCOLOR_LENGTH 15

struct Node {
  char firstName[FNAME_LENGTH];
  char lastName[LNAME_LENGTH];
  char birthday[BDAY_LENGTH];
  char gender[GENDER_LENGTH];
  char favColor[FAVCOLOR_LENGTH];
  int age;
  struct Node *next;
};

typedef struct Node DATA_NODE;

DATA_NODE *headNode, *firstNode, *tempNode = 0, *prevNode, nextNode;

int n = 0;
int command = -1;

void swap(DATA_NODE *a, DATA_NODE *b) { 
  char tempFname[FNAME_LENGTH];
  char tempLname[LNAME_LENGTH];
  char tempBday[BDAY_LENGTH];
  char tempGender[GENDER_LENGTH];
  char tempFavColor[FAVCOLOR_LENGTH];
  int tempAge;
  
  strcpy(tempFname, a->firstName);
  strcpy(tempLname, a->lastName);
  strcpy(tempBday, a->birthday);
  strcpy(tempGender, a->gender);
  strcpy(tempFavColor, a->favColor);
  tempAge = a->age;

  strcpy(a->firstName, b->firstName);
  strcpy(b->firstName, tempFname);

  strcpy(a->lastName, b->lastName);
  strcpy(b->lastName, tempLname);

  strcpy(a->birthday, b->birthday);
  strcpy(b->birthday, tempBday);

  strcpy(a->gender, b->gender);
  strcpy(b->gender, tempGender);

  strcpy(a->favColor, b->favColor);
  strcpy(b->favColor, tempFavColor);

  a->age = b->age; 
  b->age = tempAge; 
} 

void bubble_sort() { 
    int swapped, i; 
    DATA_NODE *ptr1; 
    DATA_NODE *lptr = NULL; 

    char prevFullName[LNAME_LENGTH + FNAME_LENGTH];
    char fullName[LNAME_LENGTH + FNAME_LENGTH];
  
    if (firstNode == NULL) 
        return; 
  
    do { 
        swapped = 0; 
        ptr1 = firstNode; 
  
        while (ptr1->next != lptr) { 
            strcpy(prevFullName, ptr1->lastName);
            strcat(prevFullName, ptr1->firstName);

            strcpy(fullName, ptr1->next->lastName);
            strcat(fullName, ptr1->next->firstName);
            if (strcmp(prevFullName, fullName)) {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}

void insert_user() {
  char fName[FNAME_LENGTH];
  char lName[LNAME_LENGTH];
  char bday[BDAY_LENGTH];
  char gender[GENDER_LENGTH];
  char favColor[FAVCOLOR_LENGTH];
  int age;

  printf("\n\n----------Input user----------\n");

  printf("First name: ");
  fgets(fName, sizeof(fName), stdin);

  printf("Last name: ");
  fgets(lName, sizeof(lName), stdin);

  printf("Birthday (eg: 05/02/1992): ");
  scanf("%s", bday);

  printf("Age: ");
  scanf("%d", &age);

  printf("Gender (M/F): ");
  scanf("%s", gender);
  getchar();

  printf("Favorite color (eg: blue, yellow, midnight blue, etc.): ");
  fgets(favColor, sizeof(favColor), stdin);

  tempNode = (DATA_NODE *) malloc(sizeof(DATA_NODE));

  strcpy(tempNode->firstName, fName);
  strcpy(tempNode->lastName, lName);
  strcpy(tempNode->birthday, bday);
  strcpy(tempNode->gender, gender);
  strcpy(tempNode->favColor, favColor);
  tempNode->age = age;

  if (firstNode == 0) {
    firstNode = tempNode;
  } else {
    headNode->next = tempNode;
  }
  tempNode->next = 0;
  headNode = tempNode;
  fflush(stdin);
}

void update_user() {
  char keyword[30];
  char value[30];
  int attribute = -1;
  
  char tempFname[FNAME_LENGTH];
  char tempLname[LNAME_LENGTH];
  char tempBday[BDAY_LENGTH];
  char tempGender[GENDER_LENGTH];
  char tempFavColor[FAVCOLOR_LENGTH];
  int tempAge;

  tempNode = firstNode;

  printf("\nEnter keyword, or else type exit: ");
  scanf("%s", keyword);
  
  printf("\nSearching for keyword(s): %s", keyword);
  while (tempNode != 0) {
    strcpy(tempFname, tempNode->firstName);
    strcpy(tempLname, tempNode->lastName);
    strcpy(tempBday, tempNode->birthday);
    strcpy(tempGender, tempNode->gender);
    strcpy(tempFavColor, tempNode->favColor);
    tempAge = tempNode->age;

    strtok(tempFname, "\n");
    strtok(tempLname,"\n");
    strtok(tempBday, "\n");
    strtok(tempGender, "\n");
    strtok(tempFavColor, "\n");

    int resFname = strcmp(tempFname, keyword);
    int resLname = strcmp(tempLname, keyword);
    int resBday = strcmp(tempBday, keyword);
    int resGender = strcmp(tempGender, keyword);
    int resFavColor = strcmp(tempFavColor, keyword);

    if (resFname == 0
    || resLname == 0
    || resBday == 0
    || resGender == 0
    || resFavColor == 0) {
      
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
          strcpy(tempNode->firstName, value);
      } else if (attribute == 2) {
          strcpy(tempNode->lastName, value);
      } else if (attribute == 3) {
          strcpy(tempNode->birthday, value);
      } else if (attribute == 4) {
          strcpy(tempNode->gender, value);
      } else if (attribute == 5) {
          strcpy(tempNode->favColor, value);
      }
      break;
    }
    tempNode = tempNode -> next;
  }
}

void delete_user() {
  int i = 0;
  int pos = 1;
  int countValue = count_users();
  char keyword[30];
  char yes[2] = "n";
  
  char tempFname[FNAME_LENGTH];
  char tempLname[LNAME_LENGTH];
  char tempBday[BDAY_LENGTH];
  char tempGender[GENDER_LENGTH];
  char tempFavColor[FAVCOLOR_LENGTH];
  int tempAge;

  tempNode = firstNode;

  printf("\nEnter keyword, or else type exit: ");
  scanf("%s", keyword);

  while (tempNode != 0) {
    strcpy(tempFname, tempNode->firstName);
    strcpy(tempLname, tempNode->lastName);
    strcpy(tempBday, tempNode->birthday);
    strcpy(tempGender, tempNode->gender);
    strcpy(tempFavColor, tempNode->favColor);
    tempAge = tempNode->age;

    strtok(tempFname, "\n");
    strtok(tempLname,"\n");
    strtok(tempBday, "\n");
    strtok(tempGender, "\n");
    strtok(tempFavColor, "\n");

    int resFname = strcmp(tempFname, keyword);
    int resLname = strcmp(tempLname, keyword);
    int resBday = strcmp(tempBday, keyword);
    int resGender = strcmp(tempGender, keyword);
    int resFavColor = strcmp(tempFavColor, keyword);

    if (resFname == 0
    || resLname == 0
    || resBday == 0
    || resGender == 0
    || resFavColor == 0) {
      if (i == 0) {
        tempNode = tempNode->next;
        firstNode = tempNode;
      } else {
        prevNode->next = tempNode->next;
        if (i == (countValue - 1)) {
          headNode = prevNode;
        }
      }
      printf("\nDeleted Successfully \n\n");
      break;
    } else {
      i++;
      prevNode = tempNode;
      tempNode = tempNode -> next;
    }
  }
}

void display_user(DATA_NODE *node) {
  char tempFname[FNAME_LENGTH];
  char tempLname[LNAME_LENGTH];
  char tempBday[BDAY_LENGTH];
  char tempGender[GENDER_LENGTH];
  char tempFavColor[FAVCOLOR_LENGTH];
  int tempAge;

  strcpy(tempFname, node->firstName);
  strcpy(tempLname, node->lastName);
  strcpy(tempBday, node->birthday);
  strcpy(tempGender, node->gender);
  strcpy(tempFavColor, node->favColor);
  tempAge = node->age;

  strtok(tempFname, "\n");
  strtok(tempLname,"\n");
  strtok(tempBday, "\n");
  strtok(tempGender, "\n");
  strtok(tempFavColor, "\n");

  printf("\n-------------------------");
  printf("\nFirst name: %s", tempFname);
  printf("\nLast name: %s", tempLname);
  printf("\nBirthday: %s", tempBday);
  printf("\nAge: %d", tempAge);
  printf("\nGender: %s", tempGender);
  printf("\nFavorite color: %s", tempFavColor);
  printf("\n-------------------------\n\n");
}

void display_users() {
  tempNode = firstNode;
  while (tempNode != 0) {
    display_user(tempNode);
    tempNode = tempNode -> next;
  }
}

void search_user() {
  char keyword[30];
  char tempFname[FNAME_LENGTH];
  char tempLname[LNAME_LENGTH];
  char tempBday[BDAY_LENGTH];
  char tempGender[GENDER_LENGTH];
  char tempFavColor[FAVCOLOR_LENGTH];
  int tempAge;

  while (strcmp(keyword, "exit") != 0) {
    printf("\Enter keyword or else type exit: ");
    scanf("%s", keyword);

    tempNode = firstNode;
    
    while (tempNode != 0) {
      strcpy(tempFname, tempNode->firstName);
      strcpy(tempLname, tempNode->lastName);
      strcpy(tempBday, tempNode->birthday);
      strcpy(tempGender, tempNode->gender);
      strcpy(tempFavColor, tempNode->favColor);
      tempAge = tempNode->age;

      strtok(tempFname, "\n");
      strtok(tempLname,"\n");
      strtok(tempBday, "\n");
      strtok(tempGender, "\n");
      strtok(tempFavColor, "\n");

      int resFname = strcmp(tempFname, keyword);
      int resLname = strcmp(tempLname, keyword);
      int resBday = strcmp(tempBday, keyword);
      int resGender = strcmp(tempGender, keyword);
      int resFavColor = strcmp(tempFavColor, keyword);

      if (resFname == 0
      || resLname == 0
      || resBday == 0
      || resGender == 0
      || resFavColor == 0) {
        display_user(tempNode);
        break;
      }
      tempNode = tempNode -> next;
    }
  }
}

int count_users() {
  int count = 0;
  tempNode = firstNode;
  while (tempNode != 0) {
    count++;
    tempNode = tempNode -> next;
  }
  return count;
}

int main() {
    int command = -1;
    while (command != 0) {
        printf("\n--------------------");
        printf("\nCommands -- Linked List");
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
