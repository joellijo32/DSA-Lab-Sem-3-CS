#include <stdio.h>
#include <stdlib.h>

struct Customer {
    int tokenNumber;
    int forms;
};

int main() {
    int front = -1, rear = -1;
    int maxSize = 10; 
    struct Customer queue[10];
    int tokenCounter = 1;

    while (1) {
        int choice;
        printf("\n--- Train Ticket Reservation ---\n");
        printf("1. Add Customer to Queue\n");
        printf("2. Serve Current Customer\n");
        printf("3. Display Current Customer\n");
        printf("4. Display Number of Customers Waiting\n");
        printf("5. Display All Customers in Queue\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if ((front == 0 && rear == maxSize - 1) || (rear + 1) % maxSize == front) {
                printf("Queue is full! Cannot add more customers.\n");
            } else {
                struct Customer c;
                c.tokenNumber = tokenCounter++;

                printf("Enter number of tickets (forms) for customer: ");
                scanf("%d", &c.forms);

                if (front == -1) {
                    front = rear = 0;
                } else {
                    rear = (rear + 1) % maxSize;
                }
                queue[rear] = c;
                printf("Customer with token %d added to the queue.\n", c.tokenNumber);
            }

        } else if (choice == 2) { 
            if (front == -1) {
                printf("No customers in queue.\n");
            } else {
                struct Customer c = queue[front];
                printf("Serving customer with token %d, tickets: %d\n", c.tokenNumber, 1);

                c.forms--;
                if (c.forms > 0) {
                    
                    rear = (rear + 1) % maxSize;
                    queue[rear] = c;
                    printf("Customer with token %d goes to the end of the queue with %d tickets left.\n", c.tokenNumber, c.forms);
                }

                
                if (c.forms == 0) {
                    if (front == rear) {
                        front = rear = -1;
                    } else {
                        front = (front + 1) % maxSize;
                    }
                } else {
                    if (front == rear) {
                        front = rear = -1;
                    } else {
                        front = (front + 1) % maxSize;
                    }
                }
            }

        } else if (choice == 3) { 
            if (front == -1) {
                printf("No customer is being served.\n");
            } else {
                printf("Current customer: Token %d, Tickets left: %d\n", queue[front].tokenNumber, queue[front].forms);
            }

        } else if (choice == 4) { 
            if (front == -1) {
                printf("Number of customers waiting: 0\n");
            } else if (rear >= front) {
                printf("Number of customers waiting: %d\n", rear - front + 1);
            } else {
                printf("Number of customers waiting: %d\n", (maxSize - front) + (rear + 1));
            }

        } else if (choice == 5) { 
            if (front == -1) {
                printf("No customers in queue.\n");
            } else {
                printf("Customers in queue:\n");
                int i = front;
                while (1) {
                    printf("Token %d - Tickets: %d\n", queue[i].tokenNumber, queue[i].forms);
                    if (i == rear) break;
                    i = (i + 1) % maxSize;
                }
            }

        } else if (choice == 6) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
