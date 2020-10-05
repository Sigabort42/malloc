#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "malloc.h"


int main(int ac, char **av){

  if (ac < 2)
    {
      printf("usage: a.out number lines\n");
      return (-1);
    }
  int i = 0;
  int nb = atoi(av[1]);
  char *str = malloc(nb + 1);
  printf("address str %p\n", str);
  char *str2 = malloc(nb + 1);
  printf("address str2 %p\n", str2);
  strcpy(str2, "Salut toi comment tu va?");
  while (i < nb)
    {
      str[i++] = 'a';
    }
  str[i - 1] = 'u';
  str[i - 2] = 'i';
  str[i] = '\0';
  printf("str1 ==%p %p\n", str, str2);
  str = realloc(str, 200);
  printf("str2 ==%p %p\n", str, str2);
  printf("str3 ==%s %p\n", str2, str2);
  //  show_alloc_mem();
  free(str);
  free(str2);
  //  while (1);
  return (0);
}
