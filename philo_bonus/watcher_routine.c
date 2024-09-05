/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:11:50 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/05 13:42:43 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static sem_t init_sem_finished(void)
{
	sem_t sem;
	
	sem = sem_open("/finished", O_CREAT, 0600, 0);
	if (sem == SEM_FAILED)
	{
		printf("Error: sem_open failed\n");
		exit(EXIT_FAILURE);
	}
	return (sem);
}

static void	wait_watchers(pthread_t *watchers, int n_watchers)
{
	int i;

	i = 0;
	while (i < n_watchers)
		pthread_join(watchers[i++], NULL);
}

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

static void	update_death_time(t_philo *philo)
{
	int	t_ms;

	t_ms = get_time_ms(philo);
	if (t_ms >= 0)
		philo->death_time = t_ms + philo->time2die;
	else
		printf("Error: Couldn't get current time\n");
}

static void	*watcher_routine(void *watcher_void)
{
	t_watcher	*watcher;
	int		t_ms;

	watcher = (t_watcher *)watcher_void;
	waitpid(watcher->philo->pid);
	kill_them_all(watcher->philo);
	return (NULL);
}

void init_watchers(t_data *data, t_philo *philo)
{
	t_watcher	*watchers;
	sem_t		watcher_finished;
	bool		stop;

	watchers = safe_malloc(data->n_philo * sizeof(t_watcher));
	watcher_finished = init_sem_finished();
	stop = false;
	while (!stop)
	{
		watchers[philo->id].finished = watcher_finished;
		watchers[philo->id].philo = philo;
		if (pthread_create(&watchers[philo->id].thread_id, NULL, watcher_routine, &watchers[philo->id]) != 0)
		{
			printf("Error: pthread_failed\n");
			exit(EXIT_FAILURE);
		}
		philo = philo->next;
		if (philo->id == 0)
			stop = true;
	}
	wait_watchers(watchers, data->n_philo);
	free_watchers(watchers);
}