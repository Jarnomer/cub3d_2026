/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOTION_H
# define MOTION_H

# include <types.h>
# include <vector.h>

typedef struct s_game	t_game;

typedef struct s_motion
{
	t_vec2	velocity;
	t_f32	stamina;
	t_f32	crouch_amount;
	t_f32	crouch_target;
	t_f32	jump_offset;
	t_f32	jump_velocity;
	bool	is_grounded;
	bool	is_jumping;
	bool	is_crouching;
	bool	is_sprinting;
}	t_motion;

void	motion_init(t_motion *motion);
void	motion_update(t_motion *motion, t_f32 dt);

void	move_accelerate(t_motion *motion, t_vec2 target, t_f32 dt);
void	move_apply_friction(t_motion *motion, t_f32 dt);
t_vec2	move_get_velocity(t_motion *motion);

void	crouch_start(t_motion *motion);
void	crouch_end(t_motion *motion);
void	crouch_update(t_motion *motion, t_f32 dt);
t_f32	crouch_height(t_motion *motion);
t_f32	crouch_get_mult(t_motion *motion);

bool	jump_can_start(t_motion *motion);
void	jump_start(t_motion *motion);
void	jump_update(t_motion *motion, t_f32 dt);
t_f32	jump_height(t_motion *motion);

bool	sprint_can_start(t_motion *motion);
void	sprint_start(t_motion *motion);
void	sprint_stop(t_motion *motion);
void	sprint_update(t_motion *motion, t_f32 dt);
t_f32	sprint_get_mult(t_motion *motion);

#endif
