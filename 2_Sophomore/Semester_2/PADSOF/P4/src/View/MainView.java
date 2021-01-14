package View;

import javax.swing.*;

import Model.App.Application;

import java.awt.*;
import java.io.IOException;
import java.util.Stack;

/**
 * This class contains the MainView implementation which is and extends of the
 * JFrame , this class controls all the views in the application
 *
 *
 */
public class MainView extends JFrame {
	private Container container;
	private JPanel currentView;
	public static MainView MainView;
	private static Stack<JPanel> stack;

	/**
	 * This is the constructor of MainView , this constructor have two parameter one
	 * for the name of the application and another one for the initial panel that its
	 * going to be executed first , also in this constructor we call the methods
	 * restoreApplication that restore the previous season and saveApplication for
	 * save the session before close the app
	 * 
	 * @param titulo
	 * @param initial
	 */
	private MainView(String titulo, JPanel initial) {
		super(titulo);

		this.currentView = initial;
		this.add(this.currentView);
		this.stack = new Stack<JPanel>();

		this.container = this.getContentPane();
		this.container.setLayout(new FlowLayout());

		try {
			Application.restoreApplication("savefile");
		} catch (Exception e) {
			JOptionPane.showMessageDialog(MainView.MainView, "Error Restoring " + Application.name);
		}

		Application.readNeighborhoods("files/Neighborhoods");

		this.addWindowListener(new java.awt.event.WindowAdapter() {
			@Override
			public void windowClosing(java.awt.event.WindowEvent windowEvent) {
				if (JOptionPane.showConfirmDialog(MainView.MainView,
						"Are you sure you want to close " + Application.name + "?", null, JOptionPane.YES_NO_OPTION,
						JOptionPane.QUESTION_MESSAGE) == JOptionPane.YES_OPTION) {
					Application.signOut();
					try {
						Application.saveApplication("savefile");
					} catch (IOException e) {
						JOptionPane.showMessageDialog(MainView.MainView, "Error Saving " + Application.name);
					}
					System.exit(0);
				}
			}
		});

		this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		this.setSize(500, 400);
		this.setVisible(true);
	}

	/**
	 * This method gets the MainView
	 * 
	 * @param titulo  title of the app
	 * @param initial initial panel
	 * @return MainView the actual view
	 */
	public static MainView getMainView(String titulo, JPanel initial) {
		if (MainView == null)
			MainView = new MainView(titulo, initial);
		return MainView;
	}

	/**
	 * This method set a View adding a new view to the container and removing the
	 * previous view
	 * 
	 * @param view the view that you want to see 
	 */
	public static void setView(JPanel view) {

		MainView.container.add(view);
		MainView.currentView.setVisible(false);
		MainView.container.remove(MainView.currentView);
		MainView.currentView = view;
	}

	/**
	 * This method adds a view into the stack
	 * 
	 * @param view new view 
	 */
	public static void stackView(JPanel view) {
		MainView.stack.push(view);
		MainView.container.add(view);
		MainView.currentView.setVisible(false);
	}

	/**
	 * This method lets you go back into the view that you have inserted in the
	 * stack
	 */
	public static void unStackView() {
		JPanel current = MainView.stack.pop();
		if (current != null) {
			current.setVisible(false);
			MainView.container.add(MainView.currentView);
			MainView.currentView.setVisible(true);
			MainView.container.remove(current);
		}
	}
}

