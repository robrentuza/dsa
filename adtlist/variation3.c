#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);
List resize(List L);
List insertFirst(List L, int data);
List insertLast(List L, int data);
List deleteFirst(List L);
List deleteLast(List L);
List deleteByValue(List L, int data);

List initialize(List L) {
    L.elemPtr = (int*)malloc(sizeof(int) * LENGTH);
    L.max = LENGTH;
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position) {
    if (L.count == L.max) {
        L = resize(L);
    }
    
    for (int i = L.count; i > position; i--) {
        L.elemPtr[i] = L.elemPtr[i - 1];
    }
    
    L.elemPtr[position] = data;
    L.count++;
    
    return L;
}

List deletePos(List L, int position) {
    for (int i = position; i < L.count - 1; i++) {
        L.elemPtr[i] = L.elemPtr[i + 1];
    }
    
    L.count--;
    return L;
}

int locate(List L, int data) {
    for (int i = 0; i < L.count; i++) {
        if (L.elemPtr[i] == data) {
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data) {
    if (L.count == L.max) {
        L = resize(L);
    }
    
    int position = 0;
    while (position < L.count && L.elemPtr[position] < data) {
        position++;
    }
    
    return insertPos(L, data, position);
}

void display(List L) {
    printf("List contents: [ ");
    for (int i = 0; i < L.count; i++) {
        printf("%d", L.elemPtr[i]);
        if (i < L.count - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
    printf("Count: %d, Max: %d\n", L.count, L.max);
}

List resize(List L) {
    int newMax = L.max * 2;
    int *newPtr = (int*)realloc(L.elemPtr, sizeof(int) * newMax);

    L.elemPtr = newPtr;
    L.max = newMax;
    return L;
}

List insertFirst(List L, int data) {
    return insertPos(L, data, 0);
}

List insertLast(List L, int data) {
    return insertPos(L, data, L.count);
}

List deleteFirst(List L) {
    return deletePos(L, 0);
}

List deleteLast(List L) {
    return deletePos(L, L.count - 1);
}

List deleteByValue(List L, int data) {
    int position = locate(L, data);
    if (position != -1) {
        return deletePos(L, position);
    }
    return L;
}

int main() {
    List L;
    L = initialize(L);
    
    printf("Inserting elements:\n");
    L = insertLast(L, 1);
    L = insertLast(L, 3);
    L = insertLast(L, 2);
    L = insertLast(L, 5);
    display(L);
    
    printf("\nInserting 4 at position 2:\n");
    L = insertPos(L, 4, 2);
    display(L);
    
    printf("\nDeleting element at position 1:\n");
    L = deletePos(L, 1);
    display(L);
    
    printf("\nInserting 8 in sorted order:\n");
    L = insertSorted(L, 8);
    display(L);
    
    printf("\nDeleting element with value 4:\n");
    L = deleteByValue(L, 4);
    display(L);
    
    printf("\nLocating value 5: Position %d\n", locate(L, 5));
    printf("Locating value 99: Position %d\n", locate(L, 99));
    
    free(L.elemPtr);
    return 0;
}