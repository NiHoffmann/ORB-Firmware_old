//*******************************************************************
/*!
\file   config.h
\author Thomas Breuer
\date   02.02.2021
\brief  Configuration file
*/
#ifndef CONFIG_H_
#define CONFIG_H_
    //*******************************************************************
    #include "descriptor.cpp"

    //*******************************************************************
    #if (BOARD_MAIN == 0 && BOARD_SUB == 22)

      #include "config_Board_00_22.h"

    #elif (BOARD_MAIN == 0 && BOARD_SUB == 30)

      #include "config_Board_00_30.h"

    #elif (BOARD_MAIN == 1 && BOARD_SUB == 0)

      #include "config_Board_01_00.h"

    #else

      #error "Board hardware version not defined"

    #endif

#endif
//EOF
