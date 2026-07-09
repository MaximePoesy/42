/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:43:50 by staverni          #+#    #+#             */
/*   Updated: 2025/04/21 15:47:04 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Regular text colors
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define BLUE "\001\033[0;34m\002"
# define MAGENTA "\001\033[0;35m\002"
# define CYAN "\001\033[0;36m\002"
# define WHITE "\001\033[0;37m\002"

// Bright text colors
# define BBLACK "\001\033[1;30m\002"
# define BRED "\001\033[1;31m\002"
# define BGREEN "\001\033[1;32m\002"
# define BYELLOW "\001\033[1;33m\002"
# define BBLUE "\001\033[1;34m\002"
# define BMAGENTA "\001\033[1;35m\002"
# define BCYAN "\001\033[1;36m\002"
# define BWHITE "\001\033[1;37m\002"

// Background colors
# define BG_BLACK "\001\033[40m\002"
# define BG_RED "\001\033[41m\002"
# define BG_GREEN "\001\033[42m\002"
# define BG_YELLOW "\001\033[43m\002"
# define BG_BLUE "\001\033[44m\002"
# define BG_MAGENTA "\001\033[45m\002"
# define BG_CYAN "\001\033[46m\002"
# define BG_WHITE "\001\033[47m\002"

// Styles
# define BOLD "\001\033[1m\002"
# define UNDERLINE "\001\033[4m\002"
# define REVERSED "\001\033[7m\002"
# define STRIKE "\001\033[9m\002"
# define ITALIC "\001\033[3m\002"
# define RESET "\001\033[0m\002"

#endif
