/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_sprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static bool	sprint_can_start(t_motion *motion)
{
	if (motion->is_crouching)
		return (false);
	if (!SPRINT_ALLOW_JUMP && motion->is_jumping)
		return (false);
	if (motion->stamina <= 0.0f)
		return (false);
	return (true);
}

void	sprint_start(t_motion *motion)
{
	if (!sprint_can_start(motion))
		return ;
	motion->is_sprinting = true;
}

void	sprint_end(t_motion *motion)
{
	motion->is_sprinting = false;
}

void	sprint_update(t_motion *motion, t_f32 dt)
{
	if (motion->is_sprinting)
	{
		if (!sprint_can_start(motion))
			sprint_end(motion);
		else
			motion->stamina -= SPRINT_STAMINA_DRAIN * dt;
	}
	else
		motion->stamina += STAMINA_REGEN * dt;
	motion->stamina = clampf(motion->stamina, 0.0f, STAMINA_MAX);
}

t_f32	sprint_get_mult(t_motion *motion)
{
	if (!motion->is_sprinting)
		return (1.0f);
	return (SPRINT_SPEED_MULT);
}
