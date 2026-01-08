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

t_i32	slice_calc_tex_x(t_hit *hit, t_i32 tex_w)
{
	t_i32	tex_x;

	tex_x = (t_i32)(hit->wall_x * (t_f32)tex_w);
	if (hit->axis == AXIS_X && hit->dir == WALL_EAST)
		tex_x = tex_w - tex_x - 1;
	if (hit->axis == AXIS_Y && hit->dir == WALL_SOUTH)
		tex_x = tex_w - tex_x - 1;
	return (clampi(tex_x, 0, tex_w - 1));
}

t_slice	slice_from_hit(t_hit *hit, t_i32 screen_h, t_i32 tex_w)
{
	t_slice	s;

	s = (t_slice){0};
	s.dist = hit->dist;
	s.dir = hit->dir;
	s.height = project_wall_height(hit->dist, screen_h);
	s.top = -s.height / 2 + screen_h / 2;
	s.bottom = s.height / 2 + screen_h / 2;
	s.tex_x = slice_calc_tex_x(hit, tex_w);
	return (s);
}

void	slice_apply_pitch(t_slice *s, t_camera *cam, t_i32 screen_h)
{
	s->offset = (t_i32)(cam->pitch * screen_h);
	s->start = s->top + s->offset;
	s->end = s->bottom + s->offset;
	column_clamp_bounds(screen_h, &s->start, &s->end);
}

void	slice_calc_tex_step(t_slice *s, t_i32 tex_h)
{
	s->tex_step = (t_f32)tex_h / (t_f32)s->height;
	s->tex_pos = (s->start - s->top - s->offset) * s->tex_step;
}

bool	slice_is_visible(t_slice *s, t_i32 screen_h)
{
	if (s->end < 0)
		return (false);
	if (s->start >= screen_h)
		return (false);
	return (true);
}
