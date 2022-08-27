/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:58:18 by coder             #+#    #+#             */
/*   Updated: 2022/08/27 03:51:46 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// char	**ft_split_shell(char *str, char delimiter)
// {


// }

typedef struct s_split_shell
{

}	t_split_shell;

void	iterate_through_spaces(char *str)
{
	while (*str == ' ')
		str++;
}

int	iterate_through_quotes(char *str)
{
	char first_char;

	first_char = *str;
	if (!first_char) //em caso de erro, volta 0;
		return (0);
	if (str[1]) //checa se o proximo elemento não é nulo
		str++;
	if (first_char == '\'' || first_char == '\"') //se o primeiro caractere for alguma aspa
	{
		while (*str && (*str != first_char)) //itera até achar o próximo
			str++;
		if (*str == first_char) //quer dizer que temos uma palavra nova;
			return (1); //retorna 1 para somar a palavra;
	}
	while (*str && (*str != ' ')) //aqui checamos o caso da palavra não conter aspas;
	{
		str++;
	}
	return (1); //contamos uma palavra a mais
}

int	count_words (char *str, char delimiter) //conta quantas palavras temos
{
	char	*temp; //aqui usamos temp para mantér o ponteiro original no lugar certo
	int		words = 0;
	while (*temp)
	{
		iterate_through_spaces(temp); //pula os espaços
		words += iterate_through_quotes(temp); //pula até os proximos espaços, se alguma aspas for o primeiro caratere, itera até o primeio espaço depois de aspas
	}
	return (words);
}

int	get_word_size (char *str, ' ')
{
	char	*temp; //não queremos mexer no original;
	char	first_char;
	int		size;

	temp = str;
	size = 0;
	first_char = *temp;
	if (first_char == '\'' || first_char == '\"') //se o primeiro char for aspas
	{
		temp++; //pula a primeira letra que sabemos qual é
		i++; // já soma a bagaça
		while(*str && (*str != first_char)) //enquanto não for a mesma coisa e enquanto nao acabar
		{
			temp++;
			i++;
		}
		return (i + (*str == first_char)); //retorna e i, e se o ultimo caractere for igual a ' ou ", soma mais um pq não iteramos por ele
	}
	while (*temp && (temp != ' '))
	{
		temp++;
		i++;
	}
	return (i); // se não for uma palavra que comeca com aspas, simplesmente iteramos pela palavra inteira.
}

int main (void)
{
	char	delimiter = ' ';
	char	*str = "<< hi this is \" a test<<t\'o>>test\" >><\'< \">\'>|>> \'>>\'<<>>";

	char	**splits;
	int		split_number;
	int		i;
	char	*temp;

	temp = str;
	split split_number = count_words(str, delimiter);
	splits = malloc ((split_number + 1) * sizeof(char *)); //allocamos memória para a quantidade de palavras e um byte nulo;
	while (i < split_number)
	{
		iterate_through_spaces(temp); //vai até a primeira/proxima palavra;
		split[i] = calloc ((get_word_size(temp)) + 1), sizeof(char)); //alloca memória pro rolê, já inicializada em 0 :)
		copy_to_split (temp, split[i]);
		i++;
	}
}
