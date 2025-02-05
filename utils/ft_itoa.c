/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:47:19 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/02/05 13:09:38 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	calc_len(int n)
{
	int	result;

	result = 0;
	if (n < 0)
	{
		n *= -1;
		result++;
	}
	while (n > 0)
	{
		n /= 10;
		result++;
	}
	return (result);
}

static char	*continue_func(int n)
{
	char	*result;
	char	sign;
	int		len;

	len = calc_len(n);
	sign = 'P';
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	if (n < 0)
	{
		sign = 'N';
		n *= -1;
	}
	while (len-- > 0)
	{
		result[len] = (char)(n % 10 + '0');
		n /= 10;
	}
	if (sign == 'N')
		*result = '-';
	return (result);
}

char	*ft_itoa(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (continue_func(n));
}
