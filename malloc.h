#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# define CALL_TINY (mmap(0, getpagesize() * 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
# define CALL_SMALL (mmap(0, getpagesize() * 4, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
# define CALL_LARGE(n) (mmap(0, n + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
# define TINY ((size_t)getpagesize() * 1)
# define SMALL ((size_t)getpagesize() * 4)
# include <stdio.h>
# include <sys/mman.h>
# include <unistd.h>
# include "libft/libft.h"


typedef struct	s_mem
{
  struct s_list	*next;
  struct s_list	*prev;
  void		*addr;
  size_t	size;
  int		free;
}		t_mem;

enum
{
 ENUM_TINY,
 ENUM_SMALL,
 ENUM_FREE,
};

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);

# endif
