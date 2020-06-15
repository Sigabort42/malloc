# include "malloc.h"

t_mem	tab_mem[3];

void	initialize()
{
  tab_mem[ENUM_TINY].addr = CALL_TINY;
  tab_mem[ENUM_TINY].free = 1;
  tab_mem[ENUM_TINY].size = TINY;
  tab_mem[ENUM_TINY].next = 0;
  tab_mem[ENUM_TINY].prev = 0;
  tab_mem[ENUM_SMALL].addr = CALL_SMALL;
  tab_mem[ENUM_SMALL].free = 1;
  tab_mem[ENUM_SMALL].size = SMALL;
  tab_mem[ENUM_SMALL].next = 0;
  tab_mem[ENUM_SMALL].prev = 0;
  tab_mem[ENUM_FREE].addr = CALL_SMALL;
  tab_mem[ENUM_FREE].free = 1;
  tab_mem[ENUM_FREE].size = SMALL;
  tab_mem[ENUM_FREE].next = 0;
  tab_mem[ENUM_FREE].prev = 0;  
}

void	*malloc(size_t size)
{
  if (!tab_mem[ENUM_TINY].addr)
    initialize();
  dprintf(1, "zzzz0x{%ld|%zu}0x{%ld|%zu}\n", (long int)tab_mem[0].addr, tab_mem[0].size, (long int)tab_mem[1].addr, tab_mem[1].size);
  if (size <= TINY)
    {
      return tab_mem[0].addr;
    }
  else if (size <= SMALL)
    {
      return tab_mem[1].addr;
    }
  return CALL_LARGE(size);
}

