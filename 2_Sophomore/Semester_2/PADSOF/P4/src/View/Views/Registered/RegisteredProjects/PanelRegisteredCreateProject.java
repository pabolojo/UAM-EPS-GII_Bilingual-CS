package View.Views.Registered.RegisteredProjects;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JPanel;

import Controllers.Registered.RegisteredProjects.ControllerProject;

/**
 * This Panel contains the Create Project implementation that give use the
 * option of create a infrastructure or social project
 *
 *
 */
public class PanelRegisteredCreateProject extends JPanel {

	private ControllerProject controller;
	private String[] options = { "Infrastructure", "Social" };
	private JComboBox<String> combobox = new JComboBox<String>(options);
	private PanelRegisteredInfrastructureProject infrastructure;
	private PanelRegisteredSocialProject social;

	/**
	 * This is the constructor of the PanelRegisteredCreateProject Panel with a
	 * combobox that lets the user chose the type of project that he wants to create
	 * @param prev previous controller
	 * 
	 */
	public PanelRegisteredCreateProject(ControllerProject prev) {
		this.controller = prev;
		infrastructure = new PanelRegisteredInfrastructureProject(this.controller);
		social = new PanelRegisteredSocialProject(this.controller);
		this.setLayout(new BorderLayout());
		this.add(combobox, BorderLayout.NORTH);
		this.add(infrastructure, BorderLayout.CENTER);
		combobox.addActionListener(x -> comboselection(x));

	}

	/**
	 * This method lets us select which type of group we want to create and leads us
	 * to the new view
	 * 
	 * @param e
	 */
	private void comboselection(ActionEvent e) {
		int selectedIndex = this.combobox.getSelectedIndex();
		if (selectedIndex == 0) {
			this.add(infrastructure, BorderLayout.CENTER);
			this.infrastructure.setVisible(true);
			this.social.setVisible(false);
		} else {
			this.add(social, BorderLayout.CENTER);
			this.social.setVisible(true);
			this.infrastructure.setVisible(false);
		}
	}

}
