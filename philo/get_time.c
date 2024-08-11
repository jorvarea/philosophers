/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:25:55 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 01:32:22 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_time_program_start(t_data *data)
{
	if (gettimeofday(&data->start_timestamp, NULL) != 0)
	{
		printf("Error: Could not get time of the day\n");
		data->start_timestamp.tv_sec = 0;
		data->start_timestamp.tv_usec = 0;
	}
}

int	get_time_ms(t_philo *philo)
{
	struct timeval	timestamp;
	time_t			curr_sec;
	suseconds_t		curr_usec;
	suseconds_t		t_ms;

	t_ms = -1;
	if (gettimeofday(&timestamp, NULL) == 0)
	{
		curr_sec = timestamp.tv_sec - philo->start_timestamp.tv_sec;
		curr_usec = timestamp.tv_usec - philo->start_timestamp.tv_usec;
		t_ms = curr_sec * 1000 + curr_usec / 1000;
	}
	else
		printf("Error: Could not get time of the day\n");
	return (t_ms);
}
