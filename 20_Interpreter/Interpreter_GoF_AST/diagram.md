# Interpreter Pattern (GoF AST Version)

```mermaid
classDiagram
   class IExpression {
      <<interface>>
      +evaluate()* double
      +print(int)*
   }

   class NumberNode {
      -double value_
      +evaluate() double
      +print(int)
   }

   class UnaryMinusNode {
      -ExprPtr expr_
      +evaluate() double
      +print(int)
   }

   class MathFunctionNode {
      -string func_
      -ExprPtr expr_
      +evaluate() double
      +print(int)
   }

   class BinaryExpression {
      <<abstract>>
      #ExprPtr left_
      #ExprPtr right_
   }

   class AddNode {
      +evaluate() double
      +print(int)
   }

   class MulNode {
      +evaluate() double
      +print(int)
   }

   class Parser {
      -Lexer lexer_
      +parse() ExprPtr
   }

   class Client {
      +main()
   }

   %% Inheritance
   Expression <|.. NumberNode
   Expression <|.. UnaryMinusNode
   Expression <|.. MathFunctionNode
   Expression <|.. BinaryExpression
   BinaryExpression <|-- AddNode
   BinaryExpression <|-- MulNode

   %% Composition
   BinaryExpression *-- "n" Expression : left_ / right_
   UnaryMinusNode *-- Expression : expr_
   MathFunctionNode *-- Expression : expr_
   Parser *-- Lexer : lexer_

   %% Dependency
   Parser ..> Expression : creates AST
   Client ..> Parser
   Client ..> Expression : calls evaluate()
```

### Design Note:
In the GoF AST version, the architecture is hierarchical and recursive. The 
'Parser' performs a recursive descent to translate the input string into a 
tree of polymorphic objects (nodes) in memory. Unlike the Stack Machine, there 
is no bytecode or Virtual Machine; evaluation is a decentralized process 
triggered by calling 'evaluate()' on the root node, which recursively 
calculates the result by traversing its children. This design prioritizes 
structural clarity and extensibility over raw execution speed.
