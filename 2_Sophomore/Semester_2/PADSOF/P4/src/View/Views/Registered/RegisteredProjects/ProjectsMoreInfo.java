package View.Views.Registered.RegisteredProjects;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import Model.Modules.Admin;
import Model.Modules.Infrastructure;
import Model.Modules.Project;
import Model.Modules.Social;
import View.MainView;

import static Model.App.Application.INSTANCE;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.util.*;

/**
 * This Panel show us more information about the different projects
 *
 *
 */
public class ProjectsMoreInfo extends JPanel {

	private JLabel name;
	private JLabel aim;
	private JLabel socialGroup;
	private JLabel neighborhood;
	private JLabel reqBudget;
	private JLabel grantBudget;
	private JLabel status;
	private JLabel picLabel;
	private ImageIcon image;
	private JTextArea description;
	private JButton bHome = new JButton("Home");

	/**
	 * This is the constructor of the ProjectsMoreInfo that shows all the
	 * information related with a project like the name description budget... This
	 * constructor has one label per attribute and show them using a GridLayout
	 * @param project name 
	 */
	public ProjectsMoreInfo(String project) {
		this.setLayout(new BorderLayout());
		Project p;
		if (INSTANCE.getCurrentUser() instanceof Admin) {
			Set<Project> projects = new TreeSet<Project>(INSTANCE.getAdmin().getAcceptProject());
			p = INSTANCE.getProjectByName(project, projects);
		} else {
			p = INSTANCE.getProjectByName(project, INSTANCE.getProjects());
		}

		this.name = new JLabel("Name: " + project);
		description = new JTextArea(2, 20);
		description.setText("Description: " + p.getDescription());
		description.setWrapStyleWord(true);
		description.setLineWrap(true);
		description.setEditable(false);
		description.setBackground(this.getBackground());
		this.reqBudget = new JLabel("Requested Budget: " + p.getBudget());

		this.grantBudget = new JLabel(
				"Granted Budget: " + (p.getGrantedBudget() == -1 ? "No granted Budget yet" : p.getGrantedBudget()));

		if (INSTANCE.getCurrentUser() instanceof Admin) {
			this.status = new JLabel("Status: Project is being reviewed by the admin");

		} else {

			if (p.getFundable()) {
				if (p.getUniqueID() == null) {
					this.status = new JLabel("Status: Project is fundable and keeps receiving votes");

				} else if (p.getGrantedBudget() > 0 && p.getUniqueID().length() != 0) {
					this.status = new JLabel("Status: Project has been accepted and granted a budget");

				} else if (p.getGrantedBudget() == 0 && p.getUniqueID().length() != 0) {
					this.status = new JLabel("Status: Project has been rejected by the Council Hall");

				} else if (p.getGrantedBudget() == -1 && p.getUniqueID().length() != 0) {
					this.status = new JLabel("Status: Project has been sent to the Council Hall");

				}
			} else {
				this.status = new JLabel("Status: Project is not fundable yet, receiving votes");
			}
			if (p.getExpired()) {
				this.status = new JLabel("Status: Project has expired");
			}
		}
		JPanel pn = new JPanel(new GridLayout(9, 1));
		pn.add(this.name);
		pn.add(this.description);
		pn.add(this.reqBudget);
		pn.add(this.grantBudget);
		pn.add(this.status);

		if (p instanceof Social) {
			Social social = (Social) p;
			if (social.getAim()) {
				aim = new JLabel("The aim of the project is National");
			} else {
				aim = new JLabel("The aim of the project is International");
			}
			socialGroup = new JLabel("Social Group: " + social.getSocialGroup());
			pn.add(this.aim);
			pn.add(this.socialGroup);

		}

		else if (p instanceof Infrastructure) {
			Infrastructure infrastructure = (Infrastructure) p;
			this.neighborhood = new JLabel("Neighborhood: " + infrastructure.getNeighborhood());
			this.image = new ImageIcon("files/Images/Projects/" + ((Infrastructure) p).getFileName());
			this.picLabel = new JLabel(image);
			Image scaledImage = image.getImage().getScaledInstance(100, 100, Image.SCALE_SMOOTH);
			Icon icon = new ImageIcon(scaledImage);
			picLabel.setIcon(icon);
			this.add(this.picLabel, BorderLayout.NORTH);
			pn.add(this.neighborhood);

		}
		pn.add(bHome);
		this.add(pn, BorderLayout.CENTER);

		this.bHome.addActionListener(x -> home(x));
	}

	/**
	 * This method implements the functionality of the home button
	 * 
	 * @param x
	 */
	private void home(ActionEvent x) {
		MainView.unStackView();
	}
}
