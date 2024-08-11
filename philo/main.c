/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:45:15 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/12 00:03:32 by jorvarea         ###   ########.fr       */
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
		if (!parse_input(&data, &argv[1], argc - 1))
			return (EXIT_FAILURE);
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
		if (pthread_join(watcher, NULL) != 0)
			return (EXIT_FAILURE);
		free_memory(&data, philo_l);
	}
	else
		printf("Error: Incorrect number of arguments\n");
	return (0);
}
