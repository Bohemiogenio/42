*This project was created as part of the 42 curriculum by raulsanc.*

# Philosophers

> "I never thought philosophy could be so deadly."

## Description

Philosophers is a simulation of the classic **Dining Philosophers Problem**, a well-known concurrency problem in computer science originally formulated by Edsger Dijkstra.

A number of philosophers sit at a round table with a large bowl of spaghetti in the center. There is one fork between each pair of adjacent philosophers. To eat, a philosopher must pick up both the fork to their left and the fork to their right. Philosophers alternate between three states: **eating**, **sleeping**, and **thinking**.

The simulation stops when a philosopher dies of starvation (if they haven't started eating within `time_to_die` milliseconds since their last meal or the start of the simulation), or when all philosophers have eaten the required number of times.

**Key constraints:**
- No global variables allowed.
- Each philosopher is an independent thread.
- Each fork is protected by a mutex to prevent race conditions.
- No data races are permitted.
- A philosopher's death must be reported within 10 ms of the actual death.

## Instructions

### Requirements

- A C compiler (`cc`)
- POSIX threads library (`pthread`)
- GNU Make

### Compilation

The project files must be inside the `philo/` directory. To compile:

```bash
cd philo
make
```

This produces the `philo` executable. The Makefile supports the following rules:

| Rule     | Description                        |
|----------|------------------------------------|
| `make`   | Compile the project                |
| `make clean`  | Remove object files           |
| `make fclean` | Remove object files and binary|
| `make re`     | Full recompile                |

### Usage

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Time before a philosopher dies if they haven't started eating |
| `time_to_eat` (ms) | Time a philosopher spends eating (holds both forks during this time) |
| `time_to_sleep` (ms) | Time a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation ends when all philosophers have eaten this many times |

### Examples

```bash
# 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Same but stops after each philosopher has eaten 7 times
./philo 5 800 200 200 7

# Edge case: single philosopher (will always die, only one fork)
./philo 1 800 200 200
```

### Log format

Every state change is printed in the following format:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

Where `timestamp_in_ms` is the current time in milliseconds and `X` is the philosopher's number (1 to N).

## Resources

### Documentation & References

- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- `man pthread_create`, `man pthread_mutex_init`, `man gettimeofday`, `man usleep`

### Authorized functions

`memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

### AI Usage

AI tools (Claude) were used in this project for the following tasks:

- Generating this README file based on the project subject.
- Clarifying concepts around thread synchronization and mutex usage during the learning phase.

All code was written and understood by the student. AI-generated content was reviewed, tested, and validated before being used.
