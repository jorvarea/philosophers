/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_routines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:17:36 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/06 12:11:34 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	start_odd_philos(t_philo *philo)
{
	bool	stop;

	stop = false;
	while (!stop)
	{
		if (philo->id % 2 != 0)
		{
			philo->pid = safe_fork();
			if (philo->pid == 0)
				philo_routine(philo);
		}
		philo = philo->next;
		if (philo->id == 0)
			stop = true;
	}
}

void	start_philo_routines(t_data *data, t_philo *philo)
{
	bool	stop;

	stop = false;
	while (!stop)
	{
		philo->death_time = data->time2die;
		philo->start_timestamp = data->start_timestamp;
		if (philo->id % 2 == 0)
		{
			philo->pid = safe_fork();
			if (philo->pid == 0)
				philo_routine(philo);
		}
		philo = philo->next;
		if (philo->id == 0)
			stop = true;
	}
	usleep(WAIT);
	start_odd_philos(philo);
}
