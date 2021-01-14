package View.Views.Registered;

import javax.swing.*;
import java.awt.*;
import View.Views.Registered.RegisteredGroups.PanelRegisteredGroups;
import View.Views.Registered.RegisteredProjects.PanelRegisteredProjects;
import View.Views.Registered.RegisteredSettings.PanelRegisteredSettings;

/**
 * This Panel contains the PanelRegistered , the first view that a registered
 * user see when they logs in this view allows the current user select what we
 * want to do
 *
 *
 */
public class PanelRegistered extends JPanel {

	private JTabbedPane tabs = new JTabbedPane();

	/**
	 * This is the constructor of the Panel Registered that have a tab with the
	 * different view options
	 * 
	 */
	public PanelRegistered() {
		this.setLayout(new FlowLayout());

		tabs.addTab("Groups", new PanelRegisteredGroups());
		tabs.addTab("Projects", new PanelRegisteredProjects());
		tabs.addTab("Settings", new PanelRegisteredSettings());

		tabs.setSelectedIndex(2);
		this.add(tabs);
	}
}
