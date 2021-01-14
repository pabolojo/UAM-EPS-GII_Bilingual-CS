package Tests;

import static org.junit.jupiter.api.Assertions.*;
import java.io.File;
import java.io.IOException;

import org.junit.jupiter.api.Test;
import App.Application;
import Modules.Social;
import es.uam.eps.sadp.grants.CCGG;
import es.uam.eps.sadp.grants.InvalidIDException;
import es.uam.eps.sadp.grants.InvalidRequestException;
import modifiableDates.ModifiableDate;

/**
 * This ApplicationTest class test all the functionalities of the app
 * 
 * 
 *
 */

class ApplicationTest {

	/**
	 * This method implements the functionalities of app
	 * 
	 */
	@Test
	void Application() {

		Application app = Application.getApplication();
		/** SignUp OKs */
		assertTrue(Application.signUp("Pepe", "123", "123", "12345678L"));
		assertTrue(Application.signUp("Juan Jesus", "123", "123", "22345678L"));
		assertTrue(Application.signUp("Joaquin Juan", "123", "123", "33345678L"));
		assertTrue(Application.signUp("El Jincho", "123", "123", "77456789L"));
		/** ERROR: DIFFERENT PASSWORD */
		assertFalse(Application.signUp("Pedrito", "123123442", "hola", "55345678L"));

		/** SignIn OK */
		assertTrue(Application.signIn("Pepe", "123"));
		/** Create Tree of Groups: Same owner */
		assertTrue(Application.createGroup("Animals", "jungle"));
		assertTrue(Application.createGroup("CATS", "adorable animals ", "Animals"));
		assertTrue(Application.createGroup("Dogs", "adorable dogs ", "Animals"));
		/** OK */
		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

		/** SignIn OK */
		assertTrue(Application.signIn("El Jincho", "123"));
		/** Joins To Dogs */
		assertTrue(Application.joinGroup("Dogs"));
		/** Joins To CATS */
		assertTrue(Application.joinGroup("CATS"));
		/** OK */
		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

		/** SignIn OK */
		assertTrue(Application.signIn("Juan Jesus", "123"));
		/**
		 * ERROR: Juan Jesus is not the owner of Animals and can not create groups
		 * inside it
		 */
		assertFalse(Application.createGroup("Birds", "adorable dogs ", "Animals"));
		/** Joins To animals */
		assertTrue(Application.joinGroup("Dogs"));
		/**
		 * ERROR: Can NOT create a project as a group if is not the owner of the group
		 */
		assertFalse(Application.createSocialProject("Social1", "Mi primer proyecto", 15000, Social.NATIONAL, "chinese",
				"Animals"));
		/** Can create a project as an individual citizen */
		assertTrue(Application.createSocialProject("Social2", "Mi primer proyecto", 15000, Social.NATIONAL, "chinese"));
		/** OK */
		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

		/** SignIn OK: Admin */
		assertTrue(Application.signIn("admin", "admin"));
		/** Admin accepts first project in the queue */
		assertTrue(Application.adminAcceptProject("I love social projects", true));
		/** ERROR: There are no more projects in the queue */
		assertFalse(Application.adminAcceptProject("Hello", false));
		/** OK: User banned */
		assertTrue(Application.banUser("Juan Jesus"));
		/** OK */
		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

		/** SignIn OK */
		assertTrue(Application.signIn("Pepe", "123"));
		/** Can create a project as a group because he is the owner of the group */
		assertTrue(Application.createSocialProject("Animals social", "I love animals", 3000000, Social.NATIONAL,
				"Arabian", "Animals"));
		/** ERROR: Group Birds does not exist */
		assertFalse(Application.createSocialProject("Social3", "I love animals", 20000, Social.INTERNATIONAL, "Jewish",
				"Birds"));
		/** Can create a project as a group because he is the owner of the group */
		assertTrue(Application.createSocialProject("Social3", "I love animals", 20000, Social.INTERNATIONAL, "Jewish",
				"Dogs"));

		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

		/** SignIn OK */
		assertTrue(Application.signIn("Juan Jesus", "123"));
		/** ERROR: Can not create a group if he is banned */
		assertFalse(Application.createGroup("Hot dogs", "description"));
		/** ERROR: Can not vote a project if he is banned */
		assertFalse(Application.voteProject("Social3"));
		/** ERROR: Can not leave a group if he is banned */
		assertFalse(Application.leaveGroup("Dogs"));
		/** OK */
		assertTrue(Application.showNotifications());

		/** SignIn OK: Admin */
		assertTrue(Application.signIn("admin", "admin"));
		/** Admin accepts first project in the queue */
		assertTrue(Application.adminAcceptProject("I love social projects", true));
		/** Admin accepts second project in the queue */
		assertTrue(Application.adminAcceptProject("Hello", true));
		/** Admin unbans user */
		assertTrue(Application.unbanUser("Juan Jesus"));
		/** ERROR: Threshold can not be lesser or equal than 0 */
		assertFalse(Application.setThreshold(0));
		/** Threshold set correctly */
		assertTrue(Application.setThreshold(3));
		/** OK */
		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

		/** SignIn OK */
		assertTrue(Application.signIn("Juan Jesus", "123"));
		/** User is no longer banned, can create the group */
		assertTrue(Application.createGroup("Food", "Lovers of food"));
		/** ERROR: Can not ask for popularity report if he has not voted */
		assertFalse(Application.getPopularityReport("Social3"));
		/** User is no longer banned, can vote the project */
		assertTrue(Application.voteProject("Social3", "Food"));
		/** Now he has voted and can ask for the popularity report */
		assertTrue(Application.getPopularityReport("Social3"));
		/** OK */
		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

		/** SignIn OK */
		assertTrue(Application.signIn("Joaquin Juan", "123"));
		/** Joins To Dogs */
		assertTrue(Application.joinGroup("Dogs"));
		/** ERROR: Asks for an affinity report between 2, but does not belong to both */
		assertFalse(Application.getAffinityReport("CATS", "Dogs"));
		/** Joins To CATS */
		assertTrue(Application.joinGroup("CATS"));
		/** Asks for an affinity report between 2 that he belongs to */
		assertTrue(Application.getAffinityReport("CATS", "Dogs"));
		/** OK */
		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

		/** Application is saved in file ApplicationSave */
		try {
			assertTrue(Application.saveApplication("ApplicationSave"));
		} catch (IOException e) {
			e.printStackTrace();
		}

		/** Application is restored from file ApplicationSave */
		try {
			assertTrue(Application.restoreApplication("ApplicationSave"));
		} catch (IOException e) {
			e.printStackTrace();
		}

		/** SignIn OK */
		assertTrue(Application.signIn("Joaquin Juan", "123"));
		/** ERROR: Can not subscribe if he has not voted */
		assertFalse(Application.subscribe("Animals social"));
		/** Votes to project, Project is Now Fundable!! */
		assertTrue(Application.voteProject("Animals social"));
		/** Now he can subscribe */
		assertTrue(Application.subscribe("Animals social"));
		/** OK */
		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

		/** SignIn OK */
		assertTrue(Application.signIn("Pepe", "123"));
		/** Pepe sees that he's project is fundable ans sends it for funding */
		try {
			assertTrue(Application.fundProject("Animals social")); // Sent to Councill Hall or exception
		} catch (IOException | InvalidRequestException e) {
			e.printStackTrace();
		}
		/** Pepe sees that he's project is fundable ans sends it for funding */
		ModifiableDate.plusDays(100);
		CCGG.getGateway().setDate(ModifiableDate.getModifiableDate());

		try {
			assertFalse(Application.checkProjectCouncilHall("Animals social")); // Decision: NO or exception
		} catch (IOException | InvalidIDException e) {
			e.printStackTrace();
		}

		/** OK */
		assertTrue(Application.showNotifications());
		/** SignOut OK */
		assertTrue(Application.signOut());

	}

}

