/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * WiimoteNunchuk.hpp created in 12 2008.
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


#ifndef __OPENKN_CONTROLLER__WIIMOTE_NUNCHUK_HPP__
#define __OPENKN_CONTROLLER__WIIMOTE_NUNCHUK_HPP__

/*
 * Internal Includes
 */
#include "InputController.hpp"

/*
 * External Includes
 */
#include <wiiuse.h>
#include <queue>

namespace kn{

	// Nunchuk buttons

	/**
	 * \brief No event
	 * \author Frankoi
	 */
	static const unsigned int EVENT_NONE=			   0x0;

	/**
	 * \brief State if button c of nunchuk have been released
	 * \author Frankoi
	 */
	static const unsigned int EVENT_BUTTON_C_UP=	   0x1;
	/**
	 * \brief State if button c of nunchuk have been pressed
	 * \author Frankoi
	 */
	static const unsigned int EVENT_BUTTON_C_DOWN=	   0x2;
	/**
	 * \brief State if button z of nunchuk have been released
	 * \author Frankoi
	 */
	static const unsigned int EVENT_BUTTON_Z_UP=	   0x4;
	/**
	 * \brief State if button z of nunchuk have been pressed
	 * \author Frankoi
	 */
	static const unsigned int EVENT_BUTTON_Z_DOWN=	   0x8;

	/**
	 * \brief Structure to save motion's parameters
	 *
	 * Parameters are nearly the same for wiimote and nunchuk
	 * \image html wiimotemotion.png "Motions of the wiimote" width=8cm
	 * \image latex wiimotemotion.eps  "Motions of the wiimote" width=8cm
	 * \author Frankoi
	 * 
	 */
/*	struct WiimoteMotion{
	float roll; // Movement around Y axis
	float pitch; // Movement around X axis
	float yaw; // Movement around Z axis
	float absoluteroll;
	float absolutepitch;
	float xforce; // Force applied along X axis
	float yforce; // Force applied along Y axis
	float zforce; // Force applied along Z axis
	};*/

	/**
	 * \brief Structure to save the parameters ralated to the nunchuk's joystick
	 * 
	 */
	/*struct WiimoteJoystick{
	  float angle; // Angle of the joystick 
	  float magnitude; // Distance of the stick from default position 
	  };*/

	/**
	 * \brief Class for Nunchuk control
	 * 
	 */
	class Nunchuk : public InputController{

	private:

		std::queue<unsigned int> eventsqueue; /** Queue for events from the nunchuk */

		static const unsigned int maxevents = 10; /** Number max of events int he queue */

		wiimote * wm; /** Pointer to the wiimote with which the nunchuk is connected */

	public:
		/**
		 * \brief Default constructor
		 *
		 * \author Frankoi
		 * 
		 */
		Nunchuk(void):InputController(){}

		/**
		 * \brief Constructor for nunchuk.
		 *
		 * \param wiimote the wiimote with which the nunchuk is connected
		 *
		 * \author Frankoi
		 * 
		 */
		Nunchuk(wiimote* wiimote);

		/**
		 * \brief Destructor for nunchuk
		 *
		 * \author Frankoi
		 * 
		 */
		~Nunchuk(void){clearEvents();}

		/**
		 * \brief Add an event for the nunchuk.
		 * \author Frankoi
		 * 
		 */
		void addEvent(const unsigned int& event);

		/**
		 * \brief Delete all events of the queue.
		 *
		 * \author Frankoi
		 * 
		 */
		void clearEvents(void);

		/**
		 * \brief Return the oldest event of the queue.
		 * 
		 * The event is removed from the queue
		 *
		 * \return the oldest event 
		 *
		 * \author Frankoi
		 */
		unsigned int popEvent(void) { if(eventsqueue.empty()){ return EVENT_NONE; this->updateAsNotUpdated();} unsigned int ev = eventsqueue.front(); eventsqueue.pop(); return ev;}

		/**
		 * \brief Return the oldest event of the queue.
		 *
		 * \return the oldest event
		 * 
		 * \author Frankoi
		 */
		unsigned int topEvent(void) { if(eventsqueue.empty()){ return EVENT_NONE; this->updateAsNotUpdated();} return eventsqueue.front();}

		/**
		 * \brief Should return the oldest error of the queue. The error should be removed from the queue.
		 *
		 * Error managing is not implemented because there is no error message for the moment.
		 * However the method is required because of InputController class heritage
		 *
		 * \return 0
		 *
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
		 *
		 * \author Frankoi
		 */
		unsigned int topError(void) {return 0;}

		/**
		 * \brief Return the roll value of the nunchuck
		 *
		 * In degree and between -180 to 180. Value is smoothed by the wiiuse interface
		 *
		 * \return roll
		 *
		 * \author Frankoi
		 */
		float getRoll(void)const{if(wm->exp.type==EXP_NUNCHUK)return wm->exp.nunchuk.orient.roll; return 0.0;}

		/**
		 * \brief Return the absolute roll value of the nunchuck
		 *
		 * In degree and between -180 to 180. It is the value directly emitted by the nunchuck 
		 *
		 * \return absolute roll
		 *
		 * \author Frankoi
		 */
		float getAbsoluteRoll(void)const{if(wm->exp.type==EXP_NUNCHUK)return wm->exp.nunchuk.orient.a_roll; return 0.0;}

		/**
		 * \brief Return the pitch value of the nunchuck
		 *
		 * In degree and between -180 to 180. Value is smoothed by the wiiuse interface
		 *
		 * \return pitch
		 *
		 * \author Frankoi
		 */
		float getPitch(void)const{if(wm->exp.type==EXP_NUNCHUK)return wm->exp.nunchuk.orient.pitch; return 0.0;}

		/**
		 * \brief Return the absolute pitch value of the nunchuck
		 *
		 * In degree and between -180 to 180. It is the value directly emitted by the nunchuck 
		 *
		 * \return absolute pitch
		 *
		 * \author Frankoi
		 */
		float getAbsolutePitch(void)const{if(wm->exp.type==EXP_NUNCHUK)return wm->exp.nunchuk.orient.a_pitch; return 0.0;}

		/**
		 * \brief Return acceleration on X axis
		 *
		 * The accelerometer is sensitive to within +/- 3 gravity units.
		 *
		 * \return X axis acceleration
		 *
		 * \author Frankoi
		 */
		float getXForce(void)const{if(wm->exp.type==EXP_NUNCHUK)return wm->exp.nunchuk.gforce.x; return 0.0;}

		/**
		 * \brief Return acceleration on Y axis
		 *
		 * The accelerometer is sensitive to within +/- 3 gravity units.
		 *
		 * \return Y axis acceleration
		 *
		 * \author Frankoi
		 */
		float getYForce(void)const{if(wm->exp.type==EXP_NUNCHUK)return wm->exp.nunchuk.gforce.y; return 0.0;}

		/**
		 * \brief Return acceleration on Z axis
		 *
		 * The accelerometer is sensitive to within +/- 3 gravity units.
		 *
		 * \return Z axis acceleration
		 *
		 * \author Frankoi
		 */
		float getZForce(void)const{if(wm->exp.type==EXP_NUNCHUK)return wm->exp.nunchuk.gforce.z; return 0.0;}

		// Seems to be useless
		// WiimoteMotion getMotion(void)const;

		/**
		 * \brief Returns the angle at which the joystick is being held
		 *
		 * Straight up is 0 degrees, to the right is 90 degrees, down is 180 degrees, and to the left is 270 degrees.
		 *
		 * The angle can often be 'not a number' (nan). This may occur if the joystick is in the central position. 
		 *
		 * \return angle of the joystick
		 *
		 * \author Frankoi
		 */
		float getJoystickAngle(void)const{if(wm->exp.type==EXP_NUNCHUK)return wm->exp.nunchuk.js.ang; return 0.0;}

		/**
		 * \brief Returns the magnitude at which the joystick is being held
		 *
		 * In the center is 0, and at the far edges is 1. So if the magnitude is 0.5 then the joystick is half way between the middle and outter edge.
		 *
		 * \return magnitude of the joystick
		 *
		 * \author Frankoi
		 */
		float getJoystickMagnitude(void)const{if(wm->exp.type==EXP_NUNCHUK)return wm->exp.nunchuk.js.mag; return 0.0;}

		/**
		 * \brief Returns if the nunchuck is connected or not
		 *
		 * \return true or false depending on nunchuck connection
		 *
		 * \author Frankoi
		 */
		bool isConnected(void)const{return (wm->exp.type==EXP_NUNCHUK);}

			

	};

}


#endif
