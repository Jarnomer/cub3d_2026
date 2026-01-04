/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_tex_column(t_game *game, t_i32 x, t_wall *wall, t_tex *tex)
{
	t_f32	step;
	t_f32	tex_pos;
	t_i32	tex_y;
	t_i32	y;

	step = (t_f32)tex->height / (t_f32)wall->height;
	tex_pos = (wall->begin - wall->top - wall->offset) * step;
	y = wall->begin;
	while (y <= wall->end)
	{
		tex_y = clampi((t_i32)tex_pos, 0, tex->height - 1);
		render_pixel(game->render.frame, x, y,
			texture_sample_color(tex, wall->tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}

static void	raycast_pitch_offset(t_game *game, t_wall	*wall)
{
	t_i32		game_height;

	game_height = game->render.height;
	wall->offset = (t_i32)(game->camera.pitch * game_height);
	wall->begin = clampi(wall->top + wall->offset, 0, game_height - 1);
	wall->end = clampi(wall->bottom + wall->offset, 0, game_height - 1);
}

static t_wall	raycast_get_wall(t_hit *hit, t_i32 screen_h, t_i32 tex_w)
{
	t_wall	wall;

	wall.dist = hit->dist;
	wall.dir = hit->dir;
	wall.height = (t_i32)(screen_h / hit->dist);
	wall.top = -wall.height / 2 + screen_h / 2;
	wall.bottom = wall.height / 2 + screen_h / 2;
	wall.tex_x = (t_i32)(hit->wall_x * (t_f32)tex_w);
	if (hit->axis == AXIS_X && hit->dir == WALL_WEST)
		wall.tex_x = tex_w - wall.tex_x - 1;
	if (hit->axis == AXIS_Y && hit->dir == WALL_SOUTH)
		wall.tex_x = tex_w - wall.tex_x - 1;
	wall.tex_x = clampi(wall.tex_x, 0, tex_w - 1);
	return (wall);
}

static void	raycast_column(t_game *game, t_i32 x)
{
	t_ray	ray;
	t_hit	hit;
	t_wall	wall;
	t_vec2	dir;
	t_f32	cam_x;

	cam_x = 2.0f * x / (t_f32)game->render.width - 1.0f;
	dir = vec2_add(game->camera.dir, vec2_mul(game->camera.plane, cam_x));
	ray_init(&ray, game->camera.pos, dir);
	hit = perform_dda(&ray, game->map, RAY_MAX_DIST);
	if (!hit.hit)
		return ;
	wall = raycast_get_wall(&hit, game->render.height,
			game->map->textures[hit.dir].width);
	raycast_pitch_offset(game, &wall);
	if (game->render.z_buffer)
		game->render.z_buffer[x] = hit.dist;
	draw_tex_column(game, x, &wall, &game->map->textures[hit.dir]);
}

void	render_walls(t_game *game)
{
	t_i32	x;

	x = 0;
	while (x < game->render.width)
	{
		raycast_column(game, x);
		x++;
	}
}
