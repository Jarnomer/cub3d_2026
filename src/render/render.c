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

/*
** Initializes render context with framebuffer and per-column buffers
**
** Allocates:
**   - frame:    MLX image for pixel output
**   - z_buffer: Depth values per column (wall occlusion)
**   - occlude:  Door data per column (sheet occlusion)
*/

void	render_init(t_game *game)
{
	game->render.width = WIN_WIDTH;
	game->render.height = WIN_HEIGHT;
	game->render.frame = safe_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->render.z_buffer = safe_calloc(sizeof(t_f32) * WIN_WIDTH);
	game->render.occlude = safe_calloc(sizeof(t_occlude) * WIN_WIDTH);
	safe_image_to_window(game->mlx, game->render.frame, 0, 0);
}

/*
** Cleans up render context resources
*/

void	render_destroy(t_render *render)
{
	if (!render)
		return ;
	free(render->z_buffer);
	free(render->occlude);
	*render = (t_render){0};
}

/*
** Writes a pixel to the framebuffer
**
** Direct buffer access for performance (no bounds checking)
** Caller must ensure x,y are within bounds
*/

void	render_pixel(t_mlxi *img, t_i32 x, t_i32 y, t_u32 color)
{
	((t_u32 *)img->pixels)[y * img->width + x] = color;
}
