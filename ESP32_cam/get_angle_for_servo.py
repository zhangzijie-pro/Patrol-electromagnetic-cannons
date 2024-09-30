import math

N = 0.5

# get angle
def get_tan(a,b):
    left = 0
    X1_LEN= a
    X2_LEN= b
    x = math.pow(N*X1_LEN,2)-math.pow(N*X2_LEN,2)/2
    if x<0:
        x = abs(x)
        left = 1
    else:
        left = 0
    y = math.sqrt(math.pow(N*X1_LEN,2)-math.pow(x-0.5,2))
    return (x,y,left)

def find_angle(tan_value):
    angle = math.atan(tan_value)
    return math.degrees(angle)

(a,b,left) = get_tan(2,3)
tan_value = a/b
print("tan：", tan_value)
angle = find_angle(tan_value)


print("角度：", angle)