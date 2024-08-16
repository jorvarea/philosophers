/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:11:50 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/16 18:49:59 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

static bool	check_finish_condition(t_philo *philo, int t_ms)
{
	bool	finished;

	if (t_ms + philo->time2eat <= philo->death_time)
	{
		sem_wait(philo->finished_eating_sem);
		
		sem_post(philo->finished_eating_sem);
	}
	else
	{
		usleep(philo->death_time - t_ms);
	}
	finished = t_ms > philo->death_time + 1;
	if (finished)
		philo->state = DEAD;
	else if (!finished && philo->meals_needed >= 0
		&& philo->meals_had >= philo->meals_needed)
	{
		finished = all_completed_meals(philo);
		if (finished)
			philo->state = FINISHED;
	}
	return (finished);
}

static void	*watcher_routine(void *watcher_void)
{
	t_watcher	*watcher;
	int		t_ms;

	watcher = (t_watcher *)watcher_void;
	sem_wait(watcher->finished_sem);
	while (!watcher->finished)
	{
		// Work in progress
		t_ms = get_time_ms(watcher->philo);
		if (t_ms >= 0)
			watcher->finished = check_finish_condition(watcher->philo, t_ms);
		else
			printf("Error: Watcher couldn't get current time\n");
		sem_post(watcher->finished_sem);
		sem_wait(watcher->finished_sem);
	}
	sem_post(watcher->finished_sem);
	kill_them_all(watcher->philo);
	return (NULL);
}

void init_watchers(t_data *data, t_philo *philo)
{
	t_watcher	*watchers;
	bool		stop;

	watchers = safe_malloc(data->n_philo * sizeof(t_watcher));
	stop = false;
	while (!stop)
	{
		watchers[philo->id].watcher_name = generate_watcher_sem_name(philo->id);
		watchers[philo->id].finished_sem = sem_open(watchers[philo->id].watcher_name, O_CREAT, 0600, 1);
		watchers[philo->id].finished = false;
		pthread_create(&watchers[philo->id].thread_id, NULL, watcher_routine, philo);
		philo = philo->next;
		if (philo->id == 0)
			stop = true;
	}
	wait_watchers(watchers, data->n_philo);
	free_watchers(watchers);
}