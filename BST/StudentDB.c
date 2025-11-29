#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define COURSE 4
#define LEN 10

typedef struct {
    char* id;
    char* fName;
    char* lName;
    char* course;
    int year;
} Student;

typedef struct Node{
    Student* student;
    struct Node* LC;
    struct Node* RC;
} Node, *BST;

void enrollStudent(BST* Tree, Student student);
Student* searchStudent(BST* Tree, Student student);
void unenrollStudent(BST* Tree, Student student);
void displayBlock(BST Tree);

int main() {
    BST root = NULL;  
    printf("=== Enrolling Students ===\n");
    Student s1 = {"21104436", "Patrick Charles", "Borres", "IT", 2};
    Student s2 = {"22104079", "Alicia Kate", "Bactasa", "IT", 2};
    Student s3 = {"22105026", "Jer Jurich Matthew", "Ty-Farma", "IT", 2};
    Student s4 = {"24101149", "Lloyd Anton", "Montero", "IT", 2};
    Student s5 = {"24700002", "Sybel Yadeen", "Aquillia", "IT", 2};
    Student s6 = {"21104437", "John", "Doe", "CS", 1};
    Student s7 = {"22104080", "Jane", "Smith", "EE", 2};
    Student s8 = {"22105027", "Bob", "Johnson", "ME", 3};
    Student s9 = {"24101150", "Alice", "Brown", "CS", 4};
    Student s10 = {"24700003", "Charlie", "Davis", "EE", 1};
    Student s11 = {"21104438", "Emma", "Wilson", "IT", 2};
    Student s12 = {"22104081", "Michael", "Taylor", "CS", 3};
    Student s13 = {"22105028", "Sophia", "Anderson", "ME", 1};
    Student s14 = {"24101151", "Daniel", "Thomas", "EE", 4};
    Student s15 = {"24700004", "Olivia", "Jackson", "IT", 2};

    
    enrollStudent(&root, s9);
    enrollStudent(&root, s10);
    enrollStudent(&root, s11);
    enrollStudent(&root, s12);
    enrollStudent(&root, s13);
    enrollStudent(&root, s14);
    enrollStudent(&root, s15);
    enrollStudent(&root, s1);
    enrollStudent(&root, s2);
    enrollStudent(&root, s3);
    enrollStudent(&root, s4);
    enrollStudent(&root, s5);
    enrollStudent(&root, s6);
    enrollStudent(&root, s7);
    enrollStudent(&root, s8);

    displayBlock(root);
    
    
    return 0;


}

void enrollStudent(BST* Tree, Student student) {
    BST* currentStudent = Tree;

    while(*currentStudent != NULL && strcmp((*currentStudent)->student->id, student.id) != 0) {
        currentStudent = strcmp((*currentStudent)->student->id, student.id) > 0 ? &(*currentStudent)->LC : &(*currentStudent)->RC;
    }

    if(*currentStudent != NULL && strcmp((*currentStudent)->student->id, student.id) == 0) return;

    (*currentStudent) = (BST)calloc(1, sizeof(Node));
    (*currentStudent)->student = (Student*)malloc(sizeof(Student));
    (*currentStudent)->student->id = (char*)malloc(sizeof(char) * MAX);
    (*currentStudent)->student->fName = (char*)malloc(sizeof(char) * MAX);
    (*currentStudent)->student->lName = (char*)malloc(sizeof(char) * MAX);
    (*currentStudent)->student->course = (char*)malloc(sizeof(char) * COURSE);
    strcpy((*currentStudent)->student->id, student.id);
    strcpy((*currentStudent)->student->fName, student.fName);
    strcpy((*currentStudent)->student->lName, student.lName);
    strcpy((*currentStudent)->student->course, student.course);
    (*currentStudent)->student->year = student.year;


}

Student* searchStudent(BST* Tree, Student student) {
    BST* temp = Tree;

    while(*temp != NULL && strcmp((*temp)->student->id, student.id) != 0) {
        temp = strcmp((*temp)->student->id, student.id) > 0 ? &(*temp)->LC : &(*temp)->RC;
    }
    return (*temp != NULL) ?  (*temp)->student : NULL;
}

void unenrollStudent(BST* Tree, Student student) {
    BST* currentStudent = Tree;

    while(*currentStudent != NULL && strcmp((*currentStudent)->student->id, student.id) != 0) {
        currentStudent = strcmp((*currentStudent)->student->id, student.id) > 0 ? &(*currentStudent)->LC : &(*currentStudent)->RC;
    }
    
    if(*currentStudent == NULL) {
        printf("Student: %s not found.\n", student.id);
        return;
    }

    Node* temp = *currentStudent;
    printf("Unenrolled Student: %s [%s %s] | %s-%d\n", temp->student->id, temp->student->fName, temp->student->lName, temp->student->course, temp->student->year);

    if(temp->LC == NULL && temp->RC == NULL) {
        free(temp);
        *currentStudent = NULL;
    } else if(temp->LC == NULL || temp->RC == NULL) {
        Node* child = (temp->LC != NULL) ? temp->LC : temp->RC;
        free(temp);
        *currentStudent = child;
    } else {
        BST* succ = &temp->RC;

        while((*succ)->LC != NULL) {
            succ = &(*succ)->LC;
        }

        temp->student = (*succ)->student;

        Node* toDelete = *succ;
        *succ = (toDelete->RC != NULL) ? toDelete->RC : toDelete->LC;
        free(toDelete); 
    }
}

void displayBlock(BST Tree) {
    if(Tree == NULL) return;

    displayBlock(Tree->LC);
    printf("Student: %s [%s %s] | %s-%d\n", Tree->student->id, Tree->student->fName, Tree->student->lName, Tree->student->course, Tree->student->year);
    displayBlock(Tree->RC);
}