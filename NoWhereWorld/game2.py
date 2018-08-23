import random
import pandas as pd
import time

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
    for val_1 in range(0, n):
        row_map = []
        for val_2 in range(n):
            row_map.append("O")
        map_final.append(row_map)
    return map_final


def Map_Bombs(n):
    bomb_mp = MapGenerator(n)
    for temp_val in range(0, int((n*n)/4)):
        x = random.randint(0, n-1)
        y = random.randint(0, n-1)
        bomb_mp[x][y] = "B"
    return bomb_mp


def UI(M):
    for rw in M:
        for j in rw:
            print (j+"|",end=' ')
        print("")


def checkbomb(X, Y, Map_bmb):
    if Map_bmb[X][Y] == "B":
        print("********B*o*m*b**********")
        return "B", 1
    if Map_bmb[X][Y] == "O":
        return "X", 0


def Login_menu():
    option = input('''
    ++++++++++++++++++++++++++++++
        Choose options below
        1. Login
        2. Register
    ++++++++++++++++++++++++++++++
        ''')
    
    if option == "1" :
        return Login()
    elif option == "2":
        Register()
    # elif option == "3" :
    #     Forgot_Password()
    else:
        print("Option Does not exist")
        Login_menu()
    return 0


def Register():
    excel_data = "Save.csv"
    user_name = input("Enter Username : ")

    try:
        database = pd.read_csv(excel_data)
    except:
        print("Unable to Load Save.csv ")
        Login_menu()
        pass

    if len(database[(database.Username == user_name)]) == 0:
        user_password  = input("Enter Password: ")
        new_data = pd.DataFrame([[user_name,user_password]])
        new_data.to_csv(excel_data, mode = 'a', header=False, index= False)
        print("Redirecting to Login ......")
        time.sleep(2)
        Login()
        return 0
    else:
        print("Username Already Exist")
        Register()


def Login():
    excel_data = "Save.csv"
    user_name = input("Enter Username: ")

    try:
        database = pd.read_csv(excel_data)
    except:
        print("Unable to Load Save.csv ")
        Login_menu()
        pass

    if len(database[(database.Username == user_name)]) > 0:
        user_password = input("Enter Password: ")
        if len(database[(database.Username == user_name) & (database.Password == user_password)]) > 0:
            print('''
            ************
            Login Sucess
            ************

            ''')
            print("Loading ...")
            time.sleep(2)
            return user_name
        else:
            print('''
            =============================
            !!! Username or Password is incorrect !!!
            =============================
            ''')
            Login_menu()
        
    else:
        print('''
        ================================
        !!! Username entered is wrong !!!
        =================================
        ''')
        Login_menu()



def rules():
    rules = ''' 
    ========================================================================
                       || Rules ||

            The aim of the game is to uncover all the blocks without bombs.
            You have three lives at the beggining of game. 
            Each Bomb you uncover you loose life.
            After you loose three lives, game ends.

            Controls:
            You need the input of coordinate in the format - 1, 1
            The matrix has range from [0-n, 0-n].
            Your Input should be between this range.

            Score:
            The number of boxes you uncover is your score.
    ===========================================================================
    '''
    print(rules)

def save_score(user_name, score):
    excel_data = "Save.csv"

    try:
        database = pd.read_csv(excel_data, names= ["Username", "Password", "Score"])
        print(database)
    except:
        print(''' 
             Unable to Load Save.csv
        =======================================
             Failed to Save Score!

        
        ....... Redirecting to Main Menu
        ''')
        return 0

    database.Score[database["Username"] == user_name] = score
    database.to_csv(excel_data, index= False, header = False)
    print("Sucessfully Saved")
    return 1

def game(player_name):

    # rules()
    save_score(player_name,12)
    print("Welcome %s"%player_name)
    print('''

    =============================================================================
    
    ''')
    n = 4
    count_bombs = 0
    main_map = MapGenerator(n) #Initialising Map.
    bomb_map = Map_Bombs(n)    #Initialising Bombs.
    count_total = 0            #keeping track of moves
    UI(main_map)
    while True:
        try:    
            print("Enter the coordinates: ")
            user_X,user_Y = input().split()
            user_X,user_Y = int(user_X), int(user_Y)
        except:
            print("re-check input")
            continue
        validate_response = validate_coordinate(user_X, user_Y, main_map, n)
        if validate_response == 1:
            continue
        map_val, count_val = checkbomb(user_X, user_Y, bomb_map)
        main_map[user_X][user_Y] = map_val
        count_bombs = count_val + count_bombs
        count_total += 1
        if count_bombs == 3:
            print("Score : %d"%count_total)
            save_score(player_name, count_total)
            print("Game Over")
            return 0
        if (count_total - count_bombs) == (n*n - int(n*n/4)):
            print("Score : %d"%count_total)
            print("You Have Won")
            save_score(player_name, count_total)
            time.sleep(3)
            return 0
        UI(main_map)



game("vineeth")