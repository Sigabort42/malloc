#include "../malloc.h"

t_chunk		*search(void *ptr)
{
  t_page	*page;
  t_chunk	*curr;
  int		i;

  i = 0;
  while (i < 3)
    {
      page = pages[i];
      while (page)
	{
	  curr = page->chunk;
	  while (curr)
	    {
	      dprintf(1, "curr|%p|%zu|\n", curr + sizeof(t_chunk), curr->size);
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
  dprintf(1, "ENTER REALLC %p|%s|%zu\n", ptr - sizeof(t_chunk), (char*)ptr, size);
  t_chunk	*tmp;
  t_chunk	*data;

  if (!ptr)
    return (malloc(size));
  else if (!size && ptr)
      free(ptr);
  else
    {
      dprintf(1, "IF REALLOC\n");
      if (!(tmp = search(ptr)))
	  return (ptr);
      //      dprintf(1, "REALLOC search %p|%p|%s|%zu|%zu\n", ptr, tmp, (char*)ptr, tmp->size, size);
      dprintf(1, "IF REALLOC22\n");
      data = malloc((size_t)(tmp->size + size + sizeof(t_chunk)));
      dprintf(1, "IF REALLOC222\n");
      ft_memmove((void*)data, (void*)tmp, (size_t)(tmp->size + sizeof(t_chunk)));
      // dprintf(1, "REALLOC search2 %p|%p|%p|%zu|%d|%d\n", ptr, tmp, data, data->size, data->free, tmp->free);
      data->size += size + sizeof(t_chunk);
      free(ptr);
      //dprintf(1, "REALLOC search3 %p|%p|%s|%p|%zu|%d|%d\n", ptr, tmp, (char*)ptr, data, data->size, data->free, tmp->free);
      dprintf(1, "IF REALLOC3\n");
      return (++data);
    }  
  return (0);
}
