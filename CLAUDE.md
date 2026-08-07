# AoS (Asteroids on Steroids)

AoS is a game that takes the classical Asteroids game and applies gravity to it for a new dynamic twist in gameplay. 

## Notes
For now don't make any changes to this file Claude. I'll make updates to it directly for you or unless I explicitly tell you to make updates to it. 

### Libraries
The game currently uses the following old libraries.

  1. Generic Math Template Library [gmtl](https://github.com/imvu/gmtl/)
  2. LibSDL 2
  3. The README lists out other libraries that I beleive are needed by LibSDL2
  4. freeglut - this was original used to display the score. This has been removed in favor of manual drawing.

#### GMTL Migration Notes

**Package:** `glm-devel` (Fedora, header-only, no build step) replaces
gmtl's scons-from-source install.

#### Type replacements
- `gmtl::Vec2d` → `glm::dvec2`
- `gmtl::Matrix22d` → `glm::dmat2`

#### Function/API replacements
- `gmtl::dot(a, b)` → `glm::dot(a, b)`
- `Vec2d::set(ptr)` (wraps raw `double*`) → `glm::make_vec2(ptr)`
  (needs `#include <glm/gtc/type_ptr.hpp>`)
- `a - b`, `a + b`, `a[i]` on vectors → unchanged, GLM overloads these the same way
- `using namespace gmtl;` → `using namespace glm;` (Collidable.cpp:14)

#### ⚠️ Rotation matrix gotcha (Object.cpp:155-161)
gmtl is row-major, GLM is column-major for `operator[]`. The hand-built
rotation matrix:

```cpp
R[0][0] =  cos(theta);  R[0][1] = -sin(theta);
R[1][0] =  sin(theta);  R[1][1] =  cos(theta);
```

must NOT be ported with the same indices — that would silently transpose
(flip the direction of) every rotation. Replace with the column-major
constructor instead:
R = glm::dmat2(cos(theta), sin(theta), -sin(theta), cos(theta));
R * v (matrix-vector multiply, used at Object.cpp:185-186,229) behaves
the same either way once R is built correctly.

Includes to change

- \#include <gmtl/gmtl.h> → \#include <glm/glm.hpp>
- \#include <gmtl/VecOps.h> → (folded into glm/glm.hpp, drop)
- \#include <gmtl/MatrixOps.h> → (folded into glm/glm.hpp, drop)
- Add \#include <glm/gtc/type_ptr.hpp> wherever make_vec2 is used

### Building

Building the project currently makes use of `make` and `scone`. I'm using make for my local source files and scone to build GMTL.

## Goals

### Compilation and Run

The initial step is to get this project to build and run after almost twelve years of no activity. 

### Upgrade the Libaries

DONE: I would like to use the latest version of SDL (version 3 as of now) or this url as reference https://github.com/libsdl-org/SDL
TODO

## TODOs
- [ ] Right now all of my matrices are row major, they need to be column major.
