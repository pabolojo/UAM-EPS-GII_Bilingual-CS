package Modules;

import java.io.IOException;
/**
 * This CouncilHall class implements the communication with the external Council Hall app
 *
 *
 */

import App.Application;

import es.uam.eps.sadp.grants.*;

public class CouncilHall {
	/**
	 * council (CCGG) this variable gets the instance of the CCGG
	 */

	private static CCGG council = CCGG.getGateway();

	/**
	 * This method sends a project to the council hall to be evaluated
	 * 
	 * @param project project that is going to be send to the Council Hall
	 * @throws IOException             .Throws errors to IOException
	 * @throws InvalidRequestException .Throws errors to InvalidRequestException
	 * @return true if there is no error else false
	 *
	 */
	public static boolean sendCouncilHall(Project project) throws IOException, InvalidRequestException {
		String id = null;
		try {
			id = council.submitRequest(project);
		} catch (IOException | InvalidRequestException e) {
			throw e;
		}
		project.setUniqueID(id);
		return true;
	}

	/**
	 * This method checks if a project has been accepted or rejected
	 * 
	 * @param p project to be checked
	 * @throws IOException        .Throws errors to IOException
	 * @throws InvalidIDException .Throws errors to InvalidIDException
	 * @return true if the project is accept otherwise false
	 *
	 */
	public static boolean checkProjectCouncilHall(Project p) throws IOException, InvalidIDException {
		Application app = Application.getApplication();
		String id = p.getUniqueID();
		Double amount = null;
		if (id == null) {
			app.getCurrentUser()
					.sendNotification(new Notification("You have to send your project to the Council Hall"));
			return false;
		}
		try {
			amount = council.getAmountGranted(id);

		} catch (IOException | InvalidIDException e) {
			throw e;
		}
		if (amount == null) {
			app.getCurrentUser()
					.sendNotification(new Notification("Project is still being reviewed by the Council Hall"));
			return false;
		}
		return p.setGrantedBudget(amount);
	}
}

