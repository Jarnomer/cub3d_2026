/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_err	darray_swap(t_darray *arr, size_t i, size_t j)
{
	void	*temp;
	void	*pi;
	void	*pj;

	if (i >= arr->size || j >= arr->size)
		return (ERR_INVALID);
	if (i == j)
		return (ERR_NONE);
	temp = safe_calloc(arr->elem_size);
	pi = (char *)arr->data + i * arr->elem_size;
	pj = (char *)arr->data + j * arr->elem_size;
	ft_memcpy(temp, pi, arr->elem_size);
	ft_memcpy(pi, pj, arr->elem_size);
	ft_memcpy(pj, temp, arr->elem_size);
	free(temp);
	return (ERR_NONE);
}

t_err	darray_swap_remove(t_darray *arr, size_t index, void *out)
{
	void	*target;
	void	*last;

	if (index >= arr->size)
		return (ERR_INVALID);
	target = (char *)arr->data + index * arr->elem_size;
	if (out)
		ft_memcpy(out, target, arr->elem_size);
	arr->size--;
	if (index < arr->size)
	{
		last = (char *)arr->data + arr->size * arr->elem_size;
		ft_memcpy(target, last, arr->elem_size);
	}
	return (ERR_NONE);
}

t_err	darray_insert(t_darray *arr, size_t index, const void *elem)
{
	void	*target;
	size_t	shift_bytes;

	if (index > arr->size)
		return (ERR_INVALID);
	if (arr->size >= arr->capacity)
		darray_reserve(arr, arr->capacity * 2 + 1);
	target = (char *)arr->data + index * arr->elem_size;
	shift_bytes = (arr->size - index) * arr->elem_size;
	if (shift_bytes > 0)
		ft_memmove((char *)target + arr->elem_size, target, shift_bytes);
	ft_memcpy(target, elem, arr->elem_size);
	arr->size++;
	return (ERR_NONE);
}

t_err	darray_remove(t_darray *arr, size_t index, void *out)
{
	void	*target;
	size_t	shift_bytes;

	if (index >= arr->size)
		return (ERR_INVALID);
	target = (char *)arr->data + index * arr->elem_size;
	if (out)
		ft_memcpy(out, target, arr->elem_size);
	arr->size--;
	shift_bytes = (arr->size - index) * arr->elem_size;
	if (shift_bytes > 0)
		ft_memmove(target, (char *)target + arr->elem_size, shift_bytes);
	return (ERR_NONE);
}
