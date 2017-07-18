#include "main.h"

__IO uint8_t TxCount = 0; 
__IO uint16_t RxCount = 0;

static void USART_Config(void);
static void NVIC_Config(void);


int main(void)
{ 
  /* NVIC configuration */
  NVIC_Config();
  
  /* USART configuration */
  USART_Config();
  
  /* Enable the EVAL_COM1 Transmoit interrupt: this interrupt is generated when the 
  EVAL_COM1 transmit data register is empty */  
  USART_ITConfig(WS751_UART, USART_IT_RXNE, ENABLE);
  USART_ITConfig(DEBUG_COM, USART_IT_RXNE, ENABLE);

  while(1)
  {
  }
}


/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
static void NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the USART Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = WS751_UART_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
    /* Enable the USART Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief Configure the USART Device
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
 
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(WS751_UART_TX_GPIO_CLK | WS751_UART_RX_GPIO_CLK, ENABLE);

  /* Enable USART clock */
  RCC_APB1PeriphClockCmd(WS751_UART_CLK, ENABLE);

  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(WS751_UART_TX_GPIO_PORT, WS751_UART_TX_SOURCE, WS751_UART_TX_AF);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(WS751_UART_RX_GPIO_PORT, WS751_UART_RX_SOURCE, WS751_UART_RX_AF);

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = WS751_UART_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(WS751_UART_TX_GPIO_PORT, &GPIO_InitStructure);

  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = WS751_UART_RX_PIN;
  GPIO_Init(WS751_UART_RX_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DEBUG_COM_TX_PIN;

  GPIO_Init(DEBUG_COM_TX_GPIO_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = DEBUG_COM_RX_PIN;
  GPIO_Init(DEBUG_COM_RX_GPIO_PORT, &GPIO_InitStructure);

/* USARTx configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 8 Bits
  - Two Stop Bit
  - Odd parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* USART configuration */
  USART_Init(WS751_UART, &USART_InitStructure);

  /* Enable USART */
  USART_Cmd(WS751_UART, ENABLE);

}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

