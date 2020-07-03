#include <stdio.h>
# include <sys/mman.h>
# include <unistd.h>
# include "malloc.h"
# include <string.h>

int main(int ac, char **av){

  if (ac < 2)
    {
      printf("usage: a.out number lines\n");
      return (-1);
    }
  int i = 0;
  int nb = atoi(av[1]);
  char *str = malloc(nb);
  char *str2 = malloc(nb);
  strcpy(str2, "Salut toi comment tu va?");
  while (i < nb)
    {
      str[i++] = 'a';
      }
  str[i - 1] = 'u';
  str[i - 2] = 'i';
  str[i] = '\0';
  printf("str2 ==%p %p\n", &str, &str2);
  printf("str3 ==%s\n", str);
  while (1);
  return (0);
}

