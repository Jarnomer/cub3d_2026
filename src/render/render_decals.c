/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_decals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/02/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static bool	decal_matches_hit(t_decal *d, t_decaldef *def, t_hit *hit)
{
	t_f32	half;

	if (d->dir != hit->dir)
		return (false);
	if (d->grid.x != hit->grid.x || d->grid.y != hit->grid.y)
		return (false);
	half = def->scale / 2.0f;
	if (hit->wall_x < d->wall_x - half)
		return (false);
	if (hit->wall_x > d->wall_x + half)
		return (false);
	return (true);
}

static t_slice	calc_decal_slice(t_game *game, t_hit *hit,
	t_decal *d, t_decaldef *def)
{
	t_slice	s;
	t_f32	wall_h;
	t_i32	center;

	s = (t_slice){0};
	wall_h = (t_f32)game->render.height / maxf(hit->dist, EPSILON);
	s.height = maxi((t_i32)(def->scale * wall_h), 1);
	s.dist = hit->dist;
	center = game->render.height / 2;
	center += camera_wall_offset(game, hit->dist);
	center += (t_i32)(game->camera.pitch * game->render.height);
	center -= (t_i32)(d->pos.z * wall_h);
	s.top = center - s.height / 2;
	s.bottom = center + s.height / 2;
	s.start = clampi(s.top, 0, game->render.height - 1);
	s.end = clampi(s.bottom, 0, game->render.height - 1);
	return (s);
}

static void	draw_decal_col(t_game *game, t_slice *s, t_sheet *sht, t_i32 x)
{
	t_u32	color;
	t_u32	fog;
	t_i32	tex_y;
	t_i32	y;

	slice_calc_tex_step(s, sht->height);
	fog = lookup_fog(&game->lookup, s->dist);
	y = s->start;
	while (y <= s->end)
	{
		tex_y = clampi((t_i32)s->tex_y, 0, sht->height - 1);
		color = sheet_sample(sht, s->frame, s->tex_x, tex_y);
		if (color_is_opaque(color))
			render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		s->tex_y += s->step;
		y++;
	}
}

static void	try_render_decal(t_game *game, t_hit *hit, t_decal *d, t_i32 x)
{
	t_decaldef	*def;
	t_sheet		*sheet;
	t_slice		slice;
	t_f32		left;

	def = decal_get_def(&game->decals, d->type);
	if (!def || !decal_matches_hit(d, def, hit))
		return ;
	sheet = assets_get_sheet(&game->assets, def->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return ;
	slice = calc_decal_slice(game, hit, d, def);
	left = d->wall_x - def->scale / 2.0f;
	slice.tex_x = clampi((t_i32)(((hit->wall_x - left) / def->scale)
				* (t_f32)sheet->width), 0, sheet->width - 1);
	slice.frame = d->frame;
	draw_decal_col(game, &slice, sheet, x);
}

void	render_decals(t_game *game, t_hit *hit, t_i32 x)
{
	t_decalmgr	*mgr;
	t_decal		*decal;
	t_u32		i;

	mgr = &game->decals;
	if (mgr->active == 0)
		return ;
	i = 0;
	while (i < mgr->pool.capacity)
	{
		if (!mgr->pool.active_flags[i])
		{
			i++;
			continue ;
		}
		decal = decal_get(mgr, i);
		if (decal && decal->is_active)
			try_render_decal(game, hit, decal, x);
		i++;
	}
}
