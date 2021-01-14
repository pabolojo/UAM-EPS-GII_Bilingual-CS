package View.Views.Registered.RegisteredGroups;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import Controllers.Registered.RegisteredGroups.ControllerGroup;
import Model.Modules.Group;
import Model.Modules.Registered;

import static Model.App.Application.INSTANCE;

/**
 * This Controller counts with the functionalities about Creating a group
 *
 *
 */
public class PanelRegisteredCreateGroup extends JPanel {

	private ControllerGroup controller;
	private JLabel groupName = new JLabel("Group Name: ");
	private JLabel groupDescription = new JLabel("Description: ");
	private JLabel fatherLabel = new JLabel("Father: ");
	private JButton bCreate = new JButton("Create");
	private JButton bHome = new JButton("Home");
	private JTextField name = new JTextField(20);
	private JTextField description = new JTextField(20);
	private JComboBox<String> father;

	/**
	 * This is the constructor of the PanelRegisteredCreateGroup that implements the
	 * functionality of create a group , This constructor counts with several Labels
	 * and Text field to fill up and create a group
	 * 
	 * @param prev give us the information of the previous controller
	 */
	public PanelRegisteredCreateGroup(ControllerGroup prev) {
		this.controller = prev;
		this.setLayout(new BorderLayout());
		JPanel pn = new JPanel(new GridLayout(4, 4));

		Registered user = (Registered) INSTANCE.getCurrentUser();
		String[] groups = new String[user.getMyCreatedGroups().size() + 1];

		groups[0] = "Select";
		int i = 1;
		for (Group g : user.getMyCreatedGroups()) {
			groups[i] = g.getName();
			i++;
		}

		father = new JComboBox<String>(groups);
		pn.add(groupName);
		pn.add(name);
		pn.add(groupDescription);
		pn.add(description);
		pn.add(fatherLabel);
		pn.add(father);
		this.add(pn, BorderLayout.NORTH);

		JPanel pb = new JPanel();
		pb.add(bCreate);
		pb.add(bHome);
		this.add(pb, BorderLayout.SOUTH);
		bCreate.addActionListener(x ->

		create(x));
		bHome.addActionListener(x -> home(x));

	}

	/**
	 * This method calls the method create in the Controller Group that creates a
	 * new group or subgroup
	 * 
	 * @param evento create button selected 
	 */
	public void create(ActionEvent evento) {
		String name = this.name.getText();
		String description = this.description.getText();
		String father = (String) this.father.getSelectedItem();
		if (father.equals("Select")) {
			father = "";
		}
		controller.create(name, description, father);
	}

	/**
	 * This method implements the functionality of the home button that let you go
	 * to the previous view
	 * 
	 * @param evento hombe button select
	 */
	public void home(ActionEvent evento) {
		this.controller.home();
	}

}

