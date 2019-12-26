 #include "colors.inc"
  #include "textures.inc"
               
   camera {
    location  <-4, 3, -9>
    look_at   <0, 0, 0>
    angle 48
  }
  plane {
    y, -1
    texture {
      pigment {
        checker
        color rgb<0.5, 0, 0>
        color rgb<0, 0.5, 0.5>
      }
      finish {
        diffuse 0.4
        ambient 0.2
        phong 1
        phong_size 100
        reflection 0.25
      }
    }
  }


#declare Lightbulb = union {
    merge {
      sphere { <0,0,0>,1 }
      cylinder {
        <0,0,1>, <0,0,0>, 1
        scale <0.35, 0.35, 1.0>
        translate  0.5*z
      }
      texture {
        pigment {color rgb <1, 1, 1>}
        finish {ambient .8 diffuse .6}
      }
    }
    cylinder {
      <0,0,1>, <0,0,0>, 1
      scale <0.4, 0.4, 0.5>
      texture { Brass_Texture }
      translate  1.5*z
    }
    rotate -90*x
    scale .5
  }                     
  
  // light_source {
  //   <0, 2, 0>
  //   color White
  //   looks_like { Lightbulb }
  // }
    
  // light_source {
  //   <0, 2, 0>
  //   color White
  //   area_light <1, 0, 0>, <0, 1, 0>, 2, 2
  //   adaptive 1
  //   jitter
  //   looks_like { Lightbulb }
  // }
  
  light_source {
    <0, 20, 0>
    color Gray75
    fade_distance 5
    fade_power 1
    shadowless
  }