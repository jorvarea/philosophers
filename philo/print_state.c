/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:44:58 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/28 13:27:06 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_message(suseconds_t time, int id, t_action action)
{
	if (action == TAKEN_FORK)
		printf("%s%d %d %s%s\n", MAGENTA, time, id, "has taken a fork", RESET);
	else if (action == EATING)
		printf("%s%d %d %s%s\n", GREEN, time, id, "is eating", RESET);
	else if (action == SLEEPING)
		printf("%s%d %d %s%s\n", GRAY, time, id, "is sleeping", RESET);
	else if (action == THINKING)
		printf("%s%d %d %s%s\n", TURQUOISE, time, id, "is thinking", RESET);
	else if (action == DEAD)
		printf("%s%d %d %s%s\n", RED, time, id, "died", RESET);
}

void	print_state(t_philo *philo, t_action action)
{
	struct timeval	timestamp;

	if (gettimeofday(&timestamp, NULL) == 0)
		print_message(timestamp.tv_usec, philo->id, action);
	else
		printf("Error: Could not get time of the day\n");
}
