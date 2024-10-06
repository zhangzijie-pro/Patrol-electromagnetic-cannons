#include "pid.h"

PID_TypeDef g_speed_pid;

void pid_init(void)
{
    g_speed_pid.SetPoint=0;
    g_speed_pid.ActualValue=0;
    g_speed_pid.SumError=0;    /* 累计偏差 */
    g_speed_pid.Proportion=KP;  /* 比例系数P */
    g_speed_pid.Integral=KI;    /* 积分系数I */
    g_speed_pid.Derivative=KD;  /* 微分系数D */
    g_speed_pid.Error=0;       /* error[1] */
    g_speed_pid.LastError=0;   /* error[-1] */
    g_speed_pid.PrevError=0;   /* error[-2] */
}

/* Feedback_value: 实际的值 */
int32_t increment_pid_ctrl(PID_TypeDef *PID, float Feedback_value)
{
    PID->Error = (float)(PID->SetPoint-Feedback_value);     // 计算偏差

#if INCR_LOCT_SELECT        /* 增量式 */
    PID->ActualValue += (PID->Proportion*(PID->Error-PID->LastError))   /* 比例项 */
                    + (PID->Integral*PID->Error)                        /* 积分项 */
                    + (PID->Derivative*(PID->Error-2*PID->LastError-PID->PrevError));   /* 微分项 */
    PID->PrevError = PID->LastError;
    PID->LastError = PID->Error;
#else                       /* 比例式  全量计算*/
    PID->SumError += PID->Error;
    PID->ActualValue += (PID->Proportion*PID->Error)   /* 比例项 */
                    + (PID->Integral*PID->SumError)                        /* 积分项 */
                    + (PID->Derivative*(PID->Error-PID->LastError));   /* 微分项 */
    PID->LastError = PID->Error;
#endif
    return ((int32_t)(PID->ActualValue));   /* 返回期望值 */

}

