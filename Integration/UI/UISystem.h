//========= Copyright © 2014, Bryan Andrew King, All rights reserved. ============
#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H

#include <OIS.h>
#include <vector>
#include "UIRenderer.h"

/**
 * \class UISystem
 * \brief Manages all UI related renderers
 * \details Initializes all required noesis components and manages input for the UIRenderers.
 */
class UISystem : public OIS::KeyListener, public OIS::MouseListener
{
private:
	std::vector<UIRenderer*>	listener;	///< Input listeners
	int							currentUID;
	
	// Keyboard callbacks
	bool						keyPressed(const OIS::KeyEvent &e);
	bool						keyReleased(const OIS::KeyEvent &e);

	// Mouse callbacks
	bool						mouseMoved(const OIS::MouseEvent &arg);
	bool						mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool						mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

public:
	/**
	 * \brief Initializes noesis.
	 */
	UISystem();
	virtual ~UISystem();

	/**
	 * \brief Generates a new unique id
	 * \return id
	 */
	int						GenerateUID();

	/**
	 * \brief Registers a listener for input events
	 * \warning The specified renderer must have an unique id assigned
	 * \param[in] uiRenderer Listener
	 */
	void					AddInputListener(UIRenderer* &uiRenderer);
	/**
	 * \brief Removes a listener for input events
	 * \param[in] uid	The uid of the renderer that will be removed
	 */
	void					RemoveInputListener(const int uid);
};

#endif//UI_SYSTEM_H