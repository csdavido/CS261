/*
 * CS 261 Assignment 5
 * Name: David Rider    
 * Date: 5/26/2017
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name)
{
    // FIXME: implement
    Task *newTask = malloc(sizeof(Task));
    strcpy(newTask->name, name);
    newTask->priority = priority;
    
    return newTask;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
    // FIXME: implement
    Task *leftPtr = (Task*) left;
    Task *rightPtr = (Task*) right;

    int compare = 0;

    if (leftPtr->priority < rightPtr->priority) {
    	compare = -1;
    } else if (leftPtr->priority > rightPtr->priority) {
    	compare = 1;
    }
    return compare;
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("(%d, %s)", task->priority, task->name);
}
