/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * WiimoteManager.hpp created in 12 2008.
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

#ifndef __OPENKN_CONTROLLER__WIIMOTE_MANAGER_HPP__
#define __OPENKN_CONTROLLER__WIIMOTE_MANAGER_HPP__

#include "Wiimote.hpp"


/*
 * External Includes
 */
#include <boost/thread.hpp>


/*
 * Namespace
 */
namespace kn{


	/**
	 * \brief Wiimotes manager
	 *
	 * \author Frankoi
	 */

	class WiimoteManager{

	private :

		/** Array of wiiuse wiimotes */
		wiimote** wiimotes;

		/** Maximum number of connected wiimotes */
		unsigned int maxnumberofwiimotes;
		
		/** Number of connected wiimotes */		 
		unsigned int numberofwiimotes;

		/** Array of wiimotes */
		Wiimote* wiimoteobservers;

	public :

		/** 
		 * \brief  Constructor
		 *
		 * \author Frankoi
		 * 
		 */
		WiimoteManager(void);

		/**
		 * \brief Destructor 
		 *
		 * Stops the wiimote with stop() method
		 *
		 * \author Frankoi
		 */
		~WiimoteManager(void);

		/**
		 * \brief Launches wiimote connection anf events handling 
		 *
		 * \param maxtime maximum time for wiimotes detection (in seconds)
		 * \param maxwiimotes maximum number of connected wiimote
		 *
		 * \author Frankoi
		 */ 
		void launch(const unsigned int& maxtime = 3, const unsigned int& maxwiimotes = 4);

		/**
		 * \brief Stops wimmotes connections and event treatment
		 *
		 * \author Frankoi
		 */ 
		void stop(void);

		/**
		 * \brief Returns a specific active wiimote
		 *
		 * \param i wiimote's id (lower than getWiimoteNumber())
		 *
		 * \author Frankoi
		 */ 
		Wiimote& getWiimote(const unsigned int& i = 0);

		/**
		 * \brief Returns the number of active wiimotes
		 *
		 * \return number of active wiimotes
		 *
		 * \author Frankoi
		 */ 
		unsigned int getWiimoteNumber(void){return numberofwiimotes;}

	private :

		/** Thread */
		boost::thread *thrd;
 
		/** Events' treatment status */
		volatile bool treatevents;
		
		/**
		 * \brief Checks events for each connected wiimote
		 *
		 * It is applied in a thread
		 *
		 * \author Frankoi
		 */ 
		void handleEvents(void);

		/**
		 * \brief Updates status of a connected wiimote
		 *
		 * Called by handleEvents()
		 *
		 * \param wm a wiimote
		 * \param id id of the current treated wiimote
		 *
		 * \author Frankoi
		 */ 
		void handle_event(struct wiimote_t* wm, const unsigned int& id);
	
	};
}

#endif
