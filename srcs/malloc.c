# include "../malloc.h"

int	initialize()
{
  if ((pages[E_TINY] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((pages[E_SMALL] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((pages[E_LARGE] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((pages[E_TINY]->chunk = CALL_TINY) == MAP_FAILED)
    return (1);
  pages[E_TINY]->chunk->size = TINY;
  pages[E_TINY]->chunk->free = 1;
  pages[E_TINY]->chunk->next = NULL;
  if ((pages[E_SMALL]->chunk = CALL_SMALL) == MAP_FAILED)
    return (1);
  pages[E_SMALL]->chunk->size = SMALL;
  pages[E_SMALL]->chunk->free = 1;
  pages[E_SMALL]->chunk->next = NULL;
  return (0);
}


void	*malloc(size_t size)
{
  t_chunk	*curr;
  
  if (!size)
    return (NULL);
  if (!(*pages))
    if (initialize())
      return (0);
  if (size <= TINY)
      return (find(pages[E_TINY], size));
  else if (size <= SMALL)
      return (find(pages[E_SMALL], size));
  else
    {
      curr = pages[E_LARGE]->chunk;
      while (curr)
	curr = curr->next;
      if ((curr = CALL_LARGE(size)) == MAP_FAILED)
	return (0);
      curr->size = size;
      curr->free = 0;
      curr->next = NULL;
      if (pages[E_LARGE]->chunk == NULL)
	pages[E_LARGE]->chunk = curr;
      return (++curr);
    }
  return (0);
}
