#include "../malloc.h"

int     ft_initialize()
{
  if ((g_pages[E_TINY] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((g_pages[E_SMALL] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((g_pages[E_LARGE] = mmap(0, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
    return (1);
  if ((g_pages[E_TINY]->chunk = CALL_TINY) == MAP_FAILED)
    return (1);
  g_pages[E_TINY]->chunk->size = TINY;
  g_pages[E_TINY]->chunk->free = 1;
  g_pages[E_TINY]->chunk->next = NULL;
  if ((g_pages[E_SMALL]->chunk = CALL_SMALL) == MAP_FAILED)
    return (1);
  g_pages[E_SMALL]->chunk->size = SMALL;
  g_pages[E_SMALL]->chunk->free = 1;
  g_pages[E_SMALL]->chunk->next = NULL;
  return (0);
}

void    *calloc(size_t nmemb, size_t sizem)
{
  t_chunk       *curr;
  size_t	size;
  void		*data;

  if (pthread_mutex_lock(&g_mutex.m_calloc) == EINVAL)
    {
      pthread_mutex_init(&g_mutex.m_calloc, NULL);
      pthread_mutex_lock(&g_mutex.m_calloc);
    }
  size = nmemb * sizem;
  if (!size)
    return (NULL);
  if (!(*g_pages))
    if (ft_initialize())
      return (0);
  if (size <= TINY)
    {
      curr = find(g_pages[E_TINY], size);
      data = curr;
      --curr;
      ft_bzero(data, curr->size);
      return (data);
    }
  else if (size <= SMALL)
    {
      curr = find(g_pages[E_SMALL], size);
      data = curr;
      --curr;
      ft_bzero(data, curr->size);
      return (data);
    }
  else
    {
      curr = g_pages[E_LARGE]->chunk;
      while (curr)
        curr = curr->next;
      if ((curr = CALL_LARGE(size)) == MAP_FAILED)
        return (0);
      curr->size = size;
      curr->free = 0;
      curr->next = NULL;
      if (g_pages[E_LARGE]->chunk == NULL)
        g_pages[E_LARGE]->chunk = curr;
      data = ++curr;
      --curr;
      ft_bzero(data, curr->size);
      return (data);
    }
  pthread_mutex_unlock(&g_mutex.m_calloc);
  return (0);
}
