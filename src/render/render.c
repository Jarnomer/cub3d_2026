/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	render_init(t_game *game)
{
	game->render.width = WIN_WIDTH;
	game->render.height = WIN_HEIGHT;
	game->render.frame = safe_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	safe_image_to_window(game->mlx, game->render.frame, 0, 0);
}

void	render_destroy(t_render *render)
{
	if (!render)
		return ;
	ft_bzero(render, sizeof(t_render));
}

void	render_pixel(t_mimg *img, t_i32 x, t_i32 y, t_color c)
{
	t_u32	color;

	if (x < 0 || x >= (t_i32)img->width)
		return ;
	if (y < 0 || y >= (t_i32)img->height)
		return ;
	color = color_to_u32(c);
	mlx_put_pixel(img, x, y, color);
}
