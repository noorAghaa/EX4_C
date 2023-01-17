#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "nodes.h"

int getGraphSize(pnode h)
{
    int cnt = 0;
    while (h)
    {
        cnt++;
        h = h->next;
    }
    return cnt;
}

int getMaxId(pnode h)
{
    if (h == NULL)
    {
        return -1;
    }

    int max = h->node_num;
    while (h)
    {
        if (h->node_num > max)
        {
            max = h->node_num;
        }
        h = h->next;
    }

    return max;
}

int getMin(int dist[], int visited[], int len)
{
    int min = -1;

    for (int i = 0; i < len; i++)
    {
        if (min == -1)
        {
            if (dist[i] != INT_MAX && !visited[i])
                min = i;
        }
        else if (dist[i] != INT_MAX && dist[i] < dist[min] && !visited[i])
            min = i;
    }
    return min;
}

int isEmpty(int visited[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (!visited[i])
        {
            return 0;
        }
    }
    return 1;
}

// Dijkstra Algorithm
int shortsPath_cmdDi(pnode head, int from, int to)
{
    if (head == NULL)
        return -1;

    int distLen = getMaxId(head) + 1;
    int *dist = (int *)malloc(sizeof(int) * distLen);
    int *visited = (int *)malloc(sizeof(int) * distLen);

    // init dist
    for (int i = 0; i < distLen; i++)
    {
        visited[i] = 0;
        if (getNode(head, i) == NULL)
            visited[i] = 1;
    }

    // init weights
    for (int i = 0; i < distLen; i++)
        dist[i] = INT_MAX;
    dist[from] = 0;

    int min;
    while (!isEmpty(visited, distLen) && (min = getMin(dist, visited, distLen)) != -1)
    {
        pnode p = getNode(head, min);
        pedge edge = p->edges;
        while (edge)
        {
            if (!visited[edge->endpoint->node_num])
            {
                if (dist[p->node_num] != INT_MAX && dist[p->node_num] + edge->weight < dist[edge->endpoint->node_num])
                {
                    dist[edge->endpoint->node_num] = dist[p->node_num] + edge->weight;
                }
            }
            edge = edge->next;
        }
        visited[min] = 1;
    }

 
    free(visited);

    if (dist[to] == INT_MAX)
    {
        free(dist);
        return -1;
    }

    int x = dist[to];
    free(dist);
    return x;
}

// Dijkstra Algorithm
void shortsPath_cmd(pnode head)
{
    if (head == NULL)
        return;

    int from, to;
    scanf("%d %d", &from, &to);

    int res = shortsPath_cmdDi(head, from, to);

    if (res == -1)
    {
        printf("Dijsktra shortest path: -1 \n");
        return;
    }
    printf("Dijsktra shortest path: %d \n", res);
}

int *arrayRemoveElement(int arr[], int len, int k)
{
    int *newArr = (int *)malloc(sizeof(int) * len - 1);
    for (int i = 0, j = 0; i < len; i++)
    {
        if (i != k)
        {
            newArr[j] = arr[i];
            j++;
        }
    }
    return newArr;
}

// for debug
void printArr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ,", arr[i]);

    printf("\n");
}

int tsp(pnode head, int from, int arr[], int len)
{
    if (len == 1)
        return shortsPath_cmdDi(head, from, arr[0]);

    int min = INT_MAX;

    for (int i = 0; i < len; i++)
    {
        if (i != from)
        {
            int *s = arrayRemoveElement(arr, len, i);
            int sh = shortsPath_cmdDi(head, from, arr[i]);
            int res = tsp(head, arr[i], s, len - 1);

            if (sh != -1 && res != -1 && res + sh < min)
                min = res + sh;

            free(s);
        }
    }

    if (min == INT_MAX)
        return -1;
    return min;
}

void TSP_cmd(pnode head)
{
    int size = 0;
    scanf("%d", &size);

    int *arr = (int *)malloc(sizeof(int) * size);

    if (arr == NULL)
    {
        printf("Error: malloc failed\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    int min = INT_MAX;
    for (int i = 0; i < size; i++)
    {
        int *s = arrayRemoveElement(arr, size, i);
        int x = tsp(head, arr[i], s, size - 1);
        if (x != -1 && min > x)
        {
            min = x;
        }
        free(s);
    }
    if (min == INT_MAX)
    {
        printf("TSP shortest path: -1 \n");
    }
    else
    {
        printf("TSP shortest path: %d \n", min);
    }

    free(arr);
}
