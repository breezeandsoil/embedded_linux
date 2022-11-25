#include <stdio.h>
struct REG_BITS {
    unsigned int F0 : 8;
    unsigned int F1 : 8;
    unsigned int F2 : 8;
    unsigned int F3 : 8;
};
union ADC_CONTROL {
    unsigned int U;
    struct REG_BITS B;
};

<<<<<<< HEAD
typedef struct{
    unsigned char MODE : 4;
    unsigned char EN : 1;
    unsigned char _NA : 2;
    unsigned char EOC : 1;
} ADC_REG;

#define HW_EMULATION 1
#ifdef HW_EMULATION
    unsigned char adc1;
    #define ADCR (*(volatile unsigned char*)&adc1)
#else
    #define ADCR (*(ADC_REG*)(FB000000))
#endif

// volatile

int main() {
    printf("Running...\n");

    ADCR = 0x3;
    int g = ADCR + 7;

    printf("g is %d\n", g);
=======
#define HW_EMULATION 1
#ifdef HW_EMULATION
  // allocation on memory to get region, 
  // then we can point out there with &adc_control1
  union ADC_CONTROL adc_control1;
  #define ADCC (*(volatile union ADC_CONTROL*)&adc_control1)
#else
  //                                     from Chip Spec Manual
  //                                             |
  //                                             V
  #define ADCC (*(volatile union ADC_CONTROL*)0xFFB00000)
//#define P    (*(                       int*)0xFFCC0000)
#endif

#define F2_IDX 16
#define EOC_IDX 3

int main() {
    ADCC.U = 0x12345678;
    ADCC.B.F2 = 0x5A;
    printf("ADCC: 0x%08X\n", ADCC.U);

    ADCC.U  = 0x12345678;
    ADCC.U &= 0xFF00FFFF; // masking
    ADCC.U |= 0x005A0000; // bit set
    
    printf("ADCC: 0x%08X\n", ADCC.U);

    ADCC.U  = 0x12345678;
    ADCC.U &= ~(0xFF << F2_IDX); // clear bit slide using mask pattern generation
    ADCC.U |= 0x5A << F2_IDX;    // then we can set bit slice
    printf("ADCC: 0x%08X\n", ADCC.U);
    
    // wait here until ADCC[3] is 1
    while( (ADCC.U & (1<<EOC_IDX)) == 0);
>>>>>>> dffb2f72649c40e58684cc4fd787e4719b4c16c1

    // check hardare via bus with memory-mapped hardware
    // ADCC[3] is 1, go through here
    printf("End of conversion\n");
    return 0;
}