/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_door_pixel(t_game *game, t_i32 x, t_i32 y, t_u32 color)
{
	t_u32	existing;
	t_u8	alpha;

	alpha = color_a(color);
	if (alpha < ALPHA_THRESHOLD)
		return ;
	if (alpha >= ALPHA_OPAQUE)
	{
		render_pixel(game->render.frame, x, y, color);
		return ;
	}
	existing = ((t_u32 *)game->render.frame->pixels)
	[y * game->render.frame->width + x];
	render_pixel(game->render.frame, x, y, color_blend(color, existing, alpha));
}

static void	draw_door_column(t_game *game, t_i32 x, t_wall *wall, t_sheet *sht)
{
	t_f32	step;
	t_f32	tex_pos;
	t_i32	y;
	t_u32	color;
	t_u8	fog;

	fog = lookup_fog(&game->lookup, wall->dist);
	step = (t_f32)sht->height / (t_f32)wall->height;
	tex_pos = (wall->start - wall->top - wall->offset) * step;
	y = wall->start;
	while (y <= wall->end)
	{
		color = sheet_sample(sht, wall->dir, wall->tex_x,
				clampi((t_i32)tex_pos, 0, sht->height - 1));
		color = fog_apply(color, fog);
		draw_door_pixel(game, x, y, color);
		tex_pos += step;
		y++;
	}
}

static void	calc_door_offset(t_game *game, t_wall *wall)
{
	t_i32	h;

	h = game->render.height;
	wall->offset = (t_i32)(game->camera.pitch * h);
	wall->start = clampi(wall->top + wall->offset, 0, h - 1);
	wall->end = clampi(wall->bottom + wall->offset, 0, h - 1);
}

static t_wall	calc_door_slice(t_hit *hit, t_i32 screen_h, t_sheet *sheet)
{
	t_wall	wall;

	wall.dist = hit->dist;
	wall.tex_x = (t_i32)(hit->wall_x * (t_f32)sheet->width);
	if (hit->axis == AXIS_X && hit->dir == WALL_EAST)
		wall.tex_x = sheet->width - wall.tex_x - 1;
	if (hit->axis == AXIS_Y && hit->dir == WALL_SOUTH)
		wall.tex_x = sheet->width - wall.tex_x - 1;
	wall.tex_x = clampi(wall.tex_x, 0, sheet->width - 1);
	wall.height = (t_i32)(screen_h / hit->dist);
	wall.top = -wall.height / 2 + screen_h / 2;
	wall.bottom = wall.height / 2 + screen_h / 2;
	return (wall);
}

void	render_door_column(t_game *game, t_hit *hit, t_i32 x)
{
	t_entity	*ent;
	t_sheet		*sheet;
	t_wall		wall;

	if (hit->entity < 0)
		return ;
	ent = darray_get(&game->entities, hit->entity);
	if (!ent || !ent->active)
		return ;
	sheet = assets_get_sheet(&game->assets, ent->sheet_id);
	if (!sheet || !sheet->tex.pixels)
		return ;
	wall = calc_door_slice(hit, game->render.height, sheet);
	calc_door_offset(game, &wall);
	wall.dir = door_get_frame(ent, &game->assets);
	if (hit->dist < game->render.z_buffer[x])
		game->render.z_buffer[x] = hit->dist;
	draw_door_column(game, x, &wall, sheet);
}
