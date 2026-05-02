f = 1.1
time_ms = 2000
fps = 30
delta_time_ms = 1000 / fps
n = int(time_ms / delta_time_ms)
x = 128 # 32

def F(n:int) -> float:
    return f * ( f ** (n+2) - f * (n+2) + (n+1)) / (f-1)**2


m = time_ms * F(n) / x
print(m)