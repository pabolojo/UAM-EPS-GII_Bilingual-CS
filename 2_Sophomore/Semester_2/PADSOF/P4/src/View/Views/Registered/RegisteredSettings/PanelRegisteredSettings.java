package View.Views.Registered.RegisteredSettings;

import javax.swing.*;

import Controllers.Registered.RegisteredSettings.ControllerRegisteredSettings;
import java.awt.event.*;

import java.awt.*;

/**
 * This Panel allows the current Registered User to modify its password
 *
 *
 */
public class PanelRegisteredSettings extends JPanel {

	private JPasswordField cpass = new JPasswordField(20);
	private JPasswordField pass1 = new JPasswordField(20);
	private JPasswordField pass2 = new JPasswordField(20);

	private JLabel cpassl = new JLabel("Current Password:");
	private JLabel pass1l = new JLabel("New Password:");
	private JLabel pass2l = new JLabel("Repeat New Password:");

	private JButton bSetThreshold = new JButton("Change Password");

	private JButton bSignOut = new JButton("SignOut");

	private ControllerRegisteredSettings controller;

	/**
	 * This is the constructor of the RegisteredSettings that allows the user to
	 * change its password. The change of password takes into account if the
	 * password is the same as the new one, if the new one does not match its
	 * comprobation, etc.
	 */

	public PanelRegisteredSettings() {

		this.controller = new ControllerRegisteredSettings(this);
		this.setLayout(new BorderLayout());

		JPanel newPass = new JPanel(new GridLayout(3, 2));
		newPass.add(cpassl);
		newPass.add(cpass);
		newPass.add(pass1l);
		newPass.add(pass1);
		newPass.add(pass2l);
		newPass.add(pass2);

		this.add(newPass, BorderLayout.NORTH);
		JPanel pb = new JPanel();
		pb.add(bSetThreshold);
		pb.add(bSignOut);
		this.add(pb, BorderLayout.CENTER);

		bSetThreshold.addActionListener(x -> setPass(x));
		bSignOut.addActionListener(x -> signOut(x));
	}

	/**
	 * This method calls the method in the controller that changes the password of
	 * the logged registered user.
	 * 
	 * @param e select the button change password
	 */

	public void setPass(ActionEvent e) {

		String old = String.valueOf(this.cpass.getPassword());
		String new1 = String.valueOf(this.pass1.getPassword());
		String new2 = String.valueOf(this.pass2.getPassword());

		if (controller.bSetNewPassword(old, new1, new2)) {
			this.cpass.setText("");
			this.pass1.setText("");
			this.pass2.setText("");
		}

	}

	/**
	 * This method calls the method in the controller that logs out of the account
	 * and moves to the SignIn view.
	 * 
	 * @param e select the button sign out
	 */
	public void signOut(ActionEvent e) {
		controller.bSignOut();
	}
}
