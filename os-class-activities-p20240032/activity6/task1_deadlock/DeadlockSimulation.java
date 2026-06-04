// compile: javac task1_deadlock/DeadlockSimulation.java
// run: java -cp task1_deadlock DeadlockSimulation

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

class Account {
    String name;
    int balance;
    Semaphore lock = new Semaphore(1);

    Account(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

class Transfer {

    static AtomicInteger completedTransfers = new AtomicInteger(0);

    static volatile String worker1Status = "Not started";
    static volatile String worker2Status = "Not started";

    static void transfer(Account from, Account to, int amount) {
        try {
            String threadName = Thread.currentThread().getName();

            System.out.println(threadName + " started transaction");

            System.out.println(threadName +
                    " trying to lock FROM " + from.name);

            from.lock.acquire();

            System.out.println(threadName +
                    " locked FROM " + from.name);

            // Force overlap between threads
            Thread.sleep(1000);

            System.out.println(threadName +
                    " waiting for TO " + to.name);

            if (threadName.equals("Worker-1")) {
                worker1Status = "Worker 1 is waiting for " + to.name;
            } else {
                worker2Status = "Worker 2 is waiting for " + to.name;
            }

            to.lock.acquire();

            System.out.println(threadName +
                    " locked TO " + to.name);

            from.balance -= amount;
            to.balance += amount;

            completedTransfers.incrementAndGet();

            System.out.println(threadName +
                    " transfer completed");

            to.lock.release();
            from.lock.release();

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class DeadlockSimulation {

    public static void main(String[] args) {

        Account accountA = new Account("Account-A", 1000);
        Account accountB = new Account("Account-B", 1000);

        System.out.println("Starting balances:");
        System.out.println("Account-A: " + accountA.balance);
        System.out.println("Account-B: " + accountB.balance);
        System.out.println();

        Thread t1 = new Thread(
                () -> Transfer.transfer(accountA, accountB, 100),
                "Worker-1"
        );

        Thread t2 = new Thread(
                () -> Transfer.transfer(accountB, accountA, 200),
                "Worker-2"
        );

        t1.start();
        t2.start();

        // Watchdog thread
        Thread watchdog = new Thread(() -> {
            try {
                Thread.sleep(4000);

                if (Transfer.completedTransfers.get() == 0) {

                    System.out.println();
                    System.out.println(
                        "Deadlock detected: transactions are stuck"
                    );

                    System.out.println(Transfer.worker1Status);
                    System.out.println(Transfer.worker2Status);

                    System.out.println();
                    System.out.println(
                        "Current balances remain unchanged:"
                    );
                    System.out.println(
                        "Account-A: " + accountA.balance
                    );
                    System.out.println(
                        "Account-B: " + accountB.balance
                    );
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });

        watchdog.start();
    }
}