/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	err_print_msg(const char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s%s%s\n",
		C_BOLD_RED, ERR_PREFIX, C_YELLOW, msg, C_RESET);
}

void	err_print_context(const char *context, const char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s%s: %s%s\n",
		C_BOLD_RED, ERR_PREFIX, C_YELLOW, context, msg, C_RESET);
}
