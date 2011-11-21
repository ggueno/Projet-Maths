/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * WiimoteManager.cpp created in 12 2008.
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

/*********************************************************
 * Inclusions
\*********************************************************/

#include "WiimoteManager.hpp"
#include "ControllerException.hpp"

#include <boost/bind.hpp>


namespace kn {

	WiimoteManager::WiimoteManager(void){
		wiimotes=0;
		wiimoteobservers=0;
		treatevents = false;
		maxnumberofwiimotes = 0;
		numberofwiimotes = 0;
        thrd = 0;
	}
		
	WiimoteManager::~WiimoteManager(void){
		stop();
	}

	void WiimoteManager::launch(const unsigned int& maxtime, 
								const unsigned int& maxwiimotes){

		maxnumberofwiimotes = maxwiimotes;

		// Initialize an array of wiimote objects.
		wiimotes = wiiuse_init(maxnumberofwiimotes);
			
		// Find wiimote devices during maxtime seconds
		numberofwiimotes = wiiuse_find(wiimotes, maxnumberofwiimotes, maxtime);
		if (!numberofwiimotes) throw ControllerException("No wiimote found","WiimoteManager");

		// Connect to the wiimotes
		int connected = wiiuse_connect(wiimotes, numberofwiimotes);
		if (!connected) throw ControllerException("Unable to connect wiimotes","WiimoteManager");

		wiimoteobservers = new Wiimote[numberofwiimotes];

		for(unsigned int i = 0; i < numberofwiimotes; ++i)
			wiimoteobservers[i] = Wiimote(wiimotes[i]);

		// Launch 
		treatevents=true;
		thrd = new boost::thread(boost::bind(&WiimoteManager::handleEvents, this));
	}

	void WiimoteManager::stop(void){
		if(thrd){
			treatevents = false;
			thrd->join();
			delete thrd;
			thrd = 0;
		}

		if(wiimoteobservers) delete[] wiimoteobservers;
		wiimoteobservers = 0;

		if(wiimotes) wiiuse_cleanup(wiimotes, maxnumberofwiimotes);
		wiimotes = 0;
					
		maxnumberofwiimotes = numberofwiimotes = 0;

	}	 


	Wiimote& WiimoteManager::getWiimote(const unsigned int& i){
		if(i >= numberofwiimotes) throw ControllerException("No such wiimote","getWiimote");
		return wiimoteobservers[i];
	}


	/*void handle_ctrl_status(struct wiimote_t* wm){
	  printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);
			
	  printf("attachment:	   %i\n", wm->exp.type);
	  printf("speaker:		   %i\n", WIIUSE_USING_SPEAKER(wm));
	  printf("ir:			   %i\n", WIIUSE_USING_IR(wm));
	  printf("leds:			   %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
	  printf("battery:		   %d %%\n", int(100 * wm->battery_level));
	  }*/


	void WiimoteManager::handle_event(struct wiimote_t* wm, const unsigned int& id){

		// Wiimote buttons
		if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) wiimoteobservers[id].addEvent(EVENT_BUTTON_A_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_A)) wiimoteobservers[id].addEvent(EVENT_BUTTON_A_UP);

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) wiimoteobservers[id].addEvent(EVENT_BUTTON_B_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_B)) wiimoteobservers[id].addEvent(EVENT_BUTTON_B_UP);

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) wiimoteobservers[id].addEvent(EVENT_BUTTON_UP_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_UP)) wiimoteobservers[id].addEvent(EVENT_BUTTON_UP_UP);

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) wiimoteobservers[id].addEvent(EVENT_BUTTON_DOWN_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_DOWN)) wiimoteobservers[id].addEvent(EVENT_BUTTON_DOWN_UP); 

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT)) wiimoteobservers[id].addEvent(EVENT_BUTTON_LEFT_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_LEFT)) wiimoteobservers[id].addEvent(EVENT_BUTTON_LEFT_UP);

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT)) wiimoteobservers[id].addEvent(EVENT_BUTTON_RIGHT_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_RIGHT)) wiimoteobservers[id].addEvent(EVENT_BUTTON_RIGHT_UP);

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) wiimoteobservers[id].addEvent(EVENT_BUTTON_MINUS_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_MINUS)) wiimoteobservers[id].addEvent(EVENT_BUTTON_MINUS_UP);

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) wiimoteobservers[id].addEvent(EVENT_BUTTON_PLUS_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_PLUS)) wiimoteobservers[id].addEvent(EVENT_BUTTON_PLUS_UP);

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) wiimoteobservers[id].addEvent(EVENT_BUTTON_ONE_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_ONE)) wiimoteobservers[id].addEvent(EVENT_BUTTON_ONE_UP);

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) wiimoteobservers[id].addEvent(EVENT_BUTTON_TWO_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_TWO)) wiimoteobservers[id].addEvent(EVENT_BUTTON_TWO_UP);

		if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME)) wiimoteobservers[id].addEvent(EVENT_BUTTON_HOME_DOWN);
		if (IS_RELEASED(wm, WIIMOTE_BUTTON_HOME)) wiimoteobservers[id].addEvent(EVENT_BUTTON_HOME_UP);


		// Nunchuck buttons
		if(wiimoteobservers[id].getNunchuk().isConnected()){
			struct nunchuk_t* nc = (nunchuk_t*)&wm->exp.nunchuk;
				
			if (IS_PRESSED(nc, NUNCHUK_BUTTON_C)) wiimoteobservers[id].getNunchuk().addEvent(EVENT_BUTTON_C_DOWN);
			if (IS_RELEASED(nc, NUNCHUK_BUTTON_C)) wiimoteobservers[id].getNunchuk().addEvent(EVENT_BUTTON_C_UP);
				
			if (IS_PRESSED(nc, NUNCHUK_BUTTON_Z)) wiimoteobservers[id].getNunchuk().addEvent(EVENT_BUTTON_Z_DOWN);
			if (IS_RELEASED(nc, NUNCHUK_BUTTON_Z)) wiimoteobservers[id].getNunchuk().addEvent(EVENT_BUTTON_Z_UP);
		}
	}
		

	void WiimoteManager::handleEvents(void){
		while(treatevents){
			// Check events
			if (wiiuse_poll(wiimotes, numberofwiimotes)) 
				for(unsigned int i = 0; i < numberofwiimotes; ++i){
					switch (wiimotes[i]->event) {
					case WIIUSE_EVENT:
						// a generic event occured
						handle_event(wiimotes[i],i);
						break;
						
					case WIIUSE_STATUS:
						// a status event occured
						//handle_ctrl_status(wiimotes[i]);
						break;

					case WIIUSE_DISCONNECT:
					case WIIUSE_UNEXPECTED_DISCONNECT:
						// the wiimote disconnected
						break;

					case WIIUSE_NUNCHUK_INSERTED:
					case WIIUSE_NUNCHUK_REMOVED:
						//wiimoteobservers[i].getNunchuk().checkConnected();
						break;

						//case WIIUSE_CLASSIC_CTRL_INSERTED:
						//case WIIUSE_CLASSIC_CTRL_REMOVED:
						//wiimoteobservers[i].setExpansion(EXP_CLASSIC);
						//break;

						//case WIIUSE_GUITAR_HERO_3_CTRL_INSERTED:
						//case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
						//wiimoteobservers[i].setExpansion(EXP_GUITAR_HERO_3);
						//break;

					default:
						break;


					}
				}
		}
	}


}
