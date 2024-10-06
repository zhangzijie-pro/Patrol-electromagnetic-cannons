#ifndef __pid__h__
#define __pd__h__

/* 0 位置式  1增量式 */
#define INCR_LOCT_SELECT 1

#if INCR_LOCT_SELECT

#define KP  8.50f
#define KI  5.00f
#define KD  0.10f

#else

#define KP  10.0f
#define KI  8.00f
#define KD  0.5f

#endif

typedef struct
{
    __IO float SetPoint;    /* 目标值 */
    __IO float ActualValue; /* 期望值 */
    __IO float SumError;    /* 累计偏差 */
    __IO float Proportion;  /* 比例系数P */
    __IO float Integral;    /* 积分系数I */
    __IO float Derivative;  /* 微分系数D */
    __IO float Error;       /* error[1] */
    __IO float LastError;   /* error[-1] */
    __IO float PrevError;   /* error[-2] */
}PID_TypeDef;

extern PID_TypeDef g_speed_pid;


void pid_init(void);    /* 初始化 */
int32_t increment_pid_ctrl(PID_TypeDef *PID, float Feedback_value);     /* pid闭环控制 */

#endif