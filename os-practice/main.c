//
//  pid-manager.c
//  os-ipc
//
//  Created by Karthik Pawar on 24/12/21.
//

#include <stdio.h>
#include "pid_manager.h"
int main(){

    pid_map pm_map = allocate_map();
    pid_map pm_map1 = allocate_map();
    int p1 = allocate_pid(&pm_map);
    int p2 = allocate_pid(&pm_map);
    printf("GET %d, %d \n", p1, p2);
    release_pid(&pm_map, p1);
    printf("get: %d \n", allocate_pid(&pm_map));
    int p3 = allocate_pid(&pm_map1);
    int p4 = allocate_pid(&pm_map1);
    printf("GET 2 %d, %d \n", p3, p4);
    release_pid(&pm_map1, p3);
    printf("get: %d \n", allocate_pid(&pm_map1));
    return 0;
}
