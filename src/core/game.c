/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	handle_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->running = false;
	mlx_close_window(game->mlx);
}

void	game_init(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, WIN_RESIZABLE);
	if (!game->mlx)
		err_exit_mlx();
	render_init(game);
	input_init(&game->input);
	time_init(&game->time);
	camera_init(&game->camera, game->map->spawn_pos,
		game->map->spawn_angle, FOV_DEFAULT);
	game->running = true;
	mlx_close_hook(game->mlx, handle_close, game);
}

void	game_destroy(t_game *game)
{
	map_destroy(game->map);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	time_update(&game->time);
	input_update(game);
	if (input_key_pressed(&game->input, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		return ;
	}
	player_update(game, game->time.delta);
	render_background(game);
	raycast(game);
}

void	game_run(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
