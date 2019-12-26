                                                                                                                                       // PoVRay 3.7 Scene File "Car_01_demo.pov"
// author: Friedrich A. Lohmueller, Nov-2006/Aug-2009/Jan-2011
// email: Friedrich.Lohmueller_at_t-online.de
// homepage: http://www.f-lohmueller.de
//--------------------------------------------------------------------------
#version 3.6; // 3.7;
global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 
//--------------------------------------------------------------------------
#include "colors.inc"
#include "textures.inc"
#include "glass.inc"
#include "metals.inc"
#include "golds.inc"
#include "stones.inc"
#include "woods.inc"
#include "shapes.inc"
#include "shapes2.inc"
#include "functions.inc"
#include "math.inc"
#include "transforms.inc"
//--------------------------------------------------------------------------
// camera ------------------------------------------------------------------
#declare Camera_0 = camera {/*ultra_wide_angle*/ angle 75      // front view
                            location  <0.0 , 1.0 ,-7.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 1.0 , 0.0>}
#declare Camera_1 = camera {/*ultra_wide_angle*/ angle 25   // diagonal view
                            location   < 5.00, 4.50,-12.00>
                            right     x*image_width/image_height
                            look_at   <-2.3, 0.750-0.0, 1.60>}
#declare Camera_2 = camera {/*ultra_wide_angle*/ angle 90 // right side view
                            location  <8.0 , 1.0 , 0.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 1.0 , 0.0>}
#declare Camera_3 = camera {/*ultra_wide_angle*/ angle 90        // top view
                            location  <0.0 , 15.0 ,-0.001>
                            right     x*image_width/image_height
                            look_at   <0.0 , 1.0 , 0.0>}
camera{Camera_1}
// sun ---------------------------------------------------------------------
light_source{< 2500,2500,-2500> color White}

// sky -------------------------------------------------------------- 
plane{<0,1,0>,1 hollow  
       texture{ pigment{ bozo turbulence 0.92
                         color_map { [0.00 rgb <0.20, 0.20, 1.0>*0.9]
                                     [0.50 rgb <0.20, 0.20, 1.0>*0.9]
                                     [0.70 rgb <1,1,1>]
                                     [0.85 rgb <0.25,0.25,0.25>]
                                     [1.0 rgb <0.5,0.5,0.5>]}
                        scale<1,1,2.5>*2.5  translate< 0,0,5>
                       }
                finish {ambient 1 diffuse 0} }      
       scale 10000}
// fog on the ground -------------------------------------------------
fog { fog_type   2
      distance   150
      color      White  
      fog_offset 0.1
      fog_alt    2.0
      turbulence 1.8
    }

// ground ------------------------------------------------------------
plane { <0,1,0>, 0 
        texture{ pigment{ color rgb<0.35,0.65,0.0>*0.72 }
	         normal { bumps 0.75 scale 0.015 }
                 finish { phong 0.1 }
               } // end of texture
      } // end of plane
//--------------------------------------------------------------------------
//---------------------------- objects in scene ----------------------------
//--------------------------------------------------------------------------

//-------------------------------------------------------------------------------------// 
//-------------------------------------------------------------------------------------// 
#declare Car_Body_Texture = 
         texture{ pigment{ color rgb<1,1,1>*1.2}
                //normal { radial sine_wave frequency 30 scale 0.25 }
                  finish { phong 1}
                 }
#declare Car_Top_Texture = 
         texture { pigment{ color rgb< 1, 0.95, 0.95>*1.1  } // very light red  
                // normal { bumps 0.5 scale 0.05 }
                   finish { diffuse 0.9 phong 1 reflection 0.00}
                 } // end of texture 
#declare Car_Seat_Texture = 
          texture { pigment{ color rgb< 1, 0.90, 0.85>*1.2  }// very light brown  
                   normal { bumps 0.15 scale 0.05 }
                   finish { phong 1 reflection 0.00}
                 } // end of texture 
#declare Car_Inside_Texture=
          texture { pigment{ color rgb< 1, 0.87, 0.75>  }// very light brown  
                // normal { bumps 0.5 scale 0.05 }
                   finish { phong 1 reflection 0.00}
                 } // end of texture 

#declare Wheel_Rubber_Texture = 
         texture { pigment{ color rgb< 1, 1, 1>*0.15 } //  color Gray25
                   normal { bumps 0.5 scale 0.008 }
                   finish { phong 0.2 reflection 0.00}
                 } // end of texture 
#declare Wheel_Metal_Texture = 
         texture { Chrome_Metal
                   // pigment{ color rgb<1,0,0>} 
                    normal { bumps 0.5 scale 0.005 } 
                    finish { phong 1}
                 } // end of texture 
#declare Bumper_Metal_Texture = 
         texture { Polished_Chrome
                   // pigment{ color rgb<1,0,0>} 
                   finish {   phong 1}
                 } // end of texture 
#declare Chassis_Inside_Texture = 
         texture { pigment{ color rgb< 1, 1, 1>*0.45 } //  color Gray55
                // normal { bumps 0.5 scale 0.05 }
                   finish { phong 1 reflection 0.00}
                 } // end of texture 
//---------------------------------------------------------------------------------------
#include "Car_01.inc" 
//-------------------------------------------------------------------------------------// 
object{ Car_01( 30, //Front_Wheel_Angle, // 
                1, // Coupe_ON:  0= off(hard top); 1= coup¨¦

                Car_Body_Texture,      //
                Car_Top_Texture,       //
                Car_Seat_Texture,      //
                Car_Inside_Texture,    //
                Wheel_Rubber_Texture,  //
                Wheel_Metal_Texture,   //
                Bumper_Metal_Texture,  //
                Chassis_Inside_Texture //
              ) //-------------------------------------------------- 

        scale<1,1,1>
        rotate<0,-0,0>
        translate<0,0,0>} 
//-------------------------------------------------------------------------------------// 
//-------------------------------------------------------------------------------------// 
#declare Car_Body_Texture = 
         texture{ pigment{ color rgb<1,0.8,0.9>*1.2}
                //normal { radial sine_wave frequency 30 scale 0.25 }
                  finish { phong 1}
                 }

#declare Car_Top_Texture = 
         texture { pigment{ color rgb< 1, 0.85, 0.95>*1.1  } // very light red  
                // normal { bumps 0.5 scale 0.05 }
                   finish { diffuse 0.9 phong 1 reflection 0.00}
                 } // end of texture 
//-------------------------------------------------------------------------------------// 
object{ Car_01( 30, //Front_Wheel_Angle, // 
                0, // Coupe_ON:  0= off(hard top); 1= coup¨¦

                Car_Body_Texture,      //
                Car_Top_Texture,       //
                Car_Seat_Texture,      //
                Car_Inside_Texture,    //
                Wheel_Rubber_Texture,  //
                Wheel_Metal_Texture,   //
                Bumper_Metal_Texture,  //
                Chassis_Inside_Texture //
              ) //-------------------------------------------------- 

        scale<1,1,1>
        rotate<0,-180,0>
        translate<-6,0,7>} 
//-------------------------------------------------------------------------------------// 











