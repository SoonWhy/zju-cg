#pragma once
#include"glut.h"
#include"stdio.h"
#include"stdlib.h"

void initShade(){
    /*初始化光源与阴影图*/


    //生成深度纹理(阴影图，只关心深度，对图像颜色信息并不关心，所以最后数据参数可以是NULL)
    glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 256, 256, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL );//GL_DEPTH_COMPONENT:深度纹理格式，用于将深度值记录到这张图中
	GL_MODEL
    //设置阴影图相关过滤方式
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    /*深度纹理特有*/
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL );//比较规则
    glTexParameteri( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE );//阴影图亮度
    /*分为普通对比模式（GL_NONE）和引用到贴图对比模式（GL_COMPARE_REF_TO_TEXTURE）,后者使用的深度纹理贴图是线性过滤的，而前者是直接填充。*/
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE );

    //自动生成纹理坐标
    glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
    glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
    glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
    glTexGeni( GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );

    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

    glCullFace( GL_BACK );//剔除背面

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHTING );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_TEXTURE_GEN_S );
    glEnable( GL_TEXTURE_GEN_T );
    glEnable( GL_TEXTURE_GEN_R );
    glEnable( GL_TEXTURE_GEN_Q );
    glEnable( GL_COLOR_MATERIAL );//激活颜色材料模式
    glEnable( GL_CULL_FACE );//激活表面剔除
}