/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda_pass.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	record_door(t_hit *door, t_ray *ray, int axis, t_i32 entity)
{
	if (door->entity != ENTITY_VOID)
		return ;
	door->hit = true;
	door->cell = CELL_DOOR;
	door->entity = entity;
	ray_hit(door, ray, axis);
}

static void	pass_check_door(t_hit *hit, t_hit *door, t_game *game, t_ray *ray)
{
	int		axis;
	t_i32	entity;

	axis = hit->axis;
	entity = hit->entity;
	record_door(door, ray, axis, entity);
	if (grid_door_block(game, entity))
	{
		hit->hit = true;
		hit->cell = CELL_DOOR;
		ray_hit(hit, ray, axis);
	}
}

static void	pass_check_wall(t_hit *hit, t_ray *ray, int axis)
{
	hit->hit = true;
	hit->cell = CELL_WALL;
	ray_hit(hit, ray, axis);
}

static void	pass_check_cell(t_hit *hit, t_hit *door, t_game *game, t_ray *ray)
{
	t_cell	cell;
	t_i32	entity;
	int		axis;

	axis = hit->axis;
	cell = grid_check_cell(game, ray->grid, &entity);
	hit->entity = entity;
	if (cell == CELL_WALL)
		pass_check_wall(hit, ray, axis);
	else if (cell == CELL_DOOR)
		pass_check_door(hit, door, game, ray);
}

t_hit	passthr_dda(t_ray *ray, t_game *game, t_f32 max_dist, t_hit *door)
{
	int		axis;
	t_hit	hit;

	hit = (t_hit){.entity = ENTITY_VOID};
	*door = (t_hit){.entity = ENTITY_VOID};
	axis = 0;
	while (!hit.hit)
	{
		ray_step(ray, &axis);
		hit.axis = axis;
		pass_check_cell(&hit, door, game, ray);
		if (ray_dist(ray, axis) > max_dist)
			break ;
	}
	if (!hit.hit)
		ray_hit(&hit, ray, axis);
	return (hit);
}
