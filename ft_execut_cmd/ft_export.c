#include "../minishell.h" 

t_envarment *ft_stock_envarment(char **env)
{
	t_envarment *var=NULL;
	char **list;
	int i =0;
	while (env[i])
	{
		list = ft_split(env[i], '=');
		t_envarment *elem = new_node(list[0],list[1]);
		add_back_node(&var , elem);
		free(list);
		i++;
	}
	return var;
}
int 	test_exist(t_envarment *var , char **list)
{
	t_envarment *ptr;
	ptr = var;
	while (ptr)
	{
		if(ft_strcmp(ptr->var,list[0]) == 0 && ft_strcmp(ptr->data,list[1]) == 0 && list[1]!=NULL)
		{
			return 0;
		}
		else if(ft_strcmp(ptr->var,list[0]) == 0 && ft_strcmp(ptr->data,list[1]) != 0 && list[1]!= NULL)
		{
			ptr->data=list[1];
			return 0;
		}
		else if(ft_strcmp(ptr->var,list[0]) != 0 && ft_strcmp(ptr->data,list[1]) == 0)
		{
			ptr->var=list[0];
			return 0;
		}
		else if (ft_strcmp(ptr->var,list[0]) == 0 && list[1] == NULL)
		{
			ptr->data="''";
			return 0;
		}
		ptr = ptr->next;
	}
	return 1;
	
}
void 	ft_export( t_envarment *var ,t_command *str )
{
	char **list;
	t_command *save = str;
	str = str->next;
	while (str)
	{
		if (str->type == -1  && str->str_input[0] != '=')
		{
			list = ft_split(str->str_input, '=');
			if( test_exist(var, list) == 0)
			{
				break;
			}
			if(list[1] == NULL)
			{
				t_envarment *elem = new_node(list[0], "''");
				add_back_node(&var , elem);
			}
			else
			{
				t_envarment *elem = new_node(list[0],list[1]);
				add_back_node(&var , elem);
			}
			free(list);
		}
		str = str->next;
	}
	save = save->next;
	if(save->next == NULL)
	{
		t_envarment *ptr;
		ptr = var;
		while (ptr)
		{
			printf("%s   <<<===>>>>>  %s \n", ptr->var, ptr->data);
			ptr=ptr->next;
		}
	}
}
