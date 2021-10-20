import pulp
import pandas as pd

s = 1  # 始点
t = 10  # 終点
df = pd.read_csv('capacity2.csv')
w=8

# CSVの各行Lに対して、変数xi_jを生成し、
# 新しい列'Var'として追加している。
df['Var'] = [pulp.LpVariable(f'x{df.i[L]}_{df.j[L]}', 0, df.c[L]) for L in df.index]
##z = pulp.LpVariable('z')

p = pulp.LpProblem('最大流問題', sense=pulp.LpMinimize)
p += pulp.lpDot(df.c, df.Var), '目的関数'  # zの実体は以下の制約条件内で定義する

# set(df.i)はi列の一覧、set(df.j)はj列の一覧。|でつないだら、その和集合
for n in set(df.i)|set(df.j):
    if n == s:
        p += pulp.lpSum(df.Var[df.i==n]) - pulp.lpSum(df.Var[df.j==n]) == 1, f'始点{n}'
    elif n == t:
        p += pulp.lpSum(df.Var[df.i==n]) - pulp.lpSum(df.Var[df.j==n]) == -1, f'終点{n}'
    else:
        p += pulp.lpSum(df.Var[df.i==n]) - pulp.lpSum(df.Var[df.j==n]) == 0, f'点{n}'

print(pulp.lpSum(df.Var[df.i==s]) - pulp.lpSum(df.Var[df.j==s]))
print(pulp.lpSum(df.Var[df.i==t]) - pulp.lpSum(df.Var[df.j==t]))

# 制約条件をすべて登録したので解を求める
result = p.solve(pulp.PULP_CBC_CMD(msg = False))
# LpStatusが`optimal`なら最適解が得られた事になる
print(pulp.LpStatus[result])
# 目的関数の値
print(pulp.value(p.objective))
# 'Var'変数の結果の値をまとめて'Val'列にコピーしている
df['Val'] = df.Var.apply(pulp.value)
# 結果表示
print(df)