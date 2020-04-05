### C++ spinlock
```shell script
./cppspinlock-run-tests.sh
```

### C spinlock model checking example
Because [genmc](https://github.com/MPI-SWS/genmc) only supports C language.
```shell script
./cspinlock-run-checking.sh
```
```shell script
Number of complete executions explored: 16
Number of blocked executions seen: 2
Total wall-clock time: 0.01s
```

If we break the _synchronize-with_ relation (change memory model to `memory_order_relaxed` in [this](https://github.com/akhoroshev/model-checking-task/blob/master/cspinlock/main.c#L18) line)
```shell script
Error detected: Non-Atomic race!
Event (2, 5) conflicts with event (1, 4) in graph:
<-1, 0> main:
	(0, 0): B
	(0, 1): M
	(0, 2): M
	(0, 3): TC [forks 1] L.43
	(0, 4): Wna (t1, 1) L.43
	(0, 5): TC [forks 2] L.45
	(0, 6): Wna (t2, 2) L.45
	(0, 7): Rna (t1, 1) [(0, 4)] L.48
	(0, 8): TJ L.48
	(0, 9): Rna (t2, 2) [(0, 6)] L.49
	(0, 10): TJ L.49
<0, 1> thread_1:
	(1, 0): B
	(1, 1): Uacq (spinlock._Value, 0) [INIT] L.13
	(1, 2): Uacq (spinlock._Value, 1) L.13
	(1, 3): Wna (s_data_1, 1) L.27
	(1, 4): Wna (s_data_2, -1) L.28
	(1, 5): Wrlx (spinlock._Value, 0) L.18
	(1, 6): E
<0, 2> thread_2:
	(2, 0): B
	(2, 1): Uacq (spinlock._Value, 1) [(1, 2)] L.13
	(2, 2): Uacq (spinlock._Value, 1) L.13
	(2, 3): Uacq (spinlock._Value, 0) [(1, 5)] L.13
	(2, 4): Uacq (spinlock._Value, 1) L.13
	(2, 5): Rna (s_data_2, 0) [INIT] L.35

Number of complete executions explored: 0
Total wall-clock time: 0.02s
```
