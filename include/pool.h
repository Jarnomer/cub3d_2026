/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POOL_H
# define POOL_H

# include <config.h>
# include <error.h>
# include <types.h>

# define DARRAY_INITIAL_CAP		8
# define DARRAY_GROWTH_FACTOR	2
# define ARENA_ALIGNMENT		8
# define FRAME_ARENA_SIZE		65536
# define DEFAULT_POOL_SIZE		256

typedef struct s_pool
{
	void		*data;
	t_u32		*free_stack;
	t_u8		*active_flags;
	t_u32		capacity;
	t_u32		free_count;
	t_u32		active_count;
	size_t		elem_size;
}	t_pool;

typedef struct s_arena
{
	t_u8		*data;
	size_t		size;
	size_t		offset;
	size_t		peak_usage;
}	t_arena;

typedef struct s_darray
{
	void		*data;
	size_t		size;
	size_t		capacity;
	size_t		elem_size;
}	t_darray;

void	pool_init(t_pool *pool, t_u32 capacity, size_t elem_size);
void	pool_destroy(t_pool *pool);
t_i32	pool_alloc(t_pool *pool);
void	pool_reset(t_pool *pool);
void	pool_free(t_pool *pool, t_u32 index);

void	*pool_get(t_pool *pool, t_u32 index);
bool	pool_is_empty(t_pool *pool);
bool	pool_is_full(t_pool *pool);
t_u32	pool_active_count(t_pool *pool);

void	arena_init(t_arena *arena, size_t size);
void	arena_destroy(t_arena *arena);
void	*arena_alloc(t_arena *arena, size_t size);
void	*arena_calloc(t_arena *arena, size_t count, size_t size);

void	arena_reset(t_arena *arena);
size_t	arena_usage(t_arena *arena);
size_t	arena_peak(t_arena *arena);

void	darray_init(t_darray *arr, size_t elem_size, size_t init_cap);
void	darray_destroy(t_darray *arr);
void	darray_clear(t_darray *arr);
void	*darray_get(t_darray *arr, size_t index);
t_err	darray_set(t_darray *arr, size_t index, const void *elem);

void	darray_push(t_darray *arr, const void *elem);
t_err	darray_pop(t_darray *arr, void *out);
void	darray_shrink(t_darray *arr);
void	darray_reserve(t_darray *arr, size_t capacity);

t_err	darray_swap(t_darray *arr, size_t i, size_t j);
t_err	darray_swap_remove(t_darray *arr, size_t index, void *out);
t_err	darray_insert(t_darray *arr, size_t index, const void *elem);
t_err	darray_remove(t_darray *arr, size_t index, void *out);

#endif
