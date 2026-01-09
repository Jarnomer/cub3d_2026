/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	hitscan_dda(t_vec2 from, t_vec2 to, t_game *game)
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
	hit = perform_dda(&ray, game, dist);
	if (!hit.hit)
		return (true);
	if (hit.dist >= dist - EPSILON)
		return (true);
	return (false);
}

t_hit	perform_dda(t_ray *ray, t_game *game, t_f32 max_dist)
{
	t_cell	cell;
	t_i32	entity;
	int		axis;
	t_hit	hit;

	hit = (t_hit){.entity = ENTITY_VOID};
	axis = 0;
	while (!hit.hit)
	{
		ray_step(ray, &axis);
		cell = grid_check_cell(game, ray->grid, &entity);
		if (cell == CELL_WALL)
			hit.hit = true;
		else if (cell == CELL_DOOR && grid_door_block(game, entity))
			hit.hit = true;
		if (hit.hit)
		{
			hit.cell = (t_u8)cell;
			hit.entity = entity;
		}
		if (ray_dist(ray, axis) > max_dist)
			break ;
	}
	ray_hit(&hit, ray, axis);
	return (hit);
}

static void	record_door_hit(t_hit *door_out, t_ray *ray, int axis, t_i32 entity)
{
	if (door_out->entity != ENTITY_VOID)
		return ;
	door_out->hit = true;
	door_out->cell = CELL_DOOR;
	door_out->entity = entity;
	ray_hit(door_out, ray, axis);
}

t_hit	passthr_dda(t_ray *ray, t_game *game, t_f32 max_dist, t_hit *door_out)
{
	t_cell	cell;
	t_i32	entity;
	int		axis;
	t_hit	hit;

	hit = (t_hit){.entity = ENTITY_VOID};
	*door_out = (t_hit){.entity = ENTITY_VOID};
	axis = 0;
	while (!hit.hit)
	{
		ray_step(ray, &axis);
		cell = grid_check_cell(game, ray->grid, &entity);
		if (cell == CELL_WALL)
			hit.hit = true;
		else if (cell == CELL_DOOR)
		{
			record_door_hit(door_out, ray, axis, entity);
			if (grid_door_block(game, entity))
				hit.hit = true;
		}
		if (hit.hit)
		{
			hit.cell = (t_u8)cell;
			hit.entity = entity;
		}
		if (ray_dist(ray, axis) > max_dist)
			break ;
	}
	ray_hit(&hit, ray, axis);
	return (hit);
}
