typedef enum e_token
{
    nothing = 0,
    WORD = -1,
    WHITE_SPACE = ' ',
    NEW_LINE = '\n',
    QOUTE = '\'',
    DOUBLE_QUOTE = '\"',
    ENV = '$',
    PIPE_LINE = '|',
    REDIR_IN = '<',
    REDIR_OUT = '>',
    APPEND_OUT,  // To handle '>>' redirection
    HERE_DOC,
    DREDIR_OUT,
} t_token;

typedef struct s_redirect
{
    t_token type;
    char *store;
    struct s_redirect *next;
} t_redirect;

typedef struct s_command
{
    char *content;
    char **arg;
    t_redirect *doc;
    struct s_command *next;
} t_command;


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void handle_redir_out(char *file)
{
    int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        exit(1);
    }
    close(fd);
}

void handle_append_out(char *file)
{
    int fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        exit(1);
    }
    close(fd);
}

void handle_redir_in(char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        exit(1);
    }
    close(fd);
}


void handle_redirections(t_command *cmd)
{
    t_redirect *redir = cmd->doc;

    while (redir)
    {
        if (redir->type == REDIR_OUT)
        {
            handle_redir_out(redir->store);
        }
        else if (redir->type == APPEND_OUT)
        {
            handle_append_out(redir->store);
        }
        else if (redir->type == REDIR_IN)
        {
            handle_redir_in(redir->store);
        }
        redir = redir->next;
    }
}


void execute_cmd(t_command *cmd, char **env)
{
    char *path = cmd->arg[0];
    if (fork() == 0)
    {
        handle_redirections(cmd);

printf("path: %s\n", cmd->arg[0]);
        if (execve(path, cmd->arg, env) < 0)
        {
            perror("execve");
            exit(1);
        }
    }
    else
    {
        wait(NULL); // Wait for the child process to finish
    }
}
int ft_strlen(const char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}   
char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*s2;

	len = ft_strlen(s1);
	s2 = (char *) malloc((len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2 [i] = '\0';
	return (s2);
}

int main(int argc, char **argv, char **envp)
{
    // Example: ls > file
    t_command *cmd = (t_command *)malloc(sizeof(t_command));
    if (!cmd)
        return 1;

    cmd->content = ft_strdup("ls");
    cmd->arg = (char **)malloc(2 * sizeof(char *));
    cmd->arg[0] = ft_strdup("ls");
    cmd->arg[1] = NULL;

    t_redirect *redir = (t_redirect *)malloc(sizeof(t_redirect));
    if (!redir)
        return 1;

    redir->type = REDIR_OUT;
    redir->store = ft_strdup("file");
    redir->next = NULL;

    cmd->doc = redir;
    cmd->next = NULL;

    execute_cmd(cmd, envp);

    // Clean up
    free(cmd->arg[0]);
    free(cmd->arg);
    free(cmd->doc->store);
    free(cmd->doc);
    free(cmd->content);
    free(cmd);

    return 0;
}
