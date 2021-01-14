package Model.Modules;

import java.util.*;

import Model.App.Application;

import java.io.*;

/**
 * This Group class contains all the esential information of groups, Extends
 * user because of the Compositte Pattern
 *
 *
 */
public class Group extends User implements Comparable, Serializable {
	/**
	 * name (String) name of the group description (String) description of the group
	 * registered (Registered) set of registered users that are in group subGroups
	 * (Group) set of subgroups that are in a group father (Group) the father of all
	 * subgroups depth (int) depth of the tree group owner (Registered) Register
	 * user owner of the group supportedProjects (Project) Set of supported projects
	 * by the group
	 */
	private String name;
	private String description;
	private Set<User> components;
	private int depth;
	private Registered owner;
	private Group father = null;
	private Set<Project> supportedProjects;

	/**
	 * This is the constructor of subgroup a method that initialize the atributes of
	 * a group
	 *
	 * @param name        name of the group
	 * @param description description of the group
	 * @param owner       Registered user owner of the group
	 * @param father      Is the group father of the subgroup
	 */
	public Group(String name, String description, Registered owner, Group father) {
		super(name, null, null);
		this.name = name;
		this.description = description;
		this.supportedProjects = new TreeSet<Project>();
		this.components = new TreeSet<User>();
		this.owner = owner;
		this.father = father;
		this.depth = calcDepth(this.father);
		this.owner.getMyCreatedGroups().add(this);

	}

	/**
	 * This is the constructor of group a method that initialize the atributes of a
	 * group that does not have a father (It is the root of the group tree)
	 *
	 * @param name        name of the group
	 * @param description description of the group
	 * @param owner       Register user owner of the group
	 */
	public Group(String name, String description, Registered owner) {
		super(name, null, null);
		this.name = name;
		this.description = description;
		this.supportedProjects = new TreeSet<Project>();
		this.components = new TreeSet<User>();
		this.owner = owner;
		this.depth = 0;
		this.owner.getMyCreatedGroups().add(this);
	}

	/**
	 * This method calculates the actual depth of a group
	 *
	 * @param father group father
	 * @return value of depth
	 */
	private int calcDepth(Group father) {
		if (father == null) {
			return 0;
		}
		return 1 + calcDepth(father.getFather());
	}

	/**
	 * This method set the owner of a group
	 *
	 *
	 * @param owner Registered user
	 */
	public void setOwner(Registered owner) {
		this.owner = owner;
	}

	/**
	 * This method obtains the group name
	 *
	 *
	 * @return group name
	 */
	public String getName() {
		return this.name;
	}

	/**
	 * This method adds a group to the list of subgroups
	 *
	 * @param g group to be add
	 * @return true if it has been added properly, false otherwise
	 */

	public boolean addSubGroup(Group g) {
		return this.components.add(g);
	}

	/**
	 * This method adds a project to the list of supported projects of a group
	 *
	 * @param p project that is going to be added
	 * @return true if the project has been added properly, false otherwise
	 */

	public boolean addSupportedProjects(Project p) {
		return this.supportedProjects.add(p);
	}

	/**
	 * This method obtains the owner of the group
	 *
	 * @return owner of a group
	 */
	public Registered getOwner() {
		return this.owner;
	}

	/**
	 * This method obtains the registered users of a group
	 *
	 * @return registered set of users
	 */
	public Set<Registered> getUsers() {
		Set<Registered> users = new TreeSet<Registered>();
		for (User c : this.components) {
			if (c instanceof Registered) {
				users.add((Registered) c);
			}
		}
		return users;
	}

	/**
	 * This method obtains the depth of the group
	 *
	 * @return depth of the group
	 */
	private int getDepth() {
		return this.depth;
	}

	/**
	 * This method obtains the group description
	 *
	 * @return group description
	 */
	public String getDescription() {
		return this.description;
	}

	/**
	 * This method obtains the father of the group
	 *
	 *
	 * @return father
	 */
	public Group getFather() {
		return this.father;
	}

	/**
	 * This method obtains the set of subgroups of a group
	 *
	 *
	 * @return set of subgroups
	 */
	public Set<Group> getSubGroups() {
		Set<Group> subGroups = new TreeSet<Group>();
		for (User c : this.components) {
			if (c instanceof Group) {
				subGroups.add((Group) c);
			}
		}
		return subGroups;
	}

	/**
	 * This method obtains the set of supported projects of a group
	 *
	 *
	 * @return set of supported projects of a group
	 */
	public Set<Project> getSupportedProjects() {
		return this.supportedProjects;
	}

	/**
	 * This method allow a registered user r to join a group
	 *
	 *
	 * @param r Registered user that wants to join the group
	 * @return true if a register user can joins a group and false if not
	 */
	public boolean joinGroup(Registered r) {
		Application app = Application.getApplication();
		if (r.isBanned() || this.components.contains(r)) {
			app.getCurrentUser()
					.sendNotification(new Notification((Object) Application.INSTANCE, "Error joining Group"));
			return false;
		}

		if (checkTree(r, getRoot())) {
			app.getCurrentUser().sendNotification(
					new Notification((Object) Application.INSTANCE, "You already belong to a group of the same kind"));
			return false;
		}
		this.components.add(r);
		app.getCurrentUser()
				.sendNotification(new Notification((Object) Application.INSTANCE, "You have joined " + this.name));
		r.getMyGroups().add(this);
		return true;

	}

	/**
	 * This method gets the root of a tree group
	 *
	 * @return father root
	 */
	public Group getRoot() {
		if (this.father == null) {
			return this;
		}
		return this.father.getRoot();
	}

	/**
	 * This method obtains the tree of a given group to check to which groups a
	 * registered user r belongs to. This method is used to check is the user can
	 * join a group of the tree
	 *
	 * @param r    Registered user to be searched in the tree
	 * @param root Root group of the tree
	 * @return true if everything OK else false
	 */
	private boolean checkTree(Registered r, Group root) {
		if (root.getUsers().contains(r) && root.getDepth() != this.depth) {
			return true;
		}
		for (Group g : root.getSubGroups()) {
			if (checkTree(r, g)) {
				return true;
			}
		}
		return false;
	}

	/**
	 * This method allow a registered user leave a group
	 *
	 *
	 * @param r Registered user
	 * @return true if a register user can leave a group and false if not
	 */
	public boolean leaveGroup(Registered r) {
		Application app = Application.getApplication();
		if (r.isBanned() || !this.components.contains(r)) {
			app.getCurrentUser()
					.sendNotification(new Notification((Object) Application.INSTANCE, "You can NOT leave the group"));
			return false;
		}

		this.components.remove(r);
		app.getCurrentUser()
				.sendNotification(new Notification((Object) Application.INSTANCE, "You have left group " + this.name));
		return true;

	}

	/**
	 * Override the compareTo method of a TreeSet to compare whether 2 groups are
	 * the same, it compares the name
	 *
	 * @param o groups to Compare
	 * @return 0 if the groups are equal, any number different from 0 if they are
	 *         not
	 */
	@Override
	public int compareTo(Object o) {
		if (o instanceof Registered) {
			Registered r = (Registered) o;
			return this.name.compareTo(r.getName());
		}
		Group p = (Group) o;
		return this.name.compareTo(p.name);
	}

	@Override
	public boolean equals(Object o) {
		Group p = (Group) o;
		return p.name.equals(this.name);
	}

	/**
	 * This method obtains an Affinity Report between two groups
	 *
	 * @param g1 group 1
	 * @param g2 group 2
	 * @return true if the Affinity Report is obtained otherwise false
	 */
	public static boolean getAffinityReport(Group g1, Group g2) {
		Application app = Application.getApplication();
		Registered user = (Registered) app.getCurrentUser();
		if (user.isBanned()) {
			user.sendNotification(
					new Notification((Object) Application.INSTANCE, "You can NOT ask for reports while banned"));
			return false;
		}
		if (!g1.getUsers().contains(user) || !g2.getUsers().contains(user)) {
			user.sendNotification(new Notification((Object) Application.INSTANCE,
					"You can NOT ask for a affinity report if you do NOT belong to both groups"));
			return false;
		}
		double div = (double) (getProjectsOfGroup(g1).size() + getProjectsOfGroup(g2).size());
		double result = 0;
		if (div > 0) {
			result = (getIntersectionOfProjects(g1, g2) + getIntersectionOfProjects(g2, g1)) / div;
		}

		user.sendNotification(new Notification((Object) Application.INSTANCE,
				"The affinity between group " + g1.getName() + " and " + g2.getName() + " is " + result * 100 + " %."));
		return true;
	}

	private static int getIntersectionOfProjects(Group g1, Group g2) {
		Application app = Application.getApplication();
		Set<Project> projectsG1 = getProjectsOfGroup(g1);
		int counter = 0;

		for (Iterator<Project> it = app.getProjects().iterator(); it.hasNext();) {
			Project aux = it.next();
			if (!aux.getTypeProponent()) { // If the proponent is a group
				Group g = (Group) aux.getProponent();
				if (g.equals(g1)) {
					projectsG1.add(aux);
				}
			}
		}

		Set<Project> small = null;
		Set<Project> great = null;
		if (projectsG1.size() > g2.getSupportedProjects().size()) {
			small = g2.getSupportedProjects();
			great = projectsG1;
		} else {
			small = projectsG1;
			great = g2.getSupportedProjects();
		}

		for (Project p : small) {
			if (great.contains(p)) {
				counter++;
			}
		}

		return counter;
	}

	/**
	 * This method obtains the projects of a group
	 *
	 * @param g1 group of wich we want to obtain the projects
	 * @return set of projects of the group
	 */

	private static Set<Project> getProjectsOfGroup(Group g1) {
		Application app = Application.getApplication();
		Set<Project> projectsG1 = new TreeSet<Project>();

		for (Iterator<Project> it = app.getProjects().iterator(); it.hasNext();) {
			Project aux = it.next();
			if (!aux.getTypeProponent()) { // If the proponent is a group
				Group g = (Group) aux.getProponent();
				if (g.equals(g1)) {
					projectsG1.add(aux);
				}
			}
		}
		return projectsG1;
	}
}

