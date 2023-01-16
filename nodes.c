#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "edges.h"

pnode getNode(pnode head, int key)
{

    while (head && head->node_num != key)
    {
        head = head->next;
    }
    if (!head)
        return NULL;
    return head;
}

void insert_node_cmd(pnode *head)
{
    int key;
    scanf("%d", &key);

    pnode newNode = getNode(*head, key);
    int exsists = 0;
    if (newNode == NULL)
    {
        newNode = (pnode)malloc(sizeof(node));
        newNode->next = NULL;
        newNode->node_num = key;
        newNode->edges = NULL;
    }
    else
    {
        exsists = 1;
        delete_out_edges(newNode);
    }

    // insert edges
    int w, to;
    while (scanf("%d", &to) > 0)
    {
        scanf("%d", &w);
        insert_edge(newNode, getNode(*head, to), w);
    }

    if (exsists)
        return;

    if (!*head)
    {
        *head = newNode;
        return;
    }

    pnode p = *head;
    while (p->next)
    {
        p = p->next;
    }
    p->next = newNode;
}

void delete_node_cmd(pnode *head)
{
    if (*head == NULL)
        return;

    int key;
    scanf("%d", &key);

    pnode p = *head;
    pnode *prev = head;
    while (p)
    {
        if (p->node_num == key)
        {
            break;
        }
        else
        {
            prev = &(p->next);
            p = p->next;
        }
    }

    if (!p)
        return;

    // delete edges
    delete_edges(*head, p);
    // free node
    *prev = p->next;
    free(p);
}

void printGraph_cmd(pnode head)
{
    while (head)
    {
        printf("\\%d\\  \n", head->node_num);
        printEdges(head);
        head = head->next;
    }
}

void deleteGraph_cmd(pnode *head)
{
    pnode p = *head;
    while (p)
    {
        delete_out_edges(p);
        pnode temp = p;
        p = p->next;
        free(temp);
    }
    *head = NULL;
}

char build_graph_cmd(pnode *head)
{
    if (*head)
        deleteGraph_cmd(head);

    int size;
    scanf("%d", &size);

    pnode *h = head;
    for (int i = 0; i < size; i++)
    {
        pnode newNode = (pnode)malloc(sizeof(node));
        newNode->next = NULL;
        newNode->node_num = i;
        newNode->edges = NULL;

        *h = newNode;
        h = &(*h)->next;
    }

    int flag = 1;
    char ch;
    while (flag && scanf(" %c", &ch) > 0)
    {
        if (ch == 'n')
        {
            int key;
            // get key
            scanf("%d", &key);

            // insert edges
            int w, to;
            pnode node = getNode(*head, key);
            while (scanf("%d", &to) > 0)
            {
                scanf("%d", &w);
                insert_edge(node, getNode(*head, to), w);
            }
        }
        else
        {
            flag = 0;
        }
    }

    return ch;
}