
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

//pour test il faut mettre une commande valide genre "cd bou"
//ca fait pas la commande, juste ca print et fait un ls avec le new process
//c normal c pour tester
//tkt

//Execve a besoin du path COMPLET (/home/vanfossi/blablabla)
//l'arg Env de execve determine si il recoit les variable d'enviro
//env = null par ex, il a acces a rien
//pour l'env actuel de l'os c'est 

//mais jpense faut faire le notre avec nos variables non ? (c pas precise mais ca ferait sens)

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
	execve("./test",argv,env);
	exit(EXIT_FAILURE);
	//Ca redirect bien "hello ?" et le ls dans le fichier output !! :o magie ! 🪄
}
//They took er jebs!
// Est ce quil faut rien faire avec le parent thread ? (a part wait l'exit du child)
// Je sais pas trop
// Aussi les redirections out (out et out_append) on peut les faire sans pipe
// dup2 ca fonctionne tres bien (woopi) exemple au dessus
void execute_jobs(t_job *jobs, t_shell *shell)
{
	int *statloc;
	
	statloc = (int *)malloc(sizeof(int));
	while (jobs)
	{
		pid_t n_pid = fork();
		if (n_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		// CHILD FORK
		if (n_pid == 0)
		{
			select_command(jobs,shell);
			exit(EXIT_FAILURE);
		}
		// PARENT FORK (DO NOTHING BUT WAIT)
		else
		{
			waitpid(n_pid,statloc,WUNTRACED);
		}
		jobs = jobs->piped_job;
	}
}

t_shell *create_shell(void)
{
	t_shell *s;

	s = (t_shell *)malloc(sizeof(t_shell));
	extern char **environ;
	s->env = environ;
	int i = 0;
	while (s->env[i])
		i ++;
	s->env[i] = ft_strdup("MINISHELL=trobien");
	//s->env[i+1] = NULL;
	if (!getcwd(s->cwd,0))
	{
		perror("Could not get current working dir. wtf did you do ?");
		exit(EXIT_FAILURE);
	}
	//Get the OS environement variables (spour tester)
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

int main(void)
{
	char *line;
	t_shell *shell;
	t_token **tokens;
	t_job	*jobs;

	shell = create_shell();
	int i = 0;
	// while (shell->env[i++])
	// 	printf("%s\n",shell->env[i]);

	while (1)
	{
		line = readline("labonneshell :");
		if (line)
		{
			tokens = create_lst_tokens(line);
			add_history(line);
		}
		typing_tokens(tokens);
		debug_print_tokens(tokens);
		check_env(tokens,shell);
	//	debug_print_tokens(tokens);
		check_tokens(tokens);
		debug_print_tokens(tokens);
		jobs = create_job(tokens);
		if (!check_jobs(jobs))
			execute_jobs(jobs,shell);
		debug_print_job(jobs);
		free_jobs(jobs);
	}
	clear_history();
}
