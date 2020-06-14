#include <stdio.h>
# include <sys/mman.h>
# include <unistd.h>

int main(int ac, char **av){

  if (ac < 2)
    {
      printf("usage: a.out number lines\n");
      return (-1);
    }
  int i = 0;
  int nb = atoi(av[1]);
  char *str = (char*)malloc(nb);
  while (i < nb)
      str[i++] = 'a';
  str[i] = '\0';
  printf("str=={%d} get=={%d} word=={%s}\n", nb, getpagesize(), str);
  return (0);
}

