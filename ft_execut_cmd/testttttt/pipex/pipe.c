# include "/Users/bouhammo/Desktop/minishell_5/includes/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_pipex
{
	char	**paths;
	int		f1;
	int		f2;
	char	**envp;
	char	**cmds1;
	char	**cmds2;
}	t_pipex;

char	**parse_envp(char **argv, char **envp);




char	*find_path(char **envp)
{
	char	*path_from_envp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path_from_envp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		i++;
	}
	
	return (path_from_envp);
}

char	**parse_envp(char **argv, char **envp)
{
	char	*path_from_envp;
	char	**mypaths;
	int		i;
	char	*tmp;

	path_from_envp = find_path(envp);
	mypaths = ft_split(path_from_envp, ':');
	// free(path_from_envp);
	i = 0;
	while (mypaths[i])
	{
		if (ft_strncmp(&mypaths[i][ft_strlen(mypaths[i]) - 1], "/", 1) != 0)
		{
			tmp = ft_strjoin(mypaths[i], "/");
			// free(mypaths[i]);
			mypaths[i] = tmp;
		}
		i++;
	}
	return (mypaths);
}



void	child1_process(t_pipex *info, int *end)
{
	int		i;
	char	*mycmd;

	if (dup2(info->f1, STDIN_FILENO) < 0)
		return (perror("Dup "));
	if (dup2(end[1], STDOUT_FILENO) < 0)
		return (perror("Dup "));
	close(end[0]);
	close(info->f1);
	i = 0;
	while ((info->paths)[i])
	{
		mycmd = ft_strjoin((info->paths)[i], (info->cmds1)[0]);
		if (!access(mycmd, F_OK && X_OK))
			execve(mycmd, info->cmds1, info->envp);
		// free(mycmd);
		i++;
	}
	perror("Cmd not found ");
	exit(EXIT_FAILURE);
}

void	child2_process(t_pipex *info, int *end)
{
	int		i;
	char	*mycmd;

	if (dup2(info->f2, STDOUT_FILENO) < 0)
		return (perror("Dup "));
	if (dup2(end[0], STDIN_FILENO) < 0)
		return (perror("Dup "));
	close(end[1]);
	close(info->f2);
	i = 0;
	while ((info->paths)[i])
	{
		mycmd = ft_strjoin((info->paths)[i], (info->cmds2)[0]);
		if (!access(mycmd, F_OK && X_OK))
			execve(mycmd, info->cmds2, info->envp);
		// free(mycmd);
		i++;
	}
	perror("Cmd not found ");
	exit(EXIT_FAILURE);
}

void	pipex(t_pipex *info)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child1_process(info, end);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child2_process(info, end);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	info;

	if (argc != 5)
	{
		perror("Invalid number of arguments");
		exit(EXIT_FAILURE);
	}
	info.f1 = open(argv[1], O_RDONLY );
	info.f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info.f1 < 0 || info.f2 < 0)
	{
		perror("Open ");
		exit(EXIT_FAILURE);
	}
	info.envp = envp;
	info.cmds1 = ft_split(argv[2], ' ');
	info.cmds2 = ft_split(argv[3], ' ');
	info.paths = parse_envp(argv, envp);
	pipex(&info);
	return (0);
}
