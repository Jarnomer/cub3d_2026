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

void	rect_clip(t_rect *rect, t_i32 max_w, t_i32 max_h)
{
	if (rect->x < 0)
	{
		rect->w += rect->x;
		rect->x = 0;
	}
	if (rect->y < 0)
	{
		rect->h += rect->y;
		rect->y = 0;
	}
	if (rect->x + rect->w > max_w)
		rect->w = max_w - rect->x;
	if (rect->y + rect->h > max_h)
		rect->h = max_h - rect->y;
	if (rect->w < 0)
		rect->w = 0;
	if (rect->h < 0)
		rect->h = 0;
}
