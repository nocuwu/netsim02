import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd
from ortoolpy import graph_from_table, networkx_draw

tbn = pd.read_csv('node0.csv')
tbe = pd.read_csv('edge0.csv')

g = graph_from_table(tbn, tbe)[0]
t = nx.maximum_flow(g, 5, 2)
pos = networkx_draw(g)
nx.draw_networkx_edges(g, pos, width=3, edgelist=[(k1, k2) for k1, d in t[1].items() for k2, v in d.items() if v])

plt.show()
for i, d in t[1].items():
    for j, f in d.items():
        if f: print((i, j), f)