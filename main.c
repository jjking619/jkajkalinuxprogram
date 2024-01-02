#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//执行器
#define BEEP_FileName "/sys/devices/platform/fs6818-beep/state"     //峰鸣器路径
//传感器
#define DS18B20_FileName "/dev/ds18b20"                             //温度传感器
/*------------------------------------------------------------------------------
实验结论：只需要了解2个点
    1.设备文件位置（路径+文件名)
    2.设备协议
今天的作业:使用菜单实现控制LED三元色灯 + 峰鸣器 + 温度 
思考：如何UI界面 远程控制 A53开发板设备
--------------------------------------------------------------------------------*/
int main()
{
    //执行器
    int beep_fd = open(BEEP_FileName,O_RDWR);
    if(beep_fd < 0){
        perror("峰鸣器打开失败:");
        return -1;
    }
    //传感器
    int DS18B20_fd = open(DS18B20_FileName,O_RDWR);
    if(DS18B20_fd < 0){
        perror("温度传感器打开失败:");
        return -1;
    }
    /*------- 实现一个用户交互菜单 -------*/
    int select = 0;
    char ds18b20Date[2];
    while(1)
    {
        system("clear");    //清屏幕
        printf("1.打开峰鸣器\n");
        printf("2.关闭峰鸣器\n");
        printf("3.读取温度\n");
        printf("请输入您的选项:");
        scanf("%d",&select);
        switch (select)
        {
            case 1: write(beep_fd,"1",strlen("1")); break;
            case 2: write(beep_fd,"0",strlen("0")); break;
            case 3:
                read(DS18B20_fd,ds18b20Date,2);
                printf("温度:%d.%d\n",ds18b20Date[0],ds18b20Date[1]);
                getchar();getchar();
            break;
        }
    }
    return 0;
}