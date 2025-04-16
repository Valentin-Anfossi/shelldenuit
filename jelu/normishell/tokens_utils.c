#include "minishell.h"

t_token	**create_tokenlst(void)
{
	t_token	**tokens;

	tokens = (t_token **)malloc(sizeof(t_token *));
	*tokens = NULL;
	return (tokens);
}

t_token	*create_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->type = 0;
	new_token->content = NULL;
	new_token->next = NULL;
	return (new_token);
}

//Return last token from lst
t_token	*token_last(t_token *lst)
{
	t_token	*list;

	if (!lst)
		return (0);
	list = lst;
	while (list->next)
		list = list->next;
	return (list);
}

//Add token to the back of lst
void	token_add_back(t_token **lst, t_token *token)
{
	t_token	*last;

	if (!lst || !token)
		return ;
	if (*lst == 0)
		*lst = token;
	else
	{
		last = token_last(*lst);
		last->next = token;
	}
}

void	delete_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	return ;
}
