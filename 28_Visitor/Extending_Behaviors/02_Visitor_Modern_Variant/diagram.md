# Visitor Pattern (Modern Variant - Extending Behaviors)

```mermaid
classDiagram
   class Paragraph {
      +string text_
   }

   class Image {
      +string url_
   }

   class Hyperlink {
      +string url_
      +string label_
   }

   class DocumentElement {
      <<variant>>
   }

   class HtmlExporter {
      +visit(Paragraph)
      +visit(Image)
      +visit(Hyperlink)
   }

   class TextExtractor {
      +visit(Paragraph)
      +visit(Image)
      +visit(Hyperlink)
   }

   class Client {
      +main()
   }

   %% Relationships
   DocumentElement ..> Paragraph
   DocumentElement ..> Image
   DocumentElement ..> Hyperlink

   HtmlExporter ..> Paragraph
   HtmlExporter ..> Image
   HtmlExporter ..> Hyperlink

   TextExtractor ..> Paragraph
   TextExtractor ..> Image
   TextExtractor ..> Hyperlink

   Client *-- "n" DocumentElement : collection

   Client ..> HtmlExporter : via std::visit
   Client ..> TextExtractor : via std::visit
```

### Design Note:
In this modern C++ version, the Visitor pattern is completely non-intrusive. The
element classes (Paragraph, Image, Hyperlink) do not need to inherit from a base
class or implement an 'accept' method; they are treated as pure data. The
'DocumentElement' is a type-safe union (std::variant) that can hold any of these
types. New operations like 'HtmlExporter' or 'TextExtractor' are implemented as
separate functors. The 'Client' processes the entire document using
'std::visit', which guarantees that all types in the variant are handled,
providing compile-time safety and high performance.
