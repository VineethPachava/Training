"""This code analyses the user accelerometer data
and tells us at what time he was awake during his sleep"""
import pandas as pd
import numpy as np

def noise_filter(signal, threshold= 1):
    signal = signal.copy()
    difference = np.abs(signal - np.median(signal))
    median_difference = np.median(difference)
    if median_difference == 0:
        s = 0
    else:
        s = difference / float(median_difference)
    mask = s > threshold
    signal[mask] = np.median(signal)
    return signal

def time_extracter(date_time):
    """ This function takes the time and date in string format
     and returns the array of date [year,month,day] 
     and time [hours,minutes,seconds,microseconds]"""

    date_arr, time_arr = date_time.split()
    time_arr = time_arr.split(":")
    date_arr = date_arr.split("-")
    time_arr = [int(time_arr[x] for x in range(len(time_arr)))]
    date_arr = [int(date_arr[x] for x in range(len(date_arr)))]
    return time_arr, date_arr


def sleep_time(wake_time, asleep_time):
    """This function takes two arrays containing the time, 
    when you fell asleep and the wake up time and outputs the time difference"""

    if asleep_time[0]-wake_time[0] > 0:
        total_sleep_time = [wake_time[0]-asleep_time[0],
                            abs(wake_time[1]-asleep_time[1]), abs(wake_time[2]-asleep_time[2])]
    if asleep_time[0]-asleep_time[0] < 0:
        total_sleep_time = [24-wake_time[0]+asleep_time[0],
                            abs(wake_time[1]-asleep_time[1]), abs(wake_time[2]-asleep_time[2])]
    return total_sleep_time


def night_classifier(wake_time):
    if wake_time[0] >= 6 and wake_time[0] < 12:
        night_class = "Morning"
    if wake_time[0] >= 4 and wake_time[0] < 6:
        night_class = " Early Morning"   
    if  wake_time[0] < 4 :
        night_class = "MIDNIGHT"
    if wake_time[0] >= 19 :
        night_class = "NIGHT"
    return night_class





try:
    df = pd.read_csv("sleep_14.csv")
except IOError:
    print("Unable to load data file")
    print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

linear_acc = pd.concat([df.ix[:, i:i+3].mean(axis=1)
                        for i in range(6, 9, 3)], axis=1)

linear_acc = noise_filter(linear_acc)
linear_acc = linear_acc.abs().rolling(1200).max().dropna()

linear_acc.drop_duplicates(subset=None, keep='last', inplace=True)
index_list = linear_acc[linear_acc > 1].dropna().index
store_index = 0
awake_time = []
for index_i in index_list:
    if index_i > store_index:
        # print("=============================================")
        # print("You were awake at  : %s " % df.loc[index_i, "Date"])
        # print("=============================================")
        awake_time.append(df.loc[index_i, "Date"])
        # store_index = index_i + 3600
