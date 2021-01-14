package View.Views.Registered.RegisteredProjects;

import java.awt.*;
import java.awt.event.*;
import java.io.IOException;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;

import Controllers.Registered.RegisteredProjects.ControllerMyProjects;
import Model.Modules.*;
import es.uam.eps.sadp.grants.InvalidRequestException;

import static Model.App.Application.INSTANCE;

/**
 * This Panel contains the MyProject implementation that give us the information
 * of the projects that have been created by the current user
 *
 *
 */
public class PanelRegisteredMyProjects extends JPanel {
	DefaultListModel<Project> myProjects = new DefaultListModel<Project>();
	JList<Project> list = new JList<Project>(myProjects);

	private JTextArea info;
	private JButton bMoreInfo = new JButton("More Info");
	private JButton bPopularity = new JButton("Popularity Report");
	private JButton bCouncil = new JButton("Send to CouncilHall");

	private ControllerMyProjects controller;
	private JScrollPane pnMyProjects = new JScrollPane(list);

	/**
	 * This is the constructor of the PanelRegisteredMyProjects Panel with a list
	 * with the project that have been created by the current user and buttons with
	 * different options
	 */
	public PanelRegisteredMyProjects() {

		this.controller = new ControllerMyProjects(this);
		this.setLayout(new BorderLayout());
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		list.addListSelectionListener(x -> selected(x));
		list.setCellRenderer(new MyProjectCellRenderer());

		Registered user = ((Registered) INSTANCE.getCurrentUser());
		for (Project p : user.getMyCreatedProjects()) {
			myProjects.addElement(p);
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
		bt.add(bCouncil);
		bt.add(bPopularity);
		bt.add(bMoreInfo);
		pn2.add(bt);

		bCouncil.addActionListener(x -> councilHall(x));
		bPopularity.addActionListener(x -> bPopularity(x));
		bMoreInfo.addActionListener(x -> bInfo(x));

		this.add(pnMyProjects, BorderLayout.CENTER);
		this.add(pn2, BorderLayout.SOUTH);

	}

	/**
	 * This method calls to ControllerMyProject moreInfo method that return the
	 * information of a project
	 * 
	 * @param x select the button
	 */
	private void bInfo(ActionEvent x) {
		Project p = this.list.getSelectedValue();
		if (p != null) {
			controller.moreInfo(p.getName());
		}
	}

	/**
	 * This method calls to ControllerMyProject popularity method that return the
	 * popularity report of a given project
	 * 
	 * @param x select the button
	 */
	private void bPopularity(ActionEvent x) {
		Project p = this.list.getSelectedValue();
		if (p != null) {
			controller.popularity(p.getName());
		}
	}

	/**
	 * This method calls to ControllerMyProject councilHall method that send the
	 * project to the councilHall
	 * 
	 * @param x select the button
	 */
	private void councilHall(ActionEvent x) {
		Project p = this.list.getSelectedValue();
		if (p != null) {
			controller.councilHall(p.getName());
		}
	}

	/**
	 * This method allow us know with project is being selected into the JList
	 * 
	 * @param e select something form the JList
	 */
	private void selected(ListSelectionEvent e) {
		Project project = list.getSelectedValue();
		if (project != null) {
			info.setText("Description: " + project.getDescription());
		} else {
			info.setText("Description: ");
		}

	}

	/**
	 * This put in different colors the project of the list
	 */
	class MyProjectCellRenderer extends DefaultListCellRenderer implements ListCellRenderer<Object> {

		public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected,
				boolean cellHasFocus) {
			Project p = (Project) value;
			setText((p == null) ? "" : p.getName());
			if (isSelected) {
				setBackground(list.getBackground());
			} else {
				setBackground(p.getFundable() ? Color.GREEN : Color.ORANGE);
			}
			return this;
		}
	}
}

