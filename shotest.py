import pulp
import networkx as nx

g = nx.fast_gnp_random_graph(8, 0.26, 1).to_directed()
source, sink = 0, 2
r = list(enumerate(g.edges()))
m = pulp.LpProblem()
x = [pulp.LpVariable('x%d'%k, lowBound=0, upBound=1) for k, (i, j) in r]
m += pulp.lpSum(x)

for nd in g.nodes():
    m += pulp.lpSum(x[k] for k, (i, j) in r if i == nd) \
    == pulp.lpSum(x[k] for k, (i, j) in r if j == nd) + {source:1, sink:-1}.get(nd, 0)

m.solve()

print([(i, j) for k, (i, j) in r if pulp.value(x[k]) > 0.5])