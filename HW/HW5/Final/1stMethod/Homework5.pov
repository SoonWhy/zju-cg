
// global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 

//---------------------------------------------------------------------- head file
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
#include "shapes.inc"     
// -------------------------------------------------------------------- head file end


// ------------------------------------------------------------------- SET camera
// diagonal view
camera { 
    angle 25   
    location   < 1.00, 2.50,-12.00>
    right     x*image_width/image_height
    look_at   <-2.3, 0.750-0.0, 1.60>
    }
// ------------------------------------------------------------------- SET camera ends


// ------------------------------------------------------------------- SET light
light_source{< 2500,2500,-2500> color White}
// ------------------------------------------------------------------- SET light ends


// ------------------------------------------------------------------- SET PARAM 
// correction param 
#declare Delta_modify=0.0001;

// Car body's param
#declare Car_length = 5.00;             // total length
#declare Car_Low = 0.25;                // base height
#declare Car_Tween = 1.00;              // tween height
#declare Car_Top = 1.60;                // top height
#declare Front_X = 0.70;                // length over front wheels 
#declare Body_H =Car_Top- Car_Low;  

// Place Wheel param
#declare Half = 0.90;                   // Halbe Spurweite
#declare Z_Over = 0.10;                 // Halbe Spurweite berhang
#declare Half_Brutto = Half + Z_Over; 
#declare Axis_Distance = 3.20;          // Achs-Abstand

// Wheel's param
#declare Wheel_Scale = 0.85; 
#declare Base_Wheel_R = 0.45; 
#declare Wheel_R = Wheel_Scale* Base_Wheel_R;
#declare Wheel_Rotate_Angle = 30; 

#declare Chassis_Base_R = 0.15; 

// ------------------------------------------------------------------- SET PARAM ends


// ------------------------------------------------------------------- DEFINE wheel
// #### define wheel texture
#declare Wheel_Rubber_Texture = 
    texture { 
        pigment{ 
                color rgb< 1, 1, 1>*0.15 
                } //  color Gray25
        normal { bumps 0.5 scale 0.008 }
        finish { phong 0.2 reflection 0.00}
    } 
#declare Wheel_Metal_Texture = 
    texture { 
            Chrome_Metal
        // pigment{ color rgb<1,0,0>} 
        normal { bumps 0.5 scale 0.005 } 
        finish { phong 1}
    } 

// %%%% define wheel object
#declare Single_Wheel_object = union{ 
    intersection{
        torus{ 
            0.35,0.15  
            rotate<90,0,0> 
            }
        cylinder{ 
            <0,0,-0.20>,
            <0,0,0.20>, 
            0.47
            }
        texture{
            Wheel_Rubber_Texture
            }
    }
    sphere{ 
        <0,0,0>,
        0.45 
        scale<1,1,0.25> 
        texture {
            Wheel_Metal_Texture
            }  
    } 
    translate<0,0.45,0>
    scale Wheel_Scale 
}

// %%%% define four wheel combination
#declare Four_Wheel_combination = union{
    object{ 
        Single_Wheel_object 
        rotate<0,Wheel_Rotate_Angle,0> 
        translate<0,0,-Half>
        } 
    object{ 
        Single_Wheel_object scale<1,1,-1> 
        rotate<0,Wheel_Rotate_Angle,0> 
        translate<0,0, Half>
        } 
    object{ 
        Single_Wheel_object 
        translate<-Axis_Distance,0,-Half+0.05>
        } 
    object{ 
        Single_Wheel_object 
        scale<1,1,-1> 
        translate<-Axis_Distance,0, Half-0.05>
        } 
}
// ------------------------------------------------------------------- DEFINE wheel ends




// ------------------------------------------------------------------- SET car texture
// #### define texture
#declare Car_Body_Texture = 
    texture { 
        pigment{ color rgb< 1.0, 0.0, 0.0> } //  color Red
        // normal { bumps 0.5 scale 0.05 }
        finish { diffuse 0.85  phong 1}
    } // end of texture 

#declare Chassis_Inside_Texture = 
    texture { 
        pigment{ color rgb< 1, 1, 1>*0.45 } //  color Gray55
        // normal { bumps 0.5 scale 0.05 }
        finish { phong 1 reflection 0.00}
    }
#declare Car_Inside_Texture=
    texture { 
        pigment{ color rgb< 1, 0.87, 0.75>  }// very light brown  
        // normal { bumps 0.5 scale 0.05 }
        finish { phong 1 reflection 0.00}
    }
#declare Car_Top_Texture = 
    texture { 
        pigment{ color rgb< 1.0, 0.15, 0.0> } //  red orange
        // normal { bumps 0.5 scale 0.05 }
        finish { phong 1 reflection 0.00}
    } 

// ------------------------------------------------------------------  SET car texture ends


// ------------------------------------------------------------------  DEFINE car tween part
#declare Tween_Car_With_Hole=union{
    // object{Four_Wheel_combination}
    difference{ 
        // car body
        object{ 
            Round_Box(
                <-Car_length+Front_X,Car_Low,-Half_Brutto>,
                <Front_X,Car_Tween,Half_Brutto>, 
                0.15, 
                0) 
            }
        // dig out four hole for wheels  by difference
        union{ 
            cylinder{ 
                <0,0,-Half_Brutto-Delta_modify>,
                <0,0,-Half_Brutto/2>,
                Wheel_R+0.12  
                translate<0,Wheel_R-0.05,0> 
            }        
            cylinder{ 
                <0,0, Half_Brutto/2>,
                <0,0, Half_Brutto+Delta_modify>,
                Wheel_R+0.12
                translate<0,Wheel_R-0.05,0> 
            }        
            cylinder{ 
                <0,0,-Half_Brutto-Delta_modify>,
                <0,0,-Half_Brutto/2>,
                Wheel_R+0.12
                scale<1,0.5,1>
                translate<-Axis_Distance,Wheel_R-0.05,0> 
            }
            cylinder{ 
                <0,0, Half_Brutto/2>,
                <0,0, Half_Brutto+Delta_modify>,
                Wheel_R+0.12
                scale<1,0.5,1>
                translate<-Axis_Distance,Wheel_R-0.05,0> 
            }
            texture{ 
                Chassis_Inside_Texture
            } 
        } 
        // // dig out space inside the car by difference
        intersection{
            // main inside space, a round cube
            // intersection by two parts, to ensure not include space of axle like a cylinder
            // front part
            object{ 
                Round_Box( 
                    <-Axis_Distance-0.5,0.01,-0.20>,
                    <-0.52,Body_H-0.03, 0.20>, 
                    Chassis_Base_R, 
                    0
                    )  
                scale<1,1,(Half_Brutto-0.05)*1/0.20+Delta_modify>*0.94
                matrix
                    <1, 0, 0, 
                    -0.55, 1, 0,
                    0, 0, 1,
                    0, 0, 0>
                translate<0.15,Car_Low+0.02,0.00> 
            }
            // back part
            object{ 
                Round_Box(
                <-Axis_Distance+1,0.01,-0.20>,
                <0.52,Body_H-0.03, 0.20>, 
                Chassis_Base_R, 
                0
                )  
                scale<1,1,(Half_Brutto-0.05)*1/0.20>*0.94
                matrix
                    <1, 0, 0, 
                    1.25, 1, 0,
                    0  , 0, 1,
                    0  , 0, 0>
                translate<-1.7,Car_Low+0.02+Delta_modify,0.00> 
            }
            // ensure the existence of space of axle
            // These two axle will not intersect with all inside space
            // which ensures space of axle will not belong to the car's inside space
            cylinder{ 
                <0,0,-Half_Brutto-Delta_modify>,
                <0,0, Half_Brutto+Delta_modify>,
                Wheel_R+0.14
                translate<0,Wheel_R-0.05,0> 
                inverse 
            }        
            cylinder{ 
                <0,0,-Half_Brutto-Delta_modify>,
                <0,0, Half_Brutto+Delta_modify>,
                Wheel_R+0.14
                translate<-Axis_Distance,Wheel_R-0.05,0>
                inverse 
            }        
            texture{ Car_Inside_Texture }        
        }
    }
}
// ------------------------------------------------------------------- DEFINE car tween ends



// ------------------------------------------------------------------- DEFINE car top
#declare Top_Car_With_hole=    
difference{ 
    intersection{
        // A clined round cube
        // the front and back glass is clined
        // this part is mainly for the back part
        object{ 
            Round_Box( //------------------------- upper front
                <-Axis_Distance-0.5,0,-0.20>,
                <-0.50,Body_H-0.05, 0.20>, 
                Chassis_Base_R+0.001, 
                0
            )  
            scale<1,1,(Half_Brutto-0.05)*1/0.20+Delta_modify>
            // make round cube be clined
            matrix
                <1  , 0, 0, //  matrix-shear_y_to_x
                -0.55, 1, 0,
                0  , 0, 1,
                0  , 0, 0>
            translate<0.15,Car_Low+0.02,0.00>
        }
        // this part is mainly for the front part
        // so the clined angle is bigger than former one
        object{ 
            Round_Box( //------------------------- upper back
                <-Axis_Distance+1,          0,-0.20>,
                <0.50,Body_H-0.05, 0.20>, Chassis_Base_R+0.001, 0
                )  
            scale<1,1,(Half_Brutto-0.05)*1/0.20>
                matrix
                <1  , 0, 0, //  matrix-shear_y_to_x
                1.25, 1, 0,
                0  , 0, 1,
                0  , 0, 0>
            translate<-1.8,Car_Low+0.02+Delta_modify,0.00>
        }
        // delete the space of axle(front)
        cylinder{ 
                <0,0,-Half_Brutto-Delta_modify>,
                <0,0, Half_Brutto+Delta_modify>,
                Wheel_R+0.13  
                translate<0,Wheel_R-0.05,0> inverse 
            }     
        // delete the space of axle(back)
        cylinder{ 
                <0,0,-Half_Brutto-Delta_modify>,
                <0,0, Half_Brutto+Delta_modify>,
                Wheel_R+0.13  
                translate<-Axis_Distance,Wheel_R-0.05,0> inverse 
            }        
        
        texture{ Car_Top_Texture }        
    } 
    // differ inside space of car
    intersection{
        object{ 
            Round_Box( //------------------------- upper front
                <-Axis_Distance-0.5,0,-0.20>,
                <-0.52,Body_H-0.05, 0.20>,
                Chassis_Base_R, 
                0
            )  
            scale<1,1,(Half_Brutto-0.05)*1/0.20+Delta_modify>*0.98
            matrix<1  , 0, 0, //  matrix-shear_y_to_x
           -0.55, 1, 0,
            0  , 0, 1,
            0  , 0, 0>
            translate<0.15,Car_Low+0.02,0.00>
            }
        object{ 
            Round_Box( //------------------------- upper back
                <-Axis_Distance+1,          0,-0.20>,
                <0.52,Body_H-0.05, 0.20>, Chassis_Base_R, 
                0
                )  
            scale<1,1,(Half_Brutto-0.05)*1/0.20>*0.98
            matrix<1  , 0, 0, //  matrix-shear_y_to_x
            1.25, 1, 0,
            0  , 0, 1,
            0  , 0, 0>
            translate<-1.8,Car_Low+0.02+Delta_modify,0.00> 
        }
        cylinder{ 
            <0,0,-Half_Brutto-Delta_modify>,
            <0,0, Half_Brutto+Delta_modify>,
            Wheel_R+0.14
            translate<0,Wheel_R-0.05,0> inverse 
        }        
        cylinder{ 
            <0,0,-Half_Brutto-Delta_modify>,
            <0,0, Half_Brutto+Delta_modify>,
            Wheel_R+0.14  
            translate<-Axis_Distance,Wheel_R-0.05,0> inverse 
        }        
        texture{ Car_Inside_Texture }         
    } 

// front side half window
    prism { -Half_Brutto-2*Delta_modify ,Half_Brutto+2*Delta_modify  , 5
       <-0.80, 0.00>,  // first point
       <-0.03, 0.00>, 
       <-0.26, 0.42>, 
       <-0.80, 0.42>, 
       <-0.80, 0.00>   // last point = first point!!!!
       rotate<-90,0,0> scale<1,1,-1> //turns prism in z direction! Don't change this line! 

       texture { pigment{ color White} 
                 finish { diffuse 0.9 phong 1.0}
               } // end of texture

        translate<-0.95,Car_Tween-0.04+Delta_modify,0>
    } 
// back side half window
    prism { -Half_Brutto-2*Delta_modify ,Half_Brutto+2*Delta_modify  , 6
       <-0.85, 0.00>,  // first point
       <-1.52, 0.00>, 
       <-1.52, 0.30>, 
       <-1.42, 0.42>, 
       <-0.85, 0.42>, 
       <-0.85, 0.00>   // last point = first point!!!!
       rotate<-90,0,0> scale<1,1,-1> //turns prism in z direction! Don't change this line! 

       texture { pigment{ color White} 
                 finish { diffuse 0.9 phong 1.0}
               } // end of texture

        translate<-0.95,Car_Tween-0.04+Delta_modify,0>
    } 
    
// front window
    object { 
        Round_Box(<-0.5,0,-Half_Brutto+0.10>,<0.5,0.47,Half_Brutto-0.10>, 0.05, 0)  
        scale<1,1,1>  
        rotate<0, 0,20> 
        translate<-0.85,Car_Tween-0.01+Delta_modify,0>
    }
// backside window 
    object {
        Round_Box(<-0.5,0.10,-Half_Brutto+0.20>,<0.5,0.45,Half_Brutto-0.20>, 0.10   , 0)  
        scale<1,1,1>  
    rotate<0, 0,-10> translate<-2.8,Car_Tween-0.04+Delta_modify,0>
    }


} // end top difference

// ------------------------------------------------------------------- DEFINE car top ends



// ------------------------------------------------------------------  DEFINE car glass
// still draw the car body, but give it different textures
#declare Car_Glass=


difference{ 
    intersection{
        object{ 
            Round_Box( 
                <-Axis_Distance-0.5,0,-0.20>,
                <-0.52,Body_H-0.05, 0.20>, 
                0.201, 
                1
            )  
            scale<1,1,(Half_Brutto-0.05)*1/0.20+Delta_modify>*0.98
            matrix<1  , 0, 0, //  matrix-shear_y_to_x
           -0.55, 1, 0,
            0  , 0, 1,
            0  , 0, 0>
            translate<0.15,Car_Low+0.02,0.00>
        }

        object{ 
            Round_Box(
            <-Axis_Distance+1,0,-0.201>,
            <0.52,Body_H-0.05, 0.201>, 
            0.201, 
            1)  
            scale<1,1,(Half_Brutto-0.05)*1/0.20>*0.98
            matrix<1  , 0, 0, //  matrix-shear_y_to_x
            1.25, 1, 0,
            0  , 0, 1,
            0  , 0, 0>
            translate<-1.8,Car_Low+0.02+Delta_modify,0.00>
        }

        cylinder{ 
            <0,0,-Half_Brutto-Delta_modify>,
            <0,0, Half_Brutto+Delta_modify>,
            Wheel_R+0.125  
            translate<0,Wheel_R-0.05,0> inverse 
        }        
        cylinder{ 
            <0,0,-Half_Brutto-Delta_modify>,
            <0,0, Half_Brutto+Delta_modify>,
            Wheel_R+0.125  
            translate<-Axis_Distance,Wheel_R-0.05,0> inverse 
        }        
    } 
    intersection{
        object{ 
            Round_Box( 
            <-Axis_Distance-0.5,0,-0.20>,
            <-0.565,Body_H-0.08, 0.20>, 
            Chassis_Base_R, 
            1
            )  
            scale<1,1,(Half_Brutto-0.05)*1/0.20+Delta_modify>*0.96
            matrix<1  , 0, 0, //  matrix-shear_y_to_x
           -0.55, 1, 0,
            0  , 0, 1,
            0  , 0, 0>
            translate<0.15,Car_Low+0.02,0.00>
        }
        object{ 
            Round_Box( 
                <-Axis_Distance+1,0,-0.20>,
                <0.52,Body_H-0.08, 0.20>, 
                Chassis_Base_R, 
                1
                )  
            scale<1,1,(Half_Brutto-0.05)*1/0.20>*0.96
            matrix<1  , 0, 0, //  matrix-shear_y_to_x
            1.25, 1, 0,
            0  , 0, 1,
            0  , 0, 0>
            translate<-1.8,Car_Low+0.02+Delta_modify,0.00>
        }
        cylinder{ 
            <0,0,-Half_Brutto-Delta_modify>,
            <0,0, Half_Brutto+Delta_modify>,
            Wheel_R+0.122  
            translate<0,Wheel_R-0.05,0> inverse 
        }        
        cylinder{ 
            <0,0,-Half_Brutto-Delta_modify>,
            <0,0, Half_Brutto+Delta_modify>,
            Wheel_R+0.122  
            translate<-Axis_Distance,Wheel_R-0.05,0> inverse 
        }        
    } 

    texture{ 
        pigment{ rgbf <0.98, 0.98, 0.98, 0.9>*0.9 }
        finish { 
            diffuse 0.1 
            reflection 0.2  
            specular 0.8 
            roughness 0.0003 
            phong 1 
            phong_size 400
        }
    }
} 
// ------------------------------------------------------------------  DEFINE car glass end



// ------------------------------------------------------------------- DRAW car
union{
    object{Four_Wheel_combination}
    object{Tween_Car_With_Hole}
    object{Top_Car_With_hole}
    object{Car_Glass}
    texture{ Car_Body_Texture} 

}
// ------------------------------------------------------------------  DRAW car ends



// ------------------------------------------------------------------- DRAW ground
plane { 
    <0,1,0>, 0 
    texture { 
        pigment{ color rgb<0.35,0.65,0.0>*0.72 }
        normal { bumps 0.75 scale 0.015 }
        finish { phong 0.1 }
        } 
    }
// ------------------------------------------------------------------- DRAW ground ends
