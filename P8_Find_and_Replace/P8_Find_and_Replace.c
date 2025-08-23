#include <stdio.h>
#include <string.h>


void main()
{
  
  char text[1024];
  char *token;
  printf("Enter text:");
  scanf("%[^\n]", text);

  char words[20][20];
  int i = 0;

  token =   strtok(text, " ");

  while (token != NULL)
  {
    
    strcpy(words[i++], token);
    token = strtok(NULL, " ");

  }

  printf("--- Entered Text ---\n");
  for (int j = 0; j < i;j++)
  {
    printf("%s ", words[j]);
  }
  printf("\n");

  char find[50], replace[50];
  printf("Enter find word:");
  scanf("%s", find);
  printf("Enter search word:");
  scanf("%s", replace);

  int occ = 0;

  for (int j = 0; j < i; j++)
  {
    if (strcmp(words[j], find) == 0) {
      strcpy(words[j], replace);
      occ++;
    }
  }

  printf("%d replacements made\n", occ);
  printf("---- Replaced Text ----\n");
  for (int j = 0; j < i;j++)
  {
    printf("%s ", words[j]);
  }
  printf("\n");
}
