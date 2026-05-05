# OS Lab 5 Submission — Threads, Kernel Workers & Process Signals

- **Student Name:** Chea Seavhong
- **Student ID:** p20240032

---

## Task Output Source Files

Make sure all of the following files are present in your `lab5/thread_lab/` folder:

- [x] `process_test.c`
- [x] `thread_test.c`
- [x] `multi_thread.c`
- [x] `sleeper_threads.c`
- [x] `signal_handler.c`
- [x] `challenge.c`

---

## Screenshots

Insert your screenshots below.

### Screenshot 1 — Task 1: Process vs Thread (Process Test)
Show the output of `process_test.c`.
<!-- Insert your screenshot below: -->
![process vs thread 1](images/process_vs_thread_1.png)

---

### Screenshot 2 — Task 1: Process vs Thread (Thread Test)
Show the output of `thread_test.c`.
<!-- Insert your screenshot below: -->
![process vs thread 2](images/process_vs_thread_2.png)

---

### Screenshot 3 — Task 2: Thread Interaction
Show the output of `multi_thread.c`.
<!-- Insert your screenshot below: -->
![thread interaction](images/thread_interaction.png)

---

### Screenshot 4 — Task 3: Visualizing 1:1 Thread Mapping
Show the `ps -eLf` output or `/proc/[pid]/task/` directory visualizing the LWP mapping for user threads.
<!-- Insert your screenshot below: -->
![user to kernel mapping](images/user_kernel_mapping.png)

---

### Screenshot 5 — Task 3: `htop` Kernel Threads
Show `htop` visualizing kernel threads (usually bracketed names like `[kworker]`).
<!-- Insert your screenshot below: -->
![htop kernel threads](images/htop_kernel_threads.png)

---

### Screenshot 6 — Task 4: Catching `SIGINT`
Show the output of your `signal_handler` program gracefully catching `Ctrl+C`.
<!-- Insert your screenshot below: -->
![signal handling](images/signal_sigint.png)

---

### Screenshot 7 — Challenge: Graceful Multithreaded Shutdown
Show the output of your `challenge.c` program joining its threads and exiting gracefully after receiving `Ctrl+C`.
<!-- Insert your screenshot below: -->
![challenge shutdown](images/challenge_shutdown.png)

---

## Answers to Lab Questions

1. **Why do threads share memory while processes do not (by default)?**
   > Threads share the same address space, so they can use the same data. Processes are separate by default to keep them isolated.

2. **Based on the 1:1 mapping, what is the role of an LWP (Lightweight Process) in Linux?**
   > An LWP is the kernel-side unit that represents a thread. Linux schedules each LWP separately on the CPU.

3. **Why is it restricted to send signals to kernel threads (e.g., `kthreadd` or `kworker`)?**
   > Kernel threads do important OS work, so user programs should not interrupt them directly. The restriction helps protect system stability.

4. **Why can't `SIGKILL` (kill -9) be caught by a signal handler?**
   > `SIGKILL` is forced by the kernel and cannot be blocked, ignored, or handled. It always terminates the process immediately.

---

## Reflection

> I learned that threads share memory, LWPs are the kernel-side view of threads, and signals are useful for stopping work cleanly. I also learned that `SIGKILL` cannot be handled and that graceful shutdown matters in larger programs.