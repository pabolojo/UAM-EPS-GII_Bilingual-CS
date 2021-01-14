package Controllers.Admin;

import Model.App.Application;
import View.MainView;
import View.Views.Registered.RegisteredProjects.ProjectsMoreInfo;

import javax.swing.*;

/**
 * This Controller counts with the functionalities about projects for the
 * administrator
 *
 *
 */
public class ControllerAdminProject {
	private JPanel view;

	/**
	 * This is the controller for the PanelAdmin View, with the functions that the
	 * view needs
	 * 
	 * @param view PanelAdmin view
	 */
	public ControllerAdminProject(JPanel view) {
		this.view = view;
	}

	/**
	 * This is the controller for the PanelAdmin View, with the functions that the
	 * view needs
	 * 
	 * @param project Name of the project to be accepted or rejected
	 * @param reason  reason because the the project is accepted or rejected
	 * @param accept  boolean to accept or reject the project
	 */
	public void bAccept(String project, String reason, boolean accept) {
		Application.adminAcceptProject(project, reason, accept);
	}

	/**
	 * Method that opens the MoreInfo view about a project, displaying all the
	 * attributes of a project
	 * 
	 * @param project Project of which the information is wanted to be shown
	 */
	public void moreinfo(String project) {
		MainView.stackView(new ProjectsMoreInfo(project));
	}
}
