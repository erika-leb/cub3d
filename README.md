# Cub3D

A small 3D raycasting engine inspired by early FPS games like Wolfenstein 3D, developed as part of the 42 curriculum.  
The goal is to render a 3D-like environment from a 2D map using raycasting techniques.

---

## 🚀 Features

- First-person 3D view using raycasting
- Textured walls depending on orientation (North, South, East, West)
- 2D map parsing from configuration file
- Player movement (WASD + rotation)
- Collision detection with walls
- Smooth rendering loop
- MiniLibX-based graphics rendering

---

## 🧠 What I learned

This project focuses on graphics, geometry, and real-time rendering:

- Raycasting algorithm (casting rays per screen column)
- Trigonometry for angle-based projection
- Camera plane and field of view concepts
- 2D to 3D projection techniques
- Texture mapping on walls
- Event-driven programming (keyboard input handling)
- Game loop architecture and frame rendering

---

## ⚙️ Architecture

The rendering pipeline works as follows:

1. **Map parsing**
   - Load and validate the `.cub` configuration file
   - Build a 2D grid map representation

2. **Raycasting loop**
   - For each vertical screen stripe:
     - Cast a ray from player position
     - Detect wall collision using DDA algorithm
     - Compute distance to wall
     - Calculate wall slice height

3. **Rendering**
   - Draw ceiling and floor
   - Apply wall textures based on hit direction
   - Render final frame using MiniLibX

---

## 🛠️ Tech stack

- Language: C  
- Graphics: MiniLibX  
- Math: trigonometry, linear projections  
- Environment: Linux  

---

## ▶️ Usage

make

./cub3D maps/example.cub
