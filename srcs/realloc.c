#include "../malloc.h"

t_chunk		*search(void *ptr)
{
  t_page	*page;
  t_chunk	*curr;
  int		i;

  i = 0;
  while (i < 2)
    {
      page = pages[i];
      while (page)
	{
	  curr = page->chunk;
	  while (curr)
	    {
	      if (++curr == ptr)
		  return (--curr);
	      --curr;
	      curr = curr->next;
	    }
	  page = page->next;
	}
      i++;
    }
  return (0);
}


void            *realloc(void *ptr, size_t size)
{
  dprintf(1, "ENTER REALLC %p\n", ptr);
  t_chunk	*tmp;
  void		*data;

  if (!ptr)
    return (malloc(size));
  else if (!size && ptr)
      free(ptr);
  else
    {
      if (!(tmp = search(ptr)))
	return (0);
      dprintf(1, "REALLOC search %p|%p\n", ptr, tmp);
      dprintf(1, "REALLOC search2 %p|%p\n", ptr, tmp);
      data = malloc(tmp->size + size + sizeof(t_chunk));
      data = ft_memcpy(data, (void*)tmp, tmp->size + sizeof(t_chunk));
      free(ptr);
      return (++data);
    }  
  return (0);
}
