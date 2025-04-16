Dining Philosophers Problem Simulation
This project is a simulation of the classic Dining Philosophers Problem, implemented in C using POSIX threads.
The goal is to model concurrent behavior and synchronization challenges in a multithreaded environment.
Each philosopher is represented by a thread that cycles between thinking, eating, and sleeping, while
competing for shared resources (forks). The simulation handles potential deadlocks and ensures thread-safe
operations through proper synchronization techniques.

How to run:
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

The optional 5th argument (number_of_times_each_philosopher_must_eat) can be used to stop the simulation once all
philosophers have eaten the specified number of times.

Example:
./philo 5 800 200 200

./philo 5 800 200 200 3

