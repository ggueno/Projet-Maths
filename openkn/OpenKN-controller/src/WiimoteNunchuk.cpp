/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * WiimoteNunchuk.cpp created in 12 2008.
 * Mail : biri@univ-mlv.fr					  
 *													   
 * This file is part of the OpenKraken-controller.
 *
 * The OpenKraken-controller is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-controller is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

#include "WiimoteNunchuk.hpp"
#include "ControllerException.hpp"

namespace kn {


	/*********************************
	 * Nunchuk Methods
	 *********************************/

	Nunchuk::Nunchuk(wiimote* wiimote)
		: InputController(){
		wm=wiimote;
	}

	void Nunchuk::addEvent(const unsigned int& event){
		while(eventsqueue.size() >= maxevents){
			eventsqueue.pop();
		}
		eventsqueue.push(event);
		this->flagAsUpdated();
	}

	void Nunchuk::clearEvents(void){
		while(eventsqueue.size() != 0){
			eventsqueue.pop();
		}
		this->updateAsNotUpdated();
	}

	/*WiimoteMotion Nunchuk::getMotion(void)const{
	  WiimoteMotion acc;
	  if(connected){
	  acc.roll = wm->exp.nunchuk.orient.roll;
	  acc.absoluteroll = wm->exp.nunchuk.orient.a_roll;
	  acc.pitch = wm->exp.nunchuk.orient.pitch;
	  acc.absolutepitch = wm->exp.nunchuk.orient.a_pitch;
	  acc.yaw = wm->exp.nunchuk.orient.yaw;
	  acc.xforce = wm->exp.nunchuk.gforce.x;
	  acc.yforce = wm->exp.nunchuk.gforce.y;
	  acc.zforce = wm->exp.nunchuk.gforce.z;
	  }else{
	  bzero(&acc,sizeof(WiimoteMotion));
	  }
	  return acc;
	  }*/

	/*WiimoteJoystick Nunchuk::getJoystick(void)const{
	  WiimoteJoystick js;
	  if(connected){
	  js.angle = wm->exp.nunchuk.js.ang;
	  js.magnitude = wm->exp.nunchuk.js.mag;
				
	  }else{
	  bzero(&js,sizeof(WiimoteJoystick));
	  }
	  return js;
	  }*/
}
