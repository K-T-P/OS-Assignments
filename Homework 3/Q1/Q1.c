#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define NUM_CUSTOMERS 5   // number of customers
#define NUM_TRANSACTION 6 // number of transactions/threads
#define INIT_STOCK 100    // the initial value for each person stock

pthread_mutex_t safeBox_lock;
pthread_mutex_t customer_local_lock[NUM_CUSTOMERS];
pthread_t threadId[NUM_TRANSACTION];

// type transaction. you should pass an object of this type to the function arguments while creating thread
typedef struct
{
    double amount;
    int customer_id;
} transaction_t;

double safeBox ; // shared variable for all customers

///////// Start your code here ///////////

/*1. define an array to store the stock of all customers
  2. define the necessary mutexes for each customer account and safe box*/
double Stocks[NUM_CUSTOMERS];
double debts[NUM_CUSTOMERS];

double max(double a, double b){
    if (a > b)
        return a;
    else
        return b;
}
double min(double a, double b){
    if (a>b)
        return b;
    else
        return a;
}

void *withdraw(void *arg)
{
    transaction_t *tr = (transaction_t *)arg;
    bool successFlag = true;
    pthread_mutex_lock(&customer_local_lock[tr->customer_id]);
    double customerWithdraw = 0.0;
    pthread_mutex_lock(&safeBox_lock);
    double safeBoxValue = safeBox;
    pthread_mutex_unlock(&safeBox_lock);
    double safeBoxWithdraw = 0.0;
    if (Stocks[tr->customer_id] >= tr->amount)
    {
        Stocks[tr->customer_id] -= tr->amount;
        customerWithdraw = tr->amount;
    }
    else
    {
        pthread_mutex_lock(&safeBox_lock);
        if (safeBox + max(0,Stocks[tr->customer_id]) < tr->amount)
        {
            successFlag = false;
        }
        else
        {
            safeBox -= (tr->amount - max(0,Stocks[tr->customer_id]));
            debts[tr->customer_id] += (tr->amount - max(0,Stocks[tr->customer_id]));
            safeBoxWithdraw = (tr->amount - max(0,Stocks[tr->customer_id]));
            Stocks[tr->customer_id] = min(0.0,Stocks[tr->customer_id]);
            safeBoxValue = safeBox;
        }
        pthread_mutex_unlock(&safeBox_lock);
    }
    if (successFlag == true)
    {
        printf("Customer %d withdrew %.2f and %.2f from safe-box. New balance: %.2f\tsafe-box value: %.2f \n",
               tr->customer_id, tr->amount, safeBoxWithdraw, Stocks[tr->customer_id] - debts[tr->customer_id], safeBoxValue);
    }
    else
    {
        printf("Not enough money to withdraw. Balance: %.2f\tsafe-box value: %.2f\n",
               Stocks[tr->customer_id], safeBoxValue);
    }
    pthread_mutex_unlock(&customer_local_lock[tr->customer_id]);
    /*be aware to print the result in each situation.
      for example in one case that the stock isn't adequate and customer took money from safe box, you can report like the following:
      Customer <customerID> withdrew <transaction-amount> and <the amount taken from safe box> from safe-box. New balance: <new amount of customer stock>\tsafe-box value: <new amount of safe box>\n
      don't forget to report the new balance and new safe box value*/
}

void *deposit(void *arg)
{
    transaction_t *tr = (transaction_t *)arg;
    pthread_mutex_lock(&customer_local_lock[tr->customer_id]);
    pthread_mutex_lock(&safeBox_lock);
    double safeBoxValue = safeBox;
    pthread_mutex_unlock(&safeBox_lock);
    if (debts[tr->customer_id] > 0)
    {
        if (debts[tr->customer_id] > tr->amount)
        {
            debts[tr->customer_id] -= tr->amount;
            pthread_mutex_lock(&safeBox_lock);
            safeBox += tr->amount;
            safeBoxValue = safeBox;
            pthread_mutex_unlock(&safeBox_lock);
        }
        else
        {
            pthread_mutex_lock(&safeBox_lock);
            safeBox += debts[tr->customer_id];
            safeBoxValue = safeBox;
            pthread_mutex_unlock(&safeBox_lock);
            tr->amount -= debts[tr->customer_id];
            debts[tr->customer_id] = 0.0;
            Stocks[tr->customer_id] += tr->amount;
        }
    }
    else
    {
        Stocks[tr->customer_id] += tr->amount;
    }
    double printAmount = tr->amount;
    printf("Customer %d stock was charged by %.2f. New balance: %.2f\tsafe-box value: %.2f\n",
           tr->customer_id, printAmount, Stocks[tr->customer_id] - debts[tr->customer_id], safeBoxValue);
    pthread_mutex_unlock(&customer_local_lock[tr->customer_id]);
    /*be aware to print the result in the following form:
      Customer <customerID> stock was charged by <transaction-amount>. New balance: <new amount of customer stock>\tsafe-box value: <new amount of safe box>\n
      don't forget to report the new balance and new safe box value*/
}

int main()
{
    srand(time(NULL));
    safeBox = rand() % 1000 + 1;
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        Stocks[i] = rand() % 500 + 1;
        debts[i] = 0.0;
    }

    pthread_mutex_init(&safeBox_lock, NULL);
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        pthread_mutex_init(&customer_local_lock[i], NULL);
    }

    int i = 0;
    int cusNum=0;
    transaction_t ttr[NUM_TRANSACTION] ;
    while (i < NUM_TRANSACTION)
    {
        transaction_t tr = ttr[i];
        ttr[i].amount = rand() % 300 + 1;
        ttr[i].customer_id = rand() % 5;
        if ((int)rand() % 2 == 0)
        {
            pthread_create(&threadId[i], NULL, withdraw, (void *)&ttr[i]);
        }
        else
        {
            pthread_create(&threadId[i], NULL, deposit, (void *)&ttr[i]);
        }
        i++;
    }
    for (int i = 0; i < NUM_TRANSACTION; i++)
    {
        pthread_join(threadId[i], NULL);
    }
    /* for each customer, value the stock with INIT_STOCK
    init mutex for each account and safe box */

    /* create thread for each transaction
    for each thread:
    if rand() % 2 == 0
        create thread for withdraw
    otherwise
        create thread for deposit*/

    ///////// End of your code ///////////
    return 0;
}