package Controllers;

import Model.App.Application;
import Model.Modules.Admin;

import javax.swing.*;
import static View.MainView.MainView;
import static Model.App.Application.INSTANCE;
import View.Views.Admin.PanelAdmin;
import View.Views.Registered.PanelRegistered;
import View.Views.PanelSignUp;

/**
 * This Controller counts with the functionalities for signing in the appl
 *
 *
 */

public class ControllerSingIn {

	private JPanel view;

	/**
	 * This is the controller for the SignIn View, with the functions that the view
	 * needs
	 * 
	 * @param view SignIn view
	 */

	public ControllerSingIn(JPanel view) {
		this.view = view;
	}

	/**
	 * Method to signIn the application by calling the signIn method in the
	 * application.
	 * 
	 * @param user username to signin
	 * @param pwd  password to signin
	 */

	public void bSignIn(String user, String pwd) {

		if (Application.signIn(user, pwd)) {
			if (INSTANCE.getCurrentUser() instanceof Admin) {
				MainView.setView(new PanelAdmin());
			} else {
				MainView.setView(new PanelRegistered());
			}
		}

	}

	/**
	 * Method to change the view to the signUp.
	 */

	public void bSignUp() {
		MainView.setView(new PanelSignUp());
	}
}
