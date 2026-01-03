/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
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

# include <types.h>
# include <vector.h>
# include <calc.h>
# include <error.h>
# include <pool.h>
# include <config.h>
# include <parse.h>

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_game	t_game;

/* ************************************************************************** */
/*    INPUT                                                                   */
/* ************************************************************************** */

typedef struct s_input
{
	bool	keys[MAX_KEYS];
	bool	keys_prev[MAX_KEYS];
	t_vec2	mouse_pos;
	t_vec2	mouse_delta;
	bool	mouse_captured;
}	t_input;

/* ************************************************************************** */
/*    TIME                                                                    */
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
/*    CAMERA                                                                  */
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
/*    RENDER                                                                  */
/* ************************************************************************** */

typedef struct s_render
{
	mlx_image_t	*frame;
	t_i32		width;
	t_i32		height;
}	t_render;

/* ************************************************************************** */
/*    RAY                                                                     */
/* ************************************************************************** */

typedef struct s_ray
{
	t_vec2	dir;
	t_vec2	delta;
	t_vec2	axis;
	t_vec2i	pos;
	t_vec2i	step;
	t_f32	perp_dist;
	t_axis	side;
	bool	hit;
}	t_ray;

/* ************************************************************************** */
/*    GAME                                                                    */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*    GAME FUNCTIONS                                                          */
/* ************************************************************************** */

void			game_init(t_game *game);
void			game_destroy(t_game *game);
void			game_run(t_game *game);
void			game_loop(void *param);

/* ************************************************************************** */
/*    PLAYER FUNCTIONS                                                        */
/* ************************************************************************** */

void			player_update(t_game *game, t_f32 dt);

/* ************************************************************************** */
/*    INPUT FUNCTIONS                                                         */
/* ************************************************************************** */

void			input_init(t_input *input);
void			input_update(t_game *game);
bool			input_key_down(t_input *input, int key);
bool			input_key_pressed(t_input *input, int key);
bool			input_key_released(t_input *input, int key);

/* ************************************************************************** */
/*    TIME FUNCTIONS                                                          */
/* ************************************************************************** */

void			time_init(t_time *time);
void			time_update(t_time *time);
t_f64			time_get_seconds(void);

/* ************************************************************************** */
/*    CAMERA FUNCTIONS                                                        */
/* ************************************************************************** */

void			camera_init(t_camera *cam, t_vec2 pos, t_f32 angle, t_f32 fov);
void			camera_update(t_camera *cam);

/* ************************************************************************** */
/*    RENDER FUNCTIONS                                                        */
/* ************************************************************************** */

void			render_init(t_game *game);
void			render_vline(t_game *game, int x, int *y, t_color c);
void			render_background(t_game *game);

/* ************************************************************************** */
/*    RAYCAST FUNCTIONS                                                       */
/* ************************************************************************** */

void			raycast(t_game *game);

/* ************************************************************************** */
/*    MAP FUNCTIONS                                                           */
/* ************************************************************************** */

void			map_destroy(t_map *map);
bool			map_is_wall(t_map *map, t_i32 x, t_i32 y);

/* ************************************************************************** */
/*    SAFE WRAPPER FUNCTIONS                                                  */
/* ************************************************************************** */

void			*safe_calloc(size_t size);
char			*safe_strjoin(char *s1, char *s2);
char			*safe_strdup(char *s1);
char			**safe_split(char *str, char c);

void			safe_image_to_window(mlx_t *mlx,
					mlx_image_t *img, t_i32 x, t_i32 y);
mlx_image_t		*safe_image(mlx_t *mlx, t_u32 w, t_u32 h);
mlx_texture_t	*safe_load_png(const char *path);

#endif
