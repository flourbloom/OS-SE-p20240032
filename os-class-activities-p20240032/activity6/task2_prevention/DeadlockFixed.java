// compile: javac task2_prevention/DeadlockFixed.java
// run: java -cp task2_prevention DeadlockFixed

import java.util.concurrent.Semaphore;

class Account {
    String name;
    int balance;

    Account(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

class Transfer {

    // Shared mutex for all transfers
    static Semaphore mutex = new Semaphore(1);

    static void transfer(Account from, Account to, int amount) {
        try {
            String threadName = Thread.currentThread().getName();
            System.out.println(threadName + " waiting for global mutex...");

            // Acquire the single mutex to prevent deadlock
            mutex.acquire();
            System.out.println(threadName + " acquired mutex");

            // Small delay to simulate work
            Thread.sleep(500);

            // Perform the transfer
            from.balance -= amount;
            to.balance += amount;

            System.out.println(threadName + " transferred " + amount +
                    " from " + from.name + " to " + to.name);
            System.out.println("Current balances: " +
                    from.name + ": " + from.balance +
                    ", " + to.name + ": " + to.balance);

        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            // Always release the mutex
            mutex.release();
            System.out.println(Thread.currentThread().getName() + " released mutex");
        }
    }
}

public class DeadlockFixed {

    public static void main(String[] args) {

        Account accountA = new Account("Account-A", 1000);
        Account accountB = new Account("Account-B", 1000);

        int startingTotal = accountA.balance + accountB.balance;

        System.out.println("Starting balances:");
        System.out.println(accountA.name + ": " + accountA.balance);
        System.out.println(accountB.name + ": " + accountB.balance);
        System.out.println("Starting total: " + startingTotal);
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

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        int finalTotal = accountA.balance + accountB.balance;

        System.out.println();
        System.out.println("Final balances:");
        System.out.println(accountA.name + ": " + accountA.balance);
        System.out.println(accountB.name + ": " + accountB.balance);
        System.out.println("Final total: " + finalTotal);

        if (finalTotal == startingTotal) {
            System.out.println("No deadlock occurred. Total money is consistent.");
        } else {
            System.out.println("Error: total money mismatch!");
        }
    }
}