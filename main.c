#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    pnode graph = NULL;

    int flag = 1;
    int hasNextChar = 0;
    char scanedChar;
    while (flag)
    {
        if (!hasNextChar)
        {
            int in = scanf(" %c", &scanedChar);
            if (in == 0 || in == -1)
            {
                flag = 0;
            }
        }
        if (flag)
        {
            hasNextChar = 0;
            switch (scanedChar)
            {
            case 'A':
                scanedChar = build_graph_cmd(&graph);
                hasNextChar = 1;
                break;

            case 'B':
                insert_node_cmd(&graph);
                break;

            case 'D':
                delete_node_cmd(&graph);
                break;

            case 'P':
                printGraph_cmd(graph);
                break;

            case 'S':
                shortsPath_cmd(graph);
                break;

            case 'T':
                TSP_cmd(graph);
                break;
            }
        }
    }
    deleteGraph_cmd(&graph);
    return 0;
}