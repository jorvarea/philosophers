/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:22:03 by jorvarea          #+#    #+#             */
/*   Updated: 2024/08/11 21:23:48 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ------------------- EXT LIBRARIES ------------------- //

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

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
	THINKING = 0,
	TAKEN_FORK = 1,
	TAKEN_BOTH_FORKS = 2,
	EATING = 3,
	SLEEPING = 4,
	DEAD = 5
}					t_state;

// --------------------- STRUCTURES -------------------- //

typedef struct s_data
{
	int				n_philo;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				num_meals;
	struct timeval	start_timestamp;
}					t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	t_state			state;
	pthread_mutex_t	fork;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	finish_condition_lock;
	pthread_mutex_t	death_time_lock;
	int				meals_needed;
	int				meals_had;
	int				death_time;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	bool			finished;
	struct timeval	start_timestamp;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

// ----------------------------------------------------- //
//                     MAIN FUNCTIONS                    //
// ----------------------------------------------------- //

t_philo				*create_philosophers(t_data *data);
void				*philo_routine(void *philo_void);
void				*watcher_routine(void *philo_void);
void				start_philo_routines(t_data *data, t_philo *philo);
void				start_one_philo_routine(t_data *data, t_philo *philo);

// ----------------------- UTILS ----------------------- //

void				get_time_program_start(t_data *data);
int					get_time_ms(t_philo *philo);
void				print_state(t_philo *philo);
void				print_state_dead(t_philo *philo);
int					ft_atoi(const char *str);

#endif /* PHILOSOPHERS_H */
