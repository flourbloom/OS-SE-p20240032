# commands.md — exact commands I ran, per part

## Part A — Threads, Mapping & Signals
```bash
mkdir -p partA_threads/images

nano partA_threads/thread_demo.c

gcc partA_threads/thread_demo.c -o partA_threads/thread_demo -pthread

./partA_threads/thread_demo

./partA_threads/thread_demo &

ps -ef | grep thread_demo

ps -T -p <PID>

ps -T -p <PID> > partA_threads/thread_map.txt

nano partA_threads/signal_demo.c

gcc partA_threads/signal_demo.c -o partA_threads/signal_demo

./partA_threads/signal_demo

```

## Part B — Permissions, Special Bits & ACLs
```bash
mkdir -p partB_security/images

mkdir -p partB_security/security_demo/shared

touch partB_security/security_demo/private.txt

chmod 600 partB_security/security_demo/private.txt

chmod u=rw,go= partB_security/security_demo/private.txt

chmod 711 partB_security/security_demo/shared

ls -l partB_security/security_demo

ls -ld partB_security/security_demo/shared

stat partB_security/security_demo/private.txt

mkdir partB_security/project

chmod g+s partB_security/project

chmod +t partB_security/project

ls -ld partB_security/project

nano partB_security/setuid_demo.c

gcc partB_security/setuid_demo.c -o partB_security/setuid_demo

chmod u+s partB_security/setuid_demo

ls -l partB_security/setuid_demo

./partB_security/setuid_demo

```

## Part C — Bash Scripting, PATH & Safe Scanning
```bash
mkdir -p partC_scripting/scripts
mkdir -p partC_scripting/images

nano ~/bin/greeter
chmod +x ~/bin/greeter
cp ~/bin/greeter partC_scripting/scripts/

echo $PATH
export PATH=$HOME/bin:$PATH
which greeter
greeter

mkdir -p partC_scripting/test_data/dir1
mkdir -p partC_scripting/test_data/dir2
mkdir -p partC_scripting/test_data/dir3

echo "Network configuration" > partC_scripting/test_data/dir1/file1.txt
echo "System status" > partC_scripting/test_data/dir2/file2.txt
echo "Secret data" > partC_scripting/test_data/dir3/file3.txt

chmod 000 partC_scripting/test_data/dir3/file3.txt

nano ~/bin/collector
chmod +x ~/bin/collector
cp ~/bin/collector partC_scripting/scripts/

collector
cat partC_scripting/report.txt

```

## Part D — Race Condition & flock
```bash
cd ~/OS-SE-p20240032/final-exam/partD_secure
echo 100 > stock.txt
chmod +x scripts/buy_relay_pass scripts/swarm

for i in {1..5}; do
    echo 100 > stock.txt
    ./scripts/swarm
    echo "Run $i -> $(cat stock.txt)" >> observations.txt
done
    
for i in {1..5}; do
    echo 100 > stock.txt
    ./scripts/swarm
done
```

## Part E — Backups & cron
```bash
mkdir -p partE_automation/scripts
mkdir -p partE_automation/logs
mkdir -p partE_automation/images
mkdir -p ~/exam-backups
mkdir -p partE_automation/sample_project/src
mkdir -p partE_automation/sample_project/docs
echo "main program" > partE_automation/sample_project/src/main.txt
echo "readme" > partE_automation/sample_project/docs/readme.txt
echo "config" > partE_automation/sample_project/config.cfg
nano ~/bin/backup_project
chmod +x ~/bin/backup_project
cp ~/bin/backup_project partE_automation/scripts/
backup_project
sleep 1
backup_project
sleep 1
backup_project
sleep 1
backup_project
sleep 1
backup_project
sleep 1
backup_project
ls -l partE_automation/backups
nano ~/bin/timed_job
chmod +x ~/bin/timed_job
cp ~/bin/timed_job partE_automation/scripts/
nano ~/bin/backup_exam
chmod +x ~/bin/backup_exam
cp ~/bin/backup_exam partE_automation/scripts/
backup_exam
ls -l ~/exam-backups
chmod 000 partC_scripting/test_data/dir3/file3.txt
chmod 644 partC_scripting/test_data/dir3/file3.txt
rm ~/exam-backups/final-exam-20260630_142421.tar.gz
backup_exam
ls -lh ~/exam-backups
backup_exam
ls -l ~/exam-backups
backup_exam
ls -l ~/exam-backups
crontab -e
crontab -l
cat partE_automation/logs/cron_recurring.log
cat partE_automation/logs/cron_oneshot.log
date
watch -n 2 ls -l partE_automation/logs
cat partE_automation/logs/cron_recurring.log
cat partE_automation/logs/cron_oneshot.log
{ echo "===== Crontab ====="; crontab -l;  echo; echo "===== Recurring Log ====="; cat partE_automation/logs/cron_recurring.log;  echo; echo "===== One-shot Log ====="; cat partE_automation/logs/cron_oneshot.log;  echo; echo "===== Exam Backups ====="; ls -l ~/exam-backups;  } > partE_automation/cron_report.txt
cat partE_automation/cron_report.txt
```
