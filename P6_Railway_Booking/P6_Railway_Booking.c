#include <stdio.h>
#include <string.h>

struct Customer {
    char name[30];
    int token_number;
    int forms_needed;
};

struct Customer queue[10];
int total_customers = 0;
int current_serving = 0;
int next_token = 1;

void addCustomer(char name[], int forms) {
    strcpy(queue[total_customers].name, name);
    queue[total_customers].token_number = next_token;
    queue[total_customers].forms_needed = forms;
    
    printf("Token issued: %s - Token No. %d - Forms: %d\n", name, next_token, forms);
    
    next_token++;
    total_customers++;
}

void showCurrentCustomer() {
    printf("\nCurrent customer being served:\n");
    if (current_serving < total_customers) {
        printf("Name: %s\n", queue[current_serving].name);
        printf("Token Number: %d\n", queue[current_serving].token_number);
        printf("Forms requested: %d\n", queue[current_serving].forms_needed);
    } else {
        printf("No customer is currently being served.\n");
    }
}

void showWaitingCount() {
    int waiting = total_customers - current_serving;
    if (current_serving < total_customers) {
        waiting = waiting - 1;
    }
    printf("\nNumber of customers waiting: %d\n", waiting);
}

void showAllCustomers() {
    printf("\nList of all customers in queue:\n");
    
    for (int i = 0; i < total_customers; i++) {
        printf("Token %d: %s (Forms: %d)", 
               queue[i].token_number, 
               queue[i].name, 
               queue[i].forms_needed);
        
        if (i < current_serving) {
            printf(" - Service completed\n");
        } else if (i == current_serving) {
            printf(" - Currently being served\n");
        } else {
            printf(" - Waiting\n");
        }
    }
}

void serveNext() {
    if (current_serving < total_customers) {
        printf("\nService completed for %s (Token %d)\n", 
               queue[current_serving].name, 
               queue[current_serving].token_number);
        
        current_serving++;
        
        if (current_serving < total_customers) {
            printf("Now serving: %s (Token %d)\n", 
                   queue[current_serving].name,
                   queue[current_serving].token_number);
        } else {
            printf("All customers have been served.\n");
        }
    } else {
        printf("No customers to serve.\n");
    }
}

int main() {
    
    
    int choice;
    char name[30];
    int forms;
    
    printf("\nRailway Reservation System\n");
    
    do {
        printf("\nMenu Options:\n");
        printf("1. Display current customer being served\n");
        printf("2. Display number of customers waiting\n");
        printf("3. Display all customers in queue\n");
        printf("4. Add new customer\n");
        printf("5. Complete current service\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        if (choice == 1) {
            showCurrentCustomer();
        } else if (choice == 2) {
            showWaitingCount();
        } else if (choice == 3) {
            showAllCustomers();
        } else if (choice == 4) {
            printf("Enter customer name: ");
            scanf("%s", name);
            printf("Enter number of forms: ");
            scanf("%d", &forms);
            addCustomer(name, forms);
        } else if (choice == 5) {
            serveNext();
        } else if (choice == 6) {
            printf("System closed.\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }
        
    } while (choice != 6);
    
    return 0;
}