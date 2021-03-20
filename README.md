# AdaShip - Battleship game in C++

## Challenge Outline

### Summary and review of the problem

Adaship is a command-line game based on the traditional board game battleship. Players take turns trying to destroy each other's battleships placed along a grid. This means that boards will have to hold data relating to placed boats, fired shots and missed shots. The player also needs to be able to take torpedo shots, and receive information on the result of the shot (hit/miss). Once all opponent ships are destroyed then then the player wins the game. A CPU player needs to be created utilising an auto-placing feature. The boards will also need to be displayed to the user containing the placed ships and hits/misses. The game needs to prevent invalid input but also invalid auto placing & manual placements.

The language we are using is C++, a low level language from the C family. I will be using OOP, which in addition to C++ I have little to no experience in.

My implemented solution implements all of the following requirements and implements a fully working game.

##### 1 player v computer

One human player plays against a 'fake' player which automatically takes shots, and automatically places ships.

##### 2 players

Two human players play against each other, both manually entering shots.

##### Custom board size

The size of the board will be loaded from a file. This means the size could be between 5x5 to 80x80.

##### Salvo game variation

In this version of the game, the players can take as many shots as they have remaining ships.

##### Custom boats

This means that when the ini file is modified, the ships are dynamically loaded in and therefore can have custom names and sizes.

##### Hidden mines variation

This version places mines around the board in hidden locations, where if the user hits that square, then the surrounding 8 squares are also destroyed.

##### Improved ‘computer’ player targeting capabilities

This is an algorithm that improves the targeting of the computer player(s). This means that the computer understands the basic Battleship tactic of trying squares around where a ship has already been hit.

### UML Diagram

I created a UML diagram of the classes and how they would interact, and what methods and properties they would have (this changed slightly over time but remained very similar to this structure).

![UML Diagram](UML.png 'UML Diagram')

### Development Strategy

My overall plan is an iterative approach, first building out the basic components, then creating the entire flow of a basic pass grade version of the game. After this I will gradually add new features from merit, and refactoring as I go. Finally I will add distinction level features and refactor my solution.

To ensure quality, I will write code for an epic as a function in an isolated environment (replit) until it met the requirements which that epic needed to fill. I will test this from the main funciton as a basic unit testing framework. Then I will conduct a code review and refactor my work, testing again manually for bugs and regressions. Then I would integrate it into the rest of my code base and conduct manual integration tests locally.

### Analysis and Decomposition

I will be taking an Object-Oriented approach to development, separating similar logic into separate classes which contain relevant data and functionality. I will be keeping these in separate files to make it a maintainable and readable structure. I will have a main Game class that will act as a controller for the flow and functions of the game. The rest of the game can be decomposed into smaller classes that represent the different objects that interface with each other in the game.

As this project has ambitious deadlines, I prioritised the work by grade awarded, as ensuring I have met all the pass and merit criteria is crucial before starting the distinction level features. However, I needed to be aware of the distinction criteria in order for me to write my code in a way in which it would be flexible enough to accommodate these features, for example, my capture of coordinates input had to appreciate that the sizes would need to be up to 80x80 and would need to accommodate two characters as input.

Within this, I broke the task into documentation requirements and coding requirements. The coding requirements were split into core game functionality, for example, loading the game config data was an epic, and creating the board was another.

### OOP Considerations

This basically consisted of the aforementioned `Game` class, which controls the flow of the game and acts as the parent of all other objects. It will need to handle menu input, loading configuration from the ini file and setting up the data needed to start the game.

I also created a `Player` class for each player, which can have an array of ships and have an `Ocean` object, which is essentially their gameboard containing a 2D array of `Square` classes. These hold information about if that coordinate is a ship, a mine, whether they have been hit or if they are just ocean. These will hold pointers to items in an array of `Ship` classes belonging to each `Player`. The `Ship` class holds information about how many squares are remaining and if they have been destroyed or not. This is illustrated in my UML diagram.

I will also create a `Helper` file which will contain a number of function which will be reused across the codebase to reduce code reuse. This includes getting user input, formatting and more.

## Development

### Good standards

Throughout the codebase, I adopted a number of good programming practices. For example, I created a file of helper functions that would be reused across the codebase in order to reduce code repetition and increase flexibility. I also ensured my code was readable and simple for another developer to read and understand. To do this I used consistent white spacing, styling and used descriptive variable names to help reading. I also avoided unnecessary logic whenever I could to ensure maintainability. Furthermore compartmentalised related code into separate files to separate concerns and ensure reusability. All objects were designed to be dynamic, and minimal hardcoding was used in the program.

### Phase n Development

For my developmental phases, I would write code for an epic in an isolated environment (replit) until it met the requirements which that epic needed to fill. Then I would conduct a code review and refactor my work, testing again manually for bugs and regressions. Then I would integrate it into the rest of my code base and conduct manual integration tests locally. During development, after implementing a basic version of a feature, I would leave a comment of `// todo: lorem ipsum` explaining what improvements should ideally be made before hand in. This meant that I could keep track of refactors and things which could be improved after the basic implementation is done.

### Ensuring Quality

Quality is ensuring that code is robust - it must work in all cases and be able to handle incorrect input to ensure that it performs in all circumstances. Quality is also ensuring that the code is succinct - it must achieve its purpose in a concise and simple manner.

Unfortunately, I did not have time to create a framework of unit tests for my code. Ideally, this would be in place and would have helped me ensure that the individual features of my code were working correctly, and each refactor and modification would not need to be manually tested. As mentioned, I tested the feature in an isolated environment, then tested it again after integrating it into my codebase to isolate any bugs. This meant that I could isolate the root cause of bugs much easier than directly in the program. It also meant I could test much quicker than compiling and running through the whole game. Serious game-breaking bugs needed to be addressed as soon as possible, whereas non-blocking and aesthetic bugs were of the lowest priority.

### Key Design Challenges

#### State management

I found this challenging as I wasn't sure how best I could allow state to be modified across the program, but also keep this state concurrent. I decided that the best way to do this would be to create a hierarchy of objects in a tree structure, similar to how data is passed around in a simple React project. This meant that data that needed to be drawn from the lower leaves of the tree could be stored and initialised where these branches converge, allowing state to exist in a single location and only be at a level where it was necessary to be. This ensures data quality whilst minimising redundancy and space complexity.

####

####

## Evaluation

### Analysis

refactoring, reuse, smells

### Advanced programming skills

recursion
state machine
observer/pointer

### Features Showcase

### Improved targeted algorithm

For this requirement, there were a few ways of implementing such a targeting algorithm. The first is a 'quick and dirty' algorithm that could essentially cheat, reading where the ships were and based on that information having a greater chance of hitting them. After all, there is no requirement for the AI to follow the rules - the end result makes no difference to the human player. In a way, this could be better as the chances of hitting a correct ship could be linearly scaled with the difficulty chosen by the player.

I decided to implement the strategy that a human would deploy in a real game of battleship. I considered how a human plays - they guess randomly at first, then after hitting try the four squares around this to determine the direction of the ship. Then, the player tries shots along this determined direction until the ship is destroyed.

### Reflective review

My experience with programming is almost exclusively with front-end frameworks such as Vue and React. This was a challenge for me as the management of front end state and object-oriented design is quite different, and I was never sure of what the best practices and design patterns were for this style of coding. In the end, I think my data management similarly reflects the hierarchy of state in a modern frontend framework, which I'm not sure is the best method but worked for this program.

I also struggled with the memory management of C++ and the language's lack of traceability found in front end development, and descriptive error messages (looking at you, segmentation fault). However, this is something I got used to, and I began to appreciate the data-driven model of object-oriented programming.

## Running the project

`g++ -pthread -std=c++17 main.cpp "Game/Game.cpp" "Ocean/Ocean.cpp" "Square/Square.cpp" "Ship/Ship.cpp" "Player/Player.cpp" && ./a.out`
