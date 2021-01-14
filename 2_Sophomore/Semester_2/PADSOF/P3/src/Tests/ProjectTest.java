package Tests;

import static org.junit.jupiter.api.Assertions.*;

import java.io.File;

import org.junit.jupiter.api.Test;

import App.Application;
import Modules.Registered;
import Modules.Social;

/**
 * This ProjectTest class test all the functionalities of the project class
 * 
 * 
 *
 */

class ProjectTest {

	/**
	 * This method implements the functionalities of project
	 * 
	 */
	@Test
	void Project() {
		File f = new File("hello.txt");

		Application app = Application.getApplication();
		/** SignUp */
		Application.signUp("Pepe", "123", "123", "12345678L");
		Application.signUp("Manuel", "123", "123", "22345678L");
		Application.signUp("Josete", "123", "123", "33345678L");
		Application.signUp("Pedrito", "123", "123", "55345678L");
		Application.signUp("El Jincho", "123", "123", "77456789L");
		/** Pepe Sign in */
		Application.signIn("Pepe", "123");

		/** Pepe creates a group */
		assertTrue(Application.createSocialProject("Social1", "Mi primer proyecto", 15000, Social.NATIONAL, "chinese")); // OK
		/** Admin Sign in and accepts the project */
		Application.signIn("admin", "admin");
		assertTrue(Application.adminAcceptProject("Nombre mu bonito", true));
		Application.showNotifications();

		/** Pepe Sign in and show the notifications */
		Application.signIn("Pepe", "123");
		Application.showNotifications();

		/** Manuel Logs in and creates 4 groups */
		Application.signIn("Manuel", "123");
		Application.createGroup("Animales", "d");
		Application.createGroup("Perros", "d", "Animales");
		Application.createGroup("Gatos", "d", "Animales");
		Application.createGroup("Cachorros", "d", "Perros");
		Application.showNotifications();
		/** El jincho logs in and joins 2 groups: Perros y Gatos */
		Application.signIn("El Jincho", "123");
		Application.joinGroup("Perros");
		Application.joinGroup("Gatos");

		/** josete log in and joins groups 2: groups: Perros y Gatos */
		Application.signIn("Josete", "123");
		Application.joinGroup("Perros");
		Application.joinGroup("Gatos");

		/** Manuel creates a project */
		Application.signIn("Manuel", "123");
		assertTrue(Application.createInfrastructureProject("Gim", "d", 13, f, "Chamartín", "Perros"));
		Application.showNotifications();

		/** Admin accept Manuel´s project */
		Application.signIn("admin", "admin");
		assertTrue(Application.adminAcceptProject("VIVA", true));
		Application.showNotifications();

		/*
		 * El jincho , Manuel and Josete log in and shows their queues with the list of
		 * project and groups , that they support , create or participate
		 */
		Application.signIn("El Jincho", "123");
		Application.showNotifications();
		((Registered) app.getCurrentUser()).showMyQueues();

		Application.signIn("Manuel", "123");
		Application.showNotifications();
		((Registered) app.getCurrentUser()).showMyQueues();

		Application.signIn("Josete", "123");
		Application.showNotifications();
		((Registered) app.getCurrentUser()).showMyQueues();

		/** admin log in but there are no project to accept */
		Application.signIn("admin", "admin");
		assertFalse(Application.adminAcceptProject("VIVA", true));
		/** Manuel is banned tester */
		Application.banUser("Manuel");
		Application.showNotifications();
		/** Manuel can not create a project or a group because he is banned */
		Application.signIn("Manuel", "123");
		assertFalse(Application.createInfrastructureProject("hola que ase", "hola", 13, f, "Chamartín", "Perros")); // ERROR
																													// BANNED
		Application.createGroup("Hot dogs", "amigos de los animales", "Perros"); // ERROR BANNED
		assertFalse(Application.voteProject("Gim")); // ERROR BANNED
		Application.showNotifications();
		((Registered) app.getCurrentUser()).showMyQueues();

		/** Manuel Unbanned/ */
		Application.signIn("admin", "admin");
		Application.unbanUser("Manuel");

		Application.showNotifications();
		/** Manuel is unbanned so he can do things into the app */
		Application.signIn("Manuel", "123");
		/** Manuel votes support project Social1 and ask for a popularity report */
		assertTrue(Application.voteProject("Social1")); // OK UNBANNED
		Application.getPopularityReport("Gim");
		Application.showNotifications();

		Application.signIn("admin", "admin");
		Application.banUser("Josete");
		/**
		 * Manuel ask for popularity report of project Hospital but this doesn´t exist
		 * so this returns false
		 */
		Application.signIn("Manuel", "123");
		assertFalse(Application.getPopularityReport("Hospital")); // EROR DOES NOT EXIST
		assertTrue(Application.getPopularityReport("Gim")); // Ok
		Application.showNotifications();
	}

}

