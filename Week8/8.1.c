#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Define the maximum size of the stack
#define MAX 100

// Stack structure
typedef struct Stack {
    int top;
    int items[MAX];
} Stack;

// Function to initialize the stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Function to check if the stack is full
int isFull(Stack* stack) {
    return stack->top == MAX - 1;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->items[stack->top--];
}

// Function to peek at the top element of the stack
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->items[stack->top];
}

// Function to print the stack
void printStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");
}

// Redo and undo functionality
typedef struct History {
    Stack states[MAX];
    int top;
} History;

// Function to initialize the history
void initHistory(History* history) {
    history->top = -1;
}

// Function to save the current state of the stack
void saveState(History* history, Stack* stack) {
    if (history->top == MAX - 1) {
        printf("History overflow\n");
        return;
    }
    history->top++;
    history->states[history->top] = *stack;
}

// Function to undo the last operation
void undo(History* history, Stack* stack) {
    if (history->top == -1) {
        printf("No actions to undo\n");
        return;
    }
    *stack = history->states[history->top--];
}

// Function to evaluate a mathematical expression in infix notation
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int evaluate(char* tokens) {
    int i;
    
    Stack values;
    initStack(&values);
    
    Stack ops;
    initStack(&ops);
    
    for (i = 0; i < strlen(tokens); i++) {
        
        if (tokens[i] == ' ') {
            continue;
        }
        
        if (tokens[i] == '(') {
            push(&ops, tokens[i]);
        }
        
        else if (isdigit(tokens[i])) {
            int val = 0;
            
            while (i < strlen(tokens) && isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            
            push(&values, val);
            i--;
        }
        
        else if (tokens[i] == ')') {
            while (!isEmpty(&ops) && peek(&ops) != '(') {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                
                push(&values, applyOp(val1, val2, op));
            }
            
            if (!isEmpty(&ops)) {
                pop(&ops);
            }
        }
        
        else {
            while (!isEmpty(&ops) && precedence(peek(&ops)) >= precedence(tokens[i])) {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                
                push(&values, applyOp(val1, val2, op));
            }
            
            push(&ops, tokens[i]);
        }
    }
    
    while (!isEmpty(&ops)) {
        int val2 = pop(&values);
        int val1 = pop(&values);
        char op = pop(&ops);
        
        push(&values, applyOp(val1, val2, op));
    }
    
    return pop(&values);
}

int main() {
    Stack stack;
    initStack(&stack);
    History history;
    initHistory(&history);

    int choice, value;
    char expr[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push an element onto the stack\n");
        printf("2. Pop an element from the stack\n");
        printf("3. Peek at the top element of the stack\n");
        printf("4. Print the stack\n");
        printf("5. Undo\n");
        printf("6. Evaluate a mathematical expression\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &value);
                saveState(&history, &stack);
                push(&stack, value);
                break;
            case 2:
                saveState(&history, &stack);
                value = pop(&stack);
                if (value != -1) {
                    printf("Popped element: %d\n", value);
                }
                break;
            case 3:
                value = peek(&stack);
                if (value != -1) {
                    printf("Top element: %d\n", value);
                }
                break;
            case 4:
                printStack(&stack);
                break;
            case 5:
                undo(&history, &stack);
                printf("Undo operation completed.\n");
                printStack(&stack);
                break;
            case 6:
                printf("Enter a mathematical expression in infix notation: ");
                scanf(" %[^\n]", expr);
                printf("Result of the expression: %d\n", evaluate(expr));
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
