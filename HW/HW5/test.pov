#include "colors.inc"       //..\Documents\POV-Ray\v3.7\include
#include "shapes.inc"
#include "textures.inc"
#include "stones.inc" 
   
camera
{
   location <0,1.0,-10.0>   //�������λ�ã�����ʼ������Ļ����,�����������,����xyz����ƽ��
   look_at < 0.0,0,0.0>     //��������������λ�ò���,��Ļ�����ƶ�
                            //(�������һ��֧��,����xyz�᷽��ת���ĸо�)
   //angle 90               //���������Զ��(�Ŵ���С�ĸо�,��Χ0-180)
   focal_point <-7,0,13>    //���������ڵ�λ��
   aperture   0.01          //С��Ȧ���ͼ,����ò�ͬ�ľ۽�Ч��;
                            //ֵԽС,��ע�������Խ��(����Զ����ε����嶼�����),��֮,��С.
   blur_samples 20          //��������,ֵԽ��,��������Խ��,����/�ֱ���Խ�ߵ�ͼ��
                            //����Ӧ����Ⱦʱ��ͻ᳤.
}
light_source { <5, 30, -30>  color White }    ////����������Դ;����x��Գ�
light_source { <-5, 30, -30> color White }
  
plane {                     ////����һ��ƽ��
    y, -1.5                 //ƽ�淽�̣�y=-1.5
    pigment {               //��ɫ;ʹ�����̸�
        checker color Gray65 color Gray30
    }
} 
  
sphere {
    <0,-0.3,-6>, 0.5        ////����һ������: Բ��+�뾶
    translate <0,0.5,-1>    //�ƶ�:�����Ŀǰλ��,Ҫ�ƶ��ı仯��
    finish {
    ambient 0.1             //������
    diffuse 0.7             //�����������
    }
    pigment { LimeGreen }
    //texture { PinkAlabaster }
    finish  { phong 0.3}    //���Phong����ģ�ͣ�����������Ч��
}

#declare my_box_transform = //�Զ���һ���任����
    transform {
        rotate <40, 20, 20> //��ת: ��xyz��ֱ���ת40/20/30��
        translate <0.2,-2,0>
        scale 1.5           //����: ��С*1.1��; �൱������<1.1, 1.1, 1.1>
    }  
 
box {
    <2,1,-1>, <3,2,0>       ////����һ��������: �����ԽǶ���
    //texture {				    //Method 1.���̸�����ģ��
    // pigment {
    //    checker Red, White
    //    scale 0.25            //���scaleֻӰ��texture
    //    }
    //}
    transform my_box_transform  
    finish {
        ambient 0.4
        diffuse 0.6
    }
    pigment {                   //Method 2.ľ������ģ��
        wood                    //ȷ����ɫģʽ��������ľ��
        color_map {             //ȷ����ɫ�����������������ɫֵ
          [0.0 color DarkTan]   //��DarkTan��DarkBrownռ�������90%��
          [0.9 color DarkBrown] //����DarkBrown��VeryDarkBrownռ����10%
          [1.0 color VeryDarkBrown]
        }
        turbulence 0.07         //����ģʽ����������,����ǿ��
        scale <0.25,0.1,1>      //����ģʽ�Ĵ�С,�˴�ֵԽС����Խ�ܼ�
    } 
    //pigment {DMFWood4 }       //Method 3.ʹ��Ԥ�����ľ������
}  

cylinder {                  ////����һ��Բ����: ��������Բ��+Բ���뾶
    <-7, 0, 10>, <-7, 4, 10>, 3 
    rotate <10, 0, -10>
    translate <0,0,3>
    finish {
		ambient 1.9
		diffuse 0.1
    }
    //pigment {NeonBlue}
	texture {
    	T_Stone24          //Ԥ��������: ��Ӵ���ʯ����
    	scale 0.9          //���scaleֻӰ������
	} 
	normal {
	    bumps 1.1          // ָ��͹��ı�۸߶�
	    scale 0.03         // ָ��ֱ����С(͹����/�߶�).����ɫͼ��û��Ӱ��
    }
}