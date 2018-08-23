import numpy as np
import wave
import struct
import pandas as pd


sampling_freq = 1000 	#Sampling frequency of audio signal
window = 180              #Size of window to be used for detecting silence
threshold = 300000         #threshold value
dft = []                #array to store dtf value
start = []              #array holding start indices of each note
end = []                #array holding end   indices of each note
Identified_Notes = []   #list of identified notes

array = [1046.50, 1174.66, 1318.51, 1396.91, 1567.98, 1760.00, 1975.53,
         2093.00, 2349.32, 2637.02, 2793.83, 3135.96, 3520.00, 3951.07,
         4186.01, 4698.63, 5274.04, 5587.65, 6271.93, 7040.00, 7902.13]

notes = ['C6', 'D6', 'E6', 'F6', 'G6', 'A6', 'B6',
         'C7', 'D7', 'E7', 'F7', 'G7', 'A7', 'B7',
         'C8', 'D8', 'E8', 'F8', 'G8', 'A8', 'B8']


def play():
    df = pd.read_csv("Tone.csv")
    np_array = df.SOUNDLEVEL.values
    # fourier =  np.fft.fft(np_array)


    Identified_Notes[:] = []                #Clear the list every time play() is called
    start[:] = []
    end[:] = []
    
    file_length = len(np_array)  #Decode Audio File       
    # sound = np.zeros(file_length)

    # for i in range(file_length):
    #     data = sound_file.readframes(1)
    #     data = struct.unpack("<h", data)
    #     sound[i] = int(data[0])

    sound = np.divide(np_array, float(2))
    # print(sound)
    sound_square = np.square(sound)         #square each element of sound[]
    
    i = 0
    j = 0
    f = 0
    t = 0
    # print(sound_square)
    while(i<(file_length) - window):
        s = 0.00
        j = 0
        if(t==0):
            start.append(i)                 #store start point of note
            f = 0
            t = 1 
        while(j<=window):
            s = s + sound_square[i + j]
            j = j + 1
            # print(s,threshold)
        if(s<=threshold):
            if(f==0):
                end.append(i)               #store end point of note
                f = 1
        else:
            if(f==1):
                f = 0
                t = 0
        i = i + window

    i = 0
    # print(end)
    while(i<1):                      #Identify Notes
        dft = np.array(np.fft.fft(sound[:]))  # applying fourier transform function
        dft = np.argsort(dft)
        print(dft)
        if(dft[0]>dft[-1] and dft[1]>dft[-1]):
            i_max = dft[-1]
            print(i_max)
        elif(dft[1]>dft[0] and dft[-1]>dft[0]):
            i_max = dft[0]
        else:
            i_max = dft[1]
        fr = (i_max*sampling_freq)/(len(sound))   # claculating frequency
        idx = (np.abs(array-fr)).argmin()
        print(array)
        Identified_Notes.append(notes[idx])
        i = i + 1
        
    print(Identified_Notes)


############################## Read Audio File #############################

if __name__ == "__main__":
    play()


