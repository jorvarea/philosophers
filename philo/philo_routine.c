/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:25:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 21:29:51 by jorvarea         ###   ########.fr       */
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

static void	update_death_time(t_philo *philo)
{
	int	t_ms;

	t_ms = get_time_ms(philo);
	if (t_ms >= 0)
	{
		pthread_mutex_lock(&philo->death_time_lock);
		philo->death_time = t_ms + philo->time2die;
		pthread_mutex_unlock(&philo->death_time_lock);
	}
	else
		printf("Error: Couldn't get current time\n");
}

static void	philo_eat(t_philo *philo)
{
	pick_left_fork(philo);
	pick_right_fork(philo);
	philo->state = EATING;
	print_state(philo);
	usleep(philo->time2eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_lock(&philo->meals_lock);
	philo->meals_had++;
	pthread_mutex_unlock(&philo->meals_lock);
	update_death_time(philo);
}

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	pthread_mutex_lock(&philo->finish_condition_lock);
	while (!philo->finished)
	{
		pthread_mutex_unlock(&philo->finish_condition_lock);
		philo_eat(philo);
		philo->state = SLEEPING;
		print_state(philo);
		usleep(philo->time2sleep * 1000);
		philo->state = THINKING;
		print_state(philo);
		pthread_mutex_lock(&philo->finish_condition_lock);
	}
	pthread_mutex_unlock(&philo->finish_condition_lock);
	return (NULL);
}
