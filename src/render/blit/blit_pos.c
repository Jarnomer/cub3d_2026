/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	blit_set_position(t_blit *blit, t_vec2i pos)
{
	blit->pos = pos;
	blit->start = pos;
	blit->end.x = pos.x + blit->size.x;
	blit->end.y = pos.y + blit->size.y;
	blit->offset = vec2i_new(0, 0);
}

void	blit_set_centered(t_blit *blit, t_vec2i pos)
{
	blit->pos = pos;
	blit->start.x = pos.x - blit->size.x / 2;
	blit->start.y = pos.y - blit->size.y / 2;
	blit->end.x = blit->start.x + blit->size.x;
	blit->end.y = blit->start.y + blit->size.y;
	blit->offset = vec2i_new(0, 0);
}

void	blit_apply_offset(t_blit *blit, t_vec2i offset)
{
	blit->pos.x += offset.x;
	blit->pos.y += offset.y;
	blit->start.x += offset.x;
	blit->start.y += offset.y;
	blit->end.x += offset.x;
	blit->end.y += offset.y;
}

void	blit_clip_bounds(t_blit *blit, t_i32 scr_w, t_i32 scr_h)
{
	if (blit->start.x < 0)
	{
		blit->offset.x = -blit->start.x;
		blit->start.x = 0;
	}
	if (blit->start.y < 0)
	{
		blit->offset.y = -blit->start.y;
		blit->start.y = 0;
	}
	if (blit->end.x > scr_w)
		blit->end.x = scr_w;
	if (blit->end.y > scr_h)
		blit->end.y = scr_h;
}
