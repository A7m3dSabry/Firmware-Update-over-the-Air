
#ifndef STM32F103C8T_H
#define STM32F103C8T_H

#include "std_types.h"

/*
 * File Architecture Map
 *
 * 		(1) SCB
 * 		(2) SYSTICK
 * 		(3) NVIC
 * 		(4) MPU
 * 		(5) RCC
 * 		(6) _CRC
 * 		(7) PWR
 * 		(8) BKP
 * 		(9) GPIO
 * 		(10) _AFIO
 * 		(11) EXTI
 * 		(12) DMA
 *
 * 		(13) ADC
 * 		(14) DAC TODO
 * 		(15) TIMERs (ADVANCED)
 * 		(16) TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4
 * 		(17) TIMERs (BASIC) TIM6,TIM7
 *
 * 		(18) SPI TODO
 * 		(19) USART
 * 		(20) I2Cs
 * 		(21) CAN TODO
 * 		(22) USB TODO
 * 		(23) ETH TODO
 *
 * 		(24) RTC TODO
 * 		(25) IWDG TODO
 * 		(26) WWDG TODO
 *
 * 		(27) SDIO TODO
 * 		(28) FSMC TODO
 * 		(29) FLASH
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * */



#define PERIPHERAL_MEMORY_BASE           (0x40000000UL)


/***************************************************************/
/*					    	(1) SCB							   */
/***************************************************************/

/*
 * 	SCB Section Architecture Map
 *		1- SCB->Base_Definitions
 *		2- SCB->Registers_Pointers
 *		3- SCB->Struct_Definition
 *		4- SCB->Registers_Values_Definitions
 *			4.1-
 *
 *
 * */


/***************** 1- SCB->Base_Definition ***************/

// #define SCB_ACTLR_BASE	(0xE000E008) // only available in STM32F2 and STM32L

#define SCB_BASE            (0xE000ED00)
#define SCB_CPUID_BASE        (SCB_BASE + 0x00)
#define SCB_ICSR_BASE        (SCB_BASE + 0x04)
#define SCB_VTOR_BASE        (SCB_BASE + 0x08)
#define SCB_AIRCR_BASE        (SCB_BASE + 0x0C)
#define SCB_SCR_BASE        (SCB_BASE + 0x10)
#define SCB_CCR_BASE        (SCB_BASE + 0x14)
#define SCB_SHPR1_BASE        (SCB_BASE + 0x18)
#define SCB_SHPR2_BASE        (SCB_BASE + 0x1C)
#define SCB_SHPR3_BASE        (SCB_BASE + 0x20)
#define SCB_SHCRS_BASE        (SCB_BASE + 0x24)
#define SCB_CFSR_BASE        (SCB_BASE + 0x28)
#define SCB_HFSR_BASE        (SCB_BASE + 0x2C)
#define SCB_MMAR_BASE        (SCB_BASE + 0x34)
#define SCB_BFAR_BASE        (SCB_BASE + 0x38)


/***************** 2- SCB->Registers_Pointers ***************/


#define SCB_CPUID    (*((volatile unsigned long *)SCB_CPUID_BASE))
#define SCB_ICSR    (*((volatile unsigned long *)SCB_ICSR_BASE))
#define SCB_VTOR    (*((volatile unsigned long *)SCB_VTOR_BASE))
#define SCB_AIRCR    (*((volatile unsigned long *)SCB_AIRCR_BASE))
#define SCB_SCR        (*((volatile unsigned long *)SCB_SCR_BASE))
#define SCB_CCR        (*((volatile unsigned long *)SCB_CCR_BASE))
#define SCB_SHPR1    (*((volatile unsigned long *)SCB_SHPR1_BASE))
#define SCB_SHPR2    (*((volatile unsigned long *)SCB_SHPR2_BASE))
#define SCB_SHPR3    (*((volatile unsigned long *)SCB_SHPR3_BASE))
#define SCB_SHCRS    (*((volatile unsigned long *)SCB_SHCRS_BASE))
#define SCB_CFSR    (*((volatile unsigned long *)SCB_CFSR_BASE))
#define SCB_HFSR    (*((volatile unsigned long *)SCB_HFSR_BASE))
#define SCB_MMAR    (*((volatile unsigned long *)SCB_MMAR_BASE))
#define SCB_BFAR    (*((volatile unsigned long *)SCB_BFAR_BASE))


/***************** 3- SCB->Struct_Definition ***************/

#define SCB        ((volatile SCB_t *)SCB_BASE)

typedef volatile struct {


    volatile union {
        struct {

            const unsigned long Revision: 4;
            const unsigned long PartNo: 12;
            const unsigned long RESERVED: 4;
            const unsigned long Variant: 4;
            const unsigned long Implementer: 8;
        };
        const unsigned long REG;
    } CPUID;

    volatile union {

        struct {
            unsigned long VECTACTIVE: 9;
            const unsigned long RESERVED: 2;
            const unsigned long RETOBASE: 1;
            const unsigned long VECTPENDING: 10;
            const unsigned long ISRPENDING: 1;
            const unsigned long RESERVED: 2;
            unsigned long PENDSTCLR: 1;
            unsigned long PENDSTSET: 1;
            unsigned long PENDSVCLR: 1;
            unsigned long PENDSVSET: 1;
            const unsigned long RESERVED: 2;
            unsigned long NMIPENDSET: 1;

        };
        unsigned long REG;
    } ICSR;

    volatile union {
        struct {
            const unsigned long RESERVED: 9;
            unsigned long TBLOFF: 21;
            const unsigned long RESERVED: 2;

        };
        unsigned long REG;
    } VTOR;

    volatile union {
        struct {
            unsigned long VECTRESET: 1;
            unsigned long VECTCLRACTIVE: 1;
            unsigned long SYSRESETREQ: 1;
            const unsigned long RESERVED: 5;
            unsigned long PRIGROUP: 3;
            const unsigned long RESERVED: 4;
            const unsigned long ENDIANESS: 1;
            unsigned long VECTKEY: 16;
        };
        unsigned long REG;
    } AIRCR;

    volatile union {

        struct {
            const unsigned long            : 1;
            unsigned long SLEEPONEXIT: 1;
            unsigned long SLEEPDEEP: 1;
            const unsigned long RESERVED: 1;
            unsigned long SEVONPEND: 1;
            const unsigned long RESERVED: 27;
        };
        unsigned long REG;
    } SCR;


    volatile union {
        struct {
            unsigned long NONBASETHRDENA: 1;
            unsigned long USERSETMPEND: 1;
            const unsigned long RESERVED: 1;
            unsigned long UNALIGN_TRP: 1;
            unsigned long DIV_0_TRP: 1;
            const unsigned long RESERVED: 3;
            unsigned long BFHFNMIGN: 1;
            unsigned long STKALIGN: 1;
            const unsigned long RESERVED: 22;
        };
        unsigned long REG;
    } CCR;

    volatile union {
        struct {
            unsigned long MemoryManagementFaultPriority: 8;
            unsigned long BusFaultPriority: 8;
            unsigned long UsageFaultPriority: 8;
            const unsigned long RESERVED: 8;
        };

        struct {
            unsigned long PRI_4: 8;
            unsigned long PRI_5: 8;
            unsigned long PRI_6: 8;
            const unsigned long RESERVED: 8;
        };

        struct {
            const unsigned long PRI_4_L: 4;
            unsigned long PRI_4_H: 4;
            const unsigned long PRI_5_L: 4;
            unsigned long PRI_5_H: 4;
            const unsigned long PRI_6_L: 4;
            unsigned long PRI_6_H: 4;
            const unsigned long RESERVED: 8;
        };
        unsigned long REG;
    } SHPR1;


    volatile union {

        struct {
            const unsigned long RESERVED: 24;
            const unsigned long PRI_11_L: 4;
            unsigned long PRI_11_H: 4;
        };
        struct {
            const unsigned long RESERVED: 24;
            unsigned long SVCallPriority: 8;
        };
        unsigned long REG;

    } SHPR2;


    volatile union {


        struct {
            const unsigned long RESERVED: 16;
            unsigned long PendSVPriority: 8;
            unsigned long SysTicPriority: 8;
        };

        struct {
            const unsigned long RESERVED: 16;
            unsigned long PRI_14: 8;
            unsigned long PRI_15: 8;
        };

        struct {
            const unsigned long RESERVED: 16;
            const unsigned long PRI_14_L: 4;
            unsigned long PRI_14_H: 4;
            const unsigned long PRI_15_L: 4;
            unsigned long PRI_15_H: 4;

        };


        unsigned long REG;
    } SHPR3;


    volatile union {

        struct {
            unsigned long MEMFAULTACT: 1;
            unsigned long BUSFAULTACT: 1;
            const unsigned long RESERVED: 1;
            unsigned long USGFAULT: 1;
            const unsigned long RESERVED: 3;
            unsigned long SVCALLACT: 1;
            unsigned long MONITORACT: 1;
            const unsigned long RESERVED: 1;
            unsigned long PENDSVACT: 1;
            unsigned long SYSTICKACT: 1;
            unsigned long USGFAULTPENDED: 1;
            unsigned long MEMFAULTPENDED: 1;
            unsigned long BUSFAULTPENDED: 1;
            unsigned long SVCALLPENDED: 1;
            unsigned long MEMFAULTENA: 1;
            unsigned long BUSFAULTENA: 1;
            unsigned long USGFAULTENA: 1;
            const unsigned long                : 13;

        };
        unsigned long REG;
    } SHCSR;

    volatile union {

        struct {
            unsigned long IACCVIOL: 1;
            unsigned long DACCVIOL: 1;
            const unsigned long RESERVED: 1;
            unsigned long MUNSTKERR: 1;
            unsigned long MSTKERR: 1;
            const unsigned long RESERVED: 2;
            unsigned long MMARVALID: 1;
            unsigned long IBUSERR: 1;
            unsigned long PRECISERR: 1;
            unsigned long IMPRECISERR: 1;
            unsigned long UNSTKERR: 1;
            unsigned long STKERR: 1;
            const unsigned long RESERVED: 2;
            unsigned long BFARVALID: 1;
            unsigned long UNDEFINSTR: 1;
            unsigned long INVSTATE: 1;
            unsigned long INVPC: 1;
            unsigned long NOCP: 1;
            const unsigned long RESERVED: 4;
            unsigned long UNALIGNED: 1;
            unsigned long DIVBYZERO: 1;
            const unsigned long RESERVED: 6;


        };

        struct {
            uint8_t MMFSR;
            uint8_t BFSR;
            uint16_t UFSR;
        };
        unsigned long REG;

    } CFSR;

    volatile union {

        struct {
            const unsigned long RESERVED: 1;
            unsigned long VECTTBL: 1;
            const unsigned long RESERVED: 28;
            unsigned long FORCED: 1;
            unsigned long DEBUG_VT: 1;

        };

        unsigned long REG;
    } HFSR;

    const unsigned long RESERVED; // Due to Offset

    volatile union {
        unsigned long REG;
    } MMFAR;

    volatile union {
        unsigned long REG;
    } BFAR;


} SCB_t;



/***************** 4- SCB->Registers_Values_Definitions *****/
/***************** 4.1- SCB->  ***************/
/***************** 4.2- SCB->  ***************/
/***************** 4.3- SCB->  ***************/
/***************** 4.4- SCB->AIRCR  ***************/


#define SCB_PRIORITY_GROUP0       (0)

#define SCB_PRIORITY_GROUP1       (1)

#define SCB_PRIORITY_GROUP2       (2)

#define SCB_PRIORITY_GROUP3       (3)

#define SCB_PRIORITY_GROUP4       (4)

#define SCB_PRIORITY_GROUP5       (5)

#define SCB_PRIORITY_GROUP6       (6)

#define SCB_PRIORITY_GROUP7       (7)


/***************** 4.5- SCB->VTOR  ***************/
#define SCB_VTOR_MASK  (0x3FFFFE00)
/***************** 4.6- SCB->  ***************/



/***************************************************************/
/*					    	(2) SYSTICK						   */
/***************************************************************/

/*
 * 	STK Section Architecture Map
 *		1- STK->Base_Definitions
 *		2- STK->Registers_Pointers
 *		3- STK->Struct_Definition
 *		4- STK->Registers_Values_Definitions
 *			4.1-
 *
 *
 * */


/***************** 1- STK->Base_Defintion ***************/

#define pSTK_BASE        (0xE000E010U)

#define pSTK_CTRL_BASE    (pSTK_BASE + 0x00U)
#define pSTK_LOAD_BASE    (pSTK_BASE + 0x00U)
#define pSTK_VAL_BASE    (pSTK_BASE + 0x08U)
#define pSTK_CALIB_BASE    (pSTK_BASE + 0x0CU)

/***************** 2- STK->Registers_Pointers ***************/

#define pSTK_CTRL    (*((volatile unsigned long *) pSTK_CTRL_BASE))
#define pSTK_LOAD    (*((volatile unsigned long *) pSTK_LOAD_BASE))
#define pSTK_VAL        (*((volatile unsigned long *) pSTK_VAL_BASE))
#define pSTK_CALIB    (*((volatile unsigned long *) pSTK_CALIB_BASE))

/***************** 3- STK->Struct_Definition ***************/

#define pSTK            ((volatile pSTK_t *) pSTK_BASE)


typedef volatile struct {

    volatile union {

        struct {
            unsigned long ENABLE: 1;
            unsigned long TICKINT: 1;
            unsigned long CLKSOURCE: 1;
            const unsigned long RESERVED: 13;
            unsigned long COUNTFLAG: 1;
            const unsigned long RESERVED: 15;
        };
        unsigned long REG;
    } CTRL;

    volatile union {

        unsigned long RELOAD: 24;
        unsigned long REG;
    } LOAD;

    volatile union {
        unsigned long CURRENT: 24;
        unsigned long REG;
    } VAL;


    volatile union {
        struct {
            const unsigned long TENMS: 24;
            const unsigned long                : 6;
            const unsigned long SKEW: 1;
            const unsigned long NOREF: 1;
        };

        unsigned long REG;

    } CALIB;
} pSTK_t;


/***************** 4- STK->Registers_Values_Definitions ***************/

#define pSTK_ENABLE_ON                    (1)
#define pSTK_ENABLE_OFF                    (0)

#define pSTK_TICKINT_ON                    (1)
#define pSTK_TICKINT_OFF                    (0)

#define pSTK_CLKSOURCE_AHB_DIV_BY_8        (0)
#define pSTK_CLKSOURCE_AHB                (1)

#define pSTK_COUNTFLAG_COUNTED            (1)





/***************************************************************/
/*					    	(3) NVIC						   */
/***************************************************************/

/*
 * 	NVIC Section Architecture Map
 *		1- NVIC->Base_Definitions
 *		2- NVIC->Registers_Pointers
 *		3- NVIC->Struct_Definition
 *		4- NVIC->Registers_Values_Definitions
 *			4.1-
 *
 *
 * */


/***************** 1- NVIC->Base_Defintion ***************/

#define pNVIC_BASE            (0xE000E100U)

#define pNVIC_ISER0_BASE        (pNVIC_BASE + 0x000U)
#define pNVIC_ISER1_BASE        (pNVIC_BASE + 0x004U)
#define pNVIC_ISER2_BASE        (pNVIC_BASE + 0x008U)

#define pNVIC_ICER0_BASE        (pNVIC_BASE + 0x080U)
#define pNVIC_ICER1_BASE        (pNVIC_BASE + 0x084U)
#define pNVIC_ICER2_BASE        (pNVIC_BASE + 0x088U)

#define pNVIC_ISPR0_BASE        (pNVIC_BASE + 0x100U)
#define pNVIC_ISPR1_BASE        (pNVIC_BASE + 0x104U)
#define pNVIC_ISPR2_BASE        (pNVIC_BASE + 0x108U)

#define pNVIC_ICPR0_BASE        (pNVIC_BASE + 0x180U)
#define pNVIC_ICPR1_BASE        (pNVIC_BASE + 0x184U)
#define pNVIC_ICPR2_BASE        (pNVIC_BASE + 0x188U)

#define pNVIC_IABR0_BASE        (pNVIC_BASE + 0x200U)
#define pNVIC_IABR1_BASE        (pNVIC_BASE + 0x204U)
#define pNVIC_IABR2_BASE        (pNVIC_BASE + 0x208U)

#define pNVIC_IPR0_BASE        (pNVIC_BASE + 0x300U    + 4*0)
#define pNVIC_IPR1_BASE        (pNVIC_BASE + 0x300U    + 4*1)
#define pNVIC_IPR2_BASE        (pNVIC_BASE + 0x300U    + 4*2)
#define pNVIC_IPR3_BASE        (pNVIC_BASE + 0x300U    + 4*3)
#define pNVIC_IPR4_BASE        (pNVIC_BASE + 0x300U    + 4*4)
#define pNVIC_IPR5_BASE        (pNVIC_BASE + 0x300U    + 4*5)
#define pNVIC_IPR6_BASE        (pNVIC_BASE + 0x300U    + 4*6)
#define pNVIC_IPR7_BASE        (pNVIC_BASE + 0x300U    + 4*7)
#define pNVIC_IPR8_BASE        (pNVIC_BASE + 0x300U    + 4*8)
#define pNVIC_IPR9_BASE        (pNVIC_BASE + 0x300U    + 4*9)
#define pNVIC_IPR10_BASE        (pNVIC_BASE + 0x300U    + 4*10)
#define pNVIC_IPR11_BASE        (pNVIC_BASE + 0x300U    + 4*11)
#define pNVIC_IPR12_BASE        (pNVIC_BASE + 0x300U    + 4*12)
#define pNVIC_IPR13_BASE        (pNVIC_BASE + 0x300U    + 4*13)
#define pNVIC_IPR14_BASE        (pNVIC_BASE + 0x300U    + 4*14)
#define pNVIC_IPR15_BASE        (pNVIC_BASE + 0x300U    + 4*15)
#define pNVIC_IPR16_BASE        (pNVIC_BASE + 0x300U    + 4*16)
#define pNVIC_IPR17_BASE        (pNVIC_BASE + 0x300U    + 4*17)
#define pNVIC_IPR18_BASE        (pNVIC_BASE + 0x300U    + 4*18)
#define pNVIC_IPR19_BASE        (pNVIC_BASE + 0x300U    + 4*19)
#define pNVIC_IPR20_BASE        (pNVIC_BASE + 0x300U    + 4*20)

#define pNVIC_STIR_BASE        (pNVIC_BASE + 0xE00U)


/***************** 2- NVIC->Registers_Pointers ***************/

#define pNVIC_ISER0        (*((volatile unsigned long *)pNVIC_ISER0_BASE))
#define pNVIC_ISER1        (*((volatile unsigned long *)pNVIC_ISER1_BASE))
#define pNVIC_ISER2        (*((volatile unsigned long *)pNVIC_ISER2_BASE))

#define pNVIC_ICER0        (*((volatile unsigned long *)pNVIC_ICER0_BASE))
#define pNVIC_ICER1        (*((volatile unsigned long *)pNVIC_ICER1_BASE))
#define pNVIC_ICER2        (*((volatile unsigned long *)pNVIC_ICER2_BASE))

#define pNVIC_ISPR0        (*((volatile unsigned long *)pNVIC_ISPR0_BASE))
#define pNVIC_ISPR1        (*((volatile unsigned long *)pNVIC_ISPR1_BASE))
#define pNVIC_ISPR2        (*((volatile unsigned long *)pNVIC_ISPR2_BASE))

#define pNVIC_ICPR0        (*((volatile unsigned long *)pNVIC_ICPR0_BASE))
#define pNVIC_ICPR1        (*((volatile unsigned long *)pNVIC_ICPR1_BASE))
#define pNVIC_ICPR2        (*((volatile unsigned long *)pNVIC_ICPR2_BASE))

#define pNVIC_IABR0        (*((volatile unsigned long *)pNVIC_IABR0_BASE))
#define pNVIC_IABR1        (*((volatile unsigned long *)pNVIC_IABR1_BASE))
#define pNVIC_IABR2        (*((volatile unsigned long *)pNVIC_IABR2_BASE))


#define pNVIC_IPR0        (*((volatile unsigned long *)pNVIC_IPR0_BASE))
#define pNVIC_IPR1        (*((volatile unsigned long *)pNVIC_IPR1_BASE))
#define pNVIC_IPR2        (*((volatile unsigned long *)pNVIC_IPR2_BASE))
#define pNVIC_IPR3        (*((volatile unsigned long *)pNVIC_IPR3_BASE))
#define pNVIC_IPR4        (*((volatile unsigned long *)pNVIC_IPR4_BASE))
#define pNVIC_IPR5        (*((volatile unsigned long *)pNVIC_IPR5_BASE))
#define pNVIC_IPR6        (*((volatile unsigned long *)pNVIC_IPR6_BASE))
#define pNVIC_IPR7        (*((volatile unsigned long *)pNVIC_IPR7_BASE))
#define pNVIC_IPR8        (*((volatile unsigned long *)pNVIC_IPR8_BASE))
#define pNVIC_IPR9        (*((volatile unsigned long *)pNVIC_IPR9_BASE))
#define pNVIC_IPR10        (*((volatile unsigned long *)pNVIC_IPR10_BASE))
#define pNVIC_IPR11        (*((volatile unsigned long *)pNVIC_IPR11_BASE))
#define pNVIC_IPR12        (*((volatile unsigned long *)pNVIC_IPR12_BASE))
#define pNVIC_IPR13        (*((volatile unsigned long *)pNVIC_IPR13_BASE))
#define pNVIC_IPR14        (*((volatile unsigned long *)pNVIC_IPR14_BASE))
#define pNVIC_IPR15        (*((volatile unsigned long *)pNVIC_IPR15_BASE))
#define pNVIC_IPR16        (*((volatile unsigned long *)pNVIC_IPR16_BASE))
#define pNVIC_IPR17        (*((volatile unsigned long *)pNVIC_IPR17_BASE))
#define pNVIC_IPR18        (*((volatile unsigned long *)pNVIC_IPR18_BASE))
#define pNVIC_IPR19        (*((volatile unsigned long *)pNVIC_IPR19_BASE))
#define pNVIC_IPR20        (*((volatile unsigned long *)pNVIC_IPR20_BASE))

#define pNVIC_STIR        (*((volatile unsigned long *)pNVIC_STIR_BASE))


/***************** 3- NVIC->Struct_Definition ***************/



typedef volatile union {

    volatile struct {
        struct {
            unsigned long REG;
        } ISERs[3];

        const unsigned long RESERVED[29];

        struct {
            unsigned long REG;
        } ICERs[3];

        const unsigned long RESERVED[29];

        struct {
            unsigned long REG;
        } ISPRs[3];

        const unsigned long RESERVED[29];

        struct {
            unsigned long REG;
        } ICPRs[3];

        const unsigned long RESERVED[29];

        struct {
            unsigned long REG;
        } IABRs[3];

        const unsigned long RESERVED[61];

        union {
            struct {
                uint8_t IP_LOW: 4;
                uint8_t IP_HIGH: 4;
            };

            uint8_t IP;
        } IPs[81];

        const uint8_t RESERVED[3];
        const unsigned long RESERVED[683];


    } All;

    struct {

        struct {
            unsigned long REG;
        } ISER0;

        struct {
            unsigned long REG;
        } ISER1;

        struct {
            unsigned long REG;
        } ISER2;

        const unsigned long RESERVED[29];


        struct {
            unsigned long REG;
        } ICER0;

        struct {
            unsigned long REG;
        } ICER1;

        struct {
            unsigned long REG;
        } ICER2;

        const unsigned long RESERVED[29];

        struct {
            unsigned long REG;
        } ISPR0;

        struct {
            unsigned long REG;
        } ISPR1;

        struct {
            unsigned long REG;
        } ISPR2;


        const unsigned long RESERVED[29];


        struct {
            unsigned long REG;
        } ICPR0;

        struct {
            unsigned long REG;
        } ICPR1;

        struct {
            unsigned long REG;
        } ICPR2;


        const unsigned long RESERVED[29];


        struct {
            unsigned long REG;
        } IABR0;

        struct {
            unsigned long REG;
        } IABR1;

        struct {
            unsigned long REG;
        } IABR2;


        const unsigned long RESERVED[61];

        struct {
            unsigned long REG;
        } IPRs[21];


        const unsigned long RESERVED[683];

        volatile union {
            unsigned long INTID: 9;
            unsigned long REG;
        } STIR;
    };

} pNVIC_t;

#define pNVIC           ((volatile pNVIC_t *) pNVIC_BASE)

/***************** 4- NVIC->Registers_Values_Definitions *****/
/***************** 4.1- NVIC->ISERx,ICERx  ***************/

#define pNVIC_IRQn_WWDG                    (0)
#define pNVIC_IRQn_PVD                     (1)
#define pNVIC_IRQn_TAMPER                  (2)
#define pNVIC_IRQn_RTC                     (3)
#define pNVIC_IRQn_FLASH                   (4)
#define pNVIC_IRQn_RCC                     (5)
#define pNVIC_IRQn_EXTI0                   (6)
#define pNVIC_IRQn_EXTI1                   (7)
#define pNVIC_IRQn_EXTI2                   (8)
#define pNVIC_IRQn_EXTI3                   (9)
#define pNVIC_IRQn_EXTI4                   (10)
#define pNVIC_IRQn_DMA1_Channel1           (11)
#define pNVIC_IRQn_DMA1_Channel2           (12)
#define pNVIC_IRQn_DMA1_Channel3           (13)
#define pNVIC_IRQn_DMA1_Channel4           (14)
#define pNVIC_IRQn_DMA1_Channel5           (15)
#define pNVIC_IRQn_DMA1_Channel6           (16)
#define pNVIC_IRQn_DMA1_Channel7           (17)
#define pNVIC_IRQn_ADC1_2                  (18)
#define pNVIC_IRQn_CAN1_TX                 (19)
#define pNVIC_IRQn_CAN1_RX0                (20)
#define pNVIC_IRQn_CAN1_RX1                (21)
#define pNVIC_IRQn_CAN1_SCE                (22)
#define pNVIC_IRQn_EXTI9_5                 (23)
#define pNVIC_IRQn_TIM1_BRK                (24)
#define pNVIC_IRQn_TIM1_UP                 (25)
#define pNVIC_IRQn_TIM1_TRG_COM            (26)
#define pNVIC_IRQn_TIM1_CC                 (27)
#define pNVIC_IRQn_TIM2                    (28)
#define pNVIC_IRQn_TIM3                    (29)
#define pNVIC_IRQn_TIM4                    (30)
#define pNVIC_IRQn_I2C1_EV                 (31)
#define pNVIC_IRQn_I2C1_ER                 (32)
#define pNVIC_IRQn_I2C2_EV                 (33)
#define pNVIC_IRQn_I2C2_ER                 (34)
#define pNVIC_IRQn_SPI1                    (35)
#define pNVIC_IRQn_SPI2                    (36)
#define pNVIC_IRQn_USART1                  (37)
#define pNVIC_IRQn_USART2                  (38)
#define pNVIC_IRQn_USART3                  (39)
#define pNVIC_IRQn_EXTI15_10               (40)
#define pNVIC_IRQn_RTCAlarm                (41)
#define pNVIC_IRQn_OTG_FS_WKUP             (42)
#define pNVIC_IRQn_TIM5                    (50)
#define pNVIC_IRQn_SPI3                    (51)
#define pNVIC_IRQn_UART4                   (52)
#define pNVIC_IRQn_UART5                   (53)
#define pNVIC_IRQn_TIM6                    (54)
#define pNVIC_IRQn_TIM7                    (55)
#define pNVIC_IRQn_DMA2_Channel1           (56)
#define pNVIC_IRQn_DMA2_Channel2           (57)
#define pNVIC_IRQn_DMA2_Channel3           (58)
#define pNVIC_IRQn_DMA2_Channel4           (59)
#define pNVIC_IRQn_DMA2_Channel5           (60)
#define pNVIC_IRQn_ETH                     (61)
#define pNVIC_IRQn_ETH_WKUP                (62)
#define pNVIC_IRQn_CAN2_TX                 (63)
#define pNVIC_IRQn_CAN2_RX0                (64)
#define pNVIC_IRQn_CAN2_RX1                (65)
#define pNVIC_IRQn_CAN2_SCE                (66)
#define pNVIC_IRQn_OTG_FS                  (67)


/***************** 4.2- NVIC->  ***************/
/***************** 4.3- NVIC->  ***************/
/***************** 4.4- NVIC->IPRx  ***************/

/***************** 4.5- NVIC->  ***************/
/***************** 4.6- NVIC->  ***************/




/***************************************************************/
/*					    	(4) MPU							   */
/***************************************************************/

/*
 * 	MPU Section Architecture Map
 *		1- MPU->Base_Definitions
 *		2- MPU->Registers_Pointers
 *		3- MPU->Struct_Definition
 *		4- MPU->Registers_Values_Definitions
 *			4.1-
 *
 *
 * */


/***************** 1- MPU->Base_Definition ******************/

#define MPU_BASE            (0xE000ED90)

#define MPU_TYPER_BASE      (MPU_BASE + 0x00)
#define MPU_CR_BASE         (MPU_BASE + 0x04)
#define MPU_RNR_BASE        (MPU_BASE + 0x08)
#define MPU_RBAR_BASE       (MPU_BASE + 0x0C)
#define MPU_RASR_BASE       (MPU_BASE + 0x10)

/***************** 2- MPU->Registers_Pointers ***************/

#define MPU_TYPER       (*((volatile unsigned long *)MPU_TYPER_BASE))
#define MPU_CR          (*((volatile unsigned long *)MPU_CR_BASE))
#define MPU_RNR         (*((volatile unsigned long *)MPU_RNR_BASE))
#define MPU_RBAR        (*((volatile unsigned long *)MPU_RBAR_BASE))
#define MPU_RASR        (*((volatile unsigned long *)MPU_RASR_BASE))

/***************** 3- MPU->Struct_Definition ****************/

#define MPU             ((*volatile MPU_t *)MPU_BASE)

typedef volatile struct {
    volatile union {
        struct {
            const unsigned long SEPARATE: 1;
            const unsigned long RESERVED: 7;
            const unsigned long DREGION: 8;
            const unsigned long IREGION: 8;
            const unsigned long RESERVED: 8;
        };
        unsigned long REG;
    } TYPER;

    volatile union {
        struct {
            unsigned long ENABLE: 1;
            unsigned long HFNMIENA: 1;
            unsigned long PRIVDEFENA: 1;
            const unsigned long RESERVED: 29;
        };
        unsigned long REG;
    } CR;

    volatile union {
        struct {
            unsigned long REGION: 8;
            const unsigned long      : 24;
        };
        unsigned long REG;
    } RNR;

    volatile union {
        struct {
            unsigned long REGION: 4;
            unsigned long VALID: 1;
            unsigned long ADDR: 27;
        };
        unsigned long REG;
    } RBAR;

    volatile union {
        struct {
            unsigned long ENABLE: 1;
            unsigned long SIZE: 5;
            const unsigned long      : 2;
            unsigned long SRD: 8;
            unsigned long B: 1;
            unsigned long C: 1;
            unsigned long S: 1;
            unsigned long TEX: 3;
            const unsigned long      : 2;
            unsigned long AP: 3;
            const unsigned long      : 1;
            unsigned long XN: 1;
            const unsigned long      : 3;
        };

        unsigned long REG;
    } RASR;

} MPU_t;

/***************** 4- MPU->Registers_Values_Definitions *****/

#define MPU_SEPARATE_UNIFIED            (0)
#define MPU_SEPARATE_SEPARATE           (1)

#define MPU_DREGION_EIGHT_MPU_REGIONS   (0x08)
#define MPU_DREGION_MPU_NOT_PRESENT     (0)


#define MPU_ENABLE_ON       (1)
#define MPU_ENABLE_OFF      (0)

#define MPU_HFNMIENA_DISABLE_MPU_DURING_HF_NMI    (0)
#define MPU_HFNMIENA_ENABLE_MPU_DURING_HF_NMI     (1)

#define MPU_PRIVDEFENA_DISABLE_USE_OF_DEFAULT_MEM_MAP   (0)
#define MPU_PRIVDEFENA_ENABLE_USE_OF_DEFAULT_MEM_MAP    (1)


#define MPU_VALID_YES   (0)
#define MPU_VALID_NO    (1)


#define MPU_SRD_SUB_REGION_1_ENABLE     (0b00000001)
#define MPU_SRD_SUB_REGION_2_ENABLE     (0b00000010)
#define MPU_SRD_SUB_REGION_3_ENABLE     (0b00000100)
#define MPU_SRD_SUB_REGION_4_ENABLE     (0b00001000)
#define MPU_SRD_SUB_REGION_5_ENABLE     (0b00010000)
#define MPU_SRD_SUB_REGION_6_ENABLE     (0b00100000)
#define MPU_SRD_SUB_REGION_7_ENABLE     (0b01000000)
#define MPU_SRD_SUB_REGION_8_ENABLE     (0b10000000)

#define MPU_XN_INS_FETCH_ENABLE         (0)
#define MPU_XN_INS_FETCH_DISABLE        (1)


/***************************************************************/
/*					    	(5) RCC							   */
/***************************************************************/


/*
 * 	RCC Section Architecture Map
 *		1- RCC->Base_Definitions
 *		2- RCC->Registers_Pointers
 *		3- RCC->Struct_Definition
 *		4- RCC->Registers_Values_Definitions
 *			4.1- RCC->CR
 *			4.2- RCC->CFGR
 *			4.3- RCC->CIR
 *			4.4- RCC->APB2RSTR
 *			4.5- RCC->APB1RSTR
 *			4.6- RCC->AHBENR
 *			4.7- RCC->APB2ENR
 *			4.8- RCC->APB1ENR
 *			4.9- RCC->BDCR
 *			4.10- RCC->CSR
 *
 *
 * */


/***************** 1- RCC->Base_Definition ***************/
#define RCC_BASE                (0x40021000)
#define RCC_CR_BASE                (RCC_BASE + 0x00)
#define RCC_CFGR_BASE            (RCC_BASE + 0x04)
#define RCC_CIR_BASE            (RCC_BASE + 0x08)
#define RCC_APB2RSTR_BASE        (RCC_BASE + 0x0C)
#define RCC_APB1RSTR_BASE        (RCC_BASE + 0x10)
#define RCC_AHBENR_BASE            (RCC_BASE + 0x14)
#define RCC_APB2ENR_BASE        (RCC_BASE + 0x18)
#define RCC_APB1ENR_BASE        (RCC_BASE + 0x1C)
#define RCC_BDCR_BASE            (RCC_BASE + 0x20)
#define RCC_CSR_BASE            (RCC_BASE + 0x24)


/***************** 2- RCC->Registers_Pointers ***************/


#define RCC_CR                    (*((volatile unsigned long *)RCC_CR_BASE))
#define RCC_CFGR                (*((volatile unsigned long *)RCC_CFGR_BASE))
#define RCC_CIR                    (*((volatile unsigned long *)RCC_CIR_BASE))
#define RCC_APB2RSTR            (*((volatile unsigned long *)RCC_APB2RSTR_BASE))
#define RCC_APB1RSTR            (*((volatile unsigned long *)RCC_APB1RSTR_BASE))
#define RCC_AHBENR                (*((volatile unsigned long *)RCC_AHBENR_BASE))
#define RCC_APB2ENR                (*((volatile unsigned long *)RCC_APB2ENR_BASE))
#define RCC_APB1ENR                (*((volatile unsigned long *)RCC_APB1ENR_BASE))
#define RCC_BDCR                (*((volatile unsigned long *)RCC_BDCR))
#define RCC_CSR                    (*((volatile unsigned long *)RCC_CSR))



/***************** 3- RCC->Struct_Definition ***************/

#define RCC                        ((volatile RCC_t *)RCC_BASE)


typedef union {

    volatile struct {
        const unsigned long RESERVED[5];
        struct {
            unsigned long REG;
        } ClockEnableRegisters[3];
    };

    volatile struct {
        union {
            volatile struct {
                unsigned long HSION: 1;
                unsigned long HSIRDY: 1;
                const unsigned long                : 1;
                unsigned long HSITRIM: 5;
                const unsigned long HSICAL: 8;
                unsigned long HSEON: 1;
                unsigned long HSERDY: 1;
                unsigned long HSEBYP: 1;
                unsigned long CSSON: 1;
                const unsigned long                : 4;
                unsigned long PLLON: 1;
                unsigned long PLLRDY: 1;
                const unsigned long                : 6;
            };
            volatile unsigned long REG;
        } CR;

        volatile union {
            struct {
                unsigned long SW: 2;
                const unsigned long SWS: 2;
                unsigned long HPRE: 4;
                unsigned long PPRE1: 3;
                unsigned long PPRE2: 3;
                unsigned long ADCPRE: 2;
                unsigned long PLLSRC: 1;
                unsigned long PLLXTPRE: 1;
                unsigned long PLLMUL: 4;
                unsigned long USBPRE: 1;
                const unsigned long        : 1;
                unsigned long MCO: 3;
                unsigned long            : 5;

            };
            volatile unsigned long REG;
        } CFGR;

        union {
            volatile struct {

                const unsigned long LSIRDYF: 1;
                const unsigned long LSERDYF: 1;
                const unsigned long HSIRDYF: 1;
                const unsigned long HSERDYF: 1;
                const unsigned long PLLRDYF: 1;
                const unsigned long                : 2;
                const unsigned long CSSF: 1;
                unsigned long LSIRDYIE: 1;
                unsigned long LSERDYIE: 1;
                unsigned long HSI_RDYIE: 1;
                unsigned long HSE_RDYIE: 1;
                unsigned long PLL_RDYIE: 1;
                const unsigned long                : 3;
                unsigned long LSIRDYC: 1;
                unsigned long LSERDYC: 1;
                unsigned long HSIRDYC: 1;
                unsigned long HSERDYC: 1;
                unsigned long PLLRDYC: 1;
                const unsigned long                : 2;
                unsigned long CSSC: 1;
                const unsigned long                : 8;
            };
            volatile unsigned long REG;
        } CIR;

        union {
            volatile struct {
                unsigned long AFIORST: 1;
                const unsigned long            : 1;
                unsigned long IOPARST: 1;
                unsigned long IOPBRST: 1;
                unsigned long IOPCRST: 1;
                unsigned long IOPDRST: 1;
                unsigned long IOPERST: 1;
                unsigned long IOPFRST: 1;
                unsigned long IOPGRST: 1;
                unsigned long ADC1RST: 1;
                unsigned long ADC2RST: 1;
                unsigned long TIM1RST: 1;
                unsigned long SPI1RST: 1;
                unsigned long TIM8RST: 1;
                unsigned long USART1RST: 1;
                unsigned long ADC3RST: 1;
                const unsigned long            : 3;
                unsigned long TIM9RST: 1;
                unsigned long TIM10RST: 1;
                unsigned long TIM11RST: 1;
                const unsigned long            : 10;
            };
            volatile unsigned long REG;

        } APB2RSTR;

        union {
            volatile struct {
                unsigned long TIM2RST: 1;
                unsigned long TIM3RST: 1;
                unsigned long TIM4RST: 1;
                unsigned long TIM5RST: 1;
                unsigned long TIM6RST: 1;
                unsigned long TIM7RST: 1;
                unsigned long TIM12RST: 1;
                unsigned long TIM13RST: 1;
                unsigned long TIM14RST: 1;
                const unsigned long            : 2;
                unsigned long WWDGRST: 1;
                const unsigned long            : 2;
                unsigned long SPI2RST: 1;
                unsigned long SPI3RST: 1;
                const unsigned long            : 1;
                unsigned long USART2RST: 1;
                unsigned long USART3RST: 1;
                unsigned long UART4RST: 1;
                unsigned long UART5RST: 1;
                unsigned long I2C1RST: 1;
                unsigned long I2C2RST: 1;
                unsigned long USBRST: 1;
                const unsigned long            : 1;
                unsigned long CANRST: 1;
                const unsigned long            : 1;
                unsigned long BKPRST: 1;
                unsigned long PWRRST: 1;
                unsigned long DAC_RST: 1;
                const unsigned long            : 2;
            };
            volatile unsigned long REG;


        } APB1RSTR;


        union {

            volatile struct {
                unsigned long DMA1EN: 1;
                unsigned long DMA2EN: 1;
                unsigned long SRAMEN: 1;
                const unsigned long        : 1;
                unsigned long FLITFEN: 1;
                const unsigned long        : 1;
                unsigned long CRCEN: 1;
                const unsigned long        : 1;
                unsigned long FSMCEN: 1;
                const unsigned long        : 1;
                unsigned long SDIOEN: 1;
                unsigned long            : 21;
            };

            volatile unsigned long REG;


        } AHBENR;

        union {
            volatile struct {
                unsigned long AFIOEN: 1;
                const unsigned long        : 1;
                unsigned long IOPAEN: 1;
                unsigned long IOPBEN: 1;
                unsigned long IOPCEN: 1;
                unsigned long IOPDEN: 1;
                unsigned long IOPEEN: 1;
                unsigned long IOPFEN: 1;
                unsigned long IOPGEN: 1;
                unsigned long ADC1EN: 1;
                unsigned long ADC2EN: 1;
                unsigned long TIM1EN: 1;
                unsigned long SPI1EN: 1;
                unsigned long TIM8EN: 1;
                unsigned long USART1EN: 1;
                unsigned long ADC3EN: 1;
                const unsigned long        : 3;
                unsigned long TIM9EN: 1;
                unsigned long TIM10EN: 1;
                unsigned long TIM11EN: 1;
                const unsigned long        : 10;

            };
            volatile unsigned long REG;

        } APB2ENR;


        union {
            volatile struct {
                unsigned long TIM2EN: 1;
                unsigned long TIM3EN: 1;
                unsigned long TIM4EN: 1;
                unsigned long TIM5EN: 1;
                unsigned long TIM6EN: 1;
                unsigned long TIM7EN: 1;
                unsigned long TIM12EN: 1;
                unsigned long TIM13EN: 1;
                unsigned long TIM14EN: 1;
                const unsigned long                : 2;
                unsigned long WWDGEN: 1;
                const unsigned long                : 2;
                unsigned long SPI2EN: 1;
                unsigned long SPI3EN: 1;
                const unsigned long                : 1;
                unsigned long USART2EN: 1;
                unsigned long USART3EN: 1;
                unsigned long UART4EN: 1;
                unsigned long UART5EN: 1;
                unsigned long I2C1EN: 1;
                unsigned long I2C2EN: 1;
                unsigned long USBEN: 1;
                const unsigned long                : 1;
                unsigned long CANEN: 1;
                const unsigned long                : 1;
                unsigned long BKPEN: 1;
                unsigned long PWREN: 1;
                unsigned long DACEN: 1;
                const unsigned long                : 2;

            };
            volatile unsigned long REG;

        } APB1ENR;


        union {
            volatile struct {

                unsigned long LSEON: 1;
                const unsigned long LSERDY: 1;
                unsigned long LSEBYP: 1;
                const unsigned long            : 5;
                unsigned long RTCSEL: 2;
                const unsigned long            : 5;
                unsigned long RTCEN: 1;
                unsigned long BDRST: 1;
                const unsigned long            : 15;
            };
            volatile unsigned long REG;


        } BDCR;


        union {
            volatile struct {
                unsigned long LSION: 1;
                const unsigned long LSIRDY: 1;
                const unsigned long            : 22;
                unsigned long RMVF: 1;
                const unsigned long            : 1;
                unsigned long PINRSTF: 1;
                unsigned long PORRSTF: 1;
                unsigned long SFTRSTF: 1;
                unsigned long IWDGRSTF: 1;
                unsigned long WWDGRSTF: 1;
                unsigned long LPWRRSTF: 1;

            };
            volatile unsigned long REG;


        } CSR;
    };
} RCC_t;


/***************** 4.1- RCC->CR ***************/


#define RCC_HSION_ENABLE        (1)
#define RCC_HSION_DISABLE        (0)

#define RCC_HSIRDY_READY        (1)
#define RCC_HSIRDY_NOT_READY    (0)

#define RCC_HSITRIM_DEFAULT        (16)

#define RCC_HSEON_ENABLE        (1)
#define RCC_HSEON_DISABLE        (0)

#define RCC_HSERDY_READY        (1)
#define RCC_HSERDY_NOT_READY    (0)

#define RCC_HSEBYP_BYPASS        (1)
#define RCC_HSEBYP_DONT_BYPASS    (0)

#define RCC_CSSON_ENABLE        (1)
#define RCC_CSSON_DISABLE        (0)

#define RCC_PLLON_ENABLE        (1)
#define RCC_PLLON_DISABLE        (0)

#define RCC_PLLRDY_READY        (1)
#define RCC_PLLRDY_NOT_READY    (0)


/***************** 4.2- RCC->CFGR ***************/

#define RCC_SW_HSI        (0)
#define RCC_SW_HSE        (1)
#define RCC_SW_PLL        (2)

#define RCC_SWS_HSI_SELECTED    (0)
#define RCC_SWS_HSE_SELECTED    (1)
#define RCC_SWS_PLL_SELECTED    (2)

#define RCC_HPRE_DIV_BY_1        (7)
#define RCC_HPRE_DIV_BY_2        (8)
#define RCC_HPRE_DIV_BY_4        (9)
#define RCC_HPRE_DIV_BY_8        (10)
#define RCC_HPRE_DIV_BY_16        (11)
#define RCC_HPRE_DIV_BY_64        (12)
#define RCC_HPRE_DIV_BY_128        (13)
#define RCC_HPRE_DIV_BY_256        (14)
#define RCC_HPRE_DIV_BY_512        (15)


#define RCC_PPRE1_DIV_BY_1        (3)
#define RCC_PPRE1_DIV_BY_2        (4)
#define RCC_PPRE1_DIV_BY_4        (5)
#define RCC_PPRE1_DIV_BY_8        (6)
#define RCC_PPRE1_DIV_BY_16        (7)


#define RCC_PPRE2_DIV_BY_1        (3)
#define RCC_PPRE2_DIV_BY_2        (4)
#define RCC_PPRE2_DIV_BY_4        (5)
#define RCC_PPRE2_DIV_BY_8        (6)
#define RCC_PPRE2_DIV_BY_16        (7)


#define RCC_ADCPRE_DIV_BY_2        (0)
#define RCC_ADCPRE_DIV_BY_4        (1)
#define RCC_ADCPRE_DIV_BY_6        (2)
#define RCC_ADCPRE_DIV_BY_8        (3)

#define RCC_PLLSRC_HSI_DIV_BY_2    (0)
#define RCC_PLLSRC_HSE            (1)

#define RCC_PLLXTPRE_DIV_BY_1    (0)
#define RCC_PLLXTPRE_DIV_BY_2    (1)

#define RCC_PLLMUL_MUL_BY_2            (0)
#define RCC_PLLMUL_MUL_BY_3            (1)
#define RCC_PLLMUL_MUL_BY_4            (2)
#define RCC_PLLMUL_MUL_BY_5            (3)
#define RCC_PLLMUL_MUL_BY_6            (4)
#define RCC_PLLMUL_MUL_BY_7            (5)
#define RCC_PLLMUL_MUL_BY_8            (6)
#define RCC_PLLMUL_MUL_BY_9            (7)
#define RCC_PLLMUL_MUL_BY_10        (8)
#define RCC_PLLMUL_MUL_BY_11        (9)
#define RCC_PLLMUL_MUL_BY_12        (10)
#define RCC_PLLMUL_MUL_BY_13        (11)
#define RCC_PLLMUL_MUL_BY_14        (12)
#define RCC_PLLMUL_MUL_BY_15        (13)
#define RCC_PLLMUL_MUL_BY_16        (14)
//#define RCC_PLLMUL_MUL_BY_16		(15)


#define RCC_USBPRE_DIV_BY_1_5        (0)
#define RCC_USBPRE_DIV_BY_1            (1)

#define RCC_MCO_NO_OUTPUT            (0)
#define RCC_MCO_SYSCLK                (4)
#define RCC_MCO_HSI                    (5)
#define RCC_MCO_HSE                    (6)
#define RCC_MCO_PLL_DIV_BY_2        (7)


/***************** 4.3- RCC->CIR ***************/

#define RCC_LSIRDYF_READY        (1)
#define RCC_LSIRDYF_NOT_READY    (0)

#define RCC_LSERDYF_READY        (1)
#define RCC_LSERDYF_NOT_READY    (0)

#define RCC_HSIRDYF_READY        (1)
#define RCC_HSIRDYF_NOT_READY    (0)

#define RCC_HSERDYF_READY        (1)
#define RCC_HSERDYF_NOT_READY    (0)

#define RCC_PLLRDYF_READY        (1)
#define RCC_PLLRDYF_NOT_READY    (0)

#define RCC_CSSF_HIGH            (1)
#define RCC_CSSF_LOW            (0)

#define RCC_LSIRDYIE_ENABLE        (1)
#define RCC_LSIRDYIE_DISABLE    (0)

#define RCC_LSERDYIE_ENABLE        (1)
#define RCC_LSERDYIE_DISABLE    (0)

#define RCC_HSIRDYIE_ENABLE        (1)
#define RCC_HSIRDYIE_DISABLE    (0)

#define RCC_HSERDYIE_ENABLE        (1)
#define RCC_HSERDYIE_DISABLE    (0)

#define RCC_PLLRDYIE_ENABLE        (1)
#define RCC_PLLRDYIE_DISABLE    (0)

#define RCC_LSIRDYC_CLEAR        (1)
#define RCC_LSERDYC_CLEAR        (1)
#define RCC_HSIRDYC_CLEAR        (1)
#define RCC_HSERDYC_CLEAR        (1)
#define RCC_PLLRDYC_CLEAR        (1)
#define RCC_CSSC_CLEAR            (1)


/***************** 4.4- RCC->APB2RSTR ***************/

#define RCC_AFIORST_RESET        (1)

#define RCC_IOPARST_RESET        (1)
#define RCC_IOPBRST_RESET        (1)
#define RCC_IOPCRST_RESET        (1)
#define RCC_IOPDRST_RESET        (1)
#define RCC_IOPERST_RESET        (1)
#define RCC_IOPFRST_RESET        (1)
#define RCC_IOPGRST_RESET        (1)

#define RCC_ADC1RST_RESET        (1)
#define RCC_ADC2RST_RESET        (1)

#define RCC_TIM1RST_RESET        (1)

#define RCC_SPI1RST_RESET        (1)

#define RCC_TIM8RST_RESET        (1)

#define RCC_USART1RST_RESET        (1)

#define RCC_ADC3RST_RESET        (1)

#define RCC_TIM9RST_RESET        (1)
#define RCC_TIM10RST_RESET        (1)
#define RCC_TIM11RST_RESET        (1)

/***************** 4.5- RCC->APB1RSTR ***************/

#define RCC_TIM2RST_RESET        (1)
#define RCC_TIM3RST_RESET        (1)
#define RCC_TIM4RST_RESET        (1)
#define RCC_TIM5RST_RESET        (1)
#define RCC_TIM6RST_RESET        (1)
#define RCC_TIM7RST_RESET        (1)
#define RCC_TIM12RST_RESET        (1)
#define RCC_TIM13RST_RESET        (1)
#define RCC_TIM14RST_RESET        (1)

#define RCC_WWDGRST_RESET        (1)

#define RCC_SPI2RST_RESET        (1)
#define RCC_SPI3RST_RESET        (1)

#define RCC_USART2RST_RESET        (1)
#define RCC_USART3RST_RESET        (1)
#define RCC_UART4RST_RESET        (1)
#define RCC_UART5RST_RESET        (1)

#define RCC_I2C1RST_RESET        (1)
#define RCC_I2C2RST_RESET        (1)

#define RCC_USBRST_RESET        (1)

#define RCC_CANRST_RESET        (1)

#define RCC_BKPRST_RESET        (1)

#define RCC_PWRRST_RESET        (1)

#define RCC_DAC_RESET            (1)



/***************** 4.6- RCC->AHBENR ***************/

#define RCC_DMA1EN_ENABLE        (1)
#define RCC_DMA1EN_DISABLE        (0)

#define RCC_DMA2EN_ENABLE        (1)
#define RCC_DMA2EN_DISABLE        (0)

#define RCC_SRAMEN_ENABLE        (1)
#define RCC_SRAMEN_DISABLE        (0)

#define RCC_FLITFEN_ENABLE        (1)
#define RCC_FLITFEN_DISABLE        (0)

#define RCC_CRCEN_ENABLE        (1)
#define RCC_CRCEN_DISABLE        (0)

#define RCC_FSMCEN_ENABLE        (1)
#define RCC_FSMCEN_DISABLE        (0)

#define RCC_SDIOEN_ENABLE        (1)
#define RCC_SDIOEN_DISABLE        (0)


/***************** 4.7- RCC->APB2ENR ***************/

#define RCC_AFIOEN_ENABLE        (1)
#define RCC_AFIOEN_DISABLE        (0)

#define RCC_IOPAEN_ENABLE        (1)
#define RCC_IOPAEN_DISABLE        (0)

#define RCC_IOPBEN_ENABLE        (1)
#define RCC_IOPBEN_DISABLE        (0)

#define RCC_IOPCEN_ENABLE        (1)
#define RCC_IOPCEN_DISABLE        (0)

#define RCC_IOPDEN_ENABLE        (1)
#define RCC_IOPDEN_DISABLE        (0)

#define RCC_IOPEEN_ENABLE        (1)
#define RCC_IOPEEN_DISABLE        (0)

#define RCC_IOPFEN_ENABLE        (1)
#define RCC_IOPFEN_DISABLE        (0)

#define RCC_IOPGEN_ENABLE        (1)
#define RCC_IOPGEN_DISABLE        (0)

#define RCC_ADC1EN_ENABLE        (1)
#define RCC_ADC1EN_DISABLE        (0)

#define RCC_ADC2EN_ENABLE        (1)
#define RCC_ADC2EN_DISABLE        (0)

#define RCC_TIM1EN_ENABLE        (1)
#define RCC_TIM1EN_DISABLE        (0)

#define RCC_SPI1EN_ENABLE        (1)
#define RCC_SPI1EN_DISABLE        (0)

#define RCC_TIM8EN_ENABLE        (1)
#define RCC_TIM8EN_DISABLE        (0)

#define RCC_USART1EN_ENABLE        (1)
#define RCC_USART1EN_DISABLE    (0)

#define RCC_ADC3EN_ENABLE        (1)
#define RCC_ADC3EN_DISABLE        (0)

#define RCC_TIM9EN_ENABLE        (1)
#define RCC_TIM9EN_DISABLE        (0)

#define RCC_TIM10EN_ENABLE        (1)
#define RCC_TIM10EN_DISABLE        (0)

#define RCC_TIM11EN_ENABLE        (1)
#define RCC_TIM11EN_DISABLE        (0)


/***************** 4.8- RCC->APB1ENR ***************/

#define RCC_TIM2EN_ENABLE        (1)
#define RCC_TIM2EN_DISABLE        (0)

#define RCC_TIM3EN_ENABLE        (1)
#define RCC_TIM3EN_DISABLE        (0)

#define RCC_TIM4EN_ENABLE        (1)
#define RCC_TIM4EN_DISABLE        (0)

#define RCC_TIM5EN_ENABLE        (1)
#define RCC_TIM5EN_DISABLE        (0)

#define RCC_TIM6EN_ENABLE        (1)
#define RCC_TIM6EN_DISABLE        (0)

#define RCC_TIM7EN_ENABLE        (1)
#define RCC_TIM7EN_DISABLE        (0)

#define RCC_TIM12EN_ENABLE        (1)
#define RCC_TIM12EN_DISABLE        (0)

#define RCC_TIM13EN_ENABLE        (1)
#define RCC_TIM13EN_DISABLE        (0)

#define RCC_TIM14EN_ENABLE        (1)
#define RCC_TIM14EN_DISABLE        (0)

#define RCC_WWDGEN_ENABLE        (1)
#define RCC_WWDGEN_DISABLE        (0)

#define RCC_SPI2EN_ENABLE        (1)
#define RCC_SPI2EN_DISABLE        (0)

#define RCC_SPI3EN_ENABLE        (1)
#define RCC_SPI3EN_DISABLE        (0)


/***************** 4.9- RCC->BDCR ***************/

#define RCC_LSEON_ENABLE        (1)
#define RCC_LSEON_DISABLE        (0)

#define RCC_LSERDY_READY        (1)
#define RCC_LSERDY_NOT_READY    (0)

#define RCC_LSEBYP_BYPASS        (1)
#define RCC_LSEBYP_DONT_BYPASS    (0)

#define RCC_RTCSEL_NOCLK                (0)
#define RCC_RTCSEL_LSE                    (1)
#define RCC_RTCSEL_LSI                    (2)
#define RCC_RTCSEL_HSE_DIV_BY_128        (3)


#define RCC_RTCEN_ENABLE    (1)
#define RCC_RTCEN_DISABLE    (0)

#define RCC_BDRST_RESET        (1)

/***************** 4.10- RCC->CSR ***************/

#define RCC_LSION_ENABLE    (1)
#define RCC_LSION_DISABLE    (0)

#define RCC_RMVF_REMOVE        (1)

#define RCC_PINRSTF_RESET    (1)

#define RCC_PORRSTF_RESET    (1)

#define RCC_SFTRSTF_RESET    (1)

#define RCC_IWDGRSTF_RESET    (1)

#define RCC_WWDGRSTF_RESET    (1)

#define RCC_LPWRRSTF_RESET    (1)




/***************************************************************/
/*					    	(6) _CRC							   */
/***************************************************************/

/*
 * 	_CRC Section Architecture Map
 *		1- _CRC->Base_Definitions
 *		2- _CRC->Registers_Pointers
 *		3- _CRC->Struct_Definition
 *		4- _CRC->Registers_Values_Definitions
 *			4.1- _CRC->CR
 *
 *
 * */


/***************** 1- _CRC->Base_Definition ******************/

#define CRC_BASE            (0x40023000)

#define CRC_DR_BASE         (CRC_BASE + 0x00)
#define CRC_IDR_BASE        (CRC_BASE + 0x04)
#define CRC_CR_BASE         (CRC_BASE + 0x04)

/***************** 2- _CRC->Registers_Pointers ***************/

#define CRC_DR              (*((volatile unsigned long *)CRC_DR_BASE))
#define CRC_IDR             (*((volatile unsigned long *)CRC_IDR_BASE))
#define CRC_CR              (*((volatile unsigned long *)CRC_CR_BASE))

/***************** 3- _CRC->Struct_Definition ****************/

#define pCRC             ((volatile CRC_t *)CRC_BASE)

typedef volatile struct {

    volatile union {
        unsigned long REG;
    } DR;

    volatile union {
        unsigned long ID: 8;
        unsigned long REG;
    } IDR;

    volatile union {
        unsigned long RESET: 1;
        unsigned long REG;
    } CR;
} CRC_t;


/***************** 4- _CRC->Registers_Values_Definitions *****/

/***************** 4.1- _CRC->CR  ***************/

#define CRC_RESET       (1)





/***************************************************************/
/*					    	(7) PWR							   */
/***************************************************************/

/*
 * 	MPU Section Architecture Map
 *		1- MPU->Base_Definitions
 *		2- MPU->Registers_Pointers
 *		3- MPU->Struct_Definition
 *		4- MPU->Registers_Values_Definitions
 *			4.1- CR
 *			4.2- CSR
 *
 *
 * */


/***************** 1- PWR->Base_Definition ******************/

#define PWR_BASE                (0x40007000)

#define PWR_CR_BASE             (PWR_BASE + 0x00)
#define PWR_CSR_BASE            (PWR_BASE + 0x04)

/***************** 2- PWR->Registers_Pointers ***************/

#define PWR_CR       (*((volatile unsigned long *)PWR_CR_BASE))
#define PWR_CSR      (*((volatile unsigned long *)PWR_CSR_BASE))

/***************** 3- PWR->Struct_Definition ****************/

#define PWR          ((volatile PWR_t *)PWR_BASE)

typedef volatile struct {

    volatile union {
        struct {
            unsigned long LPDS: 1;
            unsigned long PDDS: 1;
            unsigned long CWUF: 1;
            unsigned long CSBF: 1;
            unsigned long PVDE: 1;
            unsigned long PLS: 3;
            unsigned long DBP: 1;
            const unsigned long      : 23;
        };

        unsigned long REG;
    } CR;
    volatile union {
        struct {
            const unsigned long WUF: 1;
            const unsigned long SBF: 1;
            const unsigned long PVDO: 1;
            const unsigned long          : 5;
            unsigned long EWUP: 1;
            const unsigned long          : 23;
        };
        unsigned long REG;
    } CSR;


} PWR_t;




/***************** 4- PWR->Registers_Values_Definitions *****/

/***************** 4.1- PWR->CR  ****************/

#define PWR_LPDS_VOLTAGE_REGULATOR_ON_DURING_STOP_MODE                (0)
#define PWR_LPDS_VOLTAGE_REGULATOR_IN_LOW_POWER_DURING_STOP_MODE      (0)

#define PWR_PDDS_STOP_MODE_ON_DEEPSLEEP            (0)
#define PWR_PDDS_STANDBY_MODE_ON_DEEPSLEEP         (1)

#define PWR_CWUF_CLEAR_WUF_AFTER_2_SYSCLKs         (1)

#define PWR_CSBF_CLEAR_SBF                         (1)

#define PWR_PVDE_POWER_VOLTAGE_DETECTOR_ENABLE     (1)
#define PWR_PVDE_POWER_VOLTAGE_DETECTOR_DISABLE    (0)

#define PWR_PLS_PVD_VOLTAGE_SELECTION_2_2V          (0)
#define PWR_PLS_PVD_VOLTAGE_SELECTION_2_3V          (1)
#define PWR_PLS_PVD_VOLTAGE_SELECTION_2_4V          (2)
#define PWR_PLS_PVD_VOLTAGE_SELECTION_2_5V          (3)
#define PWR_PLS_PVD_VOLTAGE_SELECTION_2_6V          (4)
#define PWR_PLS_PVD_VOLTAGE_SELECTION_2_7V          (5)
#define PWR_PLS_PVD_VOLTAGE_SELECTION_2_8V          (6)
#define PWR_PLS_PVD_VOLTAGE_SELECTION_2_9V          (7)

#define PWR_DBP_BD_AND_RTC_WRITE_PROTECTION_DISABLE    (1)
#define PWR_DBP_BD_AND_RTC_WRITE_PROTECTION_ENABLE     (0)

/***************** 4.1- PWR->CSR  ***************/


#define PWR_WUF_WAKEUP_FLAG_ON        (1)

#define PWR_SBF_STANDBY_FLAG_ON       (1)

#define PWR_PVDO_VDD_HIGHER_THAN_PVD_TRH  (0)
#define PWR_PVDO_VDD_LOWER_THAN_PVD_TRH   (1)

#define PWR_EWUP_WAKEUP_PIN_ENABLE       (1)
#define PWR_EWUP_WAKEUP_PIN_DISABLE      (0)





/***************************************************************/
/*					    	(8) BKP							   */
/***************************************************************/

/*
 * 	BKP Section Architecture Map
 *		1- BKP->Base_Definitions
 *		2- BKP->Registers_Pointers
 *		3- BKP->Struct_Definition
 *		4- BKP->Registers_Values_Definitions
 *			4.1- RTCCR
 *			4.2- CR
 *			4.3- CSR
 *
 *
 * */


/***************** 1- BKP->Base_Definition ******************/

#define BKP_BASE                (0x40006C00U)

#define BKP_DR1_BASE            (BKP_BASE + 0x00 + 4 * 0 )
#define BKP_DR2_BASE            (BKP_BASE + 0x00 + 4 * 1 )
#define BKP_DR3_BASE            (BKP_BASE + 0x00 + 4 * 2 )
#define BKP_DR4_BASE            (BKP_BASE + 0x00 + 4 * 3 )
#define BKP_DR5_BASE            (BKP_BASE + 0x00 + 4 * 4 )
#define BKP_DR6_BASE            (BKP_BASE + 0x00 + 4 * 5 )
#define BKP_DR7_BASE            (BKP_BASE + 0x00 + 4 * 6 )
#define BKP_DR8_BASE            (BKP_BASE + 0x00 + 4 * 7 )
#define BKP_DR9_BASE            (BKP_BASE + 0x00 + 4 * 8 )
#define BKP_DR10_BASE           (BKP_BASE + 0x00 + 4 * 9 )

#define BKP_DR11_BASE            (BKP_BASE + 0x40 + 4 * 0 )
#define BKP_DR12_BASE            (BKP_BASE + 0x40 + 4 * 1 )
#define BKP_DR13_BASE            (BKP_BASE + 0x40 + 4 * 2 )
#define BKP_DR14_BASE            (BKP_BASE + 0x40 + 4 * 3 )
#define BKP_DR15_BASE            (BKP_BASE + 0x40 + 4 * 4 )
#define BKP_DR16_BASE            (BKP_BASE + 0x40 + 4 * 5 )
#define BKP_DR17_BASE            (BKP_BASE + 0x40 + 4 * 6 )
#define BKP_DR18_BASE            (BKP_BASE + 0x40 + 4 * 7 )
#define BKP_DR19_BASE            (BKP_BASE + 0x40 + 4 * 8 )
#define BKP_DR20_BASE            (BKP_BASE + 0x40 + 4 * 9 )
#define BKP_DR21_BASE            (BKP_BASE + 0x40 + 4 * 10 )
#define BKP_DR22_BASE            (BKP_BASE + 0x40 + 4 * 11 )
#define BKP_DR23_BASE            (BKP_BASE + 0x40 + 4 * 12 )
#define BKP_DR24_BASE            (BKP_BASE + 0x40 + 4 * 13 )
#define BKP_DR25_BASE            (BKP_BASE + 0x40 + 4 * 14 )
#define BKP_DR26_BASE            (BKP_BASE + 0x40 + 4 * 15 )
#define BKP_DR27_BASE            (BKP_BASE + 0x40 + 4 * 16 )
#define BKP_DR28_BASE            (BKP_BASE + 0x40 + 4 * 17 )
#define BKP_DR29_BASE            (BKP_BASE + 0x40 + 4 * 18 )
#define BKP_DR30_BASE            (BKP_BASE + 0x40 + 4 * 19 )
#define BKP_DR31_BASE            (BKP_BASE + 0x40 + 4 * 20 )
#define BKP_DR32_BASE            (BKP_BASE + 0x40 + 4 * 21 )
#define BKP_DR33_BASE            (BKP_BASE + 0x40 + 4 * 22 )
#define BKP_DR34_BASE            (BKP_BASE + 0x40 + 4 * 23 )
#define BKP_DR35_BASE            (BKP_BASE + 0x40 + 4 * 24 )
#define BKP_DR36_BASE            (BKP_BASE + 0x40 + 4 * 25 )
#define BKP_DR37_BASE            (BKP_BASE + 0x40 + 4 * 26 )
#define BKP_DR38_BASE            (BKP_BASE + 0x40 + 4 * 27 )
#define BKP_DR39_BASE            (BKP_BASE + 0x40 + 4 * 28 )
#define BKP_DR40_BASE            (BKP_BASE + 0x40 + 4 * 29 )
#define BKP_DR41_BASE            (BKP_BASE + 0x40 + 4 * 30 )
#define BKP_DR42_BASE            (BKP_BASE + 0x40 + 4 * 31 )


#define BKP_RTCCR_BASE          (BKP_BASE + 0x2C)
#define BKP_CR_BASE             (BKP_BASE + 0x30)
#define BKP_CSR_BASE            (BKP_BASE + 0x34)

/***************** 2- BKP->Registers_Pointers ***************/

#define BKP_DR1                 (*((volatile uint16_t *)BKP_DR1_BASE))
#define BKP_DR2                 (*((volatile uint16_t *)BKP_DR2_BASE))
#define BKP_DR3                 (*((volatile uint16_t *)BKP_DR3_BASE))
#define BKP_DR4                 (*((volatile uint16_t *)BKP_DR4_BASE))
#define BKP_DR5                 (*((volatile uint16_t *)BKP_DR5_BASE))
#define BKP_DR6                 (*((volatile uint16_t *)BKP_DR6_BASE))
#define BKP_DR7                 (*((volatile uint16_t *)BKP_DR7_BASE))
#define BKP_DR8                 (*((volatile uint16_t *)BKP_DR8_BASE))
#define BKP_DR9                 (*((volatile uint16_t *)BKP_DR9_BASE))
#define BKP_DR10                 (*((volatile uint16_t *)BKP_DR10_BASE))
#define BKP_DR11                 (*((volatile uint16_t *)BKP_DR11_BASE))
#define BKP_DR12                 (*((volatile uint16_t *)BKP_DR12_BASE))
#define BKP_DR13                 (*((volatile uint16_t *)BKP_DR13_BASE))
#define BKP_DR14                 (*((volatile uint16_t *)BKP_DR14_BASE))
#define BKP_DR15                 (*((volatile uint16_t *)BKP_DR15_BASE))
#define BKP_DR16                 (*((volatile uint16_t *)BKP_DR16_BASE))
#define BKP_DR17                 (*((volatile uint16_t *)BKP_DR17_BASE))
#define BKP_DR18                 (*((volatile uint16_t *)BKP_DR18_BASE))
#define BKP_DR19                 (*((volatile uint16_t *)BKP_DR19_BASE))
#define BKP_DR20                 (*((volatile uint16_t *)BKP_DR20_BASE))
#define BKP_DR21                 (*((volatile uint16_t *)BKP_DR21_BASE))
#define BKP_DR22                 (*((volatile uint16_t *)BKP_DR22_BASE))
#define BKP_DR23                 (*((volatile uint16_t *)BKP_DR23_BASE))
#define BKP_DR24                 (*((volatile uint16_t *)BKP_DR24_BASE))
#define BKP_DR25                 (*((volatile uint16_t *)BKP_DR25_BASE))
#define BKP_DR26                 (*((volatile uint16_t *)BKP_DR26_BASE))
#define BKP_DR27                 (*((volatile uint16_t *)BKP_DR27_BASE))
#define BKP_DR28                 (*((volatile uint16_t *)BKP_DR28_BASE))
#define BKP_DR29                 (*((volatile uint16_t *)BKP_DR29_BASE))
#define BKP_DR30                 (*((volatile uint16_t *)BKP_DR30_BASE))
#define BKP_DR31                 (*((volatile uint16_t *)BKP_DR31_BASE))
#define BKP_DR32                 (*((volatile uint16_t *)BKP_DR32_BASE))
#define BKP_DR33                 (*((volatile uint16_t *)BKP_DR33_BASE))
#define BKP_DR34                 (*((volatile uint16_t *)BKP_DR34_BASE))
#define BKP_DR35                 (*((volatile uint16_t *)BKP_DR35_BASE))
#define BKP_DR36                 (*((volatile uint16_t *)BKP_DR36_BASE))
#define BKP_DR37                 (*((volatile uint16_t *)BKP_DR37_BASE))
#define BKP_DR38                 (*((volatile uint16_t *)BKP_DR38_BASE))
#define BKP_DR39                 (*((volatile uint16_t *)BKP_DR39_BASE))
#define BKP_DR40                 (*((volatile uint16_t *)BKP_DR40_BASE))
#define BKP_DR41                 (*((volatile uint16_t *)BKP_DR41_BASE))
#define BKP_DR42                 (*((volatile uint16_t *)BKP_DR42_BASE))

#define BKP_RTCCR                (*((volatile uint16_t *)BKP_RTCCR_BASE))
#define BKP_CR                   (*((volatile uint16_t *)BKP_CR_BASE))
#define BKP_CSR                  (*((volatile uint16_t *)BKP_CSR_BASE))


/***************** 3- BKP->Struct_Definition ****************/

#define BKPD             ((volatile BKP_t *)BKP_BASE)

typedef volatile struct {

    volatile union {
        struct {
            unsigned long D: 16;
            const unsigned long RESERVED: 16;
        };
        unsigned long REG;
    } DR_1_10[11];

    volatile union {
        struct {
            unsigned long CAL: 7;
            unsigned long CCO: 1;
            unsigned long ASOE: 1;
            unsigned long ASOS: 1;
            const unsigned long RESERVED: 22;
        };
        unsigned long REG;
    } RTCCR;

    volatile union {
        struct {
            unsigned long TPE: 1;
            unsigned long TPAL: 1;
            const unsigned long RESERVED: 30;
        };
        unsigned long REG;
    } CR;

    volatile union {
        struct {
            unsigned long CTE: 1;
            unsigned long CTI: 1;
            unsigned long TPIE: 1;
            const unsigned long RESERVED: 5;
            const unsigned long TEF: 1;
            const unsigned long TIF: 1;
            const unsigned long RESERVED: 22;

        };
        unsigned long REG;
    } CSR;

    const unsigned long RESERVED[2];

    volatile union {
        struct {
            unsigned long D: 16;
            const unsigned long RESERVED: 16;
        };
        unsigned long REG;
    } DR_11_42[32];

} BKP_t;

/***************** 4- BKP->Registers_Values_Definitions *****/

/***************** 4.1- BKP->RTCCR  ***************/

#define BKP_CCO_OUTPUT_RTC_CLK_DIV_64_ON_TAMPER_PIN     (1)

#define BKP_ASOE_ALARM_PULSE_ENABLE     (1)

#define BKP_ASOS_ALARM_PULSE         (0)
#define BKP_ASOS_SECOND_PULSE        (1)

/***************** 4.2- BKP->CR  ***************/

#define BKP_TPE_TAMPER_PIN_ENABLE        (1)
#define BKP_TPE_TAMPER_PIN_DISABLE       (0)

#define BKP_TPAL_RESET_ON_HIGH_LEVEL     (0)
#define BKP_TPAL_RESET_ON_LOW_LEVEL      (1)


/***************** 4.1- BKP->CSR  ***************/

#define BKP_CTE_CLEAR_TAMPER_EVENT                  (1)

#define BKP_CTI_CLEAR_TAMPER_INTERRUPT              (1)

#define BKP_TPIE_TAMPER_PIN_INTERRUPT_ENABLE        (1)

#define BKP_TEF_TAMPER_EVENT_FLAG_HIGH              (0)
#define BKP_TEF_TAMPER_EVENT_FLAG_LOW               (0)

#define BKP_TEF_TAMPER_INTERRUPT_FLAG_HIGH          (1)
#define BKP_TEF_TAMPER_INTERRUPT_FLAG_LOW           (1)





/***************************************************************/
/*					    	(9) GPIO						   */
/***************************************************************/

/*
 * 	GPIO Section Architecture Map
 *		1- GPIO->Base_Definitions
 *		2- GPIO->Registers_Pointers
 *		3- GPIO->Struct_Definition
 *		4- GPIO->Registers_Values_Definitions
 *			4.1- GPIO->CRH, GPIO->CRL
 *			4.2- GPIO->ODR
 *			4.3- GPIO->BSRR
 *			4.4- GPIO->BRR
 *			4.5- GPIO->LCKR
 *
 *
 * */


/***************** 1- GPIO->Base_Definition ******************/

#define GPIO_BASE           (0x40010800U)

#define GPIO_PORTA_BASE     (GPIO_BASE + 0x0000)
#define GPIO_PORTB_BASE     (GPIO_BASE + 0x0400)
#define GPIO_PORTC_BASE     (GPIO_BASE + 0x0800)
#define GPIO_PORTD_BASE     (GPIO_BASE + 0x0C00)
#define GPIO_PORTE_BASE     (GPIO_BASE + 0x1000)
#define GPIO_PORTF_BASE     (GPIO_BASE + 0x1400)
#define GPIO_PORTG_BASE     (GPIO_BASE + 0x1800)


#define GPIO_PORTA_CRL_BASE          (GPIO_PORTA_BASE + 0x00)
#define GPIO_PORTA_CRH_BASE          (GPIO_PORTA_BASE + 0x04)
#define GPIO_PORTA_IDR_BASE          (GPIO_PORTA_BASE + 0x08)
#define GPIO_PORTA_ODR_BASE          (GPIO_PORTA_BASE + 0x0C)
#define GPIO_PORTA_BSRR_BASE         (GPIO_PORTA_BASE + 0x10)
#define GPIO_PORTA_BRR_BASE          (GPIO_PORTA_BASE + 0x14)
#define GPIO_PORTA_LCKR_BASE         (GPIO_PORTA_BASE + 0x18)

#define GPIO_PORTB_CRL_BASE          (GPIO_PORTB_BASE + 0x00)
#define GPIO_PORTB_CRH_BASE          (GPIO_PORTB_BASE + 0x04)
#define GPIO_PORTB_IDR_BASE          (GPIO_PORTB_BASE + 0x08)
#define GPIO_PORTB_ODR_BASE          (GPIO_PORTB_BASE + 0x0C)
#define GPIO_PORTB_BSRR_BASE         (GPIO_PORTB_BASE + 0x10)
#define GPIO_PORTB_BRR_BASE          (GPIO_PORTB_BASE + 0x14)
#define GPIO_PORTB_LCKR_BASE         (GPIO_PORTB_BASE + 0x18)

#define GPIO_PORTC_CRL_BASE          (GPIO_PORTC_BASE + 0x00)
#define GPIO_PORTC_CRH_BASE          (GPIO_PORTC_BASE + 0x04)
#define GPIO_PORTC_IDR_BASE          (GPIO_PORTC_BASE + 0x08)
#define GPIO_PORTC_ODR_BASE          (GPIO_PORTC_BASE + 0x0C)
#define GPIO_PORTC_BSRR_BASE         (GPIO_PORTC_BASE + 0x10)
#define GPIO_PORTC_BRR_BASE          (GPIO_PORTC_BASE + 0x14)
#define GPIO_PORTC_LCKR_BASE         (GPIO_PORTC_BASE + 0x18)

#define GPIO_PORTD_CRL_BASE          (GPIO_PORTD_BASE + 0x00)
#define GPIO_PORTD_CRH_BASE          (GPIO_PORTD_BASE + 0x04)
#define GPIO_PORTD_IDR_BASE          (GPIO_PORTD_BASE + 0x08)
#define GPIO_PORTD_ODR_BASE          (GPIO_PORTD_BASE + 0x0C)
#define GPIO_PORTD_BSRR_BASE         (GPIO_PORTD_BASE + 0x10)
#define GPIO_PORTD_BRR_BASE          (GPIO_PORTD_BASE + 0x14)
#define GPIO_PORTD_LCKR_BASE         (GPIO_PORTD_BASE + 0x18)

#define GPIO_PORTE_CRL_BASE          (GPIO_PORTE_BASE + 0x00)
#define GPIO_PORTE_CRH_BASE          (GPIO_PORTE_BASE + 0x04)
#define GPIO_PORTE_IDR_BASE          (GPIO_PORTE_BASE + 0x08)
#define GPIO_PORTE_ODR_BASE          (GPIO_PORTE_BASE + 0x0C)
#define GPIO_PORTE_BSRR_BASE         (GPIO_PORTE_BASE + 0x10)
#define GPIO_PORTE_BRR_BASE          (GPIO_PORTE_BASE + 0x14)
#define GPIO_PORTE_LCKR_BASE         (GPIO_PORTE_BASE + 0x18)

#define GPIO_PORTF_CRL_BASE          (GPIO_PORTF_BASE + 0x00)
#define GPIO_PORTF_CRH_BASE          (GPIO_PORTF_BASE + 0x04)
#define GPIO_PORTF_IDR_BASE          (GPIO_PORTF_BASE + 0x08)
#define GPIO_PORTF_ODR_BASE          (GPIO_PORTF_BASE + 0x0C)
#define GPIO_PORTF_BSRR_BASE         (GPIO_PORTF_BASE + 0x10)
#define GPIO_PORTF_BRR_BASE          (GPIO_PORTF_BASE + 0x14)
#define GPIO_PORTF_LCKR_BASE         (GPIO_PORTF_BASE + 0x18)

#define GPIO_PORTG_CRL_BASE          (GPIO_PORTG_BASE + 0x00)
#define GPIO_PORTG_CRH_BASE          (GPIO_PORTG_BASE + 0x04)
#define GPIO_PORTG_IDR_BASE          (GPIO_PORTG_BASE + 0x08)
#define GPIO_PORTG_ODR_BASE          (GPIO_PORTG_BASE + 0x0C)
#define GPIO_PORTG_BSRR_BASE         (GPIO_PORTG_BASE + 0x10)
#define GPIO_PORTG_BRR_BASE          (GPIO_PORTG_BASE + 0x14)
#define GPIO_PORTG_LCKR_BASE         (GPIO_PORTG_BASE + 0x18)

/***************** 2- GPIO->Registers_Pointers ***************/


#define GPIO_PORTA_CRL           (*((volatile unsigned long *)GPIO_PORTA_CRL_BASE))
#define GPIO_PORTA_CRH           (*((volatile unsigned long *)GPIO_PORTA_CRH_BASE))
#define GPIO_PORTA_IDR           (*((volatile unsigned long *)GPIO_PORTA_IDR_BASE))
#define GPIO_PORTA_ODR           (*((volatile unsigned long *)GPIO_PORTA_ODR_BASE))
#define GPIO_PORTA_BSRR          (*((volatile unsigned long *)GPIO_PORTA_BSRR_BASE))
#define GPIO_PORTA_BRR           (*((volatile unsigned long *)GPIO_PORTA_BRR_BASE))
#define GPIO_PORTA_LCKR          (*((volatile unsigned long *)GPIO_PORTA_LCKR_BASE))

#define GPIO_PORTB_CRL           (*((volatile unsigned long *)GPIO_PORTB_CRL_BASE))
#define GPIO_PORTB_CRH           (*((volatile unsigned long *)GPIO_PORTB_CRH_BASE))
#define GPIO_PORTB_IDR           (*((volatile unsigned long *)GPIO_PORTB_IDR_BASE))
#define GPIO_PORTB_ODR           (*((volatile unsigned long *)GPIO_PORTB_ODR_BASE))
#define GPIO_PORTB_BSRR          (*((volatile unsigned long *)GPIO_PORTB_BSRR_BASE))
#define GPIO_PORTB_BRR           (*((volatile unsigned long *)GPIO_PORTB_BRR_BASE))
#define GPIO_PORTB_LCKR          (*((volatile unsigned long *)GPIO_PORTB_LCKR_BASE))

#define GPIO_PORTC_CRL           (*((volatile unsigned long *)GPIO_PORTC_CRL_BASE))
#define GPIO_PORTC_CRH           (*((volatile unsigned long *)GPIO_PORTC_CRH_BASE))
#define GPIO_PORTC_IDR           (*((volatile unsigned long *)GPIO_PORTC_IDR_BASE))
#define GPIO_PORTC_ODR           (*((volatile unsigned long *)GPIO_PORTC_ODR_BASE))
#define GPIO_PORTC_BSRR          (*((volatile unsigned long *)GPIO_PORTC_BSRR_BASE))
#define GPIO_PORTC_BRR           (*((volatile unsigned long *)GPIO_PORTC_BRR_BASE))
#define GPIO_PORTC_LCKR          (*((volatile unsigned long *)GPIO_PORTC_LCKR_BASE))

#define GPIO_PORTD_CRL           (*((volatile unsigned long *)GPIO_PORTD_CRL_BASE))
#define GPIO_PORTD_CRH           (*((volatile unsigned long *)GPIO_PORTD_CRH_BASE))
#define GPIO_PORTD_IDR           (*((volatile unsigned long *)GPIO_PORTD_IDR_BASE))
#define GPIO_PORTD_ODR           (*((volatile unsigned long *)GPIO_PORTD_ODR_BASE))
#define GPIO_PORTD_BSRR          (*((volatile unsigned long *)GPIO_PORTD_BSRR_BASE))
#define GPIO_PORTD_BRR           (*((volatile unsigned long *)GPIO_PORTD_BRR_BASE))
#define GPIO_PORTD_LCKR          (*((volatile unsigned long *)GPIO_PORTD_LCKR_BASE))

#define GPIO_PORTE_CRL           (*((volatile unsigned long *)GPIO_PORTE_CRL_BASE))
#define GPIO_PORTE_CRH           (*((volatile unsigned long *)GPIO_PORTE_CRH_BASE))
#define GPIO_PORTE_IDR           (*((volatile unsigned long *)GPIO_PORTE_IDR_BASE))
#define GPIO_PORTE_ODR           (*((volatile unsigned long *)GPIO_PORTE_ODR_BASE))
#define GPIO_PORTE_BSRR          (*((volatile unsigned long *)GPIO_PORTE_BSRR_BASE))
#define GPIO_PORTE_BRR           (*((volatile unsigned long *)GPIO_PORTE_BRR_BASE))
#define GPIO_PORTE_LCKR          (*((volatile unsigned long *)GPIO_PORTE_LCKR_BASE))

#define GPIO_PORTF_CRL           (*((volatile unsigned long *)GPIO_PORTF_CRL_BASE))
#define GPIO_PORTF_CRH           (*((volatile unsigned long *)GPIO_PORTF_CRH_BASE))
#define GPIO_PORTF_IDR           (*((volatile unsigned long *)GPIO_PORTF_IDR_BASE))
#define GPIO_PORTF_ODR           (*((volatile unsigned long *)GPIO_PORTF_ODR_BASE))
#define GPIO_PORTF_BSRR          (*((volatile unsigned long *)GPIO_PORTF_BSRR_BASE))
#define GPIO_PORTF_BRR           (*((volatile unsigned long *)GPIO_PORTF_BRR_BASE))
#define GPIO_PORTF_LCKR          (*((volatile unsigned long *)GPIO_PORTF_LCKR_BASE))

#define GPIO_PORTG_CRL           (*((volatile unsigned long *)GPIO_PORTG_CRL_BASE))
#define GPIO_PORTG_CRH           (*((volatile unsigned long *)GPIO_PORTG_CRH_BASE))
#define GPIO_PORTG_IDR           (*((volatile unsigned long *)GPIO_PORTG_IDR_BASE))
#define GPIO_PORTG_ODR           (*((volatile unsigned long *)GPIO_PORTG_ODR_BASE))
#define GPIO_PORTG_BSRR          (*((volatile unsigned long *)GPIO_PORTG_BSRR_BASE))
#define GPIO_PORTG_BRR           (*((volatile unsigned long *)GPIO_PORTG_BRR_BASE))
#define GPIO_PORTG_LCKR          (*((volatile unsigned long *)GPIO_PORTG_LCKR_BASE))

/***************** 3- GPIO->Struct_Definition ****************/


#define GPIO                ((volatile GPIO_t *)GPIO_BASE)

#define GPIO_PORTA          ((volatile GPIO_PORT_t *) GPIO_PORTA_BASE)
#define GPIO_PORTB          ((volatile GPIO_PORT_t *) GPIO_PORTB_BASE)
#define GPIO_PORTC          ((volatile GPIO_PORT_t *) GPIO_PORTC_BASE)
#define GPIO_PORTD          ((volatile GPIO_PORT_t *) GPIO_PORTD_BASE)
#define GPIO_PORTE          ((volatile GPIO_PORT_t *) GPIO_PORTE_BASE)
#define GPIO_PORTF          ((volatile GPIO_PORT_t *) GPIO_PORTF_BASE)
#define GPIO_PORTG          ((volatile GPIO_PORT_t *) GPIO_PORTG_BASE)


typedef volatile struct {


    volatile union {
        unsigned long REG;
    } CRL;

    volatile union {
        unsigned long REG;
    } CRH;

    volatile union {
        struct {
            unsigned long bits: 16;
            const unsigned long RESERVED: 16;
        } BITS;
        const unsigned long REG;
    } IDR;

    volatile union {
        struct {
            unsigned long bits: 16;
            const unsigned long RESERVED: 16;
        } BITS;
        unsigned long REG;
    } ODR;


    volatile union {
        struct {
            unsigned long BS: 16;
            unsigned long BR: 16;
        } BITS;

        unsigned long REG;
    } BSRR;

    volatile union {
        struct {
            unsigned long BR: 16;
            const unsigned long RESERVED: 16;
        } BITS;
        unsigned long REG;
    } BRR;

    volatile union {
        struct {
            unsigned long LCK: 16;
            unsigned long LCKK: 1;
        } BITS;
        unsigned long REG;
    } LCKR;

} GPIO_PORT_t;

typedef volatile union {

    volatile union {

        volatile struct {
            unsigned long REG;
            const unsigned long RESERVED[255];
        } CRLs[7];

        volatile struct {
            const unsigned long RESERVED;
            unsigned long REG;
            const unsigned long RESERVED[254];
        } CRHs[7];

        volatile struct {
            const unsigned long RESERVED[2];
            unsigned long REG;
            const unsigned long RESERVED[253];
        } IDRs[7];

        volatile struct {
            const unsigned long RESERVED[3];
            unsigned long REG;
            const unsigned long RESERVED[252];
        } ODRs[7];

        volatile struct {
            const unsigned long RESERVED[4];
            unsigned long REG;
            const unsigned long RESERVED[251];
        } BSRRs[7];

        volatile struct {
            const unsigned long RESERVED[5];
            unsigned long REG;
            const unsigned long RESERVED[250];
        } BRRs[7];

        volatile struct {
            const unsigned long RESERVED[6];
            unsigned long REG;
            const unsigned long RESERVED[249];
        } LCKRs[7];
    } ALL_PORTS;
    volatile struct { ;
        volatile GPIO_PORT_t PORTA;
        const uint32_t RESERVED[254];
        volatile GPIO_PORT_t PORTB;
        const uint32_t RESERVED[254];
        volatile GPIO_PORT_t PORTC;
        const uint32_t RESERVED[254];
        volatile GPIO_PORT_t PORTD;
        const uint32_t RESERVED[254];
        volatile GPIO_PORT_t PORTE;
        const uint32_t RESERVED[254];
        volatile GPIO_PORT_t PORTF;
        const uint32_t RESERVED[254];
        volatile GPIO_PORT_t PORTG;
        const uint32_t RESERVED[254];
    };
} GPIO_t;




/***************** 4- GPIO->Registers_Values_Definitions *****/

/***************** 4.1- GPIO->CRH, GPIO->CRL  ***************/


#define GPIO_CRL_MODE0_POS      (0)
#define GPIO_CRL_MODE1_POS      (4)
#define GPIO_CRL_MODE2_POS      (8)
#define GPIO_CRL_MODE3_POS      (12)
#define GPIO_CRL_MODE4_POS      (16)
#define GPIO_CRL_MODE5_POS      (20)
#define GPIO_CRL_MODE6_POS      (24)
#define GPIO_CRL_MODE7_POS      (28)

#define GPIO_CRH_MODE8_POS       (0)
#define GPIO_CRH_MODE9_POS       (4)
#define GPIO_CRH_MODE10_POS      (8)
#define GPIO_CRH_MODE11_POS      (12)
#define GPIO_CRH_MODE12_POS      (16)
#define GPIO_CRH_MODE13_POS      (20)
#define GPIO_CRH_MODE14_POS      (24)
#define GPIO_CRH_MODE15_POS      (28)


#define GPIO_MODE_INPUT             (0)
#define GPIO_MODE_OUTPUT_10MHZ      (1)
#define GPIO_MODE_OUTPUT_2MHZ       (2)
#define GPIO_MODE_OUTPUT_50MHZ      (3)

#define GPIO_CRL_MODE0_INPUT             (GPIO_MODE_INPUT<<GPIO_CRL_MODE0_POS)
#define GPIO_CRL_MODE0_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRL_MODE0_POS)
#define GPIO_CRL_MODE0_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRL_MODE0_POS)
#define GPIO_CRL_MODE0_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRL_MODE0_POS)
#define GPIO_CRL_MODE1_INPUT             (GPIO_MODE_INPUT<<GPIO_CRL_MODE1_POS)
#define GPIO_CRL_MODE1_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRL_MODE1_POS)
#define GPIO_CRL_MODE1_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRL_MODE1_POS)
#define GPIO_CRL_MODE1_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRL_MODE1_POS)
#define GPIO_CRL_MODE2_INPUT             (GPIO_MODE_INPUT<<GPIO_CRL_MODE2_POS)
#define GPIO_CRL_MODE2_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRL_MODE2_POS)
#define GPIO_CRL_MODE2_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRL_MODE2_POS)
#define GPIO_CRL_MODE2_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRL_MODE2_POS)
#define GPIO_CRL_MODE3_INPUT             (GPIO_MODE_INPUT<<GPIO_CRL_MODE3_POS)
#define GPIO_CRL_MODE3_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRL_MODE3_POS)
#define GPIO_CRL_MODE3_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRL_MODE3_POS)
#define GPIO_CRL_MODE3_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRL_MODE3_POS)
#define GPIO_CRL_MODE4_INPUT             (GPIO_MODE_INPUT<<GPIO_CRL_MODE4_POS)
#define GPIO_CRL_MODE4_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRL_MODE4_POS)
#define GPIO_CRL_MODE4_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRL_MODE4_POS)
#define GPIO_CRL_MODE4_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRL_MODE4_POS)
#define GPIO_CRL_MODE5_INPUT             (GPIO_MODE_INPUT<<GPIO_CRL_MODE5_POS)
#define GPIO_CRL_MODE5_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRL_MODE5_POS)
#define GPIO_CRL_MODE5_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRL_MODE5_POS)
#define GPIO_CRL_MODE5_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRL_MODE5_POS)
#define GPIO_CRL_MODE6_INPUT             (GPIO_MODE_INPUT<<GPIO_CRL_MODE6_POS)
#define GPIO_CRL_MODE6_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRL_MODE6_POS)
#define GPIO_CRL_MODE6_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRL_MODE6_POS)
#define GPIO_CRL_MODE6_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRL_MODE6_POS)
#define GPIO_CRL_MODE7_INPUT             (GPIO_MODE_INPUT<<GPIO_CRL_MODE7_POS)
#define GPIO_CRL_MODE7_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRL_MODE7_POS)
#define GPIO_CRL_MODE7_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRL_MODE7_POS)
#define GPIO_CRL_MODE7_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRL_MODE7_POS)
#define GPIO_CRH_MODE8_INPUT             (GPIO_MODE_INPUT<<GPIO_CRH_MODE8_POS)
#define GPIO_CRH_MODE8_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRH_MODE8_POS)
#define GPIO_CRH_MODE8_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRH_MODE8_POS)
#define GPIO_CRH_MODE8_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRH_MODE8_POS)
#define GPIO_CRH_MODE9_INPUT             (GPIO_MODE_INPUT<<GPIO_CRH_MODE9_POS)
#define GPIO_CRH_MODE9_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRH_MODE9_POS)
#define GPIO_CRH_MODE9_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRH_MODE9_POS)
#define GPIO_CRH_MODE9_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRH_MODE9_POS)
#define GPIO_CRH_MODE10_INPUT             (GPIO_MODE_INPUT<<GPIO_CRH_MODE10_POS)
#define GPIO_CRH_MODE10_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRH_MODE10_POS)
#define GPIO_CRH_MODE10_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRH_MODE10_POS)
#define GPIO_CRH_MODE10_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRH_MODE10_POS)
#define GPIO_CRH_MODE11_INPUT             (GPIO_MODE_INPUT<<GPIO_CRH_MODE11_POS)
#define GPIO_CRH_MODE11_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRH_MODE11_POS)
#define GPIO_CRH_MODE11_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRH_MODE11_POS)
#define GPIO_CRH_MODE11_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRH_MODE11_POS)
#define GPIO_CRH_MODE12_INPUT             (GPIO_MODE_INPUT<<GPIO_CRH_MODE12_POS)
#define GPIO_CRH_MODE12_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRH_MODE12_POS)
#define GPIO_CRH_MODE12_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRH_MODE12_POS)
#define GPIO_CRH_MODE12_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRH_MODE12_POS)
#define GPIO_CRH_MODE13_INPUT             (GPIO_MODE_INPUT<<GPIO_CRH_MODE13_POS)
#define GPIO_CRH_MODE13_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRH_MODE13_POS)
#define GPIO_CRH_MODE13_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRH_MODE13_POS)
#define GPIO_CRH_MODE13_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRH_MODE13_POS)
#define GPIO_CRH_MODE14_INPUT             (GPIO_MODE_INPUT<<GPIO_CRH_MODE14_POS)
#define GPIO_CRH_MODE14_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRH_MODE14_POS)
#define GPIO_CRH_MODE14_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRH_MODE14_POS)
#define GPIO_CRH_MODE14_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRH_MODE14_POS)
#define GPIO_CRH_MODE15_INPUT             (GPIO_MODE_INPUT<<GPIO_CRH_MODE15_POS)
#define GPIO_CRH_MODE15_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRH_MODE15_POS)
#define GPIO_CRH_MODE15_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRH_MODE15_POS)
#define GPIO_CRH_MODE15_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRH_MODE15_POS)


#define GPIO_CNF_INPUT_ANALOG             (0)
#define GPIO_CNF_INPUT_FLOATING           (1)
#define GPIO_CNF_INPUT_PULL_UP_DOWN       (2)

#define GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (0)
#define GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (1)
#define GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (2)
#define GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (3)

#define GPIO_CRL_CNF0_POS              (2)
#define GPIO_CRL_CNF1_POS              (6)
#define GPIO_CRL_CNF2_POS              (10)
#define GPIO_CRL_CNF3_POS              (14)
#define GPIO_CRL_CNF4_POS              (18)
#define GPIO_CRL_CNF5_POS              (22)
#define GPIO_CRL_CNF6_POS              (26)
#define GPIO_CRL_CNF7_POS              (30)

#define GPIO_CRH_CNF8_POS               (2)
#define GPIO_CRH_CNF9_POS               (6)
#define GPIO_CRH_CNF10_POS              (10)
#define GPIO_CRH_CNF11_POS              (14)
#define GPIO_CRH_CNF12_POS              (18)
#define GPIO_CRH_CNF13_POS              (22)
#define GPIO_CRH_CNF14_POS              (26)
#define GPIO_CRH_CNF15_POS              (30)


#define GPIO_CRL_CNF0_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF0_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF0_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRL_CNF0_POS)

#define GPIO_CRL_CNF0_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF0_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF0_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF0_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRL_CNF0_POS)

#define GPIO_CRL_CNF1_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF1_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF1_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRL_CNF0_POS)

#define GPIO_CRL_CNF1_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRL_CNF1_POS)
#define GPIO_CRL_CNF1_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRL_CNF1_POS)
#define GPIO_CRL_CNF1_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRL_CNF1_POS)
#define GPIO_CRL_CNF1_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRL_CNF1_POS)

#define GPIO_CRL_CNF2_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF2_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF2_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRL_CNF0_POS)

#define GPIO_CRL_CNF2_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRL_CNF2_POS)
#define GPIO_CRL_CNF2_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRL_CNF2_POS)
#define GPIO_CRL_CNF2_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRL_CNF2_POS)
#define GPIO_CRL_CNF2_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRL_CNF2_POS)

#define GPIO_CRL_CNF3_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF3_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF3_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRL_CNF0_POS)

#define GPIO_CRL_CNF3_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRL_CNF3_POS)
#define GPIO_CRL_CNF3_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRL_CNF3_POS)
#define GPIO_CRL_CNF3_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRL_CNF3_POS)
#define GPIO_CRL_CNF3_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRL_CNF3_POS)

#define GPIO_CRL_CNF4_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF4_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF4_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRL_CNF0_POS)

#define GPIO_CRL_CNF4_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRL_CNF4_POS)
#define GPIO_CRL_CNF4_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRL_CNF4_POS)
#define GPIO_CRL_CNF4_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRL_CNF4_POS)
#define GPIO_CRL_CNF4_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRL_CNF4_POS)

#define GPIO_CRL_CNF5_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF5_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF5_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRL_CNF0_POS)

#define GPIO_CRL_CNF5_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRL_CNF5_POS)
#define GPIO_CRL_CNF5_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRL_CNF5_POS)
#define GPIO_CRL_CNF5_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRL_CNF5_POS)
#define GPIO_CRL_CNF5_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRL_CNF5_POS)

#define GPIO_CRL_CNF6_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF6_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF6_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRL_CNF0_POS)

#define GPIO_CRL_CNF6_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRL_CNF6_POS)
#define GPIO_CRL_CNF6_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRL_CNF6_POS)
#define GPIO_CRL_CNF6_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRL_CNF6_POS)
#define GPIO_CRL_CNF6_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRL_CNF6_POS)

#define GPIO_CRL_CNF7_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF7_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRL_CNF0_POS)
#define GPIO_CRL_CNF7_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRL_CNF0_POS)

#define GPIO_CRL_CNF7_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRL_CNF7_POS)
#define GPIO_CRL_CNF7_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRL_CNF7_POS)
#define GPIO_CRL_CNF7_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRL_CNF7_POS)
#define GPIO_CRL_CNF7_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRL_CNF7_POS)


#define GPIO_CRH_CNF8_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF8_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF8_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRH_CNF0_POS)

#define GPIO_CRH_CNF8_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRH_CNF8_POS)
#define GPIO_CRH_CNF8_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRH_CNF8_POS)
#define GPIO_CRH_CNF8_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRH_CNF8_POS)
#define GPIO_CRH_CNF8_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRH_CNF8_POS)

#define GPIO_CRH_CNF9_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF9_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF9_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRH_CNF0_POS)

#define GPIO_CRH_CNF9_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRH_CNF9_POS)
#define GPIO_CRH_CNF9_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRH_CNF9_POS)
#define GPIO_CRH_CNF9_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRH_CNF9_POS)
#define GPIO_CRH_CNF9_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRH_CNF9_POS)

#define GPIO_CRH_CNF10_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF10_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF10_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRH_CNF0_POS)

#define GPIO_CRH_CNF10_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRH_CNF10_POS)
#define GPIO_CRH_CNF10_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRH_CNF10_POS)
#define GPIO_CRH_CNF10_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRH_CNF10_POS)
#define GPIO_CRH_CNF10_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRH_CNF10_POS)

#define GPIO_CRH_CNF11_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF11_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF11_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRH_CNF0_POS)

#define GPIO_CRH_CNF11_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRH_CNF11_POS)
#define GPIO_CRH_CNF11_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRH_CNF11_POS)
#define GPIO_CRH_CNF11_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRH_CNF11_POS)
#define GPIO_CRH_CNF11_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRH_CNF11_POS)

#define GPIO_CRH_CNF12_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF12_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF12_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRH_CNF0_POS)

#define GPIO_CRH_CNF12_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRH_CNF12_POS)
#define GPIO_CRH_CNF12_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRH_CNF12_POS)
#define GPIO_CRH_CNF12_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRH_CNF12_POS)
#define GPIO_CRH_CNF12_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRH_CNF12_POS)

#define GPIO_CRH_CNF13_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF13_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF13_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRH_CNF0_POS)

#define GPIO_CRH_CNF13_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRH_CNF13_POS)
#define GPIO_CRH_CNF13_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRH_CNF13_POS)
#define GPIO_CRH_CNF13_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRH_CNF13_POS)
#define GPIO_CRH_CNF13_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRH_CNF13_POS)

#define GPIO_CRH_CNF14_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF14_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF14_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRH_CNF0_POS)

#define GPIO_CRH_CNF14_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRH_CNF14_POS)
#define GPIO_CRH_CNF14_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRH_CNF14_POS)
#define GPIO_CRH_CNF14_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRH_CNF14_POS)
#define GPIO_CRH_CNF14_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRH_CNF14_POS)

#define GPIO_CRH_CNF15_INPUT_ANALOG             (GPIO_CNF_INPUT_ANALOG<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF15_INPUT_FLOATING           (GPIO_CNF_INPUT_FLOATING<<GPIO_CRH_CNF0_POS)
#define GPIO_CRH_CNF15_INPUT_PULL_UP_DOWN       (GPIO_CNF_INPUT_PULL_UP_DOWN<<GPIO_CRH_CNF0_POS)

#define GPIO_CRH_CNF15_OUTPUT_PUSH_PULL_GENERAL_PURPOSE      (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE<<GPIO_CRH_CNF15_POS)
#define GPIO_CRH_CNF15_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE     (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE<<GPIO_CRH_CNF15_POS)
#define GPIO_CRH_CNF15_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION   (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION<<GPIO_CRH_CNF15_POS)
#define GPIO_CRH_CNF15_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION  (GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION<<GPIO_CRH_CNF15_POS)


#define GPIO_CRL_MODE_INPUT             (GPIO_MODE_INPUT<<GPIO_CRL_MODE_POS)
#define GPIO_CRL_MODE_OUTPUT_10MHZ      (GPIO_MODE_OUTPUT_10MHZ<<GPIO_CRL_MODE_POS)
#define GPIO_CRL_MODE_OUTPUT_2MHZ       (GPIO_MODE_OUTPUT_2MHZ<<GPIO_CRL_MODE_POS)
#define GPIO_CRL_MODE_OUTPUT_50MHZ      (GPIO_MODE_OUTPUT_50MHZ<<GPIO_CRL_MODE_POS)




/***************** 4.2- GPIO->ODR  ***************/

#define GPIO_ODR_LOGIC_HIGH     (1)
#define GPIO_ODR_LOGIC_LOW      (0)

#define GPIO_ODR_PIN0_POS       (0)
#define GPIO_ODR_PIN1_POS       (1)
#define GPIO_ODR_PIN2_POS       (2)
#define GPIO_ODR_PIN3_POS       (3)
#define GPIO_ODR_PIN4_POS       (4)
#define GPIO_ODR_PIN5_POS       (5)
#define GPIO_ODR_PIN6_POS       (6)
#define GPIO_ODR_PIN7_POS       (7)
#define GPIO_ODR_PIN8_POS       (8)
#define GPIO_ODR_PIN9_POS       (9)
#define GPIO_ODR_PIN10_POS      (10)
#define GPIO_ODR_PIN11_POS      (11)
#define GPIO_ODR_PIN12_POS      (12)
#define GPIO_ODR_PIN13_POS      (13)
#define GPIO_ODR_PIN14_POS      (14)
#define GPIO_ODR_PIN15_POS      (15)

#define GPIO_ODR_PIN0_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN0_POS)
#define GPIO_ODR_PIN1_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN1_POS)
#define GPIO_ODR_PIN2_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN2_POS)
#define GPIO_ODR_PIN3_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN3_POS)
#define GPIO_ODR_PIN4_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN4_POS)
#define GPIO_ODR_PIN5_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN5_POS)
#define GPIO_ODR_PIN6_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN6_POS)
#define GPIO_ODR_PIN7_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN7_POS)
#define GPIO_ODR_PIN8_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN8_POS)
#define GPIO_ODR_PIN9_SET       (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN9_POS)
#define GPIO_ODR_PIN10_SET      (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN10_POS)
#define GPIO_ODR_PIN11_SET      (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN11_POS)
#define GPIO_ODR_PIN12_SET      (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN12_POS)
#define GPIO_ODR_PIN13_SET      (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN13_POS)
#define GPIO_ODR_PIN14_SET      (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN14_POS)
#define GPIO_ODR_PIN15_SET      (GPIO_ODR_LOGIC_HIGH<<GPIO_ODR_PIN15_POS)



/***************** 4.3- GPIO->BSRR  ***************/

#define GPIO_BSRR_PIN0_SET_POS      (0)
#define GPIO_BSRR_PIN1_SET_POS      (1)
#define GPIO_BSRR_PIN2_SET_POS      (2)
#define GPIO_BSRR_PIN3_SET_POS      (3)
#define GPIO_BSRR_PIN4_SET_POS      (4)
#define GPIO_BSRR_PIN5_SET_POS      (5)
#define GPIO_BSRR_PIN6_SET_POS      (6)
#define GPIO_BSRR_PIN7_SET_POS      (7)
#define GPIO_BSRR_PIN8_SET_POS      (8)
#define GPIO_BSRR_PIN9_SET_POS      (9)
#define GPIO_BSRR_PIN10_SET_POS      (10)
#define GPIO_BSRR_PIN11_SET_POS      (11)
#define GPIO_BSRR_PIN12_SET_POS      (12)
#define GPIO_BSRR_PIN13_SET_POS      (13)
#define GPIO_BSRR_PIN14_SET_POS      (14)
#define GPIO_BSRR_PIN15_SET_POS      (15)

#define GPIO_BSRR_PIN0_RESET_POS      (0 + 16)
#define GPIO_BSRR_PIN1_RESET_POS      (1 + 16)
#define GPIO_BSRR_PIN2_RESET_POS      (2 + 16)
#define GPIO_BSRR_PIN3_RESET_POS      (3 + 16)
#define GPIO_BSRR_PIN4_RESET_POS      (4 + 16)
#define GPIO_BSRR_PIN5_RESET_POS      (5 + 16)
#define GPIO_BSRR_PIN6_RESET_POS      (6 + 16)
#define GPIO_BSRR_PIN7_RESET_POS      (7 + 16)
#define GPIO_BSRR_PIN8_RESET_POS      (8 + 16)
#define GPIO_BSRR_PIN9_RESET_POS      (9 + 16)
#define GPIO_BSRR_PIN10_RESET_POS      (10 + 16)
#define GPIO_BSRR_PIN11_RESET_POS      (11 + 16)
#define GPIO_BSRR_PIN12_RESET_POS      (12 + 16)
#define GPIO_BSRR_PIN13_RESET_POS      (13 + 16)
#define GPIO_BSRR_PIN14_RESET_POS      (14 + 16)
#define GPIO_BSRR_PIN15_RESET_POS      (15 + 16)


#define GPIO_BSRR_PIN0_SET      (1<<GPIO_BSRR_PIN0_SET_POS)
#define GPIO_BSRR_PIN1_SET      (1<<GPIO_BSRR_PIN1_SET_POS)
#define GPIO_BSRR_PIN2_SET      (1<<GPIO_BSRR_PIN2_SET_POS)
#define GPIO_BSRR_PIN3_SET      (1<<GPIO_BSRR_PIN3_SET_POS)
#define GPIO_BSRR_PIN4_SET      (1<<GPIO_BSRR_PIN4_SET_POS)
#define GPIO_BSRR_PIN5_SET      (1<<GPIO_BSRR_PIN5_SET_POS)
#define GPIO_BSRR_PIN6_SET      (1<<GPIO_BSRR_PIN6_SET_POS)
#define GPIO_BSRR_PIN7_SET      (1<<GPIO_BSRR_PIN7_SET_POS)
#define GPIO_BSRR_PIN8_SET      (1<<GPIO_BSRR_PIN8_SET_POS)
#define GPIO_BSRR_PIN9_SET      (1<<GPIO_BSRR_PIN9_SET_POS)
#define GPIO_BSRR_PIN10_SET      (1<<GPIO_BSRR_PIN10_SET_POS)
#define GPIO_BSRR_PIN11_SET      (1<<GPIO_BSRR_PIN11_SET_POS)
#define GPIO_BSRR_PIN12_SET      (1<<GPIO_BSRR_PIN12_SET_POS)
#define GPIO_BSRR_PIN13_SET      (1<<GPIO_BSRR_PIN13_SET_POS)
#define GPIO_BSRR_PIN14_SET      (1<<GPIO_BSRR_PIN14_SET_POS)
#define GPIO_BSRR_PIN15_SET      (1<<GPIO_BSRR_PIN15_SET_POS)

#define GPIO_BSRR_PIN0_RESET      (1<<GPIO_BSRR_PIN0_RESET_POS)
#define GPIO_BSRR_PIN1_RESET      (1<<GPIO_BSRR_PIN1_RESET_POS)
#define GPIO_BSRR_PIN2_RESET      (1<<GPIO_BSRR_PIN2_RESET_POS)
#define GPIO_BSRR_PIN3_RESET      (1<<GPIO_BSRR_PIN3_RESET_POS)
#define GPIO_BSRR_PIN4_RESET      (1<<GPIO_BSRR_PIN4_RESET_POS)
#define GPIO_BSRR_PIN5_RESET      (1<<GPIO_BSRR_PIN5_RESET_POS)
#define GPIO_BSRR_PIN6_RESET      (1<<GPIO_BSRR_PIN6_RESET_POS)
#define GPIO_BSRR_PIN7_RESET      (1<<GPIO_BSRR_PIN7_RESET_POS)
#define GPIO_BSRR_PIN8_RESET      (1<<GPIO_BSRR_PIN8_RESET_POS)
#define GPIO_BSRR_PIN9_RESET      (1<<GPIO_BSRR_PIN9_RESET_POS)
#define GPIO_BSRR_PIN10_RESET      (1<<GPIO_BSRR_PIN10_RESET_POS)
#define GPIO_BSRR_PIN11_RESET      (1<<GPIO_BSRR_PIN11_RESET_POS)
#define GPIO_BSRR_PIN12_RESET      (1<<GPIO_BSRR_PIN12_RESET_POS)
#define GPIO_BSRR_PIN13_RESET      (1<<GPIO_BSRR_PIN13_RESET_POS)
#define GPIO_BSRR_PIN14_RESET      (1<<GPIO_BSRR_PIN14_RESET_POS)
#define GPIO_BSRR_PIN15_RESET      (1<<GPIO_BSRR_PIN15_RESET_POS)

/***************** 4.3- GPIO->BRR  ***************/

#define GPIO_BRR_PIN0_RESET_POS      (0)
#define GPIO_BRR_PIN1_RESET_POS      (1)
#define GPIO_BRR_PIN2_RESET_POS      (2)
#define GPIO_BRR_PIN3_RESET_POS      (3)
#define GPIO_BRR_PIN4_RESET_POS      (4)
#define GPIO_BRR_PIN5_RESET_POS      (5)
#define GPIO_BRR_PIN6_RESET_POS      (6)
#define GPIO_BRR_PIN7_RESET_POS      (7)
#define GPIO_BRR_PIN8_RESET_POS      (8)
#define GPIO_BRR_PIN9_RESET_POS      (9)
#define GPIO_BRR_PIN10_RESET_POS      (10)
#define GPIO_BRR_PIN11_RESET_POS      (11)
#define GPIO_BRR_PIN12_RESET_POS      (12)
#define GPIO_BRR_PIN13_RESET_POS      (13)
#define GPIO_BRR_PIN14_RESET_POS      (14)
#define GPIO_BRR_PIN15_RESET_POS      (15)


#define GPIO_BRR_PIN0_RESET      (1<<GPIO_BRR_PIN0_RESET_POS)
#define GPIO_BRR_PIN1_RESET      (1<<GPIO_BRR_PIN1_RESET_POS)
#define GPIO_BRR_PIN2_RESET      (1<<GPIO_BRR_PIN2_RESET_POS)
#define GPIO_BRR_PIN3_RESET      (1<<GPIO_BRR_PIN3_RESET_POS)
#define GPIO_BRR_PIN4_RESET      (1<<GPIO_BRR_PIN4_RESET_POS)
#define GPIO_BRR_PIN5_RESET      (1<<GPIO_BRR_PIN5_RESET_POS)
#define GPIO_BRR_PIN6_RESET      (1<<GPIO_BRR_PIN6_RESET_POS)
#define GPIO_BRR_PIN7_RESET      (1<<GPIO_BRR_PIN7_RESET_POS)
#define GPIO_BRR_PIN8_RESET      (1<<GPIO_BRR_PIN8_RESET_POS)
#define GPIO_BRR_PIN9_RESET      (1<<GPIO_BRR_PIN9_RESET_POS)
#define GPIO_BRR_PIN10_RESET      (1<<GPIO_BRR_PIN10_RESET_POS)
#define GPIO_BRR_PIN11_RESET      (1<<GPIO_BRR_PIN11_RESET_POS)
#define GPIO_BRR_PIN12_RESET      (1<<GPIO_BRR_PIN12_RESET_POS)
#define GPIO_BRR_PIN13_RESET      (1<<GPIO_BRR_PIN13_RESET_POS)
#define GPIO_BRR_PIN14_RESET      (1<<GPIO_BRR_PIN14_RESET_POS)
#define GPIO_BRR_PIN15_RESET      (1<<GPIO_BRR_PIN15_RESET_POS)

/***************** 4.4- GPIO->LCKR  ***************/


#define GPIO_LCKR_LCKK_POS           (16)

#define GPIO_LCKR_PIN0_LOCK_POS      (0)
#define GPIO_LCKR_PIN1_LOCK_POS      (1)
#define GPIO_LCKR_PIN2_LOCK_POS      (2)
#define GPIO_LCKR_PIN3_LOCK_POS      (3)
#define GPIO_LCKR_PIN4_LOCK_POS      (4)
#define GPIO_LCKR_PIN5_LOCK_POS      (5)
#define GPIO_LCKR_PIN6_LOCK_POS      (6)
#define GPIO_LCKR_PIN7_LOCK_POS      (7)
#define GPIO_LCKR_PIN8_LOCK_POS      (8)
#define GPIO_LCKR_PIN9_LOCK_POS      (9)
#define GPIO_LCKR_PIN10_LOCK_POS      (10)
#define GPIO_LCKR_PIN11_LOCK_POS      (11)
#define GPIO_LCKR_PIN12_LOCK_POS      (12)
#define GPIO_LCKR_PIN13_LOCK_POS      (13)
#define GPIO_LCKR_PIN14_LOCK_POS      (14)
#define GPIO_LCKR_PIN15_LOCK_POS      (15)

#define GPIO_LCKR_LCKK_LOCK_SEQ_1      (1<<GPIO_LCKR_LCKK_POS)
#define GPIO_LCKR_LCKK_LOCK_SEQ_2      (0<<GPIO_LCKR_LCKK_POS)
#define GPIO_LCKR_LCKK_LOCK_SEQ_3      (1<<GPIO_LCKR_LCKK_POS)

#define GPIO_LCKR_PIN0_LOCK      (1<<GPIO_LCKR_PIN0_LOCK_POS)
#define GPIO_LCKR_PIN1_LOCK      (1<<GPIO_LCKR_PIN1_LOCK_POS)
#define GPIO_LCKR_PIN2_LOCK      (1<<GPIO_LCKR_PIN2_LOCK_POS)
#define GPIO_LCKR_PIN3_LOCK      (1<<GPIO_LCKR_PIN3_LOCK_POS)
#define GPIO_LCKR_PIN4_LOCK      (1<<GPIO_LCKR_PIN4_LOCK_POS)
#define GPIO_LCKR_PIN5_LOCK      (1<<GPIO_LCKR_PIN5_LOCK_POS)
#define GPIO_LCKR_PIN6_LOCK      (1<<GPIO_LCKR_PIN6_LOCK_POS)
#define GPIO_LCKR_PIN7_LOCK      (1<<GPIO_LCKR_PIN7_LOCK_POS)
#define GPIO_LCKR_PIN8_LOCK      (1<<GPIO_LCKR_PIN8_LOCK_POS)
#define GPIO_LCKR_PIN9_LOCK      (1<<GPIO_LCKR_PIN9_LOCK_POS)
#define GPIO_LCKR_PIN10_LOCK      (1<<GPIO_LCKR_PIN10_LOCK_POS)
#define GPIO_LCKR_PIN11_LOCK      (1<<GPIO_LCKR_PIN11_LOCK_POS)
#define GPIO_LCKR_PIN12_LOCK      (1<<GPIO_LCKR_PIN12_LOCK_POS)
#define GPIO_LCKR_PIN13_LOCK      (1<<GPIO_LCKR_PIN13_LOCK_POS)
#define GPIO_LCKR_PIN14_LOCK      (1<<GPIO_LCKR_PIN14_LOCK_POS)
#define GPIO_LCKR_PIN15_LOCK      (1<<GPIO_LCKR_PIN15_LOCK_POS)


/***************************************************************/
/*					    	(10) _AFIO						   */
/***************************************************************/

/*
 * 	_AFIO Section Architecture Map
 *		1- _AFIO->Base_Definitions
 *		2- _AFIO->Registers_Pointers
 *		3- _AFIO->Struct_Definition
 *		4- _AFIO->Registers_Values_Definitions
 *			4.1- _AFIO->EVCR
 *			4.2- _AFIO->MAPR
 *			4.3- _AFIO->EXTICR
 *			4.4- _AFIO->MAPR2
 *
 *
 * */


/***************** 1- _AFIO->Base_Definition ******************/

#define AFIO_BASE               (0x40010000)

#define AFIO_EVCR_BASE          (AFIO_BASE + 0x00)
#define AFIO_MAPR_BASE          (AFIO_BASE + 0x04)


#define AFIO_EXTI_BASE          (AFIO_BASE + 0x08)

#define  AFIO_EXTICR1_BASE          ( AFIO_EXTI_BASE + 0x00)
#define  AFIO_EXTICR2_BASE          ( AFIO_EXTI_BASE + 0x04)
#define  AFIO_EXTICR3_BASE          ( AFIO_EXTI_BASE + 0x08)
#define  AFIO_EXTICR4_BASE          ( AFIO_EXTI_BASE + 0x0C)

#define AFIO_MAPR2_BASE          (AFIO_BASE + 0x1C)


/***************** 2- _AFIO->Registers_Pointers ***************/

#define AFIO_EVCR           (*((volatile unsigned long *)AFIO_EVCR_BASE))
#define AFIO_MAPR           (*((volatile unsigned long *)AFIO_MAPR_BASE))

#define  AFIO_EXTICR1         (*((volatile unsigned long *) AFIO_EXTICR1_BASE))
#define  AFIO_EXTICR2         (*((volatile unsigned long *) AFIO_EXTICR2_BASE))
#define  AFIO_EXTICR3         (*((volatile unsigned long *) AFIO_EXTICR3_BASE))
#define  AFIO_EXTICR4         (*((volatile unsigned long *) AFIO_EXTICR4_BASE))

#define AFIO_MAPR2           (*((volatile unsigned long *)AFIO_MAPR2_BASE))

/***************** 3- _AFIO->Struct_Definition ****************/

#define pAFIO        ((volatile AFIO_t *)AFIO_BASE)


typedef volatile struct {
    volatile union {
        struct {
            unsigned long PIN: 4;
            unsigned long PORT: 3;
            unsigned long EVOE: 1;
            const unsigned long RESERVED: 24;
        };
        unsigned long REG;
    } EVCR;

    volatile union {
        struct {
            unsigned long SPI1_REMAP: 1;
            unsigned long I2C1_REMAP: 1;
            unsigned long USART1_REMAP: 1;
            unsigned long USART2_REMAP: 1;
            unsigned long USART3_REMAP: 2;
            unsigned long TIM1_REMAP: 2;
            unsigned long TIM2_REMAP: 2;
            unsigned long TIM3_REMAP: 2;
            unsigned long TIM4_REMAP: 1;
            unsigned long CAN_REMAP: 2;
            unsigned long PD01_REMAP: 1;
            unsigned long TIM5CH4_IREMAP: 1;
            unsigned long ADC1_ETRGINJ_REMAP: 1;
            unsigned long ADC1_ETRGREG_REMAP: 1;
            unsigned long ADC2_ETRGINJ_REMAP: 1;
            unsigned long ADC2_ETRGREG_REMAP: 1;
            const unsigned long RESERVED: 3;
            unsigned long SWJ_CFG: 3;
            const unsigned long              : 5;
        } BITS;
        unsigned long REG;
    } MAPR;

    volatile union {
        volatile struct {

            unsigned long REG;

        } EXTICR[4];

        struct {
            union {
                struct {
                    unsigned long EXTI0: 4;
                    unsigned long EXTI1: 4;
                    unsigned long EXTI2: 4;
                    unsigned long EXTI3: 4;
                    const unsigned long RESERVED: 16;
                } BITS;

                unsigned long REG;
            } EXTICR0;
            union {
                struct {
                    unsigned long EXTI4: 4;
                    unsigned long EXTI5: 4;
                    unsigned long EXTI6: 4;
                    unsigned long EXTI7: 4;
                    const unsigned long RESERVED: 16;
                } BITS;

                unsigned long REG;
            } EXTICR1;

            union {
                struct {
                    unsigned long EXTI8: 4;
                    unsigned long EXTI9: 4;
                    unsigned long EXTI10: 4;
                    unsigned long EXTI11: 4;
                    const unsigned long RESERVED: 16;
                } BITS;

                unsigned long REG;
            } EXTICR2;

            union {
                struct {
                    unsigned long EXTI12: 4;
                    unsigned long EXTI13: 4;
                    unsigned long EXTI14: 4;
                    unsigned long EXTI15: 4;
                    const unsigned long RESERVED: 16;
                } BITS;

                unsigned long REG;
            } EXTICR3;
        };
    };
    const unsigned long RESERVED;

    volatile union {
        struct {
            const unsigned long RESERVED: 5;
            unsigned long TIM9_REMAP: 1;
            unsigned long TIM10_REMAP: 1;
            unsigned long TIM11_REMAP: 1;
            unsigned long TIM13_REMAP: 1;
            unsigned long TIM14_REMAP: 1;
            unsigned long FSMC_NADV: 1;
            const unsigned long RESERVED: 21;
        } BITS;
        unsigned long REG;
    } MAPR2;
} AFIO_t;


/***************** 4- _AFIO->Registers_Values_Definitions *****/

/***************** 4.1- _AFIO->EVCR  ***************/

#define AFIO_PIN0             (0)
#define AFIO_PIN1             (1)
#define AFIO_PIN2             (2)
#define AFIO_PIN3             (3)
#define AFIO_PIN4             (4)
#define AFIO_PIN5             (5)
#define AFIO_PIN6             (6)
#define AFIO_PIN7             (7)
#define AFIO_PIN8             (8)
#define AFIO_PIN9             (9)
#define AFIO_PIN10             (10)
#define AFIO_PIN11             (11)
#define AFIO_PIN12             (12)
#define AFIO_PIN13             (13)
#define AFIO_PIN14             (14)
#define AFIO_PIN15             (15)

#define AFIO_PORTA          (0)
#define AFIO_PORTB          (1)
#define AFIO_PORTC          (2)
#define AFIO_PORTD          (3)
#define AFIO_PORTE          (4)

#define AFIO_EVOE_EVENT_OUTPUT_ENABLE        (1)
#define AFIO_EVOE_EVENT_OUTPUT_DISABLE       (0)

/***************** 4.2- _AFIO->MAPR  ***************/
/*
// TODO: Remaping functions


//#define AFIO_MAPR_SPI1_REMAP_POS             (0)
//#define AFIO_MAPR_I2C1_REMAP_POS             (1)
//#define AFIO_MAPR_USART1_REMAP_POS           (2)
//#define AFIO_MAPR_USART2_REMAP_POS           (3)
//#define AFIO_MAPR_USART3_REMAP_POS           (4)
//#define AFIO_MAPR_TIM1_REMAP_POS             (6)
//#define AFIO_MAPR_TIM2_REMAP_POS             (8)
//#define AFIO_MAPR_TIM3_REMAP_POS             (10)
//#define AFIO_MAPR_TIM4_REMAP_POS             (12)
//#define AFIO_MAPR_CAN_REMAP_POS              (13)
//#define AFIO_MAPR_PD01_REMAP_POS             (15)
//#define AFIO_MAPR_TIM5CH4_IREMAP_POS         (16)
//#define AFIO_MAPR_ADC1_ETRGINJ_REMAP_POS     (17)
//#define AFIO_MAPR_ADC1_ETRGREG_REMAP_POS     (18)
//#define AFIO_MAPR_ADC2_ETRGINJ_REMAP_POS     (19)
//#define AFIO_MAPR_ADC2_ETRGREG_REMAP_POS     (20)
//#define AFIO_MAPR_SWJ_CFG_POS                (24)
//
//#define AFIO_NO_REMAP           (0)
//
//#define AFIO_MAPR_SPI1_NO_REMAP_PA4_PA5_PA6_PA7            (0<<AFIO_MAPR_SPI1_REMAP_POS)
//#define AFIO_MAPR_SPI1_REMAP_PA15_PB3_PB4_PB5            (1<<AFIO_MAPR_SPI1_REMAP_POS)
//
//#define AFIO_MAPR_I2C1_NO_REMAP_PB6_PB7            (0<<AFIO_MAPR_I2C1_REMAP_POS)
//#define AFIO_MAPR_I2C1_REMAP_PB8_PB9            (1<<AFIO_MAPR_I2C1_REMAP_POS)
//
//
//#define AFIO_MAPR_USART1_NO_REMAP_PA9_PA10            (1<<AFIO_MAPR_USART1_REMAP_POS)
//#define AFIO_MAPR_USART2_REMAP_PB6_PB7            (1<<AFIO_MAPR_USART2_REMAP_POS)
//
//#define AFIO_MAPR_USART3_PARTIAL_REMAP            (1<<AFIO_MAPR_USART3_REMAP_POS)
//#define AFIO_MAPR_USART3_FULL_REMAP            (3<<AFIO_MAPR_USART3_REMAP_POS)
//
//#define AFIO_MAPR_TIM1_PARTIAL_REMAP             (1<<AFIO_MAPR_TIM1_REMAP_POS)
//#define AFIO_MAPR_TIM1_FULL_REMAP            (3<<AFIO_MAPR_TIM1_REMAP_POS)
//
//#define AFIO_MAPR_TIM2_PARTIAL_REMAP_PA15_PB3_PA2_PA3            (1<<AFIO_MAPR_TIM2_REMAP_POS)
//#define AFIO_MAPR_TIM2_PARTIAL_REMAP_PA0_PA1_PB10_PB11            (2<<AFIO_MAPR_TIM2_REMAP_POS)
//#define AFIO_MAPR_TIM2_FULL_REMAP_PA15_PB3_PB10_PB11            (3<<AFIO_MAPR_TIM2_REMAP_POS)
//
//#define AFIO_MAPR_TIM3_PARTIAL_REMAP_PB4_PB5_PB0_PB1            (1<<AFIO_MAPR_TIM3_REMAP_POS)
//#define AFIO_MAPR_TIM3_FULL_REMAP_PC6_PC7_PC8_PC9            (1<<AFIO_MAPR_TIM3_REMAP_POS)
//
//#define AFIO_MAPR_TIM4_REMAP            (1<<AFIO_MAPR_TIM4_REMAP_POS)
//
//#define AFIO_MAPR_CAN_REMAP            (1<<AFIO_MAPR_CAN_REMAP_POS)
//
//#define AFIO_MAPR_PD01_REMAP            (1<<AFIO_MAPR_PD01_REMAP_POS)
//#define AFIO_MAPR_TIM5CH4_IREMAP            (1<<AFIO_MAPR_TIM5CH4_IREMAP_POS)
//#define AFIO_MAPR_ADC1_ETRGINJ_REMAP            (1<<AFIO_MAPR_ADC1_ETRGINJ_REMAP_POS)
//#define AFIO_MAPR_ADC1_ETRGREG_REMAP            (1<<AFIO_MAPR_ADC1_ETRGREG_REMAP_POS)
//#define AFIO_MAPR_ADC2_ETRGINJ_REMAP            (1<<AFIO_MAPR_ADC2_ETRGINJ_REMAP_POS)
//#define AFIO_MAPR_ADC2_ETRGREG_REMAP            (1<<AFIO_MAPR_ADC2_ETRGREG_REMAP_POS)
//
//#define AFIO_MAPR_SWJ_CFG            (1<<AFIO_MAPR_SWJ_CFG_POS)

*/
/***************** 4.3- _AFIO->EXTICR  ***************/

#define AFIO_EXTIx_PA        (0)
#define AFIO_EXTIx_PB        (1)
#define AFIO_EXTIx_PC        (2)
#define AFIO_EXTIx_PD        (3)
#define AFIO_EXTIx_PE        (4)
#define AFIO_EXTIx_PF        (5)
#define AFIO_EXTIx_PG        (6)

#define AFIO_EXTICR1_EXTI0_POS       (0)
#define AFIO_EXTICR1_EXTI1_POS       (1)
#define AFIO_EXTICR1_EXTI2_POS       (2)
#define AFIO_EXTICR1_EXTI3_POS       (3)

#define AFIO_EXTICR2_EXTI4_POS       (0)
#define AFIO_EXTICR2_EXTI5_POS       (1)
#define AFIO_EXTICR2_EXTI6_POS       (2)
#define AFIO_EXTICR2_EXTI7_POS       (3)

#define AFIO_EXTICR3_EXTI8_POS       (0)
#define AFIO_EXTICR3_EXTI9_POS       (1)
#define AFIO_EXTICR3_EXTI10_POS      (2)
#define AFIO_EXTICR3_EXTI11_POS      (3)

#define AFIO_EXTICR4_EXTI12_POS      (0)
#define AFIO_EXTICR4_EXTI13_POS      (1)
#define AFIO_EXTICR4_EXTI14_POS      (2)
#define AFIO_EXTICR4_EXTI15_POS      (3)


#define AFIO_EXTICR1_EXTI0_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR1_EXTI0_POS)
#define AFIO_EXTICR1_EXTI0_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR1_EXTI0_POS)
#define AFIO_EXTICR1_EXTI0_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR1_EXTI0_POS)
#define AFIO_EXTICR1_EXTI0_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR1_EXTI0_POS)
#define AFIO_EXTICR1_EXTI0_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR1_EXTI0_POS)
#define AFIO_EXTICR1_EXTI0_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR1_EXTI0_POS)
#define AFIO_EXTICR1_EXTI0_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR1_EXTI0_POS)

#define AFIO_EXTICR1_EXTI1_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR1_EXTI1_POS)
#define AFIO_EXTICR1_EXTI1_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR1_EXTI1_POS)
#define AFIO_EXTICR1_EXTI1_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR1_EXTI1_POS)
#define AFIO_EXTICR1_EXTI1_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR1_EXTI1_POS)
#define AFIO_EXTICR1_EXTI1_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR1_EXTI1_POS)
#define AFIO_EXTICR1_EXTI1_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR1_EXTI1_POS)
#define AFIO_EXTICR1_EXTI1_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR1_EXTI1_POS)

#define AFIO_EXTICR1_EXTI2_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR1_EXTI2_POS)
#define AFIO_EXTICR1_EXTI2_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR1_EXTI2_POS)
#define AFIO_EXTICR1_EXTI2_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR1_EXTI2_POS)
#define AFIO_EXTICR1_EXTI2_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR1_EXTI2_POS)
#define AFIO_EXTICR1_EXTI2_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR1_EXTI2_POS)
#define AFIO_EXTICR1_EXTI2_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR1_EXTI2_POS)
#define AFIO_EXTICR1_EXTI2_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR1_EXTI2_POS)

#define AFIO_EXTICR1_EXTI3_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR1_EXTI3_POS)
#define AFIO_EXTICR1_EXTI3_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR1_EXTI3_POS)
#define AFIO_EXTICR1_EXTI3_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR1_EXTI3_POS)
#define AFIO_EXTICR1_EXTI3_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR1_EXTI3_POS)
#define AFIO_EXTICR1_EXTI3_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR1_EXTI3_POS)
#define AFIO_EXTICR1_EXTI3_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR1_EXTI3_POS)
#define AFIO_EXTICR1_EXTI3_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR1_EXTI3_POS)


#define AFIO_EXTICR2_EXTI4_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR2_EXTI4_POS)
#define AFIO_EXTICR2_EXTI4_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR2_EXTI4_POS)
#define AFIO_EXTICR2_EXTI4_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR2_EXTI4_POS)
#define AFIO_EXTICR2_EXTI4_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR2_EXTI4_POS)
#define AFIO_EXTICR2_EXTI4_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR2_EXTI4_POS)
#define AFIO_EXTICR2_EXTI4_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR2_EXTI4_POS)
#define AFIO_EXTICR2_EXTI4_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR2_EXTI4_POS)

#define AFIO_EXTICR2_EXTI5_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR2_EXTI5_POS)
#define AFIO_EXTICR2_EXTI5_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR2_EXTI5_POS)
#define AFIO_EXTICR2_EXTI5_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR2_EXTI5_POS)
#define AFIO_EXTICR2_EXTI5_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR2_EXTI5_POS)
#define AFIO_EXTICR2_EXTI5_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR2_EXTI5_POS)
#define AFIO_EXTICR2_EXTI5_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR2_EXTI5_POS)
#define AFIO_EXTICR2_EXTI5_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR2_EXTI5_POS)

#define AFIO_EXTICR2_EXTI6_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR2_EXTI6_POS)
#define AFIO_EXTICR2_EXTI6_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR2_EXTI6_POS)
#define AFIO_EXTICR2_EXTI6_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR2_EXTI6_POS)
#define AFIO_EXTICR2_EXTI6_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR2_EXTI6_POS)
#define AFIO_EXTICR2_EXTI6_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR2_EXTI6_POS)
#define AFIO_EXTICR2_EXTI6_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR2_EXTI6_POS)
#define AFIO_EXTICR2_EXTI6_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR2_EXTI6_POS)

#define AFIO_EXTICR2_EXTI7_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR2_EXTI7_POS)
#define AFIO_EXTICR2_EXTI7_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR2_EXTI7_POS)
#define AFIO_EXTICR2_EXTI7_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR2_EXTI7_POS)
#define AFIO_EXTICR2_EXTI7_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR2_EXTI7_POS)
#define AFIO_EXTICR2_EXTI7_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR2_EXTI7_POS)
#define AFIO_EXTICR2_EXTI7_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR2_EXTI7_POS)
#define AFIO_EXTICR2_EXTI7_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR2_EXTI7_POS)


#define AFIO_EXTICR3_EXTI8_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR3_EXTI8_POS)
#define AFIO_EXTICR3_EXTI8_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR3_EXTI8_POS)
#define AFIO_EXTICR3_EXTI8_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR3_EXTI8_POS)
#define AFIO_EXTICR3_EXTI8_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR3_EXTI8_POS)
#define AFIO_EXTICR3_EXTI8_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR3_EXTI8_POS)
#define AFIO_EXTICR3_EXTI8_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR3_EXTI8_POS)
#define AFIO_EXTICR3_EXTI8_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR3_EXTI8_POS)

#define AFIO_EXTICR3_EXTI9_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR3_EXTI9_POS)
#define AFIO_EXTICR3_EXTI9_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR3_EXTI9_POS)
#define AFIO_EXTICR3_EXTI9_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR3_EXTI9_POS)
#define AFIO_EXTICR3_EXTI9_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR3_EXTI9_POS)
#define AFIO_EXTICR3_EXTI9_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR3_EXTI9_POS)
#define AFIO_EXTICR3_EXTI9_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR3_EXTI9_POS)
#define AFIO_EXTICR3_EXTI9_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR3_EXTI9_POS)

#define AFIO_EXTICR3_EXTI10_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR3_EXTI10_POS)
#define AFIO_EXTICR3_EXTI10_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR3_EXTI10_POS)
#define AFIO_EXTICR3_EXTI10_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR3_EXTI10_POS)
#define AFIO_EXTICR3_EXTI10_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR3_EXTI10_POS)
#define AFIO_EXTICR3_EXTI10_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR3_EXTI10_POS)
#define AFIO_EXTICR3_EXTI10_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR3_EXTI10_POS)
#define AFIO_EXTICR3_EXTI10_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR3_EXTI10_POS)

#define AFIO_EXTICR3_EXTI11_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR3_EXTI11_POS)
#define AFIO_EXTICR3_EXTI11_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR3_EXTI11_POS)
#define AFIO_EXTICR3_EXTI11_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR3_EXTI11_POS)
#define AFIO_EXTICR3_EXTI11_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR3_EXTI11_POS)
#define AFIO_EXTICR3_EXTI11_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR3_EXTI11_POS)
#define AFIO_EXTICR3_EXTI11_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR3_EXTI11_POS)
#define AFIO_EXTICR3_EXTI11_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR3_EXTI11_POS)


#define AFIO_EXTICR4_EXTI12_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR4_EXTI12_POS)
#define AFIO_EXTICR4_EXTI12_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR4_EXTI12_POS)
#define AFIO_EXTICR4_EXTI12_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR4_EXTI12_POS)
#define AFIO_EXTICR4_EXTI12_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR4_EXTI12_POS)
#define AFIO_EXTICR4_EXTI12_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR4_EXTI12_POS)
#define AFIO_EXTICR4_EXTI12_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR4_EXTI12_POS)
#define AFIO_EXTICR4_EXTI12_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR4_EXTI12_POS)

#define AFIO_EXTICR4_EXTI13_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR4_EXTI13_POS)
#define AFIO_EXTICR4_EXTI13_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR4_EXTI13_POS)
#define AFIO_EXTICR4_EXTI13_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR4_EXTI13_POS)
#define AFIO_EXTICR4_EXTI13_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR4_EXTI13_POS)
#define AFIO_EXTICR4_EXTI13_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR4_EXTI13_POS)
#define AFIO_EXTICR4_EXTI13_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR4_EXTI13_POS)
#define AFIO_EXTICR4_EXTI13_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR4_EXTI13_POS)

#define AFIO_EXTICR4_EXTI14_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR4_EXTI14_POS)
#define AFIO_EXTICR4_EXTI14_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR4_EXTI14_POS)
#define AFIO_EXTICR4_EXTI14_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR4_EXTI14_POS)
#define AFIO_EXTICR4_EXTI14_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR4_EXTI14_POS)
#define AFIO_EXTICR4_EXTI14_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR4_EXTI14_POS)
#define AFIO_EXTICR4_EXTI14_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR4_EXTI14_POS)
#define AFIO_EXTICR4_EXTI14_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR4_EXTI14_POS)

#define AFIO_EXTICR4_EXTI15_PA       (AFIO_EXTIx_PA<<AFIO_EXTICR4_EXTI15_POS)
#define AFIO_EXTICR4_EXTI15_PB       (AFIO_EXTIx_PB<<AFIO_EXTICR4_EXTI15_POS)
#define AFIO_EXTICR4_EXTI15_PC       (AFIO_EXTIx_PC<<AFIO_EXTICR4_EXTI15_POS)
#define AFIO_EXTICR4_EXTI15_PD       (AFIO_EXTIx_PD<<AFIO_EXTICR4_EXTI15_POS)
#define AFIO_EXTICR4_EXTI15_PE       (AFIO_EXTIx_PE<<AFIO_EXTICR4_EXTI15_POS)
#define AFIO_EXTICR4_EXTI15_PF       (AFIO_EXTIx_PF<<AFIO_EXTICR4_EXTI15_POS)
#define AFIO_EXTICR4_EXTI15_PG       (AFIO_EXTIx_PG<<AFIO_EXTICR4_EXTI15_POS)


/***************** 4.4- _AFIO->MAPR2  ***************/
// TODO

/***************************************************************/
/*					    	(11) EXTI						   */
/***************************************************************/

/*
 * 	EXTI Section Architecture Map
 *		1- EXTI->Base_Definitions
 *		2- EXTI->Registers_Pointers
 *		3- EXTI->Struct_Definition
 *		4- EXTI->Registers_Values_Definitions
 *			4.1- EXTI->IMR
 *			4.2- EXTI->EMR
 *			4.3- EXTI->RTSR
 *			4.4- EXTI->FTSR
 *			4.5- EXTI->PR
 *
 *
 * */


/***************** 1- EXTI->Base_Definition ******************/

#define EXTI_BASE                (0x40010400U)

#define EXTI_IMR_BASE            (EXTI_BASE + 0x00)
#define EXTI_EMR_BASE            (EXTI_BASE + 0x04)
#define EXTI_RTSR_BASE           (EXTI_BASE + 0x08)
#define EXTI_FTSR_BASE           (EXTI_BASE + 0x0C)
#define EXTI_SWIER_BASE          (EXTI_BASE + 0x10)
#define EXTI_PR_BASE             (EXTI_BASE + 0x14)
/***************** 2- EXTI->Registers_Pointers ***************/

#define EXTI_IMR         (*((volatile unsigned long *)EXTI_IMR_BASE))
#define EXTI_EMR         (*((volatile unsigned long *)EXTI_EMR_BASE))
#define EXTI_RTSR        (*((volatile unsigned long *)EXTI_RTSR_BASE))
#define EXTI_FTSR        (*((volatile unsigned long *)EXTI_FTSR_BASE))
#define EXTI_SWIER       (*((volatile unsigned long *)EXTI_SWIER_BASE))
#define EXTI_PR          (*((volatile unsigned long *)EXTI_PR_BASE))


/***************** 3- EXTI->Struct_Definition ****************/

#define EXTI        ((volatile EXTI_t *)EXTI_BASE)

typedef volatile struct {

    volatile union {
        struct {
            unsigned long IM: 20;
            const unsigned long RESERVED: 12;
        } BITS;
        unsigned long REG;
    } IMR;

    volatile union {
        struct {
            unsigned long EM: 20;
            const unsigned long RESERVED: 12;
        } BITS;
        unsigned long REG;
    } EMR;

    volatile union {
        struct {
            unsigned long TR: 20;
            const unsigned long RESERVED: 12;
        } BITS;
        unsigned long REG;
    } RTSR;

    volatile union {
        struct {
            unsigned long TR: 20;
            const unsigned long RESERVED: 12;
        } BITS;
        unsigned long REG;
    } FTSR;

    volatile union {
        struct {
            unsigned long SWIE: 20;
            const unsigned long RESERVED: 12;
        } BITS;
        unsigned long REG;
    } SWIER;

    volatile union {
        struct {
            unsigned long P: 20;
            const unsigned long RESERVED: 12;
        } BITS;
        unsigned long REG;
    } PR;

} EXTI_t;



/***************** 4- EXTI->Registers_Values_Definitions *****/


#define EXTI_INTERRUPT_0_POS        (0)
#define EXTI_INTERRUPT_1_POS        (1)
#define EXTI_INTERRUPT_2_POS        (2)
#define EXTI_INTERRUPT_3_POS        (3)
#define EXTI_INTERRUPT_4_POS        (4)
#define EXTI_INTERRUPT_5_POS        (5)
#define EXTI_INTERRUPT_6_POS        (6)
#define EXTI_INTERRUPT_7_POS        (7)
#define EXTI_INTERRUPT_8_POS        (8)
#define EXTI_INTERRUPT_9_POS        (9)
#define EXTI_INTERRUPT_10_POS        (10)
#define EXTI_INTERRUPT_11_POS        (11)
#define EXTI_INTERRUPT_12_POS        (12)
#define EXTI_INTERRUPT_13_POS        (13)
#define EXTI_INTERRUPT_14_POS        (14)
#define EXTI_INTERRUPT_15_POS        (15)
#define EXTI_INTERRUPT_16_POS        (16)
#define EXTI_INTERRUPT_17_POS        (17)
#define EXTI_INTERRUPT_18_POS        (18)
#define EXTI_INTERRUPT_19_POS        (19)

#define EXTI_INTERRUPT_0            (1<<EXTI_INTERRUPT_0_POS)
#define EXTI_INTERRUPT_1            (1<<EXTI_INTERRUPT_1_POS)
#define EXTI_INTERRUPT_2            (1<<EXTI_INTERRUPT_2_POS)
#define EXTI_INTERRUPT_3            (1<<EXTI_INTERRUPT_3_POS)
#define EXTI_INTERRUPT_4            (1<<EXTI_INTERRUPT_4_POS)
#define EXTI_INTERRUPT_5            (1<<EXTI_INTERRUPT_5_POS)
#define EXTI_INTERRUPT_6            (1<<EXTI_INTERRUPT_6_POS)
#define EXTI_INTERRUPT_7            (1<<EXTI_INTERRUPT_7_POS)
#define EXTI_INTERRUPT_8            (1<<EXTI_INTERRUPT_8_POS)
#define EXTI_INTERRUPT_9            (1<<EXTI_INTERRUPT_9_POS)
#define EXTI_INTERRUPT_10            (1<<EXTI_INTERRUPT_10_POS)
#define EXTI_INTERRUPT_11            (1<<EXTI_INTERRUPT_11_POS)
#define EXTI_INTERRUPT_12            (1<<EXTI_INTERRUPT_12_POS)
#define EXTI_INTERRUPT_13            (1<<EXTI_INTERRUPT_13_POS)
#define EXTI_INTERRUPT_14            (1<<EXTI_INTERRUPT_14_POS)
#define EXTI_INTERRUPT_15            (1<<EXTI_INTERRUPT_15_POS)
#define EXTI_INTERRUPT_16            (1<<EXTI_INTERRUPT_16_POS)
#define EXTI_INTERRUPT_17            (1<<EXTI_INTERRUPT_17_POS)
#define EXTI_INTERRUPT_18            (1<<EXTI_INTERRUPT_18_POS)
#define EXTI_INTERRUPT_19            (1<<EXTI_INTERRUPT_19_POS)


#define EXTI_EVENT_0_POS        (0)
#define EXTI_EVENT_1_POS        (1)
#define EXTI_EVENT_2_POS        (2)
#define EXTI_EVENT_3_POS        (3)
#define EXTI_EVENT_4_POS        (4)
#define EXTI_EVENT_5_POS        (5)
#define EXTI_EVENT_6_POS        (6)
#define EXTI_EVENT_7_POS        (7)
#define EXTI_EVENT_8_POS        (8)
#define EXTI_EVENT_9_POS        (9)
#define EXTI_EVENT_10_POS        (10)
#define EXTI_EVENT_11_POS        (11)
#define EXTI_EVENT_12_POS        (12)
#define EXTI_EVENT_13_POS        (13)
#define EXTI_EVENT_14_POS        (14)
#define EXTI_EVENT_15_POS        (15)
#define EXTI_EVENT_16_POS        (16)
#define EXTI_EVENT_17_POS        (17)
#define EXTI_EVENT_18_POS        (18)
#define EXTI_EVENT_19_POS        (19)

#define EXTI_EVENT_0            (1<<EXTI_EVENT_0_POS)
#define EXTI_EVENT_1            (1<<EXTI_EVENT_1_POS)
#define EXTI_EVENT_2            (1<<EXTI_EVENT_2_POS)
#define EXTI_EVENT_3            (1<<EXTI_EVENT_3_POS)
#define EXTI_EVENT_4            (1<<EXTI_EVENT_4_POS)
#define EXTI_EVENT_5            (1<<EXTI_EVENT_5_POS)
#define EXTI_EVENT_6            (1<<EXTI_EVENT_6_POS)
#define EXTI_EVENT_7            (1<<EXTI_EVENT_7_POS)
#define EXTI_EVENT_8            (1<<EXTI_EVENT_8_POS)
#define EXTI_EVENT_9            (1<<EXTI_EVENT_9_POS)
#define EXTI_EVENT_10            (1<<EXTI_EVENT_10_POS)
#define EXTI_EVENT_11            (1<<EXTI_EVENT_11_POS)
#define EXTI_EVENT_12            (1<<EXTI_EVENT_12_POS)
#define EXTI_EVENT_13            (1<<EXTI_EVENT_13_POS)
#define EXTI_EVENT_14            (1<<EXTI_EVENT_14_POS)
#define EXTI_EVENT_15            (1<<EXTI_EVENT_15_POS)
#define EXTI_EVENT_16            (1<<EXTI_EVENT_16_POS)
#define EXTI_EVENT_17            (1<<EXTI_EVENT_17_POS)
#define EXTI_EVENT_18            (1<<EXTI_EVENT_18_POS)
#define EXTI_EVENT_19            (1<<EXTI_EVENT_19_POS)

/***************** 4.1- EXTI->IMR  ***************/

#define EXTI_IMR_UNMASK_INTERRUPT_0       (EXTI_INTERRUPT_0)
#define EXTI_IMR_UNMASK_INTERRUPT_1       (EXTI_INTERRUPT_1)
#define EXTI_IMR_UNMASK_INTERRUPT_2       (EXTI_INTERRUPT_2)
#define EXTI_IMR_UNMASK_INTERRUPT_3       (EXTI_INTERRUPT_3)
#define EXTI_IMR_UNMASK_INTERRUPT_4       (EXTI_INTERRUPT_4)
#define EXTI_IMR_UNMASK_INTERRUPT_5       (EXTI_INTERRUPT_5)
#define EXTI_IMR_UNMASK_INTERRUPT_6       (EXTI_INTERRUPT_6)
#define EXTI_IMR_UNMASK_INTERRUPT_7       (EXTI_INTERRUPT_7)
#define EXTI_IMR_UNMASK_INTERRUPT_8       (EXTI_INTERRUPT_8)
#define EXTI_IMR_UNMASK_INTERRUPT_9       (EXTI_INTERRUPT_9)
#define EXTI_IMR_UNMASK_INTERRUPT_10       (EXTI_INTERRUPT_10)
#define EXTI_IMR_UNMASK_INTERRUPT_11       (EXTI_INTERRUPT_11)
#define EXTI_IMR_UNMASK_INTERRUPT_12       (EXTI_INTERRUPT_12)
#define EXTI_IMR_UNMASK_INTERRUPT_13       (EXTI_INTERRUPT_13)
#define EXTI_IMR_UNMASK_INTERRUPT_14       (EXTI_INTERRUPT_14)
#define EXTI_IMR_UNMASK_INTERRUPT_15       (EXTI_INTERRUPT_15)
#define EXTI_IMR_UNMASK_INTERRUPT_16       (EXTI_INTERRUPT_16)
#define EXTI_IMR_UNMASK_INTERRUPT_17       (EXTI_INTERRUPT_17)
#define EXTI_IMR_UNMASK_INTERRUPT_18       (EXTI_INTERRUPT_18)
#define EXTI_IMR_UNMASK_INTERRUPT_19       (EXTI_INTERRUPT_19)



/***************** 4.2- EXTI->EMR  ***************/

#define EXTI_IMR_UNMASK_EVENT_0       (EXTI_EVENT_0)
#define EXTI_IMR_UNMASK_EVENT_1       (EXTI_EVENT_1)
#define EXTI_IMR_UNMASK_EVENT_2       (EXTI_EVENT_2)
#define EXTI_IMR_UNMASK_EVENT_3       (EXTI_EVENT_3)
#define EXTI_IMR_UNMASK_EVENT_4       (EXTI_EVENT_4)
#define EXTI_IMR_UNMASK_EVENT_5       (EXTI_EVENT_5)
#define EXTI_IMR_UNMASK_EVENT_6       (EXTI_EVENT_6)
#define EXTI_IMR_UNMASK_EVENT_7       (EXTI_EVENT_7)
#define EXTI_IMR_UNMASK_EVENT_8       (EXTI_EVENT_8)
#define EXTI_IMR_UNMASK_EVENT_9       (EXTI_EVENT_9)
#define EXTI_IMR_UNMASK_EVENT_10       (EXTI_EVENT_10)
#define EXTI_IMR_UNMASK_EVENT_11       (EXTI_EVENT_11)
#define EXTI_IMR_UNMASK_EVENT_12       (EXTI_EVENT_12)
#define EXTI_IMR_UNMASK_EVENT_13       (EXTI_EVENT_13)
#define EXTI_IMR_UNMASK_EVENT_14       (EXTI_EVENT_14)
#define EXTI_IMR_UNMASK_EVENT_15       (EXTI_EVENT_15)
#define EXTI_IMR_UNMASK_EVENT_16       (EXTI_EVENT_16)
#define EXTI_IMR_UNMASK_EVENT_17       (EXTI_EVENT_17)
#define EXTI_IMR_UNMASK_EVENT_18       (EXTI_EVENT_18)
#define EXTI_IMR_UNMASK_EVENT_19       (EXTI_EVENT_19)


/***************** 4.3- EXTI->RTSR  ***************/

#define EXTI_RTSR_LINE_0_RISING_TRIGGER_ENABLE          (EXTI_EVENT_0)
#define EXTI_RTSR_LINE_1_RISING_TRIGGER_ENABLE          (EXTI_EVENT_1)
#define EXTI_RTSR_LINE_2_RISING_TRIGGER_ENABLE          (EXTI_EVENT_2)
#define EXTI_RTSR_LINE_3_RISING_TRIGGER_ENABLE          (EXTI_EVENT_3)
#define EXTI_RTSR_LINE_4_RISING_TRIGGER_ENABLE          (EXTI_EVENT_4)
#define EXTI_RTSR_LINE_5_RISING_TRIGGER_ENABLE          (EXTI_EVENT_5)
#define EXTI_RTSR_LINE_6_RISING_TRIGGER_ENABLE          (EXTI_EVENT_6)
#define EXTI_RTSR_LINE_7_RISING_TRIGGER_ENABLE          (EXTI_EVENT_7)
#define EXTI_RTSR_LINE_8_RISING_TRIGGER_ENABLE          (EXTI_EVENT_8)
#define EXTI_RTSR_LINE_9_RISING_TRIGGER_ENABLE          (EXTI_EVENT_9)
#define EXTI_RTSR_LINE_10_RISING_TRIGGER_ENABLE          (EXTI_EVENT_10)
#define EXTI_RTSR_LINE_11_RISING_TRIGGER_ENABLE          (EXTI_EVENT_11)
#define EXTI_RTSR_LINE_12_RISING_TRIGGER_ENABLE          (EXTI_EVENT_12)
#define EXTI_RTSR_LINE_13_RISING_TRIGGER_ENABLE          (EXTI_EVENT_13)
#define EXTI_RTSR_LINE_14_RISING_TRIGGER_ENABLE          (EXTI_EVENT_14)
#define EXTI_RTSR_LINE_15_RISING_TRIGGER_ENABLE          (EXTI_EVENT_15)
#define EXTI_RTSR_LINE_16_RISING_TRIGGER_ENABLE          (EXTI_EVENT_16)
#define EXTI_RTSR_LINE_17_RISING_TRIGGER_ENABLE          (EXTI_EVENT_17)
#define EXTI_RTSR_LINE_18_RISING_TRIGGER_ENABLE          (EXTI_EVENT_18)
#define EXTI_RTSR_LINE_19_RISING_TRIGGER_ENABLE          (EXTI_EVENT_19)

/***************** 4.4- EXTI->FTSR  ***************/

#define EXTI_FTSR_LINE_0_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_0)
#define EXTI_FTSR_LINE_1_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_1)
#define EXTI_FTSR_LINE_2_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_2)
#define EXTI_FTSR_LINE_3_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_3)
#define EXTI_FTSR_LINE_4_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_4)
#define EXTI_FTSR_LINE_5_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_5)
#define EXTI_FTSR_LINE_6_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_6)
#define EXTI_FTSR_LINE_7_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_7)
#define EXTI_FTSR_LINE_8_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_8)
#define EXTI_FTSR_LINE_9_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_9)
#define EXTI_FTSR_LINE_10_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_10)
#define EXTI_FTSR_LINE_11_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_11)
#define EXTI_FTSR_LINE_12_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_12)
#define EXTI_FTSR_LINE_13_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_13)
#define EXTI_FTSR_LINE_14_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_14)
#define EXTI_FTSR_LINE_15_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_15)
#define EXTI_FTSR_LINE_16_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_16)
#define EXTI_FTSR_LINE_17_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_17)
#define EXTI_FTSR_LINE_18_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_18)
#define EXTI_FTSR_LINE_19_FALLING_TRIGGER_ENABLE          (EXTI_EVENT_19)

/***************** 4.5- EXTI->SWIER  ***************/

#define EXTI_SWIER_LINE_0_TRIGGER            (EXTI_EVENT_0)
#define EXTI_SWIER_LINE_1_TRIGGER            (EXTI_EVENT_1)
#define EXTI_SWIER_LINE_2_TRIGGER            (EXTI_EVENT_2)
#define EXTI_SWIER_LINE_3_TRIGGER            (EXTI_EVENT_3)
#define EXTI_SWIER_LINE_4_TRIGGER            (EXTI_EVENT_4)
#define EXTI_SWIER_LINE_5_TRIGGER            (EXTI_EVENT_5)
#define EXTI_SWIER_LINE_6_TRIGGER            (EXTI_EVENT_6)
#define EXTI_SWIER_LINE_7_TRIGGER            (EXTI_EVENT_7)
#define EXTI_SWIER_LINE_8_TRIGGER            (EXTI_EVENT_8)
#define EXTI_SWIER_LINE_9_TRIGGER            (EXTI_EVENT_9)
#define EXTI_SWIER_LINE_10_TRIGGER           (EXTI_EVENT_10)
#define EXTI_SWIER_LINE_11_TRIGGER           (EXTI_EVENT_11)
#define EXTI_SWIER_LINE_12_TRIGGER           (EXTI_EVENT_12)
#define EXTI_SWIER_LINE_13_TRIGGER           (EXTI_EVENT_13)
#define EXTI_SWIER_LINE_14_TRIGGER           (EXTI_EVENT_14)
#define EXTI_SWIER_LINE_15_TRIGGER           (EXTI_EVENT_15)
#define EXTI_SWIER_LINE_16_TRIGGER           (EXTI_EVENT_16)
#define EXTI_SWIER_LINE_17_TRIGGER           (EXTI_EVENT_17)
#define EXTI_SWIER_LINE_18_TRIGGER           (EXTI_EVENT_18)
#define EXTI_SWIER_LINE_19_TRIGGER           (EXTI_EVENT_19)

/***************** 4.6- EXTI->PR  ***************/

#define EXTI_PR_LINE_0_PENDING           (EXTI_EVENT_0)
#define EXTI_PR_LINE_1_PENDING           (EXTI_EVENT_1)
#define EXTI_PR_LINE_2_PENDING           (EXTI_EVENT_2)
#define EXTI_PR_LINE_3_PENDING           (EXTI_EVENT_3)
#define EXTI_PR_LINE_4_PENDING           (EXTI_EVENT_4)
#define EXTI_PR_LINE_5_PENDING           (EXTI_EVENT_5)
#define EXTI_PR_LINE_6_PENDING           (EXTI_EVENT_6)
#define EXTI_PR_LINE_7_PENDING           (EXTI_EVENT_7)
#define EXTI_PR_LINE_8_PENDING           (EXTI_EVENT_8)
#define EXTI_PR_LINE_9_PENDING           (EXTI_EVENT_9)
#define EXTI_PR_LINE_10_PENDING          (EXTI_EVENT_10)
#define EXTI_PR_LINE_11_PENDING          (EXTI_EVENT_11)
#define EXTI_PR_LINE_12_PENDING          (EXTI_EVENT_12)
#define EXTI_PR_LINE_13_PENDING          (EXTI_EVENT_13)
#define EXTI_PR_LINE_14_PENDING          (EXTI_EVENT_14)
#define EXTI_PR_LINE_15_PENDING          (EXTI_EVENT_15)
#define EXTI_PR_LINE_16_PENDING          (EXTI_EVENT_16)
#define EXTI_PR_LINE_17_PENDING          (EXTI_EVENT_17)
#define EXTI_PR_LINE_18_PENDING          (EXTI_EVENT_18)
#define EXTI_PR_LINE_19_PENDING          (EXTI_EVENT_19)


#define EXTI_PR_LINE_0_PENDING_CLEAR           (EXTI_EVENT_0)
#define EXTI_PR_LINE_1_PENDING_CLEAR           (EXTI_EVENT_1)
#define EXTI_PR_LINE_2_PENDING_CLEAR           (EXTI_EVENT_2)
#define EXTI_PR_LINE_3_PENDING_CLEAR           (EXTI_EVENT_3)
#define EXTI_PR_LINE_4_PENDING_CLEAR           (EXTI_EVENT_4)
#define EXTI_PR_LINE_5_PENDING_CLEAR           (EXTI_EVENT_5)
#define EXTI_PR_LINE_6_PENDING_CLEAR           (EXTI_EVENT_6)
#define EXTI_PR_LINE_7_PENDING_CLEAR           (EXTI_EVENT_7)
#define EXTI_PR_LINE_8_PENDING_CLEAR           (EXTI_EVENT_8)
#define EXTI_PR_LINE_9_PENDING_CLEAR           (EXTI_EVENT_9)
#define EXTI_PR_LINE_10_PENDING_CLEAR          (EXTI_EVENT_10)
#define EXTI_PR_LINE_11_PENDING_CLEAR          (EXTI_EVENT_11)
#define EXTI_PR_LINE_12_PENDING_CLEAR          (EXTI_EVENT_12)
#define EXTI_PR_LINE_13_PENDING_CLEAR          (EXTI_EVENT_13)
#define EXTI_PR_LINE_14_PENDING_CLEAR          (EXTI_EVENT_14)
#define EXTI_PR_LINE_15_PENDING_CLEAR          (EXTI_EVENT_15)
#define EXTI_PR_LINE_16_PENDING_CLEAR          (EXTI_EVENT_16)
#define EXTI_PR_LINE_17_PENDING_CLEAR          (EXTI_EVENT_17)
#define EXTI_PR_LINE_18_PENDING_CLEAR          (EXTI_EVENT_18)
#define EXTI_PR_LINE_19_PENDING_CLEAR          (EXTI_EVENT_19)


/***************************************************************/
/*					    	(12) DMA						   */
/***************************************************************/

/*
 * 	DMA Section Architecture Map
 *		1- DMA->Base_Definitions
 *		2- DMA->Registers_Pointers
 *		3- DMA->Struct_Definition
 *		4- DMA->Registers_Values_Definitions
 *			4.1- DMA->ISR
 *			4.2- DMA->ICFR
 *			4.3- DMA->CCRx
 *
 *
 * */


/***************** 1- DMA->Base_Definition ******************/

#define DMA1_BASE                  (0x40020000U)

#define DMA_ISR_ISR_BASE               (DMA1_BASE + 0x00)
#define DMA_ISR_IFCR_BASE              (DMA1_BASE + 0x04)

#define DMA_ISR_CHANNEL1_BASE           (DMA1_BASE + 0x08)
#define DMA_ISR_CCR1_BASE               (DMA_ISR_CHANNEL1_BASE + 0x00)
#define DMA_ISR_CNDTR1_BASE             (DMA_ISR_CHANNEL1_BASE + 0x04)
#define DMA_ISR_CPAR1_BASE              (DMA_ISR_CHANNEL1_BASE + 0x08)
#define DMA_ISR_CMAR1_BASE              (DMA_ISR_CHANNEL1_BASE + 0x0C)

#define DMA_ISR_CHANNEL2_BASE           (DMA1_BASE + 0x1C)
#define DMA_ISR_CCR2_BASE               (DMA_ISR_CHANNEL2_BASE + 0x00)
#define DMA_ISR_CNDTR2_BASE             (DMA_ISR_CHANNEL2_BASE + 0x04)
#define DMA_ISR_CPAR2_BASE              (DMA_ISR_CHANNEL2_BASE + 0x08)
#define DMA_ISR_CMAR2_BASE              (DMA_ISR_CHANNEL2_BASE + 0x0C)

#define DMA_ISR_CHANNEL3_BASE           (DMA1_BASE + 0x30)
#define DMA_ISR_CCR3_BASE               (DMA_ISR_CHANNEL3_BASE + 0x00)
#define DMA_ISR_CNDTR3_BASE             (DMA_ISR_CHANNEL3_BASE + 0x04)
#define DMA_ISR_CPAR3_BASE              (DMA_ISR_CHANNEL3_BASE + 0x08)
#define DMA_ISR_CMAR3_BASE              (DMA_ISR_CHANNEL3_BASE + 0x0C)

#define DMA_ISR_CHANNEL4_BASE           (DMA1_BASE + 0x44)
#define DMA_ISR_CCR4_BASE               (DMA_ISR_CHANNEL4_BASE + 0x00)
#define DMA_ISR_CNDTR4_BASE             (DMA_ISR_CHANNEL4_BASE + 0x04)
#define DMA_ISR_CPAR4_BASE              (DMA_ISR_CHANNEL4_BASE + 0x08)
#define DMA_ISR_CMAR4_BASE              (DMA_ISR_CHANNEL4_BASE + 0x0C)

#define DMA_ISR_CHANNEL5_BASE           (DMA1_BASE + 0x58)
#define DMA_ISR_CCR5_BASE               (DMA_ISR_CHANNEL5_BASE + 0x00)
#define DMA_ISR_CNDTR5_BASE             (DMA_ISR_CHANNEL5_BASE + 0x04)
#define DMA_ISR_CPAR5_BASE              (DMA_ISR_CHANNEL5_BASE + 0x08)
#define DMA_ISR_CMAR5_BASE              (DMA_ISR_CHANNEL5_BASE + 0x0C)


#define DMA_ISR_CHANNEL6_BASE           (DMA1_BASE + 0x6C)
#define DMA_ISR_CCR6_BASE               (DMA_ISR_CHANNEL6_BASE + 0x00)
#define DMA_ISR_CNDTR6_BASE             (DMA_ISR_CHANNEL6_BASE + 0x04)
#define DMA_ISR_CPAR6_BASE              (DMA_ISR_CHANNEL6_BASE + 0x08)
#define DMA_ISR_CMAR6_BASE              (DMA_ISR_CHANNEL6_BASE + 0x0C)

#define DMA_ISR_CHANNEL7_BASE           (DMA1_BASE + 0x80)
#define DMA_ISR_CCR7_BASE               (DMA_ISR_CHANNEL7_BASE + 0x00)
#define DMA_ISR_CNDTR7_BASE             (DMA_ISR_CHANNEL7_BASE + 0x04)
#define DMA_ISR_CPAR7_BASE              (DMA_ISR_CHANNEL7_BASE + 0x08)
#define DMA_ISR_CMAR7_BASE              (DMA_ISR_CHANNEL7_BASE + 0x0C)


#define DMA2_BASE            (0x40020400U)

/***************** 2- DMA->Registers_Pointers ***************/

#define DMA_ISR_ISR                  (*((volatile unsigned long *)DMA_ISR_ISR_BASE))
#define DMA_ISR_IFCR                 (*((volatile unsigned long *)DMA_ISR_IFCR_BASE))

#define DMA_ISR_CCR1                  (*((volatile unsigned long *)DMA_ISR_CCR1_BASE))
#define DMA_ISR_CNDTR1                (*((volatile unsigned long *)DMA_ISR_CNDTR1_BASE))
#define DMA_ISR_CPAR1                 (*((volatile unsigned long *)DMA_ISR_CPAR1_BASE))
#define DMA_ISR_CMAR1                 (*((volatile unsigned long *)DMA_ISR_CMAR1_BASE))

#define DMA_ISR_CCR2                  (*((volatile unsigned long *)DMA_ISR_CCR2_BASE))
#define DMA_ISR_CNDTR2                (*((volatile unsigned long *)DMA_ISR_CNDTR2_BASE))
#define DMA_ISR_CPAR2                 (*((volatile unsigned long *)DMA_ISR_CPAR2_BASE))
#define DMA_ISR_CMAR2                 (*((volatile unsigned long *)DMA_ISR_CMAR2_BASE))

#define DMA_ISR_CCR3                  (*((volatile unsigned long *)DMA_ISR_CCR3_BASE))
#define DMA_ISR_CNDTR3                (*((volatile unsigned long *)DMA_ISR_CNDTR3_BASE))
#define DMA_ISR_CPAR3                 (*((volatile unsigned long *)DMA_ISR_CPAR3_BASE))
#define DMA_ISR_CMAR3                 (*((volatile unsigned long *)DMA_ISR_CMAR3_BASE))

#define DMA_ISR_CCR4                  (*((volatile unsigned long *)DMA_ISR_CCR4_BASE))
#define DMA_ISR_CNDTR4                (*((volatile unsigned long *)DMA_ISR_CNDTR4_BASE))
#define DMA_ISR_CPAR4                 (*((volatile unsigned long *)DMA_ISR_CPAR4_BASE))
#define DMA_ISR_CMAR4                 (*((volatile unsigned long *)DMA_ISR_CMAR4_BASE))

#define DMA_ISR_CCR5                  (*((volatile unsigned long *)DMA_ISR_CCR5_BASE))
#define DMA_ISR_CNDTR5                (*((volatile unsigned long *)DMA_ISR_CNDTR5_BASE))
#define DMA_ISR_CPAR5                 (*((volatile unsigned long *)DMA_ISR_CPAR5_BASE))
#define DMA_ISR_CMAR5                 (*((volatile unsigned long *)DMA_ISR_CMAR5_BASE))

#define DMA_ISR_CCR6                  (*((volatile unsigned long *)DMA_ISR_CCR6_BASE))
#define DMA_ISR_CNDTR6                (*((volatile unsigned long *)DMA_ISR_CNDTR6_BASE))
#define DMA_ISR_CPAR6                 (*((volatile unsigned long *)DMA_ISR_CPAR6_BASE))
#define DMA_ISR_CMAR6                 (*((volatile unsigned long *)DMA_ISR_CMAR6_BASE))


#define DMA_ISR_CCR7                  (*((volatile unsigned long *)DMA_ISR_CCR7_BASE))
#define DMA_ISR_CNDTR7                (*((volatile unsigned long *)DMA_ISR_CNDTR7_BASE))
#define DMA_ISR_CPAR7                 (*((volatile unsigned long *)DMA_ISR_CPAR7_BASE))
#define DMA_ISR_CMAR7                 (*((volatile unsigned long *)DMA_ISR_CMAR7_BASE))



/***************** 3- DMA->Struct_Definition ****************/

#define DMA_ISR_CHANNEL1        ((volatile DMA_ISR_Channel_t *)DMA_ISR_CHANNEL1_BASE)
#define DMA_ISR_CHANNEL2        ((volatile DMA_ISR_Channel_t *)DMA_ISR_CHANNEL2_BASE)
#define DMA_ISR_CHANNEL3        ((volatile DMA_ISR_Channel_t *)DMA_ISR_CHANNEL3_BASE)
#define DMA_ISR_CHANNEL4        ((volatile DMA_ISR_Channel_t *)DMA_ISR_CHANNEL4_BASE)
#define DMA_ISR_CHANNEL5        ((volatile DMA_ISR_Channel_t *)DMA_ISR_CHANNEL5_BASE)
#define DMA_ISR_CHANNEL6        ((volatile DMA_ISR_Channel_t *)DMA_ISR_CHANNEL6_BASE)
#define DMA_ISR_CHANNEL7        ((volatile DMA_ISR_Channel_t *)DMA_ISR_CHANNEL7_BASE)

#define pDMA             ((volatile DMA_t *) DMA1_BASE)

typedef volatile struct {
    volatile union {

        struct {
            unsigned long EN: 1;
            unsigned long TCIE: 1;
            unsigned long HTIE: 1;
            unsigned long TEIE: 1;
            unsigned long DIR: 1;
            unsigned long CIRC: 1;
            unsigned long PINC: 1;
            unsigned long MINC: 1;
            unsigned long PSIZE: 2;
            unsigned long MSIZE: 2;
            unsigned long PL: 2;
            unsigned long MEM2MEM: 1;
            const unsigned long RESERVED: 17;

        } BITS;

        unsigned long REG;
    } CCR;

    volatile union {
        struct {
            unsigned long NDT: 16;
        } BITS;

        unsigned long REG;
    } CNDTR;

    volatile union {
        struct {
            unsigned long PA;
        } BITS;
        struct {
            unsigned long PeripheralAddress;
        };
        unsigned long REG;
    } CPAR;

    volatile union {
        struct {
            unsigned long MA;
        };
        struct {
            unsigned long MemoryAddress;
        };

        unsigned long REG;
    } CMAR;

} DMA_Basic_Channel_t;

typedef volatile union {

    volatile struct {
        const unsigned long RESERVED[2];

        struct {
            DMA_Basic_Channel_t channel;
            const unsigned long RESERVED;
        } Channels[7];

    } All;
    volatile struct {

        volatile union {


            struct {
                const unsigned long GIF1: 1;
                const unsigned long TCIF1: 1;
                const unsigned long HTIF1: 1;
                const unsigned long TEIF1: 1;
                const unsigned long GIF2: 1;
                const unsigned long TCIF2: 1;
                const unsigned long HTIF2: 1;
                const unsigned long TEIF2: 1;
                const unsigned long GIF3: 1;
                const unsigned long TCIF3: 1;
                const unsigned long HTIF3: 1;
                const unsigned long TEIF3: 1;
                const unsigned long GIF4: 1;
                const unsigned long TCIF4: 1;
                const unsigned long HTIF4: 1;
                const unsigned long TEIF4: 1;
                const unsigned long GIF5: 1;
                const unsigned long TCIF5: 1;
                const unsigned long HTIF5: 1;
                const unsigned long TEIF5: 1;
                const unsigned long GIF6: 1;
                const unsigned long TCIF6: 1;
                const unsigned long HTIF6: 1;
                const unsigned long TEIF6: 1;
                const unsigned long GIF7: 1;
                const unsigned long TCIF7: 1;
                const unsigned long HTIF7: 1;
                const unsigned long TEIF7: 1;
                const unsigned long RESERVED: 4;
            };
            const unsigned long REG;
        } ISR;

        volatile union {


            struct {
                 unsigned long CGIF1: 1;
                 unsigned long CTCIF1: 1;
                 unsigned long CHTIF1: 1;
                 unsigned long CTEIF1: 1;
                 unsigned long CGIF2: 1;
                 unsigned long CTCIF2: 1;
                 unsigned long CHTIF2: 1;
                 unsigned long CTEIF2: 1;
                 unsigned long CGIF3: 1;
                 unsigned long CTCIF3: 1;
                 unsigned long CHTIF3: 1;
                 unsigned long CTEIF3: 1;
                 unsigned long CGIF4: 1;
                 unsigned long CTCIF4: 1;
                 unsigned long CHTIF4: 1;
                 unsigned long CTEIF4: 1;
                 unsigned long CGIF5: 1;
                 unsigned long CTCIF5: 1;
                 unsigned long CHTIF5: 1;
                 unsigned long CTEIF5: 1;
                 unsigned long CGIF6: 1;
                 unsigned long CTCIF6: 1;
                 unsigned long CHTIF6: 1;
                 unsigned long CTEIF6: 1;
                 unsigned long CGIF7: 1;
                 unsigned long CTCIF7: 1;
                 unsigned long CHTIF7: 1;
                 unsigned long CTEIF7: 1;
                const unsigned long RESERVED: 4;
            };
            unsigned long REG;
        } IFCR;

        DMA_Basic_Channel_t Channel1;
        const unsigned long RESERVED;

        DMA_Basic_Channel_t Channel2;
        const unsigned long RESERVED;

        DMA_Basic_Channel_t Channel3;
        const unsigned long RESERVED;

        DMA_Basic_Channel_t Channel4;
        const unsigned long RESERVED;

        DMA_Basic_Channel_t Channel5;
        const unsigned long RESERVED;

        DMA_Basic_Channel_t Channel6;
        const unsigned long RESERVED;

        DMA_Basic_Channel_t Channel7;
        const unsigned long RESERVED;
    };


} DMA_t;

/***************** 4- DMA->Registers_Values_Definitions *****/

/***************** 4.1- DMA->ISR  ***************/

#define DMA_ISR_GIF_GLOBAL_FLAG_HIGH                      (1)
#define DMA_ISR_TCIF_TX_COMPLETE_FLAG_HIGH                (1)
#define DMA_ISR_HTIF_HALF_TX_COMPLETE_FLAG_HIGH           (1)
#define DMA_ISR_TEIF_TX_ERROR_FLAG_HIGH                   (1)


#define DMA_ISR_GIF1_GLOBAL_FLAG_POS                      (0)
#define DMA_ISR_TCIF1_TX_COMPLETE_FLAG_POS                (1)
#define DMA_ISR_HTIF1_HALF_TX_COMPLETE_FLAG_POS           (2)
#define DMA_ISR_TEIF1_TX_ERROR_FLAG_POS                   (3)

#define DMA_ISR_GIF2_GLOBAL_FLAG_POS                      (4)
#define DMA_ISR_TCIF2_TX_COMPLETE_FLAG_POS                (5)
#define DMA_ISR_HTIF2_HALF_TX_COMPLETE_FLAG_POS           (6)
#define DMA_ISR_TEIF2_TX_ERROR_FLAG_POS                   (7)

#define DMA_ISR_GIF3_GLOBAL_FLAG_POS                      (8)
#define DMA_ISR_TCIF3_TX_COMPLETE_FLAG_POS                (9)
#define DMA_ISR_HTIF3_HALF_TX_COMPLETE_FLAG_POS           (10)
#define DMA_ISR_TEIF3_TX_ERROR_FLAG_POS                   (11)

#define DMA_ISR_GIF4_GLOBAL_FLAG_POS                      (12)
#define DMA_ISR_TCIF4_TX_COMPLETE_FLAG_POS                (13)
#define DMA_ISR_HTIF4_HALF_TX_COMPLETE_FLAG_POS           (14)
#define DMA_ISR_TEIF4_TX_ERROR_FLAG_POS                   (15)

#define DMA_ISR_GIF5_GLOBAL_FLAG_POS                      (16)
#define DMA_ISR_TCIF5_TX_COMPLETE_FLAG_POS                (17)
#define DMA_ISR_HTIF5_HALF_TX_COMPLETE_FLAG_POS           (18)
#define DMA_ISR_TEIF5_TX_ERROR_FLAG_POS                   (19)

#define DMA_ISR_GIF6_GLOBAL_FLAG_POS                      (20)
#define DMA_ISR_TCIF6_TX_COMPLETE_FLAG_POS                (21)
#define DMA_ISR_HTIF6_HALF_TX_COMPLETE_FLAG_POS           (22)
#define DMA_ISR_TEIF6_TX_ERROR_FLAG_POS                   (23)

#define DMA_ISR_GIF7_GLOBAL_FLAG_POS                      (24)
#define DMA_ISR_TCIF7_TX_COMPLETE_FLAG_POS                (25)
#define DMA_ISR_HTIF7_HALF_TX_COMPLETE_FLAG_POS           (26)
#define DMA_ISR_TEIF7_TX_ERROR_FLAG_POS                   (27)


#define DMA_ISR_GIF1_GLOBAL_FLAG_HIGH                      (1<<DMA_ISR_GIF1_GLOBAL_FLAG_POS)
#define DMA_ISR_TCIF1_TX_COMPLETE_FLAG_HIGH                (1<<DMA_ISR_TCIF1_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_HTIF1_HALF_TX_COMPLETE_FLAG_HIGH           (1<<DMA_ISR_HTIF1_HALF_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_TEIF1_TX_ERROR_FLAG_HIGH                   (1<<DMA_ISR_TEIF1_TX_ERROR_FLAG_POS)

#define DMA_ISR_GIF2_GLOBAL_FLAG_HIGH                      (1<<DMA_ISR_GIF2_GLOBAL_FLAG_POS)
#define DMA_ISR_TCIF2_TX_COMPLETE_FLAG_HIGH                (1<<DMA_ISR_TCIF2_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_HTIF2_HALF_TX_COMPLETE_FLAG_HIGH           (1<<DMA_ISR_HTIF2_HALF_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_TEIF2_TX_ERROR_FLAG_HIGH                   (1<<DMA_ISR_TEIF2_TX_ERROR_FLAG_POS)

#define DMA_ISR_GIF3_GLOBAL_FLAG_HIGH                      (1<<DMA_ISR_GIF3_GLOBAL_FLAG_POS)
#define DMA_ISR_TCIF3_TX_COMPLETE_FLAG_HIGH                (1<<DMA_ISR_TCIF3_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_HTIF3_HALF_TX_COMPLETE_FLAG_HIGH           (1<<DMA_ISR_HTIF3_HALF_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_TEIF3_TX_ERROR_FLAG_HIGH                   (1<<DMA_ISR_TEIF3_TX_ERROR_FLAG_POS)

#define DMA_ISR_GIF4_GLOBAL_FLAG_HIGH                      (1<<DMA_ISR_GIF4_GLOBAL_FLAG_POS)
#define DMA_ISR_TCIF4_TX_COMPLETE_FLAG_HIGH                (1<<DMA_ISR_TCIF4_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_HTIF4_HALF_TX_COMPLETE_FLAG_HIGH           (1<<DMA_ISR_HTIF4_HALF_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_TEIF4_TX_ERROR_FLAG_HIGH                   (1<<DMA_ISR_TEIF4_TX_ERROR_FLAG_POS)

#define DMA_ISR_GIF5_GLOBAL_FLAG_HIGH                      (1<<DMA_ISR_GIF5_GLOBAL_FLAG_POS)
#define DMA_ISR_TCIF5_TX_COMPLETE_FLAG_HIGH                (1<<DMA_ISR_TCIF5_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_HTIF5_HALF_TX_COMPLETE_FLAG_HIGH           (1<<DMA_ISR_HTIF5_HALF_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_TEIF5_TX_ERROR_FLAG_HIGH                   (1<<DMA_ISR_TEIF5_TX_ERROR_FLAG_POS)

#define DMA_ISR_GIF6_GLOBAL_FLAG_HIGH                      (1<<DMA_ISR_GIF6_GLOBAL_FLAG_POS)
#define DMA_ISR_TCIF6_TX_COMPLETE_FLAG_HIGH                (1<<DMA_ISR_TCIF6_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_HTIF6_HALF_TX_COMPLETE_FLAG_HIGH           (1<<DMA_ISR_HTIF6_HALF_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_TEIF6_TX_ERROR_FLAG_HIGH                   (1<<DMA_ISR_TEIF6_TX_ERROR_FLAG_POS)

#define DMA_ISR_GIF7_GLOBAL_FLAG_HIGH                      (1<<DMA_ISR_GIF7_GLOBAL_FLAG_POS)
#define DMA_ISR_TCIF7_TX_COMPLETE_FLAG_HIGH                (1<<DMA_ISR_TCIF7_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_HTIF7_HALF_TX_COMPLETE_FLAG_HIGH           (1<<DMA_ISR_HTIF7_HALF_TX_COMPLETE_FLAG_POS)
#define DMA_ISR_TEIF7_TX_ERROR_FLAG_HIGH                   (1<<DMA_ISR_TEIF7_TX_ERROR_FLAG_POS)


/***************** 4.2- DMA->IFCR  ***************/

#define DMA_IFCR_CGIF1_GLOBAL_FLAG_CLEAR_POS                      (0)
#define DMA_IFCR_CTCIF1_TX_COMPLETE_FLAG_CLEAR_POS                (1)
#define DMA_IFCR_CHTIF1_HALF_TX_COMPLETE_FLAG_CLEAR_POS           (2)
#define DMA_IFCR_CTEIF1_TX_ERROR_FLAG_CLEAR_POS                   (3)

#define DMA_IFCR_CGIF2_GLOBAL_FLAG_CLEAR_POS                      (4)
#define DMA_IFCR_CTCIF2_TX_COMPLETE_FLAG_CLEAR_POS                (5)
#define DMA_IFCR_CHTIF2_HALF_TX_COMPLETE_FLAG_CLEAR_POS           (6)
#define DMA_IFCR_CTEIF2_TX_ERROR_FLAG_CLEAR_POS                   (7)

#define DMA_IFCR_CGIF3_GLOBAL_FLAG_CLEAR_POS                      (8)
#define DMA_IFCR_CTCIF3_TX_COMPLETE_FLAG_CLEAR_POS                (9)
#define DMA_IFCR_CHTIF3_HALF_TX_COMPLETE_FLAG_CLEAR_POS           (10)
#define DMA_IFCR_CTEIF3_TX_ERROR_FLAG_CLEAR_POS                   (11)

#define DMA_IFCR_CGIF4_GLOBAL_FLAG_CLEAR_POS                      (12)
#define DMA_IFCR_CTCIF4_TX_COMPLETE_FLAG_CLEAR_POS                (13)
#define DMA_IFCR_CHTIF4_HALF_TX_COMPLETE_FLAG_CLEAR_POS           (14)
#define DMA_IFCR_CTEIF4_TX_ERROR_FLAG_CLEAR_POS                   (15)

#define DMA_IFCR_CGIF5_GLOBAL_FLAG_CLEAR_POS                      (16)
#define DMA_IFCR_CTCIF5_TX_COMPLETE_FLAG_CLEAR_POS                (17)
#define DMA_IFCR_CHTIF5_HALF_TX_COMPLETE_FLAG_CLEAR_POS           (18)
#define DMA_IFCR_CTEIF5_TX_ERROR_FLAG_CLEAR_POS                   (19)

#define DMA_IFCR_CGIF6_GLOBAL_FLAG_CLEAR_POS                      (20)
#define DMA_IFCR_CTCIF6_TX_COMPLETE_FLAG_CLEAR_POS                (21)
#define DMA_IFCR_CHTIF6_HALF_TX_COMPLETE_FLAG_CLEAR_POS           (22)
#define DMA_IFCR_CTEIF6_TX_ERROR_FLAG_CLEAR_POS                   (23)

#define DMA_IFCR_CGIF7_GLOBAL_FLAG_CLEAR_POS                      (24)
#define DMA_IFCR_CTCIF7_TX_COMPLETE_FLAG_CLEAR_POS                (25)
#define DMA_IFCR_CHTIF7_HALF_TX_COMPLETE_FLAG_CLEAR_POS           (26)
#define DMA_IFCR_CTEIF7_TX_ERROR_FLAG_CLEAR_POS                   (27)


#define DMA_IFCR_CGIF1_GLOBAL_FLAG_CLEAR_HIGH                      (1<<DMA_IFCR_CGIF1_GLOBAL_FLAG_CLEAR_POS)
#define DMA_IFCR_CTCIF1_TX_COMPLETE_FLAG_CLEAR_HIGH                (1<<DMA_IFCR_CTCIF1_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CHTIF1_HALF_TX_COMPLETE_FLAG_CLEAR_HIGH           (1<<DMA_IFCR_CHTIF1_HALF_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CTEIF1_TX_ERROR_FLAG_CLEAR_HIGH                   (1<<DMA_IFCR_CTEIF1_TX_ERROR_FLAG_CLEAR_POS)

#define DMA_IFCR_CGIF2_GLOBAL_FLAG_CLEAR_HIGH                      (1<<DMA_IFCR_CGIF2_GLOBAL_FLAG_CLEAR_POS)
#define DMA_IFCR_CTCIF2_TX_COMPLETE_FLAG_CLEAR_HIGH                (1<<DMA_IFCR_CTCIF2_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CHTIF2_HALF_TX_COMPLETE_FLAG_CLEAR_HIGH           (1<<DMA_IFCR_CHTIF2_HALF_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CTEIF2_TX_ERROR_FLAG_CLEAR_HIGH                   (1<<DMA_IFCR_CTEIF2_TX_ERROR_FLAG_CLEAR_POS)

#define DMA_IFCR_CGIF3_GLOBAL_FLAG_CLEAR_HIGH                      (1<<DMA_IFCR_CGIF3_GLOBAL_FLAG_CLEAR_POS)
#define DMA_IFCR_CTCIF3_TX_COMPLETE_FLAG_CLEAR_HIGH                (1<<DMA_IFCR_CTCIF3_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CHTIF3_HALF_TX_COMPLETE_FLAG_CLEAR_HIGH           (1<<DMA_IFCR_CHTIF3_HALF_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CTEIF3_TX_ERROR_FLAG_CLEAR_HIGH                   (1<<DMA_IFCR_CTEIF3_TX_ERROR_FLAG_CLEAR_POS)

#define DMA_IFCR_CGIF4_GLOBAL_FLAG_CLEAR_HIGH                      (1<<DMA_IFCR_CGIF4_GLOBAL_FLAG_CLEAR_POS)
#define DMA_IFCR_CTCIF4_TX_COMPLETE_FLAG_CLEAR_HIGH                (1<<DMA_IFCR_CTCIF4_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CHTIF4_HALF_TX_COMPLETE_FLAG_CLEAR_HIGH           (1<<DMA_IFCR_CHTIF4_HALF_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CTEIF4_TX_ERROR_FLAG_CLEAR_HIGH                   (1<<DMA_IFCR_CTEIF4_TX_ERROR_FLAG_CLEAR_POS)

#define DMA_IFCR_CGIF5_GLOBAL_FLAG_CLEAR_HIGH                      (1<<DMA_IFCR_CGIF5_GLOBAL_FLAG_CLEAR_POS)
#define DMA_IFCR_CTCIF5_TX_COMPLETE_FLAG_CLEAR_HIGH                (1<<DMA_IFCR_CTCIF5_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CHTIF5_HALF_TX_COMPLETE_FLAG_CLEAR_HIGH           (1<<DMA_IFCR_CHTIF5_HALF_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CTEIF5_TX_ERROR_FLAG_CLEAR_HIGH                   (1<<DMA_IFCR_CTEIF5_TX_ERROR_FLAG_CLEAR_POS)

#define DMA_IFCR_CGIF6_GLOBAL_FLAG_CLEAR_HIGH                      (1<<DMA_IFCR_CGIF6_GLOBAL_FLAG_CLEAR_POS)
#define DMA_IFCR_CTCIF6_TX_COMPLETE_FLAG_CLEAR_HIGH                (1<<DMA_IFCR_CTCIF6_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CHTIF6_HALF_TX_COMPLETE_FLAG_CLEAR_HIGH           (1<<DMA_IFCR_CHTIF6_HALF_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CTEIF6_TX_ERROR_FLAG_CLEAR_HIGH                   (1<<DMA_IFCR_CTEIF6_TX_ERROR_FLAG_CLEAR_POS)

#define DMA_IFCR_CGIF7_GLOBAL_FLAG_CLEAR_HIGH                      (1<<DMA_IFCR_CGIF7_GLOBAL_FLAG_CLEAR_POS)
#define DMA_IFCR_CTCIF7_TX_COMPLETE_FLAG_CLEAR_HIGH                (1<<DMA_IFCR_CTCIF7_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CHTIF7_HALF_TX_COMPLETE_FLAG_CLEAR_HIGH           (1<<DMA_IFCR_CHTIF7_HALF_TX_COMPLETE_FLAG_CLEAR_POS)
#define DMA_IFCR_CTEIF7_TX_ERROR_FLAG_CLEAR_HIGH                   (1<<DMA_IFCR_CTEIF7_TX_ERROR_FLAG_CLEAR_POS)

/***************** 4.3- DMA->CCRx  ***************/

#define DMA_CCRx_EN_POS              (0)
#define DMA_CCRx_TCIE_POS            (1)
#define DMA_CCRx_HTIE_POS            (2)
#define DMA_CCRx_TEIE_POS            (3)
#define DMA_CCRx_DIR_POS             (4)
#define DMA_CCRx_CIRC_POS            (5)
#define DMA_CCRx_PINC_POS            (6)
#define DMA_CCRx_MINC_POS            (7)
#define DMA_CCRx_PSIZE_POS           (8)
#define DMA_CCRx_MSIZE_POS           (10)
#define DMA_CCRx_PL_POS              (12)
#define DMA_CCRx_MEM2MEM_POS         (14)


#define DMA_MSIZE_PERPH_SIZE_8BITS     (0)
#define DMA_MSIZE_PERPH_SIZE_16BITS    (1)
#define DMA_MSIZE_PERPH_SIZE_32BITS    (2)

#define DMA_PL_PRIORITY_LEVEL_LOW          (0)
#define DMA_PL_PRIORITY_LEVEL_MEDIUM       (1)
#define DMA_PL_PRIORITY_LEVEL_HIGH         (2)
#define DMA_PL_PRIORITY_LEVEL_VERYHIGH     (3)


#define DMA_CCRx_EN_ENABLE                  (1<<DMA_CCRx_EN_POS)


#define DMA_CCRx_TCIE_TX_COMPLETE_IE        (1<<DMA_CCRx_TCIE_POS)
#define DMA_CCRx_HTIE_HALF_TX_COMPLETE_IE   (1<<DMA_CCRx_HTIE_POS)
#define DMA_CCRx_TEIE_TX_ERROR_IE           (1<<DMA_CCRx_TEIE_POS)

#define DMA_CCRx_DIR_MEM_TO_PERPH           (1<<DMA_CCRx_DIR_POS)
#define DMA_CCRx_CIRC_CIRCULAR_MODE_ENABLE  (1<<DMA_CCRx_CIRC_POS)
#define DMA_CCRx_PINC_PERPH_INC             (1<<DMA_CCRx_PINC_POS)
#define DMA_CCRx_PINC_MEM_INC               (1<<DMA_CCRx_MINC_POS)

#define DMA_CCRx_PSIZE_PERPH_SIZE_8BITS      (0<<DMA_CCRx_PSIZE_POS)
#define DMA_CCRx_PSIZE_PERPH_SIZE_16BITS     (1<<DMA_CCRx_PSIZE_POS)
#define DMA_CCRx_PSIZE_PERPH_SIZE_32BITS     (2<<DMA_CCRx_PSIZE_POS)

#define DMA_CCRx_MSIZE_PERPH_SIZE_8BITS      (DMA_MSIZE_PERPH_SIZE_8BITS<<DMA_CCRx_MSIZE_POS)
#define DMA_CCRx_MSIZE_PERPH_SIZE_16BITS     (DMA_MSIZE_PERPH_SIZE_16BITS<<DMA_CCRx_MSIZE_POS)
#define DMA_CCRx_MSIZE_PERPH_SIZE_32BITS     (DMA_MSIZE_PERPH_SIZE_32BITS<<DMA_CCRx_MSIZE_POS)

#define DMA_CCRx_PL_PRIORITY_LEVEL_LOW             (DMA_PL_PRIORITY_LEVEL_LOW<<DMA_CCRx_PL_POS)
#define DMA_CCRx_PL_PRIORITY_LEVEL_MEDIUM          (DMA_PL_PRIORITY_LEVEL_MEDIUM<<DMA_CCRx_PL_POS)
#define DMA_CCRx_PL_PRIORITY_LEVEL_HIGH            (DMA_PL_PRIORITY_LEVEL_HIGH<<DMA_CCRx_PL_POS)
#define DMA_CCRx_PL_PRIORITY_LEVEL_VERYHIGH        (DMA_PL_PRIORITY_LEVEL_VERYHIGH<<DMA_CCRx_PL_POS)


#define DMA_CCRx_MEM2MEM_ENABLE                     (1<<DMA_CCRx_MEM2MEM_POS)



/***************************************************************/
/*					    	(13) ADC						   */
/***************************************************************/

/*
 * 	ADC Section Architecture Map
 *		1- ADC->Base_Definitions
 *		2- ADC->Registers_Pointers
 *		3- ADC->Struct_Definition
 *		4- ADC->Registers_Values_Definitions
 *			4.1- ADC->
 *			4.2- ADC->
 *			4.3- ADC->
 *			4.4- ADC->
 *			4.5- ADC->
 *			4.6- ADC->
 *
 *
 * */


/***************** 1- ADC->Base_Definition ******************/
#define pADC_BASE       (PERIPHERAL_MEMORY_BASE + 0x12400U)
#define pADC1_BASE      (pADC_BASE + 0x0000U)
#define pADC2_BASE      (pADC_BASE + 0x0400U)
#define pADC3_BASE      (pADC_BASE + 0x1400U)

#define pADC1_SR_BASE       (pADC1_BASE + 0x00)
#define pADC1_CR1_BASE      (pADC1_BASE + 0x04)
#define pADC1_CR2_BASE      (pADC1_BASE + 0x08)
#define pADC1_SMPR1_BASE    (pADC1_BASE + 0x0C)
#define pADC1_SMPR2_BASE    (pADC1_BASE + 0x10)
#define pADC1_JOFR1_BASE    (pADC1_BASE + 0x14)
#define pADC1_JOFR2_BASE    (pADC1_BASE + 0x18)
#define pADC1_JOFR3_BASE    (pADC1_BASE + 0x1C)
#define pADC1_JOFR4_BASE    (pADC1_BASE + 0x20)
#define pADC1_HTR_BASE      (pADC1_BASE + 0x24)
#define pADC1_LTR_BASE      (pADC1_BASE + 0x28)
#define pADC1_SQR1_BASE     (pADC1_BASE + 0x2C)
#define pADC1_SQR2_BASE     (pADC1_BASE + 0x30)
#define pADC1_SQR3_BASE     (pADC1_BASE + 0x34)
#define pADC1_JSQR_BASE     (pADC1_BASE + 0x38)
#define pADC1_JDR1_BASE     (pADC1_BASE + 0x3C)
#define pADC1_JDR2_BASE     (pADC1_BASE + 0x40)
#define pADC1_JDR3_BASE     (pADC1_BASE + 0x44)
#define pADC1_JDR4_BASE     (pADC1_BASE + 0x48)
#define pADC1_DR_BASE       (pADC1_BASE + 0x4C)


#define pADC2_SR_BASE       (pADC2_BASE + 0x00)
#define pADC2_CR1_BASE      (pADC2_BASE + 0x04)
#define pADC2_CR2_BASE      (pADC2_BASE + 0x08)
#define pADC2_SMPR1_BASE    (pADC2_BASE + 0x0C)
#define pADC2_SMPR2_BASE    (pADC2_BASE + 0x10)
#define pADC2_JOFR1_BASE    (pADC2_BASE + 0x14)
#define pADC2_JOFR2_BASE    (pADC2_BASE + 0x18)
#define pADC2_JOFR3_BASE    (pADC2_BASE + 0x1C)
#define pADC2_JOFR4_BASE    (pADC2_BASE + 0x20)
#define pADC2_HTR_BASE      (pADC2_BASE + 0x24)
#define pADC2_LTR_BASE      (pADC2_BASE + 0x28)
#define pADC2_SQR1_BASE     (pADC2_BASE + 0x2C)
#define pADC2_SQR2_BASE     (pADC2_BASE + 0x30)
#define pADC2_SQR3_BASE     (pADC2_BASE + 0x34)
#define pADC2_JSQR_BASE     (pADC2_BASE + 0x38)
#define pADC2_JDR1_BASE     (pADC2_BASE + 0x3C)
#define pADC2_JDR2_BASE     (pADC2_BASE + 0x40)
#define pADC2_JDR3_BASE     (pADC2_BASE + 0x44)
#define pADC2_JDR4_BASE     (pADC2_BASE + 0x48)
#define pADC2_DR_BASE       (pADC2_BASE + 0x4C)
/***************** 2- ADC->Registers_Pointers ***************/

#define pADC1_SR       (*((uint32_t *) pADC1_SR_BASE))
#define pADC1_CR1      (*((uint32_t *) pADC1_CR1_BASE))
#define pADC1_CR2      (*((uint32_t *) pADC1_CR2_BASE))
#define pADC1_SMPR1    (*((uint32_t *) pADC1_SMPR1_BASE))
#define pADC1_SMPR2    (*((uint32_t *) pADC1_SMPR2_BASE))
#define pADC1_JOFR1    (*((uint32_t *) pADC1_JOFR1_BASE))
#define pADC1_JOFR2    (*((uint32_t *) pADC1_JOFR2_BASE))
#define pADC1_JOFR3    (*((uint32_t *) pADC1_JOFR3_BASE))
#define pADC1_JOFR4    (*((uint32_t *) pADC1_JOFR4_BASE))
#define pADC1_HTR      (*((uint32_t *) pADC1_HTR_BASE))
#define pADC1_LTR      (*((uint32_t *) pADC1_LTR_BASE))
#define pADC1_SQR1     (*((uint32_t *) pADC1_SQR1_BASE))
#define pADC1_SQR2     (*((uint32_t *) pADC1_SQR2_BASE))
#define pADC1_SQR3     (*((uint32_t *) pADC1_SQR3_BASE))
#define pADC1_JSQR     (*((uint32_t *) pADC1_JSQR_BASE))
#define pADC1_JDR1     (*((uint32_t *) pADC1_JDR1_BASE))
#define pADC1_JDR2     (*((uint32_t *) pADC1_JDR2_BASE))
#define pADC1_JDR3     (*((uint32_t *) pADC1_JDR3_BASE))
#define pADC1_JDR4     (*((uint32_t *) pADC1_JDR4_BASE))
#define pADC1_DR       (*((uint32_t *) pADC1_DR_BASE))


#define pADC2_SR       (*((uint32_t *) pADC2_SR_BASE))
#define pADC2_CR1      (*((uint32_t *) pADC2_CR1_BASE))
#define pADC2_CR2      (*((uint32_t *) pADC2_CR2_BASE))
#define pADC2_SMPR1    (*((uint32_t *) pADC2_SMPR1_BASE))
#define pADC2_SMPR2    (*((uint32_t *) pADC2_SMPR2_BASE))
#define pADC2_JOFR1    (*((uint32_t *) pADC2_JOFR1_BASE))
#define pADC2_JOFR2    (*((uint32_t *) pADC2_JOFR2_BASE))
#define pADC2_JOFR3    (*((uint32_t *) pADC2_JOFR3_BASE))
#define pADC2_JOFR4    (*((uint32_t *) pADC2_JOFR4_BASE))
#define pADC2_HTR      (*((uint32_t *) pADC2_HTR_BASE))
#define pADC2_LTR      (*((uint32_t *) pADC2_LTR_BASE))
#define pADC2_SQR1     (*((uint32_t *) pADC2_SQR1_BASE))
#define pADC2_SQR2     (*((uint32_t *) pADC2_SQR2_BASE))
#define pADC2_SQR3     (*((uint32_t *) pADC2_SQR3_BASE))
#define pADC2_JSQR     (*((uint32_t *) pADC2_JSQR_BASE))
#define pADC2_JDR1     (*((uint32_t *) pADC2_JDR1_BASE))
#define pADC2_JDR2     (*((uint32_t *) pADC2_JDR2_BASE))
#define pADC2_JDR3     (*((uint32_t *) pADC2_JDR3_BASE))
#define pADC2_JDR4     (*((uint32_t *) pADC2_JDR4_BASE))
#define pADC2_DR       (*((uint32_t *) pADC2_DR_BASE))


/***************** 3- ADC->Struct_Definition ****************/

typedef volatile struct {
    union {
        struct {
            uint32_t AWD: 1;
            uint32_t EOC: 1;
            uint32_t JEOC: 1;
            uint32_t JSTRT: 1;
            uint32_t STRT: 1;

        };
        uint32_t REG;
    } SR;

    union {
        struct {
            uint32_t AWDCH: 5;
            uint32_t EOCIE: 1;
            uint32_t AWDIE: 1;
            uint32_t JEOCIE: 1;
            uint32_t SCAN: 1;
            uint32_t AWDSGL: 1;
            uint32_t JAUTO: 1;
            uint32_t DISCEN: 1;
            uint32_t JDISCEN: 1;
            uint32_t DISCNUM: 3;
            uint32_t DUALMOD: 4;
            const uint32_t  : 2;
            uint32_t JAWDEN: 1;
            uint32_t AWDEN: 1;
        };
        uint32_t REG;
    } CR1;

    union {
        struct {
            uint32_t ADON: 1;
            uint32_t CONT: 1;
            uint32_t CAL: 1;
            uint32_t RSTCAL: 1;
            const uint32_t  : 4;
            uint32_t DMA: 1;
            const uint32_t  : 2;
            uint32_t ALIGN: 1;
            uint32_t JEXTSEL: 3;
            uint32_t JEXTTRIG: 1;
            const uint32_t  : 1;
            uint32_t EXTSEL: 3;
            uint32_t EXTTRIG: 1;
            uint32_t JSWSTART: 1;
            uint32_t SWSTART: 1;
            uint32_t TSVREFE: 1;
        };
        uint32_t REG;
    } CR2;

    union {
        struct {
            uint32_t SMP10: 3;
            uint32_t SMP11: 3;
            uint32_t SMP12: 3;
            uint32_t SMP13: 3;
            uint32_t SMP14: 3;
            uint32_t SMP15: 3;
            uint32_t SMP16: 3;
            uint32_t SMP17: 3;
        };
        uint32_t REG;
    } SMPR1;

    union {
        struct {
            uint32_t SMP0: 3;
            uint32_t SMP1: 3;
            uint32_t SMP2: 3;
            uint32_t SMP3: 3;
            uint32_t SMP4: 3;
            uint32_t SMP5: 3;
            uint32_t SMP6: 3;
            uint32_t SMP7: 3;
            uint32_t SMP8: 3;
            uint32_t SMP9: 3;
        };
        uint32_t REG;
    } SMPR2;


    union {
        struct {
            uint32_t JOFFSET: 12;
        };
        uint32_t REG;
    } JOFR1;

    union {
        struct {
            uint32_t JOFFSET: 12;
        };
        uint32_t REG;
    } JOFR2;

    union {
        struct {
            uint32_t JOFFSET: 12;
        };
        uint32_t REG;
    } JOFR3;

    union {
        struct {
            uint32_t JOFFSET: 12;
        };
        uint32_t REG;
    } JOFR4;

    union {
        struct {
            uint32_t HT: 12;

        };
        uint32_t REG;
    } HTR;

    union {
        struct {
            uint32_t LT: 12;
        };
        uint32_t REG;
    } LTR;


    union {
        struct {
            uint32_t SQ13: 5;
            uint32_t SQ14: 5;
            uint32_t SQ15: 5;
            uint32_t SQ16: 5;
            uint32_t L: 4;
        };
        uint32_t REG;
    } SQR1;

    union {
        struct {
            uint32_t SQ7       :5;
            uint32_t SQ8       :5;
            uint32_t SQ9       :5;
            uint32_t SQ10       :5;
            uint32_t SQ11       :5;
            uint32_t SQ12       :5;

        };
        uint32_t REG;
    } SQR2;
    
    union {
        struct {
            uint32_t SQ1       :5;
            uint32_t SQ2       :5;
            uint32_t SQ3       :5;
            uint32_t SQ4       :5;
            uint32_t SQ5       :5;
            uint32_t SQ6       :5;

        };
        uint32_t REG;
    } SQR3;

    union {
        struct {
            uint32_t JSQ1       :5;
            uint32_t JSQ2       :5;
            uint32_t JSQ3       :5;
            uint32_t JSQ4       :5;
            uint32_t JL       :2;
            

        };
        uint32_t REG;
    } JSQR;

    union {
        struct {
            const uint32_t JDATA       :16;
        };
        uint32_t REG;
    } JDR1;

    union {
        struct {
            const uint32_t JDATA       :16;
        };
        uint32_t REG;
    } JDR2;

    union {
        struct {
            const uint32_t JDATA       :16;
        };
        uint32_t REG;
    } JDR3;

    union {
        struct {
            const uint32_t JDATA       :16;
        };
        uint32_t REG;
    } JDR4;


    union {
        struct {
            const uint32_t DATA       :16;
            const uint32_t ADC2DATA       :16;
        };
        uint32_t REG;
    } DR;

} pADC_Unit_t;

typedef volatile union {

    struct {
        union {

            struct {
                pADC_Unit_t ADC;
            };
            struct {

                const uint32_t RESERVED[3];
                union {
                    uint32_t REG;
                } SMPRs[2];

                union {
                    struct {
                        uint32_t JOFFSET: 12;
                    };
                    uint32_t REG;
                } JOFR[4];

                const uint32_t RESERVED[2];
                union {
                    uint32_t REG;
                } SQR[3];
                const uint32_t RESERVED;

                union {
                    struct {
                        const uint32_t JDATA: 16;
                    };
                    uint32_t REG;
                } JDR[4];
            };


        };
        const uint32_t RESERVED[80];
    } ADCs[2];


    struct {
        pADC_Unit_t ADC1;
        const uint32_t RESERVED[80];
        pADC_Unit_t ADC2;
    };

}pADC_t;

#define pADC         ((pADC_t *)pADC_BASE)
#define pADC1        ((pADC_Unit_t *)pADC1_BASE)
#define pADC2        ((pADC_Unit_t *)pADC2_BASE)

/***************** 4- ADC->Registers_Values_Definitions *****/
/***************** 4.1- ADC->SR  ***************/

#define pADC_AWD_ANALOG_WATCHDG_EVENT_OCCURED       (1)

#define pADC_EOC_CONV_COMP       (1)

#define pADC_JEOC_INJ_CONV_COMP       (1)

#define pADC_JSTRT_INJ_START       (1)

#define pADC_STRT_START       (1)



/***************** 4.2- ADC->CR1  ***************/

#define pADC_AWDCH_CHANNEL_0        (0)
#define pADC_AWDCH_CHANNEL_1        (1)
#define pADC_AWDCH_CHANNEL_2        (2)
#define pADC_AWDCH_CHANNEL_3        (3)
#define pADC_AWDCH_CHANNEL_4        (4)
#define pADC_AWDCH_CHANNEL_5        (5)
#define pADC_AWDCH_CHANNEL_6        (6)
#define pADC_AWDCH_CHANNEL_7        (7)
#define pADC_AWDCH_CHANNEL_8        (8)
#define pADC_AWDCH_CHANNEL_9        (9)
#define pADC_AWDCH_CHANNEL_10        (10)
#define pADC_AWDCH_CHANNEL_11        (11)
#define pADC_AWDCH_CHANNEL_12        (12)
#define pADC_AWDCH_CHANNEL_13        (13)
#define pADC_AWDCH_CHANNEL_14        (14)
#define pADC_AWDCH_CHANNEL_15        (15)
#define pADC_AWDCH_CHANNEL_16        (16)
#define pADC_AWDCH_CHANNEL_17        (17)


#define pADC_EOCIE_ENABLE       (1)
#define pADC_EOCIE_DISABLE      (0)


#define pADC_AWDIE_ENABLE       (1)
#define pADC_AWDIE_DISABLE      (0)

#define pADC_JEOCIE_ENABLE       (1)
#define pADC_JEOCIE_DISABLE      (0)

#define pADC_SCAN_ENABLE       (1)
#define pADC_SCAN_DISABLE      (0)

#define pADC_AWDSGL_ANALOG_WATCHDG_ALL_CHANNELS       (1)
#define pADC_AWDSGL_ANALOG_WATCHDG_ONE_CHANNEL        (0)

#define pADC_JAUTO_ENABLE       (1)
#define pADC_JAUTO_DISABLE      (0)

#define pADC_DISCEN_ENABLE       (1)
#define pADC_DISCEN_DISABLE      (0)

#define pADC_JDISCEN_ENABLE       (1)
#define pADC_JDISCEN_DISABLE      (0)

#define pADC_DISCNUM_1_CHANNEL       (0)
#define pADC_DISCNUM_2_CHANNELS      (1)
#define pADC_DISCNUM_3_CHANNELS      (2)
#define pADC_DISCNUM_4_CHANNELS      (3)
#define pADC_DISCNUM_5_CHANNELS      (4)
#define pADC_DISCNUM_6_CHANNELS      (5)
#define pADC_DISCNUM_7_CHANNELS      (6)
#define pADC_DISCNUM_8_CHANNELS      (7)

#define pADC_DUALMOD_INDEPENDENT_MODE              (0)
#define pADC_DUALMOD_REG_SIM_INJ_SIM               (1)
#define pADC_DUALMOD_REG_SIM_INJ_ALTR_TRIGERR      (2)
#define pADC_DUALMOD_INJ_SIM_INTRLV_FAST       (3)
#define pADC_DUALMOD_INJ_SIM_INTRLV_SLOW       (4)
#define pADC_DUALMOD_INJ_SIM_ONLY                  (5)
#define pADC_DUALMOD_REG_SIM_ONLY                  (6)
#define pADC_DUALMOD_INTRLV_FAST_ONLY              (7)
#define pADC_DUALMOD_INTRLV_SLOW_ONLY              (8)
#define pADC_DUALMOD_ALTR_TRIGGER_ONLY             (9)


#define pADC_JAWDEN_ANALOG_WATCHDG_INJ_CHANNELS_ENABLE       (1)
#define pADC_JAWDEN_ANALOG_WATCHDG_INJ_CHANNELS_DISABLE      (0)

#define pADC_AWDEN_ANALOG_WATCHDG_REG_CHANNELS_ENABLE       (1)
#define pADC_AWDEN_ANALOG_WATCHDG_REG_CHANNELS_DISABLE      (0)






/***************** 4.3- ADC->CR2  ***************/

#define pADC_ADON_ENABLE        (1)
#define pADC_ADON_DISABLE       (0)

#define pADC_CONT_SINGLE_MODE          (0)
#define pADC_CONT_CONTINUOUS_MODE       (1)


#define pADC_CAL_CALIBRATION_COMPLETED  (0)
#define pADC_CAL_ENABLE_CALIBRATION     (1)

#define pADC_RSTCAL_CALIBRATION_REG_INITIALIZED     (0)
#define pADC_RSTCAL_CALIBRATION_REG_START_INIT      (1)

#define pADC_DMA_DISABLE        (0)
#define pADC_DMA_ENABLE         (1)

#define pADC_ALIGN_RIGHT        (0)
#define pADC_ALIGN_LEFT         (1)

#define pADC_JEXTSEL_TIMER1_TRGO           (0)
#define pADC_JEXTSEL_TIMER1_CC4            (1)
#define pADC_JEXTSEL_TIMER2_TRGO           (2)
#define pADC_JEXTSEL_TIMER2_CC1            (3)
#define pADC_JEXTSEL_TIMER3_CC4            (4)
#define pADC_JEXTSEL_TIMER4_TRGO           (5)
#define pADC_JEXTSEL_EXTI15_TIMER8_CC4     (6)
#define pADC_JEXTSEL_JSWSTART              (7)

#define pADC_JEXTTRIG_INJ_CONV_ON_EXT_EVENT_DISABLE         (0)
#define pADC_JEXTTRIG_INJ_CONV_ON_EXT_EVENT_ENABLE          (1)

#define pADC_EXTSEL_TIMER1_CC1          (0)
#define pADC_EXTSEL_TIMER1_CC2          (1)
#define pADC_EXTSEL_TIMER1_CC3          (2)
#define pADC_EXTSEL_TIMER2_CC2          (3)
#define pADC_EXTSEL_TIMER3_TRGO         (4)
#define pADC_EXTSEL_TIMER4_CC4          (5)
#define pADC_EXTSEL_EXTI11_TIM8_TRGO    (6)
#define pADC_EXTSEL_SWSTART             (7)

#define pADC_EXTTRIG_REG_CONV_ON_EXT_EVENT_DISABLE  (0)
#define pADC_EXTTRIG_REG_CONV_ON_EXT_EVENT_ENABLE   (1)

#define pADC_JSWSTART_START_CONV_ON_INJ_CHANNELS    (1)

#define pADC_SWSTART_START_CONV_ON_REG_CHANNELS     (1)

#define pADC_TSVREFE_TEMP_SENSOR_VREF_DISABLE        (0)
#define pADC_TSVREFE_TEMP_SENSOR_VREF_ENABLE         (1)


/***************** 4.4- ADC->SMP1,SMP2  ***************/

#define pADC_SMPx_1_5_CYCLES             (0)
#define pADC_SMPx_7_5_CYCLES             (1)
#define pADC_SMPx_13_5_CYCLES            (2)
#define pADC_SMPx_28_5_CYCLES            (3)
#define pADC_SMPx_41_5_CYCLES            (4)
#define pADC_SMPx_55_5_CYCLES            (5)
#define pADC_SMPx_71_5_CYCLES            (6)
#define pADC_SMPx_239_5_CYCLES           (7)

/***************** 4.5- ADC->SQR1,SQR2,SQR3  ***************/

#define pADC_L_1_CONVERSION         (0)
#define pADC_L_2_CONVERSION         (1)
#define pADC_L_3_CONVERSION         (2)
#define pADC_L_4_CONVERSION         (3)
#define pADC_L_5_CONVERSION         (4)
#define pADC_L_6_CONVERSION         (5)
#define pADC_L_7_CONVERSION         (6)
#define pADC_L_8_CONVERSION         (7)
#define pADC_L_9_CONVERSION         (8)
#define pADC_L_10_CONVERSION         (9)
#define pADC_L_11_CONVERSION         (10)
#define pADC_L_12_CONVERSION         (11)
#define pADC_L_13_CONVERSION         (12)
#define pADC_L_14_CONVERSION         (13)
#define pADC_L_15_CONVERSION         (14)
#define pADC_L_16_CONVERSION         (15)


/***************** 4.6- ADC->JSQR  ***************/
#define pADC_JL_1_CONVERSION         (0)
#define pADC_JL_2_CONVERSION         (1)
#define pADC_JL_3_CONVERSION         (2)
#define pADC_JL_4_CONVERSION         (3)



/***************************************************************/
/*					    	(19) USART						   */
/***************************************************************/

/*
 * 	USART Section Architecture Map
 *		1- USART->Base_Definitions
 *		2- USART->Registers_Pointers
 *		3- USART->Struct_Definition
 *		4- USART->Registers_Values_Definitions
 *			4.1- USART->
 *			4.2- USART->
 *			4.3- USART->
 *
 *
 * */


/***************** 1- USART->Base_Definition ******************/

#define pUSART1_BASE               (0x40013800U)
#define pUSART2_BASE               (0x40004400UL)
#define pUSART3_BASE                (0x40004800UL)

#define pUSART1_SR_BASE            (pUSART1_BASE + 0x00)
#define pUSART1_DR_BASE            (pUSART1_BASE + 0x04)
#define pUSART1_BRR_BASE           (pUSART1_BASE + 0x08)
#define pUSART1_CR1_BASE           (pUSART1_BASE + 0x0C)
#define pUSART1_CR2_BASE           (pUSART1_BASE + 0x10)
#define pUSART1_CR3_BASE           (pUSART1_BASE + 0x14)
#define pUSART1_GTPR_BASE          (pUSART1_BASE + 0x18)

/***************** 2- USART->Registers_Pointers ***************/

#define pUSART1_SR            (*((volatile unsigned long *)pUSART1_SR_BASE))
#define pUSART1_DR            (*((volatile unsigned long *)pUSART1_DR_BASE))
#define pUSART1_BRR           (*((volatile unsigned long *)pUSART1_BRR_BASE))
#define pUSART1_CR1           (*((volatile unsigned long *)pUSART1_CR1_BASE))
#define pUSART1_CR2           (*((volatile unsigned long *)pUSART1_CR2_BASE))
#define pUSART1_CR3           (*((volatile unsigned long *)pUSART1_CR3_BASE))
#define pUSART1_GTPR          (*((volatile unsigned long *)pUSART1_GTPR_BASE))

/***************** 3- USART->Struct_Definition ****************/



typedef volatile struct {

    volatile union {
        struct {
            const unsigned long PE: 1;
            const unsigned long FE: 1;
            const unsigned long NE: 1;
            const unsigned long ORE: 1;
            const unsigned long IDLE: 1;
            unsigned long RXNE: 1;
            unsigned long TC: 1;
            const unsigned long TXE: 1;
            unsigned long LBD: 1;
            unsigned long CTS: 1;
            const unsigned long RESERVED: 22;
        };
        unsigned long REG;
    } SR;

    volatile union {
        struct {
            unsigned long DR: 9;
            const unsigned long RESERVED: 23;
        };
        unsigned long REG;
    } DR;

    volatile union {
        struct {
            unsigned long DIV_Fraction: 4;
            unsigned long DIV_Mantissa: 12;
            const unsigned long RESERVED: 16;
        };
        unsigned long REG;
    } BRR;

    volatile union {
        struct {
            unsigned long SBK: 1;
            unsigned long RWU: 1;
            unsigned long RE: 1;
            unsigned long TE: 1;
            unsigned long IDLEIE: 1;
            unsigned long RXNEIE: 1;
            unsigned long TCIE: 1;
            unsigned long TXEIE: 1;
            unsigned long PEIE: 1;
            unsigned long PS: 1;
            unsigned long PCE: 1;
            unsigned long WAKE: 1;
            unsigned long M: 1;
            unsigned long UE: 1;
            const unsigned long RESERVED: 18;
        };
        unsigned long REG;
    } CR1;

    volatile union {
        struct {
            unsigned long ADD: 4;
            const unsigned long RESERVED: 1;
            unsigned long LBDL: 1;
            unsigned long LBDIE: 1;
            const unsigned long RESERVED: 1;
            unsigned long LBCL: 1;
            unsigned long CPHA: 1;
            unsigned long CPOL: 1;
            unsigned long CLKEN: 1;
            unsigned long STOP: 2;
            unsigned long LINEN: 1;
            const unsigned long RESERVED: 17;
        };
        unsigned long REG;
    } CR2;

    volatile union {
        struct {
            unsigned long EIE: 1;
            unsigned long IREN: 1;
            unsigned long IRLP: 1;
            unsigned long HDSEL: 1;
            unsigned long NACK: 1;
            unsigned long SCEN: 1;
            unsigned long DMAR: 1;
            unsigned long DMAT: 1;
            unsigned long RTSE: 1;
            unsigned long CTSE: 1;
            unsigned long CTSIE: 1;
            const unsigned long RESERVED: 21;
        };
        unsigned long REG;
    } CR3;

    volatile union {
        struct {
            unsigned long PSC: 8;
            unsigned long GT: 8;
            const unsigned long RESERVED: 16;
        };
        unsigned long REG;
    } GTPR;

} USART_t;

#define pUSART1      ((volatile USART_t *) pUSART1_BASE)
#define pUSART2      ((volatile USART_t *) pUSART2_BASE)
#define pUSART3      ((volatile USART_t *) pUSART3_BASE)

extern USART_t *USARTs[3];

/***************** 4- USART->Registers_Values_Definitions *****/

/***************** 4.1- USART->SR  ***************/

#define pUSART_PE_HIGH                           (1)
#define pUSART_FE_HIGH                           (1)
#define pUSART_NE_HIGH                           (1)
#define pUSART_ORE_HIGH                          (1)
#define pUSART_IDLE_HIGH                         (1)
#define pUSART_RXNE_HIGH                         (1)
#define pUSART_TC_HIGH                           (1)
#define pUSART_TXE_HIGH                          (1)
#define pUSART_LBD_HIGH                          (1)
#define pUSART_CTS_HIGH                          (1)

#define pUSART_SR_PE_POS                             (0)
#define pUSART_SR_FE_POS                             (1)
#define pUSART_SR_NE_POS                             (2)
#define pUSART_SR_ORE_POS                            (3)
#define pUSART_SR_IDLE_POS                           (4)
#define pUSART_SR_RXNE_POS                           (5)
#define pUSART_SR_TC_POS                             (6)
#define pUSART_SR_TXE_POS                            (7)
#define pUSART_SR_LBD_POS                            (8)
#define pUSART_SR_CTS_POS                            (9)


#define pUSART_SR_PE_HIGH                (pUSART_PE_HIGH<<USART_SR_PE_POS)
#define pUSART_SR_FE_HIGH                (pUSART_FE_HIGH<<USART_SR_FE_POS)
#define pUSART_SR_NE_HIGH                (pUSART_NE_HIGH<<USART_SR_NE_POS)
#define pUSART_SR_ORE_HIGH               (pUSART_ORE_HIGH<<USART_SR_ORE_POS)
#define pUSART_SR_IDLE_HIGH              (pUSART_IDLE_HIGH<<USART_SR_IDLE_POS)
#define pUSART_SR_RXNE_HIGH              (pUSART_RXNE_HIGH<<USART_SR_RXNE_POS)
#define pUSART_SR_TC_HIGH                (pUSART_TC_HIGH<<USART_SR_TC_POS)
#define pUSART_SR_TXE_HIGH               (pUSART_TXE_HIGH<<USART_SR_TXE_POS)
#define pUSART_SR_LBD_HIGH               (pUSART_LBD_HIGH<<USART_SR_LBD_POS)
#define pUSART_SR_CTS_HIGH               (pUSART_CTS_HIGH<<USART_SR_CTS_POS)

/***************** 4.2- USART->CR1  ***************/

#define pUSART_SBK_SEND_BREAK             (1)

#define pUSART_RWU_ACTIVE_MODE            (0)
#define pUSART_RWU_MUTE_MODE              (1)

#define pUSART_RE_RX_ENABLE               (1)
#define pUSART_RE_RX_DISABLE              (0)

#define pUSART_TE_TX_ENABLE               (1)
#define pUSART_TE_TX_DISABLE              (1)

#define pUSART_IDLEIE_ENABLE              (1)
#define pUSART_IDLEIE_DISABLE             (0)

#define pUSART_RXNEIE_ENABLE              (1)
#define pUSART_RXNEIE_DISABLE             (0)

#define pUSART_TCIE_ENABLE                (1)
#define pUSART_TCIE_DISABLE               (0)

#define pUSART_TXEIE_ENABLE               (1)
#define pUSART_TXEIE_DISABLE              (0)

#define pUSART_PEIE_ENABLE                (1)
#define pUSART_PEIE_DISABLE               (0)

#define pUSART_PS_EVEN                  (0)
#define pUSART_PS_ODD                   (1)

#define pUSART_PCE_ENABLE                 (1)
#define pUSART_PCE_DISABLE                (0)

#define pUSART_WAKE_IDLE_LINE             (0)
#define pUSART_WAKE_ADDRESS_MARK          (0)

#define pUSART_M_8BITS                   (0)
#define pUSART_M_9BITS                   (1)

#define pUSART_UE_ENABLE                 (1)
#define pUSART_UE_DISABLE                (0)


#define  USART_CR1_SBK_POS                  (0)
#define  USART_CR1_RWU_POS                  (1)
#define  USART_CR1_RE_POS                   (2)
#define  USART_CR1_TE_POS                   (3)
#define  USART_CR1_IDLEIE_POS               (4)
#define  USART_CR1_RXNEIE_POS               (5)
#define  USART_CR1_TCIE_POS                 (6)
#define  USART_CR1_TXEIE_POS                (7)
#define  USART_CR1_PEIE_POS                 (8)
#define  USART_CR1_PS_POS                   (9)
#define  USART_CR1_PCE_POS                  (10)
#define  USART_CR1_WAKE_POS                 (11)
#define  USART_CR1_M_POS                    (12)
#define  USART_CR1_UE_POS                   (13)

#define   USART_CR1_SBK_SEND_BREAK             (pUSART_SBK_SEND_BREAK<<USART_CR1_SBK_POS)

#define  USART_CR1_RWU_ACTIVE_MODE            (pUSART_RWU_ACTIVE_MODE<<USART_CR1_RWU_POS)
#define  USART_CR1_RWU_MUTE_MODE              (pUSART_RWU_MUTE_MODE<<USART_CR1_RWU_POS)

#define  USART_CR1_RE_RX_ENABLE               (pUSART_RE_RX_ENABLE<<USART_CR1_RE_POS)
#define  USART_CR1_RE_RX_DISABLE              (pUSART_RE_RX_DISABLE<<USART_CR1_RE_POS)

#define  USART_CR1_TE_TX_ENABLE               (pUSART_TE_TX_ENABLE<<USART_CR1_TE_POS)
#define  USART_CR1_TE_TX_DISABLE              (pUSART_TE_TX_DISABLE<<USART_CR1_TE_POS)

#define  USART_CR1_IDLEIE_ENABLE              (pUSART_IDLEIE_ENABLE<<USART_CR1_IDLEIE_POS)
#define  USART_CR1_IDLEIE_DISABLE             (pUSART_IDLEIE_DISABLE<<USART_CR1_IDLEIE_POS)

#define  USART_CR1_RXNEIE_ENABLE              (pUSART_RXNEIE_ENABLE<<USART_CR1_RXNEIE_POS)
#define  USART_CR1_RXNEIE_DISABLE             (pUSART_RXNEIE_DISABLE<<USART_CR1_RXNEIE_POS)

#define  USART_CR1_TCIE_ENABLE                (pUSART_TCIE_ENABLE<<USART_CR1_TCIE_POS)
#define  USART_CR1_TCIE_DISABLE               (pUSART_TCIE_DISABLE<<USART_CR1_TCIE_POS)

#define  USART_CR1_TXEIE_ENABLE               (pUSART_TXEIE_ENABLE<<USART_CR1_TXEIE_POS)
#define  USART_CR1_TXEIE_DISABLE              (pUSART_TXEIE_DISABLE<<USART_CR1_TXEIE_POS)

#define  USART_CR1_PEIE_ENABLE                (pUSART_PEIE_ENABLE<<USART_CR1_PEIE_POS)
#define  USART_CR1_PEIE_DISABLE               ((pUSART_PEIE_DISABLE<<USART_CR1_PEIE_POS))

#define  USART_CR1_PS_EVEN                    (pUSART_PS_EVEN<<USART_CR1_PS_POS)
#define  USART_CR1_PS_ODD                     (pUSART_PS_ODD<<USART_CR1_PS_POS)

#define  USART_CR1_PCE_ENABLE                 (pUSART_PCE_ENABLE<<USART_CR1_PCE_POS)
#define  USART_CR1_PCE_DISABLE                (pUSART_PCE_DISABLE<<USART_CR1_PCE_POS)

#define  USART_CR1_WAKE_IDLE_LINE             (pUSART_WAKE_IDLE_LINE<<USART_CR1_WAKE_POS)
#define  USART_CR1_WAKE_ADDRESS_MARK          (pUSART_WAKE_ADDRESS_MARK<<USART_CR1_WAKE_POS)

#define  USART_CR1_M_8BITS                   (pUSART_M_8BITS<<USART_CR1_M_POS)
#define  USART_CR1_M_9BITS                   (pUSART_M_9BITS<<USART_CR1_M_POS)

#define  USART_CR1_UE_ENABLE                 (pUSART_UE_ENABLE<<USART_CR1_UE_POS)
#define  USART_CR1_UE_DISABLE                (pUSART_UE_DISABLE<<USART_CR1_UE_POS)

/***************** 4.3- USART->CR2  ***************/


#define pUSART_CR2_ADD_POS                    (0)
#define pUSART_CR2_LBDL_POS                   (5)
#define pUSART_CR2_LBDIE_POS                  (6)
#define pUSART_CR2_LBCL_POS                   (8)
#define pUSART_CR2_CPHA_POS                   (9)
#define pUSART_CR2_CPOL_POS                   (10)
#define pUSART_CR2_CLKEN_POS                  (11)
#define pUSART_CR2_STOP_POS                   (12)
#define pUSART_CR2_LINEN_POS                  (14)

#define pUSART_LBDL_10BIT_BREAK_DETECT                   (0)
#define pUSART_LBDL_11BIT_BREAK_DETECT                   (1)
#define pUSART_CR2_LBDL_10BIT_BREAK_DETECT               (pUSART_LBDL_10BIT_BREAK_DETECT<<USART_CR2_LBDL_POS)
#define pUSART_CR2_LBDL_11BIT_BREAK_DETECT               (pUSART_LBDL_11BIT_BREAK_DETECT<<USART_CR2_LBDL_POS)

#define pUSART_LBDIE_ENABLE_INTERRUPT                    (1)
#define pUSART_LBDIE_DISABLE_INTERRUPT                   (0)
#define pUSART_CR2_LBDIE_ENABLE_INTERRUPT                (pUSART_LBDIE_ENABLE_INTERRUPT<<USART_CR2_LBDIE_POS)
#define pUSART_CR2_LBDIE_DISABLE_INTERRUPT               (pUSART_LBDIE_DISABLE_INTERRUPT<<USART_CR2_LBDIE_POS)

#define pUSART_LBCL_OUTPUT_LAST_BIT_CLK_ENABLE           (1)
#define pUSART_LBCL_OUTPUT_LAST_BIT_CLK_DISABLE          (0)
#define pUSART_CR2_LBCL_OUTPUT_LAST_BIT_CLK_ENABLE       (pUSART_LBCL_OUTPUT_LAST_BIT_CLK_ENABLE<<USART_CR2_LBCL_POS)
#define pUSART_CR2_LBCL_OUTPUT_LAST_BIT_CLK_DISABLE      (pUSART_LBCL_OUTPUT_LAST_BIT_CLK_DISABLE<<USART_CR2_LBCL_POS)


#define pUSART_CPHA_FIRST_EDGE                           (0)
#define pUSART_CPHA_SECOND_EDGE                          (1)
#define pUSART_CR2_CPHA_FIRST_EDGE                       (pUSART_CPHA_FIRST_EDGE<<USART_CR2_CPHA_POS)
#define pUSART_CR2_CPHA_SECOND_EDGE                      (pUSART_CPHA_SECOND_EDGE<<USART_CR2_CPHA_POS)


#define pUSART_CPOL_IDLE_LOW_VOLTAGE                     (0)
#define pUSART_CPOL_IDLE_HIGH_VOLTAGE                    (1)
#define pUSART_CR2_CPOL_IDLE_LOW_VOLTAGE                 (pUSART_CPOL_IDLE_LOW_VOLTAGE<<USART_CR2_CPOL_POS)
#define pUSART_CR2_CPOL_IDLE_HIGH_VOLTAGE                (pUSART_CPOL_IDLE_HIGH_VOLTAGE<<USART_CR2_CPOL_POS)

#define pUSART_CLKEN_CLK_ENABLE                          (1)
#define pUSART_CLKEN_CLK_DISABLE                         (0)
#define pUSART_CR2_CLKEN_CLK_ENABLE                      (pUSART_CLKEN_CLK_ENABLE<<USART_CR2_CLKEN_POS)
#define pUSART_CR2_CLKEN_CLK_DISABLE                     (pUSART_CLKEN_CLK_DISABLE<<USART_CR2_CLKEN_POS)


#define pUSART_STOP_ONE_STOP_BIT                    (0)
#define pUSART_STOP_HALF_STOP_BIT                   (1)
#define pUSART_STOP_TWO_STOP_BIT                    (2)
#define pUSART_STOP_ONE_AND_HALF_STOP_BIT           (3)

#define pUSART_CR2_STOP_ONE_STOP_BIT                (pUSART_STOP_ONE_STOP_BIT<<USART_CR2_STOP_POS)
#define pUSART_CR2_STOP_HALF_STOP_BIT               (pUSART_STOP_HALF_STOP_BIT<<USART_CR2_STOP_POS)
#define pUSART_CR2_STOP_TWO_STOP_BIT                (pUSART_STOP_TWO_STOP_BIT<<USART_CR2_STOP_POS)
#define pUSART_CR2_STOP_ONE_AND_HALF_STOP_BIT       (pUSART_STOP_ONE_AND_HALF_STOP_BIT<<USART_CR2_STOP_POS)

#define pUSART_LINEN_LINE_MODE_ENABLE               (1)
#define pUSART_LINEN_LINE_MODE_DISABLE              (0)

#define pUSART_CR2_LINEN_LINE_MODE_ENABLE           (pUSART_LINEN_LINE_MODE_ENABLE<<USART_CR2_LINEN_POS)
#define pUSART_CR2_LINEN_LINE_MODE_DISABLE          (pUSART_LINEN_LINE_MODE_DISABLE<<USART_CR2_LINEN_POS)


/***************** 4.4- USART->CR3  ***************/

#define pUSART_CR3_EIE_POS               (0)
#define pUSART_CR3_IREN_POS              (1)
#define pUSART_CR3_IRLP_POS              (2)
#define pUSART_CR3_HDSEL_POS             (3)
#define pUSART_CR3_NACK_POS              (4)
#define pUSART_CR3_SCEN_POS              (5)
#define pUSART_CR3_DMAR_POS              (6)
#define pUSART_CR3_DMAT_POS              (7)
#define pUSART_CR3_RTSE_POS              (8)
#define pUSART_CR3_CTSE_POS              (9)
#define pUSART_CR3_CTSIE_POS             (10)

#define pUSART_EIE_ERROR_INT_ENABLE                 (1)
#define pUSART_CR3_EIE_ERROR_INT_ENABLE             (pUSART_EIE_ERROR_INT_ENABLE<<USART_CR2_EIE_POS)
#define pUSART_EIE_ERROR_INT_DISABLE                (0)
#define pUSART_CR3_EIE_ERROR_INT_DISABLE            (pUSART_EIE_ERROR_INT_DISABLE<<USART_CR2_EIE_POS)

#define pUSART_IREN_irDA_ENABLED                    (1)
#define pUSART_CR3_IREN_irDA_ENABLED                (pUSART_IREN_irDA_ENABLED<<USART_CR2_IREN_POS)
#define pUSART_IREN_irDA_DISABLED                   (0)
#define pUSART_CR3_IREN_irDA_DISABLED               (pUSART_IREN_irDA_DISABLED<<USART_CR2_IREN_POS)

#define pUSART_IRLP_irDA_NORMAL_MODE                (0)
#define pUSART_CR3_IRLP_irDA_NORMAL_MODE            (pUSART_IRLP_irDA_NORMAL_MODE<<USART_CR2_IRLP_POS)
#define pUSART_IRLP_irDA_LOW_PWR_MODE               (1)
#define pUSART_CR3_IRLP_irDA_LOW_PWR_MODE           (pUSART_IRLP_irDA_LOW_PWR_MODE<<USART_CR2_IRLP_POS)

#define pUSART_HDSEL_HALF_DUPLEX_SELECTED           (1)
#define pUSART_CR3_HDSEL_HALF_DUPLEX_SELECTED       (pUSART_HDSEL_HALF_DUPLEX_SELECTED<<USART_CR2_HDSEL_POS)
#define pUSART_HDSEL_HALF_DUPLEX_NOT_SELECTED       (0)
#define pUSART_CR3_HDSEL_HALF_DUPLEX_NOT_SELECTED   (pUSART_HDSEL_HALF_DUPLEX_NOT_SELECTED<<USART_CR2_HDSEL_POS)


#define pUSART_NACK_END_IF_PARITY_ERROR_ENABLE           (1)
#define pUSART_CR3_NACK_END_IF_PARITY_ERROR_ENABLE       (pUSART_NACK_END_IF_PARITY_ERROR_ENABLE<<USART_CR2_NACK_POS)
#define pUSART_NACK_END_IF_PARITY_ERROR_DISABLE          (0)
#define pUSART_CR3_NACK_END_IF_PARITY_ERROR_DISABLE      (pUSART_NACK_END_IF_PARITY_ERROR_DISABLE<<USART_CR2_NACK_POS)

#define pUSART_SCEN_SMART_CARD_MODE_ENABLE               (1)
#define pUSART_CR3_SCEN_SMART_CARD_MODE_ENABLE           (pUSART_SCEN_SMART_CARD_MODE_ENABLE<<USART_CR2_SCEN_POS)
#define pUSART_SCEN_SMART_CARD_MODE_DISABLE              (0)
#define pUSART_CR3_SCEN_SMART_CARD_MODE_DISABLE          (pUSART_SCEN_SMART_CARD_MODE_DISABLE<<USART_CR2_SCEN_POS)


#define pUSART_DMAR_DMA_RX_ENABLE                    (1)
#define pUSART_CR3_DMAR_DMA_RX_ENABLE                (pUSART_DMAR_DMA_RX_ENABLE<<USART_CR2_DMAR_POS)
#define pUSART_DMAR_DMA_RX_DISABLE                   (0)
#define pUSART_CR3_DMAR_DMA_RX_DISABLE               (pUSART_DMAR_DMA_RX_DISABLE<<USART_CR2_DMAR_POS)

#define pUSART_DMAT_DMA_TX_ENABLE                    (1)
#define pUSART_CR3_DMAT_DMA_TX_ENABLE                (pUSART_DMAT_DMA_TX_ENABLE<<USART_CR2_DMAT_POS)
#define pUSART_DMAT_DMA_TX_DISABLE                   (0)
#define pUSART_CR3_DMAT_DMA_TX_DISABLE               (pUSART_DMAT_DMA_TX_DISABLE<<USART_CR2_DMAT_POS)

#define pUSART_RTSE_RTS_ENABLE                 (1)
#define pUSART_CR3_RTSE_RTS_FLOW_CONTROL_ENABLE             (pUSART_RTSE_RTS_ENABLE<<USART_CR2_RTSE_POS)
#define pUSART_RTSE_RTS_DISABLE                (0)
#define pUSART_CR3_RTSE_RTS_FLOW_CONTROL_DISABLE            (pUSART_RTSE_RTS_DISABLE<<USART_CR2_RTSE_POS)

#define pUSART_CTSE_CTS_ENABLE                 (1)
#define pUSART_CR3_CTSE_CTS_FLOW_CONTROL_ENABLE             (pUSART_CTSE_CTS_ENABLE<<USART_CR2_CTSE_POS)
#define pUSART_CTSE_CTS_DISABLE                (0)
#define pUSART_CR3_CTSE_CTS_FLOW_CONTROL_DISABLE            (pUSART_CTSE_CTS_DISABLE<<USART_CR2_CTSE_POS)

#define pUSART_CTSIE_CTS_INTERRUPT_ENABLE                   (1)
#define pUSART_CR3_CTSIE_CTS_INTERRUPT_ENABLE               (pUSART_CTSIE_CTS_INTERRUPT_ENABLE<<USART_CR2_CTSIE_POS)
#define pUSART_CTSIE_CTS_INTERRUPT_DISABLE                  (0)
#define pUSART_CR3_CTSIE_CTS_INTERRUPT_DISABLE              (pUSART_CTSIE_CTS_INTERRUPT_DISABLE<<USART_CR2_CTSIE_POS)

/***************** 4.5- USART->GTPR  ***************/

#define pUSART_GTPR_PSC_POS             (0)
#define pUSART_GTPR_GT_POS              (8)



// TODO GuardTime Prescaller for USART

/***************************************************************/
/*					    	(15) TIMERs (ADVANCED)			   */
/***************************************************************/

/*
 * 	TIMERs (ADVANCED) Section Architecture Map
 *		1- TIMERs (ADVANCED)->Base_Definitions
 *		2- TIMERs (ADVANCED)->Registers_Pointers
 *		3- TIMERs (ADVANCED)->Struct_Definition
 *		4- TIMERs (ADVANCED)->Registers_Values_Definitions
 *			4.1- TIMERs (ADVANCED)->
 *			4.2- TIMERs (ADVANCED)->
 *			4.3- TIMERs (ADVANCED)->
 *			4.4- TIMERs (ADVANCED)->
 *			4.5- TIMERs (ADVANCED)->
 *			4.6- TIMERs (ADVANCED)->
 *
 *
 * */


/***************** 1- TIMERs (ADVANCED)->Base_Definition ******************/


#define TIMER1_BASE       (PERIPHERAL_MEMORY_BASE + 0x12C00)

#define TIMER1_CR1_BASE     (TIMER1_BASE + 0x00)
#define TIMER1_CR2_BASE     (TIMER1_BASE + 0x04)
#define TIMER1_SMCR_BASE    (TIMER1_BASE + 0x08)
#define TIMER1_DIER_BASE    (TIMER1_BASE + 0x0C)
#define TIMER1_SR_BASE      (TIMER1_BASE + 0x10)
#define TIMER1_EGR_BASE     (TIMER1_BASE + 0x14)
#define TIMER1_CCMR1_BASE   (TIMER1_BASE + 0x18)
#define TIMER1_CCMR2_BASE   (TIMER1_BASE + 0x1C)
#define TIMER1_CCER_BASE    (TIMER1_BASE + 0x20)
#define TIMER1_CNT_BASE     (TIMER1_BASE + 0x24)
#define TIMER1_PSC_BASE     (TIMER1_BASE + 0x28)
#define TIMER1_ARR_BASE     (TIMER1_BASE + 0x2C)
#define TIMER1_RCR_BASE     (TIMER1_BASE + 0x30)
#define TIMER1_CCR1_BASE    (TIMER1_BASE + 0x34)
#define TIMER1_CCR2_BASE    (TIMER1_BASE + 0x38)
#define TIMER1_CCR3_BASE    (TIMER1_BASE + 0x3C)
#define TIMER1_CCR4_BASE    (TIMER1_BASE + 0x40)
#define TIMER1_BDTR_BASE    (TIMER1_BASE + 0x44)
#define TIMER1_DCR_BASE     (TIMER1_BASE + 0x48)
#define TIMER1_DMAR_BASE    (TIMER1_BASE + 0x4C)

/***************** 2- TIMERs (ADVANCED)->Registers_Pointers ***************/

#define TIMER1_CR1      (*((uint32_t *)TIMER1_CR1_BASE))
#define TIMER1_CR2      (*((uint32_t *)TIMER1_CR2_BASE))
#define TIMER1_SMCR     (*((uint32_t *)TIMER1_SMCR_BASE))
#define TIMER1_DIER     (*((uint32_t *)TIMER1_DIER_BASE))
#define TIMER1_SR       (*((uint32_t *)TIMER1_SR_BASE))
#define TIMER1_EGR      (*((uint32_t *)TIMER1_EGR_BASE))
#define TIMER1_CCMR1    (*((uint32_t *)TIMER1_CCMR1_BASE))
#define TIMER1_CCMR2    (*((uint32_t *)TIMER1_CCMR2_BASE))
#define TIMER1_CCER     (*((uint32_t *)TIMER1_CCER_BASE))
#define TIMER1_CNT      (*((uint32_t *)TIMER1_CNT_BASE))
#define TIMER1_PSC      (*((uint32_t *)TIMER1_PSC_BASE))
#define TIMER1_ARR      (*((uint32_t *)TIMER1_ARR_BASE))
#define TIMER1_RCR      (*((uint32_t *)TIMER1_RCR_BASE))
#define TIMER1_CCR1     (*((uint32_t *)TIMER1_CCR1_BASE))
#define TIMER1_CCR2     (*((uint32_t *)TIMER1_CCR2_BASE))
#define TIMER1_CCR3     (*((uint32_t *)TIMER1_CCR3_BASE))
#define TIMER1_CCR4     (*((uint32_t *)TIMER1_CCR4_BASE))
#define TIMER1_BDTR     (*((uint32_t *)TIMER1_BDTR_BASE))
#define TIMER1_DCR      (*((uint32_t *)TIMER1_DCR_BASE))
#define TIMER1_DMAR     (*((uint32_t *)TIMER1_DMAR_BASE))

/***************** 3- TIMERs (ADVANCED)->Struct_Definition ****************/


typedef volatile struct {
    union {
        struct {
            uint32_t CEN: 1;
            uint32_t UDIS: 1;
            uint32_t URS: 1;
            uint32_t OPM: 1;
            uint32_t DIR: 1;
            uint32_t CMS: 2;
            uint32_t APRE: 1;
            uint32_t CKD: 2;
        };
        uint32_t REG;
    } CR1;


    union {
        struct {
            uint32_t CCPC: 1;
            const uint32_t      : 1;
            uint32_t CCUS: 1;
            uint32_t CCDS: 1;
            uint32_t MMS: 3;
            uint32_t TI1S: 1;
            uint32_t OIS1: 1;
            uint32_t OIS1N: 1;
            uint32_t OIS2: 1;
            uint32_t OIS2N: 1;
            uint32_t OIS3: 1;
            uint32_t OIS3N: 1;
            uint32_t OIS4: 1;
        };
        uint32_t REG;
    } CR2;

    union {
        struct {
            uint32_t SMS: 3;
            const uint32_t      : 1;
            uint32_t TS: 3;
            uint32_t MSM: 1;
            uint32_t ETF: 4;
            uint32_t ETPS: 2;
            uint32_t ECE: 1;
            uint32_t ETP: 1;
        };
        uint32_t REG;
    } SMCR;

    union {
        struct {
            uint32_t UIE: 1;
            uint32_t CC1IE: 1;
            uint32_t CC2IE: 1;
            uint32_t CC3IE: 1;
            uint32_t CC4IE: 1;
            uint32_t COMIE: 1;
            uint32_t TIE: 1;
            uint32_t BIE: 1;
            uint32_t UDE: 1;
            uint32_t CC1DE: 1;
            uint32_t CC2DE: 1;
            uint32_t CC3DE: 1;
            uint32_t CC4DE: 1;
            uint32_t COMDE: 1;
            uint32_t TDE: 1;

        };
        uint32_t REG;
    } DIER;

    union {
        struct {
            uint32_t UIF: 1;
            uint32_t CC1IF: 1;
            uint32_t CC2IF: 1;
            uint32_t CC3IF: 1;
            uint32_t CC4IF: 1;
            uint32_t COMIF: 1;
            uint32_t TIF: 1;
            uint32_t BIF: 1;
            const uint32_t      : 1;
            uint32_t CC1OF: 1;
            uint32_t CC2OF: 1;
            uint32_t CC3OF: 1;
            uint32_t CC4OF: 1;
        };
        uint32_t REG;
    } SR;

    union {
        struct {
            uint32_t UG: 1;
            uint32_t CC1G: 1;
            uint32_t CC2G: 1;
            uint32_t CC3G: 1;
            uint32_t CC4G: 1;
            uint32_t COMG: 1;
            uint32_t TG: 1;
            uint32_t BG: 1;
        };
        uint32_t REG;
    } EGR;

    union {
        struct {
            uint8_t CCM;
        } ALL_CCMR[4];
        struct {
            uint8_t CCS: 2;
            uint8_t OCFE: 1;
            uint8_t OCPE: 1;
            uint8_t OCM: 3;
            uint8_t OCCE: 1;
        } ALL_CCMR_OutputCompareMode[4];
        struct {
            uint8_t CCS: 2;
            uint8_t ICPSC: 2;
            uint8_t ICF: 4;

        } All_CCMR_InputCaptureMode[4];


        struct {
            union {
                struct {
                    const uint32_t      : 2;
                    uint32_t OC1FE: 1;
                    uint32_t OC1PE: 1;
                    uint32_t OC1M: 3;
                    uint32_t OC1CE: 1;

                    const uint32_t      : 2;
                    uint32_t OC2FE: 1;
                    uint32_t OC2PE: 1;
                    uint32_t OC2M: 3;
                    uint32_t OC2CE: 1;
                };
                struct {
                    uint32_t CC1S: 2;
                    uint32_t IC1PSC: 2;
                    uint32_t IC1F: 4;

                    uint32_t CC2S: 2;
                    uint32_t IC2PSC: 2;
                    uint32_t IC2F: 4;
                };
                uint32_t REG;
            } CCMR1;


            union {
                struct {
                    const uint32_t      : 2;
                    uint32_t OC3FE: 1;
                    uint32_t OC3PE: 1;
                    uint32_t OC3M: 3;
                    uint32_t OC3CE: 1;

                    const uint32_t      : 2;
                    uint32_t OC4FE: 1;
                    uint32_t OC4PE: 1;
                    uint32_t OC4M: 3;
                    uint32_t OC4CE: 1;
                };
                struct {
                    uint32_t CC3S: 2;
                    uint32_t IC3PSC: 2;
                    uint32_t IC3F: 4;

                    uint32_t CC4S: 2;
                    uint32_t IC4PSC: 2;
                    uint32_t IC4F: 4;
                };
                uint32_t REG;
            } CCMR2;
        };
    };

    union {
        struct {
            uint32_t CC1E: 1;
            uint32_t CC1P: 1;
            uint32_t CC1NE: 1;
            uint32_t CC1NP: 1;
            uint32_t CC2E: 1;
            uint32_t CC2P: 1;
            uint32_t CC2NE: 1;
            uint32_t CC2NP: 1;
            uint32_t CC3E: 1;
            uint32_t CC3P: 1;
            uint32_t CC3NE: 1;
            uint32_t CC3NP: 1;
            uint32_t CC4E: 1;
            uint32_t CC4P: 1;
            const uint32_t      : 1;
            uint32_t CC4NP: 1;
        };
        uint32_t REG;
    } CCER;

    union {
        struct {
            uint32_t CNT: 16;
        };
        uint32_t REG;
    } CNT;

    union {
        struct {
            uint32_t PSC: 16;
        };
        uint32_t REG;
    } PSC;

    union {
        struct {
            uint32_t ARR: 16;
        };
        uint32_t REG;
    } ARR;

    union {
        struct {
            uint32_t REP: 8;
        };
        uint32_t REG;
    } RCR;

    union {
        union {
            struct {
                uint32_t CC: 16;
            };
            uint32_t REG;
        } All_CCRs[4];

        struct {
            union {
                struct {
                    uint32_t CC: 16;
                };
                uint32_t REG;
            } CCR1;

            union {
                struct {
                    uint32_t CC: 16;
                };
                uint32_t REG;
            } CCR2;

            union {
                struct {
                    uint32_t CC: 16;
                };
                uint32_t REG;
            } CCR3;

            union {
                struct {
                    uint32_t CC: 16;
                };
                uint32_t REG;
            } CCR4;
        };
    };


    union {
        struct {
            uint32_t DTG: 8;
            uint32_t LOCK: 2;
            uint32_t OSSI: 1;
            uint32_t OSSR: 1;
            uint32_t BKE: 1;
            uint32_t BKP: 1;
            uint32_t AOE: 1;
            uint32_t MOE: 1;
        };
        uint32_t REG;
    } BDTR;

    union {
        struct {
            uint32_t DBA: 5;
            const uint32_t      : 3;
            uint32_t DBL: 5;
            const uint32_t      : 3;
        };
        uint32_t REG;
    } DCR;

    union {
        struct {
            uint32_t DMAB: 32;
        };
        uint32_t REG;
    } DMAR;

} TIMER_Memory_Unit_t;

#define pTIMER1      ((TIMER_Memory_Unit_t *)TIMER1_BASE)
/***************** 4- TIMERs (ADVANCED)->Registers_Values_Definitions *****/
/***************** 4.1- TIMERs (ADVANCED)->CR1  ***************/

#define TIMERS_CEN_ENABLE       (1)
#define TIMERS_CEN_DISABLE      (0)

#define TIMERS_UDIS_DISABLE_UPDATES       (1)
#define TIMERS_UDIS_ENABLE_UPDATES      (0)

#define TIMERS_URS_ALL       (1)
#define TIMERS_URS_ONLY_COUNTER      (0)

#define TIMERS_OPM_ENABLE       (1)
#define TIMERS_OPM_DISABLE      (0)

#define TIMERS_DIR_UP          (0)
#define TIMERS_DIR_DOWN        (1)

#define TIMERS_CMS_EDGE_ALIGNED              (0)
#define TIMERS_CMS_CENTER_ALIGNED_MODE1      (1)
#define TIMERS_CMS_CENTER_ALIGNED_MODE2      (2)
#define TIMERS_CMS_CENTER_ALIGNED_MODE3      (3)


#define TIMERS_ARPE_BUFFER_ENABLE       (1)
#define TIMERS_ARPE_BUFFER_DISABLE      (0)

#define TIMERS_CKD_DIV_BY_1      (0)
#define TIMERS_CKD_DIV_BY_2      (1)
#define TIMERS_CKD_DIV_BY_4      (2)

/***************** 4.2- TIMERs (ADVANCED)->CR2  ***************/

#define TIMERS_CCPC_CAPTURE_COMPARE_PRELOADED   (1)
#define TIMERS_CCPC_CAPTURE_COMPARE_NOT_PRELOADED   (0)

#define TIMERS_CCUS_UPDATE_ON_COMG_ONLY                (0)
#define TIMERS_CCUS_UPDATE_ON_COMG_AND_RISING_TRGI     (1

#define TIMERS_CCDS_DMA_REQ_CCx      (0)
#define TIMERS_CCDS_DMA_REQ_UEV      (1)


#define TIMERS_MMS_RESET             (0)
#define TIMERS_MMS_ENABLE            (1)
#define TIMERS_MMS_UPDATE            (2)
#define TIMERS_MMS_COMP_PULSE        (3)
#define TIMERS_MMS_COMP_OC1REF       (4)
#define TIMERS_MMS_COMP_OC2REF       (5)
#define TIMERS_MMS_COMP_OC3REF       (6)
#define TIMERS_MMS_COMP_OC4REF       (7)

#define TIMERS_TI1S_CH1_TO_TI1                          (0)
#define TIMERS_TI1S_CH1_CH2_CH3_XOR_TO_TI1              (1)

#define TIMERS_OIS1_OC1_LOW_WHEN_MOE_LOW        (0)
#define TIMERS_OIS1_OC1_HIGH_WHEN_MOE_LOW       (1)

#define TIMERS_OIS1_OC1N_LOW_WHEN_MOE_LOW        (0)
#define TIMERS_OIS1_OC1N_HIGH_WHEN_MOE_LOW       (1)


#define TIMERS_OIS2_OC2_LOW_WHEN_MOE_LOW        (0)
#define TIMERS_OIS2_OC2_HIGH_WHEN_MOE_LOW       (1)

#define TIMERS_OIS2_OC2N_LOW_WHEN_MOE_LOW        (0)
#define TIMERS_OIS2_OC2N_HIGH_WHEN_MOE_LOW       (1)

#define TIMERS_OIS3_OC3_LOW_WHEN_MOE_LOW        (0)
#define TIMERS_OIS3_OC3_HIGH_WHEN_MOE_LOW       (1)

#define TIMERS_OIS3_OC3N_LOW_WHEN_MOE_LOW        (0)
#define TIMERS_OIS3_OC3N_HIGH_WHEN_MOE_LOW       (1)

#define TIMERS_OIS4_OC4_LOW_WHEN_MOE_LOW        (0)
#define TIMERS_OIS4_OC4_HIGH_WHEN_MOE_LOW       (1)




/***************** 4.3- TIMERs (ADVANCED)->SMCR  ***************/

#define TIMERS_SMS_INTERNAL_CLK                  (0)
#define TIMERS_SMS_ENCODER_1_TI1FP2              (1)
#define TIMERS_SMS_ENCODER_2_TI2FP1              (2)
#define TIMERS_SMS_ENCODER_3_TI1FP1_TI1FP2       (3)
#define TIMERS_SMS_RESET_ON_TRIGGER              (4)
#define TIMERS_SMS_GATED_COUNT_ON_HIGH_LEVEL     (5)
#define TIMERS_SMS_TRIGGER_START                 (6)
#define TIMERS_SMS_TRIGGER_IS_CLK                (7)
#define TIMERS_SMS_EXT_CLK_MOD_1                 (7)

#define TIMERS_TS_ITR0           (0)
#define TIMERS_TS_ITR1           (1)
#define TIMERS_TS_ITR2           (2)
#define TIMERS_TS_ITR3           (3)
#define TIMERS_TS_TI1_ED         (4)
#define TIMERS_TS_TI1FP1         (5)
#define TIMERS_TS_TI2FP2         (6)
#define TIMERS_TS_ETRF           (7)

#define TIMERS_MSM_NO_ACTION    (0)
#define TIMERS_MSM_DELAY_TO_SYNC    (1)     // used when sync different timers on same external source

#define TIMERS_ETF_DTS_NO_FILTER (0)
#define TIMERS_ETF_CK_INT_N2      (1)
#define TIMERS_ETF_CK_INT_N4      (2)
#define TIMERS_ETF_CK_INT_N8     (3)
#define TIMERS_ETF_DTS_2_N6       (4)
#define TIMERS_ETF_DTS_2_N8       (5)
#define TIMERS_ETF_DTS_4_N6      (6)
#define TIMERS_ETF_DTS_4_N8       (7)
#define TIMERS_ETF_DTS_8_N6       (8)
#define TIMERS_ETF_DTS_8_N8       (9)
#define TIMERS_ETF_DTS_16_N5      (10)
#define TIMERS_ETF_DTS_16_N6      (11)
#define TIMERS_ETF_DTS_16_N8      (12)
#define TIMERS_ETF_DTS_32_N5      (13)
#define TIMERS_ETF_DTS_32_N6      (14)
#define TIMERS_ETF_DTS_32_N8      (15)

#define TIMERS_ETPS_DIV_1          (0)
#define TIMERS_ETPS_DIV_2          (1)
#define TIMERS_ETPS_DIV_4          (2)
#define TIMERS_ETPS_DIV_8          (3)

#define TIMERS_ECE_CLK_SRC_ETRF_ENABLE    (1)
#define TIMERS_ECE_CLK_SRC_ETRF_DISABLE   (0)

#define TIMERS_ECE_EXT_CLK_MOD2_ENABLE    (1)
#define TIMERS_ECE_EXT_CLK_MOD2_DISABLE   (0)

#define TIMERS_ETP_POLARITY_NON_INV  (0)
#define TIMERS_ETP_POLARITY_INV      (1)

/***************** 4.4- TIMERs (ADVANCED)->DIER  ***************/

#define TIMERS_UIE_ENABLE        (1)
#define TIMERS_UIE_DISABLE       (0)

#define TIMERS_CC1IE_ENABLE        (1)
#define TIMERS_CC1IE_DISABLE       (0)
#define TIMERS_CC2IE_ENABLE        (1)
#define TIMERS_CC2IE_DISABLE       (0)
#define TIMERS_CC3IE_ENABLE        (1)
#define TIMERS_CC3IE_DISABLE       (0)
#define TIMERS_CC4IE_ENABLE        (1)
#define TIMERS_CC4IE_DISABLE       (0)

#define TIMERS_COMIE_ENABLE       (1)
#define TIMERS_COMIE_DISABLE      (0)

#define TIMERS_TIE_ENABLE        (1)
#define TIMERS_TIE_DISABLE       (0)

#define TIMERS_BIE_ENABLE       (1)
#define TIMERS_BIE_DISABLE      (0)

#define TIMERS_UDE_ENABLE        (1)
#define TIMERS_UDE_DISABLE       (0)

#define TIMERS_CC1DE_ENABLE        (1)
#define TIMERS_CC1DE_DISABLE       (0)
#define TIMERS_CC2DE_ENABLE        (1)
#define TIMERS_CC2DE_DISABLE       (0)
#define TIMERS_CC3DE_ENABLE        (1)
#define TIMERS_CC3DE_DISABLE       (0)
#define TIMERS_CC4DE_ENABLE        (1)
#define TIMERS_CC4DE_DISABLE       (0)

#define TIMERS_COMDE_ENABLE      (1)
#define TIMERS_COMDE_DISABLE     (0)

#define TIMERS_TDE_ENABLE        (1)
#define TIMERS_TDE_DISABLE       (0)

#define TIMERS_UIE_POS            (0)
#define TIMERS_CC1IE_POS          (1)
#define TIMERS_CC2IE_POS          (2)
#define TIMERS_CC3IE_POS          (3)
#define TIMERS_CC4IE_POS          (4)
#define TIMERS_COMIE_POS          (5)
#define TIMERS_TIE_POS            (6)
#define TIMERS_BIE_POS            (7)
#define TIMERS_UDE_POS            (8)
#define TIMERS_CC1DE_POS          (9)
#define TIMERS_CC2DE_POS          (10)
#define TIMERS_CC3DE_POS          (11)
#define TIMERS_CC4DE_POS          (12)
#define TIMERS_COMDE_POS          (13)
#define TIMERS_TDE_POS            (14)


/***************** 4.5- TIMERs (ADVANCED)->SR  ***************/

#define TIMERS_UIF_ON          (1)
#define TIMERS_UIF_OFF         (0)
#define TIMERS_UIF_CLEAR       (TIMERS_UIF_OFF)

#define TIMERS_CC1IF_ON          (1)
#define TIMERS_CC1IF_OFF         (0)
#define TIMERS_CC1IF_CLEAR       (TIMERS_CC1IF_OFF)
#define TIMERS_CC2IF_ON          (1)
#define TIMERS_CC2IF_OFF         (0)
#define TIMERS_CC2IF_CLEAR       (TIMERS_CC2IF_OFF)
#define TIMERS_CC3IF_ON          (1)
#define TIMERS_CC3IF_OFF         (0)
#define TIMERS_CC3IF_CLEAR       (TIMERS_CC3IF_OFF)
#define TIMERS_CC4IF_ON          (1)
#define TIMERS_CC4IF_OFF         (0)
#define TIMERS_CC4IF_CLEAR       (TIMERS_CC4IF_OFF)

#define TIMERS_COMIF_ON          (1)
#define TIMERS_COMIF_OFF         (0)
#define TIMERS_COMIF_CLEAR       (TIMERS_COMIF_OFF)

#define TIMERS_TIF_ON          (1)
#define TIMERS_TIF_OFF         (0)
#define TIMERS_TIF_CLEAR       (TIMERS_TIF_OFF)

#define TIMERS_CC1OF_ON          (1)
#define TIMERS_CC1OF_OFF         (0)
#define TIMERS_CC1OF_CLEAR       (TIMERS_CC1OF_OFF)
#define TIMERS_CC2OF_ON          (1)
#define TIMERS_CC2OF_OFF         (0)
#define TIMERS_CC2OF_CLEAR       (TIMERS_CC2OF_OFF)
#define TIMERS_CC3OF_ON          (1)
#define TIMERS_CC3OF_OFF         (0)
#define TIMERS_CC3OF_CLEAR       (TIMERS_CC3OF_OFF)
#define TIMERS_CC4OF_ON          (1)
#define TIMERS_CC4OF_OFF         (0)
#define TIMERS_CC4OF_CLEAR       (TIMERS_CC4OF_OFF)

/***************** 4.6- TIMERs (ADVANCED)->EGR  ***************/


#define TIMERS_UG_TRIGGER         (1)
#define TIMERS_CC1G_TRIGGER       (1)
#define TIMERS_CC2G_TRIGGER       (1)
#define TIMERS_CC3G_TRIGGER       (1)
#define TIMERS_CC4G_TRIGGER       (1)
#define TIMERS_COMG_TRIGGER       (1)
#define TIMERS_TG_TRIGGER         (1)
#define TIMERS_BG_TRIGGER         (1)

/***************** 4.7- TIMERs (ADVANCED)->CCMR1, CCMR2  ***************/

#define TIMERS_CCxS_OUTPUT                     (0)
#define TIMERS_CCxS_INPUT_SAME_TIFxP           (1)
#define TIMERS_CCxS_INPUT_ALTERNATE_TIFxP      (2) // Alternate means if you are in ch1 then you use ti2
#define TIMERS_CCxS_INPUT_TRC                  (3)

#define TIMERS_OCxFE_ENABLE          (1)
#define TIMERS_OCxFE_DISABLE         (0)

#define TIMERS_OCxPE_ENABLE          (1)
#define TIMERS_OCxPE_DISABLE         (0)

#define TIMERS_OCxM_FROZEN                (0)
#define TIMERS_OCxM_OCxREF_HIGH           (1)
#define TIMERS_OCxM_OCxREF_LOW            (2)
#define TIMERS_OCxM_OCxREF_TOGGLE         (3)
#define TIMERS_OCxM_OCxREF_FORCE_LOW      (4)
#define TIMERS_OCxM_OCxREF_FORCE_HIGH     (5)
#define TIMERS_OCxM_OCxREF_PWM_MODE1      (6)
#define TIMERS_OCxM_OCxREF_PWM_MODE2      (7)
#define TIMERS_OCxM_OCxREF_PWM_NORMAL     (6)
#define TIMERS_OCxM_OCxREF_PWM_INVERTED   (7)

#define TIMERS_OCxCE_ETRF_NOT_AFFECT         (0)
#define TIMERS_OCxCE_ETRF_CLEAR              (1)


#define TIMERS_ICxPSC_DIV_1         (0)
#define TIMERS_ICxPSC_DIV_2         (1)
#define TIMERS_ICxPSC_DIV_4          (2)
#define TIMERS_ICxPSC_DIV_8          (3)

#define TIMERS_ICxF_NO_FILTER            (0)
#define TIMERS_ICxF_CK_INT_N2             (1)
#define TIMERS_ICxF_CK_INT_N4             (2)
#define TIMERS_ICxF_CK_INT_N8             (3)
#define TIMERS_ICxF_DTS_2_N6              (4)
#define TIMERS_ICxF_DTS_2_N8              (5)
#define TIMERS_ICxF_DTS_4_N6              (6)
#define TIMERS_ICxF_DTS_4_N8              (7)
#define TIMERS_ICxF_DTS_8_N6              (8)
#define TIMERS_ICxF_DTS_8_N8              (9)
#define TIMERS_ICxF_DTS_16_N5             (10)
#define TIMERS_ICxF_DTS_16_N6             (11)
#define TIMERS_ICxF_DTS_16_N8             (12)
#define TIMERS_ICxF_DTS_32_N5             (13)
#define TIMERS_ICxF_DTS_32_N6             (14)
#define TIMERS_ICxF_DTS_32_N8             (15)

/***************** 4.8- TIMERs (ADVANCED)->CCER  ***************/

#define TIMERS_CCxE_CAPTURE_DISABLED         (0)
#define TIMERS_CCxE_CAPTURE_ENABLED          (1)

#define TIMERS_CCxE_COMPARE_OCx_DISABLED             (0)
#define TIMERS_CCxE_COMPARE_OCx_ENABLED              (1)

#define TIMERS_CCxP_COMPARE_OCxREF_NON_INVERTED                 (0)
#define TIMERS_CCxP_COMPARE_OCxREF_INVERTED                     (1)
#define TIMERS_CCxP_CAPTURE_RISING_EDGE              (0)
#define TIMERS_CCxP_CAPTURE_FALLING_EDGE             (1)

#define TIMERS_CCxNE_CAPTURE_DISABLED         (0)
#define TIMERS_CCxNE_CAPTURE_ENABLED          (1)

#define TIMERS_CCxNE_COMPARE_OCxN_DISABLED             (0)
#define TIMERS_CCxNE_COMPARE_OCxN_ENABLED              (1)

#define TIMERS_CCxNP_COMPARE_OCxN_HIGH                 (0)
#define TIMERS_CCxNP_COMPARE_OCxN_LOW                  (1)
#define TIMERS_CCxNP_CAPTURE_RISING_EDGE              (0)
#define TIMERS_CCxNP_CAPTURE_FALLING_EDGE             (1)

/***************** 4.9- TIMERs (ADVANCED)->BDTR  ***************/

#define TIMERS_LOCK_OFF         (0)
#define TIMERS_LOCK_LEVEL1      (1)
#define TIMERS_LOCK_LEVEL2      (2)
#define TIMERS_LOCK_LEVEL3      (3)

//TODO :Timers Advanced BDTR

/***************** 4.7- TIMERs (ADVANCED)->CCMR1  ***************/
/***************** 4.7- TIMERs (ADVANCED)->CCMR1  ***************/


/***************************************************************/
/*		  (16) TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4		   */
/***************************************************************/

/*
 * 	TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4 Section Architecture Map
 *		1- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->Base_Definitions
 *		2- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->Registers_Pointers
 *		3- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->Struct_Definition
 *		4- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->Registers_Values_Definitions
 *			4.1- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->
 *			4.2- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->
 *			4.3- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->
 *			4.4- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->
 *			4.5- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->
 *			4.6- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->
 *
 *
 * */


/***************** 1- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->Base_Definition ******************/
#define TIMERS_GENERAL_PURPOSE_BASE       (PERIPHERAL_MEMORY_BASE + 0x0000)

#define TIMER2_BASE     (TIMERS_GENERAL_PURPOSE_BASE + 0x0000)
#define TIMER3_BASE     (TIMERS_GENERAL_PURPOSE_BASE + 0x0400)
#define TIMER4_BASE     (TIMERS_GENERAL_PURPOSE_BASE + 0x0800)

#define TIMER2_CR1_BASE     (TIMER2_BASE + 0x00)
#define TIMER2_CR2_BASE     (TIMER2_BASE + 0x04)
#define TIMER2_SMCR_BASE    (TIMER2_BASE + 0x08)
#define TIMER2_DIER_BASE    (TIMER2_BASE + 0x0C)
#define TIMER2_SR_BASE      (TIMER2_BASE + 0x10)
#define TIMER2_EGR_BASE     (TIMER2_BASE + 0x14)
#define TIMER2_CCMR1_BASE   (TIMER2_BASE + 0x18)
#define TIMER2_CCMR2_BASE   (TIMER2_BASE + 0x1C)
#define TIMER2_CCER_BASE    (TIMER2_BASE + 0x20)
#define TIMER2_CNT_BASE     (TIMER2_BASE + 0x24)
#define TIMER2_PSC_BASE     (TIMER2_BASE + 0x28)
#define TIMER2_ARR_BASE     (TIMER2_BASE + 0x2C)
#define TIMER2_CCR1_BASE    (TIMER2_BASE + 0x34)
#define TIMER2_CCR2_BASE    (TIMER2_BASE + 0x38)
#define TIMER2_CCR3_BASE    (TIMER2_BASE + 0x3C)
#define TIMER2_CCR4_BASE    (TIMER2_BASE + 0x40)
#define TIMER2_DCR_BASE     (TIMER2_BASE + 0x48)
#define TIMER2_DMAR_BASE    (TIMER2_BASE + 0x4C)

#define TIMER3_CR1_BASE     (TIMER3_BASE + 0x00)
#define TIMER3_CR2_BASE     (TIMER3_BASE + 0x04)
#define TIMER3_SMCR_BASE    (TIMER3_BASE + 0x08)
#define TIMER3_DIER_BASE    (TIMER3_BASE + 0x0C)
#define TIMER3_SR_BASE      (TIMER3_BASE + 0x10)
#define TIMER3_EGR_BASE     (TIMER3_BASE + 0x14)
#define TIMER3_CCMR1_BASE   (TIMER3_BASE + 0x18)
#define TIMER3_CCMR2_BASE   (TIMER3_BASE + 0x1C)
#define TIMER3_CCER_BASE    (TIMER3_BASE + 0x20)
#define TIMER3_CNT_BASE     (TIMER3_BASE + 0x24)
#define TIMER3_PSC_BASE     (TIMER3_BASE + 0x28)
#define TIMER3_ARR_BASE     (TIMER3_BASE + 0x2C)
#define TIMER3_CCR1_BASE    (TIMER3_BASE + 0x34)
#define TIMER3_CCR2_BASE    (TIMER3_BASE + 0x38)
#define TIMER3_CCR3_BASE    (TIMER3_BASE + 0x3C)
#define TIMER3_CCR4_BASE    (TIMER3_BASE + 0x40)
#define TIMER3_DCR_BASE     (TIMER3_BASE + 0x48)
#define TIMER3_DMAR_BASE    (TIMER3_BASE + 0x4C)


#define TIMER4_CR1_BASE     (TIMER4_BASE + 0x00)
#define TIMER4_CR2_BASE     (TIMER4_BASE + 0x04)
#define TIMER4_SMCR_BASE    (TIMER4_BASE + 0x08)
#define TIMER4_DIER_BASE    (TIMER4_BASE + 0x0C)
#define TIMER4_SR_BASE      (TIMER4_BASE + 0x10)
#define TIMER4_EGR_BASE     (TIMER4_BASE + 0x14)
#define TIMER4_CCMR1_BASE   (TIMER4_BASE + 0x18)
#define TIMER4_CCMR2_BASE   (TIMER4_BASE + 0x1C)
#define TIMER4_CCER_BASE    (TIMER4_BASE + 0x20)
#define TIMER4_CNT_BASE     (TIMER4_BASE + 0x24)
#define TIMER4_PSC_BASE     (TIMER4_BASE + 0x28)
#define TIMER4_ARR_BASE     (TIMER4_BASE + 0x2C)
#define TIMER4_CCR1_BASE    (TIMER4_BASE + 0x34)
#define TIMER4_CCR2_BASE    (TIMER4_BASE + 0x38)
#define TIMER4_CCR3_BASE    (TIMER4_BASE + 0x3C)
#define TIMER4_CCR4_BASE    (TIMER4_BASE + 0x40)
#define TIMER4_DCR_BASE     (TIMER4_BASE + 0x48)
#define TIMER4_DMAR_BASE    (TIMER4_BASE + 0x4C)

/***************** 2- TIMERs (GENERAL PURPOSE) _TIMER2,_TIMER3,_TIMER4->Registers_Pointers ***************/

#define TIMER2_CR1       (*((uint32_t) TIMER2_CR1_BASE))
#define TIMER2_CR2       (*((uint32_t) TIMER2_CR2_BASE))
#define TIMER2_SMCR       (*((uint32_t) TIMER2_SMCR_BASE))
#define TIMER2_DIER       (*((uint32_t) TIMER2_DIER_BASE))
#define TIMER2_SR       (*((uint32_t) TIMER2_SR_BASE))
#define TIMER2_EGR       (*((uint32_t) TIMER2_EGR_BASE))
#define TIMER2_CCMR1       (*((uint32_t) TIMER2_CCMR1_BASE))
#define TIMER2_CCMR2       (*((uint32_t) TIMER2_CCMR2_BASE))
#define TIMER2_CCER       (*((uint32_t) TIMER2_CCER_BASE))
#define TIMER2_CNT       (*((uint32_t) TIMER2_CNT_BASE))
#define TIMER2_PSC       (*((uint32_t) TIMER2_PSC_BASE))
#define TIMER2_ARR       (*((uint32_t) TIMER2_ARR_BASE))
#define TIMER2_CCR1       (*((uint32_t) TIMER2_CCR1_BASE))
#define TIMER2_CCR2       (*((uint32_t) TIMER2_CCR2_BASE))
#define TIMER2_CCR3       (*((uint32_t) TIMER2_CCR3_BASE))
#define TIMER2_CCR4       (*((uint32_t) TIMER2_CCR4_BASE))
#define TIMER2_DCR       (*((uint32_t) TIMER2_DCR_BASE))
#define TIMER2_DMAR       (*((uint32_t) TIMER2_DMAR_BASE))


#define TIMER3_CR1       (*((uint32_t) TIMER3_CR1_BASE))
#define TIMER3_CR2       (*((uint32_t) TIMER3_CR2_BASE))
#define TIMER3_SMCR      (*((uint32_t) TIMER3_SMCR_BASE))
#define TIMER3_DIER      (*((uint32_t) TIMER3_DIER_BASE))
#define TIMER3_SR        (*((uint32_t) TIMER3_SR_BASE))
#define TIMER3_EGR       (*((uint32_t) TIMER3_EGR_BASE))
#define TIMER3_CCMR1     (*((uint32_t) TIMER3_CCMR1_BASE))
#define TIMER3_CCMR2     (*((uint32_t) TIMER3_CCMR2_BASE))
#define TIMER3_CCER      (*((uint32_t) TIMER3_CCER_BASE))
#define TIMER3_CNT       (*((uint32_t) TIMER3_CNT_BASE))
#define TIMER3_PSC       (*((uint32_t) TIMER3_PSC_BASE))
#define TIMER3_ARR       (*((uint32_t) TIMER3_ARR_BASE))
#define TIMER3_CCR1      (*((uint32_t) TIMER3_CCR1_BASE))
#define TIMER3_CCR2      (*((uint32_t) TIMER3_CCR2_BASE))
#define TIMER3_CCR3      (*((uint32_t) TIMER3_CCR3_BASE))
#define TIMER3_CCR4      (*((uint32_t) TIMER3_CCR4_BASE))
#define TIMER3_DCR       (*((uint32_t) TIMER3_DCR_BASE))
#define TIMER3_DMAR      (*((uint32_t) TIMER3_DMAR_BASE))


#define TIMER4_CR1       (*((uint32_t) TIMER4_CR1_BASE))
#define TIMER4_CR2       (*((uint32_t) TIMER4_CR2_BASE))
#define TIMER4_SMCR       (*((uint32_t) TIMER4_SMCR_BASE))
#define TIMER4_DIER       (*((uint32_t) TIMER4_DIER_BASE))
#define TIMER4_SR       (*((uint32_t) TIMER4_SR_BASE))
#define TIMER4_EGR       (*((uint32_t) TIMER4_EGR_BASE))
#define TIMER4_CCMR1       (*((uint32_t) TIMER4_CCMR1_BASE))
#define TIMER4_CCMR2       (*((uint32_t) TIMER4_CCMR2_BASE))
#define TIMER4_CCER       (*((uint32_t) TIMER4_CCER_BASE))
#define TIMER4_CNT       (*((uint32_t) TIMER4_CNT_BASE))
#define TIMER4_PSC       (*((uint32_t) TIMER4_PSC_BASE))
#define TIMER4_ARR       (*((uint32_t) TIMER4_ARR_BASE))
#define TIMER4_CCR1       (*((uint32_t) TIMER4_CCR1_BASE))
#define TIMER4_CCR2       (*((uint32_t) TIMER4_CCR2_BASE))
#define TIMER4_CCR3       (*((uint32_t) TIMER4_CCR3_BASE))
#define TIMER4_CCR4       (*((uint32_t) TIMER4_CCR4_BASE))
#define TIMER4_DCR       (*((uint32_t) TIMER4_DCR_BASE))
#define TIMER4_DMAR       (*((uint32_t) TIMER4_DMAR_BASE))

/***************** 3- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->Struct_Definition ****************/


typedef volatile struct {
    union {
        struct {
            uint32_t CEN: 1;
            uint32_t UDIS: 1;
            uint32_t URS: 1;
            uint32_t OPM: 1;
            uint32_t DIR: 1;
            uint32_t CMS: 2;
            uint32_t APRE: 1;
            uint32_t CKD: 2;
        };
        uint32_t REG;
    } CR1;


    union {
        struct {
            const uint32_t      : 3;
            uint32_t CCDS: 1;
            uint32_t MMS: 3;
            uint32_t TI1S: 1;
        };
        uint32_t REG;
    } CR2;

    union {
        struct {
            uint32_t SMS: 3;
            const uint32_t      : 1;
            uint32_t TS: 3;
            uint32_t MSM: 1;
            uint32_t ETF: 4;
            uint32_t ETPS: 2;
            uint32_t ECE: 1;
            uint32_t ETP: 1;
        };
        uint32_t REG;
    } SMCR;

    union {
        struct {
            uint32_t UIE: 1;
            uint32_t CC1IE: 1;
            uint32_t CC2IE: 1;
            uint32_t CC3IE: 1;
            uint32_t CC4IE: 1;
            const uint32_t      : 1;
            uint32_t TIE: 1;
            const uint32_t      : 1;
            uint32_t UDE: 1;
            uint32_t CC1DE: 1;
            uint32_t CC2DE: 1;
            uint32_t CC3DE: 1;
            uint32_t CC4DE: 1;
            const uint32_t      : 1;
            uint32_t TDE: 1;

        };
        uint32_t REG;
    } DIER;

    union {
        struct {
            uint32_t UIF: 1;
            uint32_t CC1IF: 1;
            uint32_t CC2IF: 1;
            uint32_t CC3IF: 1;
            uint32_t CC4IF: 1;
            const uint32_t      : 1;
            uint32_t TIF: 1;
            const uint32_t      : 2;
            uint32_t CC1OF: 1;
            uint32_t CC2OF: 1;
            uint32_t CC3OF: 1;
            uint32_t CC4OF: 1;
        };
        uint32_t REG;
    } SR;

    union {
        struct {
            uint32_t UG: 1;
            uint32_t CC1G: 1;
            uint32_t CC2G: 1;
            uint32_t CC3G: 1;
            uint32_t CC4G: 1;
            const uint32_t      : 1;
            uint32_t TG: 1;
        };
        uint32_t REG;
    } EGR;

    union {
        struct {
            uint8_t CCS: 2;
            uint8_t OCFE: 1;
            uint8_t OCPE: 1;
            uint8_t OCM: 3;
            uint8_t OCCE: 1;
        } CCMR_OutputCompareMode[4];
        struct {
            uint8_t CCS: 2;
            uint8_t ICPSC: 2;
            uint8_t ICF: 4;

        } CCMR_InputCaptureMode[4];


        struct {
            union {
                struct {
                    const uint32_t      : 2;
                    uint32_t OC1FE: 1;
                    uint32_t OC1PE: 1;
                    uint32_t OC1M: 3;
                    uint32_t OC1CE: 1;

                    const uint32_t      : 2;
                    uint32_t OC2FE: 1;
                    uint32_t OC2PE: 1;
                    uint32_t OC2M: 3;
                    uint32_t OC2CE: 1;
                };
                struct {
                    uint32_t CC1S: 2;
                    uint32_t IC1PSC: 2;
                    uint32_t IC1F: 4;

                    uint32_t CC2S: 2;
                    uint32_t IC2PSC: 2;
                    uint32_t IC2F: 4;
                };
                uint32_t REG;
            } CCMR1;


            union {
                struct {
                    const uint32_t      : 2;
                    uint32_t OC3FE: 1;
                    uint32_t OC3PE: 1;
                    uint32_t OC3M: 3;
                    uint32_t OC3CE: 1;

                    const uint32_t      : 2;
                    uint32_t OC4FE: 1;
                    uint32_t OC4PE: 1;
                    uint32_t OC4M: 3;
                    uint32_t OC4CE: 1;
                };
                struct {
                    uint32_t CC3S: 2;
                    uint32_t IC3PSC: 2;
                    uint32_t IC3F: 4;

                    uint32_t CC4S: 2;
                    uint32_t IC4PSC: 2;
                    uint32_t IC4F: 4;
                };
                uint32_t REG;
            } CCMR2;
        };
    };

    union {
        struct {
            uint32_t CC1E: 1;
            uint32_t CC1P: 1;
            const uint32_t      : 2;
            uint32_t CC2E: 1;
            uint32_t CC2P: 1;
            const uint32_t      : 2;
            uint32_t CC3E: 1;
            uint32_t CC3P: 1;
            const uint32_t      : 2;
            uint32_t CC4E: 1;
            uint32_t CC4P: 1;
            const uint32_t      : 2;
        };
        uint32_t REG;
    } CCER;

    union {
        struct {
            uint32_t CNT: 16;
        };
        uint32_t REG;
    } CNT;

    union {
        struct {
            uint32_t PSC: 16;
        };
        uint32_t REG;
    } PSC;

    union {
        struct {
            uint32_t ARR: 16;
        };
        uint32_t REG;
    } ARR;
    const uint32_t              : 32;
    union {
        struct {
            uint32_t CC: 16;
        };
        uint32_t REG;
    } CCR1;

    union {
        struct {
            uint32_t CC: 16;
        };
        uint32_t REG;
    } CCR2;

    union {
        struct {
            uint32_t CC: 16;
        };
        uint32_t REG;
    } CCR3;

    union {
        struct {
            uint32_t CC: 16;
        };
        uint32_t REG;
    } CCR4;

    const uint32_t              : 32;

    union {
        struct {
            uint32_t DBA: 5;
            const uint32_t      : 3;
            uint32_t DBL: 5;
            const uint32_t      : 3;
        };
        uint32_t REG;
    } DCR;

    union {
        struct {
            uint32_t DMAB: 16;
        };
        uint32_t REG;
    } DMAR;

} TIMERS_GENERAL_PURPOSE_Unit_t;

typedef volatile union {

    struct {
        TIMERS_GENERAL_PURPOSE_Unit_t Timer2;
        const uint32_t RESERVED[20];
        TIMERS_GENERAL_PURPOSE_Unit_t Timer3;
        const uint32_t RESERVED[20];
        TIMERS_GENERAL_PURPOSE_Unit_t Timer4;
    };

    struct {
        TIMERS_GENERAL_PURPOSE_Unit_t Timer;
        const uint32_t RESERVED[20];
    } Timers[3];

} TIMER_GENERAL_PURPOSE_t;

#define TIMERS_GP       ((TIMER_GENERAL_PURPOSE_t *)TIMERS_GENERAL_PURPOSE_BASE)

#define pTIMER2      ((TIMERS_GENERAL_PURPOSE_Unit_t *)TIMER2_BASE)
#define pTIMER3      ((TIMERS_GENERAL_PURPOSE_Unit_t *)TIMER3_BASE)
#define pTIMER4      ((TIMERS_GENERAL_PURPOSE_Unit_t *)TIMER4_BASE)

/***************** 4- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->Registers_Values_Definitions *****/
/***************** 4.1- TIMERs (GENERAL PURPOSE) TIM2,TIM3,TIM4->CR1  ***************/



//TODO: DMA control REG in GENERAL PURPOSE Timers

/***************************************************************/
/*		    	(17) Timers (Basic) TIM6,TIM7           	   */
/***************************************************************/

/*
 * 	Timers (Basic) TIM6,TIM7 Section Architecture Map
 *		1- Timers (Basic) TIM6,TIM7->Base_Definitions
 *		2- Timers (Basic) TIM6,TIM7->Registers_Pointers
 *		3- Timers (Basic) TIM6,TIM7->Struct_Definition
 *		4- Timers (Basic) TIM6,TIM7->Registers_Values_Definitions
 *			4.1- Timers (Basic) TIM6,TIM7->CR1
 *			4.2- Timers (Basic) TIM6,TIM7->CR2
 *			4.3- Timers (Basic) TIM6,TIM7->DIER
 *			4.4- Timers (Basic) TIM6,TIM7->SR
 *			4.5- Timers (Basic) TIM6,TIM7->EGR
 *
 *
 * */


/***************** 1- Timers (Basic) TIM6,TIM7->Base_Definition ******************/

#define TIMERS_BASIC_BASE        (PERIPHERAL_MEMORY_BASE + 0x1000)

#define TIM6_BASE           (TIMERS_BASIC_BASE + 0x000)
#define TIM6_CR1_BASE       (TIM6_BASE + 0x00)
#define TIM6_CR2_BASE       (TIM6_BASE + 0x04)
#define TIM6_DIER_BASE      (TIM6_BASE + 0x0C)
#define TIM6_SR_BASE        (TIM6_BASE + 0x10)
#define TIM6_EGR_BASE       (TIM6_BASE + 0x14)
#define TIM6_CNT_BASE       (TIM6_BASE + 0x24)
#define TIM6_PSC_BASE       (TIM6_BASE + 0x28)
#define TIM6_ARR_BASE       (TIM6_BASE + 0x2C)


#define TIM7_BASE           (TIMERS_BASIC_BASE + 0x400)
#define TIM7_CR1_BASE       (TIM7_BASE + 0x00)
#define TIM7_CR2_BASE       (TIM7_BASE + 0x04)
#define TIM7_DIER_BASE      (TIM7_BASE + 0x0C)
#define TIM7_SR_BASE        (TIM7_BASE + 0x10)
#define TIM7_EGR_BASE       (TIM7_BASE + 0x14)
#define TIM7_CNT_BASE       (TIM7_BASE + 0x24)
#define TIM7_PSC_BASE       (TIM7_BASE + 0x28)
#define TIM7_ARR_BASE       (TIM7_BASE + 0x2C)

/***************** 2- Timers (Basic) TIM6,TIM7->Registers_Pointers ***************/

#define TIM6_CR1        (*((uint32_t *)TIM6_CR1_BASE))
#define TIM6_CR2        (*((uint32_t *)TIM6_CR2_BASE))
#define TIM6_DIER       (*((uint32_t *)TIM6_DIER_BASE))
#define TIM6_SR         (*((uint32_t *)TIM6_SR_BASE))
#define TIM6_EGR        (*((uint32_t *)TIM6_EGR_BASE))
#define TIM6_CNT        (*((uint32_t *)TIM6_CNT_BASE))
#define TIM6_PSC        (*((uint32_t *)TIM6_PSC_BASE))
#define TIM6_ARR        (*((uint32_t *)TIM6_ARR_BASE))


#define TIM7_CR1        (*((uint32_t *)TIM7_CR1_BASE))
#define TIM7_CR2        (*((uint32_t *)TIM7_CR2_BASE))
#define TIM7_DIER       (*((uint32_t *)TIM7_DIER_BASE))
#define TIM7_SR         (*((uint32_t *)TIM7_SR_BASE))
#define TIM7_EGR        (*((uint32_t *)TIM7_EGR_BASE))
#define TIM7_CNT        (*((uint32_t *)TIM7_CNT_BASE))
#define TIM7_PSC        (*((uint32_t *)TIM7_PSC_BASE))
#define TIM7_ARR        (*((uint32_t *)TIM7_ARR_BASE))


/***************** 3- Timers (Basic) TIM6,TIM7->Struct_Definition ****************/

typedef volatile struct {

    union {
        struct {
            uint32_t CEN: 1;
            uint32_t UDIS: 1;
            uint32_t URS: 1;
            uint32_t OPM: 1;
            const uint32_t      : 3;
            uint32_t APRE: 1;

        };
        uint32_t REG;
    } CR1;

    union {
        struct {
            const uint32_t      : 4;
            uint32_t MMS: 3;
        };
        uint32_t REG;
    } CR2;

    const uint32_t          : 32;

    union {
        struct {
            uint32_t UIE: 1;
            const uint32_t      : 7;
            uint32_t UDE: 1;
        };
        uint32_t REG;
    } DIER;

    union {
        struct {
            uint32_t UIF: 1;
        };
        uint32_t REG;
    } SR;

    union {
        struct {
            uint32_t UG: 1;
        };
        uint32_t REG;
    } EGR;

    const uint32_t RESERVED[3];

    union {
        struct {
            uint16_t CNT;
        };
        uint32_t REG;
    } CNT;

    union {
        struct {
            uint16_t PSC;
        };
        uint32_t REG;
    } PSC;

    union {
        struct {
            uint16_t value;
        };
        uint32_t REG;
    } ARR;


} TIM_Basic_Unit_t;

typedef union {
    struct {
        TIM_Basic_Unit_t timer;
    } Timers[2];
    struct {
        TIM_Basic_Unit_t TIM6;
        TIM_Basic_Unit_t TIM7;
    };
} TIM_Basic_t;

#define TIMERS_BASIC        ((TIM_Basic_t *)TIMERS_BASIC_BASE)

#define TIMERS_TIM6                ((TIM_Basic_Unit_t *)TIM6_BASE)
#define TIMERS_TIM7                ((TIM_Basic_Unit_t *)TIM7_BASE)

/***************** 4- Timers (Basic) TIM6,TIM7->Registers_Values_Definitions *****/
/***************** 4.1- Timers (Basic) TIM6,TIM7->CR1  ***************/
#define TIMERS_BASIC_CEN_ENABLE        (1)
#define TIMERS_BASIC_CEN_DISABLE       (0)

#define TIMERS_BASIC_UDIS_DISABLE_UPDATES       (1)
#define TIMERS_BASIC_UDIS_ENABLE_UPDATES      (0)

#define TIMERS_BASIC_URS_ALL       (1)
#define TIMERS_BASIC_URS_ONLY_COUNTER      (0)

#define TIMERS_BASIC_OPM_ENABLE       (1)
#define TIMERS_BASIC_OPM_DISABLE      (0)

#define TIMERS_BASIC_ARPE_BUFFER_ENABLE       (1)
#define TIMERS_BASIC_ARPE_BUFFER_DISABLE      (0)

#define TIMERS_BASIC_CEN_POS      (0)
#define TIMERS_BASIC_UDIS_POS      (1)
#define TIMERS_BASIC_URS_POS      (2)
#define TIMERS_BASIC_OPM_POS      (3)
#define TIMERS_BASIC_ARPE_POS      (7)

#define TIMERS_BASIC_CR1_CEN_ENABLE        (TIMERS_BASIC_CEN_ENABLE<<TIMERS_BASIC_CEN_POS)
#define TIMERS_BASIC_CR1_CEN_DISABLE       (TIMERS_BASIC_CEN_DISABLE<<TIMERS_BASIC_CEN_POS)

#define TIMERS_BASIC_CR1_UDIS_ENABLE        (TIMERS_BASIC_UDIS_DISABLE_UPDATES<<TIMERS_BASIC_UDIS_POS)
#define TIMERS_BASIC_CR1_UDIS_DISABLE       (TIMERS_BASIC_UDIS_ENABLE_UPDATES<<TIMERS_BASIC_UDIS_POS)

#define TIMERS_BASIC_CR1_URS_ENABLE        (TIMERS_BASIC_URS_ALL<<TIMERS_BASIC_URS_POS)
#define TIMERS_BASIC_CR1_URS_DISABLE       (TIMERS_BASIC_URS_ONLY_COUNTER<<TIMERS_BASIC_URS_POS)

#define TIMERS_BASIC_CR1_OPM_ENABLE        (TIMERS_BASIC_OPM_ENABLE<<TIMERS_BASIC_OPM_POS)
#define TIMERS_BASIC_CR1_OPM_DISABLE       (TIMERS_BASIC_OPM_DISABLE<<TIMERS_BASIC_OPM_POS)

#define TIMERS_BASIC_CR1_ARPE_ENABLE        (TIMERS_BASIC_ARPE_BUFFER_ENABLE<<TIMERS_BASIC_ARPE_POS)
#define TIMERS_BASIC_CR1_ARPE_DISABLE       (TIMERS_BASIC_ARPE_BUFFER_DISABLE<<TIMERS_BASIC_ARPE_POS)

/***************** 4.2- Timers (Basic) TIM6,TIM7->CR2  ***************/

#define TIMERS_BASIC_MMS_RESET           (0)
#define TIMERS_BASIC_MMS_ENABLE          (1)
#define TIMERS_BASIC_MMS_UPDATE          (2)

#define TIMERS_BASIC_MMS_POS        (4)

#define TIMERS_BASIC_CR2_MMS_RESET   (TIMERS_BASIC_MMS_RESET<<TIMERS_BASIC_MMS_POS)
#define TIMERS_BASIC_CR2_MMS_ENABLE  (TIMERS_BASIC_MMS_RESET<<TIMERS_BASIC_MMS_POS)
#define TIMERS_BASIC_CR2_MMS_UPDATE  (TIMERS_BASIC_MMS_RESET<<TIMERS_BASIC_MMS_POS)

/***************** 4.3- Timers (Basic) TIM6,TIM7->DIER  ***************/
//(TIMERS_BASIC_$b$_ENABLE<<TIMERS_BASIC_$b$_POS)

#define TIMERS_BASIC_UIE_ENABLE        (1)
#define TIMERS_BASIC_UIE_DISABLE       (0)

#define TIMERS_BASIC_UDE_ENABLE        (1)
#define TIMERS_BASIC_UDE_DISABLE       (0)

#define TIMERS_BASIC_UIE_POS        (0)
#define TIMERS_BASIC_UDE_POS        (8)

#define TIMERS_BASIC_CR2_UIE_ENABLE        (TIMERS_BASIC_UIE_ENABLE<<TIMERS_BASIC_UIE_POS)
#define TIMERS_BASIC_CR2_UIE_DISABLE       (TIMERS_BASIC_UIE_DISABLE<<TIMERS_BASIC_UIE_POS)

#define TIMERS_BASIC_CR2_UDE_ENABLE        (TIMERS_BASIC_UDE_ENABLE<<TIMERS_BASIC_UDE_POS)
#define TIMERS_BASIC_CR2_UDE_DISABLE       (TIMERS_BASIC_UDE_DISABLE<<TIMERS_BASIC_UDE_POS)

/***************** 4.4- Timers (Basic) TIM6,TIM7->SR  ***************/
#define TIMERS_BASIC_UIF_ON                 (1)
#define TIMERS_BASIC_UIF_OFF                (0)

#define TIMERS_BASIC_UIF_POS             (0)

#define TIMERS_BASIC_SR_UIF_ON           (TIMERS_BASIC_UIF_ON<<TIMERS_BASIC_UIF_POS)
#define TIMERS_BASIC_SR_UIF_OFF          (TIMERS_BASIC_UIF_OFF<<TIMERS_BASIC_UIF_POS)
/***************** 4.5- Timers (Basic) TIM6,TIM7->EGR  ***************/
#define TIMERS_BASIC_UG_ON                 (1)
#define TIMERS_BASIC_UG_OFF                (0)

#define TIMERS_BASIC_UG_POS             (0)

#define TIMERS_BASIC_EGR_UG_ON           (TIMERS_BASIC_UG_ON<<TIMERS_BASIC_UG_POS)
#define TIMERS_BASIC_EGR_UG_OFF          (TIMERS_BASIC_UG_OFF<<TIMERS_BASIC_UG_POS)


/***************************************************************/
/*					    	(20) I2Cs						   */
/***************************************************************/

/*
 * 	I2Cs Section Architecture Map
 *		1- I2Cs->Base_Definitions
 *		2- I2Cs->Registers_Pointers
 *		3- I2Cs->Struct_Definition
 *		4- I2Cs->Registers_Values_Definitions
 *			4.1- I2Cs->
 *			4.2- I2Cs->
 *			4.3- I2Cs->
 *			4.4- I2Cs->
 *			4.5- I2Cs->
 *			4.6- I2Cs->
 *
 *
 * */


/***************** 1- I2Cs->Base_Definition ******************/
#define pI2C_BASE            (PERIPHERAL_MEMORY_BASE + 0x5400U)

#define pI2C1_BASE           (I2C_BASE + 0x0000)
#define pI2C2_BASE           (I2C_BASE + 0x5800)


#define pI2C1_CR1_BASE        (pI2C1_BASE + 0x00)
#define pI2C1_CR2_BASE        (pI2C1_BASE + 0x04)
#define pI2C1_OAR1_BASE       (pI2C1_BASE + 0x08)
#define pI2C1_OAR2_BASE       (pI2C1_BASE + 0x0C)
#define pI2C1_DR_BASE         (pI2C1_BASE + 0x10)
#define pI2C1_SR1_BASE        (pI2C1_BASE + 0x14)
#define pI2C1_SR2_BASE        (pI2C1_BASE + 0x18)
#define pI2C1_CCR_BASE        (pI2C1_BASE + 0x1C)
#define pI2C1_TRISE_BASE      (pI2C1_BASE + 0x20)


#define pI2C2_CR1_BASE        (pI2C2_BASE + 0x00)
#define pI2C2_CR2_BASE        (pI2C2_BASE + 0x04)
#define pI2C2_OAR1_BASE       (pI2C2_BASE + 0x08)
#define pI2C2_OAR2_BASE       (pI2C2_BASE + 0x0C)
#define pI2C2_DR_BASE         (pI2C2_BASE + 0x10)
#define pI2C2_SR1_BASE        (pI2C2_BASE + 0x14)
#define pI2C2_SR2_BASE        (pI2C2_BASE + 0x18)
#define pI2C2_CCR_BASE        (pI2C2_BASE + 0x1C)
#define pI2C2_TRISE_BASE      (pI2C2_BASE + 0x20)

/***************** 2- I2Cs->Registers_Pointers ***************/

#define pI2C1_CR1       (*((uint32_t *)pI2C1_CR1_BASE))
#define pI2C1_CR2       (*((uint32_t *)pI2C1_CR2_BASE))
#define pI2C1_OAR1      (*((uint32_t *)pI2C1_OAR1_BASE))
#define pI2C1_OAR2      (*((uint32_t *)pI2C1_OAR2_BASE))
#define pI2C1_DR        (*((uint32_t *)pI2C1_DR_BASE))
#define pI2C1_SR1       (*((uint32_t *)pI2C1_SR1_BASE))
#define pI2C1_SR2       (*((uint32_t *)pI2C1_SR2_BASE))
#define pI2C1_CCR       (*((uint32_t *)pI2C1_CCR_BASE))
#define pI2C1_TRISE     (*((uint32_t *)pI2C1_TRISE_BASE))


#define pI2C2_CR1       (*((uint32_t *)pI2C2_CR1_BASE))
#define pI2C2_CR2       (*((uint32_t *)pI2C2_CR2_BASE))
#define pI2C2_OAR1      (*((uint32_t *)pI2C2_OAR1_BASE))
#define pI2C2_OAR2      (*((uint32_t *)pI2C2_OAR2_BASE))
#define pI2C2_DR        (*((uint32_t *)pI2C2_DR_BASE))
#define pI2C2_SR1       (*((uint32_t *)pI2C2_SR1_BASE))
#define pI2C2_SR2       (*((uint32_t *)pI2C2_SR2_BASE))
#define pI2C2_CCR       (*((uint32_t *)pI2C2_CCR_BASE))
#define pI2C2_TRISE     (*((uint32_t *)pI2C2_TRISE_BASE))

/***************** 3- I2Cs->Struct_Definition ****************/

typedef volatile struct {

    union {
        struct {
            uint32_t PE: 1;
            uint32_t SMBUS: 1;
            const uint32_t                  : 1;
            uint32_t SMBUSType: 1;
            uint32_t ENARP: 1;
            uint32_t ENPEC: 1;
            uint32_t ENGC: 1;
            uint32_t NOSTRETCH: 1;
            uint32_t START: 1;
            uint32_t STOP: 1;
            uint32_t ACK: 1;
            uint32_t POS: 1;
            uint32_t PEC: 1;
            uint32_t ALERT: 1;
            const uint32_t                  : 1;
            uint32_t SWRST: 1;
            const uint32_t                  : 0;
        };
        uint32_t REG;
    } CR1;

    union {
        struct {
            uint32_t FREQ: 6;
            const uint32_t                  : 2;
            uint32_t ITERREN: 1;
            uint32_t ITEVTEN: 1;
            uint32_t ITBUFEN: 1;
            uint32_t DMAEN: 1;
            uint32_t LAST: 1;
            const uint32_t                  : 0;
        };
        uint32_t REG;
    } CR2;

    union {
        struct {
            uint32_t ADD: 10;
        };
        struct {
            uint32_t ADD0: 1;
            uint32_t ADD_7_1: 7;
            uint32_t ADD_9_8: 2;
            const uint32_t              : 5;
            uint32_t ADDMODE: 1;
            const uint32_t              : 0;
        };
        uint32_t REG;
    } OAR1;


    union {
        struct {
            uint32_t ENDUAL: 1;
            uint32_t ADD: 7;
            const uint32_t              : 0;
        };
        uint32_t REG;
    } OAR2;


    union {
        struct {
            uint32_t D: 8;
        };
        uint32_t REG;
    } DR;

    union {
        struct {
            const uint32_t SB: 1;
            const uint32_t ADDR: 1;
            const uint32_t BTF: 1;
            const uint32_t ADD10: 1;
            const uint32_t STOPF: 1;
            const uint32_t              : 1;
            const uint32_t RxNE: 1;
            const uint32_t TxE: 1;
            uint32_t BERR: 1;
            uint32_t ARLO: 1;
            uint32_t AF: 1;
            uint32_t OVR: 1;
            uint32_t PECERR: 1;
            const uint32_t              : 1;
            uint32_t TIMEOUT: 1;
            uint32_t SMBALERT: 1;
            const uint32_t              : 0;

        };
        uint32_t REG;
    } SR1;

    union {
        struct {
            const uint32_t MSL: 1;
            const uint32_t BUSY: 1;
            const uint32_t TRA: 1;
            const uint32_t              : 1;
            const uint32_t GENCAL: 1;
            const uint32_t SMBDEFAULT: 1;
            const uint32_t SMBHOST: 1;
            const uint32_t DUALF: 1;
            const uint32_t PEC: 8;
            const uint32_t              : 0;
        };
        uint32_t REG;
    } SR2;


    union {
        struct {
            uint32_t CCR: 12;
            const uint32_t              : 1;
            uint32_t DUTY: 2;
            uint32_t F_S: 1;
            const uint32_t              : 0;
        };
        uint32_t REG;
    } CCR;


    union {
        struct {
            uint32_t TRISE: 6;
            const uint32_t              : 0;
        };
        uint32_t REG;
    } TRISE;
} pI2C_Unit_t;

typedef volatile union {
    struct {
        pI2C_Unit_t I2C1;
        const uint32_t RESERVED[247];
        pI2C_Unit_t I2C2;
    };
    struct {
        struct {
            pI2C_Unit_t I2C;
            const uint32_t RESERVED[247];
        } I2Cs[2];

    } All;
} pI2C_t;

#define pI2C        ((pI2C_t *)pI2C_BASE)
#define pI2C1        ((pI2C_Unit_t _t *)pI2C1_BASE)
#define pI2C2        ((pI2C_Unit_t _t *)pI2C2_BASE)


/***************** 4- I2Cs->Registers_Values_Definitions *****/
/***************** 4.1- I2Cs->CR1  ***************/

#define pI2C_PE_ENABLE          (1)
#define pI2C_PE_DISABLE         (0)

#define pI2C_SMBUS_I2C_MODE     (0)
#define pI2C_SMBUS_SMBus_MODE   (1)

#define pI2C_SMBTYPE_DEVICE     (0)
#define pI2C_SMBTYPE_HOST       (1)

#define pI2C_ENARP_DISABLE      (0)
#define pI2C_ENARP_ENABLE       (1)

#define pI2C_ENPEC_DISABLE      (0)
#define pI2C_ENPEC_ENABLE       (1)

#define pI2C_ENGC_ENABLE         (1)
#define pI2C_ENGC_DISABLE        (0)

#define pI2C_NOSTRETCH_ENABLE_STRETCHING        (0)
#define pI2C_NOSTRETCH_DISABLE_STRETCHING       (1)

#define pI2C_START_SEND_START         (1)
#define pI2C_START_NOTHING            (0)

#define pI2C_STOP_SEND_STOP         (1)
#define pI2C_STOP_NOTHING           (0)

#define pI2C_ACK_ACK_ENABLED           (1)
#define pI2C_ACK_ACK_DISABLED          (0)


#define pI2C_POS_SET    (1)
#define pI2C_POS_CLEAR  (0)

#define pI2C_PEC_ENABLE         (1)
#define pI2C_PEC_DISABLE        (0)

#define pI2C_ALERT_SET_PIN_LOW         (1)
#define pI2C_ALERT_SET_PIN_HIGH        (0)

#define pI2C_SWRST_RESET_MODE         (1)

/***************** 4.2- I2Cs->CR2  ***************/


#define pI2C_FREQ_2MHZ      (2)
#define pI2C_FREQ_3MHZ      (3)
#define pI2C_FREQ_4MHZ      (4)
#define pI2C_FREQ_5MHZ      (5)
#define pI2C_FREQ_6MHZ      (6)
#define pI2C_FREQ_7MHZ      (7)
#define pI2C_FREQ_8MHZ      (8)
#define pI2C_FREQ_9MHZ      (9)
#define pI2C_FREQ_10MHZ      (10)
#define pI2C_FREQ_11MHZ      (11)
#define pI2C_FREQ_12MHZ      (12)
#define pI2C_FREQ_13MHZ      (13)
#define pI2C_FREQ_14MHZ      (14)
#define pI2C_FREQ_15MHZ      (15)
#define pI2C_FREQ_16MHZ      (16)
#define pI2C_FREQ_17MHZ      (17)
#define pI2C_FREQ_18MHZ      (18)
#define pI2C_FREQ_19MHZ      (19)
#define pI2C_FREQ_20MHZ      (20)
#define pI2C_FREQ_21MHZ      (21)
#define pI2C_FREQ_22MHZ      (22)
#define pI2C_FREQ_23MHZ      (23)
#define pI2C_FREQ_24MHZ      (24)
#define pI2C_FREQ_25MHZ      (25)
#define pI2C_FREQ_26MHZ      (26)
#define pI2C_FREQ_27MHZ      (27)
#define pI2C_FREQ_28MHZ      (28)
#define pI2C_FREQ_29MHZ      (29)
#define pI2C_FREQ_30MHZ      (30)
#define pI2C_FREQ_31MHZ      (31)
#define pI2C_FREQ_32MHZ      (32)
#define pI2C_FREQ_33MHZ      (33)
#define pI2C_FREQ_34MHZ      (34)
#define pI2C_FREQ_35MHZ      (35)
#define pI2C_FREQ_36MHZ      (36)
#define pI2C_FREQ_37MHZ      (37)
#define pI2C_FREQ_38MHZ      (38)
#define pI2C_FREQ_39MHZ      (39)
#define pI2C_FREQ_40MHZ      (40)
#define pI2C_FREQ_41MHZ      (41)
#define pI2C_FREQ_42MHZ      (42)
#define pI2C_FREQ_43MHZ      (43)
#define pI2C_FREQ_44MHZ      (44)
#define pI2C_FREQ_45MHZ      (45)
#define pI2C_FREQ_46MHZ      (46)
#define pI2C_FREQ_47MHZ      (47)
#define pI2C_FREQ_48MHZ      (48)
#define pI2C_FREQ_49MHZ      (49)
#define pI2C_FREQ_50MHZ      (50)

#define pI2C_FREQ_MIN_SM       (_I2C_FREQ_2MHZ)
#define pI2C_FREQ_MIN_FM       (_I2C_FREQ_4MHZ)
#define pI2C_FREQ_MAX          (_I2C_FREQ_50MHZ)

#define pI2C_ITERREN_INTERRUPT_ENABLE         (1)
#define pI2C_ITERREN_INTERRUPT_DISABLE        (0)

#define pI2C_ITEVTEN_INTERRUPT_ENABLE         (1)
#define pI2C_ITEVTEN_INTERRUPT_DISABLE        (0)


#define pI2C_ITBUFEN_INTERRUPT_ENABLE         (1)
#define pI2C_ITBUFEN_INTERRUPT_DISABLE        (0)

#define pI2C_DMAEN_ENABLE         (1)
#define pI2C_DMAEN_DISABLE        (0)

#define pI2C_LAST_DMATx_ENABLE         (1)
#define pI2C_LAST_DMATx_DISABLE        (0)



/***************** 4.3- I2Cs->OAR1  ***************/

#define pI2C_ADDMODE_10BIT         (1)
#define pI2C_ADDMODE_7BIT          (0)

/***************** 4.4- I2Cs->OAR2  ***************/

#define pI2C_ENDUAL_ENABLE         (1)
#define pI2C_ENDUAL_DISABLE        (0)

/***************** 4.5- I2Cs->SR1  ***************/

#define pI2C_SB_START_GENERATED         (1)
#define pI2C_SB_START_NOT_GENERATED     (0)

#define pI2C_ADDR_ADDRESS_MISMATCH              (0)
#define pI2C_ADDR_ADDRESS_MATCHED               (1)
#define pI2C_ADDR_ADDRESS_NOT_TRANSMITTED       (0)
#define pI2C_ADDR_ADDRESS_TRANSMITTED           (1)

#define pI2C_BTF_DATA_TRANSFER_COMPLETE        (1)
#define pI2C_BTF_DATA_TRANSFER_NOT_COMPLETE    (0)

#define pI2C_ADD10_SENT_FIRST_BYTE        (1)

#define pI2C_STOPF_STOP_DETECTED        (1)

#define pI2C_RXNE_DATA_REG_NOT_EMPTY        (1)

#define pI2C_TxE_DATA_REG_EMPTY        (1)

#define pI2C_BERR_BUS_ERROR        (1)

#define pI2C_ARLO_ARBITRATION_LOST        (1)

#define pI2C_AF_ACK_FAILURE        (1)

#define pI2C_OVR_OVERRUN_DETECTED        (1)


#define pI2C_PECERR_PEC_ERROR_DETECTED        (1)

#define pI2C_TIMEOUT_TIMOUT_DETECTED        (1)

#define pI2C_SMBALERT_SMBUS_ALERT_DETECTED        (1)




/***************** 4.6- I2Cs->SR2  ***************/
#define pI2C_MSL_MASTER_MODE        (1)
#define pI2C_MSL_SLAVE_MODE        (0)

#define pI2C_BUSY_BUSY_BUS        (1)

#define pI2C_TRA_DATA_TRANSMITTED        (1)
#define pI2C_TRA_DATA_RECEIVED        (0)

#define pI2C_GENCALL_GENERAL_CALL_DETECTED        (1)

#define pI2C_SMBDEFAULT_SMBUS_DEFAULT_ADDRESS_DETECTED        (1)

#define pI2C_SMBHOST_SMBUS_HOST_ADDRESS_DETECTED        (1)

#define pI2C_DUALF_ADDRESS_MATCH_OAR1        (0)
#define pI2C_DUALF_ADDRESS_MATCH_OAR2        (1)


/***************** 4.7- I2Cs->CCR  ***************/


//  CCR
//  Controls the SCL clock in master mode.
//      Sm mode or SMBus:
//          T_high = CCR * TPCLK1
//          T_low = CCR * TPCLK1
//      Fm mode:
//          If DUTY = 0:
//              T_high = CCR * TPCLK1
//              T_low = 2 * CCR * TPCLK1
//          If DUTY = 1:
//              T_high = 9 * CCR * TPCLK1
//              T_low = 16 * CCR * TPCLK1
//
//     For instance: in Sm mode, to generate a 100 kHz SCL frequency:
//          If FREQ = 08, TPCLK1 = 125 ns so CCR must be programmed with 0x28
//              (0x28 <=> 40d x 125 ns = 5000 ns.)

/***************** 4.8- I2Cs->TRISE  ***************/


//TRISE : Maximum rise time in Fm/Sm mode (Master mode)
//            These bits should provide the maximum duration of the SCL feedback loop in master mode.
//            The purpose is to keep a stable SCL frequency whatever the SCL rising edge duration.
//            These bits must be programmed with the maximum SCL rise time given in the I2Cs bus
//            specification, incremented by 1.
//            For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
//            If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
//                    therefore the TRISE[5:0] bits must be programmed with 09h.
//            (1000 ns / 125 ns = 8 + 1)
//            The filter value can also be added to TRISE[5:0].
//            If the result is not an integer, TRISE[5:0] must be programmed with the integer part, in order
//            to respect the tHIGH parameter.
//            Note: TRISE[5:0] must be configured only when the I2Cs is disabled (PE = 0)


#define pI2C_DUTY_FM_tLOW_tHIGH_2          (0)
#define pI2C_DUTY_FM_tLOW_tHIGH_16_9       (1)

#define pI2C_F_S_STANDARD_MODE      (0)
#define pI2C_F_S_FAST_MODE          (1)






/***************************************************************/
/*					    	(29) FLASH						   */
/***************************************************************/

/*
 * 	FLASH Section Architecture Map
 *		1- FLASH->Base_Definitions
 *		2- FLASH->Registers_Pointers
 *		3- FLASH->Struct_Definition
 *		4- FLASH->Registers_Values_Definitions
 *			4.1- FLASH->ACR
 *			4.2- FLASH->SR
 *			4.3- FLASH->CR
 *			4.4- FLASH->
 *			4.5- FLASH->
 *			4.6- FLASH->
 *			4.7- FLASH->
 *			4.8- FLASH->
 *			4.9- FLASH->
 *			4.10- FLASH->
 *
 *
 * */


/***************** 1- FLASH->Base_Definition ******************/
#define FLASH_BASE            (0x40022000)

#define FLASH_ACR_BASE        (FLASH_BASE +0x00)
#define FLASH_KEYR_BASE       (FLASH_BASE +0x04)
#define FLASH_OPTKEYR_BASE    (FLASH_BASE +0x08)
#define FLASH_SR_BASE         (FLASH_BASE +0x08)
#define FLASH_CR_BASE         (FLASH_BASE +0x10)
#define FLASH_AR_BASE         (FLASH_BASE +0x14)
#define FLASH_OBR_BASE        (FLASH_BASE +0x1C)
#define FLASH_WRPR_BASE       (FLASH_BASE +0x20)


#define STM32F103_PAGE_SIZE (1024)
#define STM32F103_FLASH_PAGES_COUNT (128)

#define STM32F103_FLASH_MAX_PAGES_NUMBER   (STM32F103_FLASH_PAGES_COUNT -1)


#define STM32F103_FLASH_START			(0x08000000)
#define STM32F103_FLASH_END				(STM32F103_FLASH_START+(STM32F103_FLASH_PAGES_COUNT*STM32F103_PAGE_SIZE))


/***************** 2- FLASH->Registers_Pointers ***************/

#define FLASH_ACR       (*((volatile unsigned long *)FLASH_ACR_BASE))
#define FLASH_KEYR      (*((volatile unsigned long *)FLASH_KEYR_BASE))
#define FLASH_OPTKEYR   (*((volatile unsigned long *)FLASH_OPTKEYR_BASE))
#define FLASH_SR        (*((volatile unsigned long *)FLASH_SR_BASE))
#define FLASH_CR        (*((volatile unsigned long *)FLASH_CR_BASE))
#define FLASH_AR        (*((volatile unsigned long *)FLASH_AR_BASE))
#define FLASH_OBR       (*((volatile unsigned long *)FLASH_OBR_BASE))
#define FLASH_WRPR      (*((volatile unsigned long *)FLASH_WRPR_BASE))
/***************** 3- FLASH->Struct_Definition ****************/


/*  The Access of the FLASH registers must be in 32 bit only*/
typedef volatile struct {
    volatile union {
        unsigned long REG;
    } ACR;

    volatile union {
        unsigned long REG;
    } KEYR;

    volatile union {
        unsigned long REG;
    } OPTKEYR;

    volatile union {
        unsigned long REG;
    } SR;

    volatile union {
        unsigned long REG;
    } CR;

    volatile union {
        unsigned long REG;
    } AR;

    const uint32_t RESERVED;
    volatile union {
        struct{
            const uint32_t OPTERR :1;
            const uint32_t RDPRT :1;
            const uint32_t WDG_SW :1;
            const uint32_t nRST_STOP :1;
            const uint32_t nRST_STDBY :1;
            const uint32_t RESERVED :5;
            const uint32_t Data0 :8;
            const uint32_t Data1 :8;
        };
        unsigned long REG;
    } OBR;

    volatile union {
        unsigned long REG;
    } WRPR;
}FLASH_t;

#define pFLASH ((volatile FLASH_t *)FLASH_BASE)
/***************** 4- FLASH->Registers_Values_Definitions *****/

#define FLASH_RDPRT_KEY (0x00A5)
#define FLASH_KEY1 (0x45670123)
#define FLASH_KEY2 (0xCDEF89AB)

/***************** 4.1- FLASH->ACR  ***************/
#define FLASH_LATENCY_POS (0)
#define FLASH_HLFCYA_POS  (3)
#define FLASH_PRFTBE_POS  (4)
#define FLASH_PRFTBS_POS  (5)



#define FLASH_LATENCY_ZERO_WAIT_STATE__SYSCLK_24    (0)
#define FLASH_LATENCY_ONE_WAIT_STATE__24_SYSCLK_48  (1)
#define FLASH_LATENCY_TWO_WAIT_STATE__48_SYSCLK_72  (2)

#define FLASH_HLFCYA_HALF_CYCLE_DISABLED    (0)
#define FLASH_HLFCYA_HALF_CYCLE_ENABLED     (1)

#define FLASH_PRFTBE_PREFETCH_BUFFER_DISABLED   (0)
#define FLASH_PRFTBE_PREFETCH_BUFFER_ENABLED    (1)

#define FLASH_PRFTBS_PREFETCH_BUFFER_STATUS_DISABLED    (0)
#define FLASH_PRFTBS_PREFETCH_BUFFER_STATUS_ENABLED     (1)



#define FLASH_CR_LATENCY_ZERO_WAIT_STATE__SYSCLK_24       (FLASH_LATENCY_ZERO_WAIT_STATE__SYSCLK_24<<FLASH_LATENCY_POS)
#define FLASH_CR_LATENCY_ONE_WAIT_STATE__24_SYSCLK_48     (FLASH_LATENCY_ONE_WAIT_STATE__24_SYSCLK_48<<FLASH_LATENCY_POS)
#define FLASH_CR_LATENCY_TWO_WAIT_STATE__48_SYSCLK_72     (FLASH_LATENCY_TWO_WAIT_STATE__48_SYSCLK_72<<FLASH_LATENCY_POS)

#define FLASH_CR_HLFCYA_HALF_CYCLE_DISABLED     (FLASH_HLFCYA_HALF_CYCLE_DISABLED<<FLASH_HLFCYA_POS)
#define FLASH_CR_HLFCYA_HALF_CYCLE_ENABLED      (FLASH_HLFCYA_HALF_CYCLE_ENABLED<<FLASH_HLFCYA_POS)

#define FLASH_CR_PRFTBE_PREFETCH_BUFFER_DISABLED    (FLASH_PRFTBE_PREFETCH_BUFFER_DISABLED<<FLASH_PRFTBE_POS)
#define FLASH_CR_PRFTBE_PREFETCH_BUFFER_ENABLED     (FLASH_PRFTBE_PREFETCH_BUFFER_ENABLED<<FLASH_PRFTBE_POS)

#define FLASH_CR_PRFTBS_PREFETCH_BUFFER_STATUS_DISABLED    (FLASH_PRFTBS_PREFETCH_BUFFER_STATUS_DISABLED<<FLASH_PRFTBS_POS)
#define FLASH_CR_PRFTBS_PREFETCH_BUFFER_STATUS_ENABLED    (FLASH_PRFTBS_PREFETCH_BUFFER_STATUS_ENABLED<<FLASH_PRFTBS_POS)

/***************** 4.3- FLASH->SR  ***************/

#define FLASH_BSY_POS          (0)
#define FLASH_PGERR_POS        (2)
#define FLASH_WRPRTERR_POS     (4)
#define FLASH_EOP_POS          (5)



#define FLASH_BSY_NOTBUSY       (0)
#define FLASH_BSY_BUSY          (1)

#define FLASH_PGERR_NO_ERROR    (0)
#define FLASH_PGERR_ERROR       (1)

#define FLASH_WRPRTERR_NO_ERROR     (0)
#define FLASH_WRPRTERR_ERROR        (1)

#define FLASH_EOP_NOT_COMPLETED     (0)
#define FLASH_EOP_COMPLETED         (1)

#define FLASH_SR_BSY_NOTBUSY  (FLASH_BSY_NOTBUSY<<FLASH_BSY_POS)
#define FLASH_SR_BSY_BUSY  (FLASH_BSY_BUSY<<FLASH_BSY_POS)

#define FLASH_SR_PGERR_NO_ERROR  (FLASH_PGERR_NO_ERROR<<FLASH_PGERR_POS)
#define FLASH_SR_PGERR_ERROR  (FLASH_PGERR_ERROR<<FLASH_PGERR_POS)

#define FLASH_SR_WRPRTERR_NO_ERROR  (FLASH_WRPRTERR_NO_ERROR<<FLASH_WRPRTERR_POS)
#define FLASH_SR_WRPRTERR_ERROR  (FLASH_WRPRTERR_ERROR<<FLASH_WRPRTERR_POS)

#define FLASH_SR_EOP_NOT_COMPLETED  (FLASH_EOP_NOT_COMPLETED<<FLASH_EOP_POS)
#define FLASH_SR_EOP_COMPLETED  (FLASH_EOP_COMPLETED<<FLASH_EOP_POS)

/***************** 4.4- FLASH->CR  ***************/
#define FLASH_PG_POS        (0)
#define FLASH_PER_POS       (1)
#define FLASH_MER_POS       (2)
#define FLASH_OPTPG_POS     (4)
#define FLASH_OPTER_POS     (5)
#define FLASH_STRT_POS      (6)
#define FLASH_LOCK_POS      (7)
#define FLASH_OPTWRE_POS    (9)
#define FLASH_ERRIE_POS     (10)
#define FLASH_EOPIE_POS     (12)


#define FLASH_PG_PROGRAMMING_DISABLED    (0)
#define FLASH_PG_PROGRAMMING_ENABLED    (1)

#define FLASH_PER_PAGE_ERASE_DISABLED    (0)
#define FLASH_PER_PAGE_ERASE_ENABLED    (1)

#define FLASH_MER_MASS_ERASE_DISABLED    (0)
#define FLASH_MER_MASS_ERASE_ENABLED    (1)

#define FLASH_OPTPG_OPTION_BYTE_PROGRAMMING_DISABLED    (0)
#define FLASH_OPTPG_OPTION_BYTE_PROGRAMMING_ENABLED    (1)

#define FLASH_OPTER_OPTION_BYTE_ERASE_DISABLED    (0)
#define FLASH_OPTER_OPTION_BYTE_ERASE_ENABLED    (1)

#define FLASH_STRT_START_DISABLED    (0)
#define FLASH_STRT_START_ENABLED    (1)

#define FLASH_LOCK_UNLOCKED    (0)
#define FLASH_LOCK_LOCKED    (1)

#define FLASH_OPTWRE_OPTION_BYTE_WRITE_DISABLED    (0)
#define FLASH_OPTWRE_OPTION_BYTE_WRITE_ENABLED    (1)

#define FLASH_ERRIE_ERROR_INTERRUPT_DISABLED    (0)
#define FLASH_ERRIE_ERROR_INTERRUPT_ENABLED    (1)

#define FLASH_EOPIE_END_OF_OPERATION_INTERRUPT_DISABLED    (0)
#define FLASH_EOPIE_END_OF_OPERATION_INTERRUPT_ENABLED    (1)





#define FLASH_CR_PG_PROGRAMMING_DISABLED    (FLASH_PG_PROGRAMMING_DISABLED<<FLASH_PG_POS)
#define FLASH_CR_PG_PROGRAMMING_ENABLED     (FLASH_PG_PROGRAMMING_ENABLED<<FLASH_PG_POS)

#define FLASH_CR_PER_PAGE_ERASE_DISABLED    (FLASH_PER_PAGE_ERASE_DISABLED<<FLASH_PER_POS)
#define FLASH_CR_PER_PAGE_ERASE_ENABLED     (FLASH_PER_PAGE_ERASE_ENABLED<<FLASH_PER_POS)

#define FLASH_CR_MER_MASS_ERASE_DISABLED    (FLASH_MER_MASS_ERASE_DISABLED<<FLASH_MER_POS)
#define FLASH_CR_MER_MASS_ERASE_ENABLED     (FLASH_MER_MASS_ERASE_ENABLED<<FLASH_MER_POS)

#define FLASH_CR_OPTPG_OPTION_BYTE_PROGRAMMING_DISABLED    (FLASH_OPTPG_OPTION_BYTE_PROGRAMMING_DISABLED<<FLASH_OPTPG_POS)
#define FLASH_CR_OPTPG_OPTION_BYTE_PROGRAMMING_ENABLED     (FLASH_OPTPG_OPTION_BYTE_PROGRAMMING_ENABLED<<FLASH_OPTPG_POS)

#define FLASH_CR_OPTER_OPTION_BYTE_ERASE_DISABLED    (FLASH_OPTER_OPTION_BYTE_ERASE_DISABLED<<FLASH_OPTER_POS)
#define FLASH_CR_OPTER_OPTION_BYTE_ERASE_ENABLED     (FLASH_OPTER_OPTION_BYTE_ERASE_ENABLED<<FLASH_OPTER_POS)

#define FLASH_CR_STRT_START_DISABLED    (FLASH_STRT_START_DISABLED<<FLASH_STRT_POS)
#define FLASH_CR_STRT_START_ENABLED     (FLASH_STRT_START_ENABLED<<FLASH_STRT_POS)

#define FLASH_CR_LOCK_UNLOCKED    (FLASH_LOCK_UNLOCKED<<FLASH_LOCK_POS)
#define FLASH_CR_LOCK_LOCKED      (FLASH_LOCK_LOCKED<<FLASH_LOCK_POS)

#define FLASH_CR_OPTWRE_OPTION_BYTE_WRITE_DISABLED    (FLASH_OPTWRE_OPTION_BYTE_WRITE_DISABLED<<FLASH_OPTWRE_POS)
#define FLASH_CR_OPTWRE_OPTION_BYTE_WRITE_ENABLED     (FLASH_OPTWRE_OPTION_BYTE_WRITE_ENABLED<<FLASH_OPTWRE_POS)

#define FLASH_CR_ERRIE_ERROR_INTERRUPT_DISABLED    (FLASH_ERRIE_ERROR_INTERRUPT_DISABLED<<FLASH_ERRIE_POS)
#define FLASH_CR_ERRIE_ERROR_INTERRUPT_ENABLED     (FLASH_ERRIE_ERROR_INTERRUPT_ENABLED<<FLASH_ERRIE_POS)

#define FLASH_CR_EOPIE_END_OF_OPERATION_INTERRUPT_DISABLED    (FLASH_EOPIE_END_OF_OPERATION_INTERRUPT_DISABLED<<FLASH_EOPIE_POS)
#define FLASH_CR_EOPIE_END_OF_OPERATION_INTERRUPT_ENABLED     (FLASH_EOPIE_END_OF_OPERATION_INTERRUPT_ENABLED<<FLASH_EOPIE_POS)



/***************** 4.5- FLASH->OBR  ***************/


#endif /* STM32F103C8T_H */




//
//#define $REG$_BASE            ($BASE$)
//#define $REG$_BASE            (FLASH_BASE +0x$OFFSET$)
//
//#define $REG$    (*((volatile unsigned long *)$REG$_BASE))
//
//

//volatile union {
//    struct {
//       $END$
//    };
//    unsigned long REG;
//} $REG$;

/***************************************************************/
/*					    	($n$) $p$						   */
/***************************************************************/

/*
 * 	$p$ Section Architecture Map
 *		1- $p$->Base_Definitions
 *		2- $p$->Registers_Pointers
 *		3- $p$->Struct_Definition
 *		4- $p$->Registers_Values_Definitions
 *			4.1- $p$->
 *			4.2- $p$->
 *			4.3- $p$->
 *			4.4- $p$->
 *			4.5- $p$->
 *			4.6- $p$->
 *			4.7- $p$->
 *			4.8- $p$->
 *			4.9- $p$->
 *			4.10- $p$->
 *
 *
 * */


/***************** 1- $p$->Base_Definition ******************/

/***************** 2- $p$->Registers_Pointers ***************/
/***************** 3- $p$->Struct_Definition ****************/
/***************** 4- $p$->Registers_Values_Definitions *****/
/***************** 4.1- $p$->  ***************/
/***************** 4.3- $p$->  ***************/
/***************** 4.4- $p$->  ***************/
/***************** 4.5- $p$->  ***************/
/***************** 4.6- $p$->  ***************/
/***************** 4.7- $p$->  ***************/
/***************** 4.8- $p$->  ***************/
/***************** 4.9- $p$->  ***************/
/***************** 4.10- $p$->  **************/




