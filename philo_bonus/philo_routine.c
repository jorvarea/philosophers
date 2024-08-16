/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:25:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/16 17:07:17 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_routine(t_philo *philo)
{
	while (true)
	{
		sem_wait(philo->finished_eating_sem);
		philo_eat(philo);
		sem_post(philo->finished_eating_sem);
		philo_sleep(philo);
		philo->state = THINKING;
		print_state(philo);
	}
}
