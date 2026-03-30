/**
 * ============================================================================
 * File: Command.cpp (Modern Variant Version)
 * 
 * --- DESIGN OVERVIEW:
 * This program demonstrates a non-intrusive Command pattern using std::variant.
 * Commands are represented as simple data structures, and their execution
 * is dispatched via std::visit.
 * 
 * --- ADVANTAGES:
 * 1. No inheritance required for commands.
 * 2. Commands are stored by value in the queue (no pointers/new/delete).
 * 3. The execution logic is centralized in the 'CommandExecutor' visitor.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <utility>

//--------------------------------------------------------- Receivers:
class Cow
{
public:
   void moo() const { std::cout << " [Receiver] Cow says moo!\n"; }
};

class Dog
{
private:
   std::string name_;
public:
   explicit Dog(std::string name) : name_{std::move(name)} { }
   void bark() const { std::cout << " [Receiver] " << name_ << " barks!\n"; }
};

class Car
{
public:
   void turnOn()  const { std::cout << " [Receiver] Car engine ON.\n"; }
   void turnOff() const { std::cout << " [Receiver] Car engine OFF.\n"; }
   void rev()     const { std::cout << " [Receiver] Car: Vroom, vroom!\n"; }
};

//--------------------------------------------------------- Command Data:
// Commands are now just simple structs (Data markers)
struct CowAction { };
struct DogAction { };
struct CarAction { };

using Command = std::variant<CowAction, DogAction, CarAction>;

//--------------------------------------------------------- Command Executor:
// This is the "Visitor" that knows how to execute each command data type.
struct CommandExecutor
{
   Cow& cow;
   Dog& dog;
   Car& car;

   void operator()(const CowAction&) const { cow.moo(); }
   void operator()(const DogAction&) const { dog.bark(); }
   void operator()(const CarAction&) const
   {
      car.turnOn();
      car.rev();
      car.turnOff();
   }
};

//--------------------------------------------------------- Main Simulation:
int main()
{
   std::cout << "=== COMMAND PATTERN (MODERN VARIANT) ===\n" << std::endl;

   // 1. Create Receivers
   Cow cow;
   Dog dog{"Marshall"};
   Car car;

   // 2. Create a Queue of commands (Stored by value!)
   std::vector<Command> queue;
   queue.emplace_back(CowAction{});
   queue.emplace_back(DogAction{});
   queue.emplace_back(CarAction{});
   queue.emplace_back(DogAction{});

   // 3. Setup the Executor (Visitor)
   CommandExecutor executor{cow, dog, car};

   // 4. Dispatch and Execute
   std::cout << "Executing command queue via std::visit:\n";
   for (const auto& cmd : queue)
      std::visit(executor, cmd);

   std::cout << "\n=== SIMULATION COMPLETED ===" << std::endl;
}

//================================================================================ END
