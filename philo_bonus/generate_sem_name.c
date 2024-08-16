/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_sem_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:48:16 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/16 17:18:06 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*generate_sem_name(int philo_id)
{
	char	*name;
	char	*id_str;

	id_str = ft_itoa(philo_id);
	name = ft_strjoin("/finished_eating_sem_philo_", id_str);
	free(id_str);
	return (name);
}

char	*generate_watcher_sem_name(int philo_id)
{
	char	*name;
	char	*id_str;

	id_str = ft_itoa(philo_id);
	name = ft_strjoin("/watcher_", id_str);
	free(id_str);
	return (name);
}
