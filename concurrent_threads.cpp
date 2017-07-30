
////////////////////////////////////////////////////////////
//Michael Manzanares (cssc1125) and Stephen Summy (cssc1103)
//CS570 Summer 2017
//Assignment #1
//a1.c
////////////////////////////////////////////////////////////
#include "concurrent_threads.h"

//This function prints the current Process ID to the file, and initiates 
//our semaphore
void file_setup()
{
	ofstream file;
	int pid = getpid();

	file.open("QUOTE.txt");
	file << pid << "\r\n";
	file.close();

		
	sem_init(&FLAG, 0, 1);
}

//create a new thread that will write to our file 7 times
//Odd and even threads write different quotes
void *new_thread(void *arg)
{
	ofstream file; 
	for (int i = 0; i < N; i++)
	{
	//Call down on the semaphore
	sem_wait(&FLAG);
	file.open("QUOTE.txt", std::ofstream::app);
	//if the thread ID is even
	if((long)arg %2 ==0)
	{
		cout << "Thread " << (long)arg << " is running.\r\n";
		file << (long)arg << " \"Controlling complexity is the essence of computer programming. \" --Brian Kernigan \r\n";
	}
	//if the thread is odd
	else
	{
		cout << "Thread " << (long)arg << " is running.\r\n";
		file << (long)arg << " \"Computer science is no more about computers than astronomy is about telescopes.\" --Edsger Dijkstra \r\n";
	}
	//now we're done with the critical section, so close the file and call
	//UP on the semaphore
	file.close();
	sem_post(&FLAG);
	if ((long)arg %2 ==0)
		sleep(2);
	else
		sleep(3);
	}//end of the for loop

	//release the thread resources now that we're done using them
	pthread_exit(0);
}

//Create N threads, send them to work, and then free their resources afterwards
void create_threads(pthread_t my_thread[])
{
	//the thread attribute is necessary for many thread commands
	pthread_attr_t attr;
	int status = pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int ret;
	//Send N threads to work
	for (long id = 1; id <= N; id++)
	{
		ret = pthread_create(&my_thread[id], &attr, &new_thread, (void*)id);
	}
	//Now that the threads are done, we destroy, join, and then exit to free their resources
	status = pthread_attr_destroy(&attr);
	for (long id = 1; id <= N; id++)
	{
		pthread_join(my_thread[id], NULL);
		if(ret != 0)
		{
			printf("Error\n");
			exit(EXIT_FAILURE);
		}
	}
	pthread_exit(NULL);
}//end of create_threads


int main(){       
	pthread_t my_thread[N];
	file_setup();
	create_threads(my_thread);
		
	return 0;
}

