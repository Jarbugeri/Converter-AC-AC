# Control Application

This repository contains a control application developed for STM32F103C6TX microcontrollers. The application utilizes an LCD screen, buttons, and control functions to monitor and adjust parameters in a system.

## Features

The application has the following features:

1. Main Menu: Displays options to the user and allows navigation between them using the UP and DOWN buttons. The user can select an option by pressing the MENU button.

2. Monitoring: Displays relevant information on the LCD screen, such as the operating frequency and the reference frequency of the system. The user can adjust the reference frequency using the UP and DOWN buttons.

3. Parameters: Allows the user to adjust system parameters. The LCD screen shows the menu name and the selected parameter name. The current value of the parameter is also displayed on the second line of the screen. The UP and DOWN buttons are used to navigate between parameters and adjust their values.

## Initial Setup

Before using the application, an initial setup is required. This setup includes defining the initial values of parameters and initializing the filters and signal generators necessary for the proper functioning of the system.

## Usage

The application has a main loop called `app_loop` that continuously executes the functionalities. Within this loop, the state of the buttons is read, and the corresponding function for the current menu is called. This process is repeated indefinitely, allowing the user to interact with the application intuitively.

## Images

Below are two images illustrating the application in action:

![Inverter Acceleration](Registers/Aceleration.pnh)

![Inverter Acceleration zoom](Registers/Aceleration_zoom.jpg)

Please add the corresponding images using the provided links to visualize the application's figures in operation.

## Contribution

Contributions to the improvement and enhancement of the application are welcome. Feel free to open an issue or submit a pull request with your suggestions.

## License

This project is licensed under the [MIT License](LICENSE).
