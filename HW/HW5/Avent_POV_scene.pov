//wrap the file with the version
#local Temp_version = version;
#version 3.7;
//==================================================
//POV-Ray Main scene file
//==================================================
//This file has been created by PoseRay v3.13.29.645
//3D model to POV-Ray/Moray Converter.
//Author: FlyerX
//Email: flyerx_2000@yahoo.com
//Web: https://sites.google.com/site/poseray/
//==================================================
//Files needed to run the POV-Ray scene:
//Avent_POV_main.ini (initialization file - open this to render)
//Avent_POV_scene.pov (scene setup of cameras, lights and geometry)
//Avent_POV_geom.inc (geometry)
//Avent_POV_mat.inc (materials)
//interior_lod0.tga
//gaudges.jpg
// 
//==================================================
//Model Statistics:
//Number of triangular faces..... 183309
//Number of vertices............. 98237
//Number of normals.............. 104359
//Number of UV coordinates....... 247757
//Number of lines................ 0
//Number of materials............ 28
//Number of groups/meshes........ 270
//Number of subdivision faces.... 0
//UV boundaries........ from u,v=(-50.2391,-31.4306)
//                        to u,v=(42.2822,198.662)
//Bounding Box....... from x,y,z=(-2.83642,0.0382158,-1.31151)
//                      to x,y,z=(2.59642,1.36552,1.27151)
//                 size dx,dy,dz=(5.43284,1.3273042,2.58302)
//                  center x,y,z=(-0.12,0.7018679,-0.02)
//                       diagonal 6.16031486413947
//Surface area................... 99.1293944631083
//             Smallest face area 4.69999999828077E-10
//              Largest face area 0.348869673330635
//Memory allocated for geometry: 21 MBytes
// 
//==================================================
//IMPORTANT:
//This file was designed to run with the following command line options: 
// +W320 +H240 +FN +AM2 +A0.1 +r3 +Q9 +C -UA +MV3.7
//if you are not using an INI file copy and paste the text above to the command line box before rendering
 
#include "rad_def.inc"
 
global_settings {
  //This setting is for alpha transparency to work properly.
  //Increase by a small amount if transparent areas appear dark.
   max_trace_level 15
   adc_bailout 0.01
   assumed_gamma 1
 
   #local p_start=64/max(image_width,image_height);
   #local p_end_final=1/max(image_width,image_height);
radiosity {
     pretrace_start p_start
     pretrace_end   p_end_final
     count 800
     nearest_count 5
     error_bound 0.5
     recursion_limit 1
     low_error_factor .5
     gray_threshold 0.0
     minimum_reuse 0.015
     brightness 1
     adc_bailout 0.01/2
}
}
#include "Avent_POV_geom.inc" //Geometry
 
//CAMERA PoseRayCAMERA
camera {
        perspective
        up <0,1,0>
        right -x*image_width/image_height
        location <-1.11022302462516E-16,0,12.3206297282789>
        look_at <-1.11022302462516E-16,0,11.3206297282789>
        angle 32.9346087425027 // horizontal FOV angle
        rotate <0,0,11.2938776344019> //roll
        rotate <-27.6024768508463,0,0> //pitch
        rotate <0,-49.3207547336575,0> //yaw
        translate <-0.12,0.7018679,-0.02>
        }
 
//PoseRay default Light attached to the camera
light_source {
              <-1.11022302462516E-16,0,12.3206297282789> //light position
              color rgb <1,1,1>*1.6
              parallel
              point_at <-1.11022302462516E-16,0,0>
              rotate <0,0,11.2938776344019> //roll
              rotate <-27.6024768508463,0,0> //elevation
              rotate <0,-49.3207547336575,0> //rotation
             }
 
//Background
background { color srgb <1,1,1>  }
 
//Assembled object that is contained in Avent_POV_geom.inc with no SSLT components
object{
      Avent_
      }
 
//restore the version used outside this file
#version Temp_version;
//==================================================
