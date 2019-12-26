  #include "colors.inc"
  camera {
    location <0, 1, -10>
    look_at 0
    angle 36
  }
  light_source { <500, 500, -1000> White }
  plane { y, -1.5
    pigment { checker Green White }
  }
  
  // sphere { <0, 0, 0>, 1
  //   pigment { Blue }
  //   translate -0.5*x
  // }
  // sphere { <0, 0, 0>, 1
  //   pigment { Red }
  //   translate 0.5*x
  // }   
  
  //  union{
  //   sphere { <0, 0, 0>, 1
  //     pigment { Blue }
  //     translate -0.5*x
  //   }
  //   sphere { <0, 0, 0>, 1
  //     pigment { Red }
  //     translate 0.5*x
  //   }
  // }

  // union{
  //   sphere { <0, 0, 0>, 1
  //     translate -0.5*x
  //   }
  //   sphere { <0, 0, 0>, 1
  //     translate 0.5*x
  //   }
  //   pigment { Red }
  //   scale <1, .25, 1>
  //   rotate <30, 0, 45>
  // }

  //   union {
  //   sphere { <0, 0, 0>, 1
  //     translate -0.5*x
  //   }
  //   sphere { <0, 0, 0>, 1
  //     translate 0.5*x
  //   }
  //   pigment { Red }
  // }


  //   intersection{
  //   sphere { <0, 0, 0>, 1
  //     translate -0.5*x
  //   }
  //   sphere { <0, 0, 0>, 1
  //     translate 0.5*x
  //   }
  //   pigment { Red }
  //   rotate 90*y
  // }

  //  difference {
  //   intersection {
  //     sphere { <0, 0, 0>, 1
  //       translate -0.5*x
  //     }
  //     sphere { <0, 0, 0>, 1
  //       translate 0.5*x
  //     }
  //     pigment { Red }
  //     rotate 90*y
  //   }
  //   cylinder { <0, 0, -1> <0, 0, 1>, .35
  //     pigment { Blue }
  //   }
  // }

  #declare Lens_With_Hole = difference {
    intersection {
      sphere { <0, 0, 0>, 1
        translate -0.5*x
      }
      sphere { <0, 0, 0>, 1
        translate 0.5*x
      }
      rotate 90*y
    }
    cylinder { <0, 0, -1> <0, 0, 1>, .35 }
  }

  // union {
  //   object { Lens_With_Hole translate <-.65, .65, 0> }
  //   object { Lens_With_Hole translate <.65, .65, 0> }
  //   object { Lens_With_Hole translate <-.65, -.65, 0> }
  //   object { Lens_With_Hole translate <.65, -.65, 0> }
  //   pigment { Red }
  // }

  // union {
  //   object { Lens_With_Hole translate <-.65, .65, 0> }
  //   object { Lens_With_Hole translate <.65, .65, 0> }
  //   object { Lens_With_Hole translate <-.65, -.65, 0> }
  //   object { Lens_With_Hole translate <.65, -.65, 0> }
  //   pigment { Red filter .5 }
  // }

  //   merge {
  //   object { Lens_With_Hole translate <-.65, .65, 0> }
  //   object { Lens_With_Hole translate <.65, .65, 0> }
  //   object { Lens_With_Hole translate <-.65, -.65, 0> }
  //   object { Lens_With_Hole translate <.65, -.65, 0> }
  //   pigment { Red filter .5 }
  // }

  difference {
    box { -1, 1 pigment { Red } }
    cylinder { -z, z, 0.5 pigment { Green } }
  }