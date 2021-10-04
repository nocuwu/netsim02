from collections import defaultdict
from math import ceil, sqrt
from typing import Iterable, Tuple

import numpy as np
import pandas as pd

if "Don't show message from pulp.":
    import pulp

    if isinstance(pulp.LpSolverDefault, pulp.PULP_CBC_CMD):
        pulp.LpSolverDefault.msg = False

from more_itertools import always_iterable, pairwise

from pulp import (
    LpBinary,
    LpInteger,
    LpMaximize,
    LpMinimize,
    LpProblem,
    LpVariable,
    lpDot,
    lpSum,
    value,
)

def addvar(name=None, *, var_count=[0], lowBound=0, format="v%.6d", **kwargs):
    """変数作成用ユーティリティ"""
    if not name:
        var_count[0] += 1
        name = format % var_count[0]
    if "lowBound" not in kwargs:
        kwargs["lowBound"] = lowBound
    return LpVariable(name, **kwargs)

def gap(cst, req, cap):
    na, nj = len(cst), len(cst[0])
    m = LpProblem()
    v = [[addvar(cat=LpBinary) for _ in range(nj)] for _ in range(na)]
    m += lpSum(lpDot(cst[i], v[i]) for i in range(na))
    for i in range(na):
        m += lpDot(req[i], v[i]) <= cap[i]
    for j in range(nj):
        m += lpSum(v[i][j] for i in range(na)) == 1
    if m.solve() != 1:
        return None
    return [
        int(value(lpDot(range(na), [v[i][j] for i in range(na)]))) for j in range(nj)
    ]

ans = gap([[2, 2, 2], [1, 1, 1]], [[1, 1, 1], [1, 1, 1]], [2, 1])

print(ans)
