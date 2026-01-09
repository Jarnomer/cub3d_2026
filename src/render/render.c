/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	render_init(t_game *game)
{
	game->render.width = WIN_WIDTH;
	game->render.height = WIN_HEIGHT;
	game->render.z_buffer = safe_calloc(sizeof(t_f32) * WIN_WIDTH);
	game->render.occlude = safe_calloc(sizeof(t_occlude) * WIN_WIDTH);
	game->render.frame = safe_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->render.overlay = safe_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	safe_image_to_window(game->mlx, game->render.frame, 0, 0);
	safe_image_to_window(game->mlx, game->render.overlay, 0, 0);
}

void	render_destroy(t_render *render)
{
	if (!render)
		return ;
	free(render->z_buffer);
	free(render->occlude);
	*render = (t_render){0};
}

void	render_pixel(t_mlxi *img, t_i32 x, t_i32 y, t_u32 color)
{
	((t_u32 *)img->pixels)[y * img->width + x] = color;
}

void	render_pixel_safe(t_mlxi *img, t_i32 x, t_i32 y, t_u32 color)
{
	if (x < 0 || x >= (t_i32)img->width)
		return ;
	if (y < 0 || y >= (t_i32)img->height)
		return ;
	((t_u32 *)img->pixels)[y * img->width + x] = color;
}
