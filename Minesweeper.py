#!/usr/bin/python3.6
""" This is mini version of mine sweeper"""

import random
import time
import pandas as pd


def validate_coordinate(x_user, y_user, m_map, n_dim):
    """ Checks if user is opening new block or no, input is in right format and returns a flag.  """
    if x_user >= n_dim or x_user < 0 or y_user >= n_dim or y_user < 0:
        print("""
        !!! Invalid Input !!!
        """)
        flag = 1
    elif m_map[x_user][y_user] == "X" or m_map[x_user][y_user] == "B":
        print("""
        You Have already opened IT
        """)
        flag = 1
    else:
        flag = 0
    return flag


def map_generator(n_dim):
    """ Generates a matrix of size n_dim * n_dim as a map """
    map_final = []
    for _ in range(0, n_dim):
        row_map = []
        for _ in range(n_dim):
            row_map.append("O")
        map_final.append(row_map)
    return map_final


def map_bombs(n_dim):
    """ Creates a map and inputs bombs in 1/4 locations randomly"""
    bomb_mp = map_generator(n_dim)
    for _ in range(0, int((n_dim * n_dim)/4)):
        x_random = random.randint(0, n_dim-1)
        y_random = random.randint(0, n_dim-1)
        bomb_mp[x_random][y_random] = "B"
    return bomb_mp


def user_interface(final_map):
    """User visualisation of map is done here"""
    for map_row in final_map:
        for val_map_row in map_row:
            print((val_map_row)+"|", end=" ")
        print("")


def checkbomb(user_x, user_y, map_bmb):
    """Checks if bombs are present in the user given locations"""
    if map_bmb[user_x][user_y] == "B":
        print("********B*o*m*b**********")
        flag_val = "B"
        flag_indicator = 1
    if map_bmb[user_x][user_y] == "O":
        flag_val = "X"
        flag_indicator = 0
    return flag_val, flag_indicator


def login_menu():
    """Login Menu is displayed with login and register as options """
    option = input("""
    ++++++++++++++++++++++++++++++
        Choose options below
        1. Login
        2. Register
    ++++++++++++++++++++++++++++++
        """)
    if option == "1":
        login()

    elif option == "2":
        register_user()
    # elif option == "3" :
    #     Forgot_Password()
    else:
        print("Option Does not exist")
        login_menu()


def register_user():
    """Registeration of user takes place"""
    excel_data = "Save.csv"
    new_user_name = input("Give a Username : ")
    try:
        database = pd.read_csv(excel_data)

    except IOError:
        print("Unable to Load Save.csv ")
        login_menu()

    len_req_df = len(database[(database.Username == new_user_name)])
    if len_req_df == 0:
        user_password = input("Set Password: ")
        new_data = pd.DataFrame([[new_user_name, user_password, 0, 0]])
        new_data.to_csv(excel_data, mode='a', header=False, index=False)
        print("Redirecting to Login ......")
        time.sleep(2)
        print("         PLease Login          ")
        login()

    else:
        print("Username Already Exist")
        register_user()
    return 0


def login():
    """User authentication takes place, if it fails it goes back to Login Menu """
    excel_data = "Save.csv"
    user_name_login = input("Enter Username: ")
    try:
        database = pd.read_csv(excel_data)

    except IOError:
        # handle any other exception
        print("Unable to Load Save.csv ")
        login_menu()

    len_req_df = len(database[(database.Username == user_name_login)])

    if len_req_df > 0:
        usr_pass = input("Enter Password: ")
        mask = (database.Username == user_name_login) & (
            database.Password == usr_pass)
        len_req_data = len(database[mask])
        if len_req_data > 0:
            print("""
            ************
            Login Sucess
            ************

            """)
            print("Loading ...")
            time.sleep(1)
            main_menu(user_name_login)

        else:
            print("""
            =============================
            !!! Username or Password is incorrect !!!
            =============================
            """)
            login_menu()
    else:
        print("""
        ================================
        !!! Username entered is wrong !!!
        =================================
        """)
        login_menu()


def save_score(user_id, score):
    """Used to write score to the csv file"""
    excel_data = "Save.csv"

    try:
        database = pd.read_csv(
            excel_data, names=["Username", "Password", "Score", "Count"])
    except IOError:
        print("""
            Unable to Load Save.csv
        =======================================
             Failed to Save Score!
        =======================================
        .
        .
        .
        ....... Redirecting to Main Menu
        """)
        return 0

    database.Score[database["Username"] == user_id] = score
    database.Count[database["Username"] ==
                   user_id] = int(database.Count[database["Username"] == user_id]) + 1
    database.to_csv(excel_data, index=False, header=False)
    print("Sucessfully Saved")
    return 1


def leaderboard():
    """Displays the Scores of Registered Users """
    excel_data = "Save.csv"
    flag = 0
    try:
        database = pd.read_csv(
            excel_data, names=["Username", "Password", "Score", "Count"], header=0)
        flag = 1
    except IOError:
        print("""
             Unable to Load Save.csv
        =======================================
        ....... Redirecting to Main Menu
        """)
        flag = 0
    if flag != 0:
        leader_board = database.sort_values(by="Score", ascending=False)
        print(leader_board.loc[:, ["Username", "Score"]])
    return flag


def rules():
    """Displays rules at start of game"""
    rules_display = """
    ========================================================================
                       || Rules ||

            The aim of the game is to uncover all the blocks without bombs.
            You have three lives at the beggining of game.
            Each Bomb you uncover you loose life.
            After you loose three lives, game ends.
            Uncover all the boxes without bombs to win.

            Controls:
            You need the input of coordinate in the format - 1 1
            The matrix has range from [0-n, 0-n].
            Your Input should be between this range.

            Score:
            The number of boxes you uncover is your score.
    ===========================================================================
    """
    print(rules_display)
    time.sleep(3)


def game(player_name):
    """Core logic of game resides here"""
    n_dim = 4
    count_bombs = 0
    rules()
    print("Welcome %s" % player_name)
    print("""

    =============================================================================

    """)
    main_map = map_generator(n_dim)     # Initialising Map.
    bomb_map = map_bombs(n_dim)     # Initialising Bombs.
    count_total = 0     # keeping track of moves
    user_interface(main_map)
    while True:
        try:
            print("Enter the coordinates: ")
            user_x, user_y = input().split()
            user_x, user_y = int(user_x), int(user_y)
        except ValueError:
            print("re-check input : ")
            continue

        validate_response = validate_coordinate(
            user_x, user_y, main_map, n_dim)
        if validate_response == 1:
            continue
        map_val, count_val = checkbomb(user_x, user_y, bomb_map)
        main_map[user_x][user_y] = map_val
        count_bombs = count_val + count_bombs
        count_total += 1
        score = count_total - count_bombs
        if count_bombs == 3:
            print("Score : %d" % score)
            save_score(player_name, score)
            print("Game Over")
            return 0
        if score == (n_dim*n_dim - int(n_dim*n_dim/4)):
            print("Score : %d" % score)
            print("You Have Won")
            save_score(player_name, score)
            time.sleep(3)
            return 0
        user_interface(main_map)


def main_menu(player_id):
    """ Displays the main menu, it takes input of username for user identification"""
    while True:
        user_response = input("""
        =============================================
            Choose:
                    1. START
                    2. LeaderBoard
                    3. QUIT
        ==============================================
        """)
        if user_response == '1':
            game(player_id)
        if user_response == '2':
            leaderboard()
        if user_response == '3':
            break


login_menu()
