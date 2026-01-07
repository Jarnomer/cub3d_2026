/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

/* ************************************************************************** */
/*    STANDARD LIBRARY                                                        */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

/* ************************************************************************** */
/*    EXTERNAL LIBRARIES                                                      */
/* ************************************************************************** */

# include <MLX42.h>
# include <libft.h>

/* ************************************************************************** */
/*    PROJECT HEADERS                                                         */
/* ************************************************************************** */

# include <parse.h>
# include <input.h>
# include <config.h>
# include <assets.h>
# include <entity.h>
# include <render.h>
# include <sprite.h>
# include <thread.h>
# include <anim.h>
# include <pool.h>
# include <calc.h>
# include <vector.h>
# include <lookup.h>
# include <error.h>
# include <utils.h>
# include <types.h>
# include <defs.h>

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_game	t_game;

/* ************************************************************************** */
/*    SPAWN STRUCTURE                                                         */
/* ************************************************************************** */

typedef struct s_spawn
{
	t_vec2	pos;
	t_type	type;
}	t_spawn;

/* ************************************************************************** */
/*    MAP STRUCTURE                                                           */
/* ************************************************************************** */

typedef struct s_map
{
	char	**grid;
	t_i32	width;
	t_i32	height;
	t_vec2	spawn_pos;
	t_f32	spawn_angle;
	char	*textures[4];
	t_u32	floor_col;
	t_u32	ceil_col;
	t_spawn	spawns[MAX_ENTITIES];
	t_u32	spawn_count;
	t_u32	player_count;
}	t_map;

/* ************************************************************************** */
/*    TIME STRUCTURE                                                          */
/* ************************************************************************** */

typedef struct s_time
{
	t_f64	current;
	t_f64	previous;
	t_f64	delta;
	t_u64	frame_count;
	t_f32	fps;
	t_f32	fps_timer;
	t_u32	fps_frames;
}	t_time;

/* ************************************************************************** */
/*    CAMERA STRUCTURE                                                        */
/* ************************************************************************** */

typedef struct s_camera
{
	t_vec2	pos;
	t_f32	angle;
	t_f32	pitch;
	t_f32	fov;
	t_vec2	dir;
	t_vec2	plane;
}	t_camera;

/* ************************************************************************** */
/*    MAIN GAME STRUCTURE                                                     */
/* ************************************************************************** */

struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_input		input;
	t_time		time;
	t_camera	camera;
	t_render	render;
	t_assets	assets;
	t_darray	entities;
	t_arena		arena;
	t_lookup	lookup;
	bool		running;
};

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function details
*/

void	game_init(t_game *game);
void	game_destroy(t_game *game);
void	game_run(t_game *game);
void	game_loop(void *param);

void	player_update(t_game *game, t_f32 dt);

void	time_init(t_time *time);
void	time_update(t_time *time);
t_f64	time_get_seconds(void);

void	camera_init(t_camera *cam, t_vec2 pos, t_f32 angle, t_f32 fov);
void	camera_update(t_camera *cam);

#endif
