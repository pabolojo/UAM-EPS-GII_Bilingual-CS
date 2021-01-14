package Controllers.Registered.RegisteredProjects;

import Model.Modules.*;
import View.MainView;
import View.Views.Registered.RegisteredProjects.ProjectsMoreInfo;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import static Model.App.Application.INSTANCE;
import Model.App.Application;

/**
 * This Controller counts with the functionalities of MySupportedprojects in the
 * application
 *
 *
 */
public class ControllerMySupportedProjects {
	private JPanel view;

	/**
	 * This is the controller for MySupportedProject View, with the functions that
	 * the view needs
	 * 
	 * @param view ControllerMySupportedProjects view
	 */
	public ControllerMySupportedProjects(JPanel view) {
		this.view = view;
	}

	/**
	 * Method to subscribe into a project by calling the subscribe method in the
	 * application
	 * 
	 * @param name name of the project
	 */
	public void suscribe(String name) {
		Application.subscribe(name);
	}

	/**
	 * Method to getPopularity report of a project by calling the
	 * getPopularityReportsOfGroup method in the application
	 * 
	 * @param name name of the project
	 */
	public void popularity(String name) {
		Registered user = (Registered) INSTANCE.getCurrentUser();
		String[] listMyGroups = new String[user.getMyCreatedGroups().size() + 1];
		listMyGroups[0] = "Popularity single user";
		int i = 1;
		for (Group g : user.getMyCreatedGroups()) {
			listMyGroups[i] = g.getName();
			i++;
		}
		JComboBox<String> myGroups = new JComboBox(listMyGroups);
		if (JOptionPane.showConfirmDialog(this.view, myGroups, "Popularity type", JOptionPane.YES_NO_OPTION,
				JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION) {
			String selectedGroup = (String) myGroups.getSelectedItem();
			if (!selectedGroup.equals("Popularity single user")) {
				Application.getPopularityReportsOfGroup(selectedGroup);
			} else {
				Application.getPopularityReport(name);
			}
		}
	}

	/**
	 * Method to change to the more info view
	 * 
	 * @param name name of the project
	 */
	public void moreinfo(String name) {
		MainView.stackView(new ProjectsMoreInfo(name));
	}

}
