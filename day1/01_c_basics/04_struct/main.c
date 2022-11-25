#include <stdio.h>

<<<<<<< HEAD
typedef struct{
=======
/*
struct ADC_CONFIG {
    unsigned char CNFG1;
    unsigned char CNFG2;
    unsigned short MODE;
};
struct ADC_CONFIG adc1;
*/
typedef struct {
>>>>>>> dffb2f72649c40e58684cc4fd787e4719b4c16c1
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
} bits8;

<<<<<<< HEAD
typedef struct{
    unsigned char CNFG1;
    unsigned char CNFG2;
    unsigned short MODE ;
} ADC_CNFG;

typedef union{
    ADC_CNFG adc;
    unsigned char bytes[4];
    bits8   regs[4];
} flag_32bits;
=======
typedef struct {
    unsigned char CNFG1;
    unsigned char CNFG2;
    unsigned short MODE;
} ADC_CONFIG;

typedef union {
    ADC_CONFIG    adc;
    unsigned char bytes[4];
    bits8         regs[4];
} flag_32bits;

void mem_inspection(unsigned char* p, int N) {
    for(int i=0; i<N; i++)  
        printf("mem[%d] is 0x%02X at 0x%p\n", i, *(p+i), p+i);
}
>>>>>>> dffb2f72649c40e58684cc4fd787e4719b4c16c1

int main() {
    printf("Running...\n");
    printf("struct size : %d\r\n", sizeof(ADC_CNFG));
    ADC_CNFG adc1 = {0x01, 0x80, 0xF0};
    flag_32bits flag;
    flag.adc = adc1;
    printf("bytes is 0x%8X\n", flag.bytes[3]);
    printf("struct size : %d\r\n", sizeof(ADC_CNFG));
    flag.regs[3].b7 = 0;
    printf("bytes is 0x%8X\n", flag.bytes[3]);
    printf("union size : %d\r\n", sizeof(flag_32bits));

    ADC_CONFIG adc1 = {0x01, 0x80, 0xF000};
    printf("adc1 is allocated at 0x%p with %ld\n", &adc1, sizeof(adc1));
    printf("adc1.CNFG1 is %2X at 0x%p\n", adc1.CNFG1, &(adc1.CNFG1));
    printf("adc1.CNFG1 is %2X at 0x%p\n", adc1.CNFG2, &(adc1.CNFG2)); 
    printf("adc1.CNFG1 is %4X at 0x%p\n", adc1.MODE, &(adc1.MODE));        

    unsigned char* adc_p = (unsigned char*)&adc1;
    mem_inspection(adc_p, sizeof(adc1));
    adc1.CNFG2 = 0xBB;
    mem_inspection(adc_p, sizeof(adc1));
    *(adc_p+1) = 0xCC;
    mem_inspection(adc_p, sizeof(adc1));
    *(adc_p+2) = 0x5A;
    mem_inspection(adc_p, sizeof(adc1));

    flag_32bits flag;
    printf("flag is allocated with %ld bytes\n", sizeof(flag));

    flag.adc = adc1;
    printf("bytes[3] is 0x%02X\n", flag.bytes[3]);

    flag.bytes[1] = 0x5A;
    printf("CNFG2 is 0x%02X\n", flag.adc.CNFG2);

    printf("CNFG1.b0 is %d\n", flag.regs[0].b0);
    flag.regs[0].b1 = 1;
    flag.regs[0].b4 = 1;
    printf("CNFG1 is 0x%02X\n", flag.adc.CNFG1);

}
