#include "colors.inc"       //..\Documents\POV-Ray\v3.7\include
#include "shapes.inc"
#include "textures.inc"
#include "stones.inc" 
   
camera
{
   location <0,1.0,-10.0>   //决定相机位置：物体始终在屏幕中心,相机对着物体,沿着xyz方向平移
   look_at < 0.0,0,0.0>     //决定相机朝向：相机位置不动,屏幕中心移动
                            //(有相机绕一个支点,沿着xyz轴方向转动的感觉)
   //angle 90               //距离物体的远近(放大缩小的感觉,范围0-180)
   focal_point <-7,0,13>    //焦点所落在的位置
   aperture   0.01          //小光圈大光图,即获得不同的聚焦效果;
                            //值越小,关注的区域就越大(各个远近层次的物体都很清楚),反之,则小.
   blur_samples 20          //采样设置,值越大,采样点数越多,质量/分辨率越高的图像，
                            //但相应的渲染时间就会长.
}
light_source { <5, 30, -30>  color White }    ////定义两个光源;关于x轴对称
light_source { <-5, 30, -30> color White }
  
plane {                     ////定义一个平面
    y, -1.5                 //平面方程：y=-1.5
    pigment {               //着色;使用棋盘格
        checker color Gray65 color Gray30
    }
} 
  
sphere {
    <0,-0.3,-6>, 0.5        ////定义一个球体: 圆心+半径
    translate <0,0.5,-1>    //移动:相对于目前位置,要移动的变化量
    finish {
    ambient 0.1             //环境光
    diffuse 0.7             //物体漫反射光
    }
    pigment { LimeGreen }
    //texture { PinkAlabaster }
    finish  { phong 0.3}    //添加Phong光照模型，来产生高亮效果
}

#declare my_box_transform = //自定义一个变换集合
    transform {
        rotate <40, 20, 20> //旋转: 绕xyz轴分别旋转40/20/30度
        translate <0.2,-2,0>
        scale 1.5           //缩放: 大小*1.1倍; 相当于向量<1.1, 1.1, 1.1>
    }  
 
box {
    <2,1,-1>, <3,2,0>       ////定义一个立方体: 两个对角顶点
    //texture {				    //Method 1.棋盘格纹理模型
    // pigment {
    //    checker Red, White
    //    scale 0.25            //这个scale只影响texture
    //    }
    //}
    transform my_box_transform  
    finish {
        ambient 0.4
        diffuse 0.6
    }
    pigment {                   //Method 2.木质纹理模型
        wood                    //确定上色模式，这里是木制
        color_map {             //确定颜色向量是如何来安排颜色值
          [0.0 color DarkTan]   //从DarkTan到DarkBrown占据脉络的90%，
          [0.9 color DarkBrown] //而从DarkBrown到VeryDarkBrown占据了10%
          [1.0 color VeryDarkBrown]
        }
        turbulence 0.07         //调节模式的条纹脉络,褶皱强度
        scale <0.25,0.1,1>      //调节模式的大小,此处值越小纹理越密集
    } 
    //pigment {DMFWood4 }       //Method 3.使用预定义的木质纹理
}  

cylinder {                  ////定义一个圆柱体: 两个底面圆心+圆柱半径
    <-7, 0, 10>, <-7, 4, 10>, 3 
    rotate <10, 0, -10>
    translate <0,0,3>
    finish {
		ambient 1.9
		diffuse 0.1
    }
    //pigment {NeonBlue}
	texture {
    	T_Stone24          //预定义纹理: 添加大理石纹理
    	scale 0.9          //这个scale只影响纹理
	} 
	normal {
	    bumps 1.1          // 指定凸起的表观高度
	    scale 0.03         // 指定直径大小(凸起间隔/高度).对颜色图案没有影响
    }
}