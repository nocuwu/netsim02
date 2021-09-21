folder = "../data/gap/"
#f = open(folder+"e801600")
f = open(folder+"a05100")
data = f.readlines()
f.close()

m, n = list( map(int, data[0].split()) )
cost, a, b = {}, {}, {}
data_ = []
for row in data[1:]:
    data_.extend( list( map(int, row.split()) ) )
count = 0
for i in range(m):
    for j in range(n):
        cost[i,j] = data_[count]
        count += 1
for i in range(m):
    for j in range(n):
        a[i,j] = data_[count]
        count += 1
for i in range(m):
    b[i] = data_[count]
    count += 1