/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:11:50 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 22:35:44 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	finish_threads(t_philo *philo)
{
	while (philo->state != FINISHED && philo->state != DEAD)
	{
		pthread_mutex_lock(&philo->state_lock);
		philo->state = FINISHED;
		pthread_mutex_unlock(&philo->state_lock);
		philo = philo->next;
	}
}

static bool	all_completed_meals(t_philo *philo)
{
	bool	all_completed;
	int		initial_id;

	all_completed = true;
	initial_id = philo->id;
	while (all_completed)
	{
		if (philo->meals_had < philo->meals_needed)
			all_completed = false;
		philo = philo->next;
		if (philo->id == initial_id)
			return (all_completed);
	}
	return (all_completed);
}

static bool	check_finish_condition(t_philo *philo, int t_ms)
{
	bool	finished;

	pthread_mutex_lock(&philo->state_lock);
	finished = t_ms > philo->death_time;
	if (finished)
		philo->state = DEAD;
	else if (!finished && philo->meals_needed >= 0
		&& philo->meals_had >= philo->meals_needed)
	{
		finished = all_completed_meals(philo);
		if (finished)
			philo->state = FINISHED;
	}
	pthread_mutex_unlock(&philo->state_lock);
	return (finished);
}

void	*watcher_routine(void *philo_void)
{
	t_philo	*philo;
	bool	stop;
	int		t_ms;

	philo = (t_philo *)philo_void;
	stop = false;
	while (!stop)
	{
		t_ms = get_time_ms(philo);
		if (t_ms >= 0)
			stop = check_finish_condition(philo, t_ms);
		else
			printf("Error: Watcher couldn't get current time\n");
		philo = philo->next;
	}
	finish_threads(philo);
	return (NULL);
}
