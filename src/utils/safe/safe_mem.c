/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	*safe_calloc(size_t size)
{
	void	*ptr;

	ptr = ft_calloc(1, size);
	if (!ptr)
	{
		perror(ERR_PREFIX);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

char	*safe_strjoin(char *s1, char *s2)
{
	char	*s;

	s = ft_strjoin(s1, s2);
	if (!s)
	{
		perror(ERR_PREFIX);
		exit(EXIT_FAILURE);
	}
	return (s);
}

char	*safe_strdup(char *s1)
{
	char	*s;

	s = ft_strdup(s1);
	if (!s)
	{
		perror(ERR_PREFIX);
		exit(EXIT_FAILURE);
	}
	return (s);
}

char	**safe_split(char *str, char c)
{
	char	**s;

	s = ft_split(str, c);
	if (!s)
	{
		perror(ERR_PREFIX);
		exit(EXIT_FAILURE);
	}
	return (s);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
