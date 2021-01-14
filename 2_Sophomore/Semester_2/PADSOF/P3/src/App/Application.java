package App;

import java.io.*;
import java.util.*;
import Modules.*;
import es.uam.eps.sadp.grants.*;

/**
 * This Application class contains all the essential information of the
 * application
 *
 *
 */
public class Application implements Serializable {
	/**
	 * This are the attributes of application
	 *
	 * INSTANCE (Application) This variable contains the singleton pattern instance
	 * name (String) This variable contains the name of the application threshold
	 * (Int)The Threshold of votation for a project projects (Project) Set of
	 * projects (Non expired), currently in the Application expiredProjects
	 * (Project) Set with the expired projects groups (Group) Set with the groups of
	 * the application users (Registered) Set with the registered users currentUser
	 * (User) The current user that is working on the app admin (Admin) The admin of
	 * the application notifications (Notification) Notifications of the app
	 *
	 */
	public static Application INSTANCE;
	private String name = "CHVOTES";
	private int threshold = -1;
	private Set<Project> projects;
	private Set<Project> expiredProjects;
	private Set<Group> groups;
	private Set<Registered> users;
	private User currentUser = null;
	private Admin admin;
	protected Queue<Notification> notifications;

	/**
	 * This is the constructor of application This method initialize the attributes
	 * of application
	 */
	private Application() {
		this.admin = Admin.getAdmin();
		this.projects = new TreeSet<Project>();
		this.expiredProjects = new TreeSet<Project>();
		this.groups = new TreeSet<Group>();
		this.users = new TreeSet<Registered>();
		this.notifications = new LinkedList<Notification>();
	}

	/**
	 * The instance for the Singleton Pattern
	 *
	 * @return instance of application
	 */

	public static Application getApplication() {
		if (INSTANCE == null)
			INSTANCE = new Application();
		return INSTANCE;
	}

	/**
	 * This method add a user to the Set of users
	 *
	 * @param user Registered user that is going to be add
	 * @return true if we correctly add the user to the Set of users, false
	 *         otherwise
	 */
	public boolean addUser(Registered user) {
		return this.users.add(user);
	}

	/**
	 * This method add a Project to the Set of users
	 *
	 * @param project Project that is going to be add
	 * @return true if we add correctly the project to the Set of projects else
	 *         false
	 */
	public boolean addProject(Project project) {
		return this.projects.add(project);
	}

	/**
	 * This method add a group to the Set of groups
	 *
	 * @param group group that is going to be add
	 * @return true if we add correctly the group to the Set of groups else false
	 */
	public boolean addGroup(Group group) {
		return this.groups.add(group);
	}

	/**
	 * This method obtains the set of expired projects
	 *
	 * @return Set of expired projects
	 */
	public Set<Project> getExpiredProjects() {
		return expiredProjects;
	}

	/**
	 * This method sets a given expired Project Set
	 *
	 * @param expiredProjects set of expired projects
	 */
	public void setExpiredProjects(Set<Project> expiredProjects) {
		this.expiredProjects = expiredProjects;
	}

	/**
	 * This method obtains the threshold
	 *
	 * @return Threshold
	 */
	public int getThreshold() {
		return this.threshold;
	}

	/**
	 * This method obtains the set of projects
	 *
	 * @return Set of projects
	 */
	public Set<Project> getProjects() {
		return this.projects;
	}

	/**
	 * This method obtains the set of users
	 *
	 * @return Set of users
	 */
	public Set<Registered> getUsers() {
		return this.users;
	}

	/**
	 * This method obtains the current user
	 *
	 * @return current user
	 */
	public User getCurrentUser() {
		return this.currentUser;
	}

	/**
	 * This method allow a register user Sign in into the application
	 *
	 * @param name name of the registered user that wants to Sign In
	 * @param pass password of the registered user that wants to Sign In
	 * @return true if the notification is added correctly to the notification set
	 *         else false
	 */
	public static boolean signIn(String name, String pass) {
		Application app = Application.getApplication();
		if (name.length() == 0 || pass.length() == 0) {
			app.notifications.add(new Notification("Invalid arguments"));
			return false;
		}
		Application.checkProjects();
		if (app.admin.equal(name, pass)) {
			app.currentUser = app.admin;
			return app.notifications.add(new Notification("Admin Signed In"));
		}

		for (Iterator<Registered> it = app.getUsers().iterator(); it.hasNext();) {
			Registered r = it.next();
			if ((r.getName().equals(name) || r.getId().equals(name)) && r.getPassword().equals(pass)) {
				app.currentUser = r;
				return app.notifications.add(new Notification("Signed In"));
			}
		}
		app.notifications.add(new Notification("Wrong User"));
		return false;
	}

	/**
	 * This method allow everyone to Sign up into the application
	 *
	 * @param name  name of the registered user that wants to Sign Up
	 * @param pass  password of the user registered that wants to Sign UP
	 * @param pass2 repeat the password
	 * @param id    the NIF of a new user
	 * @return true if the notification is added correctly to the notification set
	 *         else false
	 */
	public static boolean signUp(String name, String pass, String pass2, String id) {
		Application app = Application.getApplication();

		if (name.length() == 0 || pass.length() == 0) {
			app.notifications.add(new Notification("Invalid arguments"));
			return false;
		}

		if (id.length() != 9 || !Character.isLetter(id.charAt(id.length() - 1))) {
			app.notifications.add(new Notification("Invalid NIF"));
			return false;
		}
		if (!pass.equals(pass2)) {
			app.notifications.add(new Notification("Passwords do not match"));
			return false;
		}
		Registered user = new Registered(name, pass, id);

		if (!app.addUser(user)) {
			app.notifications.add(new Notification("User already exists"));
			return false;
		}
		return app.notifications.add(new Notification("User registered"));
	}

	/**
	 * This method allows a user sing out of the application
	 *
	 * @return true if the notification is added correctly to the notification set
	 *         else false
	 */
	public static boolean signOut() {
		Application app = Application.getApplication();
		if (app.currentUser == null) {
			app.notifications.add(new Notification("There is no User signed In"));
			return false;
		}
		app.currentUser = null;
		return app.notifications.add(new Notification("Signed Out"));
	}

	/**
	 * This method allows a registered user to create a new subgroup
	 *
	 * @param name        name of the group
	 * @param description description of the group
	 * @param father      name of the super group
	 * @return true if the notification is added correctly to the notification set
	 *         else false
	 */
	public static boolean createGroup(String name, String description, String father) {
		Application app = Application.getApplication();
		Group g = null;

		if (name.length() == 0 || description.length() == 0 || father.length() == 0) {
			app.notifications.add(new Notification("Invalid arguments"));
			return false;
		}

		if (app.currentUser == null) {
			app.notifications.add(new Notification("There is no user logged in"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}

		Group gfather = getGroupByName(father, app.groups);

		if (gfather == null) {
			app.notifications.add(new Notification("There is no group named " + father));
			return false;
		}
		if (!gfather.getOwner().equals((Registered) app.currentUser)) {
			app.notifications.add(new Notification("You can NOT create a group if you are not the owner"));
			return false;
		}
		g = new Group(name, description, (Registered) app.currentUser, gfather);
		if (!app.groups.add(g)) {
			app.currentUser.sendNotification(new Notification("Group Already Exists"));
			return false;
		}
		Registered user = (Registered) app.currentUser;
		if (user.isBanned()) {
			user.sendNotification(new Notification("You can NOT create a group if you are banned"));
			return false;
		}
		gfather.addSubGroup(g);
		return app.currentUser.sendNotification(new Notification("Group created successfully"));
	}

	/**
	 * This method allows a registered user create a new group
	 *
	 * @param name        name of the group
	 * @param description description of the group
	 * @return true if the notification is added correctly to the notification set
	 *         else false
	 */
	public static boolean createGroup(String name, String description) {
		Application app = Application.getApplication();
		Group g = null;

		if (name.length() == 0 || description.length() == 0) {
			app.notifications.add(new Notification("Invalid arguments"));
			return false;
		}

		if (app.currentUser == null) {
			app.notifications.add(new Notification("There is no user logged in"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		g = new Group(name, description, (Registered) app.currentUser);

		if (!app.groups.add(g)) {
			app.currentUser.sendNotification(new Notification("Group Already Exists"));
			return false;
		}

		Registered user = (Registered) app.currentUser;
		if (user.isBanned()) {
			user.sendNotification(new Notification("You can NOT create a group if you are banned"));
			return false;
		}
		g.joinGroup(user);
		return app.currentUser.sendNotification(new Notification("Group created successfully"));
	}

	/**
	 * This method shows all the notification of the application class: User
	 * notifications and Application notifications
	 *
	 * @return true if everything go well, otherwise false
	 */
	public static boolean showNotifications() {
		Application app = Application.getApplication();
		System.out.println("\n\n!!!!!!!!!!!!!!USER: " + app.currentUser.getName() + "!!!!!!!!!!!!!!");
		if (app.currentUser == null) {
			if (app.notifications.isEmpty()) {
				return false;
			}
		} else {
			Queue<Notification> notifications = app.currentUser.getNotifications();
			if (notifications.isEmpty() && app.notifications.isEmpty()) {
				return false;
			}
			System.out.println("\nUser Notifications:\n");

			for (Notification n : notifications) {
				System.out.println(n);
			}
			app.currentUser.clearNotifications();
		}

		System.out.println("\nApp Notifications:\n");

		for (Notification n : app.notifications) {
			System.out.println(n);
		}
		app.notifications.clear();

		return true;
	}

	/**
	 * This method save the currently session for the app
	 *
	 * @param file the name of the file for saving the data
	 * @throws IOException Throws errors to IOException
	 * @return true if everything go well, otherwise false
	 */
	public static boolean saveApplication(String file) throws IOException {
		Application app = Application.getApplication();
		if (file.length() == 0) {
			app.notifications.add(new Notification("Invalid attributes"));
			return false;
		}
		ObjectOutputStream oos = null;
		FileOutputStream fout = null;
		try {
			fout = new FileOutputStream(file);
			oos = new ObjectOutputStream(fout);
			oos.writeObject(Application.getApplication());
		} catch (Exception ex) {
			ex.printStackTrace();
			app.notifications.add(new Notification("App NOT saved"));
			if (oos != null) {
				oos.close();
				fout.close();
			}
			return false;

		} finally {
			if (oos != null) {
				oos.close();
				fout.close();
			}
		}
		app.notifications.add(new Notification("App saved"));
		return true;
	}

	/**
	 * This method load all the data of the application
	 *
	 * @param file the name of the file for reading the data
	 * @throws IOException Throws errors to IOException
	 * @return true if everything go well, otherwise false
	 */
	public static boolean restoreApplication(String file) throws IOException {
		Application app = Application.getApplication();
		if (file.length() == 0) {
			app.notifications.add(new Notification("Invalid Arguments"));
			return false;
		}
		ObjectInputStream objectinputstream = null;
		FileInputStream streamIn = null;
		try {
			streamIn = new FileInputStream(file);
			objectinputstream = new ObjectInputStream(streamIn);
			Application readCase = null;
			readCase = (Application) objectinputstream.readObject();
			if (readCase == null) {
				if (objectinputstream != null) {
					objectinputstream.close();
					streamIn.close();
				}
				return false;
			}
			Application.INSTANCE = readCase;
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (objectinputstream != null) {
				objectinputstream.close();
				streamIn.close();
			}
		}
		app.notifications.add(new Notification("App restored succesfully"));
		return true;
	}

	/**
	 * This method allow a registered user to join a group
	 *
	 * @param group the name of the group that is gone to be joined
	 * @return true if the user joins the group otherwise false
	 */
	public static boolean joinGroup(String group) {

		Application app = Application.getApplication();
		Group g = null;

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}

		if (group.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid Arguments"));
			return false;
		}

		g = getGroupByName(group, app.groups);

		if (g == null) {
			app.currentUser.sendNotification(new Notification("The group does NOT exist"));
			return false;
		}

		if (g.getOwner().equals(app.currentUser)) {
			app.currentUser.sendNotification(new Notification("You can NOT join your own group"));
			return false;
		}

		return g.joinGroup((Registered) app.currentUser);
	}

	/**
	 * This method allow a registered user to leave a group
	 *
	 * @param group the name of the group that is gone to be leaved
	 * @return true if the user leaves the group otherwise false
	 */
	public static boolean leaveGroup(String group) {

		Application app = Application.getApplication();

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}

		if (group.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid attributes"));
			return false;
		}

		Registered user = (Registered) app.currentUser;
		Set<Group> usergroups = user.getMyGroups();
		Group g = getGroupByName(group, usergroups);

		if (g == null) {
			app.currentUser.sendNotification(new Notification("The group does NOT exist"));
			return false;
		}
		if (user.isBanned()) {
			user.sendNotification(new Notification("You can NOT leave a group if you are banned"));
			return false;
		}
		if (g.getOwner().equals(user)) {
			user.sendNotification(new Notification("You can NOT leave your own group"));
			return false;
		}
		user.getMyGroups().remove(g);
		return g.leaveGroup((Registered) app.currentUser);
	}

	/**
	 * This method allows a registered user to create a Infrastructure project as an
	 * individual Registered citizen
	 *
	 * @param name         group name that is gone to be created
	 * @param description  description of the project
	 * @param budget       budget of the project
	 * @param image        graphic schema
	 * @param neighborhood the neighborhood where it is going to be created the
	 *                     project
	 * @return true if the project gets created otherwise false
	 */
	public static boolean createInfrastructureProject(String name, String description, double budget, File image,
			String neighborhood) {
		Application app = Application.getApplication();
		Project p = null;
		if (name.length() > 25 || name.length() == 0 || description.length() > 500 || description.length() == 0
				|| budget < 0 || image == null || !Infrastructure.getNeighborhoods().contains(neighborhood)) {
			app.currentUser.sendNotification(new Notification("Invalid attributes for a project"));
			return false;
		}

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}

		p = new Infrastructure(name, description, budget, image, neighborhood);

		if (app.projects.contains(p)) {
			app.currentUser.sendNotification(new Notification("Project Already Exists"));
			return false;
		}
		Registered user = (Registered) app.currentUser;
		if (user.isBanned()) {
			user.sendNotification(new Notification("You can NOT create a project if you are banned"));
			return false;
		}
		app.admin.addProjectToAccept(p);
		app.currentUser.sendNotification(new Notification("Project Waiting to be Accepted"));
		return true;
	}

	/**
	 * This method allows a registered user to create a Infrastructure project as a
	 * group
	 *
	 * @param name         project name that is gone to be created
	 * @param description  description of the project
	 * @param budget       budget of the project
	 * @param image        graphic schema
	 * @param neighborhood the neighborhood where it is going to be created the
	 *                     project
	 * @param groupName    group name
	 * @return true if the project gets created otherwise false
	 */
	public static boolean createInfrastructureProject(String name, String description, double budget, File image,
			String neighborhood, String groupName) {

		Application app = Application.getApplication();
		Project p = null;
		if (name.length() > 25 || name.length() == 0 || description.length() > 500 || description.length() == 0
				|| budget < 0 || image == null || !Infrastructure.getNeighborhoods().contains(neighborhood)) {
			app.currentUser.sendNotification(new Notification("Invalid attributes for a project"));
			return false;
		}

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		Registered user = (Registered) app.currentUser;
		Group g = getGroupByName(groupName, user.getMyCreatedGroups());

		if (g == null) {
			app.getCurrentUser().sendNotification(new Notification("You are not the owner of " + groupName + " group"));
			return false;
		}

		p = new Infrastructure(name, description, budget, image, neighborhood, g);

		if (app.projects.contains(p)) {
			app.currentUser.sendNotification(new Notification("Project Already Exists"));
			return false;
		}
		if (user.isBanned()) {
			user.sendNotification(new Notification("You can NOT create a project if you are banned"));
			return false;
		}
		app.admin.addProjectToAccept(p);
		app.currentUser.sendNotification(new Notification("Project Waiting to be Accepted"));
		return true;
	}

	/**
	 * This method allows a registered user to create a Social project as an
	 * individual Registered citizen
	 * 
	 * @param name        project name that is gone to be created
	 * @param description description of the project
	 * @param budget      budget of the project
	 * @param aim         aim could be national or international
	 * @param socialGroup The social group that will be benefited
	 * @return true if the project gets created otherwise false
	 */
	public static boolean createSocialProject(String name, String description, double budget, boolean aim,
			String socialGroup) {
		Application app = Application.getApplication();
		Project p = null;
		if (name.length() > 25 || name.length() == 0 || description.length() == 0 || description.length() > 500
				|| budget < 0 || socialGroup.length() > 50 || socialGroup.length() == 0) {
			app.currentUser.sendNotification(new Notification("Invalid attributes for a project"));
			return false;
		}

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}

		p = new Social(name, description, budget, aim, socialGroup);

		if (app.projects.contains(p)) {
			app.currentUser.sendNotification(new Notification("Project Already Exists"));
			return false;
		}
		Registered user = (Registered) app.currentUser;
		if (user.isBanned()) {
			user.sendNotification(new Notification("You can NOT create a project if you are banned"));
			return false;
		}

		app.admin.addProjectToAccept(p);
		app.currentUser.sendNotification(new Notification("Project Waiting to be Accepted"));
		return true;
	}

	/**
	 * This method allows a registered user to create a Social project as a group
	 *
	 * @param name        project name that is gone to be created
	 * @param description description of the project
	 * @param budget      budget of the project
	 * @param aim         aim could be national or international
	 * @param socialGroup social group that is going to be benefited
	 * @param groupName   name of the group that creates the project
	 * @return true if the project gets created otherwise false
	 */
	public static boolean createSocialProject(String name, String description, double budget, boolean aim,
			String socialGroup, String groupName) {
		Application app = Application.getApplication();
		Project p = null;
		if (name.length() > 25 || name.length() == 0 || description.length() > 500 || description.length() == 0
				|| budget < 0 || socialGroup.length() > 50 || socialGroup.length() == 0) {
			app.currentUser.sendNotification(new Notification("Invalid attributes for a project"));
			return false;
		}

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}

		Registered user = (Registered) app.currentUser;
		Group g = getGroupByName(groupName, user.getMyCreatedGroups());

		if (g == null) {
			app.getCurrentUser().sendNotification(new Notification("You are not the owner of " + groupName + " group"));
			return false;
		}

		p = new Social(name, description, budget, aim, socialGroup, g);

		if (app.projects.contains(p)) {
			app.currentUser.sendNotification(new Notification("Project Already Exists"));
			return false;
		}
		if (user.isBanned()) {
			user.sendNotification(new Notification("You can NOT create a project if you are banned"));
			return false;
		}
		app.admin.addProjectToAccept(p);
		app.currentUser.sendNotification(new Notification("Project Waiting to be Accepted"));
		return true;
	}

	/**
	 * This method lets the admin accept or reject projects
	 *
	 * @param reason The reason why the project is accepted or rejected
	 * @param accept Flag to see is a project is accepted or rejected
	 * @return true if the project gets accepted otherwise false
	 */
	public static boolean adminAcceptProject(String reason, boolean accept) {
		Application app = Application.getApplication();
		if (reason.length() == 0 || reason.length() > 50) {
			app.currentUser.sendNotification(new Notification("Invalid arguments"));
			return false;
		}
		if (!(app.getCurrentUser() instanceof Admin)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is NOT the administrator"));
			return false;
		}
		return app.admin.acceptProject(reason, accept);
	}

	/**
	 * This method allows a Registered User to vote a project
	 *
	 * @param project name of the project
	 * @return true if the user could otherwise false
	 */
	public static boolean voteProject(String project) {
		Application app = Application.getApplication();
		if (project.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		Project p = getProjectByName(project, app.projects);

		if (p == null) {
			app.currentUser.sendNotification(new Notification("The project does NOT exist"));
			return false;
		}
		return p.vote();
	}

	/**
	 * This method implements the Group votation to a project
	 *
	 * @param project name of the project
	 * @param group   name of the group
	 * @return true if the group could vote otherwise false
	 */
	public static boolean voteProject(String project, String group) {
		Application app = Application.getApplication();
		if (project.length() == 0 || group.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		Project p = getProjectByName(project, app.projects);

		if (p == null) {
			app.currentUser.sendNotification(new Notification("The project does NOT exist"));
			return false;
		}
		Group g = getGroupByName(group, app.groups);

		if (g == null) {
			app.currentUser.sendNotification(new Notification("The group does NOT exist"));
			return false;
		}
		if (!g.getOwner().equals(app.currentUser)) {
			app.currentUser.sendNotification(new Notification("You are not the owner of group " + group));
			return false;
		}
		g.addSupportedProjects(p);
		return p.vote(g);
	}

	/**
	 * This method set a threshold in the application
	 *
	 * @param threshold threshold
	 * @return true if the threshold gets set otherwise false
	 */
	public static boolean setThreshold(int threshold) {
		Application app = Application.getApplication();

		if (!(app.getCurrentUser() instanceof Admin)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is NOT an Administrator"));
			return false;
		}
		if (threshold <= 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}

		app.threshold = threshold;
		return true;
	}

	/**
	 * check all the projects of the app to see if all the projects of the app are
	 * ok
	 *
	 * @return true
	 */
	public static boolean checkProjects() {
		Application app = Application.getApplication();
		for (Project p : app.getProjects()) {
			p.removeBannedUsers();
			p.expiredProject();
		}
		return true;
	}

	/**
	 * This method implements the subscition of a Registered user
	 *
	 * @param project project name
	 * @return true if a user subscribe into a project otherwise false
	 */
	public static boolean subscribe(String project) {
		Application app = Application.getApplication();
		Project p = null;
		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		if (project.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}

		p = getProjectByName(project, app.projects);

		if (p == null) {
			app.getCurrentUser().sendNotification(new Notification("That project does NOT exist"));
			return false;
		}
		return p.subscribe((Registered) app.currentUser);
	}

	/**
	 * This method lets the admin ban a user
	 *
	 * @param user user name
	 * @return true if a user gets banned else false
	 */
	public static boolean banUser(String user) {
		Application app = Application.getApplication();
		Registered r = null;
		if (!(app.getCurrentUser() instanceof Admin)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is NOT an Administrator"));
			return false;
		}
		if (user.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}

		for (Iterator<Registered> it = app.users.iterator(); it.hasNext();) {
			Registered aux = it.next();
			if (aux.getName().equals(user)) {
				r = aux;
				break;
			}
		}
		if (r == null) {
			app.getCurrentUser().sendNotification(new Notification("That user does NOT exist"));
			return false;
		}
		app.getCurrentUser().sendNotification(new Notification("You have banned user " + user));
		return r.banUser();
	}

	/**
	 * This method lets the admin unban a user
	 *
	 * @param user user name
	 * @return true if a user gets unbanned else false
	 */
	public static boolean unbanUser(String user) {
		Application app = Application.getApplication();
		Registered r = null;
		if (!(app.getCurrentUser() instanceof Admin)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is NOT an Administrator"));
			return false;
		}
		if (user.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}

		for (Iterator<Registered> it = app.users.iterator(); it.hasNext();) {
			Registered aux = it.next();
			if (aux.getName().equals(user)) {
				r = aux;
				break;
			}
		}
		if (r == null) {
			app.getCurrentUser().sendNotification(new Notification("That user does NOT exist"));
			return false;
		}
		app.getCurrentUser().sendNotification(new Notification("You have unbanned user " + user));
		return r.unbanUser();
	}

	/**
	 * This method implements an iterator to find a group object by its name
	 *
	 * @param name  name of the group
	 * @param group set of group
	 * @return group
	 */
	private static Group getGroupByName(String name, Set<Group> group) {
		Group g = null;
		for (Iterator<Group> it = group.iterator(); it.hasNext();) {
			Group aux = it.next();
			if (aux.getName().equals(name)) {
				g = aux;
				break;
			}
		}
		return g;
	}

	/**
	 * This method implements an iterator to find a group project by its name
	 *
	 * @param name    name of the project
	 * @param project set of project
	 * @return project
	 */
	private static Project getProjectByName(String name, Set<Project> project) {
		Project p = null;
		for (Iterator<Project> it = project.iterator(); it.hasNext();) {
			Project aux = it.next();
			if (aux.getName().equals(name)) {
				p = aux;
				break;
			}
		}
		return p;
	}

	/**
	 * This method give us the popularity report of a project
	 *
	 * @param project name of project
	 * @return true if everything gets well else false
	 */
	public static boolean getPopularityReport(String project) {
		Application app = Application.getApplication();
		Project p = null;

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		if (project.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}

		p = getProjectByName(project, app.projects);

		if (p == null) {
			app.getCurrentUser().sendNotification(new Notification("The project does NOT exists."));
			return false;
		}
		return p.getPopularityReport();
	}

	/**
	 * This method give us the Affinity report between two groups
	 *
	 * @param group1 name of group 1
	 * @param group2 name of group 2
	 * @return true if everything gets well else false
	 */
	public static boolean getAffinityReport(String group1, String group2) {
		Application app = Application.getApplication();
		Group g1 = null, g2 = null;

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		if (group1.length() == 0 || group2.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}

		g1 = getGroupByName(group1, app.groups);
		g2 = getGroupByName(group2, app.groups);

		if (g1 == null || g2 == null) {
			app.getCurrentUser().sendNotification(new Notification("The groups do NOT exists."));
			return false;
		}
		return Group.getAffinityReport(g1, g2);
	}

	/**
	 * This method give us the Popularity report of a project created by a group
	 *
	 * @param group name of group that is going to ask for the popularity report
	 * @return true if everything gets well else false
	 */
	public static boolean getPopularityReportsOfGroup(String group) {
		Application app = Application.getApplication();
		Group g1 = null;

		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		if (group.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}

		g1 = getGroupByName(group, app.groups);
		if (g1 == null) {
			app.getCurrentUser().sendNotification(new Notification("The group does NOT exist."));
			return false;
		}

		if (!g1.getOwner().equals((Registered) app.currentUser)) {
			app.getCurrentUser().sendNotification(new Notification("You are NOT the owner of group " + group));
			return false;
		}

		for (Project p : g1.getSupportedProjects()) {
			p.getPopularityReport();
		}
		return true;
	}

	/**
	 * This method implements the functionality of sending a project to the Council
	 * Hall for his acceptance or rejection
	 * 
	 * @param project name of the project
	 * @throws IOException             Throws errors to IOException
	 * @throws InvalidRequestException Throws errors to InvalidRequestException
	 * @return true if the project could be send else false
	 */
	public static boolean fundProject(String project) throws IOException, InvalidRequestException {
		Application app = Application.getApplication();
		Project p = null;
		boolean result = false;
		if (project.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}
		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		p = getProjectByName(project, app.projects);

		if (p == null) {
			app.getCurrentUser().sendNotification(new Notification("This project does NOT exist"));
			return false;
		}
		if (!p.getFundable()) {
			app.getCurrentUser().sendNotification(new Notification("The project is not fundable yet"));
			return false;
		}

		if (p.getTypeProponent()) { // If the proponent is a Registered user
			if (!(app.getCurrentUser().equals((Registered) p.getProponent()))) {
				app.getCurrentUser().sendNotification(new Notification("You are NOT the proponent of this project"));
				return false;
			}
		} else { // If the proponent is a group
			if (!(app.getCurrentUser().equals(((Group) p.getProponent()).getOwner()))) {
				app.getCurrentUser().sendNotification(
						new Notification("You are NOT the owner of the group that proposed the project"));
				return false;
			}
		}

		try {
			result = CouncilHall.sendCouncilHall(p);
		} catch (IOException | InvalidRequestException e) {
			app.getCurrentUser().sendNotification(new Notification(e.toString()));
		}
		if (result) {
			app.currentUser.sendNotification(new Notification("You have sent your project to the Council Hall"));
		}
		return result;
	}

	/**
	 * This method checks if a project that has been send is accepted or rejected by
	 * the council hall
	 * 
	 * @param project name of the project
	 * @throws IOException        Throws errors to IOException
	 * @throws InvalidIDException Throws errors to InvalidIDException
	 * @return true if it is fundable else false
	 */
	public static boolean checkProjectCouncilHall(String project) throws IOException, InvalidIDException {
		Application app = Application.getApplication();
		Project p = null;
		boolean result = false;
		if (project.length() == 0) {
			app.getCurrentUser().sendNotification(new Notification("Invalid arguments"));
			return false;
		}
		if (!(app.getCurrentUser() instanceof Registered)) {
			app.getCurrentUser().sendNotification(new Notification("The current user is an Administrator"));
			return false;
		}
		p = getProjectByName(project, app.projects);

		if (p == null) {
			app.getCurrentUser().sendNotification(new Notification("This project does NOT exist"));
			return false;
		}
		if (!p.getFundable()) {
			app.getCurrentUser().sendNotification(new Notification("The project is not fundable yet"));
			return false;
		}

		if (p.getTypeProponent()) { // If the proponent is a Registered user
			if (!(app.getCurrentUser().equals((Registered) p.getProponent()))) {
				app.getCurrentUser().sendNotification(new Notification("You are NOT the proponent of this project"));
				return false;
			}
		} else { // If the proponent is a group
			if (!(app.getCurrentUser().equals(((Group) p.getProponent()).getOwner()))) {
				app.getCurrentUser().sendNotification(
						new Notification("You are NOT the owner of the group that proposed the project"));
				return false;
			}
		}

		try {
			result = CouncilHall.checkProjectCouncilHall(p);
		} catch (IOException | InvalidIDException e) {
			app.getCurrentUser().sendNotification(new Notification(e.toString()));
		}
		return result;
	}
}

