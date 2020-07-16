# DAML_Project_Jul2020_33537140

## DualShock 4 Regression FM Synth

An FM synthesiser plugin programmed in JUCE, utilising RapidLib machine learning functions to allow gesture->parameter mappings with a games controller.

### How to run:

The machine learning gesture-mapping functionality of this software requires a Sony DualShock 4 controller, as well as Max/MSP to run the patch that extracts the data from the controller.

Assuming that you have both of these:

#### Opening:

1) Build and launch the software, either from within a digital audio workstation, or as a standalone application.

2) Launch the Max/MSP patch named "controllerOSC_JUCE.maxpat", with your DualShock 4 controller connected. Select "Wireless Controller" from the dropdown menu within the patch.

3) Having verified that motion data is streaming when you move the controller in space, the data should be received in the JUCE application via OSC (though currently there is no indicator to verify this).

#### Gesture Mapping (create pairings between the controller position and the FM parameters):

4) Set the parameter(s) to value(s) that you would like to pair with a specific controller position (currently, only the Harmonicity [ratio], the Mod Index, and the LFO Frequency are mappable). For example, turn the Harmoncity ratio to 10.

5) Hold the controller in some static position, and hold the triangle button on the games controller for around a second to record some examples. You can also move the controller whilst recording, so that a range of controller positions will recall the given parameter settings.

6) Repeat this process with other parameters and controller positions.

7) Hit the "Train" button to train the regression model, and lock these mappings in.

8) Hold the X/Cross button on the games controller to run the model. Move the controller between the positions you have mapped to recall the parameter settings. Try new positions and see what happens!











Student No: 33537140
Module: Data and Machine Learning for Creative Practice
Coursework: Project

Please see the gitHub repository for the code of my work:

https://github.com/MartinTownley/DAML_Project


For documentation, please refer to the following blog:

https://damlproject.art.blog

