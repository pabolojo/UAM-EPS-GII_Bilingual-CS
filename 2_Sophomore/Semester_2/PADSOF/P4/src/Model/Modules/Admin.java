package Model.Modules;

import java.util.*;
import Model.App.Application;
import java.io.*;

/**
 * This Admin class contains all the information related with admin
 *
 */

public class Admin extends User implements Serializable {
	/**
	 * INSTANCE this is the variable needed for the implementation of the singleton
	 * pattern acceptProjects this is a queue with the project that have to be
	 * accepted password this is the password of the admin
	 */
	public static Admin INSTANCE;
	private Queue<Project> acceptProjects;
	private Queue<Registered> acceptUsers;
	private static String password = "admin";

	/**
	 * This is the constructor of Admin. This method initialize the attributes of
	 * admin
	 *
	 * @param username username of the admin
	 * @param password password of the admin
	 * @param dni      dni of the admin
	 */
	private Admin(String username, String password, String dni) {
		super(username, password, dni);
		this.acceptProjects = new LinkedList<Project>();
		this.acceptUsers = new LinkedList<Registered>();
	}

	/**
	 * This method return the instance of the admin
	 *
	 * @return INSTANCE a single instance for admin is needed because we only have
	 *         one admin so we don´t need more instantiation
	 */
	public static Admin getAdmin() {
		if (INSTANCE == null) {
			initAdmin();
		}
		return INSTANCE;
	}

	/**
	 * This method instance the Admin object
	 */
	public static void initAdmin() {
		INSTANCE = new Admin("admin", Admin.password, "00000000X");
	}

	/**
	 * This method adds a project to the queue of projects to accept
	 *
	 * @param p project to introduce
	 * @return true if the project is added else false
	 */
	public boolean addProjectToAccept(Project p) {
		return acceptProjects.add(p);
	}

	/**
	 * This method lets the admin accept or reject a project with a reason.
	 *
	 * @param p      project to be accepted or rejected
	 * @param reason reason to accept or reject the project
	 * @param accept boolean
	 * @return true if we added the accepted project to the list of accepted
	 *         projects
	 */
	public boolean acceptProject(Project p, String reason, boolean accept) {
		Application app = Application.getApplication();

		Object proponent = p.getProponent();
		this.acceptProjects.remove(p);
		if (accept) {
			if (p.getTypeProponent()) { // If the proponent is a registered user
				Registered rproponent = (Registered) proponent;
				rproponent.sendNotification(new Notification((Object) this,
						"Your project " + p.getName() + " has been accepted. Reason: " + reason));
				p.vote(rproponent);
				p.subscribe(rproponent);
				rproponent.getMyCreatedProjects().add(p);
			} else { // If the proponent is a group
				Group gproponent = (Group) proponent;
				gproponent.getOwner().sendNotification(new Notification((Object) this,
						"Your project " + p.getName() + " has been accepted. Reason: " + reason));
				p.vote(gproponent);
				boolean ownerInGroup = false;
				gproponent.getOwner().getMyCreatedProjects().add(p);
				for (Registered r : gproponent.getUsers()) {
					p.subscribe(r);
					if (r.equals(gproponent.getOwner())) {
						ownerInGroup = true;
					}
				}
				if (!ownerInGroup) {
					p.vote(gproponent.getOwner());
					p.subscribe(gproponent.getOwner());
				}
			}
			app.getCurrentUser().sendNotification(
					new Notification((Object) app.getCurrentUser(), "You have accepted project " + p.getName()));
			p.updateDate();
			return app.addProject(p);
		} else {
			if (p.getTypeProponent()) { // If the proponent is a registered user
				Registered rproponent = (Registered) proponent;
				rproponent.sendNotification(new Notification((Object) this,
						"Your project " + p.getName() + " has been rejected. Reason: " + reason));
			} else { // If the proponent is a group
				Group gproponent = (Group) proponent;
				gproponent.getOwner().sendNotification(new Notification((Object) this,
						"Your project " + p.getName() + " has been rejected. Reason: " + reason));
			}
			app.getCurrentUser().sendNotification(
					new Notification((Object) app.getCurrentUser(), "You have rejected project " + p.getName()));
		}
		return true;
	}

	/**
	 * This method let the admin accept a new user into the application
	 *
	 * @param r      User to be registered
	 * @param accept boolean
	 * @return true if we added the user to the application users
	 */
	public boolean acceptUser(Registered r, boolean accept) {
		Application app = Application.getApplication();

		if (acceptUsers.isEmpty()) {
			app.getCurrentUser()
					.sendNotification(new Notification((Object) app.getCurrentUser(), "There are no users to accept"));
			return false;
		}

		if (accept) {
			app.addUser(r);
			app.getCurrentUser().sendNotification(
					new Notification((Object) Application.INSTANCE, "The user has been registered in the application"));
			r.sendNotification(new Notification((Object) this, "You have been approved!"));
		} else {
			app.getCurrentUser().sendNotification(new Notification((Object) Application.INSTANCE,
					"The user has NOT been registered in the application"));
		}

		return this.acceptUsers.remove(r);
	}

	/**
	 * This method obtains the queue of accepted projects
	 *
	 * @return queue with the accepted projects
	 */
	public Queue<Project> getAcceptProject() {
		return this.acceptProjects;
	}

	/**
	 * This method implements an equals method to check if two admins are equal.
	 * This happens if the names of the admin is equal to the stablished password
	 *
	 * @param username username to compare
	 * @param pass     password to compare
	 * @return true if the admins are equal, false if they are not
	 */

	public boolean equal(String username, String pass) {

		if (this.username.equals(username) && Admin.password.equals(pass))
			return true;

		return false;
	}

	public boolean addUserToAccept(Registered r) {
		return this.acceptUsers.add(r);
	}

	public Queue<Registered> getAcceptUser() {
		return this.acceptUsers;
	}

	public Project getProjectByName(String name) {
		Project p = null;
		for (Iterator<Project> it = acceptProjects.iterator(); it.hasNext();) {
			Project aux = it.next();
			if (aux.getName().equals(name)) {
				p = aux;
				break;
			}
		}
		return p;
	}
}

