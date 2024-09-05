/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:25:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/05 13:08:51 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool is_philo_dead(t_philo *philo)
{
	int t_ms;
	
	t_ms = get_time_ms(philo);
	return (t_ms > philo->death_time);
}

static bool had_enough_meals(t_philo *philo)
{
	return (philo->meals_had >= philo->meals_needed);
}

void	philo_routine(t_philo *philo)
{
	while (!is_philo_dead(philo) && !had_enough_meals(philo))
	{
		philo_eat(philo);
		if (!is_philo_dead(philo) && !had_enough_meals(philo))
			philo_sleep(philo);
		if (!is_philo_dead(philo) && !had_enough_meals(philo))
		{
			philo->state = THINKING;
			print_state(philo);
		}
	}
	if (is_philo_dead(philo))
	{
		philo->state = DEAD;
		print_state(philo);
		exit(EXIT_FAILURE);
	}
	else
	{
		philo->state = FINISHED;
		print_state(philo);
		exit(EXIT_SUCCESS);
	}
}
