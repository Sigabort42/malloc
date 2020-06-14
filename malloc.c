#include <stdio.h>
# include <sys/mman.h>
# include <unistd.h>
# include "malloc.h"

void	*malloc(size_t size)
{
  return (mmap(0, size + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0));
}

