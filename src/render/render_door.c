/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_door_column(t_game *game, t_i32 x, t_wall *wall, t_sheet *sht)
{
	t_f32	step;
	t_f32	tex_pos;
	t_i32	y;
	t_u32	color;
	t_u8	fog;

	fog = lookup_fog(&game->lookup, wall->dist);
	if (fog == 255)
		return ((void)fog_fill_column(game, x, wall->start, wall->end));
	step = (t_f32)sht->height / (t_f32)wall->height;
	tex_pos = (wall->start - wall->top - wall->offset) * step;
	y = wall->start;
	while (y <= wall->end)
	{
		color = sheet_sample(sht, wall->dir, wall->tex_x,
				clampi((t_i32)tex_pos, 0, sht->height - 1));
		if (color_a(color) > 128)
			render_pixel(game->render.frame, x, y, fog_apply(color, fog));
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

static void	calc_door_tex_x(t_wall *wall, t_hit *hit, t_i32 tex_w)
{
	wall->tex_x = (t_i32)(hit->wall_x * (t_f32)tex_w);
	if (hit->axis == AXIS_X && hit->dir == WALL_EAST)
		wall->tex_x = tex_w - wall->tex_x - 1;
	if (hit->axis == AXIS_Y && hit->dir == WALL_SOUTH)
		wall->tex_x = tex_w - wall->tex_x - 1;
	wall->tex_x = clampi(wall->tex_x, 0, tex_w - 1);
}

static t_wall	calc_door_slice(t_hit *hit, t_i32 screen_h, t_i32 tex_w)
{
	t_wall	wall;

	wall.dist = hit->dist;
	wall.dir = hit->dir;
	wall.height = (t_i32)(screen_h / hit->dist);
	wall.top = -wall.height / 2 + screen_h / 2;
	wall.bottom = wall.height / 2 + screen_h / 2;
	calc_door_tex_x(&wall, hit, tex_w);
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
	wall = calc_door_slice(hit, game->render.height, sheet->width);
	calc_door_offset(game, &wall);
	wall.dir = door_get_frame(ent, &game->assets);
	draw_door_column(game, x, &wall, sheet);
}
