package View.Views.Admin;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;

import java.awt.*;
import java.awt.event.*;
import Controllers.Admin.ControllerAdminUsers;
import Model.App.Application;
import static Model.App.Application.INSTANCE;
import Model.Modules.Registered;

/**
 * This Panel allows the admin to Accept, Reject, Ban and Unban users
 *
 *
 */

public class PanelAdminUsers extends JPanel {

	private JList<String> list;
	private JList<Registered> listBan;
	private JScrollPane scrollPane;
	private JScrollPane scrollPaneBan;
	private Dimension d;
	private JButton bAccept = new JButton("Accept");
	private JButton bReject = new JButton("Reject");
	private JButton bBan = new JButton("Ban");
	private DefaultListModel<String> registered;
	private DefaultListModel<Registered> registeredBan;
	private ControllerAdminUsers controller;
	private JComboBox<String> combo;
	private JPanel field1;
	private JPanel field2;

	/**
	 * This is the constructor of the PanelAdminUsers that counts with a list of all
	 * the pending for accept or reject users. It also counts with a list of all the
	 * already registered users. There are buttons for accepting or rejecting the
	 * pending users, and ban and unban the already registered ones.
	 */

	public PanelAdminUsers() {
		this.setLayout(new BorderLayout());
		this.controller = new ControllerAdminUsers(this);
		this.registered = new DefaultListModel<String>();

		String[] fields = { "Accept Users", "Ban/Unban Users" };
		this.combo = new JComboBox<String>(fields);
		this.add(this.combo, BorderLayout.NORTH);
		combo.addItemListener(x -> changeField(x));
		combo.setSelectedIndex(0);

		this.field1 = new JPanel();
		this.field2 = new JPanel();

		for (Registered r : Application.getAdmin().getAcceptUser()) {
			registered.addElement(r.getName());
		}

		this.list = new JList<String>(registered);

		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		this.scrollPane = new JScrollPane(list);
		d = scrollPane.getPreferredSize();
		d.width = 200;
		this.scrollPane.setPreferredSize(d);

		this.field1.add(scrollPane);

		field1.add(bAccept);
		field1.add(bReject);

		bAccept.addActionListener(x -> accept(x));
		bReject.addActionListener(x -> reject(x));

		this.add(field1, BorderLayout.CENTER);

		this.registeredBan = new DefaultListModel<Registered>();

		for (Registered r : INSTANCE.getUsers()) {
			registeredBan.addElement(r);
		}

		this.listBan = new JList<Registered>(registeredBan);
		this.listBan.addListSelectionListener(x -> changeSelection(x));

		listBan.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		listBan.setCellRenderer(new BanCellRenderer());

		this.scrollPaneBan = new JScrollPane(listBan);
		d = scrollPaneBan.getPreferredSize();
		d.width = 200;
		this.scrollPaneBan.setPreferredSize(d);

		this.field2.add(this.scrollPaneBan);

		bBan.addActionListener(x -> ban(x));
		bBan.setPreferredSize(new Dimension(80, 25));
		field2.add(bBan);
	}

	/**
	 * This method calls the method in the controller that changes the text of a
	 * selected user depending if it is banned or unbaned
	 * 
	 * @param e select something from the list 
	 */

	public void changeSelection(ListSelectionEvent e) {
		Registered selectedUser = listBan.getSelectedValue();
		if (selectedUser == null) {
			return;
		}
		if (selectedUser.isBanned()) {
			this.bBan.setText("Unban");
		} else {
			this.bBan.setText("Ban");
		}
	}

	/**
	 * This method calls the method in the controller to accept the selected user
	 * into the application
	 * 
	 * @param e select accept button 
	 */
	public void accept(ActionEvent e) {
		String selectedUser = (String) list.getSelectedValue();
		if (selectedUser != null) {
			controller.bAccept(selectedUser, true);
			this.registered.removeElement(selectedUser);
		}

	}

	/**
	 * This method calls the method in the controller to reject the selected user
	 * into the application
	 * 
	 * @param e select reject button 
	 */
	public void reject(ActionEvent e) {

		String selectedUser = (String) list.getSelectedValue();
		if (selectedUser != null) {
			controller.bAccept(selectedUser, false);
			this.registered.removeElement(selectedUser);
		}
	}

	/**
	 * This method calls the method in the controller to ban or Unban a selected
	 * User
	 * 
	 * @param e select ban button
	 */
	public void ban(ActionEvent e) {
		Registered selectedUser = listBan.getSelectedValue();
		if (this.bBan.getText().equals("Ban")) {
			this.bBan.setText("Unban");
		} else {
			this.bBan.setText("Ban");
		}
		if (selectedUser != null) {
			controller.bBan(selectedUser);
		}
	}

	/**
	 * This method changes the view between banning or accepting new users depending
	 * on the selected tab
	 * 
	 * @param e event 
	 */
	public void changeField(ItemEvent e) {
		int selectedIndex = this.combo.getSelectedIndex();
		if (selectedIndex == 0) {
			this.add(field1, BorderLayout.CENTER);
			this.field2.setVisible(false);
			this.field1.setVisible(true);
		} else {
			this.add(field2, BorderLayout.CENTER);
			this.field1.setVisible(false);
			this.field2.setVisible(true);
			registeredBan.clear();
			for (Registered r : INSTANCE.getUsers()) {
				registeredBan.addElement(r);
			}
		}
	}

	/**
	 * This class changes the colors of the cells of the list (RED if they are
	 * banned, GREEN if they are not)
	 */
	class BanCellRenderer extends DefaultListCellRenderer implements ListCellRenderer<Object> {

		public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected,
				boolean cellHasFocus) {
			Registered r = (Registered) value;
			setText((r == null) ? "" : r.getName());
			if (isSelected) {
				setBackground(list.getBackground());
			} else {
				setBackground(r.isBanned() ? Color.RED : Color.GREEN);
			}
			return this;
		}
	}
}
