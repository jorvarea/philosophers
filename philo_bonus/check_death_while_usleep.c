/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_while_usleep.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:45:42 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/19 18:49:22 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_death_while_usleep(t_philo *philo, int time2action)
{
	int	t_ms;

	t_ms = get_time_ms(philo);
	if (t_ms + time2action > philo->death_time)
	{
		usleep((philo->death_time - t_ms) * 1000);
		philo->state = DEAD;
		print_state(philo);
		exit(EXIT_FAILURE);
	}
	else
		usleep(time2action * 1000);
}
