# 🌌 **miniRT** 🌌  
_A stunning real-time raytracer built from scratch!_

![miniRT Render](https://via.placeholder.com/800x300)  
<small>*(Will add a GIF or image of our project rendering a scene here.)*</small>

---

## 🚀 **Getting Started**

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/miniRT.git
   cd miniRT
   ```

2. Build the project:
   ```bash
   make
   ```

3. Run the raytracer:
   ```bash
   ./miniRT <scene_name.rt>
   ```

   Replace `<scene_name.rt>` with the name of your `.rt` scene file. Explore pre-made scenes or create your own for limitless creativity!

---

## ✨ **Features**

### 🖼️ **Ray Tracing**
- Handles intersections with multiple shapes:
  - **Spheres**, **planes**, **cylinders**, **cones**, and **cubes**.
- Full support for:
  - Ambient, diffuse, and specular lighting.
  - Reflections/Refractions
  - Shadows and customizable **spotlights** with dynamic light falloff.

### 🎥 **Interactive Camera**
- Real-time camera movement with smooth rotations and translations.
- **Quaternion-based rotation** system for precision.
- Deltatime integration for fluid motion.

### 🎨 **Textures and Bump Mapping**
- Bump mapping for intricate surface detail using normal maps.
- Support for **XPM textures** to bring your scenes to life.
- TODO:
  - Universal UV mapping for spheres, cones, and cylinders.
  - Support for image textures (not jump normal maps).

### 💡 **Spotlights**
- Customizable cone angles based on the spotlight's spot angle for realistic light falloff.

---

## 🏎️ **Performance Optimizations**
- **Multithreading**: Efficient thread distribution for high-speed rendering.
- **Bounding Volume Hierarchies (BVH)**: Accelerates intersection tests for complex scenes.
- **SIMD Linear Algebra Library**:
  - Optimized 4x4 matrix operations for raytracing.
  - Features the `lag_mat4s_get_transform_inverse()` function for lightning-fast decomposed matrix inversions.
  - _Innovative yet highly efficient mathematical design_.

### 🔍 **Benchmarks**
- **Simple scenes**: ~(12-36)ms per frame.
- **Complex scenes with multiple normal map textures**: Under 200ms per frame.

<small>*Benchmarked on typical scenes including multiple objects and light sources.*</small>

---

## 🔧 **Technical Details**
- **Rotations**:
  - Quaternion extraction for seamless orientation.
  - Axis rotation using **Rodrigues' formula**.
- **Custom Parsing**:
  - Read `.rt` scene files to define objects, lights, and camera configurations.
  - TODO:
    - Save scenes in the same configuration after the user modified them in real-time.
- **Thread Pool**:
  - Reuses threads for every frame to minimize initialization overhead.
- **Math Library: LagAMat**
  - Used efficient memory manipulations and mathematical tricks, made available by the use of unions.
  - Broke down matrices into scale and translation vectors, and rotational component, to cut the cost of calculating a general matrix inverse as it's not needed.

---

## 🎯 **What Makes our miniRT Unique?**
- Advanced yet approachable real-time rendering capabilities.
- A dedicated linear algebra library optimized for simplicity and performance.
- Innovative, efficient mathematical solutions built exclusively for this project.
- A perfect blend of creativity and technical rigor to make ray tracing interactive.
- We're still working on making it better!

---

## 🌍 **Create Your World**
Write your own `.rt` scene files to populate your world with:
- Custom shapes, textures, and bump maps.
- Dynamic lighting and shadows.

Example `.rt` file:
```plaintext
C 0,0,-10 0,1,0 90
sp 0,0,0 1.0 255,0,0
L 5,10,-5 1.0 255,255,255
```

---

## 🖼️ **Gallery**
<small>*Will add sample images or GIFs of scenes rendered by miniRT here.*</small>  
![Sample Scene](https://via.placeholder.com/800x300)  
![Interactive Render](https://via.placeholder.com/800x300)

---

## 📜 **Acknowledgments**
This project is part of the **42 School** curriculum, blending mathematical elegance and computational performance to bring scenes to life.  

--- 

## 🛠️ **How to Contribute**
1. Fork the repo.
2. Create a feature branch: \```git checkout -b my-feature\```.
3. Commit your changes: \```git commit -m 'Add cool feature'\```.
4. Push to the branch: \```git push origin my-feature\```.
5. Open a Pull Request!

--- 

### 💻 Made with ❤️ for ray tracing enthusiasts everywhere.

