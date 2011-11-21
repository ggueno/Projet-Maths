/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Wiimote.hpp created in 12 2008.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/


#ifndef __OPENKN_CONTROLLER__WIIMOTE_HPP__
#define __OPENKN_CONTROLLER__WIIMOTE_HPP__

/*
 * Internal Includes
 */
#include "WiimoteNunchuk.hpp"

/*
 * External Includes
 */
#include <queue>
#include <iostream>

namespace kn{

	// Wiimote buttons
	static const unsigned int EVENT_BUTTON_UP_UP=	   0x4;
	static const unsigned int EVENT_BUTTON_UP_DOWN=	   0x8;
	static const unsigned int EVENT_BUTTON_DOWN_UP=	   0x10;
	static const unsigned int EVENT_BUTTON_DOWN_DOWN=  0x20;
	static const unsigned int EVENT_BUTTON_LEFT_UP=	   0x40;
	static const unsigned int EVENT_BUTTON_LEFT_DOWN=  0x80;
	static const unsigned int EVENT_BUTTON_RIGHT_UP=   0x100;
	static const unsigned int EVENT_BUTTON_RIGHT_DOWN= 0x200;
	static const unsigned int EVENT_BUTTON_PLUS_UP=	   0x400;
	static const unsigned int EVENT_BUTTON_PLUS_DOWN=  0x800;
	static const unsigned int EVENT_BUTTON_MINUS_UP=   0x1000;
	static const unsigned int EVENT_BUTTON_MINUS_DOWN= 0x2000;
	static const unsigned int EVENT_BUTTON_HOME_UP=	   0x4000;
	static const unsigned int EVENT_BUTTON_HOME_DOWN=  0x8000;
	static const unsigned int EVENT_BUTTON_ONE_UP=	   0x10000;
	static const unsigned int EVENT_BUTTON_ONE_DOWN=   0x20000;
	static const unsigned int EVENT_BUTTON_TWO_UP=	   0x40000;
	static const unsigned int EVENT_BUTTON_TWO_DOWN=   0x80000;
	static const unsigned int EVENT_BUTTON_A_UP=	   0x100000;
	static const unsigned int EVENT_BUTTON_A_DOWN=	   0x200000;
	static const unsigned int EVENT_BUTTON_B_UP=	   0x400000;
	static const unsigned int EVENT_BUTTON_B_DOWN=	   0x800000;

	// IR PARAMETERS
	static const unsigned int ASPECT_16_9 = 0x0;
	static const unsigned int ASPECT_4_3 = 0x1;
	static const unsigned int IR_POSITION_ABOVE = 0x0;
	static const unsigned int IR_POSITION_BELOW = 0x1;

	/**
	 * \brief Structure to save information about IR dots detected by the wiimote
	 *
	 * \author Frankoi
	 */
	struct WiimoteIRDot{
		unsigned int x,y; /** Corrected XY coordinates of the IR source converted from rx and ry*/
		short rx,ry; /** Position returned by the wiimote */
		size_t size; /** Size of the IR dot */
		bool visible; /** This is set to 1 if the IR source is visible, 0 if it is not */
	};

	/**
	 * \brief Information about the cursor computed from IR dot detection
	 *
	 * \author Frankoi
	 */
	struct WiimoteIRPointer{
		int x,y; /** Position of the cursor */
		float z; /** Depth of the cursor */
	};

	/**
	 * Class for Wiimote control
	 *
	 * \author Frankoi
	 */

	class Wiimote : public InputController{

	private:

		/**
		 * \brief Saves events
		 */
		std::queue<unsigned int> eventsqueue;

		/**
		 * \brief Maximum number of events in the queue
		 */		   
		static const unsigned int maxevents = 10;

		
		unsigned int expansion;

		/**
		 * \brief Wiiuse wiimote structure
		 */ 
		wiimote * wm;

		/**
		 * \brief Information about leds status
		 */ 
		int ledsstatus;

		/**
		 * \brief Information about rumble status
		 */ 
		bool rumble;

		/**
		 * \brief Information about IR status
		 */ 
		bool ir;

		/**
		 * \brief Information about data's smoothing
		 */ 
		bool smoothing;

		/**
		 * \brief Information about accelerations status
		 */ 
		bool accelerations;

		/**
		 * \brief Information about a connected nunchuck
		 */ 
		Nunchuk nunchuk;

	public:

		/**
		 * \brief Default constructor
		 * \author Frankoi
		 */
		Wiimote(void):InputController(){}

		/**
		 * \brief Constructor
		 *
		 * \param wiimote a pointer to a wiiuse wiimote descriptor
		 *
		 * \author Frankoi
		 */
		Wiimote(wiimote* wiimote);

		/**
		 * \brief Destructor
		 *
		 * \author Frankoi
		 */
		~Wiimote(void){clearEvents();wiiuse_disconnect(wm);}

		/**
		 * \brief Add a wiimote event to the event queue
		 *
		 * \param event event descriptor
		 *
		 * \author Frankoi
		 */
		void addEvent(const unsigned int& event);

		/**
		 * \brief Pop the oldest event in the queue
		 *
		 * The event is removed from the queue
		 *
		 * \return the oldest event
		 * \author Frankoi
		 */
		unsigned int popEvent(void) { if(eventsqueue.empty()){ return EVENT_NONE; this->updateAsNotUpdated();} unsigned int ev = eventsqueue.front(); eventsqueue.pop(); return ev;}

		/**
		 * \brief Pop the oldest event in the queue
		 *
		 * The event is kept in the queue
		 *
		 * \return the oldest event
		 * \author Frankoi
		 */
		unsigned int topEvent(void) { if(eventsqueue.empty()){ return EVENT_NONE; this->updateAsNotUpdated();} return eventsqueue.front();}

		/**
		 * \brief Return the oldest error of the queue.
		 *
		 * Error managing is not implemented because there is no error message for the moment.
		 * However the method is required because of InputController class heritage
		 *
		 * \return 0
		 * \author Frankoi
		 */
		unsigned int popError(void) {return 0;}

		/**
		 * \brief Return the oldest error of the queue.
		 *
		 * Error managing is not implemented because there is no error message for the moment.
		 * However the method is required because of InputController class heritage
		 *
		 * \return 0
		 * \author Frankoi
		 */
		unsigned int topError(void) {return 0;}

		/**
		 * \brief Removes all events in the queue
		 *
		 * \author Frankoi
		 */
	  void clearEvents(void);

		/**
		 * \brief Returns the expansion connected to the wiimote 
		 *
		 * \return the expansion's descriptor
		 *
		 * \author Frankoi
		 */		  
		unsigned int getExpansion(void)const{return expansion;}
				
		/**
		 * \brief Switches the rumble's status
		 *
		 * \author Frankoi
		 */	 
		void toggleRumble(void){wiiuse_toggle_rumble(wm); rumble=!rumble;}

		/**
		 * \brief Checkes if the rumble is on or off
		 *
		 * \return rumble status
		 *
		 * \author Frankoi
		 */ 
		bool isRumbleSet(void)const{return rumble;}


		/**
		 * \brief Switches the specific led's status
		 *
		 * \param id led's id (must be	1, 2, 3 or 4)
		 *
		 * \author Frankoi
		 */ 
		void toggleLED(const unsigned int& id);

		/**
		 * \brief Returns the status of a specific led
		 *
		 * \param id led's id (must be	1, 2, 3 or 4)
		 *
		 * \author Frankoi
		 */ 
		bool isLEDSet(const unsigned int& id)const;

		/**
		 * \brief Switches IR dots tracking status
		 *
		 * \author Frankoi
		 */ 
		void toggleIR(void){ir=!ir;wiiuse_set_ir(wm,ir);}

		/**
		 * \brief Returns IR dots tracking status
		 *
		 * \return IR dots tracking status
		 *
		 * \author Frankoi
		 */
		bool isIRSet(void)const{return ir;}

		/**
		 * \brief Returns IR dots tracking sensitivity value
		 *
		 * \return IR dots tracking sensitivity value
		 *
		 * \author Frankoi
		 */
		int getIRSensitivity(void)const{int lvl; WIIUSE_GET_IR_SENSITIVITY(wm,&lvl); return lvl;}

		/**
		 * \brief Sets IR dots tracking sensitivity value
		 *
		 * The camera sensitivity is a degree between 1 (lowest) and 5 (highest). The default is 3.
		 *
		 * \param lvl IR dots tracking sensitivity value
		 *
		 * \author Frankoi
		 */
		void setIRSensitivity(const int& lvl){wiiuse_set_ir_sensitivity(wm,lvl);}

		/**
		 * \brief Returns the number of detected IR dots
		 *
		 * \return the number of detected IR dots
		 *
		 * \author Frankoi
		 */
		unsigned int getDotsNumber(void) const {return wm->ir.num_dots;}

		/**
		 * \brief Returns data about a specif detected IR dot
		 *
		 * \param i id of a specific dot (lower than getDotsNumber())
		 *
		 * \return a specific dot information
		 *
		 * \author Frankoi
		 */
		WiimoteIRDot getDot(const unsigned int& i) const;

		/**
		 * \brief Returns values corresponding to conversion of IR dots into a cursor
		 *
		 * \return cursor information
		 *
		 * \author Frankoi
		 */
	  WiimoteIRPointer getPointer(void) const;
	  
		/**
		 * \brief Defines parameters for IR dots conversion into a cursor
		 *
		 * \param width window width
		 * \param height window height
		 * \param aspect window ratio (either ASPECT_4_3 or ASPECT_16_9)
		 * \param position sensor bar position related to screen (either IR_POSITION_BELOW or IR_POSITION_ABOVE)
		 *
		 * \author Frankoi
		 */
		void setIRParameters(const unsigned int& width, const unsigned int& height, const unsigned int& aspect=ASPECT_4_3, const unsigned int& position=IR_POSITION_BELOW);

		/**
		 * \brief Switches motion detection
		 *
		 * \author Frankoi
		 */
		void toggleMotion(void){accelerations = !accelerations; wiiuse_motion_sensing(wm,accelerations);}

		/**
		 * \brief Returns if motion detection is on or off
		 *
		 * \return if motion detection is set
		 *
		 * \author Frankoi
		 */
		bool isMotionSet(void)const{return accelerations;}

		/**
		 * \brief Switches to smooth motion detection
		 *
		 * \author Frankoi
		 */
	  void toggleSmoothAccelerations(void){if(smoothing) wiiuse_set_flags(wm,0,WIIUSE_SMOOTHING);  else wiiuse_set_flags(wm,WIIUSE_SMOOTHING,0);   smoothing = !smoothing;}

		/**
		 * \brief Return the roll value of the wiimote
		 *
		 * In degree and between -180 to 180. Value is smoothed by the wiiuse interface
		 *
		 * \return roll
		 *
		 * \author Frankoi
		 */
		float getRoll(void)const{return wm->orient.roll;}

		/**
		 * \brief Return the absolute roll value of the wiimote
		 *
		 * In degree and between -180 to 180. It is the value directly emitted by the wiimote
		 *
		 * \return absolute roll
		 *
		 * \author Frankoi
		 */
		float getAbsoluteRoll(void)const{return wm->orient.a_roll;}

		/**
		 * \brief Return the pitch value of the wiimote
		 *
		 * In degree and between -180 to 180. Value is smoothed by the wiiuse interface
		 *
		 * \return pitch
		 *
		 * \author Frankoi
		 */
		float getPitch(void)const{return wm->orient.pitch;}

		/**
		 * \brief Return the absolute pitch value of the wiimote
		 *
		 * In degree and between -180 to 180. It is the value directly emitted by the wiimote
		 *
		 * \return absolute pitch
		 *
		 * \author Frankoi
		 */
		float getAbsolutePitch(void)const{return wm->orient.a_pitch;}

		/**
		 * \brief Return the yaw value of the wiimote
		 *
		 * In degree and between -180 to 180. The value is computed using IR dots detection.
		 *
		 * \return yaw
		 *
		 * \author Frankoi
		 */
		float getYaw(void)const{return wm->orient.yaw;}

		/**
		 * \brief Return acceleration on X axis
		 *
		 * The accelerometer is sensitive to within +/- 3 gravity units.
		 *
		 * \return X axis acceleration
		 * \author Frankoi
		 */
		float getXForce(void)const{return wm->gforce.x;}

		/**
		 * \brief Return acceleration on Y axis
		 *
		 * The accelerometer is sensitive to within +/- 3 gravity units.
		 *
		 * \return Y axis acceleration
		 * \author Frankoi
		 */
		float getYForce(void)const{return wm->gforce.y;}

		/**
		 * \brief Return acceleration on Z axis
		 *
		 * The accelerometer is sensitive to within +/- 3 gravity units.
		 *
		 * \return Z axis acceleration
		 * \author Frankoi
		 */
		float getZForce(void)const{return wm->gforce.z;}
		//WiimoteMotion getMotion(void);

		/**
		 * \brief Prints some information about the wiimote
		 *
		 * \author Frankoi
		 */
		void showStatus(void);

		/**
		 * \brief Returns the nunchuk connected to the wiimote
		 *
		 * You have to check if the nunchuck is really connected
		 *
		 * \return the nunchuck
		 * \author Frankoi
		 */
		Nunchuk& getNunchuk(void){return nunchuk;}
	  
	  		/**
		 * \brief Output Wiimote infos
		 *
		 * \return the stream
		 * \author Pierre
		 */
	  friend std::ostream& operator<<(std::ostream & , const Wiimote&);

	};

}

#endif
