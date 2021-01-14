package Model.App;

import java.io.*;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.*;
import Model.Modules.*;
import es.uam.eps.sadp.grants.*;
import javax.swing.*;
import static View.MainView.MainView;

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
	public static final String name = "CHVOTES";
	private int threshold = 1;
	private Set<Project> projects;
	private Set<Project> expiredProjects;
	private Set<Group> groups;
	private Set<Registered> users;
	private User currentUser = null;
	private Admin admin;
	protected Queue<Notification> notifications;
	private List<String> neighborhoods = null;
	private LocalDate date;

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
		this.date = LocalDate.now();
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
	 * The instance for the Singleton Pattern
	 *
	 * @return instance of admin of the application
	 */

	public static Admin getAdmin() {
		return INSTANCE.admin;
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
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		if (app.admin.equal(name, pass)) {
			app.currentUser = app.admin;
			return applicationAddNotification(new Notification((Object) Application.INSTANCE, "Admin Signed In"));
		}

		for (Iterator<Registered> it = app.getUsers().iterator(); it.hasNext();) {
			Registered r = it.next();
			if ((r.getName().equals(name) || r.getId().equals(name)) && r.getPassword().equals(pass)) {
				app.currentUser = r;
				applicationAddNotification(new Notification((Object) Application.INSTANCE, "Welcome " + r.getName()));
				if (app.currentUser.hasNotifications()) {
					for (Notification n : app.currentUser.getNotifications()) {
						JOptionPane.showMessageDialog(MainView, n);
					}
					app.currentUser.clearNotifications();
				}
				Application.checkProjects();
				return true;
			}
		}
		applicationAddNotification(new Notification((Object) Application.INSTANCE, "Wrong User"));
		return false;
	}

	/**
	 * This method allow new users to Sign up into the application
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
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		if (id.length() != 9 || !Character.isLetter(id.charAt(id.length() - 1))) {
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "Invalid NIF"));
			return false;
		}
		if (!pass.equals(pass2)) {
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "Passwords do not match"));
			return false;
		}
		Registered user = new Registered(name, pass, id);

		if (app.users.contains(user)) {
			applicationAddNotification(
					new Notification((Object) Application.INSTANCE, "The user is already in the application"));
			return false;
		}

		if (!app.admin.addUserToAccept(user)) {
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "Error registering"));
			return false;
		}
		return applicationAddNotification(
				new Notification((Object) Application.INSTANCE, "You must wait to be approved by the Admin"));
	}

	/**
	 * This method allows a user sing out of the application
	 *
	 * @return true if the user is signedOut successfully else false
	 */
	public static boolean signOut() {
		Application app = Application.getApplication();
		if (app.currentUser == null) {
			// applicationAddNotification(new Notification((Object)
			// Application.INSTANCE,"There is no User signed In"));
			return false;
		} else {
			app.currentUser.clearNotifications();
			app.currentUser = null;
		}
		return true;
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
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		if (app.currentUser == null) {
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "There is no user logged in"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}

		Group gfather = getGroupByName(father, app.groups);

		if (gfather == null) {

			applicationAddNotification(
					new Notification((Object) Application.INSTANCE, "There is no group named " + father));
			return false;
		}

		if (!gfather.getOwner().equals((Registered) app.currentUser)) {
			applicationAddNotification(new Notification((Object) Application.INSTANCE,
					"You can NOT create a group if you are not the owner"));
			return false;
		}

		Registered user = (Registered) app.currentUser;
		if (user.isBanned()) {
			user.sendNotification(new Notification((Object) user, "You can NOT create a group if you are banned"));
			return false;

		}

		g = new Group(name, description, (Registered) app.currentUser, gfather);
		if (!app.groups.add(g)) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Group Already Exists"));
			return false;
		}

		gfather.addSubGroup(g);
		return app.currentUser
				.sendNotification(new Notification((Object) Application.INSTANCE, "Group created successfully"));
	}

	/**
	 * This method allows a registered user create a new group (root)
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
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		if (app.currentUser == null) {
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "There is no user logged in"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}

		Registered user = (Registered) app.currentUser;
		if (user.isBanned()) {
			user.sendNotification(new Notification((Object) user, "You can NOT create a group if you are banned"));
			return false;
		}

		g = new Group(name, description, (Registered) app.currentUser);

		if (!app.groups.add(g)) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Group Already Exists"));
			return false;
		}

		g.joinGroup(user);
		return app.currentUser
				.sendNotification(new Notification((Object) Application.INSTANCE, "Group created successfully"));
	}

	/**
	 * This method shows all the notification of the application class: User
	 * notifications and Application notifications
	 *
	 * @return true if everything go well, otherwise false
	 */
	public static boolean showNotifications() {
		Application app = Application.getApplication();
		if (app.currentUser == null) {
			if (app.notifications.isEmpty()) {
				return false;
			}
		} else {
			System.out.println("\n\n!!!!!!!!!!!!!!USER: " + app.currentUser.getName() + "!!!!!!!!!!!!!!");

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
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "Invalid attributes"));
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
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "App NOT saved"));
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
		// applicationAddNotification(new Notification((Object)
		// Application.INSTANCE,"App saved"));
		return true;
	}

	/**
	 * This method load all the data of the application
	 *
	 * @param file the name of the file for reading the data
	 * @return true if everything go well, otherwise false
	 * @throws Exception exception 
	 */
	public static boolean restoreApplication(String file) throws Exception {
		Application app = Application.getApplication();
		if (file.length() == 0) {
			applicationAddNotification(new Notification((Object) Application.INSTANCE, "Invalid Arguments"));
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
			throw e;
		} finally {
			if (objectinputstream != null) {
				objectinputstream.close();
				streamIn.close();
			}
		}
		// applicationAddNotification(new Notification((Object)
		// Application.INSTANCE,"App restored succesfully"));
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

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}

		if (group.length() == 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid Arguments"));
			return false;
		}

		g = getGroupByName(group, app.groups);

		if (g == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "The group does NOT exist"));
			return false;
		}

		if (g.getOwner().equals(app.currentUser)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "You can NOT join your own group"));
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

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}

		if (group.length() == 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid attributes"));
			return false;
		}

		Registered user = (Registered) app.currentUser;
		Set<Group> usergroups = user.getMyGroups();
		Group g = getGroupByName(group, usergroups);

		if (g == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "The group does NOT exist"));
			return false;
		}
		if (user.isBanned()) {
			user.sendNotification(new Notification((Object) user, "You can NOT leave a group if you are banned"));
			return false;
		}
		if (g.getOwner().equals(user)) {
			user.sendNotification(new Notification((Object) user, "You can NOT leave your own group"));
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
	public static boolean createInfrastructureProject(String name, String description, double budget, String image,
			String neighborhood) {
		Application app = Application.getApplication();
		Project p = null;
		if (name.length() > 25 || name.length() == 0 || description.length() > 500 || description.length() == 0
				|| budget < 0 || image == null || !Application.getNeighborhoods().contains(neighborhood)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "Invalid attributes for a project"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}

		p = new Infrastructure(name, description, budget, image, neighborhood);

		if (app.projects.contains(p)) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Project Already Exists"));
			return false;
		}
		Registered user = (Registered) app.currentUser;
		if (user.isBanned()) {
			user.sendNotification(new Notification((Object) user, "You can NOT create a project if you are banned"));
			return false;
		}
		app.admin.addProjectToAccept(p);
		app.currentUser
				.sendNotification(new Notification((Object) Application.INSTANCE, "Project Waiting to be Accepted"));
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
	public static boolean createInfrastructureProject(String name, String description, double budget, String image,
			String neighborhood, String groupName) {

		Application app = Application.getApplication();
		Project p = null;
		if (name.length() > 25 || name.length() == 0 || description.length() > 500 || description.length() == 0
				|| budget < 0 || image == null || !Application.getNeighborhoods().contains(neighborhood)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "Invalid attributes for a project"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}
		Registered user = (Registered) app.currentUser;
		Group g = getGroupByName(groupName, user.getMyCreatedGroups());

		if (g == null) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE,
					"You are not the owner of " + groupName + " group"));
			return false;
		}

		p = new Infrastructure(name, description, budget, image, neighborhood, g);

		if (app.projects.contains(p)) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Project Already Exists"));
			return false;
		}
		if (user.isBanned()) {
			user.sendNotification(new Notification((Object) user, "You can NOT create a project if you are banned"));
			return false;
		}
		app.admin.addProjectToAccept(p);
		app.currentUser
				.sendNotification(new Notification((Object) Application.INSTANCE, "Project Waiting to be Accepted"));
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
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "Invalid attributes for a project"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}

		p = new Social(name, description, budget, aim, socialGroup);

		if (app.projects.contains(p)) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Project Already Exists"));
			return false;
		}
		Registered user = (Registered) app.currentUser;
		if (user.isBanned()) {
			user.sendNotification(new Notification((Object) user, "You can NOT create a project if you are banned"));
			return false;
		}

		app.admin.addProjectToAccept(p);
		app.currentUser
				.sendNotification(new Notification((Object) Application.INSTANCE, "Project Waiting to be Accepted"));
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
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "Invalid attributes for a project"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}

		Registered user = (Registered) app.currentUser;
		Group g = getGroupByName(groupName, user.getMyCreatedGroups());

		if (g == null) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE,
					"You are not the owner of " + groupName + " group"));
			return false;
		}

		p = new Social(name, description, budget, aim, socialGroup, g);

		if (app.projects.contains(p)) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Project Already Exists"));
			return false;
		}
		if (user.isBanned()) {
			user.sendNotification(new Notification((Object) user, "You can NOT create a project if you are banned"));
			return false;
		}
		app.admin.addProjectToAccept(p);
		app.currentUser
				.sendNotification(new Notification((Object) Application.INSTANCE, "Project Waiting to be Accepted"));
		return true;
	}

	/**
	 * This method lets the admin accept or reject projects
	 * @param projectName name of the project 
	 * @param reason The reason why the project is accepted or rejected
	 * @param accept Flag to see is a project is accepted or rejected
	 * @return true if the project gets accepted otherwise false
	 */
	public static boolean adminAcceptProject(String projectName, String reason, boolean accept) {
		Application app = Application.getApplication();
		if (reason.length() == 0 || reason.length() > 50) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		Project p = null;

		for (Iterator<Project> it = app.admin.getAcceptProject().iterator(); it.hasNext();) {
			Project aux = it.next();
			if (aux.getName().equals(projectName)) {
				p = aux;
				break;
			}
		}

		if (p == null) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "There is no project named " + projectName));
			return false;
		}

		if (!(app.currentUser instanceof Admin)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is NOT the administrator"));
			return false;
		}
		return app.admin.acceptProject(p, reason, accept);
	}

	/**
	 * This method lets the admin accept or reject a new user into the application
	 * @param username name of the user 
	 * @param accept Flag to see if an user is accepted or rejected
	 * @return true if the project gets accepted otherwise false
	 */
	public static boolean adminAcceptUser(String username, boolean accept) {
		Application app = Application.getApplication();

		if (!(app.currentUser instanceof Admin)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is NOT the administrator"));
			return false;
		}
		Registered r = null;

		for (Iterator<Registered> it = app.admin.getAcceptUser().iterator(); it.hasNext();) {
			Registered aux = it.next();
			if (aux.getName().equals(username)) {
				r = aux;
				break;
			}
		}

		return app.admin.acceptUser(r, accept);
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
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}
		Project p = getProjectByName(project, app.projects);

		if (p == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "The project does NOT exist"));
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
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}
		Project p = getProjectByName(project, app.projects);

		if (p == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "The project does NOT exist"));
			return false;
		}
		Group g = getGroupByName(group, app.groups);

		if (g == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "The group does NOT exist"));
			return false;
		}
		if (!g.getOwner().equals(app.currentUser)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "You are not the owner of group " + group));
			return false;
		}
		g.addSupportedProjects(p);
		return p.vote(g);
	}

	/**
	 * This method set a threshold in the application
	 *
	 * @param sthreshold threshold
	 * @return true if the threshold gets set otherwise false
	 */
	public static boolean setThreshold(String sthreshold) {
		Application app = Application.getApplication();
		int threshold = -1;
		try {
			threshold = Integer.parseInt(sthreshold);
		} catch (NumberFormatException e) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The written threshold is not numeric"));
			return false;
		}

		if (threshold == app.threshold) {
			return true;
		}

		if (!(app.currentUser instanceof Admin)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is NOT an Administrator"));
			return false;
		}
		if (threshold <= 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}
		app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Threshold set successfully"));
		app.threshold = threshold;

		return true;
	}

	/**
	 * This method checks all the projects of the app to see if all the projects of
	 * the app are ok
	 *
	 * @return true
	 */
	public static boolean checkProjects() {
		Application app = Application.getApplication();
		for (Project p : app.getProjects()) {
			p.removeBannedUsers();
			p.expiredProject();
		}
		CCGG.getGateway().setDate(INSTANCE.date);
		for (Project p : INSTANCE.getProjects()) {
			if (p.getFundable()) {
				Application.checkProjectCouncilHall(p.getName());
			}

		}
		return true;
	}

	/**
	 * This method implements the subscription of a Registered user to a project
	 *
	 * @param project project name
	 * @return true if a user subscribe into a project otherwise false
	 */
	public static boolean subscribe(String project) {
		Application app = Application.getApplication();
		Project p = null;
		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}
		if (project.length() == 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		p = getProjectByName(project, app.projects);

		if (p == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "That project does NOT exist"));
			return false;
		}
		return p.subscribe((Registered) app.currentUser);
	}

	/**
	 * This method lets the admin ban an unbanned user
	 *
	 * @param user user name
	 * @return true if a user gets banned else false
	 */
	public static boolean banUser(String user) {
		Application app = Application.getApplication();
		Registered r = null;
		if (!(app.currentUser instanceof Admin)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is NOT an Administrator"));
			return false;
		}
		if (user.length() == 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
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
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "That user does NOT exist"));
			return false;
		}
		app.currentUser
				.sendNotification(new Notification((Object) Application.INSTANCE, "You have banned user " + user));
		return r.banUser();
	}

	/**
	 * This method lets the admit unban a banned user
	 *
	 * @param user user name
	 * @return true if a user gets unbanned else false
	 */
	public static boolean unbanUser(String user) {
		Application app = Application.getApplication();
		Registered r = null;
		if (!(app.currentUser instanceof Admin)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is NOT an Administrator"));
			return false;
		}
		if (user.length() == 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
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
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "That user does NOT exist"));
			return false;
		}
		app.currentUser
				.sendNotification(new Notification((Object) Application.INSTANCE, "You have unbanned user " + user));
		return r.unbanUser();
	}

	/**
	 * This method implements an iterator to find a group object by its name
	 *
	 * @param name  name of the group
	 * @param group set of group
	 * @return group
	 */
	public static Group getGroupByName(String name, Set<Group> group) {
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
	 * This method implements an iterator to find a project by its name in a set of
	 * projects
	 *
	 * @param name    name of the project
	 * @param project set of project
	 * @return project
	 */
	public static Project getProjectByName(String name, Set<Project> project) {
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

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}
		if (project.length() == 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		p = getProjectByName(project, app.projects);

		if (p == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "The project does NOT exists."));
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

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}
		if (group1.length() == 0 || group2.length() == 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		g1 = getGroupByName(group1, app.groups);
		g2 = getGroupByName(group2, app.groups);

		if (g1 == null || g2 == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "The groups do NOT exists."));
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

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}
		if (group.length() == 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}

		g1 = getGroupByName(group, app.groups);
		if (g1 == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "The group does NOT exist."));
			return false;
		}

		if (!g1.getOwner().equals((Registered) app.currentUser)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "You are NOT the owner of group " + group));
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
	 * @return true if the project could be send else false
	 */
	public static boolean fundProject(String project) {
		Application app = Application.getApplication();
		Project p = null;
		boolean result = false;
		if (project.length() == 0) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, "Invalid arguments"));
			return false;
		}
		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}
		p = getProjectByName(project, app.projects);

		if (p == null) {
			app.currentUser
					.sendNotification(new Notification((Object) Application.INSTANCE, "This project does NOT exist"));
			return false;
		}
		if (!p.getFundable()) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The project is not fundable yet"));
			return false;
		}

		if (p.getTypeProponent()) { // If the proponent is a Registered user
			if (!(app.currentUser.equals((Registered) p.getProponent()))) {
				app.currentUser.sendNotification(
						new Notification((Object) Application.INSTANCE, "You are NOT the proponent of this project"));
				return false;
			}
		} else { // If the proponent is a group
			if (!(app.currentUser.equals(((Group) p.getProponent()).getOwner()))) {
				app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE,
						"You are NOT the owner of the group that proposed the project"));
				return false;
			}
		}

		if (p.getUniqueID() != null) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE,
					"You have already sent the project to the Council Hall"));
			return false;
		}

		try {
			result = CouncilHall.sendCouncilHall(p);
		} catch (IOException | InvalidRequestException e) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, e.toString()));
		}
		if (result) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "You have sent your project to the Council Hall"));
		}
		return result;
	}

	/**
	 * This method checks if a project that has been send is accepted or rejected by
	 * the council hall
	 *
	 * @param project name of the project
	 * @return true if it is fundable else false
	 */
	public static boolean checkProjectCouncilHall(String project) {
		Application app = Application.getApplication();
		Project p = null;
		boolean result = false;
		if (project.length() == 0) {

			return false;
		}
		if (!(app.currentUser instanceof Registered)) {
			
			return false;
		}
		p = getProjectByName(project, app.projects);

		if (p == null) {
		
			return false;
		}
		if (!p.getFundable()) {
			
			return false;
		}

		try {
			result = CouncilHall.checkProjectCouncilHall(p);
		} catch (IOException | InvalidIDException e) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE, e.toString()));
			return false;
		}

		return true;
	}

	/**
	 * This method checks if there are notifications in the notifications queue
	 * 
	 * @return true if there are notification, false otherwise
	 */
	public static boolean hasNotification() {
		Application app = Application.getApplication();
		return !app.notifications.isEmpty();
	}

	/**
	 * This method obtains a notification from the notifications queue
	 * @return obtains the notification 
	 */

	public static Notification getNotification() {
		Application app = Application.getApplication();
		return app.notifications.remove();
	}

	/**
	 * This method adds a notification n to the queue of notifications
	 * 
	 * @param n notification to add
	 * @return true if the notification has been added correctly, false otherwise
	 */
	public static boolean applicationAddNotification(Notification n) {
		Application app = Application.INSTANCE;
		JOptionPane.showMessageDialog(MainView, n);
		return app.notifications.add(n);
	}

	/**
	 * This method reads and adds to the application the list of Neighborhoods from
	 * a file
	 *
	 * @param filename name of the file where the Neighborhoods will be read
	 */

	public static void readNeighborhoods(String filename) {
		List<String> result = new ArrayList<String>();
		BufferedReader buffer = null;
		try {
			buffer = new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
		} catch (FileNotFoundException e2) {
			Application
					.applicationAddNotification(new Notification(Application.INSTANCE, "Error loading neighborhoods"));
			return;
		}

		String line;
		try {
			while ((line = buffer.readLine()) != null) {
				if (!result.contains(line)) {
					result.add(line);
				}
			}
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		try {
			buffer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		Application.INSTANCE.neighborhoods = result;
	}

	/**
	 * This method reads and adds to the application the list of Neighborhoods from
	 * a file
	 * 
	 * @return list of neighborhoods
	 *
	 */

	public static List<String> getNeighborhoods() {
		return Application.INSTANCE.neighborhoods;
	}

	/**
	 * This method returns the groups of the application
	 * 
	 * @return set of groups
	 *
	 */

	public Set<Group> getGroup() {
		return this.groups;
	}

	/**
	 * This method changes the password of a registered user
	 * 
	 * @param old  old password of the user
	 * @param new1 new password of the user
	 * @param new2 repeated new password for checking
	 * @return true if the password has been changed correctly, false otherwise
	 *
	 */

	public static boolean setNewPassword(String old, String new1, String new2) {

		if (old.length() == 0 || new1.length() == 0 || new2.length() == 0) {
			Application.applicationAddNotification(
					new Notification(Application.INSTANCE, "Invalid Arguments For changing the password"));
			return false;
		}

		Application app = Application.getApplication();

		if (!(app.currentUser instanceof Registered)) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The current user is an Administrator"));
			return false;
		}
		Registered user = (Registered) app.currentUser;

		if (!(user.getPassword().equals(old))) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE,
					"The introduced password does not match with your actual password."));
			return false;
		}

		if (!(new1.equals(new2))) {
			app.currentUser.sendNotification(
					new Notification((Object) Application.INSTANCE, "The new passwords do not match"));
			return false;
		}

		if (old.equals(new1)) {
			app.currentUser.sendNotification(new Notification((Object) Application.INSTANCE,
					"The new password is equal to your previous password"));
			return false;
		}

		app.currentUser.sendNotification(
				new Notification((Object) Application.INSTANCE, "Your password has been successfully changed!"));
		user.changePassword(new1);
		return true;
	}

	/**
	 * This method returns the date of the application
	 * 
	 * @return Date of the application
	 *
	 */

	public static LocalDate getDate() {
		return INSTANCE.date;
	}

	/**
	 * This method sets the date of the application
	 * 
	 * @param date date to be changed to
	 *
	 */

	public static void setDate(Date date) {
		INSTANCE.date = date.toInstant().atZone(ZoneId.systemDefault()).toLocalDate();
		INSTANCE.currentUser.sendNotification(
				new Notification((Object) Application.INSTANCE, "The date has been successfully changed"));
	}

}

