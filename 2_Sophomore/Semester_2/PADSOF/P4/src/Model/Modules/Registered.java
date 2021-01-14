package Model.Modules;

import java.util.*;

import Model.App.Application;

import java.io.*;

/**
 * This Registered class represents a user registered in the application
 *
 *
 */

public class Registered extends User implements Serializable {

	/**
	 * This are the attributes that
	 *
	 * myGroups (Group) Set Groups that the user belongs to myCreatedGroups (Group)
	 * Set of Groups that the user has created myProjects (Project) Set of Projects
	 * to which the user has voted myCreatedProjects (Project) Set of Projects that
	 * the user has created subsProjects (Project) Set of Projects that the user has
	 * subscribed to banned (Boolean) Flag to indicate if the user has been banned
	 */

	private Set<Group> myGroups;
	private Set<Group> myCreatedGroups;
	private Set<Project> myProjects;
	private Set<Project> myCreatedProjects;
	private Set<Project> subsProjects;
	private boolean banned = false;

	/**
	 * Constructor method: Initializes the Set of groups and projects to a HashSet
	 * and the banned flag to false
	 *
	 * @param username username of the user
	 * @param password password used to log in
	 * @param dni      dni of the user
	 */

	public Registered(String username, String password, String dni) {
		super(username, password, dni);
		this.myGroups = new TreeSet<Group>();
		this.myCreatedGroups = new TreeSet<Group>();
		this.myProjects = new TreeSet<Project>();
		this.myCreatedProjects = new TreeSet<Project>();
		this.subsProjects = new TreeSet<Project>();
		this.banned = false;
	}

	/**
	 * returns name of the registered user
	 *
	 * @return string name of the registered user
	 */

	public String getName() {
		return super.username;
	}

	/**
	 * returns the password of the registered user
	 *
	 * @return string password of the registered user
	 */

	public String getPassword() {
		return super.password;
	}

	/**
	 * returns Set of groups of the registered user
	 *
	 * @return Set of groups to which the registered user belongs to
	 */

	public Set<Group> getMyGroups() {
		return this.myGroups;
	}

	/**
	 * returns Set of created groups of the registered user
	 *
	 * @return Set of created groups , which the registered user belongs to
	 */

	public Set<Group> getMyCreatedGroups() {
		return this.myCreatedGroups;
	}

	/**
	 * returns Set of created projects of the registered user
	 *
	 * @return Set of created projects , which the registered user belongs to
	 */

	public Set<Project> getMyCreatedProjects() {
		return this.myCreatedProjects;
	}

	/**
	 * returns Set of projects of the registered user
	 *
	 * @return Set of projects to which the registered user belongs to
	 */

	public Set<Project> getMyProjects() {
		return this.myProjects;
	}

	/**
	 * returns Set of subscribed projects
	 *
	 * @return subscribed projects
	 */

	public Set<Project> getSubsProjects() {
		return this.subsProjects;
	}

	/**
	 * @param p Project to which the registered user is voting to
	 * @return true if the votation has been successful or false otherwise
	 */

	public boolean vote(Project p) {
		if (this.banned)
			return false;
		return p.vote(this);
	}

	/**
	 * this method sets the banned flag to true
	 *
	 * @return true if the user has been banned, false if it has been already banned
	 */

	public boolean banUser() {
		if (this.banned) {
			return false;
		}
		this.sendNotification(new Notification(Application.getAdmin(), "You have been banned"));
		this.banned = true;
		return true;
	}

	/**
	 * this method sets the banned flag to false
	 *
	 * @return true if the user has been unbanned, false if it already unbanned
	 */

	public boolean unbanUser() {
		if (!this.banned) {
			return false;
		}
		this.sendNotification(new Notification(Application.getAdmin(), "You have been unbanned"));
		this.banned = false;
		return true;
	}

	/**
	 * returns banned state of a user
	 *
	 * @return the banned flag value
	 */

	public boolean isBanned() {
		return this.banned;
	}

	/**
	 * @param g Group to be added to the myGroups Set
	 * @return true if the the group has been added successfully, false otherwise
	 */

	public boolean addMyGroups(Group g) {
		return this.myGroups.add(g);
	}

	/**
	 * @param p Project to be added to the subsProjects Set
	 * @return true if the the Project has been added successfully, false otherwise
	 */

	public boolean addsubsProjects(Project p) {
		return this.subsProjects.add(p);
	}

	/**
	 * This method shows all the queues of a user like : MyCreatedGroups , MyCreated
	 * Projects ....
	 */
	public void showMyQueues() {
		System.out.println("\n\n!!!!!! QUEUES of " + this.username + " !!!!!!");
		System.out.println("\nMyGroups\n");
		for (Group g : this.myGroups) {
			System.out.print(g.getName() + " ");
		}

		System.out.println("\nMyCreatedGroups\n");
		for (Group g : this.myCreatedGroups) {
			System.out.print(g.getName() + " ");
		}

		System.out.println("\nMyProjects\n");
		for (Project g : this.myProjects) {
			System.out.print(g.getName() + " ");
		}

		System.out.println("\nMyCreatedProjects\n");
		for (Project g : this.myCreatedProjects) {
			System.out.print(g.getName() + " ");
		}

		System.out.println("\nSubsProjects\n");
		for (Project g : this.subsProjects) {
			System.out.print(g.getName() + " ");
		}
	}

	public void changePassword(String new1) {
		this.password = new1;
	}
}

