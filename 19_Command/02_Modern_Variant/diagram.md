# Command Pattern (Modern Variant)

```mermaid
classDiagram
   class CowAction {
      <<struct>>
   }
   class DogAction {
      <<struct>>
   }
   class CarAction {
      <<struct>>
   }

   class Command {
      <<variant>>
   }

   class Cow {
      +moo()
   }

   class Dog {
      +bark()
   }

   class Car {
      +turnOn()
      +turnOff()
      +rev()
   }

   class CommandExecutor {
      -Cow& cow
      -Dog& dog
      -Car& car
      +operator()(CowAction)
      +operator()(DogAction)
      +operator()(CarAction)
   }

   class Client {
      +main()
   }

   %% The Variant is composed of several data types
   %% We use dependency here as there is no inheritance
   Command ..> CowAction
   Command ..> DogAction
   Command ..> CarAction

   %% The Executor (Visitor) holds references to the Receivers
   %% Aggregation (o--) - Multiplicity "1" at the end
   CommandExecutor o-- "1" Cow
   CommandExecutor o-- "1" Dog
   CommandExecutor o-- "1" Car

   %% The Client manages the collection of commands by value
   %% Composition (Has_a) - Multiplicity "n" at the end
   Client *-- "n" Command : queue_

   %% The Client uses the Executor to process the variant
   Client ..> CommandExecutor : via std::visit
```

### Design Note:
In this modern approach, the 'Command' is a type-safe union (std::variant) of
plain structs. There is no base class and no virtual methods. The
'CommandExecutor' gathers all the logic that was previously scattered in command
classes. This ensures 'Value Semantics' (commands are stored directly in the
vector) and 'Static Safety' (the compiler verifies all actions are handled
during visitation).