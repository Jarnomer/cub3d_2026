/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	check_directory(const char *filepath)
{
	int	fd;

	fd = open(filepath, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		err_exit_context(filepath, MSG_FILE_DIR);
	}
}

static void	check_filename(const char *filepath, const char *ext)
{
	const char	*filename;

	filename = ft_strrchr(filepath, '/');
	if (filename)
		filename++;
	else
		filename = filepath;
	if (*filename == '.')
		err_exit_context(filepath, MSG_FILE_NAME);
	if (ft_strlen(filename) <= ft_strlen(ext))
		err_exit_context(filepath, MSG_FILE_NAME);
}

static void	check_extension(const char *filepath, const char *ext)
{
	size_t	len;
	size_t	ext_len;

	len = ft_strlen(filepath);
	ext_len = ft_strlen(ext);
	if (len <= ext_len)
		err_exit_context(filepath, MSG_FILE_EXT);
	if (ft_strcmp(filepath + len - ext_len, ext) != 0)
		err_exit_context(filepath, MSG_FILE_EXT);
}

void	parse_file_validate(const char *filepath, const char *ext)
{
	check_extension(filepath, ext);
	check_filename(filepath, ext);
	check_directory(filepath);
}

int	parse_file_open(const char *filepath)
{
	char	buf;
	int		fd;

	parse_file_validate(filepath, ".cub");
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		err_exit_errno(filepath);
	if (read(fd, &buf, 1) <= 0)
		err_exit_context(filepath, MSG_FILE_EMPTY);
	close(fd);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		err_exit_errno(filepath);
	return (fd);
}
