package Controllers.Admin;

import Model.App.Application;
import Model.Modules.Registered;

import javax.swing.*;

/**
 * This Controller counts with the functionalities about settings for the
 * administrator
 *
 *
 */
public class ControllerAdminUsers {
	private JPanel view;

	/**
	 * This is the controller for the PanelAdminUsers View, with the functions that
	 * the view needs
	 * 
	 * @param view PanelAdminUsers view
	 */

	public ControllerAdminUsers(JPanel view) {
		this.view = view;
	}

	/**
	 * This methods accepts or rejects a user by calling the method in the
	 * application
	 * 
	 * @param username username of the user to accept or reject
	 * @param accept   boolean to accept or reject the user
	 */

	public void bAccept(String username, boolean accept) {
		Application.adminAcceptUser(username, accept);
	}

	/**
	 * This methods ban or unbans a user in the application
	 * 
	 * @param r Registered user to be ban (if unbanned) or unbanned (if banned)
	 */

	public void bBan(Registered r) {
		if (r.isBanned()) {
			Application.unbanUser(r.getName());
		} else {
			Application.banUser(r.getName());
		}
	}
}
