# Named Constructors (Same Parameters)

```mermaid
classDiagram
   class Point {
      -float x_
      -float y_
      -Point(float, float)
      +rectangular(float, float)` Point
      +polar(float, float)` Point
      +print()
   }

   class Client {
      +main()
   }

   %% The static methods create and return a Point instance by value
   Point ..> "1" Point : creates
   Client ..> Point
```
