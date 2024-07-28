/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:03:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/28 18:04:46 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	test_printing(t_data *data)
{
	t_philo	philo;
	int		n_times;
	int		i;

	i = 0;
	while (n_times)
	{
		philo.id = i;
		philo.state = i % 6;
		print_state(&data, &philo);
		i++;
	}
}
