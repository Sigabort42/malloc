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
  t_page	*page;
  t_chunk	*curr;
  int		i;

  if (pthread_mutex_lock(&g_mutex.m_free) == EINVAL)
    {
      pthread_mutex_init(&g_mutex.m_free, NULL);
      pthread_mutex_lock(&g_mutex.m_free);
    }
  i = 0;
  page = g_pages[i];
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
		  //		  if (i == 2)
		  munmap((void*)curr, curr->size);
		  pthread_mutex_unlock(&g_mutex.m_free);
		  return ;
		}
	      --curr;
	      curr = curr->next;
	    }
	  page = page->next;
	}
      i++;
    }
  pthread_mutex_unlock(&g_mutex.m_free);
}
