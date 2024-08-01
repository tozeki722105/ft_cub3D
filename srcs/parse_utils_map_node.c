#include "parse.h"

t_map_node *make_new_map_node(char *str)
{
	t_map_node *new;

	
	new = (t_map_node *)malloc(sizeof(t_map_node));
	new->val = str;
	new->next = NULL;
	return (new);
}

t_map_node *find_last_map_node(t_map_node *ptr)
{
	while(ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void add_last_map_node(t_map_node **head, t_map_node *new)
{
	if (!(*head))
	{
		*head = new;
		return ;
	}
	find_last_map_node(*head)->next = new;
}

static void	free_map_node(t_map_node *map_node)
{
	free(map_node->val);
	free(map_node);
}

void	free_map_node_list(t_map_node *ptr)
{
	t_map_node *next_ptr;

	if (!ptr)
		return ;
	next_ptr = ptr->next;
	while (next_ptr)
	{
		free_map_node(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_map_node(ptr);
}