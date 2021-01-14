package View.Views.Registered.RegisteredGroups;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import Controllers.Registered.RegisteredGroups.ControllerMyGroup;
import Model.Modules.*;
import static Model.App.Application.INSTANCE;

/**
 * This Panel implements the functionality of an Affinity Report , this panel
 * shows you the affinity report between two groups
 *
 *
 */
public class PanelRegisteredAffinityReport extends JPanel {

	private JLabel group1 = new JLabel("First Group: ");
	private JLabel group2 = new JLabel("Second Group: ");
	private JComboBox<String> cgroup1;
	private JComboBox<String> cgroup2;
	private ControllerMyGroup controller;
	private JButton bHome;
	private JButton bAffinity;

	/**
	 * This is the constructor of the PanelRegisteredAffinityReport that counts with
	 * two combobox for the selection of the different groups , it also counts with
	 * two buttons one for ask for affinity report and the other one for go back
	 * 
	 * @param controller the Controller that implements the model methods
	 */

	public PanelRegisteredAffinityReport(ControllerMyGroup controller) {
		this.controller = controller;
		this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		JPanel pn = new JPanel(new GridLayout(2, 2));

		Registered user = (Registered) INSTANCE.getCurrentUser();
		String[] groups = new String[user.getMyGroups().size() + 1];

		groups[0] = "Select";
		int i = 1;
		for (Group g : user.getMyGroups()) {
			groups[i] = g.getName();
			i++;
		}

		cgroup1 = new JComboBox<String>(groups);
		cgroup2 = new JComboBox<String>(groups);
		pn.add(group1);
		pn.add(cgroup1);
		pn.add(group2);
		pn.add(cgroup2);

		JPanel bt = new JPanel();
		bHome = new JButton("Home");
		bAffinity = new JButton("Ask Report");

		bHome.addActionListener(x -> home(x));
		bAffinity.addActionListener(x -> askAffinity(x));
		bt.add(bAffinity);
		bt.add(bHome);

		this.add(pn);
		this.add(bt);
	}

	/**
	 * This method implements the functionality of the affinity button calling the
	 * Correspondent function in the controller
	 * 
	 * @param x event
	 */
	private void askAffinity(ActionEvent x) {
		String g1 = (String) cgroup1.getSelectedItem();
		String g2 = (String) cgroup2.getSelectedItem();
		this.controller.askAffinity(g1, g2);
	}

	/**
	 * This method implements the functionality of the home button that allow you go
	 * back into the views
	 * 
	 * @param x event
	 */
	private void home(ActionEvent x) {
		this.controller.home();
	}

}
