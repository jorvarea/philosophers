/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:44:22 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/16 16:17:59 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	pick_left_fork(t_philo *philo)
{
	sem_wait(philo->forks_sem);
	philo->state = TAKEN_FORK;
	print_state(philo);
}

static void	pick_right_fork(t_philo *philo)
{
	sem_wait(philo->forks_sem);
	philo->state = TAKEN_BOTH_FORKS;
	print_state(philo);
}

void	philo_eat(t_philo *philo)
{
	pick_left_fork(philo);
	pick_right_fork(philo);
	philo->state = EATING;
	print_state(philo);
	usleep(philo->time2eat * 1000);
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
}

void	philo_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	print_state(philo);
	usleep(philo->time2sleep * 1000);
}
