/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pool.h>

static void	darray_grow(t_darray *arr)
{
	size_t	new_cap;
	void	*new_data;

	if (arr->capacity == 0)
		new_cap = DARRAY_INITIAL_CAP;
	else
		new_cap = arr->capacity * DARRAY_GROWTH_FACTOR;
	new_data = safe_calloc(new_cap * arr->elem_size);
	if (arr->data)
	{
		ft_memcpy(new_data, arr->data, arr->size * arr->elem_size);
		free(arr->data);
	}
	arr->capacity = new_cap;
	arr->data = new_data;
}

void	darray_push(t_darray *arr, const void *elem)
{
	void	*dest;

	if (arr->size >= arr->capacity)
		darray_grow(arr);
	dest = (char *)arr->data + arr->size * arr->elem_size;
	ft_memcpy(dest, elem, arr->elem_size);
	arr->size++;
}

t_err	darray_pop(t_darray *arr, void *out)
{
	void	*src;

	if (arr->size == 0)
		return (ERR_INVALID);
	arr->size--;
	if (out)
	{
		src = (char *)arr->data + arr->size * arr->elem_size;
		ft_memcpy(out, src, arr->elem_size);
	}
	return (ERR_NONE);
}

void	darray_shrink(t_darray *arr)
{
	void	*new_data;

	if (arr->size == arr->capacity || arr->size == 0)
		return ;
	new_data = safe_calloc(arr->size * arr->elem_size);
	ft_memcpy(new_data, arr->data, arr->size * arr->elem_size);
	arr->capacity = arr->size;
	arr->data = new_data;
	free(arr->data);
}

void	darray_reserve(t_darray *arr, size_t capacity)
{
	void	*new_data;

	if (capacity <= arr->capacity)
		return ;
	new_data = safe_calloc(capacity * arr->elem_size);
	if (arr->data)
	{
		ft_memcpy(new_data, arr->data, arr->size * arr->elem_size);
		free(arr->data);
	}
	arr->capacity = capacity;
	arr->data = new_data;
}
