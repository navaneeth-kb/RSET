#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define SHM_SIZE 1024
int main()
{
    char str[] = &quot;Hello World&quot;;
    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    char *data = (char *)shmat(shmid, (void *)0, 0);
    if (shmid &lt; 0)
    {
        perror(&quot;shmget&quot;);
        exit(1);
    }
    // Writing the string to shared memory
    strcpy(data, str);
    printf(&quot;Parent: String \&quot;%s\&quot; written to shared memory.\n&quot;,
    str);
    // Creating a child process
    pid_t pid = fork();
    if (pid &lt; 0)
    {
        perror(&quot;fork&quot;);
        exit(1);
    }
    if (pid == 0)
    {
        // Child process
        printf(&quot;Child: Reading string from shared memory:

        \&quot;%s\&quot;\n&quot;, data);

        // Reversing the string
        int len = strlen(data);
        for (int i = 0; i &lt; len / 2; i++)
        {
            char temp = data[i];
            data[i] = data[len - i - 1];
            data[len - i - 1] = temp;
        }
        // Printing the reversed string
        printf(&quot;Child: Reversed string: \&quot;%s\&quot;\n&quot;, data);
        // Detaching from shared memory
        shmdt(data);
    }
    else
    {
        // Parent process
        wait(NULL); // Wait for child process to finish
        // Printing the original string
        printf(&quot;Parent: Original string: \&quot;%s\&quot;\n&quot;, str);
        // Printing the reversed string (modified by the child process)

        printf(&quot;Parent: Reversed string: \&quot;%s\&quot;\n&quot;, data);
        // Detaching from shared memory
        shmdt(data);
        // Deleting the shared memory segment
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}