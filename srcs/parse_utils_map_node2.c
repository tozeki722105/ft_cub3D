#include "parse.h"

void	print_map_node(t_map_node *ptr)
{
	while (ptr)
	{
		printf("%s\n", ptr->val);
		ptr = ptr->next;
	}
}

static t_map_node *find_prev_of_first(t_map_node *ptr, char *trimed_node_val)
{
	t_map_node *prev;
	t_map_node *head = ptr;

	prev = NULL;
	while (ptr && ft_isequal(ptr->val, trimed_node_val))
	{
		prev = ptr;
		ptr = ptr->next;
	}
	return (prev);
}

static t_map_node *find_last(t_map_node *ptr, char *trimed_node_val)
{
	t_map_node *next_ptr;

	while (next_ptr)
	{
		if (!ft_isequal(ptr->val, trimed_node_val)
			&& ft_isequal(next_ptr->val, trimed_node_val))
		{
			while (next_ptr && ft_isequal(next_ptr->val, trimed_node_val))
				next_ptr = next_ptr->next;
			if (!next_ptr)
				return (ptr);
		}
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	return (ptr);
}

void	trim_map_list(t_map_node **head, char *trimed_node_val)
{
	t_map_node *prev_of_first;
	t_map_node *last;
	t_map_node *first;

	if (!head || !(*head) || !((*head)->next))
		return ;
	prev_of_first = find_prev_of_first(*head, trimed_node_val);
	last = find_last(*head, trimed_node_val);
	if (prev_of_first)
	{
		
		first = prev_of_first->next;
		prev_of_first->next = NULL;
		free_map_node_list(*head);
		*head = first;
	}
	free_map_node_list(last->next);
	last->next = NULL;
}