"""This code analyses the user accelerometer data
and tells us at what time he was awake during his sleep"""
import pandas as pd


try:
    df = pd.read_csv("sleep_14.csv")
except IOError:
    print("Unable to load data file")
    print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

linear_acc = pd.concat([df.ix[:, i:i+3].mean(axis=1)
                        for i in range(6, 9, 3)], axis=1)
linear_acc = linear_acc.abs().rolling(1200).max().dropna()

linear_acc.drop_duplicates(subset=None, keep='last', inplace=True)
index_list = linear_acc[linear_acc > 1].dropna().index
store_index = 0
for index_i in index_list:
    if index_i > store_index:
        print("=============================================")
        print("You were awake at  : %s " % df.loc[index_i, "Date"])
        print("=============================================")
        store_index = index_i + 3600


