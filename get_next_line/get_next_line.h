/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MKRAForce <MKRAForce@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 09:34:34 by bpancar           #+#    #+#             */
/*   Updated: 2025/10/30 17:24:12 by MKRAForce        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef    BUFFER_SIZE
#  define   BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include "../libft/libft.h"

void	ft_bzero(void *str, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif