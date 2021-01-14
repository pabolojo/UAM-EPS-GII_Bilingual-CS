package Tests;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import App.Application;

/**
 * This RegisteredTest class test all the functionalities of the Registered user
 * class
 * 
 * 
 *
 */
class RegisteredTest {

	/**
	 * This method implements the functionalities of Registered
	 * 
	 */

	@Test
	void Registered() {
		Application app = Application.getApplication();
		/** SignUp OKs */
		assertTrue(Application.signUp("Domens", "123", "123", "12345678L"));
		assertTrue(Application.signUp("Juan Jesus", "123", "123", "22345678L"));
		assertTrue(Application.signUp("Joaquin Juan", "123", "123", "33345678L"));
		assertTrue(Application.signUp("El Jincho", "123", "123", "77456789L"));
		/** ERROR: SignUp */
		assertFalse(Application.signUp("Javi", "123", "123", "774567891")); // Error wrong ID
		assertFalse(Application.signUp("Domens", "123", "123", "12345678L")); // Error already registered
		/** SignIn OK */
		assertTrue(Application.signIn("Domens", "123"));
		assertTrue(Application.signIn("22345678L", "123"));
		/** SignIn ERROR */
		assertFalse(Application.signIn("Domens", "hola")); // Wrong password
		assertFalse(Application.signIn("77456780L", "123")); // Wrong ID
	}

}

