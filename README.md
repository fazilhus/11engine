# 11Engine
## About
And engine for building AI systems for games

## Usage
### FSM
#### Pause Button
Pauses and unpauses the simulation
#### Silder
Controls the tick rate of the simulation (from 60 times a second to once in 2 seconds)

![FSM Graphical User Interface](/doc/fsm-gui.png "fsm")

### Path
#### Main menu
- Press either one of three on the keyboard to select a map
- Press Key ‘Escape’ to exit the app

![Path Graphical User Interface Main Menu](/doc/path-gui-main.png "path main menu")

#### Game Loop
- Press Key ‘Q’ to go back to ‘Main Menu’
- Press Key ‘Escape’ to exit the app

![Path Graphical User Interface Game Loop](/doc/path-gui-loop.png "path game loop")

---

## Build and Compile
### Windows
#### Visual Studio Solution generation
Run `premake-VisualStudio.bat` or run a shell command `premake5.exe vs2022`

---

#### Compilation
Open the resulting .sln file in Visual Studio and build it

---

#### Run the Application
The built application is located in `./bin/{Debug|Release}/` under the name `{fsm|path|test}.exe`
Make sure that the maps are located in `./bin/{Debug|Release}/path/res/` before running the `path.exe` application. The maps can be found in `./path/res/`
