#!/bin/bash

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s -q ./philo_bonus $1 $2 $3 $4 $5
