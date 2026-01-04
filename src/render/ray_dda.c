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

static t_hit	update_ray_data(t_hit *hit, t_ray *ray, int axis)
{
	hit->axis = axis;
	hit->dist = calc_dist(ray, axis);
	hit->wall_x = calc_wall_x(ray, hit->dist, axis);
	hit->dir = get_dir(ray, axis);
	hit->grid = ray->grid;
	return (*hit);
}

t_hit	ray_cast(t_ray *ray, t_map *map, t_f32 max_dist)
{
	t_hit	hit;
	int		axis;

	ft_bzero(&hit, sizeof(t_hit));
	axis = -1;
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
	return (update_ray_data(&hit, ray, axis));
}
