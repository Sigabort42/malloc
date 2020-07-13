# include "../malloc.h"

int	initialize()
{
  if ((pages[E_TINY] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE,
			    MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((pages[E_SMALL] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE,
			     MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((pages[E_LARGE] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE,
			     MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((pages[E_TINY]->chunk = CALL_TINY) == MAP_FAILED)
    return (1);
  pages[E_TINY]->chunk->size = TINY;
  pages[E_TINY]->chunk->free = 1;
  pages[E_TINY]->chunk->next = NULL;
  if ((pages[E_SMALL]->chunk = CALL_SMALL) == MAP_FAILED)
    return (1);
  pages[E_SMALL]->chunk->size = SMALL;
  pages[E_SMALL]->chunk->free = 1;
  pages[E_SMALL]->chunk->next = NULL;
  return (0);
}

void	*malloc2(t_chunk *curr, size_t size)
{
  while (curr)
    curr = curr->next;
  if ((curr = CALL_LARGE(size)) == MAP_FAILED)
    return (0);
  else
    {
      curr->size = size;
      curr->free = 0;
      curr->next = NULL;
      if (pages[E_LARGE]->chunk == NULL)
	pages[E_LARGE]->chunk = curr;
      return (++curr);
    }
}

void	*malloc(size_t size)
{
  t_chunk	*curr;
  void		*data;

  if (pthread_mutex_lock(&g_mutex.m_malloc) == EINVAL)
    {
      pthread_mutex_init(&g_mutex.m_malloc, NULL);
      pthread_mutex_lock(&g_mutex.m_malloc);
    }
  if (!size)
    data = NULL;
  else if (!(*pages))
    if (initialize())
      return (0);
  if (size <= TINY)
    data = find(pages[E_TINY], size);
  else if (size <= SMALL)
    data = find(pages[E_SMALL], size);
  else
    {
      curr = pages[E_LARGE]->chunk;
      data = malloc2(curr, size);
    }
  pthread_mutex_unlock(&g_mutex.m_malloc);
  return (data);
}
