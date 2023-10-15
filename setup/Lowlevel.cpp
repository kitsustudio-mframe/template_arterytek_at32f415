/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************
 * Include
 */
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
#include "chip_arterytek_at32f415.h"
#include "core_arterytek_at32f415.h"
#include "mframe.h"
#include "rtos_rtx5.h"

//-----------------------------------------------------------------------------


/* ****************************************************************************
 * Using
 */

//-----------------------------------------------------------------------------
using namespace mframe::lang;
using namespace mframe::hal;
using namespace chip;
using namespace core;
using core::CoreHardwareInfo;
using cmsisrtos::CmsisrtosKernel;
using mframe::ctrl::SerialPort;
using mframe::hal::usart::Uart;
using mframe::sys::Stacker;
using mframe::sys::SystemConfig;
using core::CoreHardwareInfo;

/* ****************************************************************************
 * Extern
 */

/* ****************************************************************************
 * Variable
 */
static uint32_t heapMemory[7168];

/* ****************************************************************************
 * Method
 */

//----------------------------------------------------------------------------
static SerialPort* lowlevel_getConsole(void) {
  CoreChip::getInstance().getPortC().setFunction(12, false);
  
  CoreUSART *console = new CoreUSART(chip::usart::UART5);
  SerialPort *serialPort = new SerialPort(*console);

  
  console->init();
  serialPort->open();
  serialPort->setBaudrate(128000);
  return serialPort;
}

//-----------------------------------------------------------------------------

void lowlevel(void) {
  System::mAllocator = mframe::sys::Stacker::construct(heapMemory, sizeof(heapMemory));
  CoreChip::instantiation();
  
  System::mKernel = new CmsisrtosKernel();
  System::mHardwareInfo = new CoreHardwareInfo();
  
  SerialPort *serialPort = lowlevel_getConsole();
  
  SystemConfig config;
  config.svchost.stackSize = 512;
  config.svchost.taskQuantity = 32;

  config.console.inputStream = &serialPort->getInputStream();
  config.console.outputStream = &serialPort->getOutputStream();
  config.console.sizeScanner = 512;
  config.console.sizePrintBiffer = 1024;
  
  chip::misc::MISC::setInterruptPriority(chip::misc::InterruptService::TMR2_GLOBAL, 3);
  chip::misc::MISC::setInterruptPriority(chip::misc::InterruptService::UART5, 15);
  System::setup(config);
}

/* ****************************************************************************
 * End of file
 */
