/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <types.h>
# include <error.h>

/* ************************************************************************** */
/*    WINDOW SETTINGS                                                         */
/* ************************************************************************** */

# define WIN_TITLE		"cub3D"
# define WIN_WIDTH		1280
# define WIN_HEIGHT		720
# define WIN_RESIZABLE	1

/* ************************************************************************** */
/*    RENDERING SETTINGS                                                      */
/* ************************************************************************** */

# define RENDER_SCALE	1
# define FOV_DEFAULT	66.0f
# define FOV_MIN		30.0f
# define FOV_MAX		120.0f
# define Z_NEAR			0.1f
# define Z_FAR			64.0f
# define MAX_RENDER_DIST 32.0f

/* ************************************************************************** */
/*    RAYCAST SETTINGS                                                        */
/* ************************************************************************** */

# define RAY_MAX_DIST	64.0f
# define RAY_STEP_SIZE	0.01f

/* ************************************************************************** */
/*    PHYSICS SETTINGS                                                        */
/* ************************************************************************** */

# define TICK_RATE		60
# define TICK_DELTA		0.01666666666f
# define MAX_DELTA		0.1f
# define GRAVITY		20.0f
# define FRICTION		8.0f

/* ************************************************************************** */
/*    PLAYER SETTINGS                                                         */
/* ************************************************************************** */

# define PLAYER_HEIGHT		0.5f
# define PLAYER_RADIUS		0.25f
# define PLAYER_SPEED		4.0f
# define PLAYER_SPRINT_MUL	1.6f
# define PLAYER_CROUCH_MUL	0.5f
# define PLAYER_CROUCH_H	0.3f
# define PLAYER_JUMP_FORCE	8.0f
# define PLAYER_LOOK_SPEED	2.0f
# define PLAYER_MOUSE_SENS	0.002f
# define PLAYER_MAX_PITCH	1.2f
# define PLAYER_BOB_FREQ	10.0f
# define PLAYER_BOB_AMP		0.02f
# define PLAYER_SWAY_FREQ	5.0f
# define PLAYER_SWAY_AMP	0.01f
# define PLAYER_ACCEL		40.0f
# define PLAYER_DECEL		20.0f

/* ************************************************************************** */
/*    ENEMY SETTINGS                                                          */
/* ************************************************************************** */

# define ENEMY_SIGHT_RANGE	16.0f
# define ENEMY_ATTACK_RANGE	1.5f
# define ENEMY_ALERT_DECAY	0.5f
# define ENEMY_PATROL_RADIUS 4.0f

/* ************************************************************************** */
/*    COMBAT SETTINGS                                                         */
/* ************************************************************************** */

# define DAMAGE_INVULN_TIME	0.5f
# define KNOCKBACK_FORCE	5.0f
# define CRIT_MULTIPLIER	2.0f

/* ************************************************************************** */
/*    HUD SETTINGS                                                            */
/* ************************************************************************** */

# define MINIMAP_SIZE		150
# define MINIMAP_SCALE		8.0f
# define MINIMAP_MARGIN		10
# define CROSSHAIR_SIZE		8
# define CROSSHAIR_GAP		4

/* ************************************************************************** */
/*    PARTICLE SETTINGS                                                       */
/* ************************************************************************** */

# define PARTICLE_MAX		2048
# define PARTICLE_GRAVITY	15.0f

/* ************************************************************************** */
/*    AUDIO SETTINGS                                                          */
/* ************************************************************************** */

# define AUDIO_MASTER_VOL	1.0f
# define AUDIO_MUSIC_VOL	0.7f
# define AUDIO_SFX_VOL		1.0f
# define AUDIO_FALLOFF_DIST	16.0f

/* ************************************************************************** */
/*    THREAD SETTINGS                                                         */
/* ************************************************************************** */

# define THREAD_COUNT		4
# define RAYCAST_THREADS	4

/* ************************************************************************** */
/*    DEBUG SETTINGS                                                          */
/* ************************************************************************** */

# define DEBUG_SHOW_FPS		1
# define DEBUG_SHOW_POS		0
# define DEBUG_SHOW_COLLIDERS 0
# define DEBUG_SHOW_SPATIAL	0
# define DEBUG_SHOW_AI		0

/* ************************************************************************** */
/*    MAP LIMITS                                                              */
/* ************************************************************************** */

# define MAP_MAX_WIDTH		128
# define MAP_MAX_HEIGHT		128
# define MAP_MAX_ENEMIES	64
# define MAP_MAX_PICKUPS	128
# define MAP_MAX_DOORS		32
# define MAP_MAX_LIGHTS		64

/* ************************************************************************** */
/*    FILE PATHS                                                              */
/* ************************************************************************** */

# define PATH_ASSETS		"assets/"
# define PATH_TEXTURES		"assets/textures/"
# define PATH_SPRITES		"assets/sprites/"
# define PATH_SOUNDS		"assets/sounds/"
# define PATH_MAPS			"assets/maps/"
# define PATH_CONFIG		"config/"

/* ************************************************************************** */
/*    RUNTIME CONFIG STRUCTURE                                                */
/* ************************************************************************** */

typedef struct s_settings
{
	t_i32	win_width;
	t_i32	win_height;
	bool	fullscreen;
	t_f32	fov;
	t_f32	mouse_sensitivity;
	t_f32	master_volume;
	t_f32	music_volume;
	t_f32	sfx_volume;
	bool	vsync;
	bool	show_fps;
	t_i32	render_scale;
}	t_settings;

/* ************************************************************************** */
/*    FUNCTIONS                                                               */
/* ************************************************************************** */

t_err	settings_load(t_settings *cfg, const char *path);
t_err	settings_save(t_settings *cfg, const char *path);
void	settings_default(t_settings *cfg);

#endif
