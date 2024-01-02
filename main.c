#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//ִ����
#define BEEP_FileName "/sys/devices/platform/fs6818-beep/state"     //������·��
//������
#define DS18B20_FileName "/dev/ds18b20"                             //�¶ȴ�����
/*------------------------------------------------------------------------------
ʵ����ۣ�ֻ��Ҫ�˽�2����
    1.�豸�ļ�λ�ã�·��+�ļ���)
    2.�豸Э��
�������ҵ:ʹ�ò˵�ʵ�ֿ���LED��Ԫɫ�� + ������ + �¶� 
˼�������UI���� Զ�̿��� A53�������豸
--------------------------------------------------------------------------------*/
int main()
{
    //ִ����
    int beep_fd = open(BEEP_FileName,O_RDWR);
    if(beep_fd < 0){
        perror("��������ʧ��:");
        return -1;
    }
    //������
    int DS18B20_fd = open(DS18B20_FileName,O_RDWR);
    if(DS18B20_fd < 0){
        perror("�¶ȴ�������ʧ��:");
        return -1;
    }
    /*------- ʵ��һ���û������˵� -------*/
    int select = 0;
    char ds18b20Date[2];
    while(1)
    {
        system("clear");    //����Ļ
        printf("1.�򿪷�����\n");
        printf("2.�رշ�����\n");
        printf("3.��ȡ�¶�\n");
        printf("����������ѡ��:");
        scanf("%d",&select);
        switch (select)
        {
            case 1: write(beep_fd,"1",strlen("1")); break;
            case 2: write(beep_fd,"0",strlen("0")); break;
            case 3:
                read(DS18B20_fd,ds18b20Date,2);
                printf("�¶�:%d.%d\n",ds18b20Date[0],ds18b20Date[1]);
                getchar();getchar();
            break;
        }
    }
    return 0;
}