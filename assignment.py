from scipy.optimize import linear_sum_assignment
import numpy as np
#cost = np.array([[4, 1, 3], [2, 0, 5], [3, 2, 2]])
n = 1000
cost = np.random.randint(100,1000,size=(n,n))

row_ind, col_ind = linear_sum_assignment(cost)
print(cost[row_ind, col_ind].sum())