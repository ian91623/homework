#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/wait.h>

using namespace std;

struct gunboat
{	
	int x[2];
	int y[2];
	bool hit[2];
	int bomb_count;
};

struct bang
{
	int x;
	int y;
	bool sink;
	int turn;
	int attacker;
	int bomb_count;
};

void error_and_die(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

bang* shm()
{
	int fd = shm_open("name", O_CREAT | O_TRUNC | O_RDWR, 0666);
	if(fd == -1)
		error_and_die("ftruncate");
	
	int size_of_bang = sizeof(bang);

	if(ftruncate(fd, size_of_bang) != 0)
		error_and_die("shm_open");

	void *ptr = mmap(0, size_of_bang, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
		error_and_die("shm_open");
	close(fd);

	return (bang*) ptr;
}


int  main()
{
	bang* bombing_check = shm();
	bombing_check->x = 0;
	bombing_check->y = 0;
	bombing_check->sink = 0;
	bombing_check->bomb_count = 0;
	
	pid_t ppid = getpid();
	pid_t pid = fork();

	int process = (getpid() == ppid ? 0 : 1);
	int opp = (process ? 0 : 1);
	srand(time(0) + pid);

	gunboat myboat;
	myboat.x[0] = rand() % 4;
	myboat.y[0] = rand() % 4;
	if(rand() % 2)
	{
		if(rand() % 2 && myboat.x[0] != 0 || myboat.x[0] == 3)
			myboat.x[1] = myboat.x[0] - 1;
		else
			myboat.x[1] = myboat.x[0] + 1;
		myboat.y[1] = myboat.y[0];
	}
	else
	{
		if(rand() % 2 && myboat.y[0] != 0 || myboat.y[0] == 3)
			myboat.y[1] = myboat.y[0] - 1;
		else
			myboat.y[1] = myboat.y[0] + 1;
		myboat.x[1] = myboat.x[0];
	}
	myboat.hit[0] = myboat.hit[1] = false;
	myboat.bomb_count = 0;


	if(getpid() == ppid)
		bombing_check->turn = process;
	while(bombing_check->turn == opp);
	cout << '[' << getpid() << ' ' << (!process ? "Parent" : "Child") << "]:The gunboat:(" << myboat.x[0] << ',' << myboat.y[0] << ")(" << myboat.x[1] << ',' << myboat.y[1] << ')' << endl;
	bombing_check->turn = opp;
	while(bombing_check->turn == opp);

	while(1)
	{
		bombing_check->turn = opp;
		while(bombing_check->turn == opp);
		if(bombing_check->sink)
			break;
		for(int i=0 ; i<2 && bombing_check->bomb_count ; i++)
		{
			if(i == 0)
				cout << '[' << getpid() << ' ' << (!process ? "Parent" : "Child") << "]:";
			if(myboat.x[i] == bombing_check->x && myboat.y[i] == bombing_check->y)
			{
				myboat.hit[i] = true;
				cout << "hit";
				if(myboat.hit[0] && myboat.hit[1])
				{
					cout << " and sinking" << endl;
					bombing_check->sink = true;
					break;
				}
				else
				{
					cout << endl;
					break;
				}
			}
			else if(i == 1)
				cout << "missed" << endl;
		}
		if(bombing_check->sink)
		{
			cout << '[' << getpid() << ' ' << (!process ? "Parent" : "Child") << "]:" << bombing_check->attacker << " win wuth " << bombing_check->bomb_count << " bombs" << endl;
			bombing_check->turn = opp;
			break;
		}
		bombing_check->x = rand() % 4;
		bombing_check->y = rand() % 4;
		bombing_check->attacker = getpid();
		bombing_check->bomb_count = ++myboat.bomb_count;
		cout << '[' << getpid() << ' ' << (!process ? "Parent" : "Child") << "]:bombing(" << bombing_check->x << ',' << bombing_check->y << ')' << endl;
	}

	if(pid == ppid)
	{
		int r = munmap(bombing_check, sizeof(bang));
			if (r != 0)
				error_and_die("munmap");

		r = shm_unlink("name");
			if (r != 0)
				error_and_die("shm_unlink");
	}

	return 0;

}
