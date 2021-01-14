package Tests;

import static org.junit.jupiter.api.Assertions.*;

import java.io.File;
import java.io.IOException;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import App.Application;
import es.uam.eps.sadp.grants.CCGG;
import es.uam.eps.sadp.grants.InvalidIDException;
import es.uam.eps.sadp.grants.InvalidRequestException;
import modifiableDates.ModifiableDate;

/**
 * This CouncilHallTest class test all the functionalities of the CouncilHall
 * class
 * 
 * 
 *
 */

class CouncilHallTest {
	/**
	 * This method Sets up the application calling methods that call constructors
	 */
	void setUp() {

		Application app = Application.getApplication();
		File f = new File("hola");
		CCGG.getGateway().setDate(ModifiableDate.getModifiableDate());
		/** Pepe and Juan Sign Up into the app */
		Application.signUp("Pepe", "123", "123", "12345678L");
		Application.signUp("Juan", "123", "123", "12355678L");
		/** Pepe Sign in into the app and creates a Infrastrucutre project */
		Application.signIn("Pepe", "123");
		Application.createInfrastructureProject("Animals", "flor", 1100, f, "Chamartín");
		/** The admin logs in and accept the project */
		Application.signIn("admin", "admin");
		Application.setThreshold(2);
		Application.adminAcceptProject("a", true);
	}

	@Test
	/**
	 * This method test the functionality of the sendCouncilHall method
	 * 
	 * @throws IOException             Throws errors to IOException
	 * @throws InvalidRequestException Throws errors to InvalidRequestException
	 */
	void testSendCouncilHall() throws IOException, InvalidRequestException {
		/** We call to the previous method to set up the test */
		setUp();
		/** Pepe sign in into the app */
		Application.signIn("Pepe", "123");
		try {
			/** Pepe tries to fund a project */
			assertFalse(Application.fundProject("Animals")); // Not enough votes or exception
		} catch (IOException | InvalidRequestException e) {
			e.printStackTrace();
		}
		Application.showNotifications();
		/** Juan sign in into the app */
		Application.signIn("Juan", "123");
		/** Votes the project Animals created by Pepe */
		Application.voteProject("Animals");
		/**
		 * Pepe sing in and try to fund the project animals , now the project can be
		 * sent because they have support
		 */
		Application.signIn("Pepe", "123");
		try {
			assertTrue(Application.fundProject("Animals")); // Sent to Council Hall or exception
		} catch (IOException | InvalidRequestException e) {
			e.printStackTrace();
		}
		Application.showNotifications();
	}

	@Test
	/**
	 * This method test the functionality of the sendCouncilHall method
	 * 
	 * @throws IOException             Throws errors to IOException
	 * @throws InvalidRequestException Throws errors to InvalidRequestException
	 * @throws InvalidIDException      Throws errors to InvalidIDException
	 */
	void testCheckProjectCouncilHall() throws IOException, InvalidRequestException, InvalidIDException {
		/** We call to the method setUp for setting up the app */
		setUp();
		File f = new File("hola");
		try {
			/**
			 * We call the method checkProject , this method returns a exception because the
			 * council hall has not responded yet
			 */
			assertFalse(Application.checkProjectCouncilHall("Animals")); // Not reviewed yet or exception
		} catch (IOException | InvalidIDException e) {
			e.printStackTrace();
		}
		/** We added 8 days */
		ModifiableDate.plusDays(8);
		CCGG.getGateway().setDate(ModifiableDate.getModifiableDate());

		try {
			/**
			 * We call another time the previous method but this time we obtain accept or
			 * reject
			 */
			Application.checkProjectCouncilHall("Animals"); // Decision true or false or exception
		} catch (IOException | InvalidIDException e) {
			e.printStackTrace();
		}

		Application.showNotifications();
		/**
		 * Pepe sign in into the app and creates the project colors with a budget < 1000
		 */
		Application.signIn("Pepe", "123");
		Application.createInfrastructureProject("Colors", "flor", 100, f, "Chamartín");
		/** The admin accepts the project */
		Application.signIn("admin", "admin");
		Application.adminAcceptProject("a", true);
		/** Juan votes the project colors */
		Application.signIn("Juan", "123");
		Application.voteProject("Colors");
		/** Pepe logs in and tries to fund the project colors */
		Application.signIn("Pepe", "123");
		try {

			assertTrue(Application.fundProject("Colors")); // Sent to Council Hall or exception
		} catch (IOException | InvalidRequestException e) {
			e.printStackTrace();
		}
		/** We added 8 days */
		ModifiableDate.plusDays(8);
		CCGG.getGateway().setDate(ModifiableDate.getModifiableDate());

		try {
			/**
			 * We see if the project have been accepted but it can be accepted because the
			 * budget < 1000
			 */
			assertFalse(Application.checkProjectCouncilHall("Colors")); // Decision: NO or exception
		} catch (IOException | InvalidIDException e) {
			e.printStackTrace();
		}

		Application.showNotifications();
	}

}

