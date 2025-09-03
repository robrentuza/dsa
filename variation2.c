#include <stdio.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

List initialize(List L) {
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position) {
    for (int i = L.count; i >= position; i--) {
        L.elem[i] = L.elem[i - 1];
    }

    L.elem[position - 1] = data;
    L.count++;
    return L;
}

List deletePos(List L, int position) {
    for (int i = position; i < L.count; i++) {
        L.elem[i - 1] = L.elem[i];
    }
    L.count--;
    return L;
}

int locate(List L, int data) {
    for (int i = 0; i < L.count; i++) {
        if (L.elem[i] == data) {
            return i + 1;
        }
    }
    return -1;
}

List insertSorted(List L, int data) {
    int pos = 1;
    while (pos <= L.count && L.elem[pos - 1] < data) {
        pos++;
    }
    return insertPos(L, data, pos);
}

void display(List L) {
    printf("List elements: ");
    for (int i = 0; i < L.count; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

int main() {
    List L;
    L = initialize(L);

    L = insertPos(L, 1, 1);
    L = insertPos(L, 3, 2);
    L = insertPos(L, 2, 3);
    L = insertPos(L, 5, 4);

    display(L);

    L = insertPos(L, 4, 3);
    display(L);

    L = deletePos(L, 1);
    display(L);

    int pos = locate(L, 3);
    printf("Position of 3: %d\n", pos);

    L = initialize(L);
    L = insertSorted(L, 1);
    L = insertSorted(L, 3);
    L = insertSorted(L, 5);
    L = insertSorted(L, 10);
    display(L);

    L = insertSorted(L, 8);
    display(L);

    return 0;
}