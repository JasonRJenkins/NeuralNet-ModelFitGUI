# NeuralNet-ModelFitGUI
Implements a single hidden layer feedforward neural network and uses it to fit a model to a selectable dataset.

This is a C++/CLI version of the NeuralNet-ModelFit project - https://github.com/JasonRJenkins/NeuralNet-ModelFit.

Unlike the standard C++ version this version implements a form based GUI that allows the user to explore the various settings that can be applied to a simple single hidden layer neural network that can be used to model the potential relationship between a single predictor variable (X) and a single corresponding response variable (Y) chosen from a selected .CSV data file.

To build the project you will require Visual Studio 2017 (the Community version is sufficient).  Once you have downloaded the source and copied or moved the ModelFitGUI directory and all its contents to your desired location start Visual Studio. You can then open the ModelFitGUI project file (ModelFitGUI.vcxproj) which is located within the ModelFitGUI directory by selecting the Open-Project/Solution option from the File menu. You can then build the solution and run the application. N.B. When the project is opened it may take a few moments to fully initialise - this is indicated on the status bar at the bottom of the IDE. If you open the ModelFitGUIForm.h file during this period you will get an error. But this won't affect the build and if you re-open the file after the project has been initialised the Windows Form design window should open correctly.

The same three datasets used by the C++ version have been included: Auto.csv; Credit.csv and Wage.csv. But you are not restricted to these datasets - you can load any dataset you like if it is available in .CSV format. The desired dataset is loaded into the application via an 'Open File Dialog box' accessed through the 'Browse' button and once the various model settings have been selected a model can be fitted to the data using the 'Fit Model' button.  Once training is complete and a model has been fitted to the data you can save the model output to either a .CSV or an Excel (.XLS) file. The output consists of 3 columns - the first contains the selected training set input (or predictor) values, the second the selected training set target values and the third contains the trained model output responses to the given input values. In addition, the Excel output also contains a plot of the fitted model. If you want to automatically view the Excel output at the end of the training process then tick the 'Show output in Excel' checkbox. The trained network can also be serialised and saved to a file.

1) Using the Auto.csv dataset the relationship between 'horsepower' and 'mpg' can be modelled using the following settings:

Predictor Variable (X) = horsepower, Response Variable (Y) = mpg

Output Layer: Activation Function = Elliot, Slope = 35, Amplify = 1

Hidden Layer: Activation Function = ISRU, Slope = 5, Amplify = 40

The Main Settings should be left with their default values. In this example the application will converge to a solution very quickly.

2) Using the Credit.csv dataset the relationship between 'Balance' and 'Rating' can be modelled using the following settings:

Predictor Variable (X) = Balance, Response Variable (Y) = Rating

Output Layer: Activation Function = Elliot, Slope = 10, Amplify = 1

Hidden Layer: Activation Function = SoftPlus, Slope = 10, Amplify = 10

In the Main Settings set the Min. Network Error to 600, the Scale Factor to 2000 and leave all the other settings with their default values. This example will also converge to a solution fairly quickly

3) Using the Wage.csv dataset the relationship between 'age' and 'wage' can be modelled using the following settings:

Predictor Variable (X) = age, Response Variable (Y) = wage

Output Layer: Activation Function = Elliot, Slope = 10, Amplify = 1

Hidden Layer: Activation Function = SoftPlus, Slope = 10, Amplify = 10

In the Main Settings set the Min. Network Error to 2450, the Scale Factor to 1000 and the Number of Iterations to 10000 leaving all the other settings with their default values. In comparison to the other examples this example will converge to a solution fairly slowly owing to the large size of the dataset.
