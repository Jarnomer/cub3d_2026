/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	err_exit_msg(const char *msg)
{
	err_print_msg(msg);
	exit(EXIT_FAILURE);
}

void	err_exit_context(const char *context, const char *msg)
{
	err_print_context(context, msg);
	exit(EXIT_FAILURE);
}

void	err_exit_errno(const char *context)
{
	err_print_context(context, strerror(errno));
	exit(EXIT_FAILURE);
}

void	err_exit_mlx(void)
{
	err_print_context(MSG_MLX, mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
