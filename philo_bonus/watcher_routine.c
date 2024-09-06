/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:59:44 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/06 12:24:39 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*watcher_routine(void *watcher_void)
{
	t_watcher	*watcher;
	int			status;

	watcher = (t_watcher *)watcher_void;
	waitpid(watcher->philo->pid, &status, 0);
	if (WEXITSTATUS(status) == 0)
	{
		sem_wait(watcher->dead_sem);
		watcher->dead = true;
		sem_post(watcher->dead_sem);
	}
	else if (WEXITSTATUS(status) == 1)
	{
		sem_wait(watcher->completed_meals_sem);
		watcher->nphilos_completed_meals += 1;
		sem_post(watcher->completed_meals_sem);
	}
	return (NULL);
}
