/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:44:58 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/28 18:02:33 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_message(t_data *data, struct timeval *timestamp, int id,
		t_state state)
{
	time_t		curr_sec;
	suseconds_t	curr_ms;
	suseconds_t	curr_usec;

	curr_sec = timestamp->tv_sec - data->start_timestamp.tv_sec;
	curr_usec = timestamp->tv_usec - data->start_timestamp.tv_usec;
	curr_ms = curr_usec / 1000;
	curr_usec = curr_usec % 1000;
	if (state == TAKEN_FORK || state == TAKEN_BOTH_FORKS)
		printf("%s%ld:%d:%-3d %d %s%s\n", MAGENTA, curr_sec, curr_ms, curr_usec,
			id, "has taken a fork", RESET);
	else if (state == EATING)
		printf("%s%ld:%d:%-3d %d %s%s\n", GREEN, curr_sec, curr_ms, curr_usec,
			id, "is eating", RESET);
	else if (state == SLEEPING)
		printf("%s%ld:%d:%-3d %d %s%s\n", GRAY, curr_sec, curr_ms, curr_usec,
			id, "is sleeping", RESET);
	else if (state == THINKING)
		printf("%s%ld:%d:%-3d %d %s%s\n", TURQUOISE, curr_sec, curr_ms,
			curr_usec, id, "is thinking", RESET);
	else if (state == DEAD)
		printf("%s%ld:%d:%-3d %d %s%s\n", RED, curr_sec, curr_ms, curr_usec, id,
			"died", RESET);
}

void	print_state(t_data *data, t_philo *philo)
{
	struct timeval	timestamp;

	if (gettimeofday(&timestamp, NULL) == 0)
		print_message(data, &timestamp, philo->id, philo->state);
	else
		printf("Error: Could not get time of the day\n");
}
