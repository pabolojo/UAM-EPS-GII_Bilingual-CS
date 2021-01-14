package Controllers.Registered.RegisteredGroups;

import Model.App.Application;
import javax.swing.*;
import Model.Modules.*;
import View.Views.Registered.RegisteredGroups.PanelRegisteredAffinityReport;
import static Model.App.Application.INSTANCE;

import static View.MainView.MainView;

/**
 * This Controller counts with the functionalities for the groups of a
 * registered user
 *
 *
 */
public class ControllerMyGroup {
	private JPanel view;

	/**
	 * This is the controller for the the Groups of a registered user View, with the
	 * functions that the view needs
	 * 
	 * @param view RegisteredGroup view
	 */

	public ControllerMyGroup(JPanel view) {
		this.view = view;
	}

	/**
	 * This method allows the user to leave the group with the passed name as
	 * argument by calling the application method
	 * 
	 * @param name name of the group to leave
	 * @return true if the user leaves the group false otherwise 
	 */

	public boolean leave(String name) {
		return Application.leaveGroup(name);
	}

	/**
	 * This method allows the user to get more info about the group with the passed
	 * name as argument by calling the application method
	 * 
	 * @param name name of the group to leave
	 * @return Group asked for the information
	 */
	public Group getInfo(String name) {
		return Application.getGroupByName(name, INSTANCE.getGroup());
	}

	/**
	 * This method allows the user to move to a different view to ask for a affinity
	 * report between two groups
	 */
	public void affinityReport() {
		MainView.stackView(new PanelRegisteredAffinityReport(this));
	}

	/**
	 * Home method to go to the primary view.
	 */

	public void home() {
		MainView.unStackView();
	}

	/**
	 * Method to ask for an affinity report between two groups by calling to the
	 * method in the application.
	 * @param g1 group 1 name 
	 * @param g2 group 2 name 
	 */

	public void askAffinity(String g1, String g2) {
		if (g1.equals("Select") || g2.equals("Select")) {
			INSTANCE.getCurrentUser()
					.sendNotification(new Notification((Object) INSTANCE, "You have to select both groups"));
			return;
		} else {
			Application.getAffinityReport(g1, g2);
		}
	}

}
