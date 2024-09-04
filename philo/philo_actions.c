/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:44:22 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/04 20:13:25 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	pick_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
    pthread_mutex_lock(&philo->state_lock);
    if (philo->state != DEAD && philo->state != FINISHED)
    {
        philo->state = TAKEN_FORK;
        print_state(philo);
    }
    pthread_mutex_unlock(&philo->state_lock);
}

static void	pick_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);
    pthread_mutex_lock(&philo->state_lock);
    if (philo->state != DEAD && philo->state != FINISHED)
    {
        philo->state = TAKEN_FORK;
        print_state(philo);
    }
    pthread_mutex_unlock(&philo->state_lock);
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
    if (philo->id % 2 == 0)
    {
        pick_left_fork(philo);
        pick_right_fork(philo);
    }
    else
    {
        pick_right_fork(philo);
        pick_left_fork(philo);
    }
    pthread_mutex_lock(&philo->state_lock);
    if (philo->state != DEAD && philo->state != FINISHED)
    {
        philo->state = EATING;
        update_death_time(philo);
        print_state(philo);
        pthread_mutex_unlock(&philo->state_lock);
        usleep(philo->time2eat * 1000);
        pthread_mutex_lock(&philo->state_lock);
        philo->meals_had++;
    }
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->next->fork);
    pthread_mutex_unlock(&philo->state_lock);
}

void	philo_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->state_lock);
    if (philo->state != DEAD && philo->state != FINISHED)
    {
        philo->state = SLEEPING;
        print_state(philo);
        pthread_mutex_unlock(&philo->state_lock);
        usleep(philo->time2sleep * 1000);
    }
    else
        pthread_mutex_unlock(&philo->state_lock);
}
