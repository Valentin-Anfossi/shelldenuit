int shell_execute(char *path)
{
	int ret;
	pid_t f = fork();
	char **argv;

	// si f(pid du proccess fork) == 0 alors le process est le process enfant
    if(f == 0)
    {
		//Faut initialiser Argv avant de le passer a execve (meme si il est vide) sinon execve fail et ne lance rien
        argv = NULL;
        execve(path, argv, NULL);
		//perror permet de print le message d'erreur renvoye par execve (si le fichier existe pas par ex.)
        perror("Error");
        exit(EXIT_FAILURE);
    }
	// si non, c'est le parent donc on wait que f soit fini
	else
	{
		waitpid(f,&ret,0);
	}
}

int shell_testoutfile(char *path)
{
	int ret;
	int pipedes[2];
	char read_buffer;
	pipe(pipedes);
	pid_t f=fork();
	int bytes_read;
	//Cree le pipe 
	
	if(f == 0)
	{
		
		close(pipedes[0]);
		dup2(pipedes[1],1);
		//duplique le stdout(1) du process vers la write end du pipe pipedes[1])
		// if(dup2(pipedes[1],1)== -1)
		// {
		// 	perror("duperror");
		// }
		//dup2(pipedes[1],2);
		//close(pipedes[1]);
		char *argv[] = {path,NULL};
		execve(path, argv, NULL);
		perror("Execve Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipedes[1]);
		while (read(pipedes[0], &read_buffer, 1) > 0)
		{
			printf("%c/",read_buffer);
		}
		waitpid(f,&ret,0);
		//close(pipedes[0]);
	}
}

int job_exec(char *line, s_job *job, int i)
{
	int end;
	
	end = i;
	while(line[end] != ' ')
		end ++;
	if(job->command)
		return (end);
	job->command = EXEC;
	job->exec_path = ft_substr(line,i,end-i);
	return (end);
}

int job_infile(char *line, s_job *job, int i)
{
	int end;

	i ++;
	while(line[i] == ' ')
		i++;
	end = i;
	while(line[end] != ' ')
		end++;
	if(job->infile_path)
		return(end);
	job->infile_path = ft_substr(line,i,end-i);
	return (end);
}
int job_outfile(char *line, s_job *job, int i)
{
	int end;

	i ++;
	while(line[i] == ' ')
		i++;
	end = i;
	while(line[end] != ' ')
		end++;
	if(job->outfile_path)
		return(end);
	job->outfile_path = ft_substr(line,i,end-i);
	return (end);
}

int job_append(char *line, s_job *job, int i)
{
	return(i);
	
}

int job_heredoc(char *line, s_job *job, int i)
{
	return(i);
	
}

int job_pipe(char *line, s_job *job, int i)
{
	return(i);
	
}

int job_env(char *line, s_job *job, int i)
{
	return(i);	
}
int job_arg(char *line, s_job *job, int i)
{
	return(i);
}
//< << ca va pas bou
int create_job(char *line, int i, s_job *job)
{
	if(line[i] == '.' && line[i+1] == '/' && line[i+1])
		i = job_exec(line, job, i);
	else if(line[i] == '<' && line[i+1] && line[i+1] == '<')
		i = job_heredoc(line, job,i);
	else if(line[i] == '>' && line[i+1] && line[i+1] == '>')
		i = job_append(line, job,i);
	else if(line[i] == '<')
		i = job_infile(line, job,i);
	else if(line[i] == '>')
		i = job_outfile(line, job,i);
	else if(line[i] == '|')
	{
		i = job_pipe(line, job,i);
		return (i);
	}
	else if(line[i] == '$')
		i = job_env(line, job,i);
	else
	{
		if(line[i])
			i = job_arg(line,job,i);
		if(!line[i])
			return(-1);
	}
	return (i);
}

void delete_job(s_job *job)
{
	// job->args = NULL;
	// job->command = NULL;
	// job->envs = NULL;
	// job->envs_id = NULL;
	// job->exec_path = NULL;
	// job->infile_path = NULL;
	// job->outfile_path = NULL;
	free(job);
}

void print_job(s_job *job)
{
	int i;
	i = 0;
	printf("Job #%d\nCommande : %i\nExec Path : %s\nInfile : %s\nOutfile : %s\n",job->id,
		job->command,job->exec_path,job->infile_path,job->outfile_path);
	printf("Args : %s\n", job->args);
	printf("Pipe :\n");
}

void init_job(s_job *job)
{
	job->args = NULL;
	job->command = NULL;
	job->exec_path = NULL;
	job->id = NULL;
	job->infile_path = NULL;
	job->outfile_path = NULL;
}

int start_jobs(char *line)
{
	int i = 0;
	s_job *job = (s_job *)malloc(sizeof(s_job));
	if(!line)
	{
		printf("Exiting minishell...\n");
		rl_clear_history();
		exit(0);
	}
	init_job(job);
	while(line[i])
	{
		while(line[i] ==  ' ')
			i ++;
		i = create_job(line, i, job);
		i++;
	}
	print_job(job);
	delete_job(job);
	//job_print(job);
}

// char *create_input_line(char *line)
// {
// 	char *before;
// 	char *after;
// 	char *env;
// 	int i;
// 	int end;

// 	i = 0;
	
// 	while(line[i])
// 	{
// 		if (line[i] == '$' && (line[i + 1] != '?' || line[i + 1] != ' ') && line[i+1])
// 		{
// 			end = i;
// 			before = ft_substr(line,0, i-1);
// 			while(line[i] != ' ')
// 				end ++;
// 			env = getenv(ft_substr(line,i,end-i));
// 			ft_strlcat(before,env,ft_strlen(before)+ft_strlen(env));
// 			i = end;
// 		}
// 		else
// 			before[i] = line [i];
// 	}
// 	return (before);
// }

// int replace_env(char *line, int i, s_token **tokens)
// {
// 	int end;
// 	char *env;
// 	char *stor;
// 	int start;

// 	start = 0;
// 	end = i;
// 	while(line[end] != ' ' && line[end])
// 		end ++;
// 	env = getenv(ft_substr(line,i,end-i));
// 	printf("Test: %s,%d",ft_substr(line,i,end-i),end);
// 	if(!env)
// 		return(end);
// 	//stor = ft_strdup(env);
// 	tokenizer(env,tokens,0);
// 	return (end);
// }