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
    #include "lib.h"
    #include "MotorTask.h"
    #include "ServoTask.h"
    #include "SensorTask.h"

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

    Rtos rtos( NUM_OF_SENSOR_PORTS+1+1, 200/*us*/ );
    Sensor::Context sContext[ NUM_OF_SENSOR_PORTS ]
      = { Sensor::Context( adc1, adc21, digitalA_1, digitalB_1, digitalC_1, digitalD_1, digitalH_1 ),
          Sensor::Context( adc2, adc22, digitalA_2, digitalB_2, digitalC_2, digitalD_2, digitalH_2 ),
          Sensor::Context( adc3, adc23, digitalA_3, digitalB_3, digitalC_3, digitalD_3, digitalH_3 ),
          Sensor::Context( adc4, adc24, digitalA_4, digitalB_4, digitalC_4, digitalD_4, digitalH_4 ) };

    SensorTask sTask[ NUM_OF_SENSOR_PORTS ]
      = { SensorTask( rtos, sContext[0], uart1, tim10, extInt1 ),
          SensorTask( rtos, sContext[1], uart2, tim10, extInt2 ),
          SensorTask( rtos, sContext[2], uart3, tim10, extInt3 ),
          SensorTask( rtos, sContext[3], uart4, tim10, extInt4 ) };

    MotorTask mTask[ NUM_OF_MOTOR_PORTS ]
      = { MotorTask( taskManager, mot1, enc_A ),
          MotorTask( taskManager, mot2, enc_B ),
          MotorTask( taskManager, mot3, enc_C ),
          MotorTask( taskManager, mot4, enc_D ) };

    ServoTask servoTask[ NUM_OF_SERVO_PORTS ]
      = { ServoTask( taskManager, pwm_ModellServo1 ),
          ServoTask( taskManager, pwm_ModellServo2 ) };
#endif

//EOF
