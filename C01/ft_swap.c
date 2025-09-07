/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:12:02 by marvin            #+#    #+#             */
/*   Updated: 2025/09/06 11:12:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_swap(int *a, int *b)
{
    int	temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

#include <stdio.h>
int	main(void)
{
    int	x;
    int	y;

    x = 42;
    y = 21;
    printf("Before swap: x = %d, y = %d\n", x, y);
    ft_swap(&x, &y);
    printf("After swap: x = %d, y = %d\n", x, y);
    return (0);
}
