/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:25:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 21:53:45 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	update_death_time(t_philo *philo)
{
	int	t_ms;

	t_ms = get_time_ms(philo);
	if (t_ms >= 0)
		philo->death_time = t_ms + philo->time2die;
	else
		printf("Error: Couldn't get current time\n");
}

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	pthread_mutex_lock(&philo->state_lock);
	while (philo->state != DEAD && philo->state != FINISHED)
	{
		pthread_mutex_unlock(&philo->state_lock);
		philo_eat(philo);
		philo_sleep(philo);
		pthread_mutex_lock(&philo->state_lock);
		philo->state = THINKING;
		print_state(philo);
	}
	print_state(philo);
	pthread_mutex_unlock(&philo->state_lock);
	return (NULL);
}
