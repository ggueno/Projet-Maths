/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Inputcontroller.hpp created in 12 2008.
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

#ifndef __OPENKN_CONTROLLER__INPUT_CONTROLLER_HPP__
#define __OPENKN_CONTROLLER__INPUT_CONTROLLER_HPP__


/*
 * Internal Includes
 */
#include "ControllerException.hpp"

/*
 * External Includes
 */

/*
 * Namespace
 */
namespace kn{

	/**
	 * Abstract class for input device
	 */
	class InputController
	{

	protected :
		bool updatedFlag;
		/*!
		  \brief Marque le controlleur comme ayant été mis à jour
		*/
		virtual void flagAsUpdated(void) {updatedFlag = true;}
		/*!
		  \brief Vérifie si le controlleur a été mis à jour
		  \return true si le controlleur a été mis à jour et false sinon
		*/
		virtual void updateAsNotUpdated(void) {updatedFlag = false;}

	public:

		/*!
		  \brief Contructor
		*/
		InputController(void){updatedFlag=false;}

		/*!
		  \brief Virtual destructor
		*/
		virtual	 ~InputController(void){};

	public :
		/*!
		  \brief Vérifie si le controlleur a été mis à jour
		  \return true si le controlleur a été mis à jour et false sinon
		*/
		virtual bool hasBeenUpdated(void) { return updatedFlag;}

		/*
		 * Traitement génnérique des évenements
		 */

	public :
		/*!
		  \brief Retourne le code du premier élement de la file d'evenements et le retire.
		  \return  le code de l'evenement
		*/

		virtual unsigned int popEvent(void)=0; 

		/*!
		  \brief Retourne le code du premier élement de la file d'evenements
		  \return  le code de l'evenement
		*/
		virtual unsigned int topEvent(void)=0; 

		/*!
		  \brief Retourne le code du premier élement de la file d'erreurs et le retire.
		  \return  le code de l'erreur
		*/
		virtual unsigned int popError(void)=0; 

		/*!
		  \brief Retourne le code du premier élement de la file d'erreurs
		  \return  le code de l'erreur
		*/
		virtual unsigned int topError(void)=0; 

		  
	};
}


#endif
