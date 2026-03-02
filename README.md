# MiniRT

## 🧠 Objective
This project is part of the 42 curriculum and aims to build a minimal ray tracer in C capable of rendering basic 3D scenes from a scene description file.  

It was developed using only the allowed standard C library and MiniLibX, focusing on mastering core graphics programming concepts, vector math, memory management, and file parsing.

## Features
- Parses a simple scene description file including camera, lights, and objects (spheres, planes, squares, cylinders)
- Implements basic ray tracing to render 3D scenes
- Calculates lighting with ambient, diffuse, and specular components
- Handles shadows and object intersections
- Dynamic memory management with no leaks (checked with valgrind)
- Uses MiniLibX for displaying the rendered image

Bonus/optional features:  
- Anti-aliasing
- Additional textures

---

## ⚙️ Compilation

Make targets:

```bash
make        # builds the executable
make clean  # removes object files
make fclean # removes object files and the executable
make re     # rebuilds everything from scratch
```

## 🚀 Usage

Basic example:

```bash
./miniRT scenes/[scene_file].rt
```

The rendered image will open in a MiniLibX window. You can interact using keyboard and mouse according to the project instructions.

> Example scene files can be found on directory scenes/work/[scene_file].rt

## 🧩 Challenges Faced

- Correctly parsing the scene file while validating input and handling errors
- Implementing vector math and intersection algorithms for multiple object types
- Managing memory safely while creating and destroying objects dynamically
- Calculating lighting correctly with shadows and reflections in a minimal renderer
- Working with MiniLibX to display images and handle events

## ✅ Key Learnings & Solutions

- Mastered vector operations (dot, cross, normalization) for ray tracing
- Implemented ray-object intersection algorithms for spheres, planes, squares and cylinders
- Built modular code structure separating parsing, ray tracing, and rendering logic
- Learned to debug floating-point errors and edge cases in 3D calculations
- Managed memory manually to avoid leaks and dangling pointers
- Improved understanding of basic computer graphics principles and lighting models

## 🔗 Related Projects

- Libft – foundational library used for string, memory, and utility functions
- get_next_line – low-level file reading logic applied to parse the scene file
- MiniLibX – graphics library for rendering and window management

> Note: This project was completed as part of a group effort, with collaboration on specular and diffuse light, light movement and test cases.
