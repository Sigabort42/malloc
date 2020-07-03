# include "malloc.h"

int	initialize()
{
  dprintf(1, "Initialize ->|%p|\n", (void*)(*pages));
  if ((pages[E_TINY] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((pages[E_SMALL] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  pages[E_TINY]->chunk = CALL_TINY;
  pages[E_TINY]->chunk->size = TINY;
  pages[E_TINY]->chunk->free = 1;
  pages[E_TINY]->chunk->next = NULL;
  pages[E_SMALL]->chunk = CALL_SMALL;
  pages[E_SMALL]->chunk->size = SMALL;
  pages[E_SMALL]->chunk->free = 1;
  pages[E_SMALL]->chunk->next = NULL;
  return (0);
}


void	*malloc(size_t size)
{
  if (!(*pages))
    if (initialize())
      return (0);
  if (size <= TINY)
    {
      dprintf(1, "Find tiny\n");
      return (find(pages[E_TINY], size));
    }
  else if (size <= SMALL)
    {
      dprintf(1, "Find Small\n");
      return (find(pages[E_SMALL], size));
    }
  return CALL_LARGE(size);
}
