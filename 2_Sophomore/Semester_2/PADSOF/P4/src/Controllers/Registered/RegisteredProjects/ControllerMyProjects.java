package Controllers.Registered.RegisteredProjects;

import Model.App.Application;
import javax.swing.*;
import Model.Modules.*;
import View.Views.Registered.RegisteredProjects.ProjectsMoreInfo;
import es.uam.eps.sadp.grants.InvalidRequestException;

import static Model.App.Application.INSTANCE;

import static View.MainView.MainView;

import java.io.IOException;

/**
 * This Controller counts with the functionalities of Myprojects in the
 * application
 *
 *
 */
public class ControllerMyProjects {
	private JPanel view;

	/**
	 * This is the controller for MyProjects View, with the functions that the view
	 * needs
	 * 
	 * @param view ControllerMyProjects view
	 */
	public ControllerMyProjects(JPanel view) {
		this.view = view;
	}

	/**
	 * Method to send a project to the council hall calling the application method
	 * fundProject
	 * 
	 * @param name name of the group
	 * @return true if everything gets well 
	 */
	public boolean councilHall(String name) {
		return Application.fundProject(name);
	}

	/**
	 * Method to look for the project in the application of a group by calling the
	 * getProjectByName method in the application
	 * 
	 * @param name name of the project
	 * @return the project
	 */
	public Project getInfo(String name) {
		return Application.getProjectByName(name, INSTANCE.getProjects());
	}

	/**
	 * Method to change to the more info view
	 * 
	 * @param name name of the project
	 */
	public void moreInfo(String name) {
		MainView.stackView(new ProjectsMoreInfo(name));
	}

	/**
	 * Method to getPopularity report of a project by calling the
	 * getPopularityReportsOfGroup mehtod in the application
	 * 
	 * @param name name of the project
	 */
	public void popularity(String name) {
		Application.getPopularityReport(name);
	}

}
