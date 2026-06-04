# OS Lab 7 Submission — Bash Scripting, Permissions & Server Automation

- **Student Name:** Chea Seavhong
- **Student ID:** p20240032

---

## Task Output Files

- [x] task1_warmup.txt
- [x] task2_path.txt
- [x] task3_doorstep.txt
- [x] task4_inbox.txt
- [x] task5_broadcaster.txt
- [x] task6_guestbook.txt
- [x] harvest_report.txt
- [x] task8_mailman.txt
- [x] sign_book.c
- [x] scripts/warmup
- [x] scripts/broadcaster
- [x] scripts/harvester
- [x] scripts/mailman
- [x] scripts/sign_book_binary

---

## Answers to Lab Questions

1. **Why did `warmup` fail before you added execute permission?**  
   Because the file did not have execute (`x`) permission. Without it, Linux treats the script as a regular text file and refuses to run it as a program.

2. **What does adding `~/bin` to `PATH` allow you to do?**  
   It allows the system to find and run my scripts from anywhere without typing the full file path. I can just use the command name directly.

3. **Why does `chmod 733 public_inbox` allow classmates to drop files but not list the inbox?**  
   Because `7` gives full access to me (read/write/execute), while `3` gives others only write and execute permissions. They can create files but cannot read directory contents.

4. **Why does Linux ignore SUID on shell scripts, and why did we use a compiled C program instead?**  
   Linux ignores SUID on shell scripts for security reasons (to prevent privilege escalation attacks). A compiled C program is used because SUID works reliably on binaries.

5. **What is the difference between `>` and `>>` in Bash redirection?**  
   `>` overwrites the file completely, while `>>` appends new content to the existing file.

6. **How did your `harvester` avoid reading files that were missing or not readable?**  
   It used checks like `-f` and `-r` before reading files, and redirected errors using `2>/dev/null` to skip invalid or inaccessible files.

7. **What permission problems did you or your classmates need to fix during the lab?**  
   Common issues included missing execute permissions, incorrect directory permissions preventing file access, and scripts not running due to PATH misconfiguration.

---

## Reflection

This lab demonstrated how Linux permissions and shell scripting work together to enable automation in a shared environment. I learned how execute permissions control program execution, how PATH simplifies command usage, and how directory permissions affect collaboration between users. I also understood the importance of secure design choices, such as why SUID is restricted for scripts and how compiled binaries are used instead. Overall, it improved my ability to automate tasks and manage multi-user systems safely.