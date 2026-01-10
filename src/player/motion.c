/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	motion_init(t_motion *motion)
{
	*motion = (t_motion){0};
	motion->stamina = STAMINA_MAX;
	motion->is_grounded = true;
	motion->crouch_amount = 0.0f;
	motion->crouch_target = 0.0f;
}

t_f32	motion_get_speed_mult(t_motion *motion)
{
	t_f32	mult;

	mult = 1.0f;
	if (motion->is_crouching)
		mult *= CROUCH_SPEED_MULT;
	if (!motion->is_grounded)
		mult *= JUMP_SPEED_MULT;
	return (mult);
}

t_f32	motion_get_height(t_motion *motion)
{
	return (motion->height_offset - motion->crouch_amount * CROUCH_HEIGHT);
}

void	motion_jump(t_motion *motion)
{
	if (!motion->is_grounded || motion->is_crouching)
		return ;
	if (motion->stamina < JUMP_STAMINA_COST)
		return ;
	motion->jump_vel = JUMP_VELOCITY;
	motion->is_grounded = false;
	motion->stamina -= JUMP_STAMINA_COST;
}

void	motion_crouch_start(t_motion *motion)
{
	motion->is_crouching = true;
	motion->crouch_target = 1.0f;
}
