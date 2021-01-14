package View.Views;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import Controllers.ControllerSingIn;
import Model.App.Application;

/**
 * This Panel contains the Sign In implementation and the view of their
 * elements.
 *
 *
 */
public class PanelSignIn extends JPanel {
	private JLabel userLabel = new JLabel("User:");
	private JLabel passLabel = new JLabel("Password/ ID:");
	private JTextField user = new JTextField(20);
	private JPasswordField pass = new JPasswordField(20);
	private JButton bSignIn = new JButton("SignIn");
	private JButton bSignUp = new JButton("SignUp");
	private ImageIcon image;
	private JLabel picLabel;
	private ControllerSingIn controller;

	/**
	 * This is the constructor of the signIn Panel with several Labels and Text
	 * fields for the user to fill up and enter the application It also counts with
	 * a button to move to the SignUp Panel
	 */
	public PanelSignIn() {
		this.controller = new ControllerSingIn(this);
		this.image = new ImageIcon("files/Images/CHVOTES.png");
		this.picLabel = new JLabel(image);

		this.setLayout(new BorderLayout());
		JPanel pn = new JPanel(new GridLayout(2, 2));
		pn.add(userLabel);
		pn.add(user);
		pn.add(passLabel);
		pn.add(pass);
		this.add(pn, BorderLayout.CENTER);

		JPanel pb = new JPanel();
		pb.add(bSignIn);
		pb.add(bSignUp);
		this.add(pb, BorderLayout.SOUTH);

		Image scaledImage = image.getImage().getScaledInstance(100, 100, Image.SCALE_SMOOTH);
		Icon icon = new ImageIcon(scaledImage);
		picLabel.setIcon(icon);
		this.add(picLabel, BorderLayout.NORTH);

		bSignIn.addActionListener(x -> signIn(x));
		bSignUp.addActionListener(x -> signUp(x));
	}

	/**
	 * This method call the method bSignIn implemented in the controller that logs
	 * in a user into the app
	 * 
	 * @param evento select the button sign In
	 */
	public void signIn(ActionEvent evento) {
		this.controller.bSignIn(this.user.getText(), String.valueOf(this.pass.getPassword()));
	}

	/**
	 * This method calls the method in the controller to move to the SignUp Panel
	 * 
	 * @param evento select the button signUp
	 */
	public void signUp(ActionEvent evento) {
		this.controller.bSignUp();
	}
}

