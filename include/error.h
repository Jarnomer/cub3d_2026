/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define C_RESET		"\033[0m"
# define C_RED			"\033[31m"
# define C_GREEN		"\033[32m"
# define C_YELLOW		"\033[33m"
# define C_BLUE			"\033[34m"
# define C_BOLD_RED		"\033[1;31m"
# define C_BOLD_GREEN	"\033[1;32m"
# define C_BOLD_YELLOW	"\033[1;33m"

# define ERR_PREFIX		"Error\ncub3D: "
# define ERR_USAGE		"Usage: ./cub3D <map.cub>"

# define MSG_FILE_OPEN	"Cannot open file"
# define MSG_FILE_READ	"Cannot read file"
# define MSG_FILE_EXT	"Invalid file extension"
# define MSG_FILE_NAME	"Invalid filename"
# define MSG_FILE_EMPTY	"File is empty"
# define MSG_FILE_DIR	"Is a directory"

# define MSG_ELEM_MISS	"Missing element"
# define MSG_ELEM_DUP	"Duplicate element"
# define MSG_ELEM_ID	"Invalid identifier"
# define MSG_ELEM_VAL	"Invalid element value"

# define MSG_COLOR_FMT	"Invalid color format"
# define MSG_COLOR_VAL	"Color value out of range"
# define MSG_COLOR_SEP	"Invalid color separator"
# define MSG_COLOR_CNT	"Invalid amount of color values"

# define MSG_MAP_MISS	"Missing map"
# define MSG_MAP_SIZE	"Invalid map dimensions"
# define MSG_MAP_BLANK	"Map contains empty lines"
# define MSG_MAP_WALL	"Map is not enclosed by walls"
# define MSG_MAP_PLAYER	"Invalid player count"
# define MSG_MAP_CHAR	"Invalid map character"

# define MSG_MALLOC		"Memory allocation failed"
# define MSG_MLX		"MLX42 error"
# define MSG_THREAD		"Thread creation failed"

typedef enum e_err
{
	ERR_NONE,
	ERR_ARGS,
	ERR_FILE,
	ERR_PARSE,
	ERR_MAP,
	ERR_TEXTURE,
	ERR_INVALID,
	ERR_MALLOC,
	ERR_MLX,
	ERR_THREAD
}	t_err;

void	err_exit_msg(const char *msg);
void	err_exit_context(const char *context, const char *msg);
void	err_exit_errno(const char *context);
void	err_exit_mlx(void);

void	err_print_msg(const char *msg);
void	err_print_context(const char *context, const char *msg);

#endif
