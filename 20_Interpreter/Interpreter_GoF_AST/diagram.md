# Interpreter Pattern (Abstract Syntax Tree (AST) Machine Version)

```mermaid
classDiagram
    class OpCode {
        <<enumeration>>
    }

    class Instruction {
        <<struct>>
        +OpCode code
        +double value
    }

    class Lexer {
        -string input_
        -size_t pos_
        +nextToken()
        +getToken() Token
    }

    class Compiler {
        -Lexer lexer_
        -vector~Instruction~ program_
        +compile() vector~Instruction~
    }

    class VirtualMachine {
        +evaluate(vector~Instruction~) double
        +printProgram(vector~Instruction~)
    }

    class Client {
        +main()
    }

    %% Relationships using your symbology reference:

    Compiler *-- Lexer
    Compiler *-- "n" Instruction
    
    VirtualMachine ..> Instruction
    
    Client ..> Compiler
    Client ..> VirtualMachine
```

### Design Note:
In the GoF AST version, the architecture is hierarchical and recursive. The 
'Parser' performs a recursive descent to translate the input string into a 
tree of polymorphic objects (nodes) in memory. Unlike the Stack Machine, there 
is no bytecode or Virtual Machine; evaluation is a decentralized process 
triggered by calling 'evaluate()' on the root node, which recursively 
calculates the result by traversing its children. This design prioritizes 
structural clarity and extensibility over raw execution speed.
