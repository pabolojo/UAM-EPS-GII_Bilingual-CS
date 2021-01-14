package View.Views.Registered.RegisteredGroups;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;

import Controllers.Registered.RegisteredGroups.ControllerMyGroup;
import Model.Modules.*;
import static Model.App.Application.INSTANCE;

/**
 * This Panel contains the MyGroups implementation that give us the information
 * of the groups in which the user is in.
 *
 *
 */

public class PanelRegisteredMyGroups extends JPanel {
	DefaultListModel<String> myGroups = new DefaultListModel<String>();
	JList<String> list = new JList<String>(myGroups);

	private JTextArea info;
	private JButton bLeave = new JButton("Leave");
	private JButton bAffinity = new JButton("Affinity Report");

	private ControllerMyGroup controller;
	private JScrollPane pnMyGroups = new JScrollPane(list);
	private String name = null;

	/**
	 * This is the constructor of the PanelRegisteredMyGroups Panel with a list with
	 * the groups in which the user has join in and some different buttons that give
	 * us the functionality of leave a group or ask for an affinity report
	 */
	public PanelRegisteredMyGroups() {

		this.controller = new ControllerMyGroup(this);
		this.setLayout(new BorderLayout());
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		list.addListSelectionListener(x -> selected(x));

		Registered user = ((Registered) INSTANCE.getCurrentUser());
		for (Group g : user.getMyGroups()) {
			myGroups.addElement(g.getName());
		}

		info = new JTextArea(2, 20);
		info.setText("Description:");
		info.setWrapStyleWord(true);
		info.setLineWrap(true);
		info.setEditable(false);
		info.setBackground(this.getBackground());

		JPanel pn2 = new JPanel();
		pn2.setLayout(new GridLayout(2, 0));
		pn2.add(info);

		JPanel bt = new JPanel();
		bt.add(bAffinity);
		bt.add(bLeave);
		pn2.add(bt);

		bLeave.addActionListener(x -> leave(x));
		bAffinity.addActionListener(x -> affinity(x));

		this.add(pnMyGroups, BorderLayout.CENTER);
		this.add(pn2, BorderLayout.SOUTH);

	}

	/**
	 * This method calls the ControllerMyGroup leave method that lets the current
	 * user leaves a group
	 * 
	 * @param x event
	 */
	private void leave(ActionEvent x) {
		if (this.name != null) {
			if (this.controller.leave(this.name)) {
				myGroups.removeElement(name);
				name = null;
			}
		}
	}

	/**
	 * This method calls the ControllerMyGroup affinityReport method that lets the
	 * current user leaves a group
	 * 
	 * @param x event
	 */
	private void affinity(ActionEvent x) {
		this.controller.affinityReport();
	}

	/**
	 * This method allows us select a group and show their description
	 * 
	 * @param e event
	 */
	private void selected(ListSelectionEvent e) {
		name = (String) list.getSelectedValue();
		Group group = this.controller.getInfo(name);
		if (group != null) {
			info.setText("Description: " + group.getDescription());
		} else {
			info.setText("Description: ");
		}

	}

	/**
	 * This method give the dimension of the panel MyGroups that contains the list
	 */
	public Dimension getSize() {
		return this.pnMyGroups.getPreferredSize();
	}

	/**
	 * This method add and element to the list when the join group function is used
	 * @param name name group
	 */
	public void joinGroup(String name) {
		myGroups.addElement(name);
	}
}

