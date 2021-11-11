/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT5_UART1RXSRC_UART_RX 0x00u /*!<@brief UART1 Receive Data Source Select: UART1_RX pin */
#define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART1 Transmit Data Source Select: UART1_TX pin */

/*! @name PORTA2 (number 36), J1[4]/D1/UART1_TX_TGTMCU
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_row2_FGPIO FGPIOA             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_row2_GPIO GPIOA               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_row2_GPIO_PIN_MASK (1U << 2U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_row2_PORT PORTA               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_row2_PIN 2U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_row2_PIN_MASK (1U << 2U)      /*!<@brief PORT pin mask */
                                                     /* @} */

/*! @name PORTD3 (number 96), J1[6]/D2
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_row3_FGPIO FGPIOD             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_row3_GPIO GPIOD               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_row3_GPIO_PIN_MASK (1U << 3U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_row3_PORT PORTD               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_row3_PIN 3U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_row3_PIN_MASK (1U << 3U)      /*!<@brief PORT pin mask */
                                                     /* @} */

/*! @name PORTA12 (number 42), J1[8]/D3
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_row4_FGPIO FGPIOA              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_row4_GPIO GPIOA                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_row4_GPIO_PIN_MASK (1U << 12U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_row4_PORT PORTA                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_row4_PIN 12U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_row4_PIN_MASK (1U << 12U)      /*!<@brief PORT pin mask */
                                                      /* @} */

/*! @name PORTA4 (number 38), J1[10]/D4
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_column1_FGPIO FGPIOA             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_column1_GPIO GPIOA               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_column1_GPIO_PIN_MASK (1U << 4U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_column1_PORT PORTA               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_column1_PIN 4U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_column1_PIN_MASK (1U << 4U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORTA5 (number 39), J1[12]/D5
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_column2_FGPIO FGPIOA             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_column2_GPIO GPIOA               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_column2_GPIO_PIN_MASK (1U << 5U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_column2_PORT PORTA               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_column2_PIN 5U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_column2_PIN_MASK (1U << 5U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORTC9 (number 85), J1[16]/D7
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_column4_FGPIO FGPIOC             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_column4_GPIO GPIOC               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_column4_GPIO_PIN_MASK (1U << 9U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_column4_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_column4_PIN 9U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_column4_PIN_MASK (1U << 9U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORTC13 (number 89), J2[1]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_S2_FGPIO FGPIOC              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_S2_GPIO GPIOC                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_S2_GPIO_PIN_MASK (1U << 13U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_S2_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_S2_PIN 13U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_S2_PIN_MASK (1U << 13U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTC16 (number 90), J2[3]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_S1_FGPIO FGPIOC              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_S1_GPIO GPIOC                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_S1_GPIO_PIN_MASK (1U << 16U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_S1_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_S1_PIN 16U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_S1_PIN_MASK (1U << 16U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTA7 (number 41), J2[5]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_E_FGPIO FGPIOA             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_E_GPIO GPIOA               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_E_GPIO_PIN_MASK (1U << 7U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_E_PORT PORTA               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_E_PIN 7U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_E_PIN_MASK (1U << 7U)      /*!<@brief PORT pin mask */
                                                  /* @} */

/*! @name PORTE30 (number 27), J4[11]/DAC_OUT
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_D7_FGPIO FGPIOE              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_D7_GPIO GPIOE                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_D7_GPIO_PIN_MASK (1U << 30U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_D7_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_D7_PIN 30U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_D7_PIN_MASK (1U << 30U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTB20 (number 66), J4[9]/CMP_OUT
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_D6_FGPIO FGPIOB              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_D6_GPIO GPIOB                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_D6_GPIO_PIN_MASK (1U << 20U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_D6_PORT PORTB                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_D6_PIN 20U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_D6_PIN_MASK (1U << 20U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTE23 (number 21), J4[7]/DIFF_ADC1_DM
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_D5_FGPIO FGPIOE              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_D5_GPIO GPIOE                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_D5_GPIO_PIN_MASK (1U << 23U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_D5_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_D5_PIN 23U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_D5_PIN_MASK (1U << 23U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTE21 (number 19), J4[3]/DIFF_ADC0_DM
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_D4_FGPIO FGPIOE              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_D4_GPIO GPIOE                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_D4_GPIO_PIN_MASK (1U << 21U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_D4_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_D4_PIN 21U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_D4_PIN_MASK (1U << 21U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTC0 (number 70), J1[5]/I2S_TXD
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_S8_FGPIO FGPIOC             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_S8_GPIO GPIOC               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_S8_GPIO_PIN_MASK (1U << 0U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_S8_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_S8_PIN 0U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_S8_PIN_MASK (1U << 0U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTC4 (number 80), J1[7]/I2S_MCLK
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_S7_FGPIO FGPIOC             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_S7_GPIO GPIOC               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_S7_GPIO_PIN_MASK (1U << 4U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_S7_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_S7_PIN 4U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_S7_PIN_MASK (1U << 4U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTC6 (number 82), J1[9]/I2S_RX_BCLK
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_S6_FGPIO FGPIOC             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_S6_GPIO GPIOC               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_S6_GPIO_PIN_MASK (1U << 6U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_S6_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_S6_PIN 6U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_S6_PIN_MASK (1U << 6U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTC7 (number 83), J1[11]/SOF_OUT
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_S5_FGPIO FGPIOC             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_S5_GPIO GPIOC               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_S5_GPIO_PIN_MASK (1U << 7U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_S5_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_S5_PIN 7U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_S5_PIN_MASK (1U << 7U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTC10 (number 86), J1[13]/I2S_RX_FS
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_S4_FGPIO FGPIOC              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_S4_GPIO GPIOC                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_S4_GPIO_PIN_MASK (1U << 10U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_S4_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_S4_PIN 10U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_S4_PIN_MASK (1U << 10U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTC11 (number 87), J1[15]/I2S_RXD
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_S3_FGPIO FGPIOC              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_S3_GPIO GPIOC                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_S3_GPIO_PIN_MASK (1U << 11U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_S3_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_S3_PIN 11U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_S3_PIN_MASK (1U << 11U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTE2 (number 3), J3[15]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_E8_FGPIO FGPIOE             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_E8_GPIO GPIOE               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_E8_GPIO_PIN_MASK (1U << 2U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_E8_PORT PORTE               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_E8_PIN 2U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_E8_PIN_MASK (1U << 2U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTE3 (number 4), J3[13]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_E7_FGPIO FGPIOE             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_E7_GPIO GPIOE               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_E7_GPIO_PIN_MASK (1U << 3U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_E7_PORT PORTE               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_E7_PIN 3U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_E7_PIN_MASK (1U << 3U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTE6 (number 7), J3[11]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_E6_FGPIO FGPIOE             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_E6_GPIO GPIOE               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_E6_GPIO_PIN_MASK (1U << 6U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_E6_PORT PORTE               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_E6_PIN 6U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_E6_PIN_MASK (1U << 6U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTE16 (number 14), J3[9]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_E5_FGPIO FGPIOE              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_E5_GPIO GPIOE                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_E5_GPIO_PIN_MASK (1U << 16U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_E5_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_E5_PIN 16U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_E5_PIN_MASK (1U << 16U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTE17 (number 15), J3[7]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_E4_FGPIO FGPIOE              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_E4_GPIO GPIOE                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_E4_GPIO_PIN_MASK (1U << 17U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_E4_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_E4_PIN 17U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_E4_PIN_MASK (1U << 17U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTE18 (number 16), J3[5]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_E3_FGPIO FGPIOE              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_E3_GPIO GPIOE                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_E3_GPIO_PIN_MASK (1U << 18U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_E3_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_E3_PIN 18U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_E3_PIN_MASK (1U << 18U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTE19 (number 17), J3[3]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_E2_FGPIO FGPIOE              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_E2_GPIO GPIOE                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_E2_GPIO_PIN_MASK (1U << 19U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_E2_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_E2_PIN 19U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_E2_PIN_MASK (1U << 19U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTE31 (number 28), J3[1]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_E1_FGPIO FGPIOE              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_E1_GPIO GPIOE                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_E1_GPIO_PIN_MASK (1U << 31U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_E1_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_E1_PIN 31U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_E1_PIN_MASK (1U << 31U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTE0 (number 1), J2[18]/D14
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_TX_PORT PORTE               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_TX_PIN 0U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_TX_PIN_MASK (1U << 0U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTE1 (number 2), J2[20]/D15
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_RX_PORT PORTE               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_RX_PIN 1U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_RX_PIN_MASK (1U << 1U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTC8 (number 84), J1[14]/D6
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_column3_FGPIO FGPIOC             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_column3_GPIO GPIOC               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_column3_GPIO_PIN_MASK (1U << 8U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_column3_PORT PORTC               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_column3_PIN 8U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_column3_PIN_MASK (1U << 8U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORTA6 (number 40), J2[7]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RW_FGPIO FGPIOA             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_RW_GPIO GPIOA               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_RW_GPIO_PIN_MASK (1U << 6U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_RW_PORT PORTA               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_RW_PIN 6U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_RW_PIN_MASK (1U << 6U)      /*!<@brief PORT pin mask */
                                                   /* @} */

/*! @name PORTA14 (number 44), J2[9]
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RS_FGPIO FGPIOA              /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_RS_GPIO GPIOA                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_RS_GPIO_PIN_MASK (1U << 14U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_RS_PORT PORTA                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_RS_PIN 14U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_RS_PIN_MASK (1U << 14U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORTA1 (number 35), J1[2]/D0/UART1_RX_TGTMCU
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_row1_FGPIO FGPIOA             /*!<@brief FGPIO peripheral base pointer */
#define BOARD_INITPINS_row1_GPIO GPIOA               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_row1_GPIO_PIN_MASK (1U << 1U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_row1_PORT PORTA               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_row1_PIN 1U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_row1_PIN_MASK (1U << 1U)      /*!<@brief PORT pin mask */
                                                     /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
