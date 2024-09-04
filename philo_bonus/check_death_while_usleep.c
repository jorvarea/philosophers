/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_philo_dead_while_usleep.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:45:42 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/04 21:51:34 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void check_death_while_usleep(int t_ms, t_philo *philo)
{
	int i;
	int	limit;

	limit = t_ms / 5;
	while (i < limit && !is_philo_dead(philo))
		usleep(5);
	if (is_philo_dead(philo))
	{
		philo->state = DEAD;
		print_state(philo);
		exit(EXIT_FAILURE);
	}
}
