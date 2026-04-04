classDiagram
    class Car {
        -float weight_
        -float width_
        -int doorCount_
        -string color_
        -Type type_
        -unique_ptr~Engine~ engine_
        -vector~unique_ptr~Wheel~~ wheels_
        -Car(...)
        +print()
    }

    class Builder {
        -float weight_
        -float width_
        -int doorCount_
        -string color_
        -int power_
        -int wheelCount_
        +setWeight(float) Builder&
        +setWidth(float) Builder&
        +setDoorCount(int) Builder&
        +setColor(string) Builder&
        +build() unique_ptr~Car~
    }

    class Engine {
        -int power_
    }

    <<interface>> Wheel
    class StandardWheel
    class HeavyDutyWheel

    Car *-- Engine : contiene
    Car *-- Wheel : contiene 4..n
    Wheel <|-- StandardWheel
    Wheel <|-- HeavyDutyWheel
    
    %% Relación de clase anidada y amistad
    Car +-- Builder : Nesting
    Builder ..> Car : <<create>>
