/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:35:09 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/26 13:37:31 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_stack	*createstack(unsigned int capacity)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = (pthread_mutex_t *)malloc(stack->capacity * sizeof(pthread_mutex_t));
	return (stack);
}

int	isfull(t_stack *stack)
{
	return (stack->top == (int)stack->capacity - 1);
}

int	isempty(t_stack *stack)
{
	return (stack->top == -1);
}

pthread_mutex_t	pop(t_stack *stack)
{
	if (!isempty(stack))
	    return (stack->array[stack->top--]);
    return stack->array[stack->top];
}

void	push(t_stack *stack, pthread_mutex_t topush)
{
	if (isfull(stack))
		return ;
	stack->array[++stack->top] = topush;
}

// pthread_mutex_t	peek(t_stack *stack)
// {
//     pthread_mutex_t ret;
// 	if (isempty(stack))
// 		return (ret);
// 	return (stack->array[stack->top]);
// }