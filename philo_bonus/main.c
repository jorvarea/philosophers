/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:45:15 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/16 17:24:16 by jorvarea         ###   ########.fr       */
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

static void init_sem_forks(t_data *data)
{
	data->forks_sem = sem_open("/forks", O_CREAT, 0600, data->n_philo);
	if (data->forks_sem == SEM_FAILED)
	{
		printf("Error: sem_open failed\n");
		exit(EXIT_FAILURE);
	}
}

static void unlock_locked_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	pthread_mutex_lock(&philo->prev->state_lock);
	if (philo->state == EATING)
		pthread_mutex_unlock(&philo->fork);
	else if (philo->prev->state == EATING)
		pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->state_lock);
	pthread_mutex_unlock(&philo->prev->state_lock);
}

static void	free_memory(t_data *data, t_philo *philo)
{
	t_philo	*next;
	int		i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(philo->thread_id, NULL);
		unlock_locked_forks(philo);
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->state_lock);
		next = philo->next;
		free(philo->sem_name);
		free(philo);
		philo = next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo_l;

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
		// Work in progress
		watcher_routine(philo_l);
		free_memory(&data, philo_l);
	}
	else
		printf("Error: Incorrect number of arguments\n");
	return (0);
}
