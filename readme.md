# Project Description

This project focuses on the classification of drone signals using the YOLOv8 computer vision convolutional neural network (CNN) model. The objective was to accurately classify signals emitted from various drone controllers in real-time, despite mixed signals from multiple drones. Signals were captured using the HackRF Software Defined Radio (SDR) and a dedicated antenna setup, originating from different drone controllers. The raw signals were preprocessed in MATLAB to generate spectrograms, which served as the primary input for training the YOLOv8 model. After labeling the spectrograms, the model was trained to differentiate between the signals, even in overlapping scenarios. To facilitate real-time classification in dynamic environments, a custom wrapper code was developed to integrate the trained YOLOv8 model for live testing, enabling effective identification of drone signals amid simultaneous transmissions. This project showcases the feasibility of utilizing deep learning models like YOLOv8 for real-time drone signal classification, providing an efficient framework for signal identification in complex conditions.

# Project Folders

## Making_Spectrograms
This folder has 2 files:
1. **.txt to .csv**: This module will convert the received .txt files from the data acquisition system to be saved as .csv files, after being divided into I and Q channels.
2. **.csv files to spectrogram**: This module will take the data from .csv file and plot spectrograms of given chunk size and save them at a specified directory.

## Model+Wrapper
This folder has 3 files:
1. **Wrapper.cpp**: This cpp file should be compiled and executed first. This is linked to the Wrapper-helper module internally. This will extract the I and Q channel from the .txt file and send them as a complex values array to the Wrapper-Helper module.
   
2. **Wrapper-Helper.py**: This Python module will receive the complex array values from the Cpp code and plot spectrograms taking chunks of 5.3 crore samples. The model will then run inference on these spectrograms to give and save predictions.

3. **Command-to-run**: This is the command that needs to be entered to start the wrapper.

# Others

This section includes 2 folders:
1. **GPU Testing**: This is my work for future implementation. When plotting will need to be done using GPU, these libraries (Plotly, Vispy) can be used. I have also tested with Bokeh, but it could not plot signals for 1 crore samples.

2. **Labelling_Automation**: This code gives an overview of an approach to automate the process of labeling the spectrogram images. It uses the flood fill algorithm and calculations to do this efficiently.

3. **YOLO**: This code automates the process of converting the data received after labeling from YOLO label into a "YOLO Friendly manner." The overview of the "YOLO Friendly manner" is given in the SRS document.

## Final_Report
This is the final report of the entire project.

# Dataset Used

1. The dataset collected includes signals from FS-GT2, Radio link AT9S pro, Wi-Fi (802.11 n, 802.11 g), RFD900 Telemetry module, and HolyBro module.
2. The data is sampled at a 245.76 MHz sampling frequency and 200 MHz bandwidth.
3. For Wi-Fi, FSGT2, and AT9S pro: the center frequency is 2450 MHz.
4. For RFD900 and HolyBro: the center frequency is 900 MHz.
5. The dataset has 3200 million (320 crore) samples for each data category mentioned above.

# Accuracy and Recall Scores

For the **RFD900 + Wi-Fi + Holybro model**:
- **Precision**: 92
- **MAP50**: 90
- **Recall**: 80

For the **FSGT2 + Wi-Fi + AT9S pro model**:
- **Precision**: 88
- **MAP50**: 88
- **Recall**: 82



## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

