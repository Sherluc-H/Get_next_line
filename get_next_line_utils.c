/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:38:09 by lhuang            #+#    #+#             */
/*   Updated: 2019/11/07 16:24:15 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_merge(char *s1, char *s2, int s1_size, int s2_size)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(p = malloc(sizeof(char) * (s1_size + s2_size) + 1)))
		return (NULL);
	while (i < s1_size)
	{
		p[i] = s1[i];
		i++;
	}
	while (j < s2_size)
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	free(s1);
	free(s2);
	return (p);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		s1_size;
	int		s2_size;
	int		i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i])
			i++;
		s1_size = i;
		i = 0;
		while (s2[i])
			i++;
		s2_size = i;
		return (ft_merge(s1, s2, s1_size, s2_size));
	}
	return (NULL);
}

int			ft_create_remain(t_fd_list **current, int i, int end_line, char *b)
{
	int		j;
	char	*t;

	j = 0;
	t = NULL;
	if (end_line && i + j < (*current)->remain_size)
	{
		if (!(t = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		while (end_line && i + j < (*current)->remain_size)
		{
			t[j] = b[j + i];
			j++;
		}
		t[j] = '\0';
		free((*current)->remain);
		(*current)->remain = t;
		(*current)->remain_size = j;
		return (1);
	}
	free((*current)->remain);
	(*current)->remain = NULL;
	(*current)->remain_size = 0;
	return (1);
}

int			ft_cut_line(char *b, t_fd_list **current, int *rd, char **str1)
{
	int		i;
	char	*str2;

	i = 0;
	if (!(str2 = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (i < *rd)
	{
		str2[i] = b[i];
		if (b[i] == '\n')
		{
			str2[i] = '\0';
			*str1 = ft_strjoin(*str1, str2);
			(*current)->remain_size = *rd;
			return ((ft_create_remain(current, i + 1, 1, b)));
		}
		else if (i == *rd - 1)
		{
			str2[i + 1] = '\0';
			*str1 = ft_strjoin(*str1, str2);
			return (0);
		}
		i++;
	}
	return (-1);
}

int			ft_cut_remain(char *b, t_fd_list **current,
			int *end_line, char **str1)
{
	int		i;
	char	*str2;

	i = 0;
	if (!(str2 = malloc(sizeof(char) * ((*current)->remain_size + 1))))
		return (-1);
	while (i < (*current)->remain_size && !*end_line)
	{
		if (b[i] == '\n')
			*end_line = 1;
		str2[i] = b[i];
		if (*end_line)
			str2[i] = '\0';
		i++;
	}
	str2[i] = '\0';
	*str1 = str2;
	if ((ft_create_remain(current, i, *end_line, b) == -1))
		return (-1);
	return (1);
}
