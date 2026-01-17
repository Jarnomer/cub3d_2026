/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by jmertane         ###   ########.fr       */
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

void	game_init(t_game *game, t_map *map)
{
	safe_mlx_init(game);
	render_init(game);
	time_init(&game->time);
	input_init(&game->input);
	input_mouse_init(game);
	lookup_init(&game->lookup);
	assets_init(&game->assets, game->map);
	particle_init(&game->emitter, DEFAULT_POOL_SIZE);
	decal_init(&game->decals, DEFAULT_POOL_SIZE);
	arena_init(&game->arena, FRAME_ARENA_SIZE);
	darray_init(&game->entities, sizeof(t_entity), 32);
	grid_init(&game->grid, map->width, map->height);
	camera_init(game, BASE_FOV);
	player_init(&game->player, game);
	entity_load_spawns(game);
	grid_cell_fill(game);
	game->running = true;
	rand_seed((t_u32)time(NULL));
	mlx_close_hook(game->mlx, handle_close, game);
}

void	game_destroy(t_game *game)
{
	assets_destroy(&game->assets);
	render_destroy(&game->render);
	particle_destroy(&game->emitter);
	if (game->mlx)
		mlx_terminate(game->mlx);
	darray_destroy(&game->entities);
	decal_destroy(&game->decals);
	arena_destroy(&game->arena);
	grid_destroy(&game->grid);
	map_destroy(game->map);
}

static void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	input_update(game);
	time_update(&game->time, game->mlx->delta_time);
	if (input_key_pressed(&game->input, MLX_KEY_ESCAPE))
		return ((void)mlx_close_window(game->mlx));
	player_update(game, game->time.delta);
	weapon_update(&game->player.weapon, game, game->time.delta);
	motion_update(&game->player.motion, game->time.delta);
	entity_update_all(game, game->time.delta);
	particle_update_all(&game->emitter, game->time.delta);
	anim_update_entities(game, game->time.delta);
	overlay_clear(&game->render);
	arena_reset(&game->arena);
	render_floor(game);
	render_walls(game);
	render_sprites(game);
	render_weapon(game);
	render_particles(game);
}

void	game_run(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
