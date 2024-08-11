/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:06:10 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 22:19:18 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	pick_left_fork(t_philo *philo)
{
	philo->state = TAKEN_FORK;
	print_state(philo);
}

static void	*one_philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	pthread_mutex_lock(&philo->state_lock);
	pick_left_fork(philo);
	while (philo->state != DEAD && philo->state != FINISHED)
	{
		pthread_mutex_unlock(&philo->state_lock);
		usleep(100);
		pthread_mutex_lock(&philo->state_lock);
	}
	print_state(philo);
	pthread_mutex_unlock(&philo->state_lock);
	return (NULL);
}

void	start_one_philo_routine(t_data *data, t_philo *philo)
{
	philo->death_time = data->time2die;
	philo->start_timestamp = data->start_timestamp;
	pthread_create(&philo->thread_id, NULL, one_philo_routine, philo);
}
