/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		err_exit_msg(ERR_USAGE);
	game = (t_game){0};
	game.map = parse(argv[1]);
	game_init(&game, game.map);
	game_run(&game);
	game_destroy(&game);
	return (EXIT_SUCCESS);
}
