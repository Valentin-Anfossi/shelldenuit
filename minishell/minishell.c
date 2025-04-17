/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/17 19:43:56 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_token(char *line, int start, int end, t_token **tokens);
t_token **create_tokens(char *line);
void	create_space_token(t_token **tokens);
t_token **create_lst_tokens(char *line);
int create_quoted_token(char *line, t_token **tokens);
t_token **create_lst_tokens2(char *line);

int main(void)
{
	char *line;
	t_token **tokens;

	while(1)
	{
		line = readline("labonneshell :");
		if(line)
			tokens = create_lst_tokens2(line);	
		debug_print_tokens(tokens);
	}
		

}

void	create_space_token(t_token **tokens)
{
	t_token *new_token;
	new_token = malloc_token();
	new_token->content = " ";
	token_add_back(tokens,new_token);
}

int check_redirection(char *line)
{
	if(*line == '>' && *(line+1) == '>')
		return (2);
	else if(*line == '<' && *(line+1) == '<')
		return (2);
	else if(*line == '>')
		return (1);
	else if(*line == '<')
		return (1);
	else
		return (0);
}

void split_token(char *line, int start, int end, t_token **tokens)
{
	int i;
	
	i = 0;
	i = start;
	while(i <= end)
	{
		if(check_redirection(&line[i]))
		{
			printf("0");
			create_token(line,start,i,tokens);
			create_token(line,i,i + check_redirection(&line[i]),tokens);
			i += (check_redirection(&line[i]));
			start = i;
		}
		else if(i == end)
		{
			printf("1");
			create_token(line,start,end,tokens);
			i++;
		}
		else
			i ++;
	}
}

void create_token(char *line, int start, int end, t_token **tokens)
{
	t_token *new_token;
	int i;

	if(end <= start)
		return ;
	new_token = malloc_token();
	new_token->content = ft_substr(line, start, (end-start));
	token_add_back(tokens,new_token);
}

// Looks OK ! mais a tester !
// TO DO :
// pour reduire a 25 lines : tout mettre dans une struct et changer les values avec -> dans les create tokens func
// chiant a faire mais ca devrait passer

t_token **create_lst_tokens2(char *line)
{
    int in_doubles = 0;
    int in_singles = 0;
    int start = 0;
    int end = 0;
    t_token **tokens;
    
    tokens = (t_token **)malloc(sizeof(t_token *));
    *tokens = NULL;
    
    while(line[end])
    {
        if (line[end] == '"' && !in_singles)
        {
            if(in_doubles)
            {
                create_token(line, start, end + 1, tokens);
                start = end + 1;
                in_doubles = 0;
            }
            else if(ft_strchr(&line[end + 1], '"'))
            {
                split_token(line, start, end, tokens);
                start = end;
                in_doubles = 1;
            }
        }
        else if (line[end] == '\'' && !in_doubles)
        {
            if(in_singles)
            {
                create_token(line, start, end + 1, tokens);
                start = end + 1;
                in_singles = 0;
            }
            else if(ft_strchr(&line[end + 1], '\''))
            {
                split_token(line, start, end, tokens);
                start = end;
                in_singles = 1;
            }
        }
        else if (line[end] == ' ' && !in_doubles && !in_singles)
        {
            if (start != end) {
                split_token(line, start, end, tokens);
            }
            create_space_token(tokens);
            start = end + 1;
        }
        end++;
    }
    if (start < end) {
        split_token(line, start, end, tokens);
    }
    
    return tokens;
}


t_token **type_tokens(t_token **tokens)
{
		
}	


int create_quoted_token(char *line, t_token **tokens)
{
	int i;
	
    i = 1;
	while(line[i] != *line)
	{
		i++;	
	}
	create_token(line, 0, i + 1, tokens);
    return (i + 1);
}


// if strchr("/")
//	type = command;
//abou jdskdjskj "000"asda"sada asd
//0000100000000012333200002222210000
//LINE I
//dede "de"e" dwde

// int in_single;
// int in_double;

//dede "de"e" dwde
//  0000 1112   0100000 0

//abou jdskdjskj "000"asda"sada asd
// if croise une quote(weshlaquote)
// strchr("ouellestlaquote")
//si oui (bien)
//on continue jusqua cote et on tokenize
//si non (bou)
//on tokenize au prochain espace


// minishell :cd "bonjour

// t_token **create_lst_tokens(char *line)
// {
// 	int start = 0;
// 	int end = 0;
// 	t_token **tokens;

// 	tokens = (t_token **)malloc(sizeof(t_token *));
// 	*tokens = NULL;
// 	while(end <= (int)ft_strlen(line)) //"asd" "asd"
// 	{
// 		if(line[end] == ' ' || end == (int)ft_strlen(line))
// 		{
// 			create_token(line,start,end,tokens);
// 			create_space_token(tokens);
// 			start = end;
// 			start ++;
// 		}
// 		if(line[end] == '"')
// 			if (ft_strchr(&line[end],'"'))
//             {
//     			end += create_quoted_token(&line[end], tokens);
//                 start = end;
//                 continue ; 
//             }
// 		end ++;
// 	}
//     	// create_token(line, start, end, tokens);
// 	return (tokens);
// }