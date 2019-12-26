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
//McLaren_2001_POV_main.ini (initialization file - open this to render)
//McLaren_2001_POV_scene.pov (scene setup of cameras, lights and geometry)
//McLaren_2001_POV_geom.inc (geometry)
//McLaren_2001_POV_mat.inc (materials)
//DeflectGAMaclaren.jpg
//DeflectDRMaclaren.jpg
//TxturpttaileronDmaclaren.jpg
//FlanGmaclaren.jpg
//FlanDmaclaren.jpg
//pontotomaclaren.jpg
//Ferraripneus.jpg
//nezmapHakkinen.jpg
//NezmapDmaclarentest.jpg
//NezmapGmaclarentest.jpg
//retrotextureMaclaren.jpg
//camera.jpg
//AirboxLHakkinen.jpg
//AirboxRHakkinen.jpg
//CloisAVGAMaclaren.jpg
//FlapAVHakkinen.jpg
//AilAVMaclaren.jpg
//FlapARmaclaren.jpg
//cloisonaGAHakkinen.jpg
//cloisonaDRHakkinen.jpg
// 
//==================================================
//Model Statistics:
//Number of triangular faces..... 30482
//Number of vertices............. 16499
//Number of normals.............. 14845
//Number of UV coordinates....... 0
//Number of lines................ 0
//Number of materials............ 43
//Number of groups/meshes........ 1
//Number of subdivision faces.... 0
//Bounding Box....... from x,y,z=(-1.28873,-0.662106,-3.08019)
//                      to x,y,z=(1.2884,0.798188,3.08019)
//                 size dx,dy,dz=(2.57713,1.460294,6.16038)
//                  center x,y,z=(-0.000164999999999971,0.068041,0)
//                       diagonal 6.83552041528193
//Surface area................... 67.5088459234534
//             Smallest face area 3.68079550000019E-7
//              Largest face area 0.963625035444742
//Memory allocated for geometry: 2 MBytes
// 
//==================================================
//IMPORTANT:
//This file was designed to run with the following command line options: 
// +W320 +H240 +FN +AM1 +A0.3 +r3 +Q9 +C -UA +MV3.7
//if you are not using an INI file copy and paste the text above to the command line box before rendering
 
 
global_settings {
  //This setting is for alpha transparency to work properly.
  //Increase by a small amount if transparent areas appear dark.
   max_trace_level 15
   adc_bailout 0.01
   assumed_gamma 1
 
}
#include "McLaren_2001_POV_geom.inc" //Geometry
 
//CAMERA PoseRayCAMERA
camera {
        perspective
        up <0,1,0>
        right -x*image_width/image_height
        location <-2.71050543121376E-19,-1.38777878078145E-17,13.6710408305639>
        look_at <-2.71050543121376E-19,-1.38777878078145E-17,12.6710408305639>
        angle 32.9346087425027 // horizontal FOV angle
        rotate <0,0,3.39584069755449> //roll
        rotate <-7.84651152895388,0,0> //pitch
        rotate <0,-122.720909979916,0> //yaw
        translate <-0.000164999999999971,0.068041,0>
        }
 
//PoseRay default Light attached to the camera
light_source {
              <-2.71050543121376E-19,-1.38777878078145E-17,13.6710408305639> //light position
              color rgb <1,1,1>*1.6
              parallel
              point_at <-2.71050543121376E-19,-1.38777878078145E-17,0>
              rotate <0,0,3.39584069755449> //roll
              rotate <-7.84651152895388,0,0> //elevation
              rotate <0,-122.720909979916,0> //rotation
             }
 
//Background
background { color srgb <1,1,1>  }
 
//Assembled object that is contained in McLaren_2001_POV_geom.inc with no SSLT components
object{
      McLaren_2001_
      }
 
//restore the version used outside this file
#version Temp_version;
//==================================================
