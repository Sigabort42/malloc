#include "../malloc.h"

void		show_alloc_mem()
{
  dprintf(1, "show alloc mem\n\n");
  t_page	*page;
  t_chunk	*curr;
  char		data[3][6];
  int		i;
  int		idx;

  i = 0;
  idx = 0;
  ft_strcpy(data[0], "TINY");
  ft_strcpy(data[1], "SMALL");
  ft_strcpy(data[2], "LARGE");
  dprintf(1, "OKOK\n");
  while (i < 3)
    {
      page = pages[i];
      dprintf(1, "%s : %p\n", data[i], page);
      while (page)
	{
	  curr = page->chunk;
	  if (curr)
	    dprintf(1, "Page %d : %p\n", idx, curr);
	  while (curr)
	    {
	      if (getenv("MALLOC_DEBUG"))
		dprintf(1, "%p - %p : %zu octets free : %d\n",
			curr + sizeof(t_chunk), curr +
			sizeof(t_chunk) + curr->size,
			curr->size, curr->free);
	      else
		dprintf(1, "%p - %p : %zu octets\n",
			curr + sizeof(t_chunk), curr +
			sizeof(t_chunk) + curr->size,
			curr->size);
	      curr = curr->next;
	    }
	  page = page->next;
	  idx++;
	}
      idx = 0;
      i++;
    }
  dprintf(1, "ENDDDD\n");
}
