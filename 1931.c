#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000

typedef struct Edge {
    int to;
    int w;
    int next;
} Edge;

typedef struct {
    int u;
    int parity;  // 0 = número de pedágios até aqui é par; 1 = ímpar
    int dist;
} NodePQ;

typedef struct {
    NodePQ *heap;
    int size;
    int capacity;
} MinHeap;

void heap_init(MinHeap *h, int cap) {
    h->heap = (NodePQ*) malloc((cap+1) * sizeof(NodePQ));
    h->size = 0;
    h->capacity = cap;
}

void heap_free(MinHeap *h) {
    free(h->heap);
}

void heap_push(MinHeap *h, int u, int parity, int dist) {
    if (h->size + 1 > h->capacity) {
        // redimensionar
        h->capacity *= 2;
        h->heap = (NodePQ*) realloc(h->heap, (h->capacity + 1) * sizeof(NodePQ));
    }
    int i = ++h->size;
    while (i > 1 && h->heap[i/2].dist > dist) {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i].u = u;
    h->heap[i].parity = parity;
    h->heap[i].dist = dist;
}

NodePQ heap_pop(MinHeap *h) {
    NodePQ ret = h->heap[1];
    NodePQ tmp = h->heap[h->size--];
    int i = 1;
    while (2*i <= h->size) {
        int c = 2*i;
        if (c+1 <= h->size && h->heap[c+1].dist < h->heap[c].dist)
            c++;
        if (h->heap[c].dist < tmp.dist) {
            h->heap[i] = h->heap[c];
            i = c;
        } else break;
    }
    h->heap[i] = tmp;
    return ret;
}

int main() {
    int C, V;
    if (scanf("%d %d", &C, &V) != 2) return 0;

    // Aloca dinamicamente lista de adjacência
    int *head = (int*) malloc((C+1) * sizeof(int));
    for (int i = 1; i <= C; i++) head[i] = -1;

    // haverá no máximo V arestas bidirecionais → 2*V entradas
    Edge *edges = (Edge*) malloc((2 * V) * sizeof(Edge));
    int edge_cnt = 0;

    for (int i = 0; i < V; i++) {
        int c1, c2, g;
        scanf("%d %d %d", &c1, &c2, &g);
        // c1 -> c2
        edges[edge_cnt].to = c2;
        edges[edge_cnt].w = g;
        edges[edge_cnt].next = head[c1];
        head[c1] = edge_cnt++;
        // c2 -> c1 (bidirecional)
        edges[edge_cnt].to = c1;
        edges[edge_cnt].w = g;
        edges[edge_cnt].next = head[c2];
        head[c2] = edge_cnt++;
    }

    // dist[u][paridade] — 0 = par, 1 = ímpar
    int (*dist)[2] = malloc((C+1) * 2 * sizeof(int));
    for (int i = 1; i <= C; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    // Dijkstra com estado paridade
    MinHeap pq;
    heap_init(&pq, C * 2 + 5);

    dist[1][0] = 0;
    heap_push(&pq, 1, 0, 0);

    int answer = -1;

    while (pq.size > 0) {
        NodePQ cur = heap_pop(&pq);
        int u = cur.u;
        int p = cur.parity;
        int d = cur.dist;
        if (d > dist[u][p]) continue;

        // Se chegamos à cidade C com paridade 0 (par), já é melhor possível
        if (u == C && p == 0) {
            answer = d;
            break;
        }

        // Percorrer arestas
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].w;
            int np = 1 - p;  // muda paridade
            int nd = d + w;
            if (nd < dist[v][np]) {
                dist[v][np] = nd;
                heap_push(&pq, v, np, nd);
            }
        }
    }

    if (answer < 0) {
        // pode haver caso em que Dijkstra termina sem encontrar (C,par)
        if (dist[C][0] < INF) answer = dist[C][0];
    }

    if (answer >= 0 && answer < INF)
        printf("%d\n", answer);
    else
        printf("-1\n");

    // liberar memória
    free(head);
    free(edges);
    free(dist);
    heap_free(&pq);

    return 0;
}
