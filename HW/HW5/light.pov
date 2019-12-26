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
  torus {
    1.5, 0.5
    texture { Brown_Agate }
    rotate <90, 160, 0>
    translate <-1, 1, 3>
  }
  box {
    <-1, -1, -1>, <1, 1, 1>
    texture { DMFLightOak }
    translate <2, 0, 2.3>
  }
  cone {
    <0,1,0>, 0, <0,0,0>, 1
    texture { PinkAlabaster }
    scale <1, 3, 1>
    translate <-2, -1, -1>
  }
  sphere {
    <0,0,0>,1
    texture { Sapphire_Agate }
    translate <1.5, 0, -2>
  }
// light_source {
//     <0, 10, -3>
//     color White
//     cylinder
//     radius 15
//     falloff 18
//     tightness 10
//     point_at <0, 0, 0>
//   }              
//    light_source {
//     <10, 10, -1>
//     color Red
//     cylinder
//     radius 12
//     falloff 14
//     tightness 10
//     point_at <2, 0, 0>
//   }
//   light_source {
//     <-12, 10, -1>
//     color Blue
//     cylinder
//     radius 20
//     falloff 30
//     tightness 10
//     point_at <-2, 0, 0>
//   }

  // light_source {
  //   <2, 10, -3>
  //   color White
  //   area_light <5, 0, 0>, <0, 0, 5>, 5, 5
  //   adaptive 1
  //   jitter
  // }

  //  light_source {
  //   <2, 10, -3>
  //   color White
  //   spotlight
  //   radius 15
  //   falloff 18
  //   tightness 10
  //   area_light <1, 0, 0>, <0, 0, 1>, 2, 2
  //   adaptive 1
  //   jitter
  //   point_at <0, 0, 0>
  // }
  // light_source {
  //   <10, 10, -1>
  //   color Red
  //   spotlight
  //   radius 12
  //   falloff 14
  //   tightness 10
  //   area_light <1, 0, 0>, <0, 0, 1>, 2, 2
  //   adaptive 1
  //   jitter
  //   point_at <2, 0, 0>
  // }
  // light_source {
  //   <-12, 10, -1>
  //   color Blue
  //   spotlight
  //   radius 12
  //   falloff 14
  //   tightness 10
  //   area_light <1, 0, 0>, <0, 0, 1>, 2, 2
  //   adaptive 1
  //   jitter
  //   point_at <-2, 0, 0>
  // }     
  // global_settings { ambient_light rgb<1, 0, 0> }
    /*
    light_source {
    <0, 20, 0>
    color Gray50
    shadowless
  }   */