/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pool.h>

void	*pool_get(t_pool *pool, t_u32 index)
{
	if (index >= pool->capacity)
		return (NULL);
	return ((char *)pool->data + index * pool->elem_size);
}

bool	pool_is_empty(t_pool *pool)
{
	return (pool->active_count == 0);
}

bool	pool_is_full(t_pool *pool)
{
	return (pool->free_count == 0);
}

t_u32	pool_active_count(t_pool *pool)
{
	return (pool->active_count);
}
