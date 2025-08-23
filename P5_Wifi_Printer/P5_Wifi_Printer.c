#include <stdio.h>
#include <string.h>


struct PrintJob {
    char teacher[30];
    char document[50];
    int pages;
};


struct PrintJob queue[10];
int job_count = 0;
int current_job = 0; 


void addJob(char teacher[], char document[], int pages) {
    if (job_count < 10) {
        strcpy(queue[job_count].teacher, teacher);
        strcpy(queue[job_count].document, document);
        queue[job_count].pages = pages;
        job_count++;
        printf("Added: %s by %s\n", document, teacher);
    } else {
        printf("Print queue is full!\n");
    }
}


void showCurrentJob() {
    printf("\n--- Currently Printing ---\n");
    if (job_count == 0) {
        printf("No jobs in queue\n");
    } else if (current_job < job_count) {
        printf("Teacher: %s\n", queue[current_job].teacher);
        printf("Document: %s\n", queue[current_job].document);
        printf("Pages: %d\n", queue[current_job].pages);
        printf("Print time: %.1f minutes\n", queue[current_job].pages / 30.0);
    } else {
        printf("All jobs completed\n");
    }
}


void showWaitingTime(char document[]) {
    int found = 0;
    float wait_time = 0;
    
    printf("\n--- Waiting Time ---\n");
    
    for (int i = 0; i < job_count; i++) {
        if (strcmp(queue[i].document, document) == 0) {
            found = 1;
            if (i < current_job) {
                printf("Document already printed\n");
            } else if (i == current_job) {
                printf("Document is currently printing\n");
            } else {
                // Calculate waiting time
                for (int j = current_job; j < i; j++) {
                    wait_time += queue[j].pages / 30.0;
                }
                printf("Document: %s\n", document);
                printf("Waiting time: %.1f minutes\n", wait_time);
            }
            break;
        }
    }
    
    if (!found) {
        printf("Document not found in queue\n");
    }
}


void showMaxWaitTeacher() {
    printf("\n--- Teacher with Maximum Wait ---\n");
    
    if (job_count == 0) {
        printf("No jobs in queue\n");
        return;
    }
    
    float max_wait = 0;
    int max_index = current_job;
    
    for (int i = current_job; i < job_count; i++) {
        float wait_time = 0;
        for (int j = current_job; j < i; j++) {
            wait_time += queue[j].pages / 30.0;
        }
        if (wait_time > max_wait) {
            max_wait = wait_time;
            max_index = i;
        }
    }
    
    if (max_index < job_count) {
        printf("Teacher: %s\n", queue[max_index].teacher);
        printf("Document: %s\n", queue[max_index].document);
        printf("Wait time: %.1f minutes\n", max_wait);
    }
}


void nextJob() {
    if (current_job < job_count) {
        printf("\nFinished printing: %s\n", queue[current_job].document);
        current_job++;
        if (current_job < job_count) {
            printf("Now printing: %s\n", queue[current_job].document);
        } else {
            printf("All jobs completed!\n");
        }
    } else {
        printf("No more jobs to print\n");
    }
}


void showAllJobs() {
    printf("\n--- Print Queue ---\n");
    if (job_count == 0) {
        printf("No jobs in queue\n");
        return;
    }
    
    for (int i = 0; i < job_count; i++) {
        if (i == current_job) {
            printf("* %d. %s - %s (%d pages) [PRINTING]\n", 
                   i+1, queue[i].teacher, queue[i].document, queue[i].pages);
        } else if (i < current_job) {
            printf("  %d. %s - %s (%d pages) [DONE]\n", 
                   i+1, queue[i].teacher, queue[i].document, queue[i].pages);
        } else {
            printf("  %d. %s - %s (%d pages) [WAITING]\n", 
                   i+1, queue[i].teacher, queue[i].document, queue[i].pages);
        }
    }
}

int main() {
    
    
    
    int choice;
    char teacher[30], document[50];
    int pages;
    
    printf("=== WiFi Printer Simulation ===\n");
    
    do {
        printf("\n1. Add new document\n");
        printf("2. Check waiting time for document\n");
        printf("3. Show teacher with max wait\n");
        printf("4. Show currently printing\n");
        printf("5. Complete current job\n");
        printf("6. Show all jobs\n");
        printf("7. Exit\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 4:
                showCurrentJob();
                break;
                
            case 2:
                printf("Enter document name: ");
                scanf("%s", document);
                showWaitingTime(document);
                break;
                
            case 3:
                showMaxWaitTeacher();
                break;
                
            case 1:
                printf("Teacher name: ");
                scanf("%s", teacher);
                printf("Document name: ");
                scanf("%s", document);
                printf("Number of pages: ");
                scanf("%d", &pages);
                addJob(teacher, document, pages);
                break;
                
            case 5:
                nextJob();
                break;
                
            case 6:
                showAllJobs();
                break;
                
            case 7:
               
                break;
                
            default:
                printf("Invalid choice!\n");
        }
        
    } while(choice != 7);
    
    return 0;
}