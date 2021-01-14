package Tests;

import static org.junit.jupiter.api.Assertions.*;
import App.Application;
import org.junit.jupiter.api.Test;

/**
 * This AdminTest class test all the functionalities of the admin user
 * 
 * 
 *
 */

class AdminTest {

	@Test
	void Admin() {
		Application app = Application.getApplication();
		/** The admin sign Up into the application */
		Application.signUp("Pepe", "123", "123", "12345678A");
		Application.signIn("admin", "admin");
		/**
		 * Admin tries to accept project, but this return false because there are no
		 * projects to accept yet
		 */
		assertFalse(Application.adminAcceptProject("Reason", true)); // No projects to accept yet
		/** Pepe logs in and creates a project */
		Application.signIn("Pepe", "123");
		Application.createSocialProject("Name", "description", 1100, true, "socialGroup");
		/** The admin accept the project */
		Application.signIn("admin", "admin");
		assertTrue(Application.adminAcceptProject("Reason", false)); // 1 project to accept
	}

}

