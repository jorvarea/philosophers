/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_watchers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:11:50 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/19 19:20:31 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static sem_t	*init_sem(char *name, int n)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, 0600, n);
	if (sem == SEM_FAILED)
	{
		printf("Error: sem_open failed\n");
		exit(EXIT_FAILURE);
	}
	return (sem);
}

t_watcher	*init_watchers(t_data *data, t_philo *philo)
{
	t_watcher	*watchers;
	bool		stop;
	sem_t		*dead_sem;
	sem_t		*completed_meals_sem;

	watchers = safe_malloc(data->n_philo * sizeof(t_watcher));
	dead_sem = init_sem("/dead_sem", 1);
	completed_meals_sem = init_sem("/completed_meals_sem", 1);
	stop = false;
	while (!stop)
	{
		watchers[philo->id].dead = false;
		watchers[philo->id].philo = philo;
		watchers[philo->id].completed_meals = false;
		watchers[philo->id].dead_sem = dead_sem;
		watchers[philo->id].completed_meals_sem = completed_meals_sem;
		safe_pthread(&watchers[philo->id].thread_id, watcher_routine,
			&watchers[philo->id]);
		philo = philo->next;
		if (philo->id == 0)
			stop = true;
	}
	return (watchers);
}
