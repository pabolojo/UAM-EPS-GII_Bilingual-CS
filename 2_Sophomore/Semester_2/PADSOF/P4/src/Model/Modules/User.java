package Model.Modules;

import java.util.*;
import Model.App.Application;
import java.io.*;
import javax.swing.*;
import static View.MainView.MainView;

/**
 * This User class represents the users that the application can contain.
 *
 *
 */

public abstract class User implements Comparable, Serializable {

	/**
	 * This are the attributes that
	 *
	 * dni (String) dni of the user password (String) password stored when a user
	 * registers username (String) username of the users account notfications
	 * (Notification) Queue that represents the pending notifications of the users
	 *
	 */

	protected String dni;
	protected String password;
	protected String username;
	protected Queue<Notification> notifications;

	/**
	 * Constructor method
	 *
	 * @param username username of the user
	 * @param password password used to log in
	 * @param dni      dni of the user
	 */

	public User(String username, String password, String dni) {
		this.dni = dni;
		this.password = password;
		this.username = username;
		this.notifications = new LinkedList<Notification>();
	}

	/**
	 * Creates a string with the Id, username and password of a user
	 *
	 * @return String with the user information
	 */

	@Override
	public String toString() {
		return dni + ", " + username + ", " + password;
	}

	/**
	 * Override the compareTo method of a TreeSet to compare whether 2 users are the
	 * same, it compares the username and the iD
	 *
	 * @param o User to Compare
	 * @return 0 if the users are equal, any number different from 0 if they are not
	 */

	@Override
	public int compareTo(Object o) {
		if (o instanceof Group) {
			Group g = (Group) o;
			return this.username.compareTo(g.getName());
		}
		User p = (User) o;
		int comparename = this.username.compareTo(p.username);
		int comparedni = this.dni.compareTo(p.dni);
		if (comparename != 0) {
			if (comparedni != 0) {
				return comparename;
			}
		}
		return 0;
	}

	/**
	 * Override the equals method to check if two users are equal This can happen if
	 * the IDs of the users are equal, or their username is the same
	 *
	 * @param o User to Compare
	 * @return true if the users are equal, false if they are not
	 */

	@Override
	public boolean equals(Object o) {
		if (o == null || this.getClass() != o.getClass()) {
			return false;
		}

		User p = (User) o;

		if (p.dni.equals(this.dni))
			return true;

		if (p.username.equals(this.username))
			return true;

		return false;
	}

	/**
	 * returns the queue of the notifications
	 *
	 * @return Queue of the notifications pending
	 */
	public Queue<Notification> getNotifications() {
		return notifications;
	}

	/**
	 * This method obtains the user name
	 *
	 *
	 * @return user name
	 */
	public String getName() {
		return this.username;
	}

	/**
	 * This method obtains the user's id
	 *
	 *
	 * @return user's id
	 */
	public String getId() {
		return this.dni;
	}

	/**
	 * Adds a notification to the queue of notifications pending
	 *
	 * @param n Notification
	 * @return true if the notification has inserted properly, false otherwise
	 */

	public boolean sendNotification(Notification n) {
		if (Application.INSTANCE.getCurrentUser().equals(this)) {
			JOptionPane.showMessageDialog(MainView, n);
		}
		return this.notifications.add(n);
	}

	/**
	 * Deletes all the notification to the queue of notifications pending
	 *
	 */
	public void clearNotifications() {
		this.notifications.clear();
	}

	/**
	 * Check if there are notifications in the queue of noitifications
	 *
	 * @return true if there are notifications, false if there are not.
	 */

	public boolean hasNotifications() {
		return !this.notifications.isEmpty();
	}
}

