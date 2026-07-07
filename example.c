/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "example.h"
#include "lsm6dso.h"
#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables */
lsm6dso_object_t *pLsm6dso0; /* pointer referencing the LSM6DSO object instance */
lsm6dso_axes_t accData;
lsm6dso_axes_t gyroData;

/** ########## Step 1 ##########
  * The init of LSM6DSO is triggered by the applicative code
  */

app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  /* Retrieve and store the LSM6DSO object pointer */
  pLsm6dso0 = MX_LSM6DSO_getobject();
  /* Initialize the LSM6DSO device 0 */
  if (lsm6dso_drv_init(pLsm6dso0, MX_LSM6DSO) != 0)
  {
    PRINTF("[ERROR] Step 1: LSM6DSO sensor init error\n");
    goto _app_init_exit;
  }
  PRINTF("[INFO] Step 1: LSM6DSO sensor init completed\n");

  /* LSM6DSO device 0: enable the ACC feature */
  if (lsm6dso_drv_acc_enable(pLsm6dso0) != 0)
  {
    PRINTF("[ERROR] Step 1: Enabling the ACC feature error\n");
    goto _app_init_exit;
  }
  PRINTF("[INFO] Step 1: Enabling the ACC feature completed\n");

  /* LSM6DSO device 0: enable the GYRO feature */
  if (lsm6dso_drv_gyro_enable(pLsm6dso0) != 0)
  {
    PRINTF("[ERROR] Step 1: Enabling the GYRO feature error\n");
    goto _app_init_exit;
  }
  PRINTF("[INFO] Step 1: Enabling the GYRO feature completed\n");


  HAL_Delay(100);
  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
}

/** ########## Step 2 ##########
  * Gets the values of the accelerometer in hg and of the gyroscope in mdps.
  * The values are displayed on the terminal.
  * output: EXEC_STATUS_OK if OK, EXEC_STATUS_ERROR in case of error
  */

app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /* LSM6DSO device 0: get the acceleration value and print it */
  if (lsm6dso_drv_acc_getaxes(pLsm6dso0, &accData) != 0)
  {
    PRINTF("[ERROR] Step 2: Reading acceleration error\n");
    goto _app_process_exit;
  }
  PRINTF("[INFO] Step 2: ACC X=%" PRIi32 " Y=%" PRIi32 " Z=%" PRIi32 "\n", (int32_t)accData.x_axis,
         (int32_t)accData.y_axis, (int32_t)accData.z_axis);

  /* LSM6DSO device 0: get the gyroscope value and print it */
  if (lsm6dso_drv_gyro_getaxes(pLsm6dso0, &gyroData) != 0)
  {
    PRINTF("[ERROR] Step 2: Reading gyroscope error\n");
    goto _app_process_exit;
  }
  PRINTF("[INFO] Step 2: GYR X=%" PRIi32 " Y=%" PRIi32 " Z=%" PRIi32 "\n", (int32_t)gyroData.x_axis,
         (int32_t)gyroData.y_axis, (int32_t)gyroData.z_axis);


  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
}

/** ########## Step 3 ##########
  * In this example, app_deinit is never called and is provided as a reference only.
  */

app_status_t app_deinit(void)
{
  lsm6dso_drv_deinit(pLsm6dso0);

  return EXEC_STATUS_OK;
}
