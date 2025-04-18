/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/18 03:37:10 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_token(char *line, int start, int end, t_token **tokens);
t_token **create_tokens(char *line);
void	create_space_token(t_token **tokens);
t_token **create_lst_tokens(char *line);
int create_quoted_token(char *line, t_token **tokens);
t_token **create_lst_tokens2(char *line);
void type_tokens(t_token **tokens);

// SALUT VAL
// CE MESSAGE S'AUTODETRUIRA PAS PARCE QUE JE SAIS PAS CODER CA
// J'ai pas trouver d'erreur dans le tokeniser GG ! (j.ai juste ajouter un check pour le pipe)
// du coup en ce qui concerne le parsing, je fais peut etre fausse route
// mais la seule chose qui m'est venu en tete c'est de :
// commencer a preparer les jobs en creeant une struct t_job
// commencer a checker les erreurs de commande
// QUESTION : quand on tokenise les redir heredoc et append, ce serait pas mieux de ne pas les differencier 
//			dans le tokeniser mais plutot apres la creation du JOB, au moment ou on "execute" la redir/heredoc ??? 
//
//ATTENTION SPOIL : ce que j'ai fait la, segfault.... Je recheck ca vite la je pars au taff !
//
//
//petite info pour le pipe : si il est entre quote, il joue pas le role de pipe 
// jelucian@c1r2p8:~/Core$ echo salut "|" cat yo.txt 
// salut | cat yo.txt


t_job	*malloc_job(void)
{
	t_job *job;

	job = (t_job *)malloc(sizeof(t_job));
	job->args = NULL;
	job->cmd = NULL;
	job->redir = NULL;
	job->piped_job = NULL;
	return (job);
}

int check_for_commands(char *content)
{

	if (ms_strcmp("echo", ft_strtrim(content, "\"\'")))
		return (1);
	else if(ms_strcmp("cd", ft_strtrim(content, "\"\'")))
		return (1);
	else if(ms_strcmp("pwd", ft_strtrim(content, "\"\'")))
		return (1);
	else if(ms_strcmp("export", ft_strtrim(content, "\"\'")))
		return (1);
	else if(ms_strcmp("unset", ft_strtrim(content, "\"\'")))
		return (1);
	else if(ms_strcmp("env", ft_strtrim(content, "\"\'")))
		return (1);
	else if(ms_strcmp("exit", ft_strtrim(content, "\"\'")))
		return (1);
	write(2, ft_strtrim(content, "\"\'"), ft_strlen(ft_strtrim(content, "\"\'")));
	write(2, ": command not found", 20);
	return (0);
}
// skip les espaces au debut a faire;
t_job	*create_job(t_token *tokens, t_job **jobs)
{
	t_job	*new_job;
	int		i;

	i = 0;
	new_job = malloc_job();
	if (check_for_commands(tokens[0].content))
		new_job->cmd = ft_strtrim(tokens[0].content, "\"\'");
	tokens = tokens->next;
	while(tokens)
	{
		if (tokens->type == ARG && tokens->content == "|")
			new_job->piped_job = create_job(tokens, jobs);
		else if (tokens->type == ARG || tokens->type == QUO_D || tokens->type == QUO_S)
		{
			new_job->args[i] = tokens->content;
			i++;
		}
		else if (tokens->type != SPC)
			new_job->redir[0] = tokens->content;
		if (!tokens->next)
			break;
		tokens = tokens->next;
	}
	return (new_job);
}


t_job	**create_lst_job(t_token **tokens)
{
	t_job **jobs;
	t_token *t;
	
	t = *tokens;
	jobs = (t_job **)malloc(sizeof(t_job *));
	*jobs = create_job(t, jobs);
	return (jobs);
}

// BONJOUR JF
//CES INSTRUCTIONS SAUTODETRUIRON DANS 69 SECONDES
// EN VRAI JE CROIS CA MARCHE
// CA FAIT AUSSI LES TYPES

//en gros : ca fait les tokens avec create_lst_tokens2
//si c'est du texte ca l'envoie dans split token
//		ca split les >> < << etc et ca fait des tokens
//sinon si c'est entre quotes ca en fait un token

// si tu veux test fais toi plaiz, vaut mieux trouver les bug maintenant
// en gros on est de retour a ce qu'on avait avant (avec les quotes)
// maintenant faut faire le parser
// https://www.geeksforgeeks.org/recursive-descent-parser/
// il est 3h du mat donc bonne nuit

int main(void)
{
	char *line;
	t_token **tokens;
	t_job	**jobs;

	while(1)
	{
		line = readline("labonneshell :");
		if(line)
			tokens = create_lst_tokens2(line);
		type_tokens(tokens);
		debug_print_tokens(tokens);
		jobs = create_lst_job(tokens);
	//	debug_print_job(jobs);
	}
}

void	create_space_token(t_token **tokens)
{
	t_token *new_token;
	new_token = malloc_token();
	new_token->content = " ";
	token_add_back(tokens,new_token);
}

int check_redirection_pipe(char *line)
{
	if(*line == '>' && *(line+1) == '>')
		return (2);
	else if(*line == '<' && *(line+1) == '<')
		return (2);
	else if(*line == '>')
		return (1);
	else if(*line == '<')
		return (1);
	else if(*line == '|')
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
		if(check_redirection_pipe(&line[i]))
		{
			create_token(line,start,i,tokens);
			create_token(line,i,i + check_redirection_pipe(&line[i]),tokens);
			i += (check_redirection_pipe(&line[i]));
			start = i;
		}
		else if(i == end)
		{
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

//25 lignes tout pile 
void type_tokens(t_token **tokens)
{
	t_token *t;

	t = *tokens;
	while(t)
	{
		if(!ms_strcmp(t->content,">"))
			t->type = RE_OUT;
		else if(!ms_strcmp(t->content,">>"))
			t->type = RE_APP;
		else if(!ms_strcmp(t->content,"<"))
			t->type = RE_IN;
		else if(!ms_strcmp(t->content,"<<"))
			t->type = HEREDOC;
		else if(t->content[0]=='"' && t->content[ft_strlen(t->content)-1] == '"')
			t->type = QUO_D;
		else if(t->content[0]=='\'' && t->content[ft_strlen(t->content)-1] == '\'')
			t->type = QUO_S;
		else if(!ms_strcmp(t->content," "))
			t->type = SPC;
		else
			t->type = ARG;
		if(!t->next)
			break;
		t = t->next;
	}
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