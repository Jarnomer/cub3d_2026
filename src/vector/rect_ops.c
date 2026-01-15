/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_rect	rect_clip(t_rect rect, t_rect bounds)
{
	t_rect	clipped;
	t_i32	right;
	t_i32	bottom;

	clipped.x = maxi(rect.x, bounds.x);
	clipped.y = maxi(rect.y, bounds.y);
	right = mini(rect.x + rect.w, bounds.x + bounds.w);
	bottom = mini(rect.y + rect.h, bounds.y + bounds.h);
	clipped.w = maxi(0, right - clipped.x);
	clipped.h = maxi(0, bottom - clipped.y);
	return (clipped);
}
