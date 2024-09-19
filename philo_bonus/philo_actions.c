/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:44:22 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/19 18:49:51 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	pick_fork(t_philo *philo)
{
	sem_wait(philo->forks_sem);
	philo->state = TAKEN_FORK;
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
	pick_fork(philo);
	pick_fork(philo);
	philo->state = EATING;
	update_death_time(philo);
	print_state(philo);
	check_death_while_usleep(philo, philo->time2eat);
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
}

void	philo_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	print_state(philo);
	check_death_while_usleep(philo, philo->time2sleep);
}
