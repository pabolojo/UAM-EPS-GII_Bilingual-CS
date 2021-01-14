package Controllers.Registered.RegisteredProjects;

import Model.Modules.*;
import View.Views.Registered.RegisteredProjects.PanelRegisteredCreateProject;
//import View.Views.Registered.RegisteredGroups.PanelRegisteredCreateProject;
import View.Views.Registered.RegisteredProjects.PanelRegisteredProjects;
import View.Views.Registered.RegisteredProjects.ProjectsMoreInfo;
import Model.App.Application;
import static Model.App.Application.INSTANCE;

import View.MainView;

import javax.swing.JComboBox;
import javax.swing.JOptionPane;

/**
 * This Controller counts with the functionalities of projects in the
 * application
 *
 *
 */
public class ControllerProject {

	private PanelRegisteredProjects view;
	Application app = Application.getApplication();

	/**
	 * This is the controller for the Project View, with the functions that the view
	 * needs
	 * 
	 * @param view PanelRegisteredProjects view
	 */
	public ControllerProject(PanelRegisteredProjects view) {
		this.view = view;
	}

	/**
	 * Method to subscribe into a project by calling the subscribe mehtod in the
	 * application
	 * 
	 * @param name name of the project
	 * @return true if the user subscribe into the project
	 */

	public boolean subscribe(String name) {
		return Application.subscribe(name);
	}

	/**
	 * Method to look for the project in the appplication of a group by calling the
	 * getProjectByName mehtod in the application
	 * 
	 * @param name name of the project
	 * @return the project
	 */
	public Project getInfo(String name) {
		return Application.getProjectByName(name, app.getProjects());
	}

	/**
	 * Method to create an infrastructure project by calling the
	 * createInfrastructureProject mehtod in the application
	 * 
	 * @param name         name of the project
	 * @param description  description of the project
	 * @param budget       budget of the project
	 * @param image        image name loaded by the view
	 * @param neighborhood neighborhood in which the project is going to be develop
	 * @param groupName    name of the group that creates the project
	 * 
	 * 
	 */
	public void infrastructure(String name, String description, double budget, String image, String neighborhood,
			String groupName) {
		if (groupName.length() == 0) {
			if (Application.createInfrastructureProject(name, description, budget, image, neighborhood)) {
				MainView.unStackView();
			}
		} else {
			if (Application.createInfrastructureProject(name, description, budget, image, neighborhood, groupName)) {
				MainView.unStackView();
			}
		}
	}

	/**
	 * Method to create an infrastructure project by calling the
	 * createInfrastructureProject mehtod in the application
	 * 
	 * @param name        name of the project
	 * @param description description of the project
	 * @param budget      budget of the project
	 * @param aim         aim of the project
	 * @param socialGroup socialGroup for which it is intended
	 * @param groupName   name of the group that creates the project
	 * 
	 * 
	 */
	public void social(String name, String description, double budget, Boolean aim, String socialGroup,
			String groupName) {
		if (groupName.length() == 0) {
			if (Application.createSocialProject(name, description, budget, aim, socialGroup)) {
				MainView.unStackView();
			}
		} else {
			if (Application.createSocialProject(name, description, budget, aim, socialGroup, groupName)) {
				MainView.unStackView();
			}
		}
	}

	/** This method move to the PanelRegisteredCreateProject view */
	public void newProject() {
		MainView.stackView(new PanelRegisteredCreateProject(this));
	}

	/** This method move back in the stack of view */
	public void home() {
		MainView.unStackView();
	}

	/**
	 * Method to vote a project by calling the vote mehtod in the application
	 * 
	 * @param projectName name of the project
	 * @return true if everything works false otherwise
	 */
	public boolean vote(String projectName) {
		Registered user = (Registered) INSTANCE.getCurrentUser();
		String[] listMyGroups = new String[user.getMyCreatedGroups().size() + 1];
		listMyGroups[0] = "Individual Vote";

		int i = 1;
		for (Group g : user.getMyCreatedGroups()) {
			listMyGroups[i] = g.getName();
			i++;
		}
		JComboBox<String> myGroups = new JComboBox<String>(listMyGroups);

		if (JOptionPane.showConfirmDialog(this.view, myGroups, "Select vote type", JOptionPane.YES_NO_OPTION,
				JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION) {
			String selectedGroup = (String) myGroups.getSelectedItem();
			if (!selectedGroup.equals("Individual Vote")) {
				return Application.voteProject(projectName, selectedGroup);
			} else {
				return Application.voteProject(projectName);
			}
		}
		return false;
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
