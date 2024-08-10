/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:03:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/10 19:36:06 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	test_print_philos(t_philo *philo)
{
	while (philo)
	{
		if (philo->state == TAKEN_FORK)
			printf("%sid: %d, time_death: %d, %s%s\n", MAGENTA, philo->id,
				philo->death_time, "TAKEN_A_FORK", RESET);
		else if (philo->state == TAKEN_BOTH_FORKS)
			printf("%sid: %d, time_death: %d, %s%s\n", MAGENTA, philo->id,
				philo->death_time, "TAKEN_BOTH_FORKS", RESET);
		else if (philo->state == EATING)
			printf("%sid: %d, time_death: %d, %s%s\n", GREEN, philo->id,
				philo->death_time, "EATING", RESET);
		else if (philo->state == SLEEPING)
			printf("%sid: %d, time_death: %d, %s%s\n", GRAY, philo->id,
				philo->death_time, "SLEEPING", RESET);
		else if (philo->state == THINKING)
			printf("%sid: %d, time_death: %d, %s%s\n", TURQUOISE, philo->id,
				philo->death_time, "THINKING", RESET);
		else if (philo->state == DEAD)
			printf("%sid: %d, time_death: %d, %s%s\n", RED, philo->id,
				philo->death_time, "DEAD", RESET);
		philo = philo->next;
		if (philo->id == 0)
			return ;
	}
}
