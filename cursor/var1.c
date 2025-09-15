#include <stdio.h>
#define MAX 4

typedef struct {
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

typedef int List;

void initialize(VHeap *V) {
    V->avail = 0;
    for (int i = 0; i < MAX - 1; i++) {
        V->H[i].next = i + 1;
    }
    V->H[MAX - 1].next = -1;
}

int allocSpace(VHeap* V) {
    int idx = V->avail;
    if (idx != -1) {
        V->avail = V->H[idx].next;
    }
    return idx;
}

void deallocSpace(VHeap* V, int index) {
    V->H[index].next = V->avail;
    V->avail = index;
}

void insertFirst(int* L, VHeap* V, int elem) {
    int idx = allocSpace(V);
    if (idx != -1) {
        V->H[idx].elem = elem;
        V->H[idx].next = *L;
        *L = idx;
    } else {
        printf("No space to insert\n");
    }
}

void insertLast(int* L, VHeap* V, int elem) {
    int idx = allocSpace(V);
    if (idx != -1) {
        V->H[idx].elem = elem;
        V->H[idx].next = -1;
        if (*L == -1) {
            *L = idx;
        } else {
            int p = *L;
            while (V->H[p].next != -1) {
                p = V->H[p].next;
            }
            V->H[p].next = idx;
        }
    } else {
        printf("No space to insert\n");
    }
}

void insertSorted(int* L, VHeap* V, int elem) {
    int idx = allocSpace(V);
    if (idx == -1) {
        printf("No space to insert\n");
        return;
    }
    V->H[idx].elem = elem;
    if (*L == -1 || V->H[*L].elem >= elem) {
        V->H[idx].next = *L;
        *L = idx;
        return;
    }
    int p = *L;
    while (V->H[p].next != -1 && V->H[V->H[p].next].elem < elem) {
        p = V->H[p].next;
    }
    V->H[idx].next = V->H[p].next;
    V->H[p].next = idx;
}

void delete(int* L, VHeap* V, int elem) {
    int p = *L;
    int prev = -1;
    while (p != -1 && V->H[p].elem != elem) {
        prev = p;
        p = V->H[p].next;
    }
    if (p == -1) {
        printf("Element not found\n");
        return;
    }
    if (prev == -1) {
        *L = V->H[p].next;
    } else {
        V->H[prev].next = V->H[p].next;
    }
    deallocSpace(V, p);
}

void deleteAllOccurrence(int* L, VHeap* V, int elem) {
    int p = *L;
    int prev = -1;
    while (p != -1) {
        if (V->H[p].elem == elem) {
            int temp = p;
            if (prev == -1) {
                *L = V->H[p].next;
                p = *L;
            } else {
                V->H[prev].next = V->H[p].next;
                p = V->H[p].next;
            }
            deallocSpace(V, temp);
        } else {
            prev = p;
            p = V->H[p].next;
        }
    }
}

void display(int L, VHeap V) {
    int p = L;
    while (p != -1) {
        printf("%d ", V.H[p].elem);
        p = V.H[p].next;
    }
    printf("\n");
}

int main() {
    VHeap V;
    int L = -1;

    initialize(&V);

    insertLast(&L, &V, 10);
    insertLast(&L, &V, 20);
    insertFirst(&L, &V, 5);
    insertSorted(&L, &V, 15);
    display(L, V);

    delete(&L, &V, 10);
    display(L, V);

    insertLast(&L, &V, 20);
    insertLast(&L, &V, 20);
    display(L, V);

    deleteAllOccurrence(&L, &V, 20);
    display(L, V);

    return 0;
}
