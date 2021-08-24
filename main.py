import pulp
import networkx as nx

g = nx.Graph()

edges = [(1, 2, {'weight': 0.1}),
         (1, 3, {'weight': 0.1})]
         
g.add_edges_from(edges)

nx.draw(g)
