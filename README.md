# Multilevel-queue
Put process to be executed in first queue(8 quantum time) or the second queue(16 quantum time) or the third queue with unbounded time with an algorithm. 

Enter a process to a first queue if it time (quantum) fits than it's run in the first queue if not it will execute 8 quantum time in the first queue .
And the remaining time 16 quantum time of it will be executed in the second queue if there is remaining time.
so it will choose randomly between the first queue and the third queue to execute the remaining time in it.
8 in first queue and the third queue will take all no bounded time.
