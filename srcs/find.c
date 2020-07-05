#include "../malloc.h"

int	allocate_new_page(t_page *page, size_t size)
{
  t_page	*e;

  if ((e = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  else if (size <= TINY)
    {
      e->chunk = CALL_TINY;
      e->chunk->size = TINY;
    }
  else
    {
      e->chunk = CALL_SMALL;
      e->chunk->size = SMALL;
    }
  e->chunk->free = 1;
  e->chunk->next = NULL;
  page->next = e;
  return (0);
}

void	split(t_chunk *chunk, size_t size)
{
  t_chunk	*new;

  new = (void*)((void*)chunk + size + sizeof(t_chunk));
  new->size = chunk->size - size - sizeof(t_chunk);
  new->free = 1;
  new->next = chunk->next;
  chunk->size = size;
  chunk->free = 0;
  chunk->next = new;
}

void	*find(t_page *page, size_t size)
{
  dprintf(1, "enter find %zu\n", size);
  t_chunk	*chunk;
  int		i;

  i = 0;
  while (page)
    {
      chunk = page->chunk;
      dprintf(1, "Boucle %d %zu %p\n", i, size, page);
      while ((chunk->size < size || !chunk->free) && chunk->next)
	{
	  dprintf(1, "One block checked %p|%zu\n", chunk, chunk->size);
	  chunk = chunk->next;
	}
      dprintf(1, "ENd block checked %zu|%d\n", chunk->size, chunk->free);
      if (chunk->size == size && chunk->free)
	{
	  dprintf(1, "Equal chunk->size\n");
	  chunk->free = 0;
	  return ((void*)(++chunk));
	}
      dprintf(1, "2ENd block checked %zu|%d\n", chunk->size, chunk->free);
      if (chunk->size > size + sizeof(t_chunk) && chunk->free)
	{
	  dprintf(1, "split alocate %p\n", chunk);
	  split(chunk, size);
	  dprintf(1, "split alocated %p|\n", chunk);
	  return ((void*)(++chunk));
	}
      dprintf(1, "3ENd block checked %zu|%d\n", chunk->size, chunk->free);
      if ((chunk->size <= size || !chunk->free) && !page->next)
	{
	  dprintf(1, "Allocate new page %p|%p\n", page, page->next);
	  if (allocate_new_page(page, size))
	    return (0);
	  dprintf(1, "Allocate new page %p|%p\n", page, page->next);
	}
      dprintf(1, "4ENd block checked %zu|%d\n", chunk->size, chunk->free);
      page = page->next;
      i++;
      dprintf(1, "5ENd block checked %zu|%d\n", chunk->size, chunk->free);
    }
  dprintf(1, "6ENd block checked %zu|%d\n", chunk->size, chunk->free);
  return (0);
}
