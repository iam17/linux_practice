/*************************************************************************
	> File Name: sem.h
	> Author: 
	> Mail: 
	> Created Time: Mon 12 Jun 2017 12:57:26 AM PDT
 ************************************************************************/
#ifndef __SEM__
#define __SEM__
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>

#define KEY_PATH "."
#define PROJECT_ID 88
int create_sem(int _semset_num);
int init_sem(int _sem_id, int _which);
int sem_p(int _sem_id, int _which);
int sem_v(int _sen_id, int _which);
int destroy_sem(int _sem_id);
int show_sem_val(int _sem_id, int _sem_num);
int get_sem();
static int op_sem(int sem_id, int op, int which);
#endif
