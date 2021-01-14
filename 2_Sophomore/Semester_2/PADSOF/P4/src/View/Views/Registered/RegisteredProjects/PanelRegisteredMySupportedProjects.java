package View.Views.Registered.RegisteredProjects;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.ListSelectionEvent;

import Controllers.Registered.RegisteredProjects.ControllerMySupportedProjects;
import Model.Modules.Project;
import Model.Modules.Registered;
import static Model.App.Application.INSTANCE;

/**
 * This Panel contains the MySupportedProject implementation that give us the
 * information of the projects that have been supported by the current user
 *
 *
 */
public class PanelRegisteredMySupportedProjects extends JPanel {
	DefaultListModel<Project> myGroups = new DefaultListModel<Project>();
	JList<Project> list = new JList<Project>(myGroups);

	private JTextArea info;
	private JButton bSubs = new JButton("Subscribe");
	private JButton bPopularity = new JButton("Popularity Report");
	private JButton bInfo = new JButton("More Info");

	private ControllerMySupportedProjects controller;
	private JScrollPane pnMyGroups = new JScrollPane(list);

	/**
	 * This is the constructor of the PanelRegisteredMySupportedProjects Panel with
	 * a list with the projects that have been supported by the current user and
	 * buttons with different options
	 */
	public PanelRegisteredMySupportedProjects() {

		this.controller = new ControllerMySupportedProjects(this);
		this.setLayout(new BorderLayout());
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		list.setCellRenderer(new ProjectCellRenderer());

		list.addListSelectionListener(x -> selected(x));

		Registered user = ((Registered) INSTANCE.getCurrentUser());
		for (Project p : user.getMyProjects()) {
			myGroups.addElement(p);
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
		bt.add(bSubs);
		bt.add(bPopularity);
		bt.add(bInfo);
		pn2.add(bt);

		bPopularity.addActionListener(x -> popularity(x));
		bSubs.addActionListener(x -> subscribe(x));
		bInfo.addActionListener(x -> info(x));

		this.add(pnMyGroups, BorderLayout.CENTER);
		this.add(pn2, BorderLayout.SOUTH);

	}

	/**
	 * This method calls to ControllerMySupportedProject moreInfo method that return
	 * the information of a project
	 * 
	 * @param x select a project from the list
	 */
	private void info(ActionEvent x) {
		Project p = this.list.getSelectedValue();
		if (p != null) {
			controller.moreinfo(p.getName());
		}
	}

	/**
	 * This method calls to ControllerMySupportedProject moreInfo method that return
	 * the information of a project
	 * 
	 * @param x select the button
	 */
	private void subscribe(ActionEvent x) {
		Project project = list.getSelectedValue();
		if (project != null) {
			this.controller.suscribe(project.getName());
		}
	}

	/**
	 * This method calls to ControllerMySupportedProject popularity method that
	 * return the popularity report of a given project
	 * 
	 * @param x select the button
	 */
	private void popularity(ActionEvent x) {
		Project project = list.getSelectedValue();
		if (project != null) {
			this.controller.popularity(project.getName());
		}
	}

	/**
	 * This method allow us know which project has been selected into the JList and
	 * shows his description
	 * 
	 * @param e select something from the list
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
	 * This method put in different colors the project of the list
	 */
	class ProjectCellRenderer extends DefaultListCellRenderer implements ListCellRenderer<Object> {

		public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected,
				boolean cellHasFocus) {
			Project p = (Project) value;
			setText((p == null) ? "" : p.getName());
			if (isSelected) {
				setBackground(Color.YELLOW);
			} else {
				if (((Registered) (INSTANCE.getCurrentUser())).getSubsProjects().contains(p)) {
					setBackground(Color.RED);
				} else {
					setBackground(list.getBackground());
				}

				if (p.getFundable() && p.getGrantedBudget() > 0) {
					setBackground(Color.GREEN);
				}
			}
			return this;
		}
	}

	/**
	 * This method addElements to the myGroup panel
	 * @param p project that is going to be add 
	 */
	public void addSupported(Project p) {
		myGroups.addElement(p);
	}
}
