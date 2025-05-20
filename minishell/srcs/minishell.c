
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/29 13:36:35 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_redir(t_job *job)
{
	int		fd;
	char	**argv;
	char	**env;

	// Pour les rights faut mettre le code CHMOD a la fin
	fd = open("output",O_WRONLY | O_CREAT ,0755);
	argv = NULL;
	env = NULL;
	//on redirige STDOUT dans le fd
	dup2(fd, STDOUT_FILENO);
	fd = open("infile",O_RDONLY);
	// isatty (entrée utilisateur ou d,un pipe/fichier/script.), ttyname, ttyslot, ioctl,
	//on le ferme paske plus besoin
	close(fd);
	ft_printf("hello ?\n");
	execve("ls",argv,env);
	exit(EXIT_FAILURE);
	//Ca redirect bien "hello ?" et le ls dans le fichier output !! :o magie ! 🪄
}



t_shell	*create_shell(void)
{
	extern char	**environ;
	t_shell		*s;
	pid_t		pid_main;
	int			i;

	pid_main = getpid();
	i = 0;
	s = (t_shell *)malloc(sizeof(t_shell));
	while (environ[i])
		i++;
	s->env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (environ[i])
	{
		s->env[i] = ft_strdup(environ[i]);
		i++;
	}
	s->env[i] = ft_strdup("MINISHELL=trobien");
	s->env[i + 1] = NULL;
	if (!getcwd(s->cwd, 0))
	{
		ft_printf("Could not get current working dir. wtf did you do ?");
		exit(EXIT_FAILURE);
	}
	getcwd(s->cwd,0);
	return (s);
}

int	is_tok_quoted(t_token *tok)
{
	if (tok->content[0] == '\''
		&& tok->content[ft_strlen(tok->content)] == '\'')
		return (1);
	else
		return (0);
}

void tokens_start(t_token **t, t_shell *s)
{
	typing_tokens(t);
	check_env(t, s);
	check_tokens(t);
	//debug_print_tokens(tokens);
}

int	main(void)
{
	char	*line;
	t_shell	*shell;
	t_token	**tokens;
	t_job	*jobs;

	shell = create_shell();
	while (1)
	{
		line = readline("minishell: ");
		if (line)
		{
			tokens = create_lst_tokens(line);
			add_history(line);
		}
		tokens_start(tokens,shell);
		//debug_print_tokens(tokens);
		jobs = create_job(tokens);
		debug_print_job(jobs);
		if (!check_jobs(jobs))
			execute_jobs(jobs, shell);
		//debug_print_job(jobs);
		free_jobs(jobs);
		//exit(0);
	}
	clear_history();
}
