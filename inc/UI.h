#ifndef _UI_H_
#define _UI_H_
#include "common.h"
#include  "KEY.h"
/*******��������*******/

extern u8 (*FunctionPointer[11])(void);
//extern u8 KEY_;
extern u8 FLAG_RUN;
extern u8 Plan_1;
extern u8 Plan_2;
extern u8 Plan_3;
extern u8 Plan_4;
extern u8 Plan_5;
extern u8 Plan_6;


extern u8 FLAG_RUN;

extern u8 (*FunctionPointer[11])(void);


#define Menu_UI_ID               0
#define Run_UI_ID                1
#define State1_UI_ID             2
#define Set_UI_ID                3
#define Record_UI_ID             4
#define Read_UI_ID               5

/*******��������*******/

//void KEY_Init();    //������ʼ��
//void KEY_Service(); //�жϹܽ�����


void KEY_Display(void);   //���湦����ʾ

u8 UI_Menu(void);      //������
u8 UI_Star(void);      //����
u8 UI_PID(void);       //��ʾPID��������
u8 UI_State(void);     //��ʾС��״̬����
u8 UI_Flash(void);  //��ʾ����A
u8 UI_Scheme_B(void);  //��ʾ����B


u8 Menu_UI(void); //  ������ IDΪ0
u8 Run_UI(void);  //  ���ܽ��� IDΪ1
u8 State1_UI(void); //  �鿴��ͷ״̬���� IDΪ2
u8 Set_UI(void);   //  �������ý��� IDΪ3
u8 Record_UI(void); // ����������� IDΪ4
u8 Read_UI(void); //IDΪ5
void AddNumString(u8 ss[],u8 n[]);//���ּ�����ʾ�ַ���
void speedClear(void);            //������ �ص���ʼ״̬

#endif

