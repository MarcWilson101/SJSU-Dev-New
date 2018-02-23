#include <LabGPIOInterrupts.hpp>
#include "LPC17xx.h"
#include "lpc_isr.h"
#include <cstdint>
#include <stdio.h>

#include "uart0_min.h"

  void ( * LabGPIOInterrupts::ISRLookup[2][32]) (void) = {0};

  LabGPIOInterrupts::LabGPIOInterrupts()
  {

  }

  //* 1) Should setup register "externalIRQHandler" as the EINT3 ISR.
  //* 2) Should configure NVIC to notice EINT3 IRQs.
  void LabGPIOInterrupts::init()
  {
    uart0_puts("in init");
    isr_register(EINT3_IRQn, externalIRQHandler);
    NVIC_EnableIRQ(EINT3_IRQn);
  }
  /**
   * This handler should place a function pointer within the lookup table for the externalIRQHandler to find.
   *
   * @param[in] port         specify the GPIO port
   * @param[in] pin          specify the GPIO pin to assign an ISR to
   * @param[in] pin_isr      function to run when the interrupt event occurs
   * @param[in] condition    condition for the interrupt to occur on. RISING, FALLING or BOTH edges. 0,1,2
   * @return should return true if valid ports, pins, isrs were supplied and pin isr insertion was sucessful
   */
  bool LabGPIOInterrupts::attachInterruptHandler(uint8_t port, uint32_t pin, void (* pin_isr) (void), uint8_t condition)
  {
    uart0_puts("inside attatchinterrupthandler");
    ISRLookup[port][pin] = pin_isr;
    if(port == 0)
    {
      if(condition == 0)
      {
        LPC_GPIOINT->IO0IntEnR |= (1 << pin);
      }
      else if(condition == 1)
      {
        LPC_GPIOINT->IO0IntEnF |= (1 << pin);
      }
      else if(condition == 2)
      {
        LPC_GPIOINT->IO0IntEnR |= (1 << pin);
        LPC_GPIOINT->IO0IntEnF |= (1 << pin);
      }
    }
    else if(port == 2)
    {
      {
        if(condition == 0)
        {
          LPC_GPIOINT->IO2IntEnR |= (1 << pin);
        }
        else if(condition == 1)
        {
          LPC_GPIOINT->IO2IntEnF |= (1 << pin);
        }
        else if(condition == 2)
        {
          LPC_GPIOINT->IO2IntEnR |= (1 << pin);
          LPC_GPIOINT->IO2IntEnF |= (1 << pin);
        }
      }
    }
    else
    {
      //wrong port
    }
    //portISRLookup[port][pin] = pin_isr;
    return true;
  }
  /**
   * After the init function has run, this will be executed whenever a proper
   * EINT3 external GPIO interrupt occurs. This function figure out which pin
   * has been interrupted and run the ccorrespondingISR for it using the lookup table.
   *
   * VERY IMPORTANT! Be sure to clear the interrupt flag that caused this
   * interrupt, or this function will be called again and again and again, ad infinitum.
   *
   * Also, NOTE that your code needs to be able to handle two GPIO interrupts occurring
   * at the same time.
   */
  void LabGPIOInterrupts::externalIRQHandler(void)
  {
    int isrPort0Pin = 1, isrPort2Pin = 1;     //pin where interrupt happens
    if(LPC_GPIOINT->IO0IntStatR > 0)          //if an interrupt happens, there will be a 1 somewhere
    {
      int temp = LPC_GPIOINT->IO0IntStatR;
      while(temp != 1)
      {
        isrPort0Pin++;
        temp = temp >> 1;
      }
       ISRLookup[0][isrPort0Pin]();
       LPC_GPIOINT->IO0IntClr |= (1 << isrPort0Pin);
    }
  }
  LabGPIOInterrupts::~LabGPIOInterrupts(){}
