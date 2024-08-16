/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:44:58 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/12 11:55:48 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_message(struct timeval *start_timestamp,
		struct timeval *timestamp, int id, t_state state)
{
	time_t		curr_sec;
	suseconds_t	curr_usec;
	suseconds_t	t_ms;

	curr_sec = timestamp->tv_sec - start_timestamp->tv_sec;
	curr_usec = timestamp->tv_usec - start_timestamp->tv_usec;
	t_ms = curr_sec * 1000 + curr_usec / 1000;
	if (state == TAKEN_FORK || state == TAKEN_BOTH_FORKS)
		printf("%s%d %d %s%s\n", MAGENTA, t_ms, id, "has taken a fork", RESET);
	else if (state == EATING)
		printf("%s%d %d %s%s\n", GREEN, t_ms, id, "is eating", RESET);
	else if (state == SLEEPING)
		printf("%s%d %d %s%s\n", GRAY, t_ms, id, "is sleeping", RESET);
	else if (state == THINKING)
		printf("%s%d %d %s%s\n", TURQUOISE, t_ms, id, "is thinking", RESET);
	else if (state == DEAD)
		printf("%s%d %d %s%s\n", RED, t_ms, id, "died", RESET);
}

void	print_state(t_philo *philo)
{
	struct timeval	timestamp;

	if (gettimeofday(&timestamp, NULL) == 0)
		print_message(&philo->start_timestamp, &timestamp, philo->id,
			philo->state);
	else
		printf("Error: Could not get time of the day\n");
}
