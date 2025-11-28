#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 505
#define MAXE 250000

typedef struct {
    int to, w, next;
} Edge;

Edge edges[MAXE];
int head[MAXN], edge_count;

int N, E;

int stack[MAXN], top;
int indexx[MAXN], lowlink[MAXN], onstack[MAXN], scc_id[MAXN], idx, scc_count;

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

/* ---------- TARJAN (SCC) ---------- */

void tarjan(int u) {
    indexx[u] = lowlink[u] = ++idx;
    stack[top++] = u;
    onstack[u] = 1;

    for (int e = head[u]; e != -1; e = edges[e].next) {
        int v = edges[e].to;
        if (!indexx[v]) {
            tarjan(v);
            if (lowlink[v] < lowlink[u]) lowlink[u] = lowlink[v];
        } else if (onstack[v]) {
            if (indexx[v] < lowlink[u]) lowlink[u] = indexx[v];
        }
    }

    if (lowlink[u] == indexx[u]) {
        scc_count++;
        int v;
        do {
            v = stack[--top];
            onstack[v] = 0;
            scc_id[v] = scc_count;
        } while (v != u);
    }
}

/* ---------- DIJKSTRA ---------- */

typedef struct {
    int node, dist;
} HeapNode;

HeapNode heap[MAXN * 10];
int heap_size;

void push(int node, int dist) {
    int i = heap_size++;
    while (i && heap[(i - 1) / 2].dist > dist) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i].node = node;
    heap[i].dist = dist;
}

HeapNode pop() {
    HeapNode result = heap[0];
    HeapNode temp = heap[--heap_size];

    int i = 0, child;
    while ((child = 2 * i + 1) < heap_size) {
        if (child + 1 < heap_size &&
            heap[child + 1].dist < heap[child].dist)
            child++;

        if (temp.dist <= heap[child].dist)
            break;

        heap[i] = heap[child];
        i = child;
    }
    heap[i] = temp;
    return result;
}

int dist_scc[MAXN];

int dijkstra(int start, int target) {
    for (int i = 1; i <= scc_count; i++)
        dist_scc[i] = INT_MAX;

    heap_size = 0;
    dist_scc[start] = 0;
    push(start, 0);

    while (heap_size) {
        HeapNode h = pop();
        int u = h.node, d = h.dist;
        if (d > dist_scc[u]) continue;
        if (u == target) return d;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].w;
            if (dist_scc[v] > d + w) {
                dist_scc[v] = d + w;
                push(v, dist_scc[v]);
            }
        }
    }
    return -1;
}

int main() {
    while (1) {
        scanf("%d %d", &N, &E);
        if (N == 0 && E == 0) break;

        memset(head, -1, sizeof(head));
        edge_count = 0;

        for (int i = 0; i < E; i++) {
            int x, y, h;
            scanf("%d %d %d", &x, &y, &h);
            add_edge(x, y, h);
        }

        /* ---- Compute SCCs ---- */
        memset(indexx, 0, sizeof(indexx));
        memset(onstack, 0, sizeof(onstack));
        idx = top = scc_count = 0;

        for (int i = 1; i <= N; i++)
            if (!indexx[i])
                tarjan(i);

        /* ---- Build condensed graph ---- */
        Edge new_edges[MAXE];
        int new_head[MAXN];
        int new_edge_count = 0;

        for (int i = 1; i <= scc_count; i++)
            new_head[i] = -1;

        for (int u = 1; u <= N; u++) {
            for (int e = head[u]; e != -1; e = edges[e].next) {
                int v = edges[e].to;
                int w = edges[e].w;
                int su = scc_id[u], sv = scc_id[v];

                int cost = (su == sv ? 0 : w);

                new_edges[new_edge_count].to = sv;
                new_edges[new_edge_count].w = cost;
                new_edges[new_edge_count].next = new_head[su];
                new_head[su] = new_edge_count++;
            }
        }

        /* Replace old graph with condensed graph */
        memcpy(edges, new_edges, sizeof(new_edges));
        memcpy(head, new_head, sizeof(new_head));
        edge_count = new_edge_count;

        int K;
        scanf("%d", &K);

        while (K--) {
            int o, d;
            scanf("%d %d", &o, &d);

            int so = scc_id[o], sd = scc_id[d];

            int ans = dijkstra(so, sd);

            if (ans < 0)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", ans);
        }

        printf("\n");
    }

    return 0;
}
