#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <unistd.h>
#include <pthread.h>

using namespace std;

struct DiscussInfo
{
	DiscussInfo(int a, int b);
	int stu_num;
	int time;
};

class semaphore
{
public:
	semaphore(int count = 0);
	~semaphore();
	void wait();
	void signal();
private:
	int val;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

deque< DiscussInfo > waiting_TA;
deque< DiscussInfo > waiting_prof;

semaphore sem_stu_wait_TA;
semaphore sem_stu_wait_prof;
semaphore sem_prof;
semaphore sem_TA;

pthread_mutex_t mutex_stu;

bool rest_TA;
bool rest_prof;
int num[50];

timespec begin_time;

void* Prof_TY(void*);
void* TA_Yang(void*);
void* student(void*);

int time_calculate();

int main()
{
	srand(0);
	pthread_mutex_init(&mutex_stu, NULL);

	pthread_t Prof_TY_thread;
	pthread_t TA_Yang_thread;
	pthread_t student_thread[50];

	pthread_create(&Prof_TY_thread, NULL, Prof_TY, 0);
	pthread_create(&TA_Yang_thread, NULL, TA_Yang, 0);
	for(int i=0 ; i<50 ; i++)
	{
		num[i] = i+1;
		pthread_create(&student_thread[i], NULL, student, &num[i]);
	}

	pthread_join(Prof_TY_thread, NULL);
	pthread_join(TA_Yang_thread, NULL);
	for(int i = 0 ; i < 50 ; i++)
		pthread_join(student_thread[i], NULL);

	pthread_mutex_destroy(&mutex_stu);
}


void* Prof_TY(void* f)
{
	clock_gettime(CLOCK_REALTIME, &begin_time);
	cout << "0 ms -- Prof. TY: rest" << endl;
	rest_prof = true;
	for(int i = 0 ; i < 50 ; i++)
	{
		if(waiting_prof.size() == 0 && i != 0)
		{
			rest_prof = true;
			if(rest_TA)
				cout << time_calculate() << " ms -- Prof. TY: Play LOL with TA_Yang" << endl;
			else
				cout << time_calculate() << " ms -- Prof. TY: rest" << endl;
		}
		sem_prof.wait();
		rest_prof = false;
		DiscussInfo tmp = waiting_prof.back();
		waiting_prof.pop_back();
		cout << time_calculate() << " ms -- Prof. TY: discuss with student " << tmp.stu_num << ' ' << tmp.time << " ms" << endl;
		usleep(tmp.time * 1000);
		sem_stu_wait_prof.signal();
	}
}


void* TA_Yang(void* f)
{
	cout << "0 ms -- TA Y: rest" << endl;
	rest_TA = true;
	for(int i = 0 ; i < 50 ; i++)
	{
		if(waiting_TA.size() == 0 && i != 0)
		{
			rest_TA = true;
				cout << time_calculate() << " ms -- TA Y: rest" << endl;
		}
		sem_TA.wait();
		rest_TA = false;
		DiscussInfo tmp = waiting_TA.back();
		waiting_TA.pop_back();
		cout << time_calculate() << " ms -- TA Y: discuss with student " << tmp.stu_num << ' ' << tmp.time << " ms" << endl;
		usleep(tmp.time * 1000);
		sem_stu_wait_TA.signal();
	}
}

void* student(void* n)
{
	int num = *(int*)n;
	DiscussInfo stu_dinfo(num, 10 + rand() % 21);
	bool is_waiting = false;

	pthread_mutex_lock(&mutex_stu);
	usleep((5 + rand() % 6) * 1000);

	if(waiting_TA.size() + waiting_prof.size() < 5)
	{
		cout << time_calculate() << " ms -- Student " << num << ": enter & wait" << endl;
		waiting_TA.push_front(stu_dinfo);
		is_waiting = true;
	}
	pthread_mutex_unlock(&mutex_stu);

	while(!is_waiting)
	{
		int t = 30 + rand() % 21;
		cout << time_calculate() << " ms -- Student " << num << ": see \"the world between us\" with Xing " << t << " ms" << endl;
		usleep(t * 1000);
		pthread_mutex_lock(&mutex_stu);
		if(waiting_TA.size() + waiting_prof.size() < 5)
		{
			cout << time_calculate() << " ms -- Student " << num << ": enter & wait" << endl;
			waiting_TA.push_front(stu_dinfo);
			is_waiting = true;
		}
		pthread_mutex_unlock(&mutex_stu);
	}


	stu_dinfo.time = 50 + rand() % 51;
	sem_TA.signal();
	sem_stu_wait_TA.wait();

	waiting_prof.push_front(stu_dinfo);

	sem_prof.signal();
	sem_stu_wait_prof.wait();
	cout << time_calculate() << " ms -- Student " << num << ": leave" << endl;
}

int time_calculate()
{
	timespec now_time;
	clock_gettime(CLOCK_REALTIME, &now_time);
	int sec = now_time.tv_sec - begin_time.tv_sec;
	int nsec = now_time.tv_nsec - begin_time.tv_nsec;
	if(nsec < 0)
	{
		nsec += 1000000000;
		--sec;
	}
	return sec*1000 + nsec/1000000;
}

DiscussInfo::DiscussInfo(int a, int b)
	:stu_num(a), time(b)
{
}

semaphore::semaphore(int count)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	val = count;
}

semaphore::~semaphore()
{
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}

void semaphore::wait() 
{
	pthread_mutex_lock(&mutex);
	while(val==0) 
		pthread_cond_wait(&cond, &mutex);
	val--;
	pthread_mutex_unlock(&mutex);
}

void semaphore::signal() 
{
	pthread_mutex_lock(&mutex);
	if(val++ == 0) 
		pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
}
