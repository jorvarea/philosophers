/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:45:15 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/28 13:30:57 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	parse_input(t_data *data, char **args, int n_args)
{
	data->n_philo = (unsigned int)ft_atoi(args[0]);
	data->time2die = (unsigned int)ft_atoi(args[1]);
	data->time2die = (unsigned int)ft_atoi(args[2]);
	data->time2sleep = (unsigned int)ft_atoi(args[3]);
	if (n_args == 5)
		data->num_meals = (unsigned int)ft_atoi(args[4]);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		parse_input(&data, &argv[1], argc - 1);
	}
	else
		printf("Error: Incorrect number of arguments\n");
	return (0);
}
