


/**************	Section: Includes *********************************/
#include "std_math.h"

/**************	Section: Local Variables Declarations *************/
/**************	Section: Local Methods Prototype Declarations *****/
/**************	Section: Methods Declarations *********************/
/**************	Section: Helper Methods Declarations  *************/

uint32_t pow2(uint32_t x, uint32_t y) {

    uint32_t ret = 1;
    if (y != 0) {

    	for (uint32_t i = 0; i < y; i++) {
    	        ret *= x;
    	    }
    }

    return ret;
}
