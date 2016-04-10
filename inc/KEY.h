#ifndef _KEY_H
#define _KEY_H
#include "common.h"
#include "includes.h"
 
#define KEY_U  PAin(13)
#define KEY_D  PAin(12)
#define KEY_A  PAin(19)
#define KEY_B  PAin(11)


///////////////////////////////////////

typedef enum
{   
    KEY_DOWN    = 12,  //�¼�
    KEY_RIGHT   = 19,  //�Ҽ�
    KEY_UP      = 13, //�ϼ�
    KEY_LEFT    = 11, //���
	
	
}KEY_e;

static void KEY_Scan(void);
void KEY_Init(void);    //������ʼ��
void KEY_Service(void); //�жϹܽ�����

u8 key_check(KEY_e key);  //ɨ�谴��

#endif












