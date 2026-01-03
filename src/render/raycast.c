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

static void	init_ray(t_ray *ray, t_game *game, int x)
{
	t_camera	cam;
	t_f32		cam_x;

	cam = game->camera;
	cam_x = 2.0f * x / (t_f32)game->render.width - 1.0f;
	ray->dir = vec2_add(cam.dir, vec2_mul(cam.plane, cam_x));
	ray->pos = vec2i_from_vec2(cam.pos);
	ray->delta.x = inv_absf(ray->dir.x);
	ray->delta.y = inv_absf(ray->dir.y);
	ray->hit = false;
}

static void	init_step(t_ray *ray, t_vec2 cam_pos)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->axis.x = (cam_pos.x - ray->pos.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->axis.x = (ray->pos.x + 1.0f - cam_pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->axis.y = (cam_pos.y - ray->pos.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->axis.y = (ray->pos.y + 1.0f - cam_pos.y) * ray->delta.y;
	}
}

static void	perform_dda(t_ray *ray, t_game *game)
{
	while (!ray->hit)
	{
		if (ray->axis.x < ray->axis.y)
		{
			ray->axis.x += ray->delta.x;
			ray->pos.x += ray->step.x;
			ray->side = AXIS_X;
		}
		else
		{
			ray->axis.y += ray->delta.y;
			ray->pos.y += ray->step.y;
			ray->side = AXIS_Y;
		}
		if (map_is_wall(game->map, ray->pos.x, ray->pos.y))
			ray->hit = true;
	}
	if (ray->side == AXIS_X)
		ray->perp_dist = ray->axis.x - ray->delta.x;
	else
		ray->perp_dist = ray->axis.y - ray->delta.y;
	ray->perp_dist = maxf(ray->perp_dist, EPSILON);
}

static t_color	get_wall_color(t_ray *ray)
{
	if (ray->side == AXIS_X)
	{
		if (ray->step.x > 0)
			return (color_new(200, 50, 50, 255));
		else
			return (color_new(50, 200, 50, 255));
	}
	else
	{
		if (ray->step.y > 0)
			return (color_new(50, 50, 200, 255));
		else
			return (color_new(200, 200, 50, 255));
	}
}

void	raycast(t_game *game)
{
	t_ray	ray;
	t_i32	line_h;
	t_i32	game_h;
	int		col_y[2];
	int		col_x;

	col_x = 0;
	game_h = game->render.height;
	while (col_x < game->render.width)
	{
		init_ray(&ray, game, col_x);
		init_step(&ray, game->camera.pos);
		perform_dda(&ray, game);
		line_h = game_h / ray.perp_dist;
		col_y[0] = -line_h / 2 + game_h / 2;
		col_y[1] = line_h / 2 + game_h / 2;
		col_y[0] = clampi(col_y[0], 0, game_h - 1);
		col_y[1] = clampi(col_y[1], 0, game_h - 1);
		render_vline(game, col_x, col_y, get_wall_color(&ray));
		col_x++;
	}
}
