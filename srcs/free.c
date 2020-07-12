#include "../malloc.h"

void		merge(t_chunk *chunk)
{
  t_chunk	*curr;

  curr = chunk;
  while (curr && curr->next)
    {
      //      dprintf(1, "currr %p %d %d\n", curr, curr->free, curr->next->free);
      if (curr->free && curr->next->free)
	{
	  curr->size += curr->next->size + sizeof(t_chunk);
	  curr->next = curr->next->next;
	}
      curr = curr->next;
    }
}


void		free(void *ptr)
{
  t_page	*page;
  t_chunk	*curr;
  int		i;

  i = 0;
  page = pages[i];
  while (i < 3)
    {
      while (page)
	{
	  curr = page->chunk;
	  while (curr)
	    {
	      if (++curr == ptr)
		{
		  --curr;
		  curr->free = 1;
		  merge(page->chunk);
		  return ;
		}
	      --curr;
	      curr = curr->next;
	    }
	  page = page->next;
	}
      i++;
    }
}
