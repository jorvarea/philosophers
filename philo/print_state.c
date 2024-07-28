/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:44:58 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/28 13:44:37 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_message(suseconds_t time, int id, t_state state)
{
	if (state == TAKEN_FORK)
		printf("%s%d %d %s%s\n", MAGENTA, time, id, "has taken a fork", RESET);
	else if (state == EATING)
		printf("%s%d %d %s%s\n", GREEN, time, id, "is eating", RESET);
	else if (state == SLEEPING)
		printf("%s%d %d %s%s\n", GRAY, time, id, "is sleeping", RESET);
	else if (state == THINKING)
		printf("%s%d %d %s%s\n", TURQUOISE, time, id, "is thinking", RESET);
	else if (state == DEAD)
		printf("%s%d %d %s%s\n", RED, time, id, "died", RESET);
}

void	print_state(t_philo *philo, t_state state)
{
	struct timeval	timestamp;

	if (gettimeofday(&timestamp, NULL) == 0)
		print_message(timestamp.tv_usec, philo->id, state);
	else
		printf("Error: Could not get time of the day\n");
}
