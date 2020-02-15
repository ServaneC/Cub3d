/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:33:33 by schene            #+#    #+#             */
/*   Updated: 2020/02/12 12:05:57 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		++i;
	}
	return (0);
}

static int		is_word(char c, char cbefore, char *charset)
{
	return (!(is_sep(c, charset)) && is_sep(cbefore, charset));
}

static int		ft_nbwords(char *str, char *charset)
{
	int	i;
	int	nbwords;

	i = 0;
	nbwords = 0;
	while (str[i])
	{
		if (is_word(str[i], str[i - 1], charset) ||
				(!is_sep(str[i], charset) && i == 0))
			nbwords++;
		i++;
	}
	return (nbwords);
}

static int		*ft_size(char *str, char *charset)
{
	int	i;
	int	j;
	int	nbwords;
	int	*size;

	i = 0;
	nbwords = ft_nbwords(str, charset);
	if (!(size = malloc(sizeof(int) * nbwords)))
		return (0);
	while (i <= nbwords)
	{
		size[i] = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!(is_sep(str[i], charset)))
			size[j]++;
		else if (i > 0 && !is_sep(str[i - 1], charset))
			j++;
		i++;
	}
	return (size);
}

char			**ft_split_s(char *str, char *charset)
{
	char	**tab;
	int		i;
	int		j;
	int		x;
	int		*size;

	tab = malloc(sizeof(char *) * (ft_nbwords(str, charset) + 1));
	size = ft_size(str, charset);
	i = -1;
	j = 0;
	x = 0;
	while (str[++i])
	{
		if (!is_sep(str[i], charset))
		{
			if (i == 0 || is_word(str[i], str[i - 1], charset))
				tab[x] = malloc(sizeof(char) * (size[x] + 1));
			tab[x][j] = str[i];
			tab[x][++j] = '\0';
		}
		else if (i > 0 && !(is_sep(str[i - 1], charset)) && ++x)
			j = 0;
	}
	tab[ft_nbwords(str, charset)] = 0;
	return (tab);
}
