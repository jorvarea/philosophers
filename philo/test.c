/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:03:35 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/28 18:23:33 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	test_printing(t_data *data, int n_times)
{
	t_philo	philo;
	int		i;

	i = 0;
	while (i < n_times)
	{
		philo.id = i;
		philo.state = i % 6;
		print_state(data, &philo);
		i++;
	}
}
