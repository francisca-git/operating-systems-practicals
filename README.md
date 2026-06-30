# Operating Systems Practical Assignment

## Student Information

**Course:** Operating Systems  
**Assignment:** Practical Sessions  
**Language:** C

---

## Practical 1 – Mutex Lock Demonstration

### Objective
Demonstrate how a mutex prevents race conditions when multiple threads access a shared variable.

### Features
- Creates multiple threads.
- Increments a shared counter.
- Shows execution with and without a mutex.
- Uses:
  - `pthread_mutex_init()`
  - `pthread_mutex_lock()`
  - `pthread_mutex_unlock()`
  - `pthread_mutex_destroy()`

---

## Practical 2 – Producer-Consumer Problem

### Objective
Implement the Producer-Consumer problem using POSIX semaphores.

### Features
- Fixed-size circular buffer.
- Producer inserts items.
- Consumer removes items.
- Displays buffer contents during execution.
- Uses:
  - `sem_init()`
  - `sem_wait()`
  - `sem_post()`
  - `sem_destroy()`

---

## Practical 3 – Semaphore Demonstration

### Objective
Protect a shared counter using a binary semaphore.

### Features
- Multiple threads increment a shared counter.
- Synchronizes access using a semaphore.
- Includes a brief comparison between mutexes and semaphores.

---

## Practical 4 – Shared Memory Communication

### Objective
Demonstrate communication between parent and child processes using shared memory.

### Features
- Creates shared memory.
- Parent process writes data.
- Child process reads data.
- Cleans up shared memory after execution.

---

## Compilation

### Practical 1

```bash
gcc practical1_mutex.c -o practical1 -pthread
```

### Practical 2

```bash
gcc practical2_producer_consumer.c -o practical2 -pthread
```

### Practical 3

```bash
gcc practical3_semaphore.c -o practical3 -pthread
```

### Practical 4 (Linux Only)

```bash
gcc practical4_shared_memory.c -o practical4 -pthread
```

---

## Running

```bash
./practical1
./practical2
./practical3
./practical4
```

> **Note:** Practical 4 uses Linux System V shared memory (`shmget`, `shmat`, `fork`) and is intended to be compiled and executed on a Linux operating system.
