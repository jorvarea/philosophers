/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_watchers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:37:28 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/12 19:08:03 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_watchers(t_watcher *watchers, int n_watchers)
{
	int	i;

	i = 0;
	while (i < n_watchers)
		pthread_join(watchers[i++].thread_id, NULL);
	sem_close(watchers[0].dead_sem);
	sem_unlink("/dead_sem");
	sem_close(watchers[0].completed_meals_sem);
	sem_unlink("/completed_meals_sem");
	free(watchers);
}

static void	kill_them_all(t_watcher *watchers, int n_watchers)
{
	int	i;

	i = 0;
	while (i < n_watchers)
		kill(watchers[i++].philo->pid, SIGKILL);
}

void	monitor_watchers(t_watcher *watchers, int nphilos)
{
	bool	stop;
	int		i;

	stop = false;
	while (!stop)
	{
		i = 0;
		while (i < nphilos)
		{
			sem_wait(watchers[i].dead_sem);
			sem_wait(watchers[i].completed_meals_sem);
			if (watchers[i].dead)
				stop = true;
			else if (*(watchers[i].nphilos_completed_meals) == nphilos)
				stop = true;
			sem_post(watchers[i].dead_sem);
			sem_post(watchers[i].completed_meals_sem);
			i++;
		}
	}
	kill_them_all(watchers, nphilos);
	free_watchers(watchers, nphilos);
}
