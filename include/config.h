/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <defs.h>

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_assets	t_assets;
typedef struct s_entdef	t_entdef;
typedef struct s_anidef	t_anidef;
typedef struct s_wpndef	t_wpndef;

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

# define FOV_DEFAULT			66.0f
# define RAY_MAX_DIST			64.0f
# define ALPHA_THRESHOLD		128
# define ALPHA_OPAQUE			250
# define MAX_ENTITIES			128
# define THREAD_COUNT			8
# define SKYBOX_ENABLED			0
# define FLASH_DURATION			0.05f
# define FLASH_MAX_ALPHA		80.0f
# define FLASH_COLOR_MUZZLE		0x00FFAA44

/* ************************************************************************** */
/*    PHYSICS SETTINGS                                                        */
/* ************************************************************************** */

# define MAX_DELTA				0.1f
# define GRAVITY				12.0f

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
# define AMMO_MAX_EXP		25

# define AMMO_START_SHELL		12
# define AMMO_START_BULLET		50
# define AMMO_START_CELL		0
# define AMMO_START_EXP	0

/* ************************************************************************** */
/*    WEAPON SETTINGS                                                         */
/* ************************************************************************** */

# define WEAPON_BOB_SPEED		8.0f
# define WEAPON_BOB_AMOUNT		4.0f
# define WEAPON_SWAY_AMOUNT		0.002f
# define WEAPON_SWAY_SMOOTH		0.1f
# define WEAPON_RECOIL_MAX		8.0f
# define WEAPON_RECOIL_DECAY	12.0f

# define WEAPON_OFFSET_X		125
# define WEAPON_OFFSET_Y		0
# define WEAPON_SCALE			3.0f

/* ************************************************************************** */
/*    GAMEPLAY SETTINGS                                                       */
/* ************************************************************************** */

# define INTERACT_RANGE			1.5f
# define DOOR_TIMER				3.0f
# define DOOR_AUTO_CLOSE		1

# define MOVE_ACCEL				12.0f
# define MOVE_DECEL				8.0f
# define MOVE_FRICTION			6.0f

# define JUMP_VELOCITY			4.0f
# define JUMP_SPEED_MULT		0.8f
# define JUMP_STAMINA_COST		15.0f

# define CROUCH_HEIGHT			0.3f
# define CROUCH_SPEED_MULT		0.5f
# define CROUCH_LERP_SPEED		8.0f

# define STAMINA_MAX			100.0f
# define STAMINA_REGEN			20.0f

/* ************************************************************************** */
/*    EFFECT SETTINGS                                                         */
/* ************************************************************************** */

# define HEAD_BOB_SPEED			10.0f
# define HEAD_BOB_AMOUNT		0.015f
# define BOB_LERP				10.0f

# define IDLE_SPEED				1.5f
# define IDLE_AMOUNT			0.003f
# define WEAPON_IDLE_AMOUNT		2.0f

# define SHAKE_DECAY			0.9f
# define SHAKE_FIRE_INTENSITY	3.0f
# define SHAKE_FIRE_DURATION	0.1f
# define SHAKE_DAMAGE_INTENSITY	8.0f
# define SHAKE_DAMAGE_DURATION	0.2f

/* ************************************************************************** */
/*    INPUT SETTINGS                                                          */
/* ************************************************************************** */

# define KEY_INTERACT			MLX_KEY_E
# define KEY_RELOAD				MLX_KEY_R
# define KEY_JUMP				MLX_KEY_SPACE
# define KEY_CROUCH				MLX_KEY_LEFT_CONTROL
# define KEY_FIRE				MLX_MOUSE_BUTTON_LEFT
# define MAX_KEYS				512
# define MAX_MOUSE_KEYS			8

/* ************************************************************************** */
/*    POOL SETTINGS                                                           */
/* ************************************************************************** */

# define DARRAY_INITIAL_CAP		8
# define DARRAY_GROWTH_FACTOR	2
# define ARENA_ALIGNMENT		8
# define FRAME_ARENA_SIZE		65536

/* ************************************************************************** */
/*    FOG SETTINGS                                                            */
/* ************************************************************************** */

# define FOG_ENABLED			1
# define FOG_START				1.2f
# define FOG_END				15.0f
# define FOG_INTENSITY			2.0f
# define FOG_COLOR_R			0
# define FOG_COLOR_G			0
# define FOG_COLOR_B			0

/* ************************************************************************** */
/*    CONFIG FILE SETTINGS                                                    */
/* ************************************************************************** */

# define TEXDEF_FIELD_COUNT		3
# define SHTDEF_FIELD_COUNT		4
# define ENTDEF_FIELD_COUNT		6
# define ANIDEF_FIELD_COUNT		7
# define WPNDEF_FIELD_COUNT		10

# define PATH_CONFIG_TEXTURE	"config/texture.def"
# define PATH_CONFIG_ENTITY		"config/entity.def"
# define PATH_CONFIG_SHEET		"config/sheet.def"
# define PATH_CONFIG_ANIM		"config/anim.def"
# define PATH_CONFIG_WEAPON		"config/weapon.def"

/* ************************************************************************** */
/*    CONFIG FUNCTIONS                                                        */
/* ************************************************************************** */

void		config_load_all(t_assets *assets);

void		config_load_textures(t_assets *assets);
void		config_load_sprites(t_assets *assets);
void		config_load_sheets(t_assets *assets);
void		config_load_entities(t_entdef *defs);
void		config_load_anims(t_anidef *defs);
void		config_load_weapons(t_wpndef *defs);

t_tex_id	str_to_tex_id(const char *str);
t_spr_id	str_to_spr_id(const char *str);
t_sht_id	str_to_sht_id(const char *str);
t_anim_id	str_to_anim_id(const char *str);

#endif
