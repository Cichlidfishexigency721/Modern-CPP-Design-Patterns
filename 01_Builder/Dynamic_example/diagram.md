```mermaid
classDiagram
    class Engine {
        -int power_
    }
    class Wheel {
        <<interface>>
    }
    class StandardWheel
    class HeavyDutyWheel
    
    class Car {
        -float weight_
        -float width_
        -int doorCount_
        -string color_
        -Type type_
        +print()
    }

    class Builder {
        -float weight_
        -float width_
        -int doorCount_
        -string color_
        -int power_
        -int wheelCount_
        +setWeight(float)
        +setWidth(float)
        +build()
    }

    Wheel <|-- StandardWheel
    Wheel <|-- HeavyDutyWheel
    Car *-- Engine
    Car *-- Wheel
    Builder o-- Engine
    Builder o-- Wheel
    Builder ..> Car
    note for Builder "Nested inside Car"
```

### Symbology Reference


| Symbol | Meaning | C++ Implementation |
| :--- | :--- | :--- |
| **` <|-- `** | **Inheritance** | `public Wheel` |
| **` *--  `** | **Composition** | `std::unique_ptr` (Ownership) |
| **` o--  `** | **Aggregation** | Configuration / Pre-build data |
| **` ..>  `** | **Dependency** | `build()` method creates `Car` |
