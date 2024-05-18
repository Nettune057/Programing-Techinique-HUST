#include <stdio.h>
#include <stdlib.h>

// Node structure for the singly linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add a node at the end of the list
void addNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to update a node's value
void updateNode(struct Node* head, int oldData, int newData) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == oldData) {
            temp->data = newData;
            printf("Updated node with value %d to %d\n", oldData, newData);
            return;
        }
        temp = temp->next;
    }
    printf("Element %d not found in the list.\n", oldData);
}

// Function to delete a node
void deleteNode(struct Node** head, int data) {
    struct Node* temp = *head;
    struct Node* prev = NULL;
    
    // If the node to be deleted is the head
    if (temp != NULL && temp->data == data) {
        *head = temp->next;
        free(temp);
        printf("Deleted node with value %d\n", data);
        return;
    }

    // Search for the node to be deleted
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    // If the node was not found
    if (temp == NULL) {
        printf("Element %d not found in the list.\n", data);
        return;
    }

    // Unlink the node from the list
    prev->next = temp->next;
    free(temp);
    printf("Deleted node with value %d\n", data);
}

// Function to search for an element in the list
void searchNode(struct Node* head, int data) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            printf("Element %d found in the list.\n", data);
            return;
        }
        temp = temp->next;
    }
    printf("Element %d not found in the list.\n", data);
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to input a linked list
void inputList(struct Node** head, int n) {
    int data;
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);
        addNode(head, data);
    }
}

int main() {
    struct Node* head = NULL;
    int n, choice, data, oldData, newData;

    // Inputting the linked list
    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &n);
    inputList(&head, n);

    // Menu-driven program to perform various operations
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add an element\n");
        printf("2. Update an element\n");
        printf("3. Delete an element\n");
        printf("4. Search an element\n");
        printf("5. Print the list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to add: ");
                scanf("%d", &data);
                addNode(&head, data);
                break;
            case 2:
                printf("Enter the element to update: ");
                scanf("%d", &oldData);
                printf("Enter the new value: ");
                scanf("%d", &newData);
                updateNode(head, oldData, newData);
                break;
            case 3:
                printf("Enter the element to delete: ");
                scanf("%d", &data);
                deleteNode(&head, data);
                break;
            case 4:
                printf("Enter the element to search: ");
                scanf("%d", &data);
                searchNode(head, data);
                break;
            case 5:
                printList(head);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
