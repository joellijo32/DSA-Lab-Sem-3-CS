#include <stdio.h>
int main(){
	FILE *fp = fopen("integers.txt","r"); 
	if(fp == NULL){
		printf("File not found.\n");
		return 1; 
	}
	int arr[1000] , n = 0; 
	while(fscanf(fp, "%d", &arr[n]) == 1 && n < 1000){
		n++; 
	}
	fclose(fp); 
	int mode = arr[0], maxCount = 0; 
	for(int i = 0; i < n ;i++){
		int count = 0; 
		for(int j = 0; j < n ; j++){
			if(arr[j] == arr[i]){
				count++; 
			}
		}
		if(count > maxCount){
			maxCount = count; 
			mode = arr[i]; 
		}
	}
	printf("Mode = %d\n", mode); 
	return 0; 
}
