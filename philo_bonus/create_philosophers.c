/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:27:58 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/05 13:14:23 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philo(t_data *data, t_philo *curr_philo, t_philo *prev_philo,
		int id)
{
	curr_philo->id = id;
	curr_philo->meals_needed = data->num_meals;
	curr_philo->meals_had = 0;
	curr_philo->state = THINKING;
	curr_philo->time2die = data->time2die;
	curr_philo->time2eat = data->time2eat;
	curr_philo->time2sleep = data->time2sleep;
	curr_philo->forks_sem = data->forks_sem;
	if (id != 0)
	{
		curr_philo->prev = prev_philo;
		prev_philo->next = curr_philo;
	}
}

void	make_list_circular(t_philo *philo_list, t_philo *curr_philo)
{
	curr_philo->next = philo_list;
	philo_list->prev = curr_philo;
}

t_philo	*create_philosophers(t_data *data)
{
	t_philo	*philo_list;
	t_philo	*curr_philo;
	t_philo	*prev_philo;
	int		i;

	i = 0;
	while (i < data->n_philo)
	{
		curr_philo = (t_philo *)safe_malloc(sizeof(t_philo));
		if (i == 0)
		{
			philo_list = curr_philo;
			curr_philo->prev = NULL;
		}
		init_philo(data, curr_philo, prev_philo, i);
		prev_philo = curr_philo;
		i++;
	}
	make_list_circular(philo_list, curr_philo);
	return (philo_list);
}
