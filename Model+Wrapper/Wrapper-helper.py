from ultralytics import YOLO
import matplotlib.pyplot as plt
import cv2
import numpy as np
import os
import time as time

# Function to load the YOLO model from weights and 
def load_model(location):
     model = YOLO(location)
     print(f"Model loaded from python at {time.time()}")
     return model

# Function to plot spectrograms using matplotlib and save them in a .npy format for further predictions
def make_spec(IQ,model):
        print(f"Save_spec function called at {time.time()}")

        # Initialize variables
        chunk_size = 53335380
        cur_dir = os.getcwd()
        results = "" # all result labels are stored in a string
        model = model.cpu()
        sampling_freq = 245.76e6 # sampling frequency 

        for i in range(6):
            chunk = IQ[i*chunk_size: (i+1)*chunk_size] # Chunk the data for a particular piece

            print(f"Spectrogram {i} plotting started at {time.time()}")
            plt.specgram(chunk,Fs=sampling_freq)    # Plot the spectrum 
            plt.axis('off')
            # plt.show()

            fig = plt.gcf()
            fig.canvas.draw()        # This step is important to ensure that figure is rendered completely before converting to an image
            image_np = np.array(fig.canvas.renderer._renderer)   # Converts the image to array
            bgr_image = cv2.cvtColor(image_np,cv2.COLOR_RGB2BGR)  # Converts image from RGB to BGR format as YOLO expects it to be in BGR

            result = model(bgr_image)
            results = results + (f'{result[0].verbose()}\n')
            print(f"Spectrogram {i} plotting ended at {time.time()}")
            if i==0:
                 break

        print(f"All Spectrograms plotted at {time.time()}")

         # The result string is then written in a file
        with open(f'{cur_dir}\\result.txt' ,'w') as f:
            f.write(f'{results}')
        print(f"prediction ended and saved in a file at {time.time()}")
        #print(results)
        return results
