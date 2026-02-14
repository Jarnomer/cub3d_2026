/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	input_mouse_center(t_game *game)
{
	t_vec2i	center;

	if (!game->input.mouse_captured)
		return ;
	center.x = game->render.width / 2;
	center.y = game->render.height / 2;
	mlx_set_mouse_pos(game->mlx, center.x, center.y);
	game->input.mouse_pos.x = (t_f32)center.x;
	game->input.mouse_pos.y = (t_f32)center.y;
}

static void	input_mouse_capture(t_game *game)
{
	if (game->input.mouse_captured)
		return ;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	game->input.mouse_captured = true;
	input_mouse_center(game);
	game->input.mouse_delta = vec2_zero();
}

static void	cursor_callback(double x, double y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->input.mouse_pos.x = (t_f32)x;
	game->input.mouse_pos.y = (t_f32)y;
}

void	input_mouse_init(t_game *game)
{
	t_vec2i	pos;

	mlx_get_mouse_pos(game->mlx, &pos.x, &pos.y);
	game->input.mouse_pos.x = (t_f32)pos.x;
	game->input.mouse_pos.y = (t_f32)pos.y;
	game->input.mouse_captured = false;
	mlx_cursor_hook(game->mlx, cursor_callback, game);
	input_mouse_capture(game);
}

void	input_mouse_update(t_game *game)
{
	t_vec2	center;

	if (!game->input.mouse_captured)
	{
		game->input.mouse_delta = vec2_zero();
		return ;
	}
	center.x = (t_f32)(game->render.width / 2);
	center.y = (t_f32)(game->render.height / 2);
	game->input.mouse_delta = vec2_sub(game->input.mouse_pos, center);
	input_mouse_center(game);
}
