/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkim <youkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 13:53:13 by youkim            #+#    #+#             */
/*   Updated: 2021/08/16 21:49:58 by youkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#define LOG printf("%02d:%c %c%c%c (x%d)\n",\
	(int)i, s[i],\
	flag & INQ ? '"':'.',\
	flag & INW ? 'w':'.',\
	flag & FW  ? 'f':'.',\
	(int)num);
// #define LOG printf("%02d:%c %c%c%c (x%d)\n",\
// 	(int)i, s[i], inq ? '"' : '.', inw ? 'w' : '.', fw ? 'f' : '.', (int)num);
	// (int)i, s[i], inq ? '"' : '.', inw ? 'w' : '.', (int)num);

static int	st_strsnum(char const *s, char c)
{
	int	i;
	size_t	num;
	unsigned char flag;

	i = -1;
	num = 0;
	flag = FW;
	while (s[++i])
	{
		if (flag & FW && flag & INW)
		{
			flag &= ~FW;
			num++;
		}
		if (s[i] == '\'')
			flag ^= INQ;
		if (!(flag & INQ) && s[i] == c)
			flag &= ~INW;
		else
			flag |= INW;
		if (!(flag & INW))
			flag |= FW;
	}
	return (num);
}

static int	st_lenstr(size_t i, char const *s, char c)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	**st_alloc2str(char **str2d, size_t numstrs, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] && j < numstrs)
	{
		while (s[i] == c)
			i++;
		str2d[j] = malloc((st_lenstr(i, s, c) + 1) * sizeof(char));
		if (!str2d[j])
			return (ft_purge2str(str2d));
		k = 0;
		while (s[i] && s[i] != c)
		{
			str2d[j][k] = s[i];
			i++;
			k++;
		}
		str2d[j][k] = 0;
		j++;
	}
	str2d[j] = 0;
	return (str2d);
}

char	**ft_qsplit(char const *s, char c)
{
	char	**strarr;
	size_t	numstrs;

	if (!s)
		return (0);
	numstrs = st_strsnum(s, c);
	strarr = malloc((numstrs + 1) * sizeof(char *));
	if (!strarr)
		return (0);
	return (st_alloc2str(strarr, numstrs, s, c));
}
