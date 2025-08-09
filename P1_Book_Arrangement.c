#include <stdio.h>

int isPossible(int pages[], int n, int s, int maxPages){
	int students = 1, sum = 0; 
	for(int i= 0; i < n ; i++){
		if(pages[i] > maxPages)
			return 0; 
		if(sum + pages[i] > maxPages){
			students++; 
			sum = pages[i]; 
			if(students > s)
				return 0; 
		}
		else {
			sum += pages[i]; 
		}
	}
	return 1; 
}

int main(){
	int n , s; 
	printf("Enter number of books: "); 
	scanf("%d", &n); 
	int pages[n]; 
	printf("Enter number of pages in each book (sorted): \n"); 	
	for(int i = 0; i < n;i++)
		scanf("%d", &pages[i]); 
	printf("Enter number of students: "); 
	scanf("%d", &s); 
	int low = 0, high = 0; 
	for(int i = 0; i < n; i++){
		high += pages[i];
	} 
	int ans = -1; 
	while(low <= high){
		int mid = (low+high)/2; 
		if(isPossible(pages, n, s, mid)){
			ans = mid; 
			high = mid - 1; 
		}else {
			low = mid + 1; 
		}
	}
	int sum = 0; int students = 1; 
	printf("Students %d: [", students); 
	for(int i= 0; i < n;i++){
		if(sum + pages[i] > ans){
			printf("] -->  %d pages\n", sum); 
			sum = pages[i]; 
			students++; 
			printf("Student %d: [%d", students, pages[i]); 
		}
		else{
			if(sum == 0)
				printf("%d", pages[i]); 
			else
				printf(", %d", pages[i]); 
			sum += pages[i]; 
		}
	}
	printf("] --> %d pages \n", sum); 
	return 0; 

}
