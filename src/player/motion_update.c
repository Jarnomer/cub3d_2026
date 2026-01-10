/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	motion_crouch_end(t_motion *motion)
{
	motion->is_crouching = false;
	motion->crouch_target = 0.0f;
}

static void	update_crouch(t_motion *motion, t_f32 dt)
{
	t_f32	diff;

	diff = motion->crouch_target - motion->crouch_amount;
	if (absf(diff) < 0.01f)
		motion->crouch_amount = motion->crouch_target;
	else
		motion->crouch_amount += diff * CROUCH_LERP_SPEED * dt;
}

static void	update_jump(t_motion *motion, t_f32 dt)
{
	if (motion->is_grounded)
		return ;
	motion->jump_vel -= GRAVITY * dt;
	motion->height_offset += motion->jump_vel * dt;
	if (motion->height_offset <= 0.0f)
	{
		motion->height_offset = 0.0f;
		motion->jump_vel = 0.0f;
		motion->is_grounded = true;
	}
}

static void	update_stamina(t_motion *motion, t_f32 dt)
{
	if (motion->stamina < STAMINA_MAX)
	{
		motion->stamina += STAMINA_REGEN * dt;
		if (motion->stamina > STAMINA_MAX)
			motion->stamina = STAMINA_MAX;
	}
}

void	motion_update(t_motion *motion, t_game *game, t_f32 dt)
{
	(void)game;
	update_jump(motion, dt);
	update_crouch(motion, dt);
	update_stamina(motion, dt);
}
