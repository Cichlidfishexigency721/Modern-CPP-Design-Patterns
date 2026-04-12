# Builder Pattern (Dynamic)

```mermaid
classDiagram
   class Client { +main() }

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
      -unique_ptr~Engine~ engine_
      -vector~unique_ptr~Wheel~~ wheels_
      +print()
   }

   class Builder {
      -float weight_
      -float width_
      -int doorCount_
      -string color_
      -int power_
      -int wheelCount_
      -buildWheels() : Wheels_vector
      +setWeight(float) Builder&
      +setWidth(float) Builder&
      +setDoorCount(float) Builder&
      +setColor(float) Builder&
      +setPower(float) Builder&
      +setWheelCount(float) Builder&
      +build() unique_ptr~Car~
   }

   Wheel <|.. StandardWheel
   Wheel <|.. HeavyDutyWheel
   
   %% Relations
   Car *-- Engine
   Car *-- "n" Wheel
   
   Builder o-- Engine
   Builder o-- "n" Wheel
   
   Builder ..> Car
   note for Builder "Builder is nested inside Car"

   Client --> Car
```
