package View.Views.Registered.RegisteredProjects;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.ListSelectionEvent;

import Controllers.Registered.RegisteredProjects.ControllerProject;
import Model.Modules.*;

import static Model.App.Application.INSTANCE;

/**
 * This Panel contains the RegisteredProject implementation that give us the
 * information of all the projects that have been created in the app
 *
 *
 */

public class PanelRegisteredProjects extends JPanel {

	DefaultListModel<Project> projects = new DefaultListModel<Project>();
	JList<Project> list = new JList<Project>(projects);

	private String[] options = { "Projects", "My Projects", "My Supported Projects" };
	private JComboBox<String> combobox = new JComboBox<String>(options);
	private JTextArea info;
	private JButton bInfo = new JButton("More Info");
	private JButton bVote = new JButton("Vote");
	private JButton bCreate = new JButton("Create Project");
	private JButton bSearch = new JButton("Search");
	private JTextField searchText = new JTextField();
	private ControllerProject controller;
	private JScrollPane scrollProjects;
	private JPanel field1;
	private PanelRegisteredMyProjects field2 = new PanelRegisteredMyProjects();
	private PanelRegisteredMySupportedProjects field3 = new PanelRegisteredMySupportedProjects();

	/**
	 * This is the constructor of the PanelRegisteredProjects Panel with a list with
	 * all the projects and some buttons with different options
	 */
	public PanelRegisteredProjects() {
		this.controller = new ControllerProject(this);
		this.setLayout(new BorderLayout());

		this.scrollProjects = new JScrollPane(this.list);

		update();

		list.addListSelectionListener(x -> selected(x));
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		list.setCellRenderer(new ProjectCellRenderer());

		info = new JTextArea(2, 20);
		info.setText("Description: ");
		info.setWrapStyleWord(true);
		info.setLineWrap(true);
		info.setEditable(false);
		info.setBackground(this.getBackground());

		JPanel buttons = new JPanel(new FlowLayout());
		buttons.add(bCreate);
		buttons.add(bVote);
		buttons.add(bInfo);

		JPanel pn2 = new JPanel();
		pn2.setLayout(new GridLayout(2, 0));
		pn2.add(info);
		pn2.add(buttons);

		combobox.addActionListener(x -> comboselection(x));
		bCreate.addActionListener(x -> newProject(x));
		bVote.addActionListener(x -> vote(x));
		bInfo.addActionListener(x -> info(x));
		bSearch.addActionListener(x -> search(x));

		JPanel psearch = new JPanel();
		psearch.setLayout(new GridLayout(1, 2));
		psearch.add(searchText);
		psearch.add(bSearch);

		this.field1 = new JPanel();
		this.field1.setLayout(new BoxLayout(this.field1, BoxLayout.Y_AXIS));

		this.field1.add(psearch);
		this.field1.add(scrollProjects);
		this.field1.add(pn2);

		this.add(combobox, BorderLayout.NORTH);
		this.add(field1, BorderLayout.CENTER);

	}

	/** This method update the view of the Jtree */
	private void update() {

		this.projects.clear();

		for (Project p : INSTANCE.getProjects()) {
			if (p instanceof Infrastructure) {
				this.projects.addElement(p);
			}
		}

		for (Project p : INSTANCE.getProjects()) {
			if (p instanceof Social) {
				this.projects.addElement(p);
			}
		}
	}

	/**
	 * This method implements the functionality of searching in projects , they
	 * obtain the information of the text field and search this information in the
	 * JTree
	 * 
	 * @param x select the button search
	 * 
	 */
	private void search(ActionEvent x) {
		String text = this.searchText.getText();
		if (text.equals("")) {
			update();
			return;
		}
		boolean flag = false;
		for (Project p : INSTANCE.getProjects()) {
			if (p.getName().indexOf(text) != -1) {
				if (!flag) {
					this.projects.clear();
					flag = true;
				}
				this.projects.addElement(p);
			}
		}

		if (!flag) {
			INSTANCE.getCurrentUser().sendNotification(new Notification((Object) INSTANCE, "No results"));
			this.searchText.setText("");
		}
	}

	/**
	 * This method calls to ControllerProject moreInfo method that return the
	 * information of a project
	 * 
	 * @param x
	 */
	private void info(ActionEvent x) {
		Project p = this.list.getSelectedValue();
		if (p != null) {
			controller.moreinfo(p.getName());
		}
	}

	/**
	 * This method calls to ControllerProject vote method that implements the
	 * functionality of voting the information of a project
	 * 
	 * @param x
	 */
	private void vote(ActionEvent x) {
		Project p = this.list.getSelectedValue();
		if (p != null) {
			if (this.controller.vote(p.getName())) {
				field3.addSupported(p);
			}
		}
	}

	/**
	 * This method calls to ControllerProject newProject that move to the
	 * CreateProjects Panel
	 * 
	 * @param x
	 */
	private void newProject(ActionEvent x) {
		this.controller.newProject();
	}

	/**
	 * This method lets us know with option of the combobox is selected and moves
	 * into the different views related with projects like CreateProject
	 * 
	 * @param e
	 */
	private void comboselection(ActionEvent e) {
		int selectedIndex = this.combobox.getSelectedIndex();
		if (selectedIndex == 0) {
			this.add(field1, BorderLayout.CENTER);
			this.field2.setVisible(false);
			this.field3.setVisible(false);
			this.field1.setVisible(true);
		} else if (selectedIndex == 1) {
			this.add(field2, BorderLayout.CENTER);
			this.field1.setVisible(false);
			this.field3.setVisible(false);
			this.field2.setVisible(true);
		} else {
			this.add(field3, BorderLayout.CENTER);
			this.field1.setVisible(false);
			this.field2.setVisible(false);
			this.field3.setVisible(true);
		}
	}

	/**
	 * This method allow us know which project has been selected into the JList and
	 * shows his description
	 * 
	 * @param e
	 */
	private void selected(ListSelectionEvent e) {
		Project project = (Project) list.getSelectedValue();
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
				setBackground(list.getBackground());
			} else {
				setBackground((p instanceof Infrastructure) ? Color.ORANGE : Color.MAGENTA);
			}
			return this;
		}
	}

}
