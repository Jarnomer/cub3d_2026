/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

# include <MLX42.h>
# include <libft.h>

# include <settings.h>
# include <config.h>
# include <parse.h>
# include <input.h>
# include <assets.h>
# include <entity.h>
# include <player.h>
# include <weapon.h>
# include <motion.h>
# include <anim.h>
# include <render.h>
# include <blit.h>
# include <particle.h>
# include <decal.h>
# include <grid.h>
# include <pool.h>
# include <lookup.h>
# include <error.h>
# include <utils.h>
# include <vector.h>
# include <calc.h>
# include <types.h>
# include <defs.h>

typedef struct s_spawn
{
	t_vec3	pos;
	t_type	type;
}	t_spawn;

typedef struct s_map
{
	char	**grid;
	t_i32	width;
	t_i32	height;
	t_u32	players;
	t_vec2	position;
	t_f32	angle;
	t_spawn	spawns[MAX_ENTITIES];
	t_u32	entities;
	char	*textures[4];
	t_u32	ceiling;
	t_u32	floor;
}	t_map;

typedef struct s_time
{
	t_f64	current;
	t_f64	delta;
	t_f32	fps;
	t_f32	accumulator;
	t_u64	frames;
	t_u32	samples;
}	t_time;

typedef struct s_camera
{
	t_vec2	pos;
	t_f32	angle;
	t_f32	pitch;
	t_f32	fov;
	t_vec2	dir;
	t_vec2	plane;
}	t_camera;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_input		input;
	t_time		time;
	t_camera	camera;
	t_render	render;
	t_assets	assets;
	t_player	player;
	t_darray	entities;
	t_prtclmgr	particles;
	t_decalmgr	decals;
	t_grid		grid;
	t_arena		arena;
	t_lookup	lookup;
	bool		running;
}	t_game;

void	game_init(t_game *game, t_map *map);
void	game_destroy(t_game *game);
void	game_run(t_game *game);

void	time_init(t_time *time);
void	time_update(t_time *time, t_f32 dt);

void	camera_init(t_game *game, t_f32 fov);
void	camera_update(t_game *game);

#endif
