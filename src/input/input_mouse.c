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

void	input_mouse_capture(t_game *game)
{
	if (game->input.mouse_captured)
		return ;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	game->input.mouse_captured = true;
	input_mouse_center(game);
	game->input.mouse_delta = vec2_zero();
}

void	input_mouse_release(t_game *game)
{
	if (!game->input.mouse_captured)
		return ;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	game->input.mouse_captured = false;
}

void	input_mouse_center(t_game *game)
{
	t_i32	center_x;
	t_i32	center_y;

	if (!game->input.mouse_captured)
		return ;
	center_x = game->render.width / 2;
	center_y = game->render.height / 2;
	mlx_set_mouse_pos(game->mlx, center_x, center_y);
	game->input.mouse_pos.x = (t_f32)center_x;
	game->input.mouse_pos.y = (t_f32)center_y;
}
