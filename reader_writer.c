#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Shared variables
int data = 0;
int readers_count = 0;

// Semaphores
sem_t mutex, write_mutex;

// Function prototypes
void *reader(void *arg);
void *writer(void *arg);

int main()
{   
    printf("Sahib Preet Singh AI-ML 00713211621")
    // Initialize semaphores
    sem_init(&mutex, 0, 1);       // Semaphore for mutual exclusion among readers
    sem_init(&write_mutex, 0, 1); // Semaphore for mutual exclusion for writers

    // Create reader and writer threads
    pthread_t reader_thread[5], writer_thread[5];
    int i;

    for (i = 0; i < 5; i++)
    {
        pthread_create(&reader_thread[i], NULL, reader, (void *)(intptr_t)i);
        pthread_create(&writer_thread[i], NULL, writer, (void *)(intptr_t)i);
    }

    // Join threads
    for (i = 0; i < 5; i++)
    {
        pthread_join(reader_thread[i], NULL);
        pthread_join(writer_thread[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&write_mutex);

    return 0;
}

void *reader(void *arg)
{
    int reader_id = (intptr_t)arg;

    while (1)
    {
        // Entry section
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1)
        {
            sem_wait(&write_mutex); // If this is the first reader, lock the writers out
        }
        sem_post(&mutex); // Exit section

        // Critical section (reading)
        printf("Reader %d is reading data: %d\n", reader_id, data);

        // Exit section
        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0)
        {
            sem_post(&write_mutex); // If this is the last reader, writers can access
        }
        sem_post(&mutex); // Exit section

        // Sleep to simulate reading time
        sleep(1);
    }

    pthread_exit(NULL);
}

void *writer(void *arg)
{
    int writer_id = (intptr_t)arg;

    while (1)
    {
        // Entry section
        sem_wait(&write_mutex);

        // Critical section (writing)
        data++;
        printf("Writer %d is writing data: %d\n", writer_id, data);

        // Exit section
        sem_post(&write_mutex);

        // Sleep to simulate writing time
        sleep(2);
    }

    pthread_exit(NULL);
}
