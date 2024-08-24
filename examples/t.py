import matplotlib.pyplot as plt
import math

# 讀取txt檔案並將內容分別存入x和y
x = []
pred_y = []
y = []
origin = 0
with open('result.txt', 'r') as file:
    lines = file.readlines()
    for i in range(0, len(lines), 2):
        #x.append(math.log(int(lines[i].strip()),2))
        x.append(int(lines[i].strip()))
        pred_y.append(abs(int(lines[i+1].strip())))
        y.append(origin)
        origin += 1
#print(y)
#print(pred_y)
#print(min(x))
#print(max(x))

plt.plot(x, pred_y, 'r.', linewidth=1, markersize=1,label="Model")
plt.plot(x, y, 'b', linewidth=1, markersize=1,label="Origin")
# 設定X和Y軸的範圍
plt.xlim(min(x) , max(x) )
plt.ylim(min(pred_y) - 1, max(pred_y) + 1)
plt.title('test', fontsize=8)
plt.xlabel('index', fontsize=8)
plt.ylabel('position', fontsize=8)
plt.savefig('test.png',
            transparent=True,
            bbox_inches='tight',
            pad_inches=1)
plt.show()


def AvgErrorBound(pred_y):
    Sum = 0.0
    for index, val in enumerate(pred_y):
        Sum += abs(val - index)

    return Sum/len(pred_y)

def MaxErrorBound(pred_y):
    Max = 0.0
    for index, val in enumerate(pred_y):
        if(Max < abs(val - index)):
            Max = abs(val - index)

    return Max


print(f"Average Error Bound: {AvgErrorBound(pred_y)}")
print(f"Max Error Bound: {MaxErrorBound(pred_y)}")
