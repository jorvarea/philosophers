/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:25:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 00:59:53 by jorvarea         ###   ########.fr       */
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
		pick_right_fork(philo);
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

void	start_philo_routines(t_data *data, t_philo *philo)
{
    bool stop;
    
    stop = false;
	while (!stop)
	{
		philo->death_time = data->time2die;
		philo->start_timestamp = data->start_timestamp;
        if (philo->id % 2 == 0)
		    pthread_create(&philo->thread_id, NULL, philo_routine, philo);
		philo = philo->next;
		if (philo->id == 0)
			stop = true;
	}
    while (!stop)
	{
        printf("id: \n", philo->id);
        if (philo->id % 2 != 0)
		    pthread_create(&philo->thread_id, NULL, philo_routine, philo);
		philo = philo->next;
		if (philo->id == 0)
			stop = true;
	}
}
