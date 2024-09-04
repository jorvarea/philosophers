/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:06:10 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/04 21:57:15 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	pick_left_fork(t_philo *philo)
{
	philo->state = TAKEN_FORK;
	print_state(philo);
}

static void	one_philo_routine(t_philo *philo)
{
	pick_left_fork(philo);
	while (!is_philo_dead(philo))
		usleep(100);
	philo->state = DEAD;
	print_state(philo);
}

void	start_one_philo_routine(t_data *data, t_philo *philo)
{
	philo->death_time = data->time2die;
	philo->start_timestamp = data->start_timestamp;
	philo->pid = safe_fork();
	if (philo->pid == 0)
		one_philo_routine(philo);
	usleep(WAIT);
}
