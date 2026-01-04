/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	draw_tex_column(t_game *game, t_i32 x, t_wall *s, t_tex *t)
{
	t_f32	step;
	t_f32	tex_pos;
	t_i32	tex_y;
	t_i32	y;
	t_color	c;

	step = (t_f32)t->height / (t_f32)s->height;
	tex_pos = (s->begin - game->render.height / 2 + s->height / 2);
	tex_pos *= step;
	y = s->begin;
	while (y <= s->end)
	{
		tex_y = clampi((t_i32)tex_pos, 0, t->height - 1);
		c = texture_sample_color(t, s->tex_x, tex_y);
		render_pixel(game->render.frame, x, y, c);
		tex_pos += step;
		y++;
	}
}

static t_vec2	get_dir(t_camera *cam, t_i32 x, t_i32 screen_w)
{
	t_f32	cam_x;

	cam_x = 2.0f * x / (t_f32)screen_w - 1.0f;
	return (vec2_add(cam->dir, vec2_mul(cam->plane, cam_x)));
}

static void	raycast_column(t_game *game, t_i32 x)
{
	t_ray	ray;
	t_hit	hit;
	t_wall	wall;
	t_tex	*tex;
	t_vec2	dir;

	dir = get_dir(&game->camera, x, game->render.width);
	ray_init(&ray, game->camera.pos, dir);
	hit = ray_cast(&ray, game->map, RAY_MAX_DIST);
	if (!hit.hit)
		return ;
	tex = &game->map->textures[hit.dir];
	wall = raycast_get_wall(&hit, game->render.height, tex->width);
	if (game->render.z_buffer)
		game->render.z_buffer[x] = hit.dist;
	draw_tex_column(game, x, &wall, tex);
}

void	raycast_walls(t_game *game)
{
	t_i32	x;

	x = 0;
	while (x < game->render.width)
	{
		raycast_column(game, x);
		x++;
	}
}
