/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	blit_set_position(t_blit *blit, t_vec2i pos)
{
	blit->pos = pos;
	blit->bounds = rect_new(pos.x, pos.y, blit->size.x, blit->size.y);
	blit->offset = vec2i_new(0, 0);
}

void	blit_set_centered(t_blit *blit, t_vec2i pos)
{
	blit->pos = pos;
	blit->bounds = rect_centered(pos, blit->size);
	blit->offset = vec2i_new(0, 0);
}

void	blit_apply_offset(t_blit *blit, t_vec2i offset)
{
	blit->pos.x += offset.x;
	blit->pos.y += offset.y;
	blit->bounds.x += offset.x;
	blit->bounds.y += offset.y;
}

void	blit_clip_bounds(t_blit *blit, t_i32 scr_w, t_i32 scr_h)
{
	t_vec2i	center;

	rect_clip(&blit->bounds, scr_w, scr_h);
	center.x = blit->pos.x - blit->size.x / 2;
	center.y = blit->pos.y - blit->size.y / 2;
	if (blit->bounds.x > center.x)
		blit->offset.x = blit->bounds.x - center.x;
	if (blit->bounds.y > center.y)
		blit->offset.y = blit->bounds.y - center.y;
}
