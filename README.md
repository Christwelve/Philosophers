# Philosophers #
### Multithreading
> Multithreading is a technique to run different tasks at the same time in the same process.


![philo](https://github.com/Christwelve/Philosophers/assets/39922270/28762a1d-c89b-4ad2-b5ea-ab6119636ed7)

## Topic
Think of multithreading as several people working together on one Excel sheet, it makes the work faster. But if two people change the same value at the same time, there will be a data race. 
To prevent this, we use a tool called Mutex. Think of each value as a box with a key. Only the person who has the key can read or use the value. 
If someone else wants to access the same value, they must wait until the key is available again.

## Visualization 
To illustrate multithreading, we have a scenario where a certain number of people (philosophers) are sitting around a table, each with a fork. In the middle of the table is a pot of spaghetti and to eat you need two forks, so they need to use a fork to their left to eat. You can set the time to eat, to die and to sleep to find a setting where no philo dies. Each philo is a thread.  

## How to use
```
 git clone
 cd Philosophers
 make
 ./philo <nbr_philos> <time_to_die> <time_to_eat> <time_to_sleep> (<nbr_must_eat>) 
 example: ./philo 100 150 60 60
```
>Limitation nbr_philos 200, time_to_die and time_to_eat 60ms

The last parameter is optional to specify how many times each philo must eat before the program stops. 


