/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpersboss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:26:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/12 12:27:16 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Lee si la simulación debe parar
// necesita mutex porq simulation_stop es leido por multiples hilos
// y porque es escrito por el boss, sin mutex hay race condition
int should_stop(t_program *program)
{
    int stop;
    
    pthread_mutex_lock(&program->stop_mutex);
    stop = program->simulation_stop;
    pthread_mutex_unlock(&program->stop_mutex);
    return (stop);
}

//Activa la señal de parada de la simulación (cuando detecta una muerte o completaron comidas)
//necesita mutex xq simulation_stop es leido por otros hilos y tmb lo escribe el boss.
void set_stop(t_program *program)
{
    pthread_mutex_lock(&program->stop_mutex);
    program->simulation_stop = 1;
    pthread_mutex_unlock(&program->stop_mutex);
}
//Lee cuándo fue la última vez que este filósofo comió
//necesita mutex xq last_meal_time es leido por el boss y escrito por el filosofo en eating
// se le pasa t_philo porque etsamos diciendo: dame la ultima comida de este filosofo
long long get_last_meal(t_philo *philo)
{
    long long last_meal;
    
    pthread_mutex_lock(&philo->program->meal_mutex);
    last_meal = philo->last_meal_time;
    pthread_mutex_unlock(&philo->program->meal_mutex);
    return (last_meal);
}
//contabiliza cuantas comidas han hecho
int get_meals_eaten(t_philo *philo)
{
    int meals;

    pthread_mutex_lock(&philo->program->meal_mutex);
    meals = philo->meals_eaten;
    pthread_mutex_unlock(&philo->program->meal_mutex);
    return (meals);
}
