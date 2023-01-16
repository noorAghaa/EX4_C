#include "graph.h"
#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>

void insert_edge(pnode n, pnode to, int w)
{
    if (!n || !to)
        return;
    
    pedge newEdge = (pedge)malloc(sizeof(edge));

    newEdge->next = NULL;
    newEdge->weight = w;
    newEdge->endpoint = to;

    pedge ed = n->edges;

    while (ed && ed->next)
    {

        ed = ed->next;
    }

    if (!ed)
    {
        n->edges = newEdge;
        return;
    }

    ed->next = newEdge;
}

void printEdges(pnode node)
{
    if (node == NULL)
        return;

    pedge e = node->edges;
    printf("node key %d edges :\n", node->node_num);
    while (e)
    {
        printf("key %d w %d , ", e->endpoint->node_num, e->weight);
        e = e->next;
    }
    printf("\n");
}

void delete_edges(pnode head, pnode n)
{
    if (head == NULL)
        return;

    // delete in edges
    while (head)
    {
        pedge p = head->edges;
        pedge *prev = &head->edges;
        while (p)
        {
            if (p->endpoint == n)
            {
                *prev = p->next;
                free(p);
                p = *prev;
            }
            else
            {
                prev = &(p->next);
                p = p->next;
            }
        }

        head = head->next;
    }

    // delete out edges
    pedge ed = n->edges;
    while (ed)
    {
        pedge e = ed;
        ed = ed->next;
        free(e);
    }
}

void delete_out_edges(pnode n)
{
    // delete out edges
    pedge ed = n->edges;
    while (ed)
    {
        pedge e = ed;
        ed = ed->next;
        free(e);
    }
    n->edges = NULL;
}