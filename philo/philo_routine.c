/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:25:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/10 19:50:02 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	pick_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo->state = TAKEN_FORK;
	print_state(philo);
}

static void	pick_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);
	philo->state = TAKEN_BOTH_FORKS;
	print_state(philo);
}

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	while (!philo->error && !philo->finished)
	{
		pick_left_fork(philo);
		print_state(philo);
		pick_right_fork(philo);
		print_state(philo);
		philo->state = EATING;
		print_state(philo);
		usleep(philo->time2eat * 1000);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		philo->state = SLEEPING;
		print_state(philo);
		usleep(philo->time2sleep * 1000);
		philo->state = THINKING;
		print_state(philo);
	}
	return (NULL);
}
