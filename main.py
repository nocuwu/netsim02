import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()

edges = [
         ("0: src",1),
         ("0: src",2),
         (1,2),
         (1,"3: dst"),
         (2,"3: dst")
        ]

G.add_edges_from(edges)

nx.draw(G, with_labels=True, font_size=10, node_size=2000, font_color="w")
plt.savefig("nx_tmp.png")
