

//#include <ap_fixed.h>
//#define	DEBUG			0
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
typedef			unsigned int				TYPE_PINT;
//typedef		double						TYPE_T;

typedef			float						TYPE_T;

typedef		ap_fixed<16, 6, AP_TRN_ZERO>	TYPE_T;

//typedef		ap_fixed<20, 12, AP_TRN_ZERO>	TYPE_T;

#define Tr 13
#define Tc 13
#define Tm 48
#define Tn 3

#define R_IN1 227
#define C_INx1 227
#define N1 3
#define K1 11
#define P1 0
#define R_OUT1 55
#define C_OUT1 55
#define M1 96
#define S1 4

#define POOL_R1 3
#define POOL_C1 3
#define POOL_S1 2
