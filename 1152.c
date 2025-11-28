#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
    int w;
} Edge;

int parent[200001];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    int m, n;

    while (1) {
        scanf("%d %d", &m, &n);
        if (m == 0 && n == 0) break;

        Edge *edges = (Edge*) malloc(n * sizeof(Edge));
        long long total = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
            total += edges[i].w;
        }

        for (int i = 0; i < m; i++)
            parent[i] = i;

        qsort(edges, n, sizeof(Edge), cmp);

        long long mst = 0;
        for (int i = 0; i < n; i++) {
            int pu = find(edges[i].u);
            int pv = find(edges[i].v);

            if (pu != pv) {
                parent[pu] = pv;
                mst += edges[i].w;
            }
        }

        printf("%lld\n", total - mst);

        free(edges);
    }

    return 0;
}
