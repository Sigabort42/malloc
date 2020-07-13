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
  t_chunk	*tmp;
  t_chunk	*data;

  if (!ptr)
    return (malloc(size));
  else if (!size && ptr)
      free(ptr);
  else
    {
      if (!(tmp = search(ptr)))
	  return (ptr);
      data = (t_chunk*)malloc((size_t)(tmp->size + size + sizeof(t_chunk)));
      ft_memmove((void*)data, (void*)tmp, (size_t)(tmp->size + sizeof(t_chunk)));
      data->size += size + sizeof(t_chunk);
      free(ptr);
      return (++data);
    }  
  return (0);
}
