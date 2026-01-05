
# Project Goal

## What the System Solves
The project is an educational implementation of the Pac-Man game, aimed at reproducing the basic game logic of the original: character movement, point collection, interaction with ghosts, game state and level management.
The system serves as a testing ground for practicing architectural design, working with the game loop, states, and component interaction.

## Non-Functional Requirements

The main focus is on clean architecture, extensibility, and testability.
The game logic is isolated from graphics and input so that behavior can be tested independently of SFML.
The architecture should allow new modes, rules, or AI to be easily added without rewriting existing code, while remaining simple enough for a learning project.


# Selected Architectural Style

---

![Game Architectural diagram](report/game_logic.png)

---

## MVC Architecture Overview

The project follows a clear **Model–View–Controller (MVC)** architectural pattern, which ensures separation of concerns, high testability, and independence of core game logic from rendering and input handling.

---

### Model

The **Model** layer contains all core game logic and domain rules and is fully independent from any rendering or platform-specific code.  
According to the documentation, this layer is primarily represented by the `model` namespace and includes:

- **World representation**: maze structure, tiles, and spatial data.
- **Game entities**: player character, ghosts, collectibles, and their state.
- **Game rules**: and collision logic.
- **Artificial intelligence**: ghost behavior implemented via strategy-based AI modes (`Chase`, `Scatter`, `Frightened`, and idle/house modes), located in `model::ai`.
- **State and events**: game state transitions and internal events used to notify other layers.

The Model does not depend on UI, rendering, or input systems, which allows it to be compiled and tested as a standalone library.

---

![model diagram](report/model.png)

---

### View

The **View** layer is responsible solely for visual representation of the current game state.  
Based on the documentation, this functionality is encapsulated in UI- and rendering-related components (e.g. rendering systems, HUD, visual assets).

The View:
- reads data from the Model,
- subscribes to model events using an **Observer mechanism**,
- renders entities, maze, and UI elements (score, lives, states).

The View never modifies the game state directly and has no knowledge of game rules.



### Controller

The **Controller** layer acts as an intermediary between user input and the Model.  
It is responsible for:
- processing player input,
- triggering state changes in the Model,
- managing the main game loop and update cycle.

Controller logic invokes Model operations in response to input events but does not contain game rules itself.

---

### Component Interaction

The interaction between components follows strict dependency rules:

- **Controller → Model**: updates game state based on input and timing.
- **Model → View**: notifies the View of state changes via events/observers.
- **View → Controller**: no direct dependency.

This unidirectional dependency structure enforces clean separation and prevents tight coupling between gameplay logic and presentation.

---

### Architectural Rationale

This MVC-based design was chosen to:
- keep game logic independent from rendering and input,
- simplify future extensions (e.g. new AI modes, entities, or UI),
- allow reuse of the Model layer across different platforms or frontends.

The documented use of strategies for ghost AI and event-based communication further reinforces modularity and extensibility.

---

![MVC diagram](report/mvc.png)

*Figure: High-level MVC architecture.  
The Model contains all core gameplay logic and AI, the View handles rendering and UI, and the Controller translates user input into model updates. Communication from Model to View is performed using an observer/event-based mechanism.*

---

## Stage Pattern Overview

The project leverages a Stage (Game State) pattern to manage different phases of the game, such as menus, levels, pause screens, and end-of-game sequences.
Each stage encapsulates its own:

- Initialization and cleanup logic,

- Event handling and input processing,

- Update cycle for game entities,

- Rendering instructions (via View layer).

A central Stage Manager handles transitions between stages, ensuring that only the active stage receives updates and input.
This approach prevents the main game loop from becoming a monolithic block of conditional logic and makes it easier to add new game modes or screens without affecting existing stages.

---

## Integration with MVC

The Stage pattern works together with MVC as follows:

- Each Stage contains its own Controller and references the relevant Model and View components for that phase.

- The Model remains decoupled and reusable, storing game logic and rules.

- The View renders only the entities and UI relevant to the current stage.

- The Controller within a stage handles stage-specific input and events, translating them to model updates.

This combination allows clean separation of game logic, presentation, and flow control, making both testing and feature expansion straightforward.

---

# Architectural Alternatives Considered

1. Monolithic Game Loop

   - All game states handled in a single loop with if/else conditions.

   - Rejected due to poor scalability and hard-to-maintain code as stages increase.

2. Pure State Pattern (without Stage Manager)

    - Could encapsulate stage behavior, but lacks a central point for stage transitions, complicating resource management and flow control.

3. Entity-Component-System (ECS)

    - Offers high flexibility for entity behaviors.

    - Considered overkill for a small educational Pac-Man project, adding unnecessary complexity.

4. Hexagonal / Clean Architecture

    - Strong modularity for large-scale systems.

    - Rejected because the project’s size does not justify extra abstraction layers.

---

# Namespaces and Libraries (Modules/Layers)

The project is organized into namespaces and libraries to enforce clear separation of responsibilities and reduce coupling:

1. `model` namespace / library

    - Contains all core game logic: player and ghost behavior, collision detection, and AI.

    - Fully independent from rendering or input.

    - Can be compiled and tested as a standalone module.

2. `view` namespace / library

    - Handles all rendering, UI, and visual feedback.

    - Observes the model for state changes via events/observer mechanisms.

    - Never modifies game logic.

3. `controller` namespace / library

    - Interprets user input and translates it into updates to the model.

    - Manages the main game loop and updates the active stage. 
4. `stg` namespace / library

   - Encapsulates individual game phases (menu, level, pause, game-over). Each stage has its own controller and references relevant model/view components. Stage Manager centralizes stage transitions, keeping flow control clean and preventing monolithic loops.
   
5. `infra` (infrastructure) namespace / library
   - Provides generic, reusable utilities that support the system but do not represent domain logic. Examples include:

   - `Delta_Timer`: measures time intervals for frame-independent updates. Placing it in Model would violate separation of concerns, as timing is a technical utility, not game logic.

   - `Random`: generates random values used by AI or procedural systems. Keeping it in Infrastructure ensures the Model remains predictable and free of implementation details.

   - `Score`: a helper container for numerical scoring, calculations, and storage. Its utility nature makes it reusable across multiple modules without blurring Model responsibilities.

   - `ScoreBoard`: manages storage, formatting, and retrieval of scores independently from game rules. This preserves MVC separation and allows reuse across different games or modules.

By organizing these utilities in the Infrastructure library, the system maintains a clean distinction between core domain logic and supporting services, which simplifies testing, extension, and platform adaptation.

---

# Patterns used

In addition to the MVC, Observer, Abstract Factory, Singleton, and State patterns (described in README.md), several additional patterns are also used.


### Data Transfer Object (DTO)

The DTO pattern is used to encapsulate data structures for communication between different layers of the system, particularly between the Model and View or between the Model and Infrastructure components.
DTOs carry only data without any business logic, ensuring that changes in the Model’s internal representation do not propagate directly to the UI or external modules.
This simplifies serialization, event emission, and testing by providing a clean, immutable snapshot of the current state.

### Visitor

The Visitor pattern is employed to separate algorithms from the objects on which they operate, allowing new operations to be added without modifying existing class hierarchies.
In this project, it can be used for traversing game entities, nodes in the AST, or other structured objects, enabling flexible operations like rendering, scoring updates, or state inspection.
This promotes open/closed principle compliance: the object structure remains stable while new behaviors can be introduced via Visitors.

---

# Compromises

### View_Collector_Factory

Why are View and Event Collector assembled in one place, even though they have completely different roles, uses, and purposes?
This is because in order to receive events from SFML, a window must be open, and its ownership is directly linked to View.
And no, the event collector itself does not have access to the window.
It uses one of the interfaces from which SFML_View is collected.

### View is unique to the entire game

It is not unique for each stage. This is directly related to the fact that the number of sprites for the game is quite small.
Also, the lack of uniqueness made it possible not to transfer windows from View to View, not to rewrite the Event Collector, and not to read new files after loading the configuration at the beginning of the game.

---

# Extensibility and support

### New stages of the game

If this is necessary, the following steps must be taken:
- Register the Stage UI 
- Connect the Controller for the Stage
- Record the event that will trigger the creation of this Stage
- Add tracking for this event in the Stage Controller
- Register the creation of this stage

### Adding new sprites/fonts to View 

Simply fill in the View configuration and all sprites/fonts will be added to the system upon loading.

### Adding new model elements and displaying them 

Write them in the Model, record access to them in Constant Access to the Model, and then add your method of interpreting them in the corresponding UI class.
