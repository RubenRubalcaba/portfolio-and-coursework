# Gotcha Anti theft lock
Part 1 Factory Preset Model

## Installation

Secret key is "10111100"


## Usage

```LogicWorks
To use the lock there is two buttons top is "1" the other is "0" the user needs to successfully type in a form of 10111100, if not the user gets a second try, of putting in the correct answer. If not the circuit will lock as it only accepts a maximum of 16 bits. Furthermore the user has to keep reset toggled at 1 for the duration of the usage and toggle to 0 and back to 1 when wanting to try inputting the numbers again. 
```

## Contributing
Ruben Rubalcaba 
within this folder is the state diagram,table and k maps. I chose to use as least amount of wires as possible by wrapping the outputs A,B,C around the circuit. The setup of the values go "ABC" in respectively with the first state being 001.

