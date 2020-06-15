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
  void *str = malloc(nb);
  void *str2 = malloc(nb);
  //  strcpy(str2, "Salut toi comment tu va?");
  /*while (i < nb)
    {
      str[i++] = 'a';
    }
  str[i - 1] = 'u';
  str[i - 2] = 'i';
  str[i] = '\0';
  */
  //  i -= nb;
  //  printf("str ==%ld %ld %c\n", &str[i], &str[i] + 4096, str[i + 4097]);
  printf("str2 ==%ld %ld\n", &str, &str2);
  printf("str3 ==%s %d\n", str, strlen(str));
  while (1);
  return (0);
}

