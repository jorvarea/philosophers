/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:59:44 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/19 19:22:05 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*watcher_routine(void *watcher_void)
{
	t_watcher	*watcher;
	int			status;

	watcher = (t_watcher *)watcher_void;
	if (waitpid(watcher->philo->pid, &status, 0) == -1)
	{
		printf("Error: waitpid failed\n");
		exit(EXIT_FAILURE);
	}
	if (WEXITSTATUS(status) == EXIT_FAILURE)
	{
		sem_wait(watcher->dead_sem);
		watcher->dead = true;
		sem_post(watcher->dead_sem);
	}
	else if (WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		sem_wait(watcher->completed_meals_sem);
		watcher->completed_meals = true;
		sem_post(watcher->completed_meals_sem);
	}
	return (NULL);
}
