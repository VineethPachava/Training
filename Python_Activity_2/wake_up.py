"""This code analyses the user accelerometer data
and tells us at what time he was awake during his sleep"""
import pandas as pd


def time_extracter(date_time):
    """ This function takes the time and date in string format
    and returns the array of date [year,month,day]
    and time [hours,minutes,seconds,microseconds]"""
    date_arr, time_arr = date_time.split()
    time_arr = time_arr.split(":")
    date_arr = date_arr.split("-")
    time_arr = [int(time_arr[x]) for x in range(len(time_arr))]
    date_arr = [int(date_arr[x]) for x in range(len(date_arr))]
    return time_arr, date_arr


def tot_sleep_time(wake_time, asleep_time):
    """This function takes two arrays containing the time,
    when you fell asleep and the wake up time and outputs the time difference"""
    total_sleep_time = 0
    if (asleep_time[0]-wake_time[0]) <= 0:
        total_sleep_time = [wake_time[0]-asleep_time[0],
                            abs(wake_time[1]-asleep_time[1]), abs(wake_time[2]-asleep_time[2])]
    if (asleep_time[0]-wake_time[0]) > 0:
        total_sleep_time = [24-wake_time[0]+asleep_time[0],
                            abs(wake_time[1]-asleep_time[1]), abs(wake_time[2]-asleep_time[2])]
    return total_sleep_time[0]


def night_classifier(wake_time):
    """This funtion takes time as input and classifies night it into 4 categories.
        -NIGHT
        -MIDNIGHT
        -EARLY MORNING
        -MORNING
    """
    if wake_time[0] >= 6 and wake_time[0] < 12:
        night_class = "Morning"
    if wake_time[0] >= 4 and wake_time[0] < 6:
        night_class = " Early Morning"
    if wake_time[0] < 4:
        night_class = "MIDNIGHT"
    if wake_time[0] >= 19:
        night_class = "NIGHT"
    return night_class


try:
    DF = pd.read_csv("sleep_12.csv")
except IOError:
    print("Unable to load data file")
    print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

linear_acc = pd.concat([DF.ix[:, i:i+3].mean(axis=1)
                        for i in range(6, 9, 3)], axis=1)
linear_acc = linear_acc.abs().rolling(1200).max().dropna()

linear_acc.drop_duplicates(subset=None, keep='last', inplace=True)
index_list = linear_acc[linear_acc > 1].dropna().index
store_index = 0
sleep_time, sleep_date = time_extracter(DF.loc[1800, "Date"])
awake_time = []
for index_i in index_list:
    if index_i > store_index:
        # print("=============================================")
        # print("You were awake at  : %s " % DF.loc[index_i, "Date"])
        # print("=============================================")
        # awake_time.append(DF.loc[index_i, "Date"()
        awake_time, awake_date = time_extracter(DF.loc[index_i, "Date"])
        part_of_night = night_classifier(awake_time)
        if part_of_night == "Morning":
            print("=============================================")
            print("You woke up in the Morning  at:",
                  awake_time[0], ":", awake_time[1], "AM")
            print("=============================================")
            print("You slept for about ", tot_sleep_time(
                awake_time, sleep_time), "Hrs")
            print("=============================================")

        else:
            print("=============================================")
            print("You woke up " + part_of_night + " at {0:2d} : {1:02d} ".format(
                awake_time[0], awake_time[1]), "and went back to sleep")
            print("=============================================")
        store_index = index_i + 2400
