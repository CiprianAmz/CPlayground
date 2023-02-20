#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_SCORE 999999

// competence from 0 to 10 for each language
typedef struct {
    int c;
    int python;
} Competence;

typedef struct {
    Competence competence;
    int planned_days;
    char name[40];
} Task;

typedef struct TaskNodeList {
    Task* task;
    struct TaskNodeList* next;
} TaskNodeList;

typedef struct {
    Competence competence;
    int total_days;
    int remaining_working_days;
    char name[20];

    TaskNodeList* tasks_list;
} DevAllocation;

/*
    Use the manhattan distance to compare devs to tasks based on competence.
    https://xlinux.nist.gov/dads/HTML/manhattanDistance.html
*/
int manhattan_distance(Competence c1, Competence c2) {
    return abs(c1.c - c2.c) + abs(c1.python - c2.python);
}

void add_to_task_list(TaskNodeList** head, Task* task) {
    TaskNodeList* it = *head;

    // check if there is a head
    if (!(*head)) {
        *head = malloc(sizeof(TaskNodeList));
        (*head)->task = task;
        (*head)->next = NULL;

        return;
    }

    // parse to the end of list
    while (it -> next) {
        it = it->next;
    }

    it->next = malloc(sizeof(TaskNodeList));
    it->next->task = task;
    it->next->next = NULL;
}

void print_allocation(DevAllocation devs[], int n_devs) {
    int dev_it;

    for (dev_it = 0; dev_it < n_devs; dev_it++) {
        TaskNodeList* tasks_it = devs[dev_it].tasks_list;        

        printf(
            "Developer: %s {c: %d, python: %d}\n",
            devs[dev_it].name,
            devs[dev_it].competence.c,
            devs[dev_it].competence.python
            );
        printf("Total working days: %d\n", devs[dev_it].total_days);
        printf("Remaining working days: %d\n", devs[dev_it].remaining_working_days);
        printf("Tasks:\n");
        
        while(tasks_it) {
            printf(
                "  %s {c: %d, python: %d, estimated_time: %d}\n",
                tasks_it->task->name,
                tasks_it->task->competence.c * 10,
                tasks_it->task->competence.python * 10,
                tasks_it->task->planned_days
            );
            tasks_it = tasks_it->next;
        }

        printf("\n");
    }
}

/*
    Used to free the linked lists used to save the tasks.
*/
void free_devs_allocation_dynamic_memory(DevAllocation devs[], size_t devs_n) {
    int dev_it;

    for (dev_it = 0; dev_it < devs_n; dev_it++) {
        TaskNodeList* tasks_it = devs[dev_it].tasks_list;        

        while (tasks_it) {
            TaskNodeList* current_node = tasks_it;
            tasks_it = tasks_it->next;
            free(current_node);
        }
    }
}

void solve(DevAllocation devs[], size_t devs_n, Task tasks[], size_t tasks_n) {
    int task_it;
    int dev_it;

    for (task_it = 0; task_it < tasks_n; task_it++) {
        int best_score = DEFAULT_SCORE;
        DevAllocation* dev_ptr = NULL;

        for (dev_it = 0; dev_it < devs_n; dev_it++) {
            int current_score = manhattan_distance(tasks[task_it].competence, devs[dev_it].competence);

            if (
                ( current_score < best_score)
                &&
                ( tasks[task_it].planned_days <= devs[dev_it].remaining_working_days )
             ) {
                best_score = current_score;
                dev_ptr = &devs[dev_it];
            }
        }

        if (!dev_ptr) {
            printf("Sprint can't be completed!\nCurrent allocation:\n");
            print_allocation(devs, devs_n);
            return;
        }

        dev_ptr->remaining_working_days -= tasks[task_it].planned_days;
        add_to_task_list(&dev_ptr->tasks_list, &tasks[task_it]);
    }

    printf("Sprint can be completed!\nCurrent allocation:\n");
    print_allocation(devs, devs_n);
}

void solve_task_1() {
    DevAllocation devs[] = {
    /*    {python, c}, total_days, remaining_working_days, name, tasks_list*/
        { {10, 2}, 20, 20, "John", NULL },
        { {3 , 4}, 20, 20, "Gary", NULL },
        { {5 , 8}, 20, 20, "Anne", NULL }
    };

    /*
        The language percentage was divided by 10 in order to normalize with the dev skill;
        ex: python 90% -> python 9
            c      10% -> c      1
    */
    Task tasks[] = {
    /* {c, python}, planned_days, name */
        { {10, 0},  10, "Write an ADC driver"               },
        { {4 , 6},  5 , "Create tests for Clock driver"     },
        { {8 , 2},  10, "Create new demo application"       },
        { {1 , 9},  2 , "Fix bug found by customer"         },
        { {5 , 5},  7 , "Analyze feature request"           },
        { {9 , 1},  10, "Implement new partitioning schema" }
    };

    solve(
        devs, sizeof(devs) / sizeof(DevAllocation),
        tasks, sizeof(tasks) / sizeof(Task)
    );

    free_devs_allocation_dynamic_memory(devs, sizeof(devs) / sizeof(DevAllocation));
}

void solve_task_2() {
    DevAllocation devs[] = {
    /*    {python, c}, total_days, remaining_working_days, name, tasks_list*/
        { {10, 2}, 20, 20, "John", NULL },
        { {3 , 4}, 20, 20, "Gary", NULL },
        { {5 , 8}, 15, 15, "Anne", NULL } // Anne has 5 days off
    };

    /*
        The language percentage was divided by 10 in order to normalize with the dev skill;
        ex: python 90% -> python 9
            c      10% -> c      1
    */
    Task tasks[] = {
    /* {c, python}, planned_days, name */
        { {10, 0},  10, "Write an ADC driver"               },
        { {4 , 6},  5 , "Create tests for Clock driver"     },
        { {8 , 2},  10, "Create new demo application"       },
        { {1 , 9},  2 , "Fix bug found by customer"         },
        { {5 , 5},  7 , "Analyze feature request"           },
        { {9 , 1},  10, "Implement new partitioning schema" }
    };

    solve(
        devs, sizeof(devs) / sizeof(DevAllocation),
        tasks, sizeof(tasks) / sizeof(Task)
    );

    free_devs_allocation_dynamic_memory(devs, sizeof(devs) / sizeof(DevAllocation));
}

int main() {
    printf("Task 1:\n\n");
    solve_task_1();
    printf("\n\n--------------\nTask 2:\n\n");
    solve_task_2();

    return 0;
}