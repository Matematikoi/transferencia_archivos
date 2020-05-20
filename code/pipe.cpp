#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<iostream>
#include<vector>

using namespace std;

//const int NUMBER_OF_ITEMS = 25000000;
const int NUMBER_OF_ITEMS = 25000;

int main()
{
    pid_t pid;
    int r;
    int pipefd[2];

    r = pipe(pipefd);
    if (r < 0)
    {
        perror("Error pipe() ");
        exit(-1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(pipefd[0]);
        int *arr = new int[NUMBER_OF_ITEMS];
        for(int i = 0; i < NUMBER_OF_ITEMS; i++)arr[i] = i;
        r = write(pipefd[1], arr, NUMBER_OF_ITEMS*sizeof(int));
        if (r < 0)
        {
            perror("error writing");
        }
        close(pipefd[1]);
        delete [] arr;
        exit(0);
    }
    else
    {
        close(pipefd[1]);
        int *res = new int[NUMBER_OF_ITEMS];
        r = read(pipefd[0], res, NUMBER_OF_ITEMS*sizeof(int));
        if (r < 0)
        {
            perror("error reading");
        }
        for(int i = 0; i < NUMBER_OF_ITEMS; i++)cout << res[i]<<'\n';
        close(pipefd[0]);
        delete [] res;
    }
}