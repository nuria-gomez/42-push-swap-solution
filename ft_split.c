/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomez-v <ngomez-v@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:02:27 by ngomez-v          #+#    #+#             */
/*   Updated: 2026/09/02 11:23:04 by ngomez-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allocates memory (using malloc(3)) and returns an
array of strings obtained by splitting ’s’ using
the character ’c’ as a delimiter. The array must
end with a NULL pointer.

RETURN: 
+ The array of new strings resulting from the split.
+ NULL if the allocation fails.

External functions: malloc() and free()
*/

#include "push_swap.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	*copy_word(char const *s, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	liberating(char **arr, int n)
{
	while (n >= 0)
	{
		free(arr[n]);
		n--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		n;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	i = 0;
	n = 0;
	while (n < words)
	{
		while (s[i] == c)
			i++;
		arr[n] = copy_word(&s[i], word_len(&s[i], c));
		if (!arr[n])
			return (liberating(arr, n - 1), NULL);
		n++;
		i += word_len(&s[i], c);
	}
	arr[n] = NULL;
	return (arr);
}
/*
#include <stdio.h>
int  main (void)
{
	//char *arr = "Hola, buenos dias";
	//char **s = ft_split(arr, ' ');
	ft_split("Hola, buenos dias", ' ');
	ft_split("Hola,    buenos dias", ' ');
	ft_split("          ", ' ');
	ft_split("     H     ", ' ');
}
*/