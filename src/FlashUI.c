#include "includes.h"
#include "FlashUI.h"

extern u16 adc_max[8];
extern u16 adc_min[8];

//u16 missLine = 220;
//u16 missLine_M = 150;


VIM_PID  stree_vim_pid;
PID stree_pid;    
//PID speedPid;
PID speedPid;

void Falsh_Reserve() 
{
  flash_erase_sector(SECTOR_NUM); 
  flash_write(SECTOR_NUM, 0,(u32)(stree_pid.p*10));
  flash_write(SECTOR_NUM, 4,(u32)(stree_pid.d*10));  
  flash_write(SECTOR_NUM, 8,(u32)(speedPid.p*10));  
  flash_write(SECTOR_NUM, 12,(u32)(speedPid.i*10));  
  flash_write(SECTOR_NUM, 16,(u32)(speedPid.d*10));  
  flash_write(SECTOR_NUM, 20,(u32)speedPid.goal);  
  flash_write(SECTOR_NUM, 24,(u32)(stree_pid.i*10));
  flash_write(SECTOR_NUM, 28,(u32)(stree_vim_pid.Kp_1*10));
  flash_write(SECTOR_NUM, 32,(u32)(stree_vim_pid.Kp_2*10));
  flash_write(SECTOR_NUM, 36,(u32)(stree_vim_pid.Kp_3*10));
  flash_write(SECTOR_NUM, 40,(u32)(stree_vim_pid.Kp_4*10));
  flash_write(SECTOR_NUM, 44,(u32)(stree_vim_pid.Kp_5*10));
//  flash_write(SECTOR_NUM, 48,(u32)(missLine));
//  flash_write(SECTOR_NUM, 52,(u32)(missLine_M));
}

void Flash_Read()  
{
  stree_pid.p=((float)(flash_read(SECTOR_NUM, 0, u32)))/10;
  stree_pid.i=((float)(flash_read(SECTOR_NUM, 24, u32)))/10;
  stree_pid.d=((float)(flash_read(SECTOR_NUM, 4, u32)))/10;
  speedPid.p=((float)(flash_read(SECTOR_NUM, 8, u32)))/10;
  speedPid.i=((float)(flash_read(SECTOR_NUM, 12, u32)))/10;
  speedPid.d=((float)(flash_read(SECTOR_NUM, 16, u32)))/10;
  speedPid.goal=flash_read(SECTOR_NUM, 20, u32);
  stree_vim_pid.Kp_1=((float)(flash_read(SECTOR_NUM, 28, u32)))/10;
  stree_vim_pid.Kp_2=((float)(flash_read(SECTOR_NUM, 32, u32)))/10;
  stree_vim_pid.Kp_3=((float)(flash_read(SECTOR_NUM, 36, u32)))/10;
  stree_vim_pid.Kp_4=((float)(flash_read(SECTOR_NUM, 40, u32)))/10;
  stree_vim_pid.Kp_5=((float)(flash_read(SECTOR_NUM, 44, u32)))/10;
//  missLine= ((float)(flash_read(SECTOR_NUM, 48, u32)));
//  missLine_M= ((float)(flash_read(SECTOR_NUM, 52, u32)));
}


