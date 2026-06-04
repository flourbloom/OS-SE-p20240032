// compile: javac task3_optional_deadlock_recovery/DeadlockRecovery.java
// run: java -cp task3_optional_deadlock_recovery DeadlockRecovery

import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

class Account {
    String name;
    int balance;
    Semaphore lock = new Semaphore(1);

    Account(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

class TransferRecovery {

    static void transfer(Account from, Account to, int amount) {
        String threadName = Thread.currentThread().getName();
        boolean success = false;

        while (!success) {
            try {
                System.out.println(threadName + " trying to lock FROM " + from.name);
                from.lock.acquire();
                System.out.println(threadName + " locked FROM " + from.name);

                System.out.println(threadName + " trying to lock TO " + to.name + " with timeout");
                if (to.lock.tryAcquire(1, TimeUnit.SECONDS)) {
                    // Acquired both locks
                    System.out.println(threadName + " locked TO " + to.name);
                    from.balance -= amount;
                    to.balance += amount;
                    System.out.println(threadName + " transferred " + amount +
                            " from " + from.name + " to " + to.name);
                    success = true;

                    to.lock.release();
                    from.lock.release();
                } else {
                    // Could not acquire second lock → release first and retry
                    System.out.println(threadName + " could not lock TO " + to.name +
                            ", releasing FROM " + from.name + " and retrying");
                    from.lock.release();
                    Thread.sleep(500); // backoff before retry
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class DeadlockRecovery {

    public static void main(String[] args) {
        Account accountA = new Account("Account-A", 1000);
        Account accountB = new Account("Account-B", 1000);

        System.out.println("Starting balances:");
        System.out.println(accountA.name + ": " + accountA.balance);
        System.out.println(accountB.name + ": " + accountB.balance);
        System.out.println();

        Thread t1 = new Thread(
                () -> TransferRecovery.transfer(accountA, accountB, 100),
                "Worker-1"
        );

        Thread t2 = new Thread(
                () -> TransferRecovery.transfer(accountB, accountA, 200),
                "Worker-2"
        );

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        int total = accountA.balance + accountB.balance;
        System.out.println();
        System.out.println("Final balances:");
        System.out.println(accountA.name + ": " + accountA.balance);
        System.out.println(accountB.name + ": " + accountB.balance);
        System.out.println("Final total: " + total);
        System.out.println("Deadlock avoided: all transfers completed successfully.");
    }
}