package part6.ads.assignment3;

import java.util.*;
/**
* These are the functions and variables that define the StockManagement objects, the StockManagement class.
*/
public class StockManagement {
	private Map<Appliance, Integer> catalog;
	private static StockManagement INSTANCE; 

	/**
	 * Constructor of this class. 
	 * It is private so in can be instantiated just from inside the class.
	 */
	private StockManagement() {
		this.catalog = new HashMap<>();
	}

	/**
	 * StockManagement getter. It follows the singleton pattern.
	 * @return INSTANCE .
	 */
	public static StockManagement getStockManagement() {
		if(INSTANCE == null) {
			INSTANCE= new StockManagement();
		}
		return INSTANCE;
	}

	/**
	 * Function that adds a product with its number of units to the catalog of appliances.
	 * @param a The Appliance we are going to add.
	 * @param n The number of units.
	 * @return boolean
	 */
	public boolean addProduct(Appliance a, int n) {
		for (Appliance b : this.catalog.keySet()) {
			if(a.equals(b)) {
				return false;
			}
		}
		catalog.put(a, n);
		return true;
	}

	/**
	 * Function that updates a product with its number of units from the catalog of appliances.
	 * @param a The Appliance we are going to update.
	 * @param n The new number of units.
	 */
	public void updateProduct(Appliance a, int n) {
		catalog.replace(a, n);
	}

	/**
	 * Function that adds a unit to a product on the catalog of appliances.
	 * @param a The Appliance we are going to update.
	 */
	public void addUnit(Appliance a) {
		catalog.replace(a, catalog.get(a)+1);
	}

	/**
	 * Function that removes a unit from a product on the catalog of appliances.
	 * @param a The Appliance we are going to update.
	 * @return boolean value. False if there are 0 units or true if it could be done.
	 */
	public boolean removeUnit(Appliance a) {
		if(catalog.get(a)==0) {
			return false;
		}
		catalog.replace(a, catalog.get(a)-1);
		return true;
	}

	/**
	 * Function that removes a product from the catalog of appliances.
	 * @param a The Appliance we are going to remove.
	 * @return int the number of units of that appliance
	 */
	public int removeProduct(Appliance a) {
		return catalog.remove(a);
	}

	/**
	 * Function that shows the inventory of appliances.
	 * @return String with the inventory.
	 */
	public String getInventory() {
		String inventory = "";
		for(Map.Entry<Appliance, Integer> entry : catalog.entrySet()) {
			inventory = inventory.concat("Article: " + String.format(Locale.ROOT, "%40s",entry.getKey()) + "    Units:"+ String.format(Locale.ROOT, "%5d",entry.getValue()) +"\n");
		}
		return inventory;
	}

	/**
	 * Function that shows the inventory of appliances of a determined type.
	 * @param type The type of appliance of the inventory, that we are going to show.
	 * @return String with the inventory.
	 */
	public String getInventory(String type) {
		String inventory = "";
		for (Appliance a : this.catalog.keySet()) {
			if (a.getClass().getSimpleName().equals(type)) {
				inventory = inventory.concat("Article: " + String.format(Locale.ROOT, "%40s",a) + "    Units: " + String.format(Locale.ROOT, "%5d",catalog.get(a))+ "\n");
			}
		}
		return inventory;
	}	
}

