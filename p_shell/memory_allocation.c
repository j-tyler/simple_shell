#include "shell.h"
/**
 * _free - frees memory and removes address from defer'd free list
 * @address: address to free
 */
void _free(void *address)
{
	defer_free(address);
	free(address);
}
/**
 * defer_free - sets an address to be free'd on exit, removes from list if exists
 * @address: address to set
 */
void defer_free(void *address)
{
	static addr_list list = {NULL, NULL};
	addr_list *tmp;

	tmp = &list;
	/* If not given signal to free all, and address not already in list, add it */
	if (address != FREE_ADDRESSES && !clear_addr_list_node(tmp, address))
	{
		while (1)
		{
			if (tmp->address == NULL)
			{
				tmp->address = address;
				return;
			}
			else if (tmp->next == NULL)
			{
				add_addr_list_node(tmp, address);
				return;
			}
			tmp = tmp->next;
		}
	}
	else /*free all addresses*/
	{
		free_addr_list(list.next);
		if (list.address != NULL)
			free(list.address);
	}
}
/**
 * clear_addr_list_node - clear an address from the list
 * @list: addr_list list
 * @address: address to search and clear
 *
 * Return: 0 if address is found and cleared, 1 if no match is found
*/
int clear_addr_list_node(addr_list *list, void *address)
{
	while (list != NULL)
	{
		if (list->address == address)
		{
			list->address = NULL;
			return (0);
		}
		list = list->next;
	}
	return (1);
}
/**
 * add_addr_list_node - add a node to the end of an addr_list list
 * @list: addr_list list
 * @address: address to add to node
 */
void add_addr_list_node(addr_list *list, void *address)
{
	addr_list *node;

	node = safe_malloc(sizeof(addr_list));
	node->address = address;
	list->next = node;
}
/**
 * free_addr_list - free the addr_list and all addresses stored
 * @list: the addr_list to free
 */
void free_addr_list(addr_list *list)
{
	addr_list *tmp;

	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		if (tmp->address != NULL)
			free(tmp->address);
		free(tmp);
	}
}
