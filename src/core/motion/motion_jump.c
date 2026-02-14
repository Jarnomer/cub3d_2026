/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static bool	jump_can_start(t_motion *motion)
{
	if (!motion->is_grounded)
		return (false);
	if (motion->is_crouching)
		return (false);
	if (motion->is_jumping)
		return (false);
	return (true);
}

void	jump_start(t_motion *motion)
{
	if (!jump_can_start(motion))
		return ;
	motion->is_jumping = true;
	motion->is_grounded = false;
	motion->jump.velocity = JUMP_VELOCITY;
}

void	jump_end(t_motion *motion)
{
	motion->is_jumping = false;
	motion->is_grounded = true;
	motion->jump.offset = 0.0f;
	motion->jump.velocity = 0.0f;
}

void	jump_update(t_motion *motion, t_f32 dt)
{
	if (!motion->is_jumping)
		return ;
	motion->jump.velocity -= GRAVITY * dt;
	motion->jump.offset += motion->jump.velocity * dt;
	if (motion->jump.offset <= 0.0f)
		jump_end(motion);
}

t_f32	jump_get_height(t_motion *motion)
{
	return (-motion->jump.offset);
}
