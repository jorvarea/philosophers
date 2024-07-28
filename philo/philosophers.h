/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:22:03 by jorvarea          #+#    #+#             */
/*   Updated: 2024/07/28 18:22:13 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ------------------- EXT LIBRARIES ------------------- //

# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

// ------------------- COLOR MACROS -------------------- //

# define RESET "\033[0m"
# define WHITE "\033[0;37m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"
# define MAGENTA "\033[0;35m"
# define TURQUOISE "\033[0;36m"
# define BLACK "\033[0;30m"
# define GRAY "\033[1;30m"
# define LIGHT_RED "\033[1;31m"
# define LIGHT_GREEN "\033[1;32m"
# define LIGHT_YELLOW "\033[1;33m"
# define LIGHT_BLUE "\033[1;34m"
# define LIGHT_MAGENTA "\033[1;35m"
# define LIGHT_CYAN "\033[1;36m"
# define LIGHT_WHITE "\033[1;37m"

// ----------------------- ENUM ------------------------ //

typedef enum e_state
{
	TAKEN_FORK = 0,
	TAKEN_BOTH_FORKS = 1,
	EATING = 2,
	SLEEPING = 3,
	THINKING = 4,
	DEAD = 5
}					t_state;

// --------------------- STRUCTURES -------------------- //

typedef struct s_data
{
	unsigned int	n_philo;
	unsigned int	time2die;
	unsigned int	time2eat;
	unsigned int	time2sleep;
	unsigned int	num_meals;
	struct timeval	start_timestamp;
}					t_data;

typedef struct s_philo
{
	int				id;
	t_state			state;
}					t_philo;

// ----------------------------------------------------- //
//                     MAIN FUNCTIONS                    //
// ----------------------------------------------------- //

void				print_state(t_data *data, t_philo *philo);
int					ft_atoi(const char *str);
void				test_printing(t_data *data, int n_times);

#endif /* PHILOSOPHERS_H */
