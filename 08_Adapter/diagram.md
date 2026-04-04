# Adapter Pattern

```mermaid
classDiagram
   class LegacyRectangle {
      +oldDraw(x, y, w, h)
   }

   class ModernRectangle {
      <<interface>>
      +draw(x1, y1, x2, y2)*
   }

   class RectangleAdapter {
      -legacyInstance_ LegacyRectangle
      +draw(x1, y1, x2, y2)
   }

   class Client {
      +render(ModernRectangle)
   }

   %% Inheritance (Is_a) - No numbers
   ModernRectangle <|-- RectangleAdapter

   %% Composition (Has_a) - Multiplicity "1" only at the end
   RectangleAdapter *-- "1" LegacyRectangle

   %% Dependency - No numbers
   Client ..> ModernRectangle
```
