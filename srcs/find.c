#include "../malloc.h"

int	allocate_new_page(t_page *page, size_t size)
{
  t_page	*e;

  if ((e = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)) == MAP_FAILED)
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
  new->next = NULL;
  new->next = chunk->next;
  chunk->size = size;
  chunk->free = 0;
  chunk->next = new;
}

void	*find(t_page *page, size_t size)
{
  t_chunk	*chunk;
  int		f;

  while (page)
    {
      chunk = page->chunk;
      while (((f = F(chunk->size, size)) || chunk->size < size ||
	      !chunk->free) && chunk->next)
	  chunk = chunk->next;
      if (chunk->size == size && chunk->free)
	{
	  chunk->free = 0;
	  return ((void*)(++chunk));
	}
      if (chunk->size > size && !f && chunk->free)
	{
	  split(chunk, size);
	  return ((void*)(++chunk));
	}
      if ((f || chunk->size <= size || !chunk->free) && !page->next)
	  if (allocate_new_page(page, size))
	    return (0);
      page = page->next;
    }
  return (0);
}
