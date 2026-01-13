/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_slice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_i32	slice_calc_tex_x(t_hit *hit, t_i32 tex_w)
{
	t_i32	tex_x;

	tex_x = (t_i32)(hit->wall_x * (t_f32)tex_w);
	if (hit->axis == AXIS_X && hit->dir == WALL_EAST)
		tex_x = tex_w - tex_x - 1;
	if (hit->axis == AXIS_Y && hit->dir == WALL_SOUTH)
		tex_x = tex_w - tex_x - 1;
	return (clampi(tex_x, 0, tex_w - 1));
}

t_slice	slice_from_hit(t_hit *hit, t_i32 scr_h, t_i32 tex_w)
{
	t_slice	slice;

	slice = (t_slice){.dist = hit->dist, .dir = hit->dir};
	slice.tex_x = slice_calc_tex_x(hit, tex_w);
	if (hit->dist < EPSILON)
		slice.height = scr_h;
	else
		slice.height = scr_h / hit->dist;
	slice.top = -slice.height / 2 + scr_h / 2;
	slice.bottom = slice.height / 2 + scr_h / 2;
	return (slice);
}

void	slice_apply_pitch(t_slice *slice, t_game *game)
{
	slice->offset = (t_i32)(game->camera.pitch * game->render.height);
	slice->start = slice->top + slice->offset;
	slice->end = slice->bottom + slice->offset;
	if (slice->start < 0)
		slice->start = 0;
	if (slice->end >= game->render.height)
		slice->end = game->render.height - 1;
}

void	slice_apply_height(t_slice *slice, t_game *game)
{
	t_i32	offset;

	offset = camera_wall_offset(game, slice->dist);
	slice->top += offset;
	slice->bottom += offset;
	slice->start = slice->top;
	slice->end = slice->bottom;
	if (slice->start < 0)
		slice->start = 0;
	if (slice->end >= game->render.height)
		slice->end = game->render.height - 1;
}

void	slice_calc_tex_step(t_slice *slice, t_i32 tex_h)
{
	t_i32	offset;

	slice->step = (t_f32)tex_h / (t_f32)slice->height;
	offset = slice->start - slice->top - slice->offset;
	slice->tex_y = offset * slice->step;
}
