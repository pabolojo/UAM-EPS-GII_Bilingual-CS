package View.Views.Admin;

import javax.swing.*;
import java.awt.*;

/**
 * This Panel contains a tabbed pane that represents all the different
 * functionalitites of the administrator. This different tabs move the admin to
 * different panels
 *
 *
 */
public class PanelAdmin extends JPanel {

	private JTabbedPane tabs = new JTabbedPane();

	/**
	 * This is the constructor of the PanelAdmin panel that has 3 tabs for the 3
	 * different primary functions of the admin
	 */
	public PanelAdmin() {
		this.setLayout(new FlowLayout());

		tabs.addTab("Users", new PanelAdminUsers());
		tabs.addTab("Projects", new PanelAdminProjects());
		tabs.addTab("Settings", new PanelAdminSettings());
		tabs.setSelectedIndex(2);
		this.add(tabs);
	}

}
