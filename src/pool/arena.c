/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pool.h>

#define ARENA_ALIGNMENT 8

t_err	arena_init(t_arena *arena, size_t size)
{
	arena->data = safe_calloc(size);
	arena->size = size;
	arena->offset = 0;
	arena->peak_usage = 0;
	return (ERR_NONE);
}

void	arena_destroy(t_arena *arena)
{
	if (arena->data)
		free(arena->data);
	arena->data = NULL;
	arena->size = 0;
	arena->offset = 0;
	arena->peak_usage = 0;
}

static size_t	align_up(size_t value, size_t alignment)
{
	return ((value + alignment - 1) & ~(alignment - 1));
}

void	*arena_alloc(t_arena *arena, size_t size)
{
	size_t	aligned_size;
	void	*ptr;

	aligned_size = align_up(size, ARENA_ALIGNMENT);
	if (arena->offset + aligned_size > arena->size)
		return (NULL);
	ptr = arena->data + arena->offset;
	arena->offset += aligned_size;
	if (arena->offset > arena->peak_usage)
		arena->peak_usage = arena->offset;
	return (ptr);
}

void	*arena_calloc(t_arena *arena, size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = count * size;
	ptr = arena_alloc(arena, total);
	if (ptr)
		ft_memset(ptr, 0, total);
	return (ptr);
}
