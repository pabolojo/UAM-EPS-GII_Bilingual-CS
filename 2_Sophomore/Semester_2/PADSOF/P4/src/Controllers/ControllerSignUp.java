package Controllers;

import Model.App.Application;
import javax.swing.*;
import View.Views.PanelSignIn;

import static View.MainView.MainView;

/**
 * This Controller counts with the functionalities for signing Up in the appl
 *
 *
 */

public class ControllerSignUp {

	private JPanel view;

	/**
	 * This is the controller for the SignUp View, with the functions that the view
	 * needs
	 * 
	 * @param view SignUp view
	 */

	public ControllerSignUp(JPanel view) {
		this.view = view;
	}

	/**
	 * This is the controller for the SignUp View, with the functions that the view
	 * needs
	 * 
	 * @param user username of the user account
	 * @param id   id of the user account
	 * @param pwd  password of the user account
	 * @param psw2 repetition of the password
	 */

	public void bSignUp(String user, String id, String pwd, String psw2) {

		if (Application.signUp(user, pwd, psw2, id)) {
			MainView.setView(new PanelSignIn());
		}
	}

	/**
	 * Method to change the view to the signIn.
	 */

	public void bSignIn() {
		MainView.setView(new PanelSignIn());
	}
}
