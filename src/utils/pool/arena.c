/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	arena_init(t_arena *arena, size_t size)
{
	*arena = (t_arena){.size = size};
	arena->data = safe_calloc(size);
}

void	arena_destroy(t_arena *arena)
{
	free(arena->data);
	*arena = (t_arena){0};
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

	if (count > SIZE_MAX / size)
		return (NULL);
	total = count * size;
	ptr = arena_alloc(arena, total);
	if (ptr)
		ft_bzero(ptr, total);
	return (ptr);
}
