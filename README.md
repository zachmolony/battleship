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

![UML Diagram](documentation/UML.png 'UML Diagram')

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

For my developmental phases, I would write code for an epic in an isolated environment (replit) until it met the requirements which that epic needed to fill. Then I would conduct a code review and refactor my work, testing again manually for bugs and regressions. Then I would integrate it into the rest of my code base and conduct manual integration tests locally. My commits detail the work I completed in that session. During development, after implementing a basic version of a feature, I would leave a comment of `// todo: lorem ipsum` explaining what improvements should ideally be made before hand in. This meant that I could keep track of refactors and things which could be improved after the basic implementation is done. These can be seen throughout my commits, indicating incomplete features, bugs which I spotted that need to be fixed, or general improvements/refactors which I could see improving the code base along the way. (some of these may still be there :)).

### Ensuring Quality

Quality is ensuring that code is robust - it must work in all cases and be able to handle incorrect input to ensure that it performs in all circumstances. Quality is also ensuring that the code is succinct - it must achieve its purpose in a concise and simple manner.

Unfortunately, I did not have time to create a framework of unit tests for my code. Ideally, this would be in place and would have helped me ensure that the individual features of my code were working correctly, and each refactor and modification would not need to be manually tested. As mentioned, I tested the feature in an isolated environment, then tested it again after integrating it into my codebase to isolate any bugs. This meant that I could isolate the root cause of bugs much easier than directly in the program. It also meant I could test much quicker than compiling and running through the whole game. Serious game-breaking bugs needed to be addressed as soon as possible, whereas non-blocking and aesthetic bugs were of the lowest priority.

### Key Design Challenges and Innovations

#### State management design

I found this challenging as I wasn't sure how best I could allow the state to be modified across the program and keep this state concurrent. I decided that the best way to do this would be to create a hierarchy of objects in a tree structure, similar to how data is passed around in a simple React project. This meant that data that needed to be drawn from the lower leaves of the tree could be stored and initialised where these branches converge, allowing state to exist in a single location and only be at a level where it was necessary to be. This ensures data quality whilst minimising redundancy and space complexity.

#### Memory Management

I found this difficult as I have had almost no experience in memory management, and this was a complex project which had several different instances in which I had to deal with pointers and their associated memory. This may have been a failure/complication of my design - my design of an Object-Oriented tree structure meant that a lot of my Objects which were being added as properties of each other were not updating or erroring when accessed from another location in the code.
This was because I was declaring these objects inside of a function, then assigning a reference to this object to the parent object. However, once this 'setup' function ended, the object to which the reference was referring was lost. This meant that the compiler was trying to access memory which it wasn't allowed to. To solve this, when creating the objects, I created them as pointers with the `new` keyword and passed this pointer down. This meant that these pointers were all pointing to the same, valid object.
This memory also had to be freed up once the program ends. To do this I created destructors that freed up this memory at the end of the parent's life cycle.

#### Flexible Design

One of the requirements of the game was for it to have several different game modes, with different combinations of human and computer-controlled players. The same goes for an unexpected number and properties of ships, sizes of the board, and a lot of user inputs that needed to be validated/automatically generated.
This meant that keeping code repetition to a minimum was highly important in creating a maintainable, testable and expandable codebase. To do this, I needed to create specific purpose, agnostic functions which could be reused across the project. I also needed to ensure that my objects and methods were flexible enough to accommodate features that I had not implemented yet. An example of this is my game setup. By passing a variable representing the number of human players to a single setup function, I could create a game with the correct amount of human and computer-controlled players without having to hardcode methods to control this.

## Evaluation

### Analysis

#### Reuse

Throughout my code, I need to get inputs for, and generate, a range of data in multiple places in my code. To achieve this I created a Helper file. This contained a number of functions which could be repeated across my codebase. This is great as it improves maintainability and testability, while minimising the places for bugs to hide. An example of this is my random integer generator.

I need to generate random numbers between certain values. This is necessary to generate evenly distributed spaces on the board to place ships, and for the computer-controlled player to take shots at random coordinates. To minimise code repetition and prevent bugs, I created a function `randomInt` which took a maximum number as a parameter and returned a random number between these.
Furthermore, I used this function to derive another function's return, `randomBool`. This returns a boolean if the `randomInt` between 0 and 1 is equal to 1 (50% chance). See the implementation below.

![Random Function](documentation/randomfunction.png 'Random Function')

#### Refactoring

The random function, explained previously, was originally using the `rand()` function from the C++ standard library. This is a very poor pseudorandom implementation - the distribution of numbers was extremely biased, often repeating numbers multiple times and often staying within the same 20% of the maximum range. The implications of this were that ships were placed in very close proximity to each other, despite being placed on very large boards. Moreover, this method was painfully slow: placing ships could often take several seconds.
I upgraded the implementation of this random generation and implemented the Mersenne Twister pseudorandom number generation engine. This speeded up placement timings exponentially, and ship distribution was much more realistic. See the image above for the implementation.

#### Code Smells

##### Feature Envy
Feature envy is a code smell where an object performs a method on fields pulled from another object, rather than getting that object to do the calculation and returning that value. This was the case in my code when my `Game` class was performing methods based on data from my `Square` and `Ship` classes, at the other end of the tree. My `Game` class called a method on the `Square` which returned a tuple containing multiple bits of data about if the `Square` had been hit and the status of the `Ship` object it was referring to. This was unnecessary and overly complex. I refactored this code to instead not return any data, and handle the actions (outputting shot results to the user) internally.

![](documentation/codesmell1.png 'Intial Refactor')

![](documentation/codesmell2.png 'Final Refactor')

##### Long Methods
A method should not be too long, as code needs to be readable and maintainable. Methods should serve individual purposes to ensure decoupling and reusability. An example of this in my codebase was my `startGame()` method. This method controlled functionality far beyond its scope and I, therefore, split it into four smaller functions: `playGame`, `getWinner`, `takeTurn` and `takeSalvoTurn`.

![](documentation/longfunction.png 'Long Function')

### Advanced programming skills

##### Recursion

I needed to create a function that can convert letters inputted as coordinates when a player takes a shot, into an index for the coordinate on the x-axis. As the top line of the gameboard is labelled with letters, and the maximum size of a board can exceed the 26 characters in the alphabet, I needed to account for multicharacter inputs for values exceeding 26. In my implementation, I solved this by calculating the ASCII value of the second letter, then adding this to 26 multiplied by the return of the same function with the first letter.

![](documentation/recursion.png 'Recursion')

##### Pointers

As mentioned, the structure of the objects in my codebase follow a tree structure. This means that objects needed to be properties of each other, some with many-to-many relationships. These should be pointers, as we do not want to assign the actual object, instead, the address of it in memory. This means we can ensure we are accessing the same object which we want to refer to, rather than a copy of that object. Pointers are essentially new variables that point to created data, rather than references that sits in the same memory location as the created data.

![](documentation/pointer.png 'Pointers')

##### Memory Management

This however comes with data management issues, for example, we need to remember to free this memory when the data reaches the end of its life cycle. This is done with the `delete` keyword. This is used in the destructor of the parent class. If we do not do this, we can have memory leaks, where memory used by the program is never released back to the operating system once the program has ended. This is bad because it can reduce the amount of memory an operating system can use once the program is over.

![](documentation/memmgmt.png 'Memory Management')

##### Bitwise
In my `Game` class, I needed to switch between two different indexes in a two-item vector. These indexes are `0` and `1`, so switching between them needed to be done without accidentally accessing the index of `-1` or `2`. For this, I used bitwise, a level of operations involving working with individual bits. I used the exclusive or `XOR` operator, `^` which essentially flips the bit which the number is stored as. This is a single bit, so would flip `0` to `1` and vice versa. This is perhaps the simplest operation a computer can do, which, although, doesn't have much effect in this game, on a larger scale can be highly efficient.

![](documentation/bitwise.png 'Bitwise')

### Features Showcase

In addition to the aforementioned:

- Encapsulation though separated objects for distinct entities within the game.
- Highly flexible function and method implementations.
- Balanced randomiser using Mersenne Twister implementation.
- Helper function file to ensure reuse and modularity.
- Pointer connection of objects to ensure data synchronism.
- Memory management through `delete` in destructors and reset functions.
- Recursive implementations to reduce code repetition and improve efficiency.

One of the smaller features that make my implementation great is my presentation. This is done with a title sequence, clearing the screen after each page, and extensive formatting. This ensures a strong user experience as it keeps the amount of data shown to the user at any time to a minimum. This makes the user have a much more enjoyable experience.

![](documentation/ascii.png 'Title Screen')

In addition to this, I used a clear and consistent file structure to separate code by their function. This ensures readability, testability and maintainability. I included named header files to reuse my code across my other files in the project.

![](documentation/header.png 'Header Files')

### Improved targeted algorithm

I didn't have time to implement a fully-functional version of this algorithm, but there are a couple of ways in which I could have implemented it.

The first is a 'quick and dirty' algorithm that could essentially cheat, reading where the ships were and based on that information having a greater chance of hitting them. After all, there is no requirement for the AI to follow the rules - the end result makes no difference to the human player. In a way, this could be better as the chances of hitting a correct ship could be linearly scaled with the difficulty chosen by the player.

Alternatively, a strategy that a human would deploy in a real game of battleship could be implemented. Consider how you would play - they guess randomly at first, then after hitting try the four squares around the one you hit to determine the direction of the ship. Then, the try shots along this determined axis until the ship is destroyed. This would be implemented by simply adding one to the value of `x` or `y` generated on the previous shot.

### Reflective review

My experience with programming is almost exclusively with front-end frameworks such as Vue and React. This was a challenge for me as the management of front end state and object-oriented design is quite different, and I was never sure of what the best practices and design patterns were for this style of coding. In the end, I think my data management similarly reflects the hierarchy of state in a modern frontend framework, although I'm not sure is the best method, albiet worked for this program.

I also struggled with the memory management of C++ and the language's lack of traceability found in front end development, and descriptive error messages (looking at you, seg fault). However, this is something I got used to - I think it made me much more rigourous in making sure I understand every part of my code, rather than relying on developer tools and extensions. Furthermore, I began to appreciate the encapsulation and interfacing found in object-oriented programming, and rediscovered the joy of tinkering with the lower level aspects of a computer, which are seldom seen in modern web development.

## Running the project

`g++ -pthread -std=c++17 main.cpp "Game/Game.cpp" "Ocean/Ocean.cpp" "Square/Square.cpp" "Ship/Ship.cpp" "Player/Player.cpp" "Helper/Helper.cpp" && ./a.out`
