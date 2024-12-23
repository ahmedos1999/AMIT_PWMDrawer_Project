
# AMIT PWM Drawer Project

The AMIT PWM Drawer is an embedded systems project developed as part of the AMIT Embedded Systems Diploma. 
This project involves creating a Pulse Width Modulation (PWM) drawing device using the Atmega32 microcontroller, designed to visualize PWM signals and their corresponding duty cycles.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation and Setup](#installation-and-setup)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Project Overview

The PWM Drawer project aims to provide a visual representation of PWM signals, which are commonly used in embedded systems for controlling devices such as motors and LEDs.
By utilizing the Atmega32 microcontroller, this project captures PWM signals and displays their characteristics, aiding in the understanding and analysis of PWM behavior.

## Features

- **PWM Signal Visualization**: Displays the waveform of PWM signals in real-time.
- **Duty Cycle Calculation**: Calculates and shows the duty cycle percentage of the PWM signal.
- **Frequency Measurement**: Measures and displays the frequency of the PWM signal.
- **User-Friendly Interface**: Provides an intuitive interface for easy interaction and analysis.

## Hardware Requirements

- **Atmega32 Microcontroller**: Serves as the core processing unit.
- **LCD Display**: For visual representation of PWM signals and parameters.
- **Signal Input Interface**: To feed PWM signals into the microcontroller.
- **Power Supply**: Appropriate power source for the microcontroller and peripherals.

## Software Requirements

- **Atmel Studio**: For writing and compiling the firmware code.
- **eXtreme Burner - AVR**: For uploading the compiled code to the microcontroller.
- **Proteus**: For simulating the circuit design.

## Installation and Setup

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/ahmedos1999/AMIT_PWMDrawer_Project.git
   ```

2. **Open the Project in Atmel Studio**:
   - Launch Atmel Studio.
   - Navigate to `File` > `Open` > `Project/Solution`.
   - Select the `.atsln` file located in the cloned repository.

3. **Build the Project**:
   - Click on `Build` > `Build Solution` to compile the code.

4. **Upload the Firmware**:
   - Connect your Atmega32 microcontroller to your PC via a programmer.
   - Use AVRDUDE or Atmel Studio's programming tool to upload the compiled `.hex` file to the microcontroller.

5. **Set Up the Hardware**:
   - Assemble the circuit as per the schematic provided in the `Simulation` folder.
   - Ensure all connections are secure and the power supply is appropriate.

## Usage

1. **Power On the Device**:
   - Once powered, the LCD should initialize and display the welcome message.

2. **Input PWM Signal**:
   - Connect the PWM signal source to the designated input pin on the microcontroller.

3. **View Signal Parameters**:
   - The LCD will display the PWM signal's frequency and duty cycle in real-time.

## Project Structure

- `/Source`: Contains the firmware source code written in C.
- `/Simulation`: Includes the Proteus simulation files and circuit schematic.
- `/Documentation`: Additional documents and resources related to the project.

## Contributing

Contributions are welcome! If you'd like to improve or expand this project, please fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Acknowledgments

Special thanks to Eng.Eman for her guidance and support throughout the development of this project.
