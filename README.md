# Toy Box  

**Toy Box** is a work-in-progress game engine that reflects over 15 years of engine/systems code I have developed on and off. This project is an effort to refactor and formalize that work into something that is useful to me and for others to enjoy.

## **Purpose**  
Toy Box is not intended to be a generic, commercial-grade engine. Instead, it is designed specifically for creating imaginative, quirky games that emphasize creativity and exploration. It focuses on empowering developers to craft unique, expressive worlds with simplicity and efficiency.

## **Core Philosophy**  
- **Experimental Creativity:** Toy Box is designed to enable experimentation, where gameplay and solutions emerge from tinkering and playing with its tools, much like how a box full of toys inspires unexpected and imaginative outcomes.
- **Selective Refinement:** Critical systems are carefully developed in pure C for performance and control, with higher-level systems adopting a "C with templates" philosophy for C++.  
- **Modular Design:** Key systems are decoupled into standalone projects for reusability and clarity.

## **Key Features**  
- **Custom ECS Framework:** Powered by the unique concepts of **Toy** (entity), **Part** (component), and **Work** (system) for flexible entity and component management.  
- **EmberScript Scripting:** A lightweight scripting language built for embedding and runtime flexibility ([EmberScript](https://github.com/simondevenish/EmberScript)).  
- **Physics with Phyzzy:** A physics library for imaginative games, turning physics into a creative toolkit for vibrant, unexpected, and personality-filled worlds ([Phyzzy](https://github.com/simondevenish/Phyzzy)).  
- **AllocX Memory Management:** A high-performance custom memory management library, is integrated to optimize allocation ([AllocX](https://github.com/simondevenish/AllocX)).  
- **Rendering with Aether:** A purpose-built renderer focused on delivering dream-like, soft visuals.  

## **Core Design Principles**  
1. **Imaginative Creativity:** Every aspect of the engine is tailored to empower developers to build expressive, quirky worlds.  
2. **Performance-Critical Systems:** Math, physics, and memory allocation are built in pure C to maximize speed and efficiency.  
3. **Minimal Abstraction:** Higher-level systems adopt a lightweight C++ approach, with templates where necessary but avoiding unnecessary class hierarchies.  

## **Standalone Projects**  
Several core systems of Toy Box have been refactored into standalone repositories for broader usability:  
- **[EmberScript](https://github.com/simondevenish/EmberScript):** A lightweight, embeddable scripting language.  
- **[Phyzzy](https://github.com/simondevenish/Phyzzy):** A C++ physics library for imaginative, personality-filled games.  
- **[AllocX](https://github.com/simondevenish/AllocX):** A memory management library for low-latency systems.

## **Third Party Projects**  
- **[The Forge](https://github.com/ConfettiFX/The-Forge):** A robust, cross-platform rendering framework.

## **Status**  
Toy Box is under active development and is not yet production-ready. Contributions and discussions are welcome to help shape its future!  
