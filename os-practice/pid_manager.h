//
//  pid_manager.h
//  os-practice
//
//  Created by Karthik Pawar on 24/12/21.
//

#ifndef pid_manager_h
#define pid_manager_h

#include <stdio.h>

/*
 
 Linked list node
 
 */
typedef struct ll_node{
    int pid;
    int status;
    struct ll_node * next_node;
    struct ll_node * prev_node;
}ll_node;

/*
 
 Structure of a pid manager object
 */
typedef struct{
    ll_node * pid_array;
    ll_node * head_node;
    ll_node * tail_node;
}pid_map;

/*
 Creates a pid manager object
 */
pid_map allocate_map(void);

/*
 Get and reserve some valid pid from a pid manager
 */
int allocate_pid(pid_map * pmap);

/*
 Release a reserved pid from a pid manager
 */
void release_pid(pid_map * pmap, int pid);

#endif /* pid_manager_h */
