import random


def validate_coordinate(x, y, M, n):
    if x >= n or x < 0 or y >= n or y < 0:
        print("Invalid Input")
        return 1
    if M[x][y] == "X" or M[x][y] == "B":
        print(" You Have already opened IT")
        return 1
    else:
        return 0


def MapGenerator(n):
    map_final = []
    for i in range(0, n):
        row_map = []
        for i in range(n):
            row_map.append("O")
        map_final.append(row_map)
    return map_final


def Map_Bombs(n):
    bomb_mp = MapGenerator(n)
    for i in range(0, int((n*n)/4)):
        x = random.randint(0, n-1)
        y = random.randint(0, n-1)
        bomb_mp[x][y] = "B"
    return bomb_mp


def UI(M):
    for rw in M:
        for j in rw:
            print j+"|",
        print("")


def checkbomb(X, Y, Map_bmb):
    if Map_bmb[X][Y] == "B":
        print("********B*o*m*b**********")
        return "B", 1
    if Map_bmb[X][Y] == "O":
        return "X", 0

n = 4
count = 0
main_map = MapGenerator(n)
bomb_map = Map_Bombs(n)

UI(main_map)

while True:
    user_X, user_Y = input()
    validate_response = validate_coordinate(user_X, user_Y, main_map, n)
    if validate_response == 1:
        continue
    map_val, count_val = checkbomb(user_X, user_Y, bomb_map)
    main_map[user_X][user_Y] = map_val
    count = count_val + count
    if count == 3:
        print("Game Over")
        break
    if count_total == n*n:
        print("You Have Won")
        break
    UI(main_map)




    
        
        
