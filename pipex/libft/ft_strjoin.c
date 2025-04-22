/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalien <alvalien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:38:54 by alvalien          #+#    #+#             */
/*   Updated: 2025/04/21 17:08:26 by alvalien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aux;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	aux = (char *) malloc (sizeof(char) * (s1_len + s2_len + 1));
	if (aux == NULL)
		return (NULL);
	while (i < s1_len)
	{
		aux[i] = s1[i];
		i++;
	}
	while (*s2)
		aux[i++] = *s2++;
	aux[i] = '\0';
	return (aux);
}
