/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pool.h>

t_err	pool_init(t_pool *pool, t_u32 capacity, size_t elem_size)
{
	t_u32	i;

	pool->data = safe_calloc(capacity * elem_size);
	pool->free_stack = safe_calloc(capacity * sizeof(t_u32));
	pool->capacity = capacity;
	pool->elem_size = elem_size;
	pool->free_count = capacity;
	pool->active_count = 0;
	i = 0;
	while (i < capacity)
	{
		pool->free_stack[i] = capacity - 1 - i;
		i++;
	}
	return (ERR_NONE);
}

void	pool_destroy(t_pool *pool)
{
	if (pool->data)
		free(pool->data);
	if (pool->free_stack)
		free(pool->free_stack);
	pool->data = NULL;
	pool->free_stack = NULL;
	pool->capacity = 0;
	pool->free_count = 0;
	pool->active_count = 0;
}

t_i32	pool_alloc(t_pool *pool)
{
	t_u32	index;

	if (pool->free_count == 0)
		return (-1);
	pool->free_count--;
	index = pool->free_stack[pool->free_count];
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
		i++;
	}
}

void	pool_free(t_pool *pool, t_u32 index)
{
	if (!pool->active_flags[index])
		return ;
	if (index >= pool->capacity)
		return ;
	if (pool->free_count >= pool->capacity)
		return ;
	pool->active_flags[index] = 0;
	pool->free_stack[pool->free_count] = index;
	pool->free_count++;
	pool->active_count--;
}
