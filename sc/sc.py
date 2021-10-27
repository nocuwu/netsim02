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
    m = pulp.LpProblem('最小化問題', sense=pulp.LpMinimize)
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

    if m.solve() != 1:
        return None

    s = 1  # 始点
    t = 4  # 終点
    df = pd.read_csv('bw.csv')

    # CSVの各行Lに対して、変数xi_jを生成し、
    # 新しい列'Var'として追加している。
    df['Var'] = [pulp.LpVariable(f'x{df.i[L]}_{df.j[L]}', 0, df.c[L]) for L in df.index]
    ##z = pulp.LpVariable('z')

    m2 = pulp.LpProblem('最大流問題', sense=pulp.LpMinimize)
    m2 += pulp.lpDot(df.c, df.Var), '目的関数'  # zの実体は以下の制約条件内で定義する

    # set(df.i)はi列の一覧、set(df.j)はj列の一覧。|でつないだら、その和集合
    # set(df.i)はi列の一覧、set(df.j)はj列の一覧。|でつないだら、その和集合
    for n in set(df.i)|set(df.j):
        if n == s:
            m2 += pulp.lpSum(df.Var[df.i==n]) - pulp.lpSum(df.Var[df.j==n]) == 1, f'始点{n}'
        elif n == t:
            m2 += pulp.lpSum(df.Var[df.i==n]) - pulp.lpSum(df.Var[df.j==n]) == -1, f'終点{n}'
        else:
            m2 += pulp.lpSum(df.Var[df.i==n]) - pulp.lpSum(df.Var[df.j==n]) == 0, f'点{n}'

    # print(na)
    # print(nj)
    # print(len(cst[0]))

    '''
    for i in range(na):
        for j in range(nj):
            print(value(v[i][j]))
    '''

    # 制約条件をすべて登録したので解を求める
    result = m2.solve(pulp.PULP_CBC_CMD(msg = False))
    # LpStatusが`optimal`なら最適解が得られた事になる
    print(pulp.LpStatus[result])
    # 目的関数の値
    print(pulp.value(m2.objective))
    # 'Var'変数の結果の値をまとめて'Val'列にコピーしている
    df['Val'] = df.Var.apply(pulp.value)
    # 結果表示
    print(df)
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

ans = Gap('cp.csv', [2, 1])
print(ans)