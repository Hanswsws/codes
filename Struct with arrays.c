#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int age;
    char name[10];
} personinfo;

typedef struct {
    personinfo student;
    int yrlvl;
    int grades[3];
} studentinfo;

typedef struct node {
    studentinfo data;
    struct node* next;
} Node;

// Insert a student at the beginning of the list
void InsertFirst(Node** head, char* name, int age, int yrlvl, int g1, int g2, int g3) {
    Node* newNode = (Node*)malloc(sizeof(Node));


    strcpy(newNode->data.student.name, name);
    newNode->data.student.age = age;
    newNode->data.yrlvl = yrlvl;
    newNode->data.grades[0] = g1;
    newNode->data.grades[1] = g2;
    newNode->data.grades[2] = g3;

    newNode->next = *head;
    *head = newNode;
}

// Calculate average of 3 grades
float computeAverage(int grades[3]) {
    return (grades[0] + grades[1] + grades[2]) / 3.0;
}

// Transfer students with average >= 80 to PassersList
void transferPassers(Node** sourceList, Node** passersList) {
    Node* current = *sourceList;
    while (current != NULL) {
        float avg = (current->data.grades[0] + current->data.grades[1] + current->data.grades[2]) / 3;
        if (avg >= 80.0) {
            InsertFirst(passersList,
                        current->data.student.name,
                        current->data.student.age,
                        current->data.yrlvl,
                        current->data.grades[0],
                        current->data.grades[1],
                        current->data.grades[2]);
        }
        current = current->next;
    }
}

// Print list contents
void printList(Node* head, char* listName) {
    printf("\n%s:\n", listName);
    while (head != NULL) {
        float avg = computeAverage(head->data.grades);
        printf("Name: %s | Age: %d | Year: %d | Grades: %d, %d, %d | Avg: %.2f\n",
               head->data.student.name,
               head->data.student.age,
               head->data.yrlvl,
               head->data.grades[0],
               head->data.grades[1],
               head->data.grades[2],
               avg);
        head = head->next;
    }
}


int main() {
    Node* StudentList = NULL;
    Node* PassersList = NULL;

    // Add 5 students to StudentList
    InsertFirst(&StudentList, "Anna", 18, 1, 90, 85, 88);  // Avg 87.7 ✅
    InsertFirst(&StudentList, "Ben", 19, 2, 75, 78, 72);   // Avg 75.0 ❌
    InsertFirst(&StudentList, "Cara", 20, 3, 82, 80, 85);  // Avg 82.3 ✅
    InsertFirst(&StudentList, "Dino", 21, 4, 60, 70, 65);  // Avg 65.0 ❌
    InsertFirst(&StudentList, "Ella", 22, 1, 95, 92, 90);  // Avg 92.3 ✅

    // Transfer passers
    transferPassers(&StudentList, &PassersList);

    // Print both lists
    printList(StudentList, "All Students");
    printList(PassersList, "Passers (Avg >= 80)");

    return 0;
}
