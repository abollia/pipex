/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:52:16 by abollia           #+#    #+#             */
/*   Updated: 2025/01/27 10:35:05 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(int c)
{
	if (('0' <= c && c <= '9') || ('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z'))
		return (1);
	else
		return (0);
}
