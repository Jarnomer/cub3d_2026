/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	pool_init(t_pool *pool, t_u32 capacity, size_t elem_size)
{
	t_u32	i;

	*pool = (t_pool){.capacity = capacity, .elem_size = elem_size};
	pool->data = safe_calloc(capacity * elem_size);
	pool->free_stack = safe_calloc(capacity * sizeof(t_u32));
	pool->active_flags = safe_calloc(capacity * sizeof(t_u8));
	pool->free_count = pool->capacity;
	i = 0;
	while (i < capacity)
	{
		pool->free_stack[i] = capacity - 1 - i;
		i++;
	}
}

void	pool_destroy(t_pool *pool)
{
	free(pool->data);
	free(pool->free_stack);
	free(pool->active_flags);
	*pool = (t_pool){0};
}

t_i32	pool_alloc(t_pool *pool)
{
	t_u32	index;

	if (pool->free_count == 0)
		return (-1);
	pool->free_count--;
	index = pool->free_stack[pool->free_count];
	pool->active_flags[index] = 1;
	pool->active_count++;
	return ((t_i32)index);
}

void	pool_reset(t_pool *pool)
{
	t_u32	i;

	pool->free_count = pool->capacity;
	pool->active_count = 0;
	i = 0;
	while (i < pool->capacity)
	{
		pool->free_stack[i] = pool->capacity - 1 - i;
		pool->active_flags[i] = 0;
		i++;
	}
}

void	pool_free(t_pool *pool, t_u32 index)
{
	if (index >= pool->capacity)
		return ;
	if (!pool->active_flags[index])
		return ;
	if (pool->free_count >= pool->capacity)
		return ;
	pool->active_flags[index] = 0;
	pool->free_stack[pool->free_count] = index;
	pool->free_count++;
	pool->active_count--;
}
