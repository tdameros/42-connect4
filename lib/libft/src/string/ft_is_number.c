/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:07:14 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/12 17:01:23 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_number(char *s)
{
	int	is_number;

	is_number = 0;
	if (*s == '-' || *s == '+')
		s++;
	while (*s != '\0')
	{
		if (!ft_isdigit(*s))
			return (0);
		is_number = 1;
		s++;
	}
	return (is_number);
}
