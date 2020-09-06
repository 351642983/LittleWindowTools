//设置信息的总头文件，以方便修改游戏属性
#ifndef HANDOPTION_H
#define HANDOPTION_H

//版本，用于检查更新
#define VERSION "1.3.4"

#define LENTH 20
#define LENNUM 800/(int)LENTH
#define HEINUM 600/(int)LENTH
#define MG_RUNFPS 200
#define MGRUNSPEED 250.0
#define BACKSPEED 150.0

#define SPEEDSET MGRUNSPEED/(qreal)MG_RUNFPS
#define BACKSPEEDSET BACKSPEED/(qreal)MG_RUNFPS


#endif // HANDOPTION_H
