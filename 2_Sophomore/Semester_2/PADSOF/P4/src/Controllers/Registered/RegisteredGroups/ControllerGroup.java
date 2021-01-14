package Controllers.Registered.RegisteredGroups;

import Model.Modules.*;
import Model.App.Application;
import View.Views.Registered.RegisteredGroups.PanelRegisteredCreateGroup;
import View.Views.Registered.RegisteredGroups.PanelRegisteredGroups;

import static View.MainView.MainView;

/**
 * This Controller counts with the functionalities for Groups
 *
 *
 */

public class ControllerGroup {

	private PanelRegisteredGroups view;
	Application app = Application.getApplication();

	/**
	 * This is the controller for the Groups View, with the functions that the view
	 * needs
	 * 
	 * @param view RegisteredGroup view
	 */

	public ControllerGroup(PanelRegisteredGroups view) {
		this.view = view;
	}

	/**
	 * This method allows the user to join the group with the passed name as
	 * argument by calling the application method
	 * 
	 * @param name name of the group to join
	 * @return true if the user joins the application
	 */
	public boolean join(String name) {
		return Application.joinGroup(name);
	}

	/**
	 * Method to get the searched group by the passed name
	 * 
	 * @param name name of the group to get the info of
	 * @return Group asked for information
	 */
	public Group getInfo(String name) {
		return Application.getGroupByName(name, app.getGroup());
	}

	/**
	 * This method creates a group by calling the method in the application
	 * 
	 * @param name        name of the new group
	 * @param description description of the new group
	 * @param father      father of the new group (can be null if its a root)
	 */

	public void create(String name, String description, String father) {
		boolean result;
		if (father.length() == 0) {
			result = Application.createGroup(name, description);
		} else {
			result = Application.createGroup(name, description, father);
		}
		if (result) {
			MainView.unStackView();
			this.view.update();
		}
	}

	/**
	 * Unstacks the view to the previous one.
	 */

	public void newGroup() {
		MainView.stackView(new PanelRegisteredCreateGroup(this));
	}

	/**
	 * Home method to go to the primary view.
	 */

	public void home() {
		MainView.unStackView();
		this.view.update();
	}

}
