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
    A[Class A] --|> B[Class B] -- Inheritance_Public
```

```mermaid
graph LR
    C[Class A] *-- D[Class B] -- Composition_Ownership
```

```mermaid
graph LR
    E[Class A] o-- F[Class B] -- Aggregation_PreBuildData
```

```mermaid
graph LR
    G[Class A] ..> H[Class B] -- Dependency_CreatesInstance
```
