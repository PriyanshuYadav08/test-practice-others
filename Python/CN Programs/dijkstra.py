import heapq

def dijkstra(graph, start):
    # initialize distances and parents
    dist = {node: float('inf') for node in graph}
    parent = {node: None for node in graph}
    dist[start] = 0

    pq = [(0, start)]   # (distance, node)

    while pq:
        current_dist, u = heapq.heappop(pq)
        if current_dist > dist[u]:
            continue

        for v, w in graph[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                parent[v] = u
                heapq.heappush(pq, (dist[v], v))

    return dist, parent

def reconstruct_path(parent, start, target):
    path = []
    node = target
    while node is not None:
        path.append(node)
        node = parent[node]
    path.reverse()
    if path and path[0] == start:
        return path
    return []

# ---------- TOP-LEVEL DEMO (NO MAIN) ----------

print("=== DIJKSTRA SHORTEST PATH ROUTING ===")

# example network graph (adjacency list)
graph = {
    'A': [('B', 2), ('C', 5)],
    'B': [('A', 2), ('C', 1), ('D', 4)],
    'C': [('A', 5), ('B', 1), ('D', 2)],
    'D': [('B', 4), ('C', 2)]
}

start_node = 'A'
distances, parents = dijkstra(graph, start_node)

print("Shortest distances from node", start_node)
for node in graph:
    print(f"{start_node} -> {node} = {distances[node]}")

print("\nPaths from node", start_node)
for node in graph:
    path = reconstruct_path(parents, start_node, node)
    print(f"{start_node} -> {node}: {path}")