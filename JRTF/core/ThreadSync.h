#pragma once
#include<stdio.h>
#include<iostream>
#include"semaphore.h"
#include<unistd.h>
#include<sys/syscall.h>
#include<pthread.h>
#include<sys/prctl.h>


using namespace std;

class ThreadSync
{
public:
	ThreadSync() {
		pthread_mutex_init(&mutex, NULL);
		pthread_spin_init(&spin, 0);

		pthread_cond_init(&cond, NULL);
		pthread_mutex_init(&mutex_c, NULL);

		sem_init(&sem, 0, 0);
		pthread_mutex_init(&mutex_s, 0);
	}

	//synchronization functions
	void mutexlock() { pthread_mutex_lock(&mutex); }
	void mutexunlock() { pthread_mutex_unlock(&mutex); }

	void spinlock() { pthread_spin_lock(&spin); }
	void spinunlock() { pthread_spin_unlock(&spin); }

	void condwait() {
		pthread_mutex_lock(&mutex_c);
		pthread_cond_wait(&cond, &mutex_c);
		pthread_mutex_unlock(&mutex_c);
	}
	void condsignal() {
		pthread_mutex_lock(&mutex_c);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex_c);
	}

	void sempost() {
		pthread_mutex_lock(&mutex_s);
		sem_post(&sem);
		pthread_mutex_unlock(&mutex_s);
	}
	void semwait() {
		sem_wait(&sem);
	}

	pthread_mutex_t mutex;
	pthread_spinlock_t spin;

	pthread_cond_t  cond;
	pthread_mutex_t mutex_c;

	sem_t sem;
	pthread_mutex_t mutex_s;

private:

};


