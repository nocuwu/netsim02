import networkx as nx
import matplotlib.pyplot as plt

Data = open('data.txt', "r")
next(Data, None)
Graphtype = nx.Graph()

G = nx.read_weighted_edgelist(Data)

nx.draw(G, with_labels=True, font_size=10, node_size=2000, font_color="w")
plt.savefig("nx_tmp.png")
