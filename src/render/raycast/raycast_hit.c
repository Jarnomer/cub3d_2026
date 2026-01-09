/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_dir	get_wall_direction(t_ray *ray, int axis)
{
	if (axis == AXIS_X)
	{
		if (ray->step.x > 0)
			return (WALL_WEST);
		return (WALL_EAST);
	}
	if (ray->step.y > 0)
		return (WALL_SOUTH);
	return (WALL_NORTH);
}

static t_f32	calc_wall_hit_x(t_ray *ray, t_f32 dist, int axis)
{
	t_f32	wall_x;

	if (axis == AXIS_X)
		wall_x = ray->origin.y + dist * ray->dir.y;
	else
		wall_x = ray->origin.x + dist * ray->dir.x;
	return (wall_x - floorf(wall_x));
}

void	ray_hit(t_hit *hit, t_ray *ray, int axis)
{
	hit->dist = ray_dist(ray, axis);
	hit->wall_x = calc_wall_hit_x(ray, hit->dist, axis);
	hit->dir = get_wall_direction(ray, axis);
	hit->grid = ray->grid;
	hit->axis = axis;
}
