/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:45:15 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 15:05:41 by jorvarea         ###   ########.fr       */
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
	else
		data->num_meals = -1;
}

static void	free_memory(t_data *data, t_philo *philo)
{
	t_philo			*next;
	unsigned int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_detach(philo->thread_id);
		pthread_mutex_destroy(&philo->fork);
		next = philo->next;
		free(philo);
		philo = next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo_l;
	pthread_t	watcher;

	if (argc == 5 || argc == 6)
	{
		parse_input(&data, &argv[1], argc - 1);
		philo_l = create_philosophers(&data);
		if (!philo_l)
			return (EXIT_FAILURE);
		get_time_program_start(&data);
		if (data.n_philo == 1)
			start_one_philo_routine(&data, philo_l);
		else
			start_philo_routines(&data, philo_l);
		if (pthread_create(&watcher, NULL, watcher_routine, philo_l) != 0)
			return (EXIT_FAILURE);
		pthread_join(watcher, NULL);
		free_memory(&data, philo_l);
	}
	else
		printf("Error: Incorrect number of arguments\n");
	return (0);
}
