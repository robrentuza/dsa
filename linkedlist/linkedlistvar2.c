#include <stdio.h>
#include <stdlib.h>
#define MAX10

typedef struct node{
    int data;
    struct node* next;
}Node;

typedef struct{
    Node* head;
    int count;
}List;


List* initialize() {
    List *list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->count = 0;
    return list;
}

void empty(List *list) {
    Node *current = list->head;
    Node *temp;
    
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    
    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;

    list->count++;
}


void insertLast(List *list, int data){
 Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
     if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->count++;
}

void insertPos(List *list, int data, int index) {
    if (index < 0 || index > list->count) {
        return;
    }
    
    if (index == 0) {
        insertFirst(list, data);
        return;
    }
    
    if (index == list->count) {
        insertLast(list, data);
        return;
    }
    
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    
    Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    list->count++;
}

void deleteStart(List *list) {
    if (list->head == NULL) {
        return;
    }
    
    Node *current = list->head;
    list->head = current->next;
    free(current);
    list->count--;
}

void deleteLast(List *list) {
    if (list->head == NULL) {
        return;
    }
    
    if (list->count == 1) {
        free(list->head);
        list->head = NULL;
        list->count--;
        return;
    }
    
    Node *current = list->head;
    for (int i = 0; i < list->count - 2; i++) {
        current = current->next;
    }
    
    free(current->next);
    current->next = NULL;
    list->count--;
}

void deletePos(List *list, int index) {
    if (index < 0 || index >= list->count || list->head == NULL) {
        return;
    }
    
    if (index == 0) {
        deleteStart(list);
        return;
    }
    
    Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    list->count--;
}

int retrieve(List *list, int index) {
    if (index < 0 || index >= list->count) {
        return -1;
    }
    
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

int locate(List *list, int data) {
    if (list->head == NULL) {
        return -1;
    }
    
    Node *current = list->head;
    int index = 0;
    
    while (current != NULL) {
        if (current->data == data) {
            return index;
        }
        current = current->next;
        index++;
    }
    
    return -1;
}

void display(List *list) {
    Node *current = list->head;
    
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    List *list = initialize();
    
    insertFirst(list, 2);
    insertFirst(list, 6);
    insertFirst(list, 5);
    display(list);
    
    insertLast(list, 7);
    display(list);
    
    insertPos(list, 9, 2);
    display(list);
    
    deleteStart(list);
    display(list);
    
    deleteLast(list);
    display(list);
    
    deletePos(list, 1);
    display(list);
    
    printf("Element at index 1: %d\n", retrieve(list, 1));
    printf("Location of 9: %d\n", locate(list, 9));
    
    empty(list);
    free(list);
    
    return 0;
}


