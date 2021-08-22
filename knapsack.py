import pulp
from ortoolpy import knapsack

size = [21, 11, 15, 9, 34, 25, 41, 52]
weight = [22, 12, 16, 10, 35, 26, 42, 53]
capacity = 100
knapsack(size, weight, capacity)

r = range(len(size))
m = pulp.LpProblem(sense=pulp.LpMaximize)
x = [pulp.LpVariable('x%d'%i, cat=pulp.LpBinary) for i in r]
m += pulp.lpDot(weight, x)
m += pulp.lpDot(size, x) <= capacity
m.solve()
print((pulp.value(m.objective), [i for i in r if pulp.value(x[i]) > 0.5]))