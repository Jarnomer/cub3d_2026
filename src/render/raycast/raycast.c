/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_step_y(t_ray *ray, t_vec2 origin, t_vec2 dir)
{
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

static void	init_step_x(t_ray *ray, t_vec2 origin, t_vec2 dir)
{
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
}

void	ray_init(t_ray *ray, t_vec2 origin, t_vec2 dir)
{
	ray->origin = origin;
	ray->dir = dir;
	ray->grid = vec2i_from_vec2(origin);
	ray->delta.x = iabsf(dir.x);
	ray->delta.y = iabsf(dir.y);
	init_step_x(ray, origin, dir);
	init_step_y(ray, origin, dir);
}
