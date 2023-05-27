#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
} element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

void error(char* message) {
    fprintf(stderr, "%s", message);
    return;
}

ListNode* search(ListNode* head, element x) {
    ListNode* p = head;

    while (p != NULL) {
        if (strcmp(p->data.name, x.name) == 0)
            return p;
        p = p->link;
    }
    return NULL;
}

ListNode* insert_last(ListNode* head, element value) {
    if (search(head, value) == NULL) {
        ListNode* p = (ListNode*)malloc(sizeof(ListNode));
        p->data = value;
        p->link = NULL;

        if (head == NULL) {
            head = p;
        }
        else {
            ListNode* current = head;
            while (current->link != NULL) {
                current = current->link;
            }
            current->link = p;
        }
        printf("%s has been added.\n", value.name);
    }
    else {
        printf("%s already exists.\n", value.name);
    }

    return head;
}

ListNode* insert_first(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode* delete(ListNode* head, element value, ListNode** deletedListHead) {
    ListNode* found = search(head, value);

    if (found == NULL) {
        printf("%s is not on the list.\n", value.name);
    }
    else {
        if (head == found) {
            *head = *(found->link);
        }
        else {
            ListNode* prev = head;
            while (prev->link != found) {
                prev = prev->link;
            }
            prev->link = found->link;
        }

        printf("%s has been deleted.\n", value.name);
        found->link = *deletedListHead;
        *deletedListHead = found;
    }

    return head;
}

void print_list(ListNode* head) {
    printf("Fruit list:\n");
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%s->", p->data.name);
    printf("NULL\n");
}

void print_deleted_list(ListNode* deletedListHead) {
    printf("Deleted Fruit list: ");
    for (ListNode* p = deletedListHead; p != NULL; p = p->link)
        printf("%s->", p->data.name);
    printf("NULL\n");
}

void delete_list(ListNode* head, ListNode* deletedListHead) {
    ListNode* current = head;
    while (current != NULL) {
        ListNode* next = current->link;
        current->link = deletedListHead;
        deletedListHead = current;
        current = next;
    }
}

int main(void) {
    ListNode* head = NULL;
    ListNode* deletedListHead = NULL;
    element data;
    char fruit[100];

    strcpy_s(data.name, sizeof(data.name), "Peach");
    head = insert_first(head, data);
    strcpy_s(data.name, sizeof(data.name), "Banana");
    head = insert_first(head, data);
    strcpy_s(data.name, sizeof(data.name), "Raspberry");
    head = insert_first(head, data);
    strcpy_s(data.name, sizeof(data.name), "Guava");
    head = insert_first(head, data);
    strcpy_s(data.name, sizeof(data.name), "Plum");
    head = insert_first(head, data);
    strcpy_s(data.name, sizeof(data.name), "Cherry");
    head = insert_first(head, data);
    strcpy_s(data.name, sizeof(data.name), "Grape");
    head = insert_first(head, data);
    strcpy_s(data.name, sizeof(data.name), "Apple");
    head = insert_first(head, data);
    strcpy_s(data.name, sizeof(data.name), "Orange");
    head = insert_first(head, data);
    strcpy_s(data.name, sizeof(data.name), "Mango");
    head = insert_first(head, data);

    int answer;

    while (1) {
        printf("1. Insert new fruit\n");
        printf("2. Delete a fruit\n");
        printf("3. Print the deleted list\n");
        printf("4. Exit\n");
        printf("Enter the menu: ");
        scanf_s("%d", &answer);

        if (answer > 4 || answer < 1) {
            printf("Invalid Menu. Please select again.\n");
        }
        else if (answer == 4) {
            printf("Exit the program.\n\n");
            delete_list(head, &deletedListHead);  
            break;
        }
        else if (answer == 1) {
            printf("Enter the fruit name to add: ");
            scanf_s("%s", fruit, sizeof(fruit));
            strcpy_s(data.name, sizeof(data.name), fruit);
            head = insert_last(head, data);
        }
        else if (answer == 2) {
            printf("Enter the fruit name to delete: ");
            scanf_s("%s", fruit, sizeof(fruit));
            strcpy_s(data.name, sizeof(data.name), fruit);
            head = delete(head, data, &deletedListHead);  
        }
        else if (answer == 3) {
            print_deleted_list(deletedListHead);  
        }
        printf("\n");
        print_list(head);
        printf("\n");
    }

    return 0;
}
