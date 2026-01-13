/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_bob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	bob_calc_idle(t_bob *bob, t_f32 dt)
{
	bob->phase += BOB_IDLE_FREQ * dt;
	bob->target_amp_y = BOB_IDLE_AMP;
	bob->target_amp_x = 0.0f;
	bob->target_freq = BOB_IDLE_FREQ;
}

static void	bob_calc_move(t_bob *bob, t_motion *motion, t_f32 speed)
{
	t_f32	mult;

	mult = 1.0f;
	if (motion->is_crouching)
		mult = BOB_CROUCH_MULT;
	bob->target_amp_y = BOB_WALK_AMP_Y * mult;
	bob->target_amp_x = BOB_WALK_AMP_X * mult;
	bob->target_freq = BOB_WALK_FREQ * (speed / PLAYER_SPEED);
}

static void	bob_calc_sprint(t_bob *bob, t_f32 speed)
{
	t_f32	mult;

	bob->target_amp_y = BOB_SPRINT_AMP_Y;
	bob->target_amp_x = BOB_SPRINT_AMP_X;
	mult = speed / (PLAYER_SPEED * SPRINT_SPEED_MULT);
	bob->target_freq = BOB_SPRINT_FREQ * mult;
}

static void	bob_apply_offsets(t_bob *bob, t_motion *motion, t_f32 dt)
{
	t_f32	sin_val;
	t_f32	cos_val;

	bob->phase += bob->current_freq * dt;
	if (bob->phase > TAU)
		bob->phase -= TAU;
	sin_val = sinf(bob->phase);
	if (motion->is_sprinting && sin_val > 0.0f)
		sin_val = powf(sin_val, BOB_SPRINT_ASYM);
	cos_val = cosf(bob->phase * 0.5f);
	bob->amount_y = sin_val * bob->current_amp_y;
	bob->amount_x = cos_val * bob->current_amp_x;
}

void	bob_update(t_bob *bob, t_motion *motion, t_f32 dt)
{
	t_f32	speed;
	t_f32	factor;

	speed = vec2_len(motion->velocity);
	if (speed < MOVE_STOP_THRESHOLD)
		bob_calc_idle(bob, dt);
	else if (motion->is_sprinting)
		bob_calc_sprint(bob, speed);
	else
		bob_calc_move(bob, motion, speed);
	factor = BOB_LERP_SPEED * dt;
	bob->current_amp_y = lerpf(bob->current_amp_y, bob->target_amp_y, factor);
	bob->current_amp_x = lerpf(bob->current_amp_x, bob->target_amp_x, factor);
	bob->current_freq = lerpf(bob->current_freq, bob->target_freq, factor);
	bob_apply_offsets(bob, motion, dt);
}
