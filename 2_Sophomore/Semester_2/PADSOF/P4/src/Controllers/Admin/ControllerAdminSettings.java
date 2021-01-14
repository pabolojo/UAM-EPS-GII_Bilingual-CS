package Controllers.Admin;

import Model.App.Application;
import javax.swing.*;
import static View.MainView.MainView;

import java.util.Date;

import View.Views.*;

/**
 * This Controller counts with the functionalities about settings for the
 * administrator
 *
 *
 */
public class ControllerAdminSettings {
	private JPanel view;

	/**
	 * This is the controller for the PanelAdminSettings View, with the functions
	 * that the view needs
	 * 
	 * @param view PanelAdmin view
	 */

	public ControllerAdminSettings(JPanel view) {
		this.view = view;
	}

	/**
	 * This methods sets the threhold of the applocation by calling the setter in
	 * the app
	 * 
	 * @param threshold boolean to accept or reject the project
	 */

	public void bSetThreshold(String threshold) {
		Application.setThreshold(threshold);
	}

	/**
	 * This method exits the logged account, moves to the signIn view
	 */
	public void bSignOut() {
		Application.signOut();
		MainView.setView(new PanelSignIn());
	}

	/**
	 * This methods sets the date of the applocation by calling the setter in the
	 * app
	 * 
	 * @param value boolean to accept or reject the project
	 */
	public void setDate(Date value) {
		Application.setDate(value);
	}
}
