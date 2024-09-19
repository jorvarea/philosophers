/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:45:15 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/19 18:40:51 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	parse_input(t_data *data, char **args, int n_args)
{
	bool	valid_input;

	data->n_philo = ft_atoi(args[0]);
	data->time2die = ft_atoi(args[1]);
	data->time2eat = ft_atoi(args[2]);
	data->time2sleep = ft_atoi(args[3]);
	valid_input = data->n_philo >= 0 && data->time2die >= 0
		&& data->time2eat >= 0 && data->time2sleep >= 0;
	if (valid_input && n_args == 5)
	{
		data->num_meals = ft_atoi(args[4]);
		valid_input = data->num_meals >= 0;
	}
	else
		data->num_meals = -1;
	if (!valid_input)
		printf("Error: Arguments should be positive integers\n");
	return (valid_input);
}

static void	init_forks_sem(t_data *data)
{
	sem_unlink("/forks");
	data->forks_sem = sem_open("/forks", O_CREAT, 0600, data->n_philo);
	if (data->forks_sem == SEM_FAILED)
	{
		printf("Error: sem_open failed\n");
		exit(EXIT_FAILURE);
	}
}

static void	free_memory(t_data *data)
{
	sem_close(data->forks_sem);
	sem_unlink("/forks");
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo_l;
	t_watcher	*watchers;

	if (argc == 5 || argc == 6)
	{
		if (!parse_input(&data, &argv[1], argc - 1))
			return (EXIT_FAILURE);
		init_forks_sem(&data);
		philo_l = create_philosophers(&data);
		get_time_program_start(&data);
		if (data.n_philo == 1)
			start_one_philo_routine(&data, philo_l);
		else
			start_philo_routines(&data, philo_l);
		watchers = init_watchers(&data, philo_l);
		monitor_watchers(watchers, data.n_philo);
		free_memory(&data);
	}
	else
		printf("Error: Incorrect number of arguments\n");
	return (0);
}
