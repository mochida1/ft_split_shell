/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:58:18 by coder             #+#    #+#             */
/*   Updated: 2022/08/27 06:06:51 by coder            ###   ########.fr       */
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
	char	*string;
	char	*temp;
	int		words;
	int		i;
	int		split_number;
	char	delimiter;
}	t_split_shell;

void	iterate_through_quotes(t_split_shell *this)
{
	char first_char;

	first_char = this->temp[0];
	if (first_char == '\'' || first_char == '\"') //se o primeiro caractere for alguma aspa
	{
		if (this->temp[1]) //checa se o proximo elemento não é nulo
			this->temp++;
		while (this->temp[0] && (this->temp[0] != first_char)) //itera até achar o próximo
			this->temp++;
		if (this->temp[0] == first_char)
			this->temp++;
		this->words++;
		return ;
	}
	while (this->temp[0] && (this->temp[0] != this->delimiter)) //aqui checamos o caso da palavra não conter aspas;
		this->temp++;
	this->words++; //contamos mais uma palavra
}

void	count_words (t_split_shell *this) //conta quantas palavras temos
{
	this->temp = this->string;
	while (this->temp[0])
	{
		while (this->temp[0] == this->delimiter)
			this->temp++;
		iterate_through_quotes(this); //pula até os proximos espaços, se alguma aspas for o primeiro caratere, itera até o primeio espaço depois de aspas
	}
}

int	get_word_size (char *str, char delimiter)
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
		size++; // já soma a bagaça
		while(*str && (*str != first_char)) //enquanto não for a mesma coisa e enquanto nao acabar
		{
			temp++;
			size++;
		}
		return (size + (*str == first_char)); //retorna e i, e se o ultimo caractere for igual a ' ou ", soma mais um pq não iteramos por ele
	}
	while (*temp && (*temp != delimiter))
	{
		temp++;
		size++;
	}
	return (size); // se não for uma palavra que comeca com aspas, simplesmente iteramos pela palavra inteira.
}

void	copy_to_split(char *split, t_split_shell *this)
{
	char	first_char;
	int		i;

	i = 0;
	first_char = this->temp[0];
	if (first_char == '\'' || first_char == '\"')
	{
		split[i++] = first_char;
		this->temp++;
		while (this->temp[0] != first_char)
		{
			split[i] = this->temp[0];
			printf (">%d<%c\n", i, split[i]);
			i++;
			this->temp++;
		}
		this->temp++;
		split[i] = first_char;
		return ;
	}
	while (this->temp[0] && this->temp[0] != ' ')
	{
		split[i] = this->temp[0];
		this->temp++;
		i++;
	}
	split[i] = 0;
}

int main (void)
{
	char	delimiter = ' ';
	// char	*str = "<< hi this is \" a test<<t\'o>>test\" >><\'< \">\'>|>> \'>>\'<<>>";
	char	*str = strdup("    aaaaa    \'bbbbbbb\'   \"ccccccc\" \'dd\"dd\'      \"ee\'ee\" ffffff g");

	char			**splits;
	t_split_shell	*this;

	this = calloc (1, sizeof(*this) + 1);
	this->temp = str;
	this->delimiter = delimiter;
	this->string = str;
	count_words(this);
	splits = calloc ((this->words + 1) , sizeof(char *)); //allocamos memória para a quantidade de palavras e um byte nulo;
	this->temp = this->string;
	while (this->i < this->words)
	{
		while (this->temp[0] == this->delimiter) //vai até a primeira/proxima palavra;
			this->temp++;
		splits[this->i] = calloc ((get_word_size(this->temp, this->delimiter) + 1) , sizeof(char)); //alloca memória pro rolê, já inicializada em 0 :)
		copy_to_split (splits[this->i], this);
		printf ("[%d]%s\n", this->i, splits[this->i]);
		this->i++;
	}


	this->i = 0;
	{
		while (this->i < this->words)
		{
			free (splits[this->i]);
			this->i++;
		}
	}
	free (this);
	free (str);
	return (0);
}
