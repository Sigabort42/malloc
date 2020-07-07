#include "../malloc.h"

void		merge(t_chunk *chunk)
{
  t_chunk	*curr;

  curr = chunk;
  while (curr && curr->next)
    {
      dprintf(1, "currr %p %d %d\n", curr, curr->free, curr->next->free);
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
		  merge(curr);
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



/*void		free(void *ptr)
{
  t_page	*last;
  t_chunk	*curr;

  last = pages[E_SMALL];
  while (last && last->next)
    last = last->next;
  if (last && (void*)pages[E_SMALL]->chunk <= ptr && ptr <= (void*)last->chunk)
    {
      dprintf(1, "FREE SMALL %p|%p\n", (void*)pages[E_SMALL]->chunk, (void*)last->chunk);
      curr = ptr;
      --curr;
      curr->free = 1;
      merge(pages[E_SMALL]->chunk);
      return ;
    }
  last = pages[E_TINY];
  while (last && last->next)
    last = last->next;
  if (last && (void*)pages[E_TINY]->chunk <= ptr && ptr <= (void*)last->chunk)
    {
      dprintf(1, "FREE TINY %p|%p\n", (void*)pages[E_TINY]->chunk, (void*)last->chunk);
      curr = ptr;
      --curr;
      curr->free = 1;
      merge(pages[E_TINY]->chunk);
      return ;
    }
  last = pages[E_LARGE];
  while (last && last->next)
    last = last->next;
  if (last && (void*)pages[E_LARGE]->chunk <= ptr && ptr <= (void*)last->chunk)
    {
      dprintf(1, "FREE LARGE\n");
      curr = ptr;
      curr->free = 1;
      merge(pages[E_SMALL]->chunk);
      return ;
      }
}
*/
