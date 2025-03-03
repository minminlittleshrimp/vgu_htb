#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <dlt/dlt.h>
#include <errno.h>
#include <string.h>

DLT_DECLARE_CONTEXT(ctx);

#define MAX_THREADS 5

sem_t t_dlt_mutex;
int total_hold = 0;
int enable_malicious = 0;
int enable_exit = 0;
int malicious_speed = 1;
int exit_delay = 1;

#define T_DLT_SEM_LOCK() do { \
    while ((sem_wait(&t_dlt_mutex) == -1) && (errno == EINTR)) \
        continue; /* Restart if interrupted */ \
} while (false)

#define T_DLT_SEM_FREE() { sem_post(&t_dlt_mutex); }

void print_help() {
    printf("Usage: ./program [OPTIONS]\n");
    printf("  -m [speed]   Enable malicious thread with optional speed (default: 1s)\n");
    printf("  -e [delay]   Enable exit thread with optional delay (default: 1s)\n");
    printf("  -h           Show this help message\n");
}

void* legitimate_thread(void *arg) {
    int thread_num = *((int *)arg);
    while (1) {
        T_DLT_SEM_LOCK();
        DLT_LOG(ctx, DLT_LOG_INFO, DLT_CSTRING("Legitimate thread: Logging message"));
        printf("Legitimate thread %d: Logging message\n", thread_num);
        sleep(1);
        T_DLT_SEM_FREE();
    }
    return NULL;
}

void* malicious_thread(void *arg) {
    while (1) {
        printf("Malicious thread: Holding the semaphore, total hold: %d \n", total_hold);
        T_DLT_SEM_LOCK();
        total_hold++;
        sleep(malicious_speed); // Hold semaphore for specified duration
    }
    return NULL;
}

void* exit_thread(void *arg) {
    printf("Exit thread: Observing issue for %d seconds before exit()\n", exit_delay);
    sleep(exit_delay);
    printf("Exit thread: Calling exit()\n");
    exit(EXIT_SUCCESS);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t threads[MAX_THREADS];
    pthread_t attacker, exiter;
    int thread_nums[MAX_THREADS - 2];

    // Parse arguments
    if (argc == 1) {
        fprintf(stderr, "Error: No arg, please use one: -m or -e.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0) {
            enable_malicious = 1;
            if (i + 1 < argc) {
                malicious_speed = atof(argv[i + 1]);
                if (malicious_speed <= 0) {
                    malicious_speed = 1;
                }
            }
        } else if (strcmp(argv[i], "-e") == 0) {
            enable_exit = 1;
            if (i + 1 < argc) {
                exit_delay = atof(argv[i + 1]);
                if (exit_delay <= 0) {
                    exit_delay = 1;
                }
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            print_help();
            exit(EXIT_SUCCESS);
        }
    }

    // Ensure only one is enabled
    if (enable_malicious && enable_exit) {
        fprintf(stderr, "Error: Cannot enable both malicious and exit threads. Use only -m or -e.\n");
        return EXIT_FAILURE;
    }

    DLT_REGISTER_APP("HELO", "Test App for DLT");
    DLT_REGISTER_CONTEXT(ctx, "CTX1", "DLT Context");

    sem_init(&t_dlt_mutex, 0, MAX_THREADS - 2);

    // Create legitimate threads
    for (int i = 0; i < MAX_THREADS - 2; i++) {
        thread_nums[i] = i + 1;
        pthread_create(&threads[i], NULL, legitimate_thread, &thread_nums[i]);
    }

    // Create the malicious thread if enabled
    if (enable_malicious) {
        pthread_create(&attacker, NULL, malicious_thread, NULL);
    }

    // Create the exit thread if enabled
    if (enable_exit) {
        pthread_create(&exiter, NULL, exit_thread, NULL);
    }

    for (int i = 0; i < MAX_THREADS - 2; i++) {
        pthread_join(threads[i], NULL);
    }

    if (enable_malicious) {
        pthread_join(attacker, NULL);
    }

    if (enable_exit) {
        pthread_join(exiter, NULL);
    }

    DLT_UNREGISTER_CONTEXT(ctx);
    DLT_UNREGISTER_APP();
    sem_destroy(&t_dlt_mutex);

    return 0;
}
