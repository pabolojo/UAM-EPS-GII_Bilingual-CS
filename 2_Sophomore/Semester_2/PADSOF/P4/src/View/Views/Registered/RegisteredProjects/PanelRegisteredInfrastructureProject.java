package View.Views.Registered.RegisteredProjects;

import static Model.App.Application.INSTANCE;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.io.*;

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
 * This Panel contains the Infrastructure Project implementation that give use
 * the option of create a infrastructure project
 *
 *
 */
public class PanelRegisteredInfrastructureProject extends JPanel {

	private ControllerProject controller;
	private JLabel nameLabel = new JLabel("Project Name: ");
	private JLabel descriptionLabel = new JLabel("Description: ");
	private JLabel budgetLabel = new JLabel("Budget: ");
	private JLabel fileLabel = new JLabel("Image: ");
	private JLabel neighborhoodLabel = new JLabel("Neighborhood: ");
	private JLabel groupLabel = new JLabel("Group: ");

	private JButton bCreate = new JButton("Create");
	private JButton bfile = new JButton("Choose a file");
	private JButton bHome = new JButton("Home");

	private JTextField name = new JTextField(20);
	private JTextField description = new JTextField(20);
	private JTextField budget = new JTextField(20);
	private JFileChooser fc = new JFileChooser();
	private JComboBox<String> neighborhood;
	private JComboBox<String> groups;
	private File file = null;
	private int selection = 0;

	/**
	 * This is the constructor of the PanelRegisteredInfrastructureProject Panel
	 * with several Labels and Text fields for the user to fill up and create a
	 * group It also counts with two buttons one to move to the previous Panel and
	 * other one for create the project
	 * @param prev previous controller
	 */
	public PanelRegisteredInfrastructureProject(ControllerProject prev) {

		this.controller = prev;
		this.setLayout(new BorderLayout());
		JPanel pn = new JPanel(new GridLayout(6, 6));

		String[] projects = new String[Application.getNeighborhoods().size() + 1];
		projects[0] = "Select";
		int i = 1;
		for (String p : Application.getNeighborhoods()) {
			projects[i] = p;
			i++;
		}

		Registered user = ((Registered) INSTANCE.getCurrentUser());
		String[] groupsName = new String[user.getMyCreatedGroups().size() + 1];
		groupsName[0] = "Select";
		int j = 1;
		for (Group g : user.getMyCreatedGroups()) {
			groupsName[j] = g.getName();
			j++;
		}

		neighborhood = new JComboBox<String>(projects);
		groups = new JComboBox<String>(groupsName);
		pn.add(nameLabel);
		pn.add(name);
		pn.add(descriptionLabel);
		pn.add(description);
		pn.add(budgetLabel);
		pn.add(budget);
		pn.add(fileLabel);
		pn.add(bfile);
		pn.add(neighborhoodLabel);
		pn.add(neighborhood);
		pn.add(groupLabel);
		pn.add(groups);
		this.add(pn, BorderLayout.NORTH);

		JPanel pb = new JPanel();
		pb.add(bCreate);
		pb.add(bHome);
		this.add(pb, BorderLayout.SOUTH);
		bCreate.addActionListener(x -> create(x));
		bfile.addActionListener(x -> choose(x));
		bHome.addActionListener(x -> home(x));

	}

	/**
	 * This method obtains the string of the TextLabels and call the method
	 * implemented in the constructor that creates a infrastructure project
	 * 
	 * @param evento select the button create
	 */
	public void create(ActionEvent evento) {
		String name = this.name.getText();
		String description = this.description.getText();
		double budget = 0;
		try {
			budget = Double.parseDouble(this.budget.getText());
		} catch (NumberFormatException e) {
			INSTANCE.getCurrentUser().sendNotification(
					new Notification((Object) Application.INSTANCE, "The written budget is not numeric"));
			return;
		}
		String neighborhood = (String) this.neighborhood.getSelectedItem();
		String groups = (String) this.groups.getSelectedItem();

		if (groups.equals("Select")) {
			groups = "";
		}

		if (neighborhood.equals("Select")) {
			neighborhood = "";
		}
		if (file == null) {
			INSTANCE.getCurrentUser()
					.sendNotification(new Notification((Object) INSTANCE, "You have to choose an Image"));
			return;
		}

		File copy = new File("files/Images/Projects/" + name);
		try {
			this.copyPaste(file, copy);
		} catch (IOException e) {
			e.printStackTrace();
		}

		this.controller.infrastructure(name, description, budget, copy.getName(), neighborhood, groups);
	}

	/**
	 * This method let us decide with image you want to upload from your device and
	 * save the information of that file into the app
	 * 
	 * @param evento select the option choose
	 */
	public void choose(ActionEvent evento) {
		selection = fc.showOpenDialog(this);

		if (selection == JFileChooser.APPROVE_OPTION) {
			this.file = fc.getSelectedFile();
			if (file.getName().endsWith("png") || file.getName().endsWith("jpg") || file.getName().endsWith("jpeg")) {
				bfile.setText(file.getName());
			} else {
				INSTANCE.getCurrentUser()
						.sendNotification(new Notification((Object) Application.INSTANCE, "This is not an image"));
				return;
			}

		}

	}

	/**
	 * This method allows us copy the information of the uploaded file and save them
	 * into the application
	 * 
	 * @param src File that is going to be copied
	 * @param dst File that is going to be pasted
	 * 
	 */
	private void copyPaste(File src, File dst) throws IOException {
		try {

			InputStream in = new FileInputStream(src);
			OutputStream out = new FileOutputStream(dst);

			byte[] b = new byte[1024];
			int l;
			while ((l = in.read(b)) > 0) {
				out.write(b, 0, l);
			}

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
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

