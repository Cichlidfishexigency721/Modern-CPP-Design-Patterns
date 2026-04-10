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

    %% Relationships using only your defined symbology:

    Command ..> CowAction
    Command ..> DogAction
    Command ..> CarAction

    CommandExecutor *-- "1" Cow
    CommandExecutor *-- "1" Dog
    CommandExecutor *-- "1" Car

    Client *-- "n" Command
    Client ..> CommandExecutor
```

### Design Note:
In this modern approach, the 'Command' is a type-safe union (std::variant) of
plain structs. The 'CommandExecutor' holds references to the receivers,
establishing a 'Has_a' relationship (Composition). The Client manages a
collection of commands by value and depends on the Executor to process them via
'std::visit'.
