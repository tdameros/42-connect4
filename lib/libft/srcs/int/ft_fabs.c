/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:11:52 by ibertran          #+#    #+#             */
/*   Updated: 2024/01/31 02:01:30 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

float	ft_fabs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}
