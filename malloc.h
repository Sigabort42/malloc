#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define CALL_TINY (mmap(0, getpagesize() * 1 + sizeof(t_chunk), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
# define CALL_SMALL (mmap(0, getpagesize() * 4 + sizeof(t_chunk), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
# define CALL_LARGE(n) (mmap(0, n + sizeof(t_chunk), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))

# define F(chunk_size, size) (((int)(chunk->size - size - sizeof(t_chunk)) > 0) ? 0 : 1)


# define TINY ((size_t)getpagesize() * 1)
# define SMALL ((size_t)getpagesize() * 4)

# include <stdio.h>
# include <sys/mman.h>
# include <unistd.h>
# include "libft/libft.h"

enum
{
 E_TINY,
 E_SMALL,
 E_LARGE,
 E_FREE,
};

typedef struct		s_chunk
{
  size_t		size;
  int			free;
  struct s_chunk	*next;
}			t_chunk;

typedef struct		s_page
{
  t_chunk		*chunk;
  struct s_page		*next;
}			t_page;


struct s_page *pages[3];


void		show_alloc_mem();
void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		*find(t_page *page, size_t size);

# endif
