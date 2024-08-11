/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:11:50 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 03:25:11 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	finish_threads(t_philo *philo)
{
	while (!philo->finished)
	{
		philo->finished = true;
		philo = philo->next;
	}
}

static void	check_finish_condition(t_philo *philo)
{
	if (philo->error_code != 0)
		printf("Error code: %d\n", philo->error_code);
    else if (philo->finished)
    {
        philo->state = DEAD;
        print_state(philo);
    }
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
		{
			philo->finished = (unsigned int)t_ms > philo->death_time
				|| philo->error_code != 0;
			stop = philo->finished;
			check_finish_condition(philo);
		}
		else
		{
			printf("Error: Watcher couldn't get current time\n");
			stop = true;
		}
		philo = philo->next;
	}
	finish_threads(philo);
	return (NULL);
}
