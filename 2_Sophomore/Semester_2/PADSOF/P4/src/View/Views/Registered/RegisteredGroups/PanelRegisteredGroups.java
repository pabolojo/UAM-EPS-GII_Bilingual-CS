package View.Views.Registered.RegisteredGroups;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.tree.*;

import Controllers.Registered.RegisteredGroups.ControllerGroup;
import Model.Modules.*;

import static Model.App.Application.INSTANCE;

/**
 * This Panel contains the PanelRegisteredGroups implementation that give us the
 * information of all the groups that exist in the application
 *
 *
 */
public class PanelRegisteredGroups extends JPanel {

	private DefaultMutableTreeNode nseleccionado;
	private DefaultMutableTreeNode rootNode = new DefaultMutableTreeNode("Groups");
	private JTree treeGroups = new JTree(rootNode);
	private String[] options = { "Groups", "My Groups" };
	private JComboBox<String> combobox = new JComboBox<String>(options);
	private JTextArea info;
	private JButton bJoin = new JButton("Join");
	private JButton bCreate = new JButton("Create Group");
	private JButton bSearch = new JButton("Search");
	private JTextField searchText = new JTextField();
	private ControllerGroup controller;
	private JScrollPane pnGroups;
	private String name = null;
	private JPanel field1;
	private PanelRegisteredMyGroups field2 = new PanelRegisteredMyGroups();

	/**
	 * This is the constructor of the PanelRegisteredGroups that counts with a list
	 * of all the groups that exist in the app and a combobox for move into the
	 * different views possibilities It also counts with a textArea with the
	 * description of the group and several buttons for create a new group or join
	 * in
	 */
	public PanelRegisteredGroups() {
		this.controller = new ControllerGroup(this);
		this.setLayout(new BorderLayout());

		treeGroups.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
		treeGroups.addTreeSelectionListener(x -> selected(x));

		this.update();

		this.pnGroups = new JScrollPane(this.treeGroups);
		this.pnGroups.setPreferredSize(field2.getSize());

		JPanel buttons = new JPanel(new FlowLayout());
		buttons.add(bCreate);
		buttons.add(bJoin);

		info = new JTextArea(2, 20);
		info.setText("Description:");
		info.setWrapStyleWord(true);
		info.setLineWrap(true);
		info.setEditable(false);
		info.setBackground(this.getBackground());

		JPanel pn2 = new JPanel();
		pn2.setLayout(new GridLayout(2, 0));
		pn2.add(info);
		pn2.add(buttons);

		JPanel psearch = new JPanel();
		psearch.setLayout(new GridLayout(1, 2));
		psearch.add(searchText);
		psearch.add(bSearch);

		combobox.addActionListener(x -> comboselection(x));
		bCreate.addActionListener(x -> newGroup(x));
		bJoin.addActionListener(x -> join(x));
		bSearch.addActionListener(x -> search(x));

		this.field1 = new JPanel();
		this.field1.setLayout(new BoxLayout(this.field1, BoxLayout.Y_AXIS));
		this.field1.add(psearch);
		this.field1.add(pnGroups);
		this.field1.add(pn2);

		this.add(combobox, BorderLayout.NORTH);
		this.add(field1, BorderLayout.CENTER);

	}

	/**
	 * This method implements the functionality of searching in groups , they obtain
	 * the information of the text field and search this information in the JTree
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
		for (Group g : INSTANCE.getGroup()) {
			if (g.getName().indexOf(text) != -1) {
				if (!flag) {
					rootNode.removeAllChildren();
					flag = true;
				}
				depthFirstInsert(g, this.rootNode);
			}
		}

		if (!flag) {
			INSTANCE.getCurrentUser().sendNotification(new Notification((Object) INSTANCE, "No results"));
			this.searchText.setText("");
		} else {
			DefaultTreeModel model = (DefaultTreeModel) treeGroups.getModel();
			model.reload();
		}
	}

	/**
	 * This method calls the joinGroup controller method that allows us joining a
	 * group
	 * 
	 * @param x select the button join
	 */
	private void join(ActionEvent x) {
		if (this.name != null) {
			if (this.controller.join(this.name)) {
				this.field2.joinGroup(this.name);
			}
		}
	}

	/**
	 * This method calls the newGroup controller method that opens the new view to
	 * create a group group
	 * 
	 * @param x event
	 */
	private void newGroup(ActionEvent x) {
		this.controller.newGroup();
	}

	/**
	 * This method moves into the different views when you select and option in the
	 * combobox
	 * 
	 * @param e select a option on the combobox
	 */
	private void comboselection(ActionEvent e) {
		int selectedIndex = this.combobox.getSelectedIndex();
		if (selectedIndex == 0) {
			this.add(field1, BorderLayout.CENTER);
			this.field2.setVisible(false);
			this.field1.setVisible(true);
		} else {
			this.add(field2, BorderLayout.CENTER);
			this.field1.setVisible(false);
			this.field2.setVisible(true);
		}
	}

	/**
	 * This method allows us select a group and show their description
	 * 
	 * @param e select a option on the JTree
	 */
	private void selected(TreeSelectionEvent e) {

		nseleccionado = (DefaultMutableTreeNode) treeGroups.getLastSelectedPathComponent();
		if (nseleccionado != null) {
			name = nseleccionado.getUserObject().toString();
			Group group = this.controller.getInfo(name);

			if (group != null) {
				info.setText("Description: " + group.getDescription());
			} else {
				info.setText("Description: ");
			}
		}

	}

	/** This method update the view of the tree for when you join into a group */
	public void update() {
		rootNode.removeAllChildren();
		if (!INSTANCE.getGroup().isEmpty()) {
			for (Group g : INSTANCE.getGroup()) {
				if (g.getFather() == null) {
					depthFirstInsert(g, this.rootNode);
				}
			}
		}
		DefaultTreeModel model = (DefaultTreeModel) treeGroups.getModel();
		model.reload();
	}

	/**
	 * This method implements a search for obtain a node into the tree
	 * 
	 * @param current group to search
	 * @param node    root to search the group
	 */
	private void depthFirstInsert(Group current, DefaultMutableTreeNode node) {
		DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(current.getName());
		node.add(newNode);
		if (!current.getSubGroups().isEmpty()) {
			for (Group g : current.getSubGroups()) {
				depthFirstInsert(g, newNode);
			}
		}
	}

}
