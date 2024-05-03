/*************定时器3 time_go和编码器冲突*************/
/**********************接线***************************/
/*前八路灰度->八路灰度1  后八路灰度->八路灰度2*/
/*前一路灰度->HDIO2   中一路灰度->HDIO3 后一路灰度->HDIO4*/
/*左前电机 电机1 左后电机 电机2 右前电机 电机3 右后电机 电机4*/
/*pca9685 IIC1 TCS34725 IIC3*/
/***********************舵机**************************/
/*pca9685 接线
#define daduoji    7              //大舵机  
#define taotong_1  5  
#define taotong_2  6
#define hozhua_A   1  
#define hozhua_B   4
#define hozhua_C   3
#define hozhua_D   2
#define hozhua_E   0
#define qianzhua_zuo 9
#define qianzhua_you 8
*/