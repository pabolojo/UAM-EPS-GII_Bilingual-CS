package View.Views.Admin;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.ListSelectionEvent;

import Controllers.Admin.ControllerAdminProject;
import Model.Modules.Notification;
import Model.Modules.Project;
import Model.App.Application;
import static Model.App.Application.INSTANCE;

/**
 * This Panel contains the different functionalities of the administrator
 * regarding projects (accept, denied, look more information...)
 *
 *
 */
public class PanelAdminProjects extends JPanel {

	private JList<String> list;
	private JScrollPane scrollPane;
	private Dimension d;
	private JButton bAccept = new JButton("Accept");
	private JButton bReject = new JButton("Reject");
	private JButton bInfo = new JButton("More Info");
	private JTextField reason = new JTextField(20);
	private DefaultListModel<String> projects;
	private ControllerAdminProject controller;
	private JPanel pn;
	private JPanel bp;
	private JPanel lp;
	private JTextArea description;

	/**
	 * This is the constructor of the PanelAdminProjects that counts with a list
	 * with all the pending to accept project. It counts with several button for
	 * accepting, rejecting and getting more information about the project. The
	 * decription is shown when selecting a project.
	 */

	public PanelAdminProjects() {

		this.setLayout(new GridLayout(1, 2));
		this.controller = new ControllerAdminProject(this);

		this.lp = new JPanel();
		lp.setLayout(new BoxLayout(lp, BoxLayout.Y_AXIS));

		this.projects = new DefaultListModel<String>();

		for (Project p : Application.getAdmin().getAcceptProject()) {
			projects.addElement(p.getName());
		}

		this.list = new JList<String>(projects);

		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		list.addListSelectionListener(x -> changeSelection(x));

		this.scrollPane = new JScrollPane(list);
		d = scrollPane.getPreferredSize();
		d.width = 200;
		this.scrollPane.setPreferredSize(d);

		description = new JTextArea(2, 20);
		description.setText("Description:");
		description.setWrapStyleWord(true);
		description.setLineWrap(true);
		description.setEditable(false);
		description.setBackground(this.getBackground());

		lp.add(scrollPane);
		lp.add(description);
		lp.add(bInfo);
		this.add(lp);

		pn = new JPanel();
		pn.setLayout(new BorderLayout());
		JPanel pnf = new JPanel();
		pnf.setLayout(new BoxLayout(pnf, BoxLayout.Y_AXIS));
		JLabel label = new JLabel("Reason:");
		label.setAlignmentX(Component.CENTER_ALIGNMENT);
		pnf.add(label);
		pnf.add(reason);
		pn.add(pnf, BorderLayout.NORTH);

		bp = new JPanel();
		bp.add(bAccept);
		bp.add(bReject);

		pn.add(bp);

		this.add(pn);

		bAccept.addActionListener(x -> accept(x));
		bReject.addActionListener(x -> reject(x));
		bInfo.addActionListener(x -> info(x));
	}

	/**
	 * This method calls the method in the controller to get more information about
	 * a project
	 * 
	 * @param x
	 */
	private void info(ActionEvent x) {
		String project = (String) list.getSelectedValue();
		controller.moreinfo(project);
	}

	/**
	 * This method calls the method in the controller to accept the selected project
	 * 
	 * @param x select accept button
	 */
	public void accept(ActionEvent x) {
		String project = (String) list.getSelectedValue();
		if (project != null) {
			controller.bAccept(project, this.reason.getText(), true);
			if (this.reason.getText().length() == 0) {
				INSTANCE.getCurrentUser()
						.sendNotification(new Notification((Object) Application.INSTANCE, "Introduce some reason"));
				return;
			} else {
				this.projects.removeElement(project);
			}

			this.reason.setText("");

		}
	}

	/**
	 * This method calls the method in the controller to reject the selected project
	 * 
	 * @param x select reject button 
	 */
	public void reject(ActionEvent x) {
		String project = (String) list.getSelectedValue();
		if (project != null) {
			controller.bAccept(project, this.reason.getText(), false);
			this.projects.removeElement(project);
			this.reason.setText("");
		}
	}

	/**
	 * This method calls the method in the controller that changes the description
	 * text depending on the selected project
	 * 
	 * @param e select something from the list 
	 */
	public void changeSelection(ListSelectionEvent e) {
		Project p = INSTANCE.getAdmin().getProjectByName(this.list.getSelectedValue());
		if (p == null) {
			this.description.setText("Description: ");
		} else {
			this.description.setText("Description: " + p.getDescription());
		}
	}
}
