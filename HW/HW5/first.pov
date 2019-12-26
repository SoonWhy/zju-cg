#include "colors.inc"
#include "stones.inc"

// coordinate is similar with openGL
// location: up 2, back 3
// lookat: center of image, up 1, forward 2, related with origin
camera {
    location <0, 2, -3>
    look_at  <0, 1,  2>
}

// center related with origin, radius=2
// texture : color, numpiness, finish properties
// color: full illuminated ,for ray-tracing modified it, so just the color of object
//          has but not looks like: pigment
     
//   sphere {
//     <0, 1, 2>, 2
//     texture {
//       pigment { color Yellow }
//     }
//   }


light_source { <2, 4, -3> color White}


// cube
//   box {
//     <-1, 0,   -1>,  // Near lower left corner
//     < 1, 0.5,  3>   // Far upper right corner
//     texture {
//       T_Stone25     // Pre-defined from stones.inc
//       scale 4       // Scale by the same amount in all
//                     // directions
//     }
//     rotate y*90     // Equivalent to "rotate <0,20,0>", param is angle
//   }


   cone {
    <0, 1, 0>, 0.3    // Center and radius of one end
    <1, 2, 3>, 1.0    // Center and radius of other end
    texture { T_Stone25 scale 4 }
  }

// <>, normal of plane , <0,1,0> == symbol y
// -1, move -1 unit
    plane { <0, 1, 0>, -1
    pigment {
      checker color Red, color Blue
    }
  }