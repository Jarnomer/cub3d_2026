/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <calc.h>

t_rect	rect_new(t_i32 x, t_i32 y, t_i32 w, t_i32 h)
{
	return ((t_rect){x, y, w, h});
}

bool	rect_contains(t_rect r, t_vec2i point)
{
	if (point.x < r.x || point.x >= r.x + r.w)
		return (false);
	if (point.y < r.y || point.y >= r.y + r.h)
		return (false);
	return (true);
}

bool	rect_overlaps(t_rect a, t_rect b)
{
	if (a.x >= b.x + b.w || b.x >= a.x + a.w)
		return (false);
	if (a.y >= b.y + b.h || b.y >= a.y + a.h)
		return (false);
	return (true);
}

t_rect	rect_intersect(t_rect a, t_rect b)
{
	t_rect	result;
	t_i32	ax2;
	t_i32	ay2;
	t_i32	bx2;
	t_i32	by2;

	ax2 = a.x + a.w;
	ay2 = a.y + a.h;
	bx2 = b.x + b.w;
	by2 = b.y + b.h;
	result.x = maxi(a.x, b.x);
	result.y = maxi(a.y, b.y);
	result.w = mini(ax2, bx2) - result.x;
	result.h = mini(ay2, by2) - result.y;
	if (result.w < 0)
		result.w = 0;
	if (result.h < 0)
		result.h = 0;
	return (result);
}
