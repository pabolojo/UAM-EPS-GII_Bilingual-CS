package Model.Modules;

import java.util.*;
import java.time.LocalDate;
import Model.App.Application;
import Model.modifiableDates.ModifiableDate;

import java.io.*;
import es.uam.eps.sadp.grants.GrantRequest;

/**
 *
 * This module contains the class Project , that manage all the information
 * related to projects
 *
 *
 */

public abstract class Project implements Comparable, Serializable, GrantRequest {
	/**
	 * This are the attributes that defines a project
	 *
	 * subUsers (Registered) Set of subscribed users voteUsers (Registered) Set of
	 * users that have voted name (String) name of the project description (String)
	 * description of the project budget (double) budget for the project
	 * grantedBudget (double) granted budget for the project numVotes (int) number
	 * of votes of a project fundable (boolean) attribute that tell us if is
	 * fundable or not expired (boolean) attribute that tell us if a project is
	 * expired or not date (LocalDate) date of creation gProponent (Group) group
	 * proponent rProponent (Registered) registered user proponent uniqueId (String)
	 * Id of a project setted by the Council Hall
	 */

	private Group gProponent = null;
	private Registered rProponent = null;
	private double grantedBudget;
	private Set<Registered> subUsers;
	private Set<Registered> voteUsers;
	private String name;
	private String description;
	private double budget;
	private int numVotes;
	private boolean fundable;
	private boolean expired;
	private LocalDate date;
	private String uniqueId;
	private boolean notified;
	private boolean notifiedExpired;

	/**
	 * Constructor of this class.
	 *
	 * This is the method that implements the constructor of project , this module
	 * Initialize the attributes of a project created by a single registered user
	 *
	 * @param name        name of the project
	 * @param description description of the project
	 * @param budget      budget for the project
	 */

	public Project(String name, String description, double budget) {
		Application app = Application.getApplication();
		this.name = name;
		this.description = description;
		this.budget = budget;
		this.fundable = false;
		this.numVotes = 0;
		this.date = null;
		this.subUsers = new TreeSet<Registered>();
		this.voteUsers = new TreeSet<Registered>();
		this.expired = false;
		this.rProponent = (Registered) app.getCurrentUser();
		this.uniqueId = null;
		this.grantedBudget = -1;
		this.notified = false;
		this.notifiedExpired = false;
	}

	/**
	 * Constructor of this class.
	 *
	 * This is the method that implements the constructor of project , this module
	 * Initialize the attributes of a project created by a group
	 *
	 * @param name        name of the project
	 * @param description description of the project
	 * @param budget      budget for the project
	 * @param proponent   group proponent
	 */

	public Project(String name, String description, double budget, Group proponent) {
		this.name = name;
		this.description = description;
		this.budget = budget;
		this.fundable = false;
		this.numVotes = 0;
		this.date = null;
		this.subUsers = new TreeSet<Registered>();
		this.voteUsers = new TreeSet<Registered>();
		this.expired = false;
		this.gProponent = proponent;
		this.uniqueId = null;
		this.grantedBudget = -1;
		this.notified = false;
		this.notifiedExpired = false;
	}

	/**
	 * This method add a registered user to a project
	 *
	 * @param r Registered user to suscribe to the project
	 * @return true if the user can subscribe, false otherwise
	 *
	 */
	public boolean subscribe(Registered r) {
		if (r.isBanned()) {
			r.sendNotification(
					new Notification((Object) Application.INSTANCE, "You can NOT subscribe if you are banned"));
			return false;
		}
		if (this.expired) {
			r.sendNotification(new Notification((Object) Application.INSTANCE,
					"You can NOT subscribe project " + this.name + " because it has expired"));
			return false;
		}
		if (!this.voteUsers.contains(r)) {
			r.sendNotification(
					new Notification((Object) Application.INSTANCE, "You can NOT subscribe if you have NOT voted"));
			return false;
		}
		if (r.getSubsProjects().contains(this)) {
			r.sendNotification(
					new Notification((Object) Application.INSTANCE, "You are already subscribed to " + this.name));
			return false;
		}
		r.sendNotification(
				new Notification((Object) Application.INSTANCE, "You have subscribed to project " + this.name));
		r.addsubsProjects(this);
		return this.subUsers.add(r);
	}

	/**
	 * This method implements votation to a project and adds the registered user
	 * into an Set of vote users
	 *
	 * @param r Registered user to vote to the project
	 * @return true if the votation get well and false if it is not
	 */
	public boolean vote(Registered r) {
		Application app = Application.getApplication();
		if (r.isBanned()) {
			r.sendNotification(new Notification((Object) Application.INSTANCE, "You can NOT vote when you are banned"));
			return false;
		}
		if (this.voteUsers.contains(r)) {
			r.sendNotification(
					new Notification((Object) Application.INSTANCE, "You already voted to project " + this.name));
			return false;
		}
		if (this.expired) {
			r.sendNotification(new Notification((Object) Application.INSTANCE,
					"You can NOT vote project " + this.name + " because it has expired"));
			return false;
		}
		this.numVotes++;

		if (app.getThreshold() == this.numVotes) {
			this.fundable = true;
			for (Registered re : this.subUsers) {
				re.sendNotification(
						new Notification((Object) Application.INSTANCE, "Project " + this.name + " is now fundable!"));
			}
		}
		r.sendNotification(new Notification((Object) Application.INSTANCE, "You have voted project " + this.name));
		this.date = Application.getDate();
		r.getMyProjects().add(this);
		return this.voteUsers.add(r);
	}

	/**
	 * This method implements votation to a project and adds the registered user
	 * into an Set of vote users
	 *
	 * @return true if the votation get well and false if it is not
	 */
	public boolean vote() {
		Application app = Application.getApplication();
		Registered r = (Registered) app.getCurrentUser();
		return vote(r);
	}

	/**
	 * This method implement the votation to a project and by a group and introduces
	 * the registered users of the group into an Set of vote users Recursive method
	 * 
	 * @param g Group that will vote to the project
	 * @return true if the votation get well and false if it is not
	 */
	public boolean vote(Group g) {
		Set<Registered> totalUsers = new TreeSet<Registered>();
		voteRec(g, totalUsers);
		for (Registered r : totalUsers) {
			vote(r);
		}
		return true;
	}

	public void voteRec(Group g, Set<Registered> totalUsers) {
		totalUsers.addAll(g.getUsers());
		for (Group sg : g.getSubGroups()) {
			voteRec(sg, totalUsers);
		}
	}

	/**
	 * This method checks if a project has been expired
	 *
	 * @return true if the project that we are looking is expired and false if it is
	 *         not
	 */
	public boolean expiredProject() {
		if (Application.getDate().minusDays(30).isAfter(this.date) && !notifiedExpired) {
			Application app = Application.getApplication();
			notifiedExpired = true;
			app.getExpiredProjects().add(this);
			this.expired = true;
			this.fundable = false;
			for (Registered r : this.subUsers) {
				r.sendNotification(
						new Notification((Object) Application.INSTANCE, "Project " + this.name + " has expired"));
			}
			return true;
		}
		return false;
	}

	/**
	 * This method adds a project to the pending list projects of the administrator
	 * The admin would afterwards accept or reject the project
	 */
	public void acceptProjects() {
		Admin admin = Admin.getAdmin();
		admin.addProjectToAccept(this);
	}

	/**
	 * This method obtains a Popularity Report for this project
	 *
	 * @return true if the Popularity Report is obtain otherwise false
	 */
	public boolean getPopularityReport() {
		Application app = Application.getApplication();
		Registered user = (Registered) app.getCurrentUser();
		if (user.isBanned()) {
			user.sendNotification(
					new Notification((Object) Application.INSTANCE, "You can NOT ask for reports while banned"));
			return false;
		}
		if (!this.voteUsers.contains(user)) {
			user.sendNotification(new Notification((Object) Application.INSTANCE,
					"You can NOT ask for a popularity report if you have NOT voted"));
			return false;
		}
		user.sendNotification(new Notification((Object) Application.INSTANCE,
				"Project: " + this.name + " has " + this.numVotes + " votes."));
		return true;
	}

	/**
	 * This method sets the unique Id
	 * 
	 * @param uniqueId unique id of the project
	 */
	public void setUniqueID(String uniqueId) {
		this.uniqueId = uniqueId;
	}

	/**
	 * This method sets the granted Budget
	 * 
	 * @param granted granted budget
	 * @return true if budget is set , false otherwise
	 */
	public boolean setGrantedBudget(double granted) {
		this.grantedBudget = granted;
		if (granted == 0) {
			for (Registered r : this.subUsers) {
				r.sendNotification(new Notification((Object) Application.INSTANCE,
						"Project " + this.name + " has been rejected by the Council Hall"));
			}
			return false;
		}
		for (Registered r : this.subUsers) {
			r.sendNotification(new Notification((Object) Application.INSTANCE,
					"Project " + this.name + " has been accepted by the Council Hall with budget " + granted));
		}
		return true;
	}

	/**
	 * This method return the number votes
	 *
	 * @return the numVotes
	 */
	public int getNumVotes() {
		return numVotes;
	}

	/**
	 * This method return the fundable flag
	 *
	 * @return fundable flag
	 */
	public boolean getFundable() {
		return this.fundable;
	}

	/**
	 * This method return the granted Budget
	 *
	 * @return granted Budget
	 */
	public double getGrantedBudget() {
		return this.grantedBudget;
	}

	/**
	 * This method return the Unique Id
	 *
	 * @return Unique Id
	 */
	public String getUniqueID() {
		return this.uniqueId;
	}

	/**
	 * This method updates the date
	 *
	 */
	public void updateDate() {
		this.date = Application.getDate();
	}

	/**
	 * This method return the proponent of a project
	 *
	 * @return proponent of a project
	 */
	public Object getProponent() {
		if (gProponent == null) {
			return rProponent;
		}
		return gProponent;
	}

	/**
	 * This method returns the type of the proponent of a project
	 *
	 * @return 0 if it is a group, 1 if it is a registered
	 */
	public boolean getTypeProponent() {
		if (this.getProponent() instanceof Group) {
			return false;
		}
		return true;
	}

	/**
	 * This method return the name of a project
	 *
	 * @return the name
	 */

	public String getName() {
		return this.name;
	}

	/**
	 * Override the equals method to check if two projects are equal This can happen
	 * if the names of the projects are equal
	 *
	 * @param o Project to Compare
	 * @return true if the Project are equal, false if they are not
	 */

	@Override
	public boolean equals(Object o) {

		if (o == null || this.getClass() != o.getClass()) {
			return false;
		}

		Project p = (Project) o;

		if (p.name.equals(this.name))
			return true;

		return false;
	}

	/**
	 * Override the compareTo method of a TreeSet to compare wether 2 projects are
	 * the same, it compares the name
	 *
	 * @param o Project to Compare
	 * @return 0 if the projects are equal, any number different from 0 if they are
	 *         not
	 */
	@Override
	public int compareTo(Object o) {
		Project p = (Project) o;
		return this.name.compareTo(p.name);
	}

	/**
	 * This method return the Description of a project
	 *
	 * @return description
	 */
	public String getDescription() {
		return this.description;
	}

	/**
	 * This method return the budget of a project
	 *
	 * @return budget
	 */
	public double getBudget() {
		return this.budget;
	}

	/**
	 * This method sets the notified flag
	 * @param notified notification flag 
	 *
	 */
	public void setNotified(boolean notified) {
		this.notified = notified;
	}

	/**
	 * This method return the subscribed users of the project
	 *
	 * @return subscribed users of the project
	 */
	public Set<Registered> getSubUsers() {
		return this.subUsers;
	}

	/**
	 * This method return the expired state of the project
	 *
	 * @return expired
	 */
	public boolean getExpired() {
		return this.expired;
	}

	/**
	 * This method return the notified state of a project
	 *
	 * @return notified
	 */
	public boolean getNotified() {
		return this.notified;
	}

	/**
	 * This method remove the ban users votes
	 */

	public void removeBannedUsers() {
		int votes = 0;
		for (Registered r : this.voteUsers) {
			if (!r.isBanned()) {
				votes++;
			}
		}
		this.numVotes = votes;
	}

	/**
	 * This method return the description of a project
	 *
	 * @return description
	 */
	@Override
	public String getProjectDescription() {
		return this.description;
	}

	/**
	 * This method return the title of a project
	 *
	 * @return name of the project
	 */
	@Override
	public String getProjectTitle() {
		return this.name;
	}

	/**
	 * This method return the granted budget of a project
	 *
	 * @return budget
	 */
	@Override
	public double getRequestedAmount() {
		return this.budget;
	}

}

