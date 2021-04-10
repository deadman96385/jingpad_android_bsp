typedef struct
{
    unsigned long FIX_EN;
    unsigned long RD_PRIORITY;
    unsigned long WR_PRIORITY;
    unsigned long BDW;
    unsigned long BDW_OVFL;
    unsigned long ALL_STRB_EN;
    unsigned long ACMDQ_TH;
    unsigned long AGE_COUNT;
    unsigned long CMD_AGE_COUNT;
    unsigned long Q_FULLNESS;
    unsigned long NQ_DIS;
}CANDS_QOS_T;


CANDS_QOS_T *__get_qos_info();
