/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pool.h>

void	darray_init(t_darray *arr, size_t elem_size, size_t init_cap)
{
	arr->elem_size = elem_size;
	arr->capacity = init_cap;
	arr->data = NULL;
	arr->size = 0;
	if (init_cap > 0)
		arr->data = safe_calloc(init_cap * elem_size);
}

void	darray_destroy(t_darray *arr)
{
	free(arr->data);
	ft_bzero(arr, sizeof(t_darray));
}

void	darray_clear(t_darray *arr)
{
	arr->size = 0;
}

void	*darray_get(t_darray *arr, size_t index)
{
	if (index >= arr->size)
		return (NULL);
	return ((char *)arr->data + index * arr->elem_size);
}

t_err	darray_set(t_darray *arr, size_t index, const void *elem)
{
	void	*dest;

	if (index >= arr->size)
		return (ERR_INVALID);
	dest = (char *)arr->data + index * arr->elem_size;
	ft_memcpy(dest, elem, arr->elem_size);
	return (ERR_NONE);
}
