/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

/* ************************************************************************** */
/*    WINDOW SETTINGS                                                         */
/* ************************************************************************** */

# define WIN_TITLE				"cub3D"
# define WIN_WIDTH				1280
# define WIN_HEIGHT				720
# define WIN_RESIZABLE			1

/* ************************************************************************** */
/*    RENDERING SETTINGS                                                      */
/* ************************************************************************** */

# define BASE_FOV				66.0f
# define RAY_MAX_DIST			64.0f
# define ALPHA_THRESHOLD		128
# define ALPHA_OPAQUE			250
# define MAX_ENTITIES			128
# define THREAD_COUNT			8
# define SKYBOX_ENABLED			0
# define FLASH_DURATION			0.05f
# define FLASH_MAX_ALPHA		80.0f
# define FLASH_COLOR_MUZZLE		0xFFFFFF44

/* ************************************************************************** */
/*    PHYSICS SETTINGS                                                        */
/* ************************************************************************** */

# define MAX_DELTA				0.1f
# define GRAVITY				8.0f

/* ************************************************************************** */
/*    CAMERA SETTINGS                                                         */
/* ************************************************************************** */

# define CAMERA_HEIGHT			0.5f
# define CAM_X_SCALE			2.0f

/* ************************************************************************** */
/*    PLAYER SETTINGS                                                         */
/* ************************************************************************** */

# define PLAYER_SPEED			4.0f
# define PLAYER_LOOK_SPEED		2.0f
# define PLAYER_MOUSE_SENS		0.001f
# define PLAYER_MAX_PITCH		1.2f
# define PLAYER_RADIUS			0.2f

# define PLAYER_MAX_HEALTH		100
# define PLAYER_MAX_ARMOR		100
# define PLAYER_START_HEALTH	100
# define PLAYER_START_ARMOR		0

# define AMMO_MAX_SHELL			50
# define AMMO_MAX_BULLET		200
# define AMMO_MAX_CELL			100
# define AMMO_MAX_EXPLOSIVE		25

# define AMMO_START_SHELL		50
# define AMMO_START_BULLET		200
# define AMMO_START_CELL		0
# define AMMO_START_EXPLOSIVE	0

/* ************************************************************************** */
/*    WEAPON SETTINGS                                                         */
/* ************************************************************************** */

# define WEAPON_RECOIL_MAX		8.0f
# define WEAPON_RECOIL_DECAY	12.0f

# define WEAPON_OFFSET_X		125
# define WEAPON_OFFSET_Y		-130
# define WEAPON_SCALE			3.0f

# define SWAY_IDLE_FREQ			1.5f
# define SWAY_IDLE_AMP_X		5.0f
# define SWAY_IDLE_AMP_Y		3.0f
# define SWAY_MOVE_AMP_X		16.0f
# define SWAY_MOVE_AMP_Y		12.0f
# define SWAY_CROUCH_MULT		0.6f
# define SWAY_LERP_SPEED		10.0f

# define INERTIA_STRENGTH		8.0f
# define INERTIA_MAX_X			100.0f
# define INERTIA_MAX_Y			25.0f
# define INERTIA_VEL_DECAY		15.0f
# define INERTIA_POS_DECAY		15.0f

# define WEAPON_BOB_IDLE_AMP	1.5f
# define WEAPON_BOB_MOVE_AMP	5.0f
# define WEAPON_BOB_CROUCH_MULT	0.6f
# define WEAPON_BOB_LERP		12.0f

# define SPRINT_DROP_Y			20.0f
# define SPRINT_TILT_Y			35.0f
# define SPRINT_SWAY_MULT		1.0f
# define SPRINT_BOB_MULT		2.0f
# define SPRINT_THRUST_AMP		8.0f
# define SPRINT_THRUST_MULT		2.0f
# define SPRINT_LERP			8.0f

/* ************************************************************************** */
/*    GAMEPLAY SETTINGS                                                       */
/* ************************************************************************** */

# define INTERACT_RANGE			1.5f
# define DOOR_TIMER				3.0f
# define DOOR_AUTO_CLOSE		1

# define STAMINA_MAX			100.0f
# define STAMINA_REGEN			20.0f

/* ************************************************************************** */
/*    MOTION SETTINGS                                                         */
/* ************************************************************************** */

# define MOVE_ACCEL				6.0f
# define MOVE_FRICTION			10.0f
# define MOVE_STOP_THRESHOLD    0.01f

# define JUMP_VELOCITY			2.8f
# define JUMP_SPEED_MULT		0.8f
# define JUMP_STAMINA_COST		15.0f

# define CROUCH_HEIGHT			0.3f
# define CROUCH_SPEED_MULT		0.5f
# define CROUCH_LERP_SPEED		8.0f
# define CROUCH_HEIGHT_OFFSET	0.25f
# define CROUCH_THRESHOLD		0.01f

# define SPRINT_SPEED_MULT		1.6f
# define SPRINT_STAMINA_DRAIN	25.0f
# define SPRINT_ALLOW_JUMP		0
# define SPRINT_ALLOW_STRAFE	0

/* ************************************************************************** */
/*    HEAD BOB SETTINGS                                                       */
/* ************************************************************************** */

# define BOB_IDLE_FREQ			0.0f
# define BOB_IDLE_AMP			0.0f
# define BOB_WALK_FREQ			10.0f
# define BOB_WALK_AMP_Y			0.05f
# define BOB_WALK_AMP_X			0.03f
# define BOB_CROUCH_MULT		0.6f
# define BOB_SPRINT_FREQ		14.5f
# define BOB_SPRINT_AMP_Y		0.05f
# define BOB_SPRINT_AMP_X		0.04f
# define BOB_SPRINT_ASYM		0.6f
# define BOB_LERP_SPEED			8.0f

/* ************************************************************************** */
/*    FOV SETTINGS                                                            */
/* ************************************************************************** */

# define FOV_SPRINT_OFFSET		4.0f
# define FOV_LERP_SPEED			6.0f

/* ************************************************************************** */
/*    INPUT SETTINGS                                                          */
/* ************************************************************************** */

# define KEY_INTERACT			MLX_KEY_E
# define KEY_RELOAD				MLX_KEY_R
# define KEY_JUMP				MLX_KEY_SPACE
# define KEY_SPRINT				MLX_KEY_LEFT_SHIFT
# define KEY_CROUCH				MLX_KEY_LEFT_CONTROL
# define KEY_MOUSE_FIRE			MLX_MOUSE_BUTTON_LEFT
# define MAX_KEYS				512
# define MAX_MOUSE_KEYS			8

/* ************************************************************************** */
/*    FOG SETTINGS                                                            */
/* ************************************************************************** */

# define FOG_ENABLED			1
# define FOG_START				1.2f
# define FOG_END				15.0f
# define FOG_INTENSITY			2.5f
# define FOG_START_R			10
# define FOG_START_G			15
# define FOG_START_B			30
# define FOG_END_R				0
# define FOG_END_G				0
# define FOG_END_B				0

/* ************************************************************************** */
/*    PARTICLE SETTINGS                                                       */
/* ************************************************************************** */

# define PARTICLE_POOL_SIZE		256
# define PARTICLE_BASE_SIZE		8.0f
# define PARTICLE_WALL_OFFSET	0.1f
# define PARTICLE_FLOOR_Z		-0.6f
# define PARTICLE_CEILING_Z		0.4f
# define PARTICLE_GRAVITY		9.8f
# define PARTICLE_STOP_VEL		0.1f
# define PARTICLE_FLOOR_FRIC	0.7f
# define PARTICLE_PITCH_SCALE	0.5f

#endif
