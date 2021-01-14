package Modules;

import java.io.Serializable;

/**
 *
 * This module contains the class Notification , that is the class that
 * implements the feedback for a registered user and for the application
 *
 *
 */
public class Notification implements Serializable {

	/**
	 * text text of the notification
	 */
	private String text;

	/**
	 * This is the constructor of notification
	 *
	 * @param text text of the notification
	 */
	public Notification(String text) {
		this.text = text;
	}

	/**
	 * This method prints the Notification as a String
	 *
	 * @return text of the notification
	 */
	@Override
	public String toString() {
		return this.text;
	}
}

