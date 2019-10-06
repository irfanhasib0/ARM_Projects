/* 
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2018, Kenta Yonekura (a.k.a. yoneken)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote prducts derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ROS_STM32_HARDWARE_H_
#define ROS_STM32_HARDWARE_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_tim.h"
static unsigned long time_ms=0;
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;
//extern char pData[10];
static void _MX_USART1_UART_Init(void);

#define IT_ROS


#ifdef IT_ROS
//void USART1_IRQHandler(void)
//{
//  HAL_UART_IRQHandler(&huart1);
//}
char pData[1];
class STM32Hardware {
public:

	STM32Hardware(){

	}
	void init(){
		_MX_USART1_UART_Init();

		//__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);

	}
	int read(){
		int rbyte=-1;
		memset(pData,0,1);
		HAL_UART_Receive_DMA(&huart1, (uint8_t*)pData,1);
		if(pData[0])rbyte=(int)pData[0];
		return rbyte;
	}
	void write(uint8_t* data, int length){
		HAL_UART_Transmit(&huart1, (uint8_t*)data,length,1000);
	}
	unsigned long time(){
		return time_ms;
	}
};
#endif

#ifdef UART_ROS
class STM32Hardware {
public:

	STM32Hardware(){

	}
	void init(){
		_MX_USART1_UART_Init();
		//__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);

	}
	int read(){
		int rbyte=-1;
		char pData[1];
		memset(pData,0,1);
		HAL_UART_Receive(&huart1, (uint8_t*)pData,1,1000);
		if(pData[0])rbyte=(int)pData[0];
		return rbyte;
	}
	void write(uint8_t* data, int length){
		HAL_UART_Transmit(&huart1, (uint8_t*)data,length,1000);
	}
	unsigned long time(){
		return time_ms;
	}
};
#endif

#ifdef DMA_ROS
class STM32Hardware {
  protected:
    TIM_HandleTypeDef *htim;
    UART_HandleTypeDef *huart;

    const static uint16_t rbuflen = 128;
    uint8_t rbuf[rbuflen];
    uint32_t rind;
    inline uint32_t getRdmaInd(void){ return (rbuflen - huart->hdmarx->Instance->NDTR) & (rbuflen - 1); }

    const static uint16_t tbuflen = 256;
    uint8_t tbuf[tbuflen];
    uint32_t twind, tfind;

  public:
    STM32Hardware():
      htim(&htim1), huart(&huart1), rind(0), twind(0), tfind(0){
    }

    STM32Hardware(TIM_HandleTypeDef *htim_, UART_HandleTypeDef *huart_):
      htim(htim_), huart(huart_), rind(0), twind(0), tfind(0){
    }
  
    void init(){
      reset_rbuf();
      _MX_USART1_UART_Init();
      //HAL_TIM_Base_Start(htim);
    }

    void reset_rbuf(void){
      memset(rbuf,0,rbuflen);
      HAL_UART_Receive_IT(huart, rbuf, rbuflen);
    }

    int read(){
      int c = -1;
      //if(rind != getRdmaInd()){
      if(rbuf[rind]){
        c = rbuf[rind++];
        rind &= rbuflen - 1;
      }
      return c;
    }

    void flush(void){
      static bool mutex = false;

      if((huart->gState == HAL_UART_STATE_READY) && !mutex){
        mutex = true;

        if(twind != tfind){
          uint16_t len = tfind < twind ? twind - tfind : tbuflen - tfind;
          HAL_UART_Transmit_IT(huart, &(tbuf[tfind]), len);
          tfind = (tfind + len) & (tbuflen - 1);
        }
        mutex = false;
      }
    }

    void write(uint8_t* data, int length){
      int n = length;
      n = n <= tbuflen ? n : tbuflen;

      int n_tail = n <= tbuflen - twind ? n : tbuflen - twind;
      memcpy(&(tbuf[twind]), data, n_tail);
      twind = (twind + n) & (tbuflen - 1);

      if(n != n_tail){
        memcpy(tbuf, &(data[n_tail]), n - n_tail);
      }

      flush();
    }

    unsigned long time(){ return time_ms; }

  protected:
};
#endif
#endif

static void _MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
#ifdef IT_ROS
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  //_HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
 // __HAL_UART_ENABLE_IT(&huart1,UART_IT_TXE);
#endif
  /* USER CODE END USART1_Init 2 */

}
