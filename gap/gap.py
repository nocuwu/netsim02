from collections import defaultdict
from math import ceil, sqrt
from typing import Iterable, Tuple

import numpy as np
import pandas as pd

from ortoolpy import graph_from_table
from more_itertools import first, pairwise

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

## 変数の作成
def addvar(name=None, *, var_count=[0], lowBound=0, format="v%.6d", **kwargs):
    """変数作成用ユーティリティ"""
    if not name:
        var_count[0] += 1
        name = format % var_count[0]
    if "lowBound" not in kwargs:
        kwargs["lowBound"] = lowBound
    
    ## print(LpVariable(name, **kwargs))
    return LpVariable(name, **kwargs)

def gap(cst, req, cap):
    ## na: エージェント数 nj: ジョブ数
    na, nj = len(cst), len(cst[0])
    ## 目的関数　最小化問題
    m = LpProblem()
    ## 変数　addvarの返り値はLpVariable() cat=0-1整数問題??
    v = [[addvar(cat=LpBinary) for _ in range(nj)] for _ in range(na)]
    ## 制約?? コスト[]×バイナリ[] = コストの総和
    m += lpSum(lpDot(cst[i], v[i]) for i in range(na)) ## 内積: lpDot(係数のリスト, 変数のリスト)
    ## 制約　エージェントの容量チェック
    for i in range(na):
        m += lpDot(req[i], v[i]) <= cap[i]
    ## 制約　xij=1
    for j in range(nj):
        m += lpSum(v[i][j] for i in range(na)) == 1

    ##フロー保存則
    '''
    for j in range(nj):
        m += (lpSum(v[i][j] for i in range(na)) - lpSum(v[j][i] for i in range(na))) != -549
    '''
    # 辺
    es = ['ab', 'ac', 'bc', 'bd', 'cd']
    # 容量
    ws = [5, 2, 6, 4, 2]
    # 変数
    vs = {e: pulp.LpVariable('x{}'.format(e), lowBound = 0, upBound = w) for e, w in zip(es, ws)}
    # 目的関数
    #prob += vs['ab'] + vs['ac']
    # 制約条件
    m += vs['ab'] == vs['bc'] + vs['bd']
    m += vs['ac'] + vs['bc'] == vs['cd']

    # print(na)
    # print(nj)
    # print(len(cst[0]))

    ## 解けなかったらnone
    if m.solve() != 1:
        return None
    '''
    for i in range(na):
        for j in range(nj):
            print(value(v[i][j]))
    '''

    ## それ以外（解けたら）return
    return [
        int(value(lpDot(range(na), [v[i][j] for i in range(na)]))) for j in range(nj)
    ]

## csvファイルを読んでgap()に投げる
def Gap(
    df,
    capacity,
    agent_label="agent",
    job_label="job",
    cost_label="cost",
    req_label="req",
    **kwargs,
):

    df = graph_from_table(df, None, no_graph=True, **kwargs)[1]
    a = range(df[agent_label].max() + 1)
    j = range(df[job_label].max() + 1)
    c = [
        [
            first(df[(df[agent_label] == i) & (df[job_label] == k)][cost_label], 0)
            for k in j
        ]
        for i in a
    ]
    r = [
        [
            first(df[(df[agent_label] == i) & (df[job_label] == k)][req_label], 1e6)
            for k in j
        ]
        for i in a
    ]
    t = gap(c, r, capacity)
    return pd.concat(
        [df[(df[agent_label] == i) & (df[job_label] == k)] for k, i in enumerate(t)]
    )

ans = Gap('gap.csv', [2, 1])
print(ans)
