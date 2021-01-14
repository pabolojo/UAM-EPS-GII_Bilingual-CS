package Tests;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import App.Application;

/**
 * This GroupTest class test all the functionalities of the Group class
 * 
 * 
 *
 */
class GroupTest {
	/**
	 * This method implements the functionalities of group
	 * 
	 */

	@Test
	void Group() {
		/** Pepe and Juan sing up int the application */
		Application app = Application.getApplication();
		Application.signUp("Pepe", "123", "123", "12345678L");
		Application.signUp("Juan", "123", "123", "12355678L");

		/** Pepe creates a 1 group and 2 subgroups everything goes well */
		Application.signIn("Pepe", "123");
		assertTrue(Application.createGroup("Animals", "description"));
		assertTrue(Application.createGroup("Cats", "description", "Animals"));
		assertTrue(Application.createGroup("Dogs", "description", "Animals")); // Ok because Pepe is the representative
		/**
		 * Pepe tries to create another group but this doen´t works because the group
		 * already exist
		 */ // of Animals
		assertFalse(Application.createGroup("Dogs", "description", "Animals")); // False because Dogs group already
																				// exists
		/**
		 * Pepe sing in into the application and tries to create the group cats he can´t
		 * do it because he is NOT the representative of Animals
		 */
		Application.signIn("Juan", "123");
		assertFalse(Application.createGroup("Cats", "description", "Animals")); // No because Juan is NOT the
																				// representative of Animals

		/** Pepe tries to join a group in which he are , so he can´t do it */
		Application.signIn("Pepe", "123");
		assertFalse(Application.joinGroup("Animals")); // False owner can NOT join
		/** Pepe tries to join 4 differents groups */
		Application.signIn("Juan", "123");
		/** False because the group does NOT exist */
		assertFalse(Application.joinGroup("Birds"));
		/** ok */
		assertTrue(Application.joinGroup("Cats"));
		/**
		 * False because Juan is already member of Cats which is a subgroup of Animals
		 */
		assertFalse(Application.joinGroup("Animals"));
		/** OK because Dogs and cats are at the same level */
		assertTrue(Application.joinGroup("Dogs"));

		/*
		 * Pepe tries to leave the Animals group but he can´t do that because he is the
		 * owner
		 */
		Application.signIn("Pepe", "123");
		assertFalse(Application.leaveGroup("Animals"));
		/** admin ban Juan so he can´t do nothing in the app */
		Application.signIn("admin", "admin");
		Application.banUser("Juan");

		Application.signIn("Juan", "123");
		/** false he is banned */
		assertFalse(Application.leaveGroup("Dogs"));
		/** Juan is unbanned by the admin */
		Application.signIn("admin", "admin");
		Application.unbanUser("Juan");
		Application.showNotifications();
		/** Now Juan can do all the things , that a registered user can do */
		Application.signIn("Juan", "123");
		/** Juan leaves the group Dogs */
		assertTrue(Application.leaveGroup("Dogs")); // Ok
		Application.showNotifications();
		/**
		 * He wants a affinity report of Dogs and cats but he can´t has it because he is
		 * not in Dogs
		 */
		assertFalse(Application.getAffinityReport("Dogs", "Cats"));
		/**
		 * He request for a affinity report and he obtains it , because he is in both
		 * groups
		 */
		Application.joinGroup("Dogs");
		assertTrue(Application.getAffinityReport("Dogs", "Cats"));
		Application.showNotifications();
	}
}

