/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 * 
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************
 * Include
 */  

//-----------------------------------------------------------------------------
#include "mframe.h"
#include "core_arterytek_at32f415.h"

/* ****************************************************************************
 * Using
 */
 
//-----------------------------------------------------------------------------
using mframe::sys::Thread;
using core::CoreGeneralPin;
using core::CoreGeneralPort;
using core::OutputMode;
using core::CoreChip;
//-----------------------------------------------------------------------------

/* ****************************************************************************
 * Extern
 */

/* ****************************************************************************
 * Class
 */

/* ****************************************************************************
 * Variable
 */

static mframe::hal::GeneralPin* led[8];


/* ****************************************************************************
 * Method
 */


//-----------------------------------------------------------------------------
void setup(Thread* _this){
  for(uint32_t i=0; i<8; ++i){
    CoreGeneralPort& port = CoreChip::getInstance().getPortB();
    led[i] = new CoreGeneralPin(port, i);
    led[i]->setOutput();
    port.configOutput(i, OutputMode::SPEED_2M, false, false, false);
    led[i]->setLow();
  }
  

  _this->delay(100);
} 

//-----------------------------------------------------------------------------
void loop(Thread* _this){
  for(int i=0; i<8; ++i){
    led[i]->setToggle();
    _this->delay(200);
  }
  _this->delay(20);
}

/* ****************************************************************************
 * End of file
 */ 
