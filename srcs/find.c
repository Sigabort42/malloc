#include "../malloc.h"
# define F(chunk_size, size)	(((int)(chunk->size - size - sizeof(t_chunk)) > 0) ? 0 : 1)

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
  show_alloc_mem();
  t_chunk	*chunk;
  int		i;
  int		f;

  i = 0;
  while (page)
    {
      chunk = page->chunk;
      dprintf(1, "Boucle %d %zu %p %d\n", i, size, page, chunk->free);
      while (((f = F(chunk->size, size)) || chunk->size < size || !chunk->free) && chunk->next)
	{
	  dprintf(1, "One block checked %p|%zu|%d\n", chunk, chunk->size, chunk->free);
	  chunk = chunk->next;
	}
      dprintf(1, "ENd block checked %p|%zu|%d\n", chunk, chunk->size, chunk->free);
      if (chunk->size == size && chunk->free)
	{
	  dprintf(1, "Equal chunk->size\n");
	  chunk->free = 0;
	  return ((void*)(++chunk));
	}
      dprintf(1, "2ENd block checked %zu|%d|%d\n", chunk->size, chunk->free, (int)(chunk->size - size - sizeof(t_chunk)));
      if (chunk->size > size && !f && chunk->free)
	{
	  dprintf(1, "split alocate %p|%zu\n", chunk, size);
	  split(chunk, size);
	  dprintf(1, "split alocated %p|%zu|%zu\n", chunk, chunk->size, size);
	  return ((void*)(++chunk));
	}
      dprintf(1, "3ENd block checked %zu|%d\n", chunk->size, chunk->free);
      if ((f || chunk->size <= size || !chunk->free) && !page->next)
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
