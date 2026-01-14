/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
# define WEAPON_H

# include <anim.h>
# include <types.h>
# include <defs.h>

typedef struct s_game	t_game;
typedef struct s_motion	t_motion;
typedef struct s_bob	t_bob;

typedef struct s_wpndef
{
	t_wpn_id	id;
	t_sheet_id	sheet_id;
	t_anim_id	anim_idle;
	t_anim_id	anim_fire;
	t_anim_id	anim_reload;
	t_ammo		ammo_type;
	t_i32		damage;
	t_i32		pellets;
	t_i32		mag_size;
	t_f32		fire_rate;
	t_f32		reload_time;
	t_f32		spread;
	t_f32		range;
	bool		automatic;
}	t_wpndef;

typedef struct s_sway
{
	t_vec2	current;
	t_vec2	target;
	t_vec2	inertia;
	t_vec2	velocity;
	t_f32	phase;
	t_f32	sprint;
}	t_sway;

typedef struct s_weapon
{
	t_wpn_id	id;
	t_state		state;
	t_anim		anim;
	t_sway		sway;
	t_f32		timer;
	t_f32		bob;
	t_f32		recoil;
	bool		ready;
}	t_weapon;

void		weapon_init(t_weapon *wpn, t_wpn_id id, t_game *game);
t_i32		weapon_get_frame(t_weapon *wpn, t_game *game);
t_wpndef	*weapon_get_def(t_game *game, t_wpn_id id);

void		weapon_fire(t_weapon *wpn, t_game *game);
void		weapon_reload(t_weapon *wpn, t_game *game);

void		weapon_update(t_weapon *wpn, t_game *game, t_f32 dt);

void		weapon_set_state(t_weapon *wpn, t_state state, t_game *game);
bool		weapon_can_fire(t_weapon *wpn, t_game *game);
bool		weapon_can_reload(t_weapon *wpn, t_game *game);

void		weapon_sway_update(t_sway *sway, t_motion *motion, t_f32 dt);
void		weapon_inertia_update(t_sway *sway, t_vec2 mouse_delta, t_f32 dt);
void		weapon_bob_update(t_weapon *wpn, t_motion *motion, t_f32 dt);

void		weapon_fire_all_pellets(t_game *game, t_wpndef *def);
t_vec2		sprint_get_offset(t_sway *sway, t_bob *bob);

#endif
