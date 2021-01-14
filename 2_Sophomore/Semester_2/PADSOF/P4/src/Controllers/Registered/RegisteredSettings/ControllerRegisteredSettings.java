package Controllers.Registered.RegisteredSettings;

import Model.App.Application;
import javax.swing.*;
import static View.MainView.MainView;
import View.Views.*;

/**
 * This Controller counts with the functionalities for the settings of a
 * registered user
 *
 *
 */

public class ControllerRegisteredSettings {
	private JPanel view;

	/**
	 * This is the controller for the RegisteredSettings View, with the functions
	 * that the view needs
	 * 
	 * @param view RegisteredSettings view
	 */

	public ControllerRegisteredSettings(JPanel view) {
		this.view = view;
	}

	/**
	 * This methods changes the password of the current user by calling the method
	 * in the application
	 * 
	 * @param old  old password
	 * @param new1 new password
	 * @param new2 new password repeated
	 * @return true if the password has changed else false 
	 */

	public boolean bSetNewPassword(String old, String new1, String new2) {
		return Application.setNewPassword(old, new1, new2);
	}

	/**
	 * This methods logs out the signed account and moves to the signIn view
	 */

	public void bSignOut() {
		Application.signOut();
		MainView.setView(new PanelSignIn());
	}

}
