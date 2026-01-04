### Delta_Timer
The `Delta_Timer` class is placed in the Infrastructure library because it provides a low-level utility for measuring time intervals and controlling frame-independent updates.
Its functionality is generic and not tied to any specific game logic or domain concepts, making it a service that can be reused across multiple parts of the system.
Including it in the Model layer would violate the separation of concerns, as the Model should focus on representing the game state rather than handling timing mechanics.
By keeping it in Infrastructure, the system maintains a clean distinction between core utilities and the game’s business logic.
This design also allows for easier testing and replacement if the timing mechanism needs optimization or adaptation to different platforms.

### Random
The `Random` class belongs in Infrastructure because it serves as a general-purpose utility for generating random numbers or values.
Randomization is a fundamental tool that can support various parts of the system, from AI behavior to procedural content generation, without being tied to a specific domain concept.
Placing it in the Model layer would blur the line between core domain logic and utility functionality, potentially making the Model dependent on implementation details.
By keeping `Random` in Infrastructure, the design remains modular, and other components can rely on it without introducing unnecessary coupling.
It also ensures that the Model remains predictable and focused on representing the state of the game.

### Score
The `Score` class is kept in Infrastructure because it provides a basic container for numerical scoring and related operations, acting as a simple utility rather than a domain-specific concept.
While it represents data, its primary role is as a helper for storage and calculations, which can be leveraged across multiple game modules.
Placing it in the Model would conflate utility responsibilities with domain logic, undermining the clarity of the MVC pattern.
Housing it in Infrastructure allows the Model to focus on core entities and rules while relying on `Score` as a reusable component.
This separation simplifies maintenance and encourages consistent handling of scoring across different game systems.

### ScoreBoard
The `ScoreBoard` class resides in Infrastructure because it handles the presentation and storage of scores in a generalized way, independent of specific game logic.
Its responsibilities include formatting, storing, and possibly retrieving scores, which are technical concerns rather than domain behaviors.
By keeping it out of the Model, the MVC separation is preserved: the Model focuses on the underlying game state, while `ScoreBoard` provides a utility layer for managing and displaying score data.
This arrangement also allows multiple models or games to reuse the `ScoreBoard` without modification. It supports modularity and reduces dependencies between core logic and ancillary functionality.
