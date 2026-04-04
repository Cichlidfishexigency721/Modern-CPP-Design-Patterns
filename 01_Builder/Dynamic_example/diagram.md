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
    style A fill:none,stroke:none
    style B fill:none,stroke:none
    text1(Inheritance / public)
    style text1 fill:none,stroke:none
```

```mermaid
graph LR
    C[Class A] *-- D[Class B]
    style C fill:none,stroke:none
    style D fill:none,stroke:none
    text2(Composition / unique_ptr ownership)
    style text2 fill:none,stroke:none
```

```mermaid
graph LR
    E[Class A] o-- F[Class B]
    style E fill:none,stroke:none
    style F fill:none,stroke:none
    text3(Aggregation / Pre-build data)
    style text3 fill:none,stroke:none
```

```mermaid
graph LR
    G[Class A] ..> H[Class B]
    style G fill:none,stroke:none
    style H fill:none,stroke:none
    text4(Dependency / creates instance)
    style text4 fill:none,stroke:none
```
