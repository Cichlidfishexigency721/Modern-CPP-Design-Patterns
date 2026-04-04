# Builder Pattern (Dynamic)

```mermaid
classDiagram
    class Engine { -int power_ }
    class Wheel { <<interface>> }
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

```mermaid
graph LR
    A[Class A] --|> B[Class B]
    Description1(Inheritance / public)
```

```mermaid
graph LR
    C[Class A] *-- D[Class B]
    Description2(Composition / unique_ptr ownership)
```

```mermaid
graph LR
    E[Class A] o-- F[Class B]
    Description3(Aggregation / Pre-build data)
```

```mermaid
graph LR
    G[Class A] ..> H[Class B]
    Description4(Dependency / creates instance)
```
