/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Wiimote.cpp created in 12 2008.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/
#include "Wiimote.hpp"
#include "ControllerException.hpp"

namespace kn {

	Wiimote::Wiimote(wiimote* wiimote)
		:InputController(),wm(wiimote){

		nunchuk = Nunchuk(wiimote);

		expansion = wm->exp.type; 
			
		rumble=false;
		wiiuse_rumble(wm,0);
		
		accelerations = true;
		wiiuse_motion_sensing(wm,accelerations);
		
		smoothing = true;
		
		ledsstatus=WIIMOTE_LED_NONE; 
		wiiuse_set_leds(wm,ledsstatus);
			
		ir = false;

	}


	void Wiimote::addEvent(const unsigned int& event){
		while(eventsqueue.size() >= maxevents){
			eventsqueue.pop();
		}
		eventsqueue.push(event);
		this->flagAsUpdated();
	}


	void Wiimote::clearEvents(void){
		while(eventsqueue.size() != 0){
			eventsqueue.pop();
		}
		this->updateAsNotUpdated();
	}

	bool Wiimote::isLEDSet(const unsigned int& id)const{
		if(id==1)
			return WIIUSE_IS_LED_SET(wm,1);
		if(id==2)
			return WIIUSE_IS_LED_SET(wm,2);
		if(id==3)
			return WIIUSE_IS_LED_SET(wm,3);
		if(id==4)
			return WIIUSE_IS_LED_SET(wm,4);
		return false;
	}


	void Wiimote::toggleLED(const unsigned int& id){
		int tmpstatus = WIIMOTE_LED_NONE;
		if(id==1) tmpstatus = WIIMOTE_LED_1;
		if(id==2) tmpstatus = WIIMOTE_LED_2;
		if(id==3) tmpstatus = WIIMOTE_LED_3;
		if(id==4) tmpstatus = WIIMOTE_LED_4;
		if(tmpstatus == WIIMOTE_LED_NONE) ledsstatus = WIIMOTE_LED_NONE;
		else ledsstatus ^= tmpstatus;
		wiiuse_set_leds(wm,ledsstatus);
	}

	WiimoteIRDot Wiimote::getDot(const unsigned int& i) const{
		if(i > wm->ir.num_dots) throw ControllerException("No such dot","getDot");
		WiimoteIRDot ird;
		ird.x = wm->ir.dot[i].x;
		ird.y = wm->ir.dot[i].y;
		ird.rx = wm->ir.dot[i].rx;
		ird.ry = wm->ir.dot[i].ry;
		ird.size = wm->ir.dot[i].size;
		ird.visible = wm->ir.dot[i].visible;
		return ird;
	}

	WiimoteIRPointer Wiimote::getPointer(void) const{
		WiimoteIRPointer irp;
		irp.x = wm->ir.x;
		irp.y = wm->ir.y;
		irp.z = wm->ir.z;
		return irp;
	}

	void Wiimote::setIRParameters(const unsigned int& width, 
								  const unsigned int& height, 
								  const unsigned int& aspect, 
								  const unsigned int& position){
		if(aspect==ASPECT_16_9)
			wiiuse_set_aspect_ratio(wm,WIIUSE_ASPECT_16_9); 
		else
			wiiuse_set_aspect_ratio(wm,WIIUSE_ASPECT_4_3); 
			  
		if(position==IR_POSITION_ABOVE)
			wiiuse_set_ir_position(wm,WIIUSE_IR_ABOVE);
		else
			wiiuse_set_ir_position(wm,WIIUSE_IR_BELOW);

		wiiuse_set_ir_vres(wm, width, height);
	}

/*	WiimoteMotion Wiimote::getMotion(void){
	WiimoteMotion acc;
	acc.roll = wm->orient.roll;
	acc.absoluteroll = wm->orient.a_roll;
	acc.pitch = wm->orient.pitch;
	acc.absolutepitch = wm->orient.a_pitch;
	acc.yaw = wm->orient.yaw;
	acc.xforce = wm->gforce.x;
	acc.yforce = wm->gforce.y;
	acc.zforce = wm->gforce.z;
	return acc;
	}*/


	void Wiimote::showStatus(void){
	  std::cout << *this << std::endl;
	}
  
  std::ostream& operator<<(std::ostream &os, const Wiimote &wiimote)
  {
    os << "--- WIIMOTE STATUS [wiimote id " << wiimote.wm->unid << "] ---"<< std::endl;
    os << "attachment:" ;
    switch(wiimote.wm->exp.type)
      {
      case EXP_NONE:
	os << "none";
	break;
      case EXP_NUNCHUK:
	os << "nunchuk";
	break;
      case EXP_CLASSIC:
	os << "classic";
	break;
      case EXP_GUITAR_HERO_3:
	os << "guitar hero 3";
	break;
      default:
	os << "unknown attachment";	
	break;
      }
    os << std::endl;
    os << "ir:" ;
    wiimote.ir ? os << "on" : os << "off";
    os << std::endl;
    os << "motion:";
    wiimote.accelerations ? os << "on": os << "off";
    os << std::endl;
    os << "leds:";
    WIIUSE_IS_LED_SET(wiimote.wm, 1) ? os << "on ": os << "off "; 
    WIIUSE_IS_LED_SET(wiimote.wm, 2) ? os << "on ": os << "off "; 
    WIIUSE_IS_LED_SET(wiimote.wm, 3) ? os << "on ": os << "off "; 
    WIIUSE_IS_LED_SET(wiimote.wm, 4) ? os << "on ": os << "off "; 
    os << std::endl;
    os << "battery:"<< int(100 * wiimote.wm->battery_level) << "%"<<std::endl;
    os << "smooth:" ;
    wiimote.wm->flags&WIIUSE_SMOOTHING? os << "on": os << "off";
    return os;
  }
}
