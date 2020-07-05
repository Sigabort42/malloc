#include "../malloc.h"

void		merge(t_chunk *chunk)
{
  t_chunk	*curr;

  curr = chunk;
  while (curr && curr->next)
    {
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
  //  dprintf(1, "ENTER FREE\n");
  t_page	*last;
  t_chunk	*curr;

  last = pages[E_TINY];
  while (last && last->next)
    last = last->next;
  if (last && (void*)pages[E_TINY]->chunk <= ptr && ptr <= (void*)last->chunk)
    {
      dprintf(1, "FREE TINY\n");
      curr = ptr;
      curr->free = 1;
      merge(pages[E_TINY]->chunk);
      return ;
    }
  last = pages[E_SMALL];
  while (last && last->next)
    last = last->next;
  if (last && (void*)pages[E_SMALL]->chunk <= ptr && ptr <= (void*)last->chunk)
    {
      dprintf(1, "FREE SMALL\n");
      curr = ptr;
      curr->free = 1;
      merge(pages[E_SMALL]->chunk);
      return ;
    }
}
