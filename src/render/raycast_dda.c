/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	ray_init(t_ray *ray, t_vec2 origin, t_vec2 dir)
{
	ray->origin = origin;
	ray->dir = dir;
	ray->grid = vec2i_from_vec2(origin);
	ray->delta.x = iabsf(dir.x);
	ray->delta.y = iabsf(dir.y);
	if (dir.x < 0)
	{
		ray->step.x = -1;
		ray->dist.x = (origin.x - ray->grid.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->dist.x = (ray->grid.x + 1.0f - origin.x) * ray->delta.x;
	}
	if (dir.y < 0)
	{
		ray->step.y = -1;
		ray->dist.y = (origin.y - ray->grid.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->dist.y = (ray->grid.y + 1.0f - origin.y) * ray->delta.y;
	}
}

static t_dir	get_dir(t_ray *ray, int axis)
{
	if (axis == AXIS_X)
	{
		if (ray->step.x > 0)
			return (WALL_WEST);
		return (WALL_EAST);
	}
	if (ray->step.y > 0)
		return (WALL_NORTH);
	return (WALL_SOUTH);
}

static t_f32	calc_wall_x(t_ray *ray, t_f32 dist, int axis)
{
	t_f32	wall_x;

	if (axis == AXIS_X)
		wall_x = ray->origin.y + dist * ray->dir.y;
	else
		wall_x = ray->origin.x + dist * ray->dir.x;
	return (wall_x - floorf(wall_x));
}

static t_f32	calc_dist(t_ray *ray, int axis)
{
	t_f32	dist;

	if (axis == AXIS_X)
		dist = ray->dist.x - ray->delta.x;
	else
		dist = ray->dist.y - ray->delta.y;
	return (maxf(dist, EPSILON));
}

t_hit	ray_cast(t_ray *ray, t_map *map, t_f32 max_dist)
{
	t_hit	hit;
	int		axis;

	ft_bzero(&hit, sizeof(t_hit));
	axis = AXIS_X;
	while (!hit.hit)
	{
		if (ray->dist.x < ray->dist.y)
		{
			ray->dist.x += ray->delta.x;
			ray->grid.x += ray->step.x;
			axis = AXIS_X;
		}
		else
		{
			ray->dist.y += ray->delta.y;
			ray->grid.y += ray->step.y;
			axis = AXIS_Y;
		}
		if (map_is_wall(map, ray->grid.x, ray->grid.y))
			hit.hit = true;
		if (calc_dist(ray, axis) > max_dist)
			break ;
	}
	hit.axis = axis;
	hit.dist = calc_dist(ray, axis);
	hit.wall_x = calc_wall_x(ray, hit.dist, axis);
	hit.dir = get_dir(ray, axis);
	hit.grid = ray->grid;
	return (hit);
}
