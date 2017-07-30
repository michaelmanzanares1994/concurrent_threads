
////////////////////////////////////////////////////////////
//Michael Manzanares (cssc1125) and Stephen Summy (cssc1103)
//CS570 Summer 2017
//Assignment #1
//a1.h
////////////////////////////////////////////////////////////

#ifndef A1_H
#define A1_H

#include <iostream>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string>
using namespace std;

#define N 7

sem_t FLAG;

void file_setup();
void *new_thread(void *arg);
void create_threads(pthread_t my_thread[]);


#endif
