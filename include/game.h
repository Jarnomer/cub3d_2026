/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <cub3d.h>
# include <types.h>

typedef struct s_game	t_game;

typedef struct s_map
{
	char	**grid;
	t_i32	width;
	t_i32	height;
	t_vec2	spawn_pos;
	t_f32	spawn_angle;
	char	*tex_paths[4];
	t_color	floor;
	t_color	ceiling;
}	t_map;

typedef struct s_input
{
	bool	keys[MAX_KEYS];
	bool	keys_prev[MAX_KEYS];
	t_vec2	mouse_pos;
	t_vec2	mouse_delta;
	bool	mouse_captured;
}	t_input;

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

typedef struct s_camera
{
	t_vec2	pos;
	t_f32	angle;
	t_f32	pitch;
	t_f32	fov;
	t_vec2	dir;
	t_vec2	plane;
}	t_camera;

typedef struct s_render
{
	mlx_image_t	*frame;
	t_i32		width;
	t_i32		height;
}	t_render;

struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_input		input;
	t_time		time;
	t_camera	camera;
	t_render	render;
	bool		running;
};

void	game_init(t_game *game);
void	game_destroy(t_game *game);
void	game_run(t_game *game);

void	game_loop(void *param);

void	player_update(t_game *game, t_f32 dt);

void	input_init(t_input *input);
void	input_update(t_game *game);
bool	input_key_down(t_input *input, int key);
bool	input_key_pressed(t_input *input, int key);
bool	input_key_released(t_input *input, int key);

void	time_init(t_time *time);
void	time_update(t_time *time);
t_f64	time_get_seconds(void);

void	camera_init(t_camera *cam, t_vec2 pos, t_f32 angle, t_f32 fov);
void	camera_update(t_camera *cam);

void	render_init(t_game *game);
void	render_vline(t_game *game, int x, int *y, t_color c);
void	render_background(t_game *game);

void	raycast(t_game *game);

void	map_destroy(t_map *map);
bool	map_is_wall(t_map *map, t_i32 x, t_i32 y);

#endif
