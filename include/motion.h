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
	t_f32	speed_current;
	t_f32	speed_target;
	t_f32	bob_timer;
	t_f32	bob_offset;
	t_f32	idle_timer;
	t_f32	idle_offset;
	t_f32	jump_vel;
	t_f32	height_offset;
	t_f32	crouch_amount;
	t_f32	crouch_target;
	t_f32	stamina;
	bool	is_grounded;
	bool	is_crouching;
	bool	is_moving;
}	t_motion;

typedef struct s_shake
{
	t_f32	intensity;
	t_f32	duration;
	t_f32	timer;
	t_f32	offset_x;
	t_f32	offset_y;
	t_f32	decay;
}	t_shake;

void	motion_init(t_motion *motion);
void	motion_update(t_motion *motion, t_game *game, t_f32 dt);

void	motion_jump(t_motion *motion);
void	motion_crouch_start(t_motion *motion);
void	motion_crouch_end(t_motion *motion);

void	shake_init(t_shake *shake);
void	shake_add(t_shake *shake, t_f32 intensity, t_f32 duration);
void	shake_update(t_shake *shake, t_f32 dt);

t_f32	motion_get_speed_mult(t_motion *motion);
t_f32	motion_get_height(t_motion *motion);

void	bob_update(t_motion *motion, t_f32 dt, bool is_moving);
void	idle_update(t_motion *motion, t_f32 dt);
t_f32	bob_get_weapon_offset(t_motion *motion);
t_f32	bob_get_camera_offset(t_motion *motion);

#endif
