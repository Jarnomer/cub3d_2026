/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_sprite_ctx(t_thd *thd, t_game *game, t_proj *projs, t_u32 cnt)
{
	t_i32	cols_per_thread;
	t_i32	i;

	cols_per_thread = game->render.width / THREAD_COUNT;
	i = 0;
	while (i < THREAD_COUNT)
	{
		thd[i] = (t_thd){.game = game, .projs = projs, .id = i, .count = cnt};
		thd[i].start = i * cols_per_thread;
		if (i == THREAD_COUNT - 1)
			thd[i].end = game->render.width;
		else
			thd[i].end = (i + 1) * cols_per_thread;
		i++;
	}
}

static void	*sprite_worker(void *arg)
{
	t_thd	*thd;
	t_i32	x;
	t_u32	i;

	thd = (t_thd *)arg;
	i = 0;
	while (i < thd->count)
	{
		x = maxi(thd->projs[i].start.x, thd->start);
		while (x < thd->projs[i].end.x && x < thd->end)
		{
			if (zbuf_test(&thd->game->render, x, thd->projs[i].dist))
			{
				if (thd->projs[i].use_sheet)
					render_sheet_column(thd->game, &thd->projs[i], x);
				else
					render_sprite_column(thd->game, &thd->projs[i], x);
			}
			x++;
		}
		i++;
	}
	return (NULL);
}

static void	thread_sprites(t_game *game, t_proj *projs, t_u32 count)
{
	pthread_t	threads[THREAD_COUNT];
	t_thd		thd[THREAD_COUNT];
	int			err;
	t_i32		i;

	init_sprite_ctx(thd, game, projs, count);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, sprite_worker, &thd[i]);
		if (err != 0)
			err_exit_context(MSG_THREAD, strerror(err));
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	render_sprites(t_game *game)
{
	t_proj	*projs;
	t_u32	count;

	if (game->entities.size == 0)
		return ;
	projs = arena_alloc(&game->arena, sizeof(t_proj) * game->entities.size);
	if (!projs)
		return ;
	count = sprites_collect(game, projs);
	if (count == 0)
		return ;
	sprites_sort(projs, count);
	thread_sprites(game, projs, count);
}
