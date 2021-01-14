package Model.Modules;

import java.util.*;

import Model.App.Application;

/**
 * This Infrastructure class defines one of the two kinds of projects:
 * Infrastructure
 *
 *
 */

public class Infrastructure extends Project {

	/**
	 * This are the attributes of application
	 *
	 * graphicalSchema (File) neighborhoods (String) List of neighborhoods that the
	 * project can affect neighborhood (String) neighborhood that the project
	 * affects
	 *
	 */

	private String graphicalSchema;
	private static final List<String> neighborhoods = Application.getNeighborhoods();
	private String neighborhood;

	/**
	 * Constructor of this class.
	 *
	 * This is the method that implements the constructor of an Infrastructure
	 * project , this module Initialize the attributes of a Infrastructure project
	 *
	 * @param name            name of the project
	 * @param description     description of the project
	 * @param budget          budget for the project
	 * @param graphicalSchema File for the graphicalSchema, e.g, a blueprint
	 * @param neighborhood    neighborhood that this project is affecting
	 */

	public Infrastructure(String name, String description, double budget, String graphicalSchema, String neighborhood) {
		super(name, description, budget);
		this.graphicalSchema = graphicalSchema;
		this.neighborhood = neighborhood;
	}

	/**
	 * Constructor of this class.
	 *
	 * This is the method that implements the constructor of an Infrastructure
	 * project as a group, this module Initialize the attributes of a Infrastructure
	 * project
	 *
	 * @param name            name of the project
	 * @param description     description of the project
	 * @param budget          budget for the project
	 * @param graphicalSchema File for the graphicalSchema, e.g, a blueprint
	 * @param neighborhood    neighborhood that this project is affecting
	 * @param g               Group that has proposed the project
	 */

	public Infrastructure(String name, String description, double budget, String graphicalSchema, String neighborhood,
			Group g) {
		super(name, description, budget, g);
		this.graphicalSchema = graphicalSchema;
		this.neighborhood = neighborhood;
	}

	/**
	 * This method returns the list of all neighborhoods
	 * 
	 * @return list of neighborhoods
	 */

	public static List<String> getNeighborhoods() {
		return neighborhoods;
	}

	/**
	 * This method returns the neighborhood
	 * 
	 * @return neighborhood
	 */

	public String getNeighborhood() {
		return neighborhood;
	}

	/**
	 * This method returns Extra information about infrastructure project: The
	 * neighborhood
	 * 
	 * @return ExtraData of infrastrucutre project
	 */

	@Override
	public String getExtraData() {
		return "Infrastructure located in " + this.neighborhood + " neighborhood";
	}

	/**
	 * This method returns the kind of the project
	 * 
	 * @return Kind of the project
	 */

	@Override
	public ProjectKind getProjectKind() {
		return ProjectKind.Infrastructure;
	}

	/**
	 * This method returns the neighborhood
	 * 
	 * @return neighborhood
	 */

	public String getFileName() {
		return this.graphicalSchema;
	}
}

