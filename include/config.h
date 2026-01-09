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

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_assets	t_assets;
typedef struct s_entdef	t_entdef;
typedef struct s_anidef	t_anidef;

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

# define FOV_DEFAULT		66.0f
# define RAY_MAX_DIST		64.0f
# define ALPHA_THRESHOLD	128
# define ALPHA_OPAQUE		250
# define MAX_ENTITIES		128
# define THREAD_COUNT		8
# define SKYBOX_ENABLED		0

/* ************************************************************************** */
/*    PHYSICS SETTINGS                                                        */
/* ************************************************************************** */

# define MAX_DELTA		0.1f

/* ************************************************************************** */
/*    GAMEPLAY SETTINGS                                                       */
/* ************************************************************************** */

# define INTERACT_RANGE		1.5f
# define DOOR_TIMER			3.0f
# define DOOR_AUTO_CLOSE	1

/* ************************************************************************** */
/*    CAMERA SETTINGS                                                         */
/* ************************************************************************** */

# define CAMERA_HEIGHT	0.5f
# define CAM_X_SCALE	2.0f

/* ************************************************************************** */
/*    PLAYER SETTINGS                                                         */
/* ************************************************************************** */

# define PLAYER_SPEED		4.0f
# define PLAYER_LOOK_SPEED	2.0f
# define PLAYER_MOUSE_SENS	0.001f
# define PLAYER_MAX_PITCH	1.2f
# define PLAYER_RADIUS		0.2f

/* ************************************************************************** */
/*    INPUT SETTINGS                                                          */
/* ************************************************************************** */

# define INTERACT_KEY	MLX_KEY_E
# define MAX_KEYS		512

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

# define FOG_ENABLED	1
# define FOG_START		1.2f
# define FOG_END		15.0f
# define FOG_INTENSITY	2.0f
# define FOG_COLOR_R	0
# define FOG_COLOR_G	0
# define FOG_COLOR_B	0

/* ************************************************************************** */
/*    CONFIG FILE SETTINGS                                                    */
/* ************************************************************************** */

# define TEXDEF_FIELD_COUNT		3
# define SHTDEF_FIELD_COUNT		4
# define ENTDEF_FIELD_COUNT		6
# define ANIDEF_FIELD_COUNT	    7
# define WPNDEF_FIELD_COUNT		8
# define ENEDEF_FIELD_COUNT		10

# define PATH_CONFIG_TEXTURE	"config/texture.def"
# define PATH_CONFIG_ENTITY		"config/entity.def"
# define PATH_CONFIG_SHEET		"config/sheet.def"
# define PATH_CONFIG_ANIM		"config/anim.def"
# define PATH_CONFIG_WEAPON		"config/weapon.def"
# define PATH_CONFIG_ENEMY		"config/enemy.def"

/* ************************************************************************** */
/*    CONFIG FUNCTIONS                                                        */
/* ************************************************************************** */

void	config_load_all(t_assets *assets);
void	config_load_textures(t_assets *assets);
void	config_load_sprites(t_assets *assets);
void	config_load_entities(t_entdef *defs);
void	config_load_sheets(t_assets *assets);
void	config_load_anims(t_anidef *defs);

#endif
