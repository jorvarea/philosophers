/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pthread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:16:47 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/06 12:20:08 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	safe_pthread(pthread_t *thread_id, void *routine, void *data)
{
	if (pthread_create(thread_id, NULL, routine, data) != 0)
	{
		printf("Error: pthread_failed\n");
		exit(EXIT_FAILURE);
	}
}
