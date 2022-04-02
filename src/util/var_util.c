#include "minishell.h"

static unsigned int	name_len(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] == '=')
			break;
	}
	return (i);
}

void	add_var(t_list *var_list, char *name_and_value)
{
	t_list	*new;

	new = ft_lstnew(ft_strdup(name_and_value));
	ft_lstadd_back(&var_list, new);
}

char	*find_var(t_list *var_list, char *name)
{
	t_list	*tmp;
	char	*tmp_name;
	char	*tmp_value;
	unsigned int	tmp_name_len;

	tmp = var_list;
	while (tmp)
	{
		tmp_name = (char *)tmp->content;
		tmp_name_len = name_len(tmp_name);
		if (ft_strncmp(name, tmp_name, tmp_name_len) == 0)
		{
			tmp_value = ft_strdup(tmp_name + tmp_name_len + 1);
			return (tmp_value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_var(t_list *var_list, char *name, char *new_value)
{
	t_list	*tmp;
	char	*tmp_name;
	unsigned int	tmp_name_len;
	char	*new;

	tmp = var_list;
	while (tmp)
	{
		tmp_name = (char *)tmp->content;
		tmp_name_len = name_len(tmp_name);
		if (!ft_strncmp(name, tmp_name, tmp_name_len))
			break ;
		tmp = tmp->next;
	}
	new = ft_strjoin(ft_strndup(tmp_name, tmp_name_len + 1), new_value);
	free(tmp->content);
	tmp->content = new;
}

void	remove_var(t_list *var_list, char	*name)
{
	t_list	*tmp;
	t_list	*before_tmp;
	char	*tmp_name;

	tmp = var_list;
	while (tmp)
	{
		tmp_name = (char *)tmp->content;
		if (!ft_strncmp(name, tmp_name, name_len(tmp_name)))
			break ;
		before_tmp = tmp;
		tmp = tmp->next;
	}
	before_tmp->next = tmp->next;
	ft_lstdelone(tmp, free);
}
