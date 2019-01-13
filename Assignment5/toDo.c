/*
 * CS 261 Assignment 5
 * Name: David Rider
 * Date: 5/23/2017
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
    char *file = malloc(sizeof(char) * 256);
    char *task = malloc(sizeof(char) * 256);

    int priority;

    switch (command) {
    	case 'l':
    		printf("Enter file name: ");
            
            fgets(file, 100, stdin);
            
            if (file[strlen(file) - 1] == '\n') {
                file[strlen(file) - 1] = 0;
            }
            
            FILE * readFile = fopen(file, "r");
            
            listLoad(list, readFile);
            
            printf("List read successfully.\n");
            printf("\n");
            
            fclose(readFile);

    		break;
    	case 's':
    		printf("Enter file name: ");
            
            fgets(file, 100, stdin);
            
            if (file[strlen(file) - 1] == '\n') {
                file[strlen(file) - 1] = 0;
            }
            
            FILE *writtenFile = fopen(file, "w+");
            
            listSave(list, writtenFile);
            
            printf("The list was saved to the file: '%s'.\n", file);
            printf("\n");
            
            fclose(writtenFile);

    		break;
    	case 'a':
    		printf("Enter task: ");
            
            fgets(task, 100, stdin);
            
            if (task[strlen(task) - 1] == '\n') {
                task[strlen(task) - 1] = 0;
            }
            
            printf("Enter task priority (0-999): ");
            
            scanf("%d", &priority);
            
            while (getchar() != '\n');
            
            Task *newTask = taskNew(priority, task);
            
            dyHeapAdd(list, newTask, taskCompare);
            
            printf("'%s' added.\n", task);
            printf("\n");

    		break;
    	case 'g':
    		if (dySize(list) != 0) {
                printf("First task: %s\n", ((struct Task *)dyHeapGetMin(list))->name);
            } else {
                printf("Task list is empty.\n");
            }
            
            printf("\n");

    		break;
    	case 'r':
    		 if (dySize(list) == 0) {
                printf("List is empty.\n");
            } else {
                struct Task* rem = (struct Task*)dyHeapGetMin(list);
                
                printf("'%s' removed from the list.\n",rem->name);
                
                dyHeapRemoveMin(list, taskCompare);
                
                taskDelete(rem);
            }
            
            printf("\n");

    		break;
    	case 'p':
    		if (dySize(list) == 0) {
                printf("List is empty.\n");
            } else {
                listPrint(list);
            }
            
            printf("\n");

    		break;
    	case 'e':
    		printf("Exiting program.\n");
    		free(file);
    		free(task);
    		break;
    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
 /* free dynamically allocated List pointers in array to avoid memory leaks */
         /* Fix it */

    dyDelete(list);
    return 0;
}