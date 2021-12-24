//
//  pid_manager.c
//  os-practice
//
//  Created by Karthik Pawar on 24/12/21.
//

#include "pid_manager.h"
#include <stdio.h>
#include <stdlib.h>
#define MIN_PID 300
#define MAX_PID 5000

pid_map allocate_map(void){
    ll_node * PID_MAP = malloc((MAX_PID-MIN_PID+1)*sizeof*PID_MAP);
    int ending_pid = (MAX_PID - MIN_PID);
    for(int i=0; i<=(ending_pid); i++){
        PID_MAP[i].pid = MIN_PID + i;
        PID_MAP[i].status = 0;
    }
    
    for(int j =0; j<(ending_pid+1); j++){
        if(j == ending_pid){
            PID_MAP[j].next_node = NULL;
            PID_MAP[j].prev_node = &PID_MAP[j-1];
            continue;
        }
        if(j == 0){
            PID_MAP[j].prev_node = NULL;
            PID_MAP[j].next_node = &PID_MAP[j+1];
            continue;
        }
        if(j>0 && j<ending_pid){
            PID_MAP[j].next_node = &PID_MAP[j+1];
            PID_MAP[j].prev_node = &PID_MAP[j-1];
        }
        
    }
    PID_MAP[ending_pid].next_node = NULL;
    pid_map pmap;
    pmap.pid_array = PID_MAP;
    pmap.head_node = &PID_MAP[0];
    pmap.tail_node = &PID_MAP[ending_pid];
    return pmap;
}

int allocate_pid(pid_map * pmap){
    if(pmap->head_node->status==1){
        return -1;
    }
    // pluck head node
    ll_node * temp_head_node = pmap->head_node;
    pmap->head_node->status = 1;
    int allocated_pid = temp_head_node->pid;
    pmap->head_node = pmap->head_node->next_node;
    if(pmap->head_node->prev_node){
        pmap->head_node->prev_node = NULL;
    }
    
    // insert at end
    pmap->tail_node->next_node = temp_head_node;
    temp_head_node->prev_node = pmap->tail_node;
    temp_head_node->next_node = NULL;
    pmap->tail_node = temp_head_node;

    return allocated_pid;
}


void release_pid(pid_map * pmap, int pid){

    ll_node *pid_array = pmap->pid_array;
    if(pid_array[pid-MIN_PID].status == 0){
        return;
    }
    // 1. get ll_node from array
    
    ll_node *temp_block = &(pmap->pid_array[pid-MIN_PID]);
    if(temp_block->prev_node != NULL){
        temp_block->prev_node->next_node = temp_block->next_node;
    }
    if(temp_block->next_node != NULL){
        temp_block->next_node->prev_node = temp_block->prev_node;
    }
    temp_block->status = 0;
    temp_block->prev_node = NULL;
    temp_block->next_node = pmap->head_node;
    pmap->head_node = temp_block;
}
