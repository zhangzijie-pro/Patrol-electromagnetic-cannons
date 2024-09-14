// 伪代码

#include <iostream>
#include <cstdlib>

//* 定义esp32-cam发送报文内容  
    // 1. esp32-cam -> HC-04 -> Stm32f4
    // 2. esp32-cam -> stm32f4  串口
int content[9]={0};

void init_content(){
    content[0] = 0xAA;
    content[1] = 0xAA;

    contnet[7] = 0x11;
    content[8] = 0x00;
}

void check(){
    if(camera_regconize()){
        content[2] = 1;
    }else{
        content[2] = 0;
    }

    int *postion = camera_cheack_pos();
    for(int i=0;i<3,i++){
        content[2++] = postion[i];
    }
}



#include "stdlib.h"
#include "string.h"
//* 解析报文 
//* 1.读取HC-04返回数据
//* 2.esp32-cam -> stm32f4: Usart

int *spilt_content(int *content){
/*     int* pvalue  = NULL; // 初始化为 null 的指针
    pvalue  = new int;   // 为变量请求内存 */

    int* pvalue = malloc(sizeof(int) * (1 + 5)); // 1个整数加上5个整数

    if (pvalue == NULL) {
        // 如果内存分配失败，返回 NULL
        return NULL;
    }

    if(sizeof(content)<8&&content[0]==content[1]&&(content[7]&content[8]==0)){
        *pvalue[0] = 1;
    }else{
        *pvalue[0] = 0;
    }
    
    memcpy(pvalue + 1, content + 1, sizeof(int) * 5);
    
    return pvalue;
}

/* return content: bool: 判断是否该设备返回报文, bool: 是否识别到人体, 2-5: 目标相对坐标  */
void camera_do(){
    int *content_return = spilt_content(content);
    if(content_return[0]==1){
        if(content_return[1]==1){  /* 识别到人体 */
            /* 进行坐标的计算转换 */
            /* 调整电磁炮的射击角度锁定目标并且完成发送 */
        }
        else if(content_return[1]==0){
            /* 切换武器为炮弹向大致范围中投出 */
        }
    }
}