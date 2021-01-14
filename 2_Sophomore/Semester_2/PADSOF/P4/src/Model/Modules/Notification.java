package Model.Modules;

import java.io.Serializable;
import java.time.LocalDate;
import Model.App.Application;

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
	private String from;
	private LocalDate date;

	/**
	 * This is the constructor of notification
	 * 
	 * @param from sender of the notification
	 * @param text text of the notification
	 */
	public Notification(Object from, String text) {
		if (from instanceof Application) {
			this.from = "Application";
		} else if (from instanceof User) {
			this.from = ((User) from).getName();
		} else {
			this.from = "";
		}

		this.text = text;
		this.date = Application.getDate();
	}

	/**
	 * This method prints the Notification as a String
	 *
	 * @return text of the notification
	 */
	@Override
	public String toString() {
		return this.from + "\n" + this.text + "\n" + date;
	}

	public String getNotification() {
		return this.text;
	}

}

