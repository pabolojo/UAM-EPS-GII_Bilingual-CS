package View.Views.Registered.RegisteredProjects;

import static Model.App.Application.INSTANCE;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.io.File;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import Controllers.Registered.RegisteredProjects.ControllerProject;
import Model.Modules.*;
import Model.App.Application;

/**
 * This Panel contains the Social Project implementation that give use the
 * option of create a social project
 *
 *
 */

public class PanelRegisteredSocialProject extends JPanel {

	private ControllerProject controller;

	private JLabel nameLabel = new JLabel("Project Name: ");
	private JLabel descriptionLabel = new JLabel("Description: ");
	private JLabel budgetLabel = new JLabel("Budget: ");
	private JLabel aimLabel = new JLabel("Aim: ");
	private JLabel socialGroupLabel = new JLabel("SocialGroup: ");
	private JLabel groupLabel = new JLabel("Group: ");

	private JButton bCreate = new JButton("Create");
	private JButton bHome = new JButton("Home");

	private JTextField name = new JTextField(20);
	private JTextField description = new JTextField(20);
	private JTextField budget = new JTextField(20);
	private JTextField social = new JTextField(20);
	private JComboBox<String> aim;
	private JComboBox<String> groups;

	/**
	 * This is the constructor of the PanelRegisteredSocialProject Panel with
	 * several Labels and Text fields for the user to fill up and create a group It
	 * also counts with a two buttons one to move to the previous Panel and one for
	 * create the project
	 * @param prev previous controller
	 */
	public PanelRegisteredSocialProject(ControllerProject prev) {
		this.controller = prev;
		this.setLayout(new BorderLayout());

		JPanel pn = new JPanel(new GridLayout(6, 6));
		String[] aimProject = { "Select", "NATIONAL", "INTERNATIONAL" };

		Registered user = ((Registered) INSTANCE.getCurrentUser());
		String[] groupsName = new String[user.getMyCreatedGroups().size() + 1];
		groupsName[0] = "Select";
		int j = 1;

		for (Group g : user.getMyCreatedGroups()) {
			groupsName[j] = g.getName();
			j++;
		}

		aim = new JComboBox<String>(aimProject);
		groups = new JComboBox<String>(groupsName);
		pn.add(nameLabel);
		pn.add(name);
		pn.add(descriptionLabel);
		pn.add(description);
		pn.add(budgetLabel);
		pn.add(budget);
		pn.add(aimLabel);
		pn.add(aim);
		pn.add(socialGroupLabel);
		pn.add(social);
		pn.add(groupLabel);
		pn.add(groups);
		this.add(pn, BorderLayout.NORTH);
		JPanel pb = new JPanel();
		pb.add(bCreate);
		pb.add(bHome);
		this.add(pb, BorderLayout.SOUTH);
		bCreate.addActionListener(x -> create(x));
		bHome.addActionListener(x -> home(x));

	}

	/**
	 * This method obtains the string information written in the TextLabels and call
	 * the method implemented in the constructor that creates a social project
	 * 
	 * @param evento select the button create
	 */
	public void create(ActionEvent evento) {
		String name = this.name.getText();
		String description = this.description.getText();
		String social = this.social.getText();
		double budget = 0;
		try {
			budget = Double.parseDouble(this.budget.getText());
		} catch (NumberFormatException e) {
			INSTANCE.getCurrentUser().sendNotification(
					new Notification((Object) Application.INSTANCE, "The written budget is not numeric"));
			return;
		}
		String aimText = (String) this.aim.getSelectedItem();
		String groups = (String) this.groups.getSelectedItem();
		boolean aimB;

		if (groups.equals("Select")) {
			groups = "";
		}

		if (aimText.equals("NATIONAL")) {
			aimB = true;
		} else if (aimText.equals("INTERNATIONAL")) {
			aimB = false;
		} else {
			INSTANCE.getCurrentUser()
					.sendNotification(new Notification((Object) Application.INSTANCE, "Please select a aim"));
			return;
		}
		this.controller.social(name, description, budget, aimB, social, groups);
	}

	/**
	 * This method implements the functionality of the home button that let you go
	 * to the previous
	 * 
	 * @param evento select the button
	 */
	public void home(ActionEvent evento) {
		this.controller.home();
	}

}

