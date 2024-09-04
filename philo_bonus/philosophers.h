/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:22:03 by jorvarea          #+#    #+#             */
/*   Updated: 2024/09/04 21:53:57 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ------------------- EXT LIBRARIES ------------------- //

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

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

// ----------------------- CONST ------------------------ //

# define WAIT 300

// ----------------------- ENUM ------------------------ //

typedef enum e_state
{
	THINKING = 0,
	TAKEN_FORK = 1,
	TAKEN_BOTH_FORKS = 2,
	EATING = 3,
	SLEEPING = 4,
	DEAD = 5,
	FINISHED = 6
}					t_state;

// --------------------- STRUCTURES -------------------- //

typedef struct s_data
{
	int				n_philo;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				num_meals;
	sem_t			*forks_sem;
	struct timeval	start_timestamp;
}					t_data;

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	t_state			state;
	char			*sem_name;
	sem_t			*finished_eating_sem;
	sem_t			*forks_sem;
	int				meals_needed;
	int				meals_had;
	int				death_time;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	struct timeval	start_timestamp;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

typedef struct s_watcher
{
	pthread_t	thread_id;
	t_philo		*philo;
	char		*watcher_name;
	sem_t		finished_sem;
	bool		finished;
}					t_watcher;

// ----------------------------------------------------- //
//                     MAIN FUNCTIONS                    //
// ----------------------------------------------------- //

t_philo				*create_philosophers(t_data *data);
void				philo_routine(t_philo *philo);
bool 				is_philo_dead(t_philo *philo);
void				watcher_routine(t_philo *philo_l);
void				start_philo_routines(t_data *data, t_philo *philo);
void				start_one_philo_routine(t_data *data, t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void 				check_death_while_usleep(int t_ms, t_philo *philo);

// ----------------------- UTILS ----------------------- //

void				get_time_program_start(t_data *data);
int					get_time_ms(t_philo *philo);
void				print_state(t_philo *philo);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
void				*safe_malloc(size_t size);
pid_t				safe_fork(void);
char				*generate_sem_name(int philo_id);
char				*generate_watcher_sem_name(int philo_id);
size_t				ft_strlen(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);

#endif /* PHILOSOPHERS_H */
