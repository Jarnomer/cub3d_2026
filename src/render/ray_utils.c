/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	ray_check_los(t_vec2 from, t_vec2 to, t_map *map)
{
	t_ray	ray;
	t_vec2	dir;
	t_f32	dist;
	t_hit	hit;

	dir = vec2_sub(to, from);
	dist = vec2_len(dir);
	if (dist < EPSILON)
		return (true);
	dir = vec2_normalize(dir);
	ray_init(&ray, from, dir);
	hit = ray_cast(&ray, map, dist);
	if (!hit.hit)
		return (true);
	if (hit.dist >= dist - EPSILON)
		return (true);
	return (false);
}

t_wall	raycast_get_wall(t_hit *hit, t_i32 screen_h, t_i32 tex_w)
{
	t_wall	wall;

	wall.dist = hit->dist;
	wall.dir = hit->dir;
	wall.height = (t_i32)(screen_h / hit->dist);
	wall.begin = -wall.height / 2 + screen_h / 2;
	wall.end = wall.height / 2 + screen_h / 2;
	wall.begin = maxi(wall.begin, 0);
	wall.end = mini(wall.end, screen_h - 1);
	wall.tex_x = (t_i32)(hit->wall_x * (t_f32)tex_w);
	if (hit->axis == AXIS_X && hit->dir == WALL_WEST)
		wall.tex_x = tex_w - wall.tex_x - 1;
	if (hit->axis == AXIS_Y && hit->dir == WALL_SOUTH)
		wall.tex_x = tex_w - wall.tex_x - 1;
	wall.tex_x = clampi(wall.tex_x, 0, tex_w - 1);
	return (wall);
}
