/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:44:22 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 23:38:52 by jorvarea         ###   ########.fr       */
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
		philo->death_time = t_ms + philo->time2die;
	else
		printf("Error: Couldn't get current time\n");
}

void	philo_eat(t_philo *philo)
{
    if (philo->state != DEAD && philo->state != FINISHED)
    {
        pthread_mutex_lock(&philo->state_lock);
        pick_left_fork(philo);
        pick_right_fork(philo);
        philo->state = EATING;
        print_state(philo);
        pthread_mutex_unlock(&philo->state_lock);
        usleep(philo->time2eat * 1000);
        pthread_mutex_unlock(&philo->fork);
        pthread_mutex_unlock(&philo->next->fork);
        pthread_mutex_lock(&philo->state_lock);
        philo->meals_had++;
        update_death_time(philo);
        pthread_mutex_unlock(&philo->state_lock);
    }
}

void	philo_sleep(t_philo *philo)
{
    if (philo->state != DEAD && philo->state != FINISHED)
    {
        pthread_mutex_lock(&philo->state_lock);
        philo->state = SLEEPING;
        print_state(philo);
        pthread_mutex_unlock(&philo->state_lock); 
        usleep(philo->time2sleep * 1000);
    }
}
