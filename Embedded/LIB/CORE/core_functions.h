#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H
/**************	Section: Includes ***************************/
#include "std_types.h"
/**************	Section: Macro Definitions Declarations *****/



/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

#define CORE_FUNCTIONS_USE_C_IMPLEMENTATION


uint32_t __get_BASEPRI(void);
 inline void __set_BASEPRI(uint32_t priority);

uint32_t __get_PRIMASK(void);
 inline void __set_PRIMASK(uint32_t priority);

#ifdef CORE_FUNCTIONS_USE_C_IMPLEMENTATION
void __disable_irq();
void __enable_irq();


/**
 * @brief Set the Main Stack Pointer (MSP)
 * @param topOfMainStack The address to set as the new MSP
 */
void __set_MSP(uint32_t topOfMainStack);

/**
 * @brief Get the current Main Stack Pointer (MSP)
 * @return The current value of the MSP
 */
uint32_t __get_MSP(void);

/**
 * @brief Set the Process Stack Pointer (PSP)
 * @param topOfProcessStack The address to set as the new PSP
 */
void __set_PSP(uint32_t topOfProcessStack);

/**
 * @brief Get the current Process Stack Pointer (PSP)
 * @return The current value of the PSP
 */
uint32_t __get_PSP(void);



#else

#define __disable_irq() (__asm__ volatile ("CPSID i"))
#define __enable_irq() (__asm__ volatile ("CPSIE i"))

#endif //CORE_FUNCTIONS_USE_C_IMPLEMENTATION
/**************	Section: Methods Declarations  **************/
#endif //CORE_FUNCTIONS_H
