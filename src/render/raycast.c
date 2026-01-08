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

/*
** DDA (Digital Differential Analysis) Ray Casting
**
** The algorithm traces a ray through a 2D grid by stepping from cell to cell,
** always crossing the nearest grid line first.
**
**        +---+---+---+---+
**        |   |   |   |   |
**        +---+---*---+---+    * = ray origin
**        |   | / |   |   |    The ray travels until hitting a wall
**        +---+/--+---+---+
**        |  /|   |   |   |
**        +-/-+---+---+---+
**        |/  |   |   |   |
**        +---+---+---+---+
**
** Key insight: We don't sample the ray at fixed intervals.
** Instead, we jump from grid line to grid line.
**
** delta.x = distance to travel along ray to cross 1 unit in X
** delta.y = distance to travel along ray to cross 1 unit in Y
**
** For a ray with direction (dx, dy):
**   delta.x = |1 / dx|  (infinite if dx == 0)
**   delta.y = |1 / dy|  (infinite if dy == 0)
*/

/*
** Initializes Y-axis stepping parameters
**
** If ray points up (dir.y < 0):
**   - Step decrements grid.y
**   - Initial dist.y is distance to cell's top edge
**
** If ray points down (dir.y > 0):
**   - Step increments grid.y
**   - Initial dist.y is distance to cell's bottom edge
*/

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

/*
** Initializes X-axis stepping parameters
**
** Same logic as Y-axis:
**   dir.x < 0: step left, measure to left edge
**   dir.x > 0: step right, measure to right edge
*/

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

/*
** Initializes ray for DDA traversal
**
** Sets up:
**   - Origin point and direction
**   - Starting grid cell
**   - Delta distances (1/|dir| for each axis)
**   - Step directions and initial distances
*/

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

/*
** Advances ray to next grid cell
**
** Always crosses the nearest grid line first:
**   - If dist.x < dist.y: cross vertical line (move in X)
**   - Otherwise: cross horizontal line (move in Y)
**
**        dist.x         dist.y
**        <---->         <---->
**        +----+----+    +----+----+
**        |    |    |    |    |    |
**        | *--+->  |    | *  |    |
**        |    |    |    | |  |    |
**        +----+----+    +-+--+----+
**                         V
**
** After stepping:
**   - grid is updated to new cell
**   - dist is updated to next grid line
**   - axis output indicates which boundary was crossed
*/

void	ray_step(t_ray *ray, int *axis)
{
	if (ray->dist.x < ray->dist.y)
	{
		ray->dist.x += ray->delta.x;
		ray->grid.x += ray->step.x;
		*axis = AXIS_X;
	}
	else
	{
		ray->dist.y += ray->delta.y;
		ray->grid.y += ray->step.y;
		*axis = AXIS_Y;
	}
}
