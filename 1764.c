#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
    int w;
} Edge;

int parent[40000];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    int M, N;

    while (1) {
        scanf("%d %d", &M, &N);
        if (M == 0 && N == 0) break;

        Edge *edges = (Edge*) malloc(N * sizeof(Edge));

        for (int i = 0; i < M; i++)
            parent[i] = i;

        for (int i = 0; i < N; i++)
            scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

        qsort(edges, N, sizeof(Edge), cmp);

        long long mst = 0;
        int edges_used = 0;

        for (int i = 0; i < N && edges_used < M - 1; i++) {
            int pu = find(edges[i].u);
            int pv = find(edges[i].v);

            if (pu != pv) {
                parent[pu] = pv;
                mst += edges[i].w;
                edges_used++;
            }
        }

        printf("%lld\n", mst);

        free(edges);
    }

    return 0;
}
