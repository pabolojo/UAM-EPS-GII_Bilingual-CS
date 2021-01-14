package Model.Modules;

/**
 * This Social class defines one of the two kinds of projects: Social
 *
 *
 */
public class Social extends Project {
	/**
	 * This are the attributes of application
	 *
	 * typeAim (File) aim of the project socialGroup (String) Social group that are
	 * going to receive the project NATIONAL (boolean) type of aim INTERNATIONAL
	 * (boolean) type of aim
	 *
	 */

	private boolean typeAim;
	private String socialGroup;
	public static final boolean NATIONAL = true;
	public static final boolean INTERNATIONAL = false;

	/**
	 * This is the registered constructor for social projects
	 * 
	 * @param name        name of the project
	 * @param description description of a project
	 * @param budget      budget of the project
	 * @param type        type of the project
	 * @param socialGroup socialGroup that is gone to receive the project
	 */
	public Social(String name, String description, double budget, boolean type, String socialGroup) {
		super(name, description, budget);
		this.typeAim = type;
		this.socialGroup = socialGroup;
	}

	/**
	 * This is the registered constructor for social projects
	 * 
	 * @param name        name of the project
	 * @param description description of a project
	 * @param budget      budget of the project
	 * @param type        type of the project
	 * @param socialGroup socialGroup that is gone to receive the project
	 * @param g           Group that has proposed the project
	 */
	public Social(String name, String description, double budget, boolean type, String socialGroup, Group g) {
		super(name, description, budget, g);
		this.typeAim = type;
		this.socialGroup = socialGroup;
	}

	public String getSocialGroup() {
		return this.socialGroup;
	}

	public boolean getAim() {
		return this.typeAim;
	}

	/**
	 * This method returns Extra information about social project: The socialGroup
	 * 
	 * @return ExtraData of infrastructure project
	 */
	@Override
	public String getExtraData() {
		if (this.typeAim) {
			return "Project for " + this.socialGroup + " social group and with National aim";
		}
		return "Project for " + this.socialGroup + " social group and with International aim";
	}

	/**
	 * This method returns the kind of the project
	 * 
	 * @return Kind of the project
	 */
	@Override
	public ProjectKind getProjectKind() {
		return ProjectKind.Social;
	}
}

