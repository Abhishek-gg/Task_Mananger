#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int id;
    char description[100];
    int isImportant;
    int isCompleted;
    struct Task *next;
} Task;

Task *head = NULL;
int taskCounter = 0;



void addTask() {
    Task *newTask = (Task *)malloc(sizeof(Task));
    printf("Enter task description: ");
    getchar(); 
    fgets(newTask->description, 100, stdin);
    newTask->description[strcspn(newTask->description, "\n")] = '\0'; 
    newTask->id = ++taskCounter; 
    newTask->isImportant = 0;
    newTask->isCompleted = 0;
    newTask->next = head;
    head = newTask;
    printf("Task added successfully with ID: %d\n", newTask->id);
}

void removeTask() {
    int id;
    printf("Enter the task ID to remove: ");
    scanf("%d", &id);

    Task *current = head;
    Task *previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Task with ID %d removed successfully.\n", id);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Task with ID %d not found.\n", id);
}

void markImportant() {
    int id;
    printf("Enter the task ID to mark as important: ");
    scanf("%d", &id);

    Task *current = head;
    while (current != NULL) {
        if (current->id == id) {
            current->isImportant = 1;
            printf("Task with ID %d marked as important.\n", id);
            return;
        }
        current = current->next;
    }
    printf("Task with ID %d not found.\n", id);
}

void markCompleted() {
    int id;
    printf("Enter the task ID to mark as completed: ");
    scanf("%d", &id);

    Task *current = head;
    while (current != NULL) {
        if (current->id == id) {
            current->isCompleted = 1;
            printf("Task with ID %d marked as completed.\n", id);
            return;
        }
        current = current->next;
    }
    printf("Task with ID %d not found.\n", id);
}

void displayTasks() {
    Task *current = head;
    if (current == NULL) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n--- Pending Tasks ---\n");
    while (current != NULL) {
        if (!current->isCompleted) {
            printf("ID: %d | Description: %s | Important: %s\n",
                   current->id,
                   current->description,
                   current->isImportant ? "Yes" : "No");
        }
        current = current->next;
    }

    current = head;
    printf("\n--- Completed Tasks ---\n");
    while (current != NULL) {
        if (current->isCompleted) {
            printf("ID: %d | Description: %s | Important: %s\n",
                   current->id,
                   current->description,
                   current->isImportant ? "Yes" : "No");
        }
        current = current->next;
    }
}

void displayMenu() {
    printf("\nDaily Task Manager\n");
    printf("1. Add Task\n");
    printf("2. Remove Task\n");
    printf("3. Mark Task as Important\n");
    printf("4. Mark Task as Completed\n");
    printf("5. Display Tasks\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                removeTask();
                break;
            case 3:
                markImportant();
                break;
            case 4:
                markCompleted();
                break;
            case 5:
                displayTasks();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    
    Task *current = head;
    while (current != NULL) {
        Task *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
