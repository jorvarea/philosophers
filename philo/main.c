/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:45:15 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/10 20:28:18 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	parse_input(t_data *data, char **args, int n_args)
{
	data->n_philo = (unsigned int)ft_atoi(args[0]);
	data->time2die = (unsigned int)ft_atoi(args[1]);
	data->time2eat = (unsigned int)ft_atoi(args[2]);
	data->time2sleep = (unsigned int)ft_atoi(args[3]);
	if (n_args == 5)
		data->num_meals = (unsigned int)ft_atoi(args[4]);
}

static void	get_time_program_start(t_data *data)
{
	if (gettimeofday(&data->start_timestamp, NULL) != 0)
	{
		printf("Error: Could not get time of the day\n");
		data->start_timestamp.tv_sec = 0;
		data->start_timestamp.tv_usec = 0;
	}
}

static void	wait_threads(t_philo *philo)
{
	while (philo)
	{
		pthread_join(philo->thread_id, NULL);
		philo = philo->next;
		if (philo->id == 0)
			return ;
	}
}

static void free_memory(t_philo *philo)
{
	t_philo *next;

	while (philo)
	{
		pthread_mutex_destroy(&philo->fork);
		next = philo->next;
		free(philo);
		philo = next;
		if (philo->id == 0)
			return ;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo_l;

	if (argc == 5 || argc == 6)
	{
		parse_input(&data, &argv[1], argc - 1);
		get_time_program_start(&data);
		philo_l = create_philosophers(&data);
		if (!philo_l)
			return (EXIT_FAILURE);
		wait_threads(philo_l);
		free_memory(philo_l);
	}
	else
		printf("Error: Incorrect number of arguments\n");
	return (0);
}
