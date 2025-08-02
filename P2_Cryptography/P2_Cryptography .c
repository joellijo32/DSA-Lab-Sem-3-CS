#include <stdio.h>
int main(){
	int m[100] = {0}, k[100] = {0}, c[100] = {0}; 
	int deg_m, deg_k; 

	printf("Degree of m(x): "); 
	scanf("%d", &deg_m); 
	for(int i = 0; i <= deg_m; i++)
		scanf("%d", &m[i]), m[i] %= 3;
 
	printf("Degree of k(x): "); 
	scanf("%d", &deg_k); 
	for(int i = 0; i <= deg_k; i++)
		scanf("%d", &k[i]), k[i] %= 3;


	int deg_c = deg_m > deg_k ? deg_m: deg_k; 
	for(int i = 0; i <= deg_c; i++){
		c[i] = (m[i] + k[i]) % 3; 
	}

	printf("c(x) = "); 
	for(int i = deg_c; i >= 0; i--){
		if(c[i]){
			if(i != deg_c) printf(" + ") ;
			if(i == 0) printf("%d", c[i]); 
			else
			      if (c[i] == 1) 
				printf("x^%d", i);
			     else printf("%dx^%d", c[i], i); 
		}
	}
	printf("\n"); 
	return 0; 
}

