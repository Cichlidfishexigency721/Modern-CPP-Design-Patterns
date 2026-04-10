# Finite State Machine (CD Player - Variant Version)

```mermaid
classDiagram
    class StateVariant {
        <<variant>>
        std::monostate
    }

    class Closed_without_CD {
        -FSM* fsm
        +open()
    }

    class Open_without_CD {
        -FSM* fsm
        +close()
        +insert_CD(int)
    }

    class Open_with_CD {
        -FSM* fsm
        +close()
        +remove_CD()
        +play()
    }

    class Closed_with_CD {
        -FSM* fsm
        +open()
        +play()
    }

    class Playing {
        -FSM* fsm
        +stop()
        +pause()
        +next_song()
        +previous_song()
    }

    class Paused {
        -FSM* fsm
        +play()
        +stop()
    }

    class FSM {
        -StateVariant state_
        +string name
        +bool tray_open
        +bool playing
        +bool cian_light_on
        +transitionTo~T~()
        +open()
        +play()
    }

    class Client {
        +main()
    }

    FSM *-- "1" StateVariant : state_

    StateVariant ..> Closed_without_CD
    StateVariant ..> Open_without_CD
    StateVariant ..> Open_with_CD
    StateVariant ..> Closed_with_CD
    StateVariant ..> Playing
    StateVariant ..> Paused

    Closed_without_CD *-- "1" FSM
    Open_without_CD *-- "1" FSM
    Open_with_CD *-- "1" FSM
    Closed_with_CD *-- "1" FSM
    Playing *-- "1" FSM
    Paused *-- "1" FSM

    Client ..> FSM
```

### Design Note:
In this modern variant-based FSM, inheritance and the dynamic registry are
replaced by a type-safe union (std::variant). The FSM class owns the current
state by value on the Stack. Transitions are handled via 'std::visit' and
'transitionTo<T>', which leverages RAII: assigning a new state to the variant
automatically triggers the destructor of the previous state (onExit) and the
constructor of the new one (onEntry). This provides both memory safety and high
execution performance.
