
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/****************** Section: Includes ****************************/
/****************** Section: Macro Declarations ******************/

#define _INT8_T_DECLARED
#define _UINT8_T_DECLARED
#define _INT16_T_DECLARED
#define _UINT16_T_DECLARED
#define _INT32_T_DECLARED
#define _UINT32_T_DECLARED
#define _INT64_T_DECLARED
#define _UINT64_T_DECLARED


#define STD_ON    (1)
#define STD_OFF   (0)

#define STD_HIGH   (1)
#define STD_LOW    (0)

#ifndef NULL
#define NULL    ((void*)0)
#endif

#define E_OK        (0)
#define E_NOT_OK    (1)
#define E_TIMEOUT   (2)

#define BIT_0    0
#define BIT_1    1
#define BIT_2    2
#define BIT_3    3
#define BIT_4    4
#define BIT_5    5
#define BIT_6    6
#define BIT_7    7
#define BIT_8    8
#define BIT_9    9
#define BIT_10    10
#define BIT_11    11
#define BIT_12    12
#define BIT_13    13
#define BIT_14    14
#define BIT_15    15
#define BIT_16    16
#define BIT_17    17
#define BIT_18    18
#define BIT_19    19
#define BIT_20    20
#define BIT_21    21
#define BIT_22    22
#define BIT_23    23
#define BIT_24    24
#define BIT_25    25
#define BIT_26    26
#define BIT_27    27
#define BIT_28    28
#define BIT_29    29
#define BIT_30    30
#define BIT_31    31

#define PIN_0        (1<<(0))
#define PIN_1        (1<<(1))
#define PIN_2        (1<<(2))
#define PIN_3        (1<<(3))
#define PIN_4        (1<<(4))
#define PIN_5        (1<<(5))
#define PIN_6        (1<<(6))
#define PIN_7        (1<<(7))
#define PIN_8        (1<<(8))
#define PIN_9        (1<<(9))
#define PIN_10       (1<<(10))
#define PIN_11       (1<<(11))
#define PIN_12       (1<<(12))
#define PIN_13       (1<<(13))
#define PIN_14       (1<<(14))
#define PIN_15       (1<<(15))
#define PIN_16       (1<<(16))
#define PIN_17       (1<<(17))
#define PIN_18       (1<<(18))
#define PIN_19       (1<<(19))
#define PIN_20       (1<<(20))
#define PIN_21       (1<<(21))
#define PIN_22       (1<<(22))
#define PIN_23       (1<<(23))
#define PIN_24       (1<<(24))
#define PIN_25       (1<<(25))
#define PIN_26       (1<<(26))
#define PIN_27       (1<<(27))
#define PIN_28       (1<<(28))
#define PIN_29       (1<<(29))
#define PIN_30       (1<<(30))
#define PIN_31       (1<<(31))


/****************** Section: Macro Functions Declarations ********/

#define SET_BIT(REG, BIT)    ((REG)|=  (1<<(BIT)))
#define CLEAR_BIT(REG, BIT)    ((REG)&= ~(1<< (BIT)))
#define TOGGLE_BIT(REG, BIT)    ((REG)^=    (1<< (BIT)))
#define FORCE_BIT(REG, BIT, VAL)  ((VAL)? SET_BIT((REG),(BIT)): CLEAR_BIT((REG),(BIT)))

#define FORCE_MASK(REG, MASK, VAL)    ((REG)&= ~(MASK) , (REG)|=(VAL))
#define FORCE_MASK_OFFSET(REG, MASK, VAL, OFFSET)    ((REG)&= ~((MASK) << (OFFSET)) , (REG)|=((VAL) << (OFFSET)))
#define SET_MASK(REG, MASK) ((REG)=|(MASK))
#define CLEAR_MASK(REG, MASK)((REG)&=~(MASK))

#define READ_BIT(REG, BIT)    (((REG) & (1<<(BIT)))>>(BIT))
#define READ_MASK(REG, MASK)     ((REG) & (MASK))


#define CONCAT(x, y) x##y
#define EXPAND(x, y) CONCAT(x,y)
#define RESERVED    EXPAND(reserved,__LINE__)

#define CONVERT_TYPE(TYPE, TARGET)       (*((TYPE*)&TARGET))
#define CONVERT_TYPE_INDX(TYPE, TARGET, INDX)       (*( ((TYPE*)&TARGET) + (INDX)))


#define WAIT_CONDITION_OR_TIMEOUT(CONDITION, TIMEOUT)  \
          uint32_t __timeout_counter = 0;         \
          while ((__timeout_counter++ <= TIMEOUT) && !(CONDITION)) \
          {/* Do Nothing */}

/*
 * M stands for modifying
 *  Use it for not defining counter
 */
#define WAIT_CONDITION_OR_TIMEOUT_M(CONDITION, TIMEOUT)     while ((0<= TIMEOUT--) && !(CONDITION)) {/* Do Nothing */}


#define STR(x) #x
#define STRINGFY(x) #x
#define STRINGFY2(x, y) STRINGFY(x##y)
#define STRINGFY3(x, y, z) STRINGFY(x##y##z)

#define TIMEOUT_INF     (~(0UL))
#define TIMEOUT_INF_INT32_T (~(0UL)>>1)
#define TIMEOUT_INF_UINT32_T TIMEOUT_INF

/****************** Section: Data Types Declarations *************/

typedef signed char sint8_t;
typedef signed short int sint16_t;
typedef signed long int sint32_t;
typedef signed long long sint64_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;

typedef char int8_t;
typedef short int int16_t;
typedef long int int32_t;
typedef long long int64_t;

typedef float f32_t;
typedef double f64_t;

typedef uint8_t Std_ReturnType;

typedef enum {
    TimeOut_Valid = (0),
    TimeOut_Expired = (1),
} TimeOut_t;


/****************** Section: Functions Declarations **************/

#endif /* STD_TYPES_H_ */
