/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_sway.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	sway_calc_idle(t_sway *sway, t_f32 dt)
{
	sway->phase += SWAY_IDLE_FREQ * dt;
	if (sway->phase > TAU)
		sway->phase -= TAU;
	sway->target.x = sinf(sway->phase) * SWAY_IDLE_AMP_X;
	sway->target.y = sinf(sway->phase * 2.0f) * SWAY_IDLE_AMP_Y;
}

static void	sway_calc_move(t_sway *sway, t_bob *bob, t_f32 amp_mult)
{
	t_f32	amp_x;
	t_f32	amp_y;

	amp_x = SWAY_MOVE_AMP_X * amp_mult;
	amp_y = SWAY_MOVE_AMP_Y * amp_mult;
	sway->target.x = sinf(bob->phase * 0.5f) * amp_x;
	sway->target.y = sinf(bob->phase) * amp_y;
}

static t_f32	sway_get_amp_mult(t_sway *sway, t_motion *motion)
{
	t_f32	mult;

	mult = 1.0f;
	if (motion->is_crouching)
		mult *= SWAY_CROUCH_MULT;
	mult += sway->sprint * SPRINT_SWAY_MULT;
	return (mult);
}

void	weapon_sway_update(t_sway *sway, t_motion *motion, t_f32 dt)
{
	t_f32	speed;
	t_f32	amp_mult;
	t_f32	factor;

	speed = vec2_len(motion->velocity);
	if (motion->is_sprinting)
		sway->sprint = lerpf(sway->sprint, 1.0f, SPRINT_LERP * dt);
	else
		sway->sprint = lerpf(sway->sprint, 0.0f, SPRINT_LERP * dt);
	amp_mult = sway_get_amp_mult(sway, motion);
	if (speed < MOVE_STOP_THRESHOLD)
		sway_calc_idle(sway, dt);
	else
		sway_calc_move(sway, &motion->bob, amp_mult);
	factor = SWAY_LERP_SPEED * dt;
	sway->current.x = lerpf(sway->current.x, sway->target.x, factor);
	sway->current.y = lerpf(sway->current.y, sway->target.y, factor);
}
