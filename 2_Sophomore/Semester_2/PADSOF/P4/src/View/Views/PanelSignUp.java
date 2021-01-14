package View.Views;

import View.MainView;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import Controllers.ControllerSignUp;

/**
 * This Panel contains the SignUp implementatios that lets a user register into
 * the app
 *
 *
 */
public class PanelSignUp extends JPanel {
	private JLabel username = new JLabel("Username: ");
	private JLabel id = new JLabel("ID: ");
	private JLabel psw = new JLabel("Introduce your password: ");
	private JLabel psw2 = new JLabel("Reintroduce your password: ");

	private JTextField user = new JTextField(20);;
	private JTextField dni = new JTextField(20);;
	private JPasswordField password = new JPasswordField(20);
	private JPasswordField password2 = new JPasswordField(20);
	private ImageIcon image;
	private JLabel picLabel;

	private ControllerSignUp controller;

	private JButton bSignUp = new JButton("SignUp");
	private JButton bSignIn = new JButton("SignIn");

	/**
	 * This is the constructor of the signUp Panel with several Labels and Text
	 * fields for the user to fill up and register in the application It also counts
	 * with a button to move to the SignIn Panel
	 */

	public PanelSignUp() {
		this.controller = new ControllerSignUp(this);
		this.setLayout(new BorderLayout());
		this.image = new ImageIcon("files/Images/CHVOTES.png");
		this.picLabel = new JLabel(image);

		JPanel pn = new JPanel(new GridLayout(4, 2));
		pn.add(username);
		pn.add(user);
		pn.add(id);
		pn.add(dni);
		pn.add(psw);
		pn.add(password);
		pn.add(psw2);
		pn.add(password2);

		this.add(pn, BorderLayout.CENTER);
		JPanel pb = new JPanel();
		pb.add(bSignIn);
		pb.add(bSignUp);
		this.add(pb, BorderLayout.SOUTH);

		Image scaledImage = image.getImage().getScaledInstance(100, 100, Image.SCALE_SMOOTH);
		Icon icon = new ImageIcon(scaledImage);
		picLabel.setIcon(icon);
		this.add(picLabel, BorderLayout.NORTH);

		bSignUp.addActionListener(x -> signUp(x));
		bSignIn.addActionListener(x -> signIn(x));
	}

	/**
	 * This method call the method bSignUp implemented in the controller that
	 * registers a user into the app
	 * 
	 * @param event select the button signUp
	 */
	public void signUp(ActionEvent event) {
		String user = this.user.getText();
		String id = this.dni.getText();
		String psw = String.valueOf(this.password.getPassword());
		String psw2 = String.valueOf(this.password2.getPassword());

		controller.bSignUp(user, id, psw, psw2);
	}

	/**
	 * This method calls the method in the controller to move to the SignIn Panel
	 * 
	 * @param event select the button signIN
	 */
	public void signIn(ActionEvent event) {
		controller.bSignIn();
	}
}

